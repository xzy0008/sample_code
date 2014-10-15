



#include <vgStableHeaders.h>
#include <vgTerritory/vgTerrainLevelling.h>
#include <vgKernel/vgkPointInPolygon.h>
#include <vgTerritory/vgVgtrWriter.h>

#include <vgKernel/vgkOpenGLSupport.h>


namespace vgTerritory {
	
	
	
	
	//----------------------------------------------------------------
	bool TerrainLevelling::doLevelling( const VgtrFilePtr vgtrfile ,
		const GLuint& heightmapid ,
		vgKernel::Vec3* vec3list,const int& vec3listnum ,  const float& lastheight )
	{

		assert(0);

		return true;

#if 0
		const int xnum = vgtrfile->_headerPtr->xNum;
		const int znum = vgtrfile->_headerPtr->zNum;
		const float scaley = vgtrfile->_headerPtr->displaceScaleY;
		const float cellsize = vgtrfile->_headerPtr->cellsize;

		//------------------------------------------
		// 首先复制vector2列表
		//------------------------------------------
		vgKernel::Vec2* vec2list = new vgKernel::Vec2[ vec3listnum ];

		for ( int i = 0 ; i < vec3listnum ; ++ i )
		{
			vec2list[i].x = vec3list[i].x / cellsize + xnum / 2;
			vec2list[i].y = vec3list[i].z / cellsize + znum / 2;
		}

		//------------------------------------------
		// 处理高度
		//------------------------------------------
		float last_height_saturate = lastheight / scaley;


		if( last_height_saturate <= 1.0f && last_height_saturate >= 0.0f )
		{
			//------------------------------------------
			// 开始核心运算
			//------------------------------------------
			vgKernel::PointInPolygon pointinpolygon( vec3listnum , vec2list );

			float* data = vgtrfile->_data;

			vgKernel::Vec2 tmp;

			for ( int i = 0 ; i < xnum * znum ; ++ i )
			{
				tmp.x = i % xnum;
				tmp.y = i / xnum;

				if ( pointinpolygon.contains( tmp ) )
				{
					data[i] = last_height_saturate;
				}
			}
		}
		else
		{
			assert(0);
			delete[] vec2list;
			return false;
		}

		//------------------------------------------
		// 删除中间temp变量
		//------------------------------------------
		delete[] vec2list;


		return dumpDataToTexture( vgtrfile , heightmapid );

#endif
	}
	//----------------------------------------------------------------
	bool TerrainLevelling::dumpDataToTexture( const VgtrFilePtr vgtrfile , 
		const GLuint& heightmapid )
	{

		assert(0);

		return true;

#if 0
		assert( vgtrfile.isNull() == false );
		assert( vgtrfile->_headerPtr.isNull() == false );
		assert( vgtrfile->_data != NULL );


		glBindTexture( GL_TEXTURE_2D , heightmapid );

		glTexSubImage2D( GL_TEXTURE_2D , 0 , 0 , 0 ,
			vgtrfile->_headerPtr->xNum , vgtrfile->_headerPtr->zNum , GL_LUMINANCE , 
			GL_FLOAT , vgtrfile->_data );


		VGK_CHECK_OPENGL_ERROR();

		return true;
#endif
	}
	//----------------------------------------------------------------
	bool TerrainLevelling::saveVgtrFile( const String& outputfilename , 
		const VgtrFilePtr vgtrfile , const GLuint& heightmapid )
	{
		bool ret = dumpDataToTexture( vgtrfile , heightmapid );

		if ( ret == false )
		{
			return false;
		}

		return VgtrWriter::writeVgtrToFile( vgtrfile , outputfilename );

	}
	//----------------------------------------------------------------
	bool TerrainLevelling::dumpTextureToData( const GLuint& heightmapid , 
		const VgtrFilePtr vgtrfile )
	{
		assert( vgtrfile.isNull() == false );

		glBindTexture( GL_TEXTURE_2D , heightmapid );

		//------------------------------------------
		// 首先检查tex是否和vgtr对应
		//------------------------------------------
		GLint texwidth = 0;
		GLint texheight = 0;

		glGetTexLevelParameteriv( GL_TEXTURE_2D , 0 , GL_TEXTURE_WIDTH , &texwidth );
		glGetTexLevelParameteriv( GL_TEXTURE_2D , 0 , GL_TEXTURE_HEIGHT , &texheight );

		if ( texwidth != vgtrfile->_headerPtr->xNum ||
			 texheight != vgtrfile->_headerPtr->zNum )
		{
			return false;
		}

		glGetTexImage( GL_TEXTURE_2D , 0 , GL_LUMINANCE , GL_FLOAT , 
			vgtrfile->_dataLod[VGLOD_CLEAR] );

		VGK_CHECK_OPENGL_ERROR();

		return true;
	}
}// end of namespace vgTerritory
