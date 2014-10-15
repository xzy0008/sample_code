


#include <vgStableHeaders.h>
#include <vgKernel/vgkRgbaQuad.h>
#include <vgMesh/vgmMeshItem.h>
#include <vgMesh/vgmFileDefinitionVgm.h>
#include <vgMesh/vgmMeshData.h>
#include <vgMesh/vgmMeshDataPlus.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgMesh/vgmIoRequestMeshData.h>




namespace vgMesh {
	

	VGK_RENDERER_IMPLEMENT( MeshItem , RENDERER_TYPE_MESH )

	//----------------------------------------------------------------
	MeshItem::MeshItem( )
	{
		
		
		setDefault();

	}
	//----------------------------------------------------------------
	MeshItem::~MeshItem()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void MeshItem::destroy()
	{
		if ( _wholeFileInfo != NULL )
		{
			delete _wholeFileInfo;
			_wholeFileInfo = NULL;
		}

		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			if ( _refMesh[i] != NULL )
			{
				_refMesh[i]->releaseRef();
				_refMesh[i] = NULL;
			}
		}
		
		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			if ( _meshLod[i] != NULL )
			{
				delete _meshLod[i];
				_meshLod[i] = NULL;
			}
		}
	}
	//----------------------------------------------------------------
	void MeshItem::setDefault()
	{
		_isTransparent = false;

		_squareDistNear = VGLOD_SQU_DIST_NEAR;
		_squareDistFar = VGLOD_SQU_DIST_FAR;

		_isLodMesh = true;

		_squaredDistanceToViewer = 0.0f;

		_wholeFileInfo = NULL;


		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			_meshLod[i] = NULL;
			_refMesh[i] = NULL;
		}

		_numberOfTriangles = 0;

		_distanceLod = VGLOD_COARSE;

		_currentLod = VGLOD_COARSE ;

		_viewReference  = 0;
	}
	//----------------------------------------------------------------
	String MeshItem::getDetails() 
	{
		std::ostringstream o;

		o << "MeshItem details:( "
			<< "_uniqueID: " << _uniqueID.getString()
			<< "_meshName: " << _meshName
			<< " );";

		return o.str();
	}
	//----------------------------------------------------------------
	bool MeshItem::dumpInfoToVgmBrief( VgmBrief* vgmbrief )
	{
		assert( vgmbrief != NULL );

		vgmbrief->_uniqueId = _uniqueID;

		assert( _meshName.size() < VGM_MESH_NAME_LENGTH );
		String buf = _meshName;
		buf.resize( VGM_MESH_NAME_LENGTH -1 );
		
		strcpy( vgmbrief->_meshName , buf.c_str() );

		vgmbrief->_colorQuad = *getRgbaQuadRef();
		vgmbrief->_dynamicBoundingBox = _dynamicBox;
		vgmbrief->_staticBoundingBox = _staticBox;
		vgmbrief->_multMatrix = _matrix;
		vgmbrief->_isVisible = getVisible();
		vgmbrief->_numberOfFaces = _numberOfTriangles;

		assert( _wholeFileInfo != NULL );

		// 下面的_position项在写文件的时候要重新更新
		vgmbrief->_positionOfFile = _wholeFileInfo->_fileOffset;
		vgmbrief->_lengthOfFile = _wholeFileInfo->_fileSize;

		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			assert( _meshLod[i] != NULL );

			vgmbrief->_positionOfMeshData[i] = _meshLod[i]->_meshDataFileInfo->_fileOffset;
			vgmbrief->_lengthOfMeshData[i] = _meshLod[i]->_meshDataFileInfo->_fileSize;
		
			vgmbrief->_positionOfMeshDataPlus[i] = _meshLod[i]->_meshDataPlusFileInfo->_fileOffset;
			vgmbrief->_lengthOfMeshPlus[i] = _meshLod[i]->_meshDataPlusFileInfo->_fileSize;
		}

		vgmbrief->_isLodMesh = _isLodMesh;
		vgmbrief->_squaredDistanceOfLodNear = _squareDistNear;
		vgmbrief->_squaredDistanceOfLodFar = _squareDistFar;

		return true;
	}
	//----------------------------------------------------------------
	bool MeshItem::dumpFileInfoToBuffer( char*& whole_file , long& file_length )
	{
		assert( whole_file == NULL );
		assert( file_length == 0 );
		assert( _wholeFileInfo != NULL );

		IoReqMeshItemDumpInfo* request = 
			new IoReqMeshItemDumpInfo( _wholeFileInfo->clone() );

		assert( request != NULL );

		// 实际为同步操作
		request->sendRequestAndDoAsynHandlerFunc( true );

		whole_file = request->getBuffer();
		assert( whole_file != NULL );

		file_length = _wholeFileInfo->_fileSize;
		assert( file_length > 0 );

		delete request;

		return true;
	}
	//----------------------------------------------------------------
	float MeshItem::setDistanceToViewer( const Vec3& viewer_pos )
	{
		//------------------------------------------
		// 1.首先通过包围盒计算与视点的距离.
		//------------------------------------------
		float delta[3];

		for ( int i = 0 ; i < 3 ; ++ i )
		{
			float _cur = viewer_pos[i];
			float _max = _dynamicBox._maxVertex.v[i];
			float _min = _dynamicBox._minVertex.v[i];

			if ( _cur > _max )
			{
				delta[i] = _cur - _max;
			}
			else if ( _cur < _min )
			{
				delta[i] = _min - _cur;
			}
			else
			{
				delta[i] = 0.0f;
			}
		}

		_squaredDistanceToViewer = 
			delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];

		//------------------------------------------
		// 2.更新_distanceLod
		//----------------------------------------------------------------
		if ( _squaredDistanceToViewer > _squareDistFar )
		{
			_distanceLod = VGLOD_COARSE;
		}
		else if( _squaredDistanceToViewer > _squareDistNear )
		{
			_distanceLod = VGLOD_COARSE + 1;
		}
		else
		{
			_distanceLod = VGLOD_COARSE + 2;
		}

		return _squaredDistanceToViewer;
	}
	//----------------------------------------------------------------
	void MeshItem::addViewRef()
	{
		++_viewReference;

		if ( _viewReference == 1 )
		{
			//------------------------------------------
			// 这个时候需要载入
			//------------------------------------------
			assert( _refMesh[0] == NULL );
			assert( _refMesh[1] == NULL );
			assert( _refMesh[2] == NULL );


			//------------------------------------------
			// !!重点!!
			// 不为lodMesh时,只载入最清晰的即可.
			//------------------------------------------
			if ( _isLodMesh == false )
			{
				_refMesh[ VGLOD_CLEAR ] = _meshLod[ VGLOD_CLEAR ];
				_refMesh[ VGLOD_CLEAR ]->addRef( false );
			}
			else
			{
				//------------------------------------------
				// 默认载入最模糊的一级
				//------------------------------------------
				_refMesh[ VGLOD_COARSE ] = _meshLod[ VGLOD_COARSE ];
				_refMesh[ VGLOD_COARSE ]->addRef( false );

				//------------------------------------------
				// 这个时候_currentLod应该还没有更新
				//------------------------------------------
				if ( _distanceLod != VGLOD_COARSE )
				{
					_refMesh[ _distanceLod ] = _meshLod[ _distanceLod ];
					_refMesh[ _distanceLod ]->addRef( false );
				}
			}
		}

		if ( _isLodMesh == true )
		{
			updateMeshLod();
		}
		else
		{
			if ( _refMesh[ VGLOD_CLEAR ] == NULL )
			{
				_refMesh[ VGLOD_CLEAR ] = _meshLod[ VGLOD_CLEAR ];
				_refMesh[ VGLOD_CLEAR ]->addRef( false );
			}
		}
	}
	//----------------------------------------------------------------
	void MeshItem::releaseViewRef()
	{
		if( _viewReference <= 0 )
		{
			assert(0);
			return;
		}

		-- _viewReference;

		if ( _viewReference == 0 )
		{
			//------------------------------------------
			// 此时需要卸载掉
			//------------------------------------------
			for ( int i = 0 ; i < VGLOD_N ; ++ i )
			{
				if ( _refMesh[i] != NULL )
				{
					_refMesh[i]->releaseRef();
					_refMesh[i] = NULL;
				}
			}
		}
	}

	//----------------------------------------------------------------
	void MeshItem::updateMeshLod()
	{
		// 首先检查是否有lod的更新
		if ( _currentLod != _distanceLod )
		{
			_currentLod = _distanceLod;

			if ( _currentLod == VGLOD_COARSE )
			{
				//------------------------------------------
				// 当为最不清晰的一层时,
				// 卸载其他级即可.
				//------------------------------------------

				for ( int i = 1 ; i < VGLOD_N ; ++ i )
				{
					if ( _refMesh[i] != NULL )
					{
						_refMesh[i]->releaseRef();
						_refMesh[i] = NULL;
					}
				}
			}
			else if ( _currentLod == VGLOD_CLEAR )
			{
				//------------------------------------------
				// 当为最清晰的一级时,只要确认
				// Clearest Observer 载入即可
				//------------------------------------------
				if( _refMesh[ VGLOD_CLEAR ] == NULL )
				{
					_refMesh[ VGLOD_CLEAR ] = _meshLod[ VGLOD_CLEAR ];
					_refMesh[ VGLOD_CLEAR ]->addRef( false );
				}
				else
				{
					// 在最清晰一级已经载入的情况下,卸载第二级
					if ( _refMesh[ VGLOD_COARSE + 1 ] != NULL )
					{
						_refMesh[ VGLOD_COARSE + 1 ]->releaseRef();
						_refMesh[ VGLOD_COARSE + 1 ] = NULL;
					}
				}
			}
			else
			{
				//------------------------------------------
				// 当为中间的一级时
				//------------------------------------------

				// 检查最清晰的是否已经载入
				if ( _refMesh[ VGLOD_CLEAR ] != NULL &&
					_refMesh[ VGLOD_COARSE + 1 ] != NULL)
				{
					_refMesh[ VGLOD_CLEAR ]->releaseRef();
					_refMesh[ VGLOD_CLEAR ] = NULL;
				}
				//else if ( observers[ VGLOD_CLEAR ] != NULL && 
				//	observers[ VGLOD_COARSE + 1 ] == NULL )
				//{
				//	// do nothing.
				//}
				else if ( _refMesh[ VGLOD_COARSE + 1 ] == NULL )
				{
					// 检查中间级,没载入的话,将其载入.
					_refMesh[ VGLOD_COARSE + 1 ] = _meshLod[ VGLOD_COARSE + 1 ];
					_refMesh[ VGLOD_COARSE + 1 ]->addRef( false );
				}
			}
		}
	}

	//----------------------------------------------------------------

	void MeshItem::translate(const float& x, const float& y, const float& z)
	{
		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		//TRACE("translate Matrix \n");


		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

		this->notifyOberversOnEvent(VG_OBS_PROPCHANGED, NULL);
	}
	
	//----------------------------------------------------------------

	void MeshItem::rotateSelf(const float& angle, const float& x, const float& y, const float& z)
	{
		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(-_dynamicBox.getCenter().x, -_dynamicBox.getCenter().y, -_dynamicBox.getCenter().z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createRotationMatrix(angle, x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;
		
		vgKernel::Math::createTranslationMatrix(_dynamicBox.getCenter().x, _dynamicBox.getCenter().y, _dynamicBox.getCenter().z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;
		
		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);
	}
	 
	//----------------------------------------------------------------
	void MeshItem::rotate(const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
	{
		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(-cx, -cy, -cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createRotationMatrix(angle, x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(cx, cy,cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);
	}

	//----------------------------------------------------------------
	
	void MeshItem::scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
	{
		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;


		vgKernel::Math::createTranslationMatrix(-cx, -cy, -cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createScaleMatrix(x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(cx, cy,cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);
	}

	//----------------------------------------------------------------
	void MeshItem::render()
	{
		if( getVisible() == false )
		{
			return;
		}

		assert ( _meshLod[ _distanceLod ] != NULL );

		//_matrix;
		//_dynamicBox.render();
		//_staticBox.render();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glMultMatrixf(_matrix._m);

		for ( int i = VGLOD_CLEAR ; i >= 0 ; --i )
		{
			if ( _meshLod[ i ]->hasMeshData() == true )
			{
				_meshLod[ i ]->render( _distanceLod , _isTransparent,
					getRgbaQuadRef() );
				break;
			}
		}

		glPopMatrix();
	}
	//----------------------------------------------------------------
	std::pair<bool, float> MeshItem::testIntersectWithTriangles( const vgKernel::Ray& ray )
	{
		vgKernel::Ray translatedRay;


		std::pair<bool, float> finalResult; // = vgKernel::Math::intersects( ray, _dynamicBox );
		finalResult.first = false;
		finalResult.second = 1e10;
		//------------------------------------------
		// 从最清晰的开始遍历
		//------------------------------------------
		for ( int i = VGLOD_CLEAR ; i >=0  ; --i )
		{
			Mesh* curlod = getMeshByLod( i );
			assert( curlod != NULL );

			MeshData* data = curlod->getMeshData();

			if ( data == NULL )
			{
				//return std::make_pair( false , result.second );
				continue;
			}

			vgKernel::Mat4 mat = getTranslationMaxtrix();

			vgKernel::Math::invertMatrix( getTranslationMaxtrix(), mat );

			Vec3 orgi = vgKernel::Math::translateVec3(mat, ray.getOrigin());
			translatedRay.setOrigin( orgi );

			Vec3 endPoint = vgKernel::Math::translateVec3( mat, ray.getPoint(1));

			translatedRay.setDirection(Vec3(endPoint.x - orgi.x, endPoint.y -orgi.y, endPoint.z - orgi.z));

			finalResult = data->getRenderWay()->testIntersection(&translatedRay);

			if ( finalResult.first )
			{
				return finalResult;
			}
		}

		return std::make_pair( false , finalResult.second );

	}
	//----------------------------------------------------------------
	bool MeshItem::testIntersectWithTriangles(
		const vgKernel::Segment3& segment )
	{
		using namespace vgKernel;

		bool result = vgKernel::Math::intersects( segment, _dynamicBox );

		if ( result == false )
		{
			return false;
		}

		//------------------------------------------
		// 从最清晰的开始遍历
		//------------------------------------------
		for ( int i = VGLOD_CLEAR ; i >=0  ; --i )
		{
			Mesh* curlod = getMeshByLod( i );
			assert( curlod != NULL );

			MeshData* data = curlod->getMeshData();

			if ( data == NULL )
			{
				//return std::make_pair( false , result.second );
				continue;
			}

			vgKernel::Mat4 mat = getTranslationMaxtrix();

			vgKernel::Math::invertMatrix( getTranslationMaxtrix(), mat );

			Vec3 orgi = vgKernel::Math::translateVec3(mat, segment.getNegEnd());

			Vec3 endPoint = vgKernel::Math::translateVec3( mat, segment.getPosEnd() );

			Segment3 translatedSeg( orgi , endPoint );

			if ( data->getRenderWay()->testIntersection(&translatedSeg) )
			{
				return true;
			}
		}

		return false;
	}
	//----------------------------------------------------------------
	void MeshItem::renderInShadowMode()
	{
		if( getVisible() == false || getShadowCastEnable() == false )
		{
			return;
		}

		assert ( _meshLod[ _distanceLod ] != NULL );

		//_matrix;
		//_dynamicBox.render();
		//_staticBox.render();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glMultMatrixf(_matrix._m);

		if ( _meshLod[ VGLOD_CLEAR ]->hasMeshData() == true )
		{
			_meshLod[ VGLOD_CLEAR ]->forceRenderInShadowMode();
		}

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void MeshItem::onLightDirectionChanged( const vgKernel::Vec3& light_dir )
	{
		ShadowCastObject::onLightDirectionChanged( light_dir );

		_meshLod[ VGLOD_CLEAR ]->changeLightDirectionImpl();
	}
	//----------------------------------------------------------------
	void MeshItem::turnOnShadowCast( const vgKernel::Vec3& light_dir ,
		bool force_to_load )
	{
		// 只能为false。shadowmanager负责
		assert( getShadowCastEnable() == false );

		ShadowCastObject::turnOnShadowCast( light_dir , force_to_load );

		assert( getShadowCastEnable() == true );

		Mesh& msh = *_meshLod[ VGLOD_CLEAR ];

		//------------------------------------------
		// 倘若已经载入了plus data，那么就不用再载入了
		//------------------------------------------
		if ( msh.hasMeshPlusData() == true )
		{
			msh.addRef( force_to_load );
			// 设置载入shadow的标记
			// 注意，只针对最清晰的一级
			msh.turnOnShadowImpl();
			msh.changeLightDirectionImpl();
			return;
		}

		int refcount = msh.getReferenceCount();

		// 首先清空数据
		while ( msh.getReferenceCount() != 0 )
		{
			msh.releaseRef();
		}

		// 设置载入shadow的标记
		// 注意，只针对最清晰的一级
		msh.turnOnShadowImpl();

		while ( msh.getReferenceCount() != refcount )
		{
			msh.addRef( force_to_load );
		}

		// 再多添加一次ref
		msh.addRef( force_to_load );

		assert( msh.getReferenceCount() == refcount + 1 );

		return;
	}
	//----------------------------------------------------------------
	void MeshItem::turnOffShadowCast()
	{
		ShadowCastObject::turnOffShadowCast();

		_meshLod[ VGLOD_CLEAR ]->turnOffShadowImpl();
		// 释放多添加的ref
		_meshLod[ VGLOD_CLEAR ]->releaseRef();
	}
	//----------------------------------------------------------------
	bool MeshItem::isTransparent()
	{
		return _isTransparent;
	}
	//----------------------------------------------------------------
	void MeshItem::setTransparent( bool set_to_transp /*= true */ )
	{
		_isTransparent = set_to_transp;
	}

	bool MeshItem::initialise( VgmBrief* vgmbrief , vgAsyn::FileHandle* filehandle )
	{

		assert( vgmbrief != NULL );

		_uniqueID = vgmbrief->_uniqueId;

		setColorableValue( vgmbrief->_colorQuad );
		_isLodMesh = vgmbrief->_isLodMesh;

		_squareDistNear = vgmbrief->_squaredDistanceOfLodNear;
		_squareDistFar = vgmbrief->_squaredDistanceOfLodFar;

		assert( _squareDistNear > 0.0f );
		assert( _squareDistFar > 0.0f );
		assert( _squareDistFar > _squareDistNear );


		_uniqueID = vgmbrief->_uniqueId;

		_meshName = vgmbrief->_meshName;
		_dynamicBox = vgmbrief->_dynamicBoundingBox;
		_staticBox = vgmbrief->_staticBoundingBox;
		_matrix = vgmbrief->_multMatrix;
		setVisible( vgmbrief->_isVisible );
		_numberOfTriangles = vgmbrief->_numberOfFaces;


		_wholeFileInfo = new vgAsyn::FileInfo(_meshName , filehandle , 
			vgmbrief->_positionOfFile , vgmbrief->_lengthOfFile);

		for ( int i = 0 ; i < VGLOD_N ; ++ i )
		{
			assert( _meshLod[i] == NULL );
			_meshLod[i] = new Mesh( this , vgmbrief , filehandle , i );
		}

		return true;
	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	//----------------------------------------------------------------
	IoReqMeshItemDumpInfo::IoReqMeshItemDumpInfo( 
		vgAsyn::FileInfo* fileinfo ) 
		: IoRequest( fileinfo )
	{
		// 设置同步模式
		setAsynchronousMode( false );

		// 设置buffer的不自动删除
		setDeleteBufferFlag( false );

	}
	//----------------------------------------------------------------
	IoReqMeshItemDumpInfo::~IoReqMeshItemDumpInfo()
	{

	}
	//----------------------------------------------------------------
	bool IoReqMeshItemDumpInfo::anotherThreadHandler()
	{

		return true;
	}

	bool IoReqMeshItemDumpInfo::mainThreadHandler()
	{

		return true;
	}

	//----------------------------------------------------------------
}// end of namespace vgMesh
