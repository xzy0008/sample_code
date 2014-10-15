


#include <vgStableHeaders.h>
#include <vgShape/vgshLayer.h>


#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>

//#include <vgTerritory/vgtTerrainManager.h>


namespace vgShape {
	
	

	VGK_RENDERER_IMPLEMENT( Layer , RENDERER_TYPE_SHAPE_LAYER )


	Layer::TravGeoForRender Layer::_traverseGeoRender;
	Layer::TravGeoForCreateDisplayList Layer::_traversForCreateDisplayList;

	

	//----------------------------------------------------------------
	Layer::Layer()
	{

		_transX = 0.0f;
		_transY = 0.0f;
		_transZ = 0.0f;


		_inEditMode = false;
		_numOfPoints = 0;
		_uniqueID = vgKernel::UniqueIDFactory::getUniqueID();

		_matrix = vgKernel::Mat4::IDENTITY;

		_dynamicBox = _staticBox = vgKernel::Box::NULL_BOX;

		_displayListID = 0;
	}
	//----------------------------------------------------------------
	//----------------------------------------------------------------
	void Layer::render()
	{
		if ( getVisible() == false )
		{
			return;
		}

		_matrix._m[13] = _transY;



		glDisable(GL_CULL_FACE);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glMultMatrixf(_matrix._m);

		if ( _inEditMode == false )
		{
			if ( _displayListID == 0 )
			{
				_displayListID = glGenLists( 1 );   
				assert( _displayListID != 0 );

				glNewList( _displayListID, GL_COMPILE );
				for_each(_geometries.begin() , 
					_geometries.end() , 
					_traversForCreateDisplayList );
				glEndList();	

				////------------------------------------------
				//// 删除临时数据
				////------------------------------------------
				//GeometryPointerVec::iterator iter = _geometries.begin();
				//GeometryPointerVec::iterator iter_end = _geometries.end();

				//for ( ; iter != iter_end ; ++ iter )
				//{
				//	Geometry* geo = *iter;
				//	geo->clearRecoverableData();
				//}
			}

			glPushMatrix();
			glCallList( _displayListID );
			glPopMatrix();
		}
		else
		{
			for_each(_geometries.begin() , 
				_geometries.end() , 
				_traverseGeoRender );
		}

		//------------------------------------------
		// 渲染选择物体
		//------------------------------------------
		glPushMatrix();
		{
			GeometryPointerVec::iterator iter = _selectedGeometries.begin();
			GeometryPointerVec::iterator iter_end = _selectedGeometries.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				(*iter)->renderInSelectedMode();
			}
		}
		glPopMatrix();

		glPopMatrix();

		return;
	}
	//----------------------------------------------------------------
	void Layer::translate( const float& x, const float& y, const float& z )
	{
		_transX += x;
		_transY += y;
		_transZ += z;

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		//TRACE("translate Matrix \n");

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

		this->notifyOberversOnEvent( vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
	//----------------------------------------------------------------
	void Layer::scale( const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z )
	{
		//vgKernel::Mat4 tran;
		//vgKernel::Mat4 tmp;


		//vgKernel::Math::createTranslationMatrix(-cx, -cy, -cz, tran);
		//vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		//_matrix = tmp;

		//vgKernel::Math::createScaleMatrix(x, y, z, tran);
		//vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		//_matrix = tmp;

		//vgKernel::Math::createTranslationMatrix(cx, cy,cz, tran);
		//vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		//_matrix = tmp;

		//_dynamicBox = _staticBox;
		//_dynamicBox.matrixTranslation(_matrix);
	}
	//----------------------------------------------------------------
	void Layer::pushGeometry( Geometry* geo )
	{
		_geometries.push_back( geo );

		_numOfPoints += geo->getNumOfPoints();

		//------------------------------------------
		// 计算包围盒信息
		//------------------------------------------

		_staticBox.merge( geo->getEnvelope3f() );
		_dynamicBox = _staticBox;

		return;
	}
	//----------------------------------------------------------------
	void Layer::destroy()
	{
		GeometryPointerVec::iterator iter = _geometries.begin();
		GeometryPointerVec::iterator iter_end = _geometries.end();

		for ( ; iter != iter_end
			; ++ iter )
		{
			delete *iter;
		}

		_geometries.clear();

		if ( _displayListID != 0 )
		{
			glDeleteLists( _displayListID , 1 );
			_displayListID = 0;
		}
	}
	//----------------------------------------------------------------
	Geometry* Layer::testIntersectWithGeometry( const RayLine3d& rayline )
	{
		//------------------------------------------
		// 首先判断是否和layer的box相交
		//------------------------------------------
		std::pair<bool, float> result = vgKernel::Math::intersects( 
			rayline.getRay3d().getRayFloat(), _dynamicBox );

		if ( result.first == false )
		{
			return NULL;
		}


		//------------------------------------------
		// 计算转换的ray
		//------------------------------------------
		//Ray3d translatedRay = ray;
		RayLine3d transRayline;

		vgKernel::Mat4 mat = _matrix;
		mat.inverse();

		vgKernel::Vec3 p1 = vgKernel::Math::translateVec3( mat, rayline._pointStart.getVec3Float() );
		transRayline._pointStart = Vec3d( p1 );

		vgKernel::Vec3 p2 = vgKernel::Math::translateVec3( mat, rayline._pointEnd.getVec3Float() );
		transRayline._pointEnd = Vec3d( p2 );



		//vgKernel::Mat4 mat = _matrix;
		//mat.inverse();

		//vgKernel::Vec3 orgi = vgKernel::Math::translateVec3( mat, ray.mOrigin );
		//translatedRay.setOrigin( orgi );

		////vgKernel::Vec3 dir = vgKernel::Math::translateVec3( mat , ray.mDirection );
		////translatedRay.setDirection( dir );

		//vgKernel::Vec3 endPoint = vgKernel::Math::translateVec3( mat, ray.getPoint(1));
		//translatedRay.setDirection(
		//	vgKernel::Vec3(endPoint.x - orgi.x, endPoint.y -orgi.y, endPoint.z - orgi.z));


		//------------------------------------------
		// 然后遍历每一个geo, 判断是否相交
		//------------------------------------------
		GeometryPointerVec::iterator iter = _geometries.begin();
		GeometryPointerVec::iterator iter_end = _geometries.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			Geometry* geo = *iter;

			bool testok = geo->testIntersect( transRayline );

			if ( testok == true )
			{
				return geo;
			}
		}

		return NULL;
	}
	//----------------------------------------------------------------
	void Layer::delSelectedGeometry( Geometry* del_geo )
	{
		GeometryPointerVec::iterator iter = _selectedGeometries.begin();

		while ( iter != _selectedGeometries.end() )
		{
			if ( *iter == del_geo )
			{
				iter = _selectedGeometries.erase( iter );
			}
			else
			{
				++iter;
			}
		}

		return;
	}
	//----------------------------------------------------------------
	void Layer::clearSelectedGeometry()
	{
		_selectedGeometries.clear();
	}
	//----------------------------------------------------------------
	void Layer::addSelectedGeometry( Geometry* add_geo )
	{
		GeometryPointerVec::iterator findres = 
			std::find( _selectedGeometries.begin() , _selectedGeometries.end() , add_geo );

		if ( findres == _selectedGeometries.end() )
		{
			_selectedGeometries.push_back( add_geo );
		}
		
		return;
	}
	//----------------------------------------------------------------
	void Layer::setSelectedGeometry( Geometry* selected_geo )
	{
		_selectedGeometries.clear();
		_selectedGeometries.push_back( selected_geo );
	}
	//----------------------------------------------------------------
	vgKernel::Vec3 Layer::transStaticCoordToOpenGLCoord( const vgKernel::Vec3& static_vec )
	{
		vgKernel::Vec3 ret = vgKernel::Math::translateVec3( _matrix, 
			static_vec );

		return ret;
	}
	//----------------------------------------------------------------
	float Layer::getHeightInOpenGL( const vgKernel::Vec3& static_vec )
	{
		float ret = 0.0f;
#if 0
		bool getok =vgTerritory::TerrainManager::getSingleton().getElevationByPosition(
			transStaticCoordToOpenGLCoord( static_vec ),
			ret , true );


		if ( getok == false )
		{
			return 0.0f;
		}
#endif
		//待整理
		assert(0);
		
		return ret;
	}
	//----------------------------------------------------------------
	void Layer::invalidateRendering()
	{
		if ( _displayListID != 0 )
		{
			glDeleteLists( _displayListID , 1 );
			_displayListID = 0;
		}

		GeometryPointerVec::iterator iter = _geometries.begin();
		GeometryPointerVec::iterator iter_end = _geometries.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			(*iter)->invalidateRendering();
		}
	}
	//----------------------------------------------------------------
	bool Layer::attachGeometriesToTerrain()
	{
		//待整理
		assert(0);
		return	false;
#if 0
		bool haveterrain = 
			vgTerritory::TerrainManager::getSingleton().hasTerrainData();

		if ( haveterrain == false )
		{
			return false;
		}

		//------------------------------------------
		// !!!!!!!注意！！这里的设置
		//------------------------------------------
		_transY = 0.0f;

		_staticBox = vgKernel::Box::NULL_BOX;

		GeometryPointerVec::iterator iter = _geometries.begin();
		GeometryPointerVec::iterator iter_end = _geometries.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			Geometry* geo = *iter;
			geo->attachToTerrain();

			_staticBox.merge( geo->getEnvelope3f() );
		}

		invalidateRendering();

		//------------------------------------------
		// 开始更新包围盒
		//------------------------------------------
		_matrix = vgKernel::Mat4::IDENTITY;
		_dynamicBox = _staticBox;

		float tmpx = _transX;
		float tmpy = _transY;
		float tmpz = _transZ;
		_transX = 0.0f;
		_transY = 0.0f;
		_transZ = 0.0f;

		translate( tmpx , tmpy , tmpz );


		return true;
#endif
	}
	//----------------------------------------------------------------
	void Layer::setOGRFeature( OGRFeature* feature )
	{
		VGSH_CHECK_OGR_ERROR();

		OGRErr err =  _ogrLayer->SetFeature( feature );
		assert( err == OGRERR_NONE );
		CPLErrorReset();

		VGSH_CHECK_OGR_ERROR();

		return;
	}
	//----------------------------------------------------------------
	bool Layer::selectByFieldString( const String& fieldname , const String& content )
	{
		clearSelectedGeometry();

		GeometryPointerVec::iterator iter = _geometries.begin();
		GeometryPointerVec::iterator iter_end= _geometries.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			Geometry* geo = *iter;

			OGRFeaturePtr pfeat = geo->getOGRFeaturePtr();

			const char* str = pfeat->GetFieldAsString( fieldname.c_str() );

			if ( str == NULL )
			{
				continue;
			}

			if ( String( str ) == content )
			{
				addSelectedGeometry( geo );
			}
		}

		return true;
	}

	void Layer::setMatrix( const vgKernel::Mat4& matrix )
	{
		_matrix = matrix;
		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

		_transX = 	_matrix._m[12];
		_transY = _matrix._m[13];
		_transZ = _matrix._m[14];
	}

	OGRFeature* Layer::getOGRFeatureByFID( const long& fid )
	{
		assert( _ogrLayer != NULL );
		return _ogrLayer->GetFeature( fid );
	}

	OGRFeatureDefn* Layer::getFeatureDefn()
	{
		return _ogrLayer->GetLayerDefn();
	}
	//----------------------------------------------------------------
	bool Layer::initialise( OGRLayer* ogrlayer )
	{
		OGRFeatureDefn* def = ogrlayer->GetLayerDefn();
		_shapeName = def->GetName();

		_ogrLayer = ogrlayer;
		assert( _ogrLayer != NULL );



		OGREnvelope env;
		OGRErr err = ogrlayer->GetExtent( &env );
		assert( err == OGRERR_NONE );

		return true;
	}
	//----------------------------------------------------------------


}// end of namespace vgShape
