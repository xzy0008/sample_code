


#include <vgStableHeaders.h>
#include <vgModel/vgmoModelItem.h>
#include <vgModel/vgmoFileDefinitionVmd.h>
#include <vgModel/vgmoModelData.h>
#include <vgAsyn/vgaIoRequest.h>
#include <vgModel/vgmoFileHandleVmd.h>
#include <vgKernel/vgkOpenGLSupport.h>



namespace vgModel {
	

	VGK_RENDERER_IMPLEMENT( ModelItem , RENDERER_TYPE_MODEL)

	//----------------------------------------------------------------
	ModelItem::ModelItem()
	{
		
		
		setDefault();


	}
	//----------------------------------------------------------------
	ModelItem::~ModelItem()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void ModelItem::destroy()
	{
		if ( _wholeFileInfo != NULL )
		{
			delete _wholeFileInfo;
			_wholeFileInfo = NULL;
		}

		//assert( _modelObject != NULL );
		//if ( _modelObject != NULL )
		//{
		//	delete _modelObject;
		//	_modelObject = NULL;
		//}

		if ( _meshData != NULL )
		{
			delete _meshData;
			_meshData = NULL;
		}
		if ( _meshDataFileInfo != NULL )
		{
			delete _meshDataFileInfo;
			_meshDataFileInfo = NULL;
		}
	}
	//----------------------------------------------------------------
	void ModelItem::setDefault()
	{
		//_modelObject = NULL;
		 _meshData = NULL;
		 _meshDataFileInfo = NULL;

		_isTransparent = false;

		_squareDistNear = VGLOD_SQU_DIST_NEAR;
		_squareDistFar = VGLOD_SQU_DIST_FAR;

		_squaredDistanceToViewer = 0.0f;

		_wholeFileInfo = NULL;

		_isVisible = true;

		_numberOfTriangles = 0;

		_distanceLod = VGLOD_COARSE;

		_currentLod = VGLOD_COARSE ;

	}
	//----------------------------------------------------------------
	String ModelItem::getDetails() 
	{
		std::ostringstream o;

		o << "ModelItem details:( "
			<< "_uniqueID: " << _uniqueID.getString()
			<< "_modelName: " << _modelName
			<< " );";

		return o.str();
	}
	//----------------------------------------------------------------
	bool ModelItem::dumpInfoToVmdBrief( VmdBrief* vgmbrief )
	{
		assert( vgmbrief != NULL );

		vgmbrief->setClassName( getClassName() );

		vgmbrief->_uniqueId = _uniqueID;

		assert( _modelName.size() < VMD_MODEL_NAME_LENGTH );
		String buf = _modelName;
		buf.resize( VMD_MODEL_NAME_LENGTH -1 );
		
		strcpy( vgmbrief->_modelName , buf.c_str() );

		vgmbrief->_colorQuad = *getRgbaQuadRef();
		vgmbrief->_dynamicBoundingBox = _dynamicBox;
		vgmbrief->_staticBoundingBox = _staticBox;
		vgmbrief->_multMatrix = _matrix;
		vgmbrief->_isVisible = _isVisible;
		vgmbrief->_numberOfFaces = _numberOfTriangles;

		assert( _wholeFileInfo != NULL );

		// 下面的_position项在写文件的时候要重新更新
		vgmbrief->_positionOfFile = _wholeFileInfo->_fileOffset;
		vgmbrief->_lengthOfFile = _wholeFileInfo->_fileSize;


		vgmbrief->_positionOfModelData = _meshDataFileInfo->_fileOffset;
		vgmbrief->_lengthOfModelData = _meshDataFileInfo->_fileSize;


		vgmbrief->_squaredDistanceOfLodNear = _squareDistNear;
		vgmbrief->_squaredDistanceOfLodFar = _squareDistFar;

		return true;
	}
	//----------------------------------------------------------------
	bool ModelItem::dumpFileInfoToBuffer( char*& whole_file , long& file_length )
	{
		assert( whole_file == NULL );
		assert( file_length == 0 );
		assert( _wholeFileInfo != NULL );

		vgAsyn::IoRequest* request = 
			new vgAsyn::IoRequest( _wholeFileInfo->clone() );

		request->setDeleteBufferFlag( false );
		request->setAsynchronousMode( false );

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
	float ModelItem::setDistanceToViewer( const Vec3& viewer_pos )
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

	void ModelItem::translate(const float& x, const float& y, const float& z)
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

	void ModelItem::rotateSelf(const float& angle, const float& x, const float& y, const float& z)
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
	void ModelItem::rotate(const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
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
	
	void ModelItem::scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
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
	void ModelItem::render()
	{
		if( _isVisible == false )
		{
			return;
		}

		//assert ( _meshLod[ _distanceLod ] != NULL );

		//_matrix;
		//_dynamicBox.render();
		//_staticBox.render();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glMultMatrixf(_matrix._m);

		_meshData->render( _distanceLod , getShadowCastEnable() ? 1 : 0, 
			_isTransparent,
			getRgbaQuadRef() );

		//for ( int i = VGLOD_CLEAR ; i >= 0 ; --i )
		//{
		//	if ( _meshLod[ i ]->hasModelData() == true )
		//	{
		//		_meshLod[ i ]->render( _distanceLod , _isTransparent,
		//			getRgbaQuadRef() );
		//		break;
		//	}
		//}

		glPopMatrix();
	}
	//----------------------------------------------------------------
	std::pair<bool, float> ModelItem::testIntersectWithTriangles( const vgKernel::Ray& ray )
	{
		vgKernel::Ray translatedRay;


		std::pair<bool, float> finalResult; // = vgKernel::Math::intersects( ray, _dynamicBox );
		finalResult.first = false;
		finalResult.second = 1e10;



			ModelData* data = _meshData;

			if ( data == NULL )
			{
				assert(0);
				//return std::make_pair( false , result.second );
				return finalResult;
			}

			vgKernel::Mat4 mat = _matrix;

			vgKernel::Math::invertMatrix( _matrix, mat );

			Vec3 orgi = vgKernel::Math::translateVec3(mat, ray.getOrigin());
			translatedRay.setOrigin( orgi );

			Vec3 endPoint = vgKernel::Math::translateVec3( mat, ray.getPoint(1));

			translatedRay.setDirection(Vec3(endPoint.x - orgi.x, endPoint.y -orgi.y, endPoint.z - orgi.z));

			finalResult = data->getRenderWay()->testIntersection(&translatedRay);

			if ( finalResult.first )
			{
				return finalResult;
			}



		return std::make_pair( false , finalResult.second );

	}
	//----------------------------------------------------------------
	bool ModelItem::testIntersectWithTriangles(
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

			ModelData* data = _meshData;

			if ( data == NULL )
			{
				//return std::make_pair( false , result.second );
				assert(0);
				return false;
			}

			vgKernel::Mat4 mat = _matrix;

			vgKernel::Math::invertMatrix( _matrix, mat );

			Vec3 orgi = vgKernel::Math::translateVec3(mat, segment.getNegEnd());

			Vec3 endPoint = vgKernel::Math::translateVec3( mat, segment.getPosEnd() );

			Segment3 translatedSeg( orgi , endPoint );

			if ( data->getRenderWay()->testIntersection(&translatedSeg) )
			{
				return true;
			}


		return false;
	}
	//----------------------------------------------------------------
	void ModelItem::renderInShadowMode()
	{
		if( _isVisible == false || getShadowCastEnable() == false )
		{
			return;
		}

		assert ( _meshData != NULL );

		////_matrix;
		////_dynamicBox.render();
		////_staticBox.render();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glMultMatrixf(_matrix._m);

		//if ( _meshLod[ VGLOD_CLEAR ]->hasModelData() == true )
		//{
		//	_meshLod[ VGLOD_CLEAR ]->forceRenderInShadowMode();
		//}
		_meshData->getRenderWay()->renderInShadowModeImpl();

		glPopMatrix();
	}
	//----------------------------------------------------------------
	void ModelItem::onLightDirectionChanged( const vgKernel::Vec3& light_dir )
	{
		ShadowCastObject::onLightDirectionChanged( light_dir );

		_meshData->getRenderWay()->changeLightDirectionImpl( light_dir );
	}
	//----------------------------------------------------------------
	void ModelItem::turnOnShadowCast( const vgKernel::Vec3& light_dir ,
		bool force_to_load )
	{
		assert( _meshData != NULL );
		// 只能为false。shadowmanager负责
		assert( getShadowCastEnable() == false );

		ShadowCastObject::turnOnShadowCast( light_dir , force_to_load );

		assert( getShadowCastEnable() == true );

		_meshData->getRenderWay()->turnOnShadowImpl( light_dir );

		return;
	}
	//----------------------------------------------------------------
	void ModelItem::turnOffShadowCast()
	{
		ShadowCastObject::turnOffShadowCast();

		_meshData->getRenderWay()->turnOffShadowImpl();
	}
	//----------------------------------------------------------------
	bool ModelItem::isTransparent()
	{
		return _isTransparent;
	}
	//----------------------------------------------------------------
	void ModelItem::setTransparent( bool set_to_transp /*= true */ )
	{
		_isTransparent = set_to_transp;
	}
	//----------------------------------------------------------------
	bool ModelItem::load( VmdBrief* vgmbrief , FileHandleVmd* filehandle,
		int version )
	{
		assert( vgmbrief != NULL );
		_uniqueID = vgmbrief->_uniqueId;
		setColorableValue( vgmbrief->_colorQuad );


		_squareDistNear = vgmbrief->_squaredDistanceOfLodNear;
		_squareDistFar = vgmbrief->_squaredDistanceOfLodFar;

		assert( _squareDistNear > 0.0f );
		assert( _squareDistFar > 0.0f );
		assert( _squareDistFar > _squareDistNear );


		_uniqueID = vgmbrief->_uniqueId;

		_modelName = vgmbrief->_modelName;
		_dynamicBox = vgmbrief->_dynamicBoundingBox;
		_staticBox = vgmbrief->_staticBoundingBox;
		_matrix = vgmbrief->_multMatrix;
		_isVisible = vgmbrief->_isVisible;
		_numberOfTriangles = vgmbrief->_numberOfFaces;


		_wholeFileInfo = new vgAsyn::FileInfo(_modelName , filehandle , 
			vgmbrief->_positionOfFile , vgmbrief->_lengthOfFile);


		//----------------------------------------------------------------
		//_modelObject = new Model( this , vgmbrief , filehandle );

		//_modelObject->load( );

		_meshDataFileInfo = new vgAsyn::FileInfo( 
			getName() , filehandle , 
			vgmbrief->_positionOfModelData , 
			vgmbrief->_lengthOfModelData );

		// 这个时候需要载入
		assert( _meshData == NULL );

		vgAsyn::IoRequest* request = NULL;
		assert( _meshDataFileInfo != NULL );
		vgAsyn::FileInfo* fileinfo = _meshDataFileInfo->clone();

		request = 	new vgAsyn::IoRequest( fileinfo  );
		request->setAsynchronousMode( false );
		request->setDeleteBufferFlag( false );
		request->sendRequestAndDoAsynHandlerFunc( true );

		//----------------------------------------------------------------
		assert( _meshData == NULL );
		_meshData = 	new ModelData();

		bool initok = _meshData->initialise(  request->getBuffer() , 
			request->getBufferSize() );
		assert( initok == true );
		assert( _meshData != NULL );

		initok = _meshData->initInMainThread();
		if ( initok == false )
		{
			assert(0);
			destroy();
			return false;
		}


#if VMD_RENDER_WAY == 0
		VGK_CHECK_OPENGL_ERROR();
		_meshData->convertToVboRenderWay();
		VGK_CHECK_OPENGL_ERROR();
#endif

		return true;
	}
	//----------------------------------------------------------------
	void ModelItem::invalidateTextures()
	{
		_meshData->getRenderWay()->invalidateTextures();
	}
	//----------------------------------------------------------------

}// end of namespace vgModel
