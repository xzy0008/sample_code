



#include <vgStableHeaders.h>
#include <vgTerritory/vgtTerrainCenter.h>
#include <vgTerritory/vgtTerrainManager.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgImage/vgiTextureManager.h>

#include <vgCam/vgcaCamManager.h>

namespace vgTerritory {
	
#if 0

	ElevationItem* MeshTextureCenter::_emptyTexBlock = NULL;

	//----------------------------------------------------------------
	ElevationItem::ElevationItem( 
		float texUScale, float texUBias, float texVScale, 
		float texVBias , String texname , const bool& isempty /*= false */)
	{
		_texObserver = NULL;

		_isEmptyBlock = isempty;

		_texParams[0] = texUScale;
		_texParams[1] = texUBias;

		_texParams[2] = texVScale;
		_texParams[3] = texVBias;

		_pgpuprogram = 	TerrainManager::getSingleton().getGpuProgramPtr();

		assert( _pgpuprogram != NULL );

		//assert(0);

		if ( _isEmptyBlock == false )
		{
			_texObserver = vgImage::TextureManager::getSingleton().getTextureObserver(
				texname , VGLOD_CLEAR - 1 );



			if ( _texObserver != NULL )
			{
				_texObserver->addRef();
			}



			//_texturePtr = vgCore::TextureManager::getSingleton().getTexturePtr( texname ,
			//	true , true , vgCore::TextureBuildOptionPtr::DEFAULT_HUGE_MAP_DXT_OPTION);

			//assert( _texturePtr->isEmptyTexture() == false );

			//_texturePtr->useBind();

			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		}

	}
	//----------------------------------------------------------------
	ElevationItem::~ElevationItem()
	{
		if ( _texObserver != NULL )
		{
			_texObserver->releaseRef();
			_texObserver = NULL;
		}

	}
	//----------------------------------------------------------------
	void ElevationItem::useBindInTerrainGpuProgram()
	{

		if ( _isEmptyBlock == true )
		{
			_pgpuprogram->setDecalUVParamsEveryFrame( 0 , _texParams );

		}
		else
		{
			if ( _texObserver != NULL )
			{
				//_texObserver->useBind();

				//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S ,GL_CLAMP_TO_BORDER);
				//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T ,GL_CLAMP_TO_BORDER);


				//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S ,GL_CLAMP_TO_EDGE);
				//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T ,GL_CLAMP_TO_EDGE);

				_pgpuprogram->setDecalUVParamsEveryFrame(
					_texObserver->getTextureID() , _texParams );
			}

		}
	}
	//----------------------------------------------------------------
	
	//----------------------------------------------------------------
	MeshTextureCenter::MeshTextureCenter(  bool needupdate )
	{

		_isNeedUpdate = needupdate;


		static bool static_init_tag = false;

		if ( static_init_tag == false )
		{
			static_init_tag = true;

			_emptyTexBlock = new ElevationItem( 1.0f , 0.0f , 1.0f , 0.0f , "" , true );

		}


		_absoluteCenterX = 0;
		_absoluteCenterZ = 0;

		//_movingDisplaceCenterX = 0;
		//_movingDisplaceCenterZ = 0;



		_pCurrentPosX = &vgCam::CamManager::getSingleton().getCurrentPositionPtr()->x;
		_pCurrentPosZ = &vgCam::CamManager::getSingleton().getCurrentPositionPtr()->z;

		_pTexBlockLeftUp = NULL;
		_pTexBlockLeftDown = NULL;
		_pTexBlockRightUp = NULL;
		_pTexBlockRightDown = NULL;

		_texBlocks = NULL;

		_whichLayer = -1;
	}
	//----------------------------------------------------------------
	MeshTextureCenter::~MeshTextureCenter()
	{
		destroy();
	}
	//----------------------------------------------------------------
	bool MeshTextureCenter::init( const String& prefix , const float& blockwidth ,
		const int& num_in_width , const float& displace_in_x , 
		const float& displace_in_z , const int& whichlayer )
	{
		assert( prefix.empty() == false );
		assert( blockwidth > 0 );
		assert( num_in_width > 0 );
		assert( _whichLayer == -1 );
		assert( _pTexBlockLeftUp == NULL );
		assert( _pTexBlockLeftDown == NULL );
		assert( _pTexBlockRightUp == NULL );
		assert( _pTexBlockRightDown == NULL );
		assert( num_in_width % 2 == 0 );

		_prefix = prefix;
		_blockWidth = blockwidth;
		_numInWidth = num_in_width;
		_displaceInX = displace_in_x;
		_displaceInZ = displace_in_z;
		_whichLayer = whichlayer;

		_absoluteCenterX = _displaceInX;
		_absoluteCenterZ = _displaceInZ;

		//------------------------------------------
		// 处理名称
		//------------------------------------------
		_texBlocks = new ElevationItem*[ _numInWidth * _numInWidth ];

		for ( int i = 0 ; i < _numInWidth * _numInWidth ; ++ i )
		{
			_texBlocks[i] = NULL;
		}

		const float uvwidth = 1.0f / (float)_numInWidth;
		const float uvscale = 1.0f / uvwidth;

		for ( int i = 0 ; i < _numInWidth * _numInWidth ; ++ i )
		{
			const int x = i % _numInWidth;
			const int z = i / _numInWidth;

			std::ostringstream o;

			o << _prefix << "_level" << _whichLayer << "_" << x << "_" << z << ".dds";

			String ddd = o.str();

			_texBlocks[i] = new ElevationItem(
				uvscale ,  (-1.0f) * uvwidth * x * uvscale , 
				uvscale ,  (-1.0f) * uvwidth * z * uvscale , 
				o.str() );
		}

		_halfNum = _numInWidth / 2;

		update();


		return true;
	}
	//----------------------------------------------------------------
	void MeshTextureCenter::destroy()
	{
		if ( _texBlocks != NULL )
		{
			for ( int i = 0 ; i < _numInWidth * _numInWidth ; ++ i )
			{
				if ( _texBlocks[i] != NULL )
				{
					delete _texBlocks[i];
					_texBlocks[i] = NULL;
				}
			}
			delete[] _texBlocks;
			_texBlocks = NULL;
		}
	}
	//----------------------------------------------------------------
	void MeshTextureCenter::update()
	{

		if ( _isNeedUpdate )
		{
			_transX = floor( *_pCurrentPosX / _blockWidth + 0.5f);
			_transZ = floor( *_pCurrentPosZ / _blockWidth + 0.5f);

			// 注意是负的
			_absoluteCenterX = _blockWidth * _transX * (-1);
			_absoluteCenterZ = _blockWidth * _transZ * (-1);
		}
		else
		{
			_transX = 0;
			_transZ = 0;
			// 先这么写!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			_absoluteCenterX = 0;
			_absoluteCenterZ = 0;
		}

		_pTexBlockLeftUp = getTexBlock( _transX + _halfNum - 1 , _transZ + _halfNum - 1 );

		_pTexBlockLeftDown = getTexBlock( _transX + _halfNum - 1 , _transZ + _halfNum );

		_pTexBlockRightUp = getTexBlock( _transX + _halfNum , _transZ + _halfNum - 1 );

		_pTexBlockRightDown = getTexBlock( _transX + _halfNum , _transZ + _halfNum );
	}
	//----------------------------------------------------------------


#endif

}// end of namespace vgTerritory
