


#include <vgStableHeaders.h>
#include <vgMesh/vgmMesh.h>
#include <vgMesh/vgmMeshData.h>
#include <vgMesh/vgmMeshDataPlus.h>
#include <vgMesh/vgmIoRequestMeshData.h>
#include <vgMesh/vgmMeshItem.h>



namespace vgMesh {
	
	
	//----------------------------------------------------------------
	Mesh::Mesh( MeshItem* item , 
		VgmBrief* vgmbrief , vgAsyn::FileHandle* filehandle , int lod )
	{
		setDefault();

		assert( item != NULL );
		_fatherItem = item;
		_lod = lod;

		assert( vgmbrief != NULL );
		assert( filehandle != NULL );
		assert( lod >= VGLOD_COARSE );
		assert( lod <= VGLOD_CLEAR );

		_meshDataFileInfo = new vgAsyn::FileInfo( 
			_fatherItem->getName() , filehandle , 
			vgmbrief->_positionOfMeshData[ lod ] , 
			vgmbrief->_lengthOfMeshData[ lod ] );

		_meshDataPlusFileInfo = new vgAsyn::FileInfo( 
			_fatherItem->getName() , filehandle , 
			vgmbrief->_positionOfMeshDataPlus[ lod ] , 
			vgmbrief->_lengthOfMeshPlus[ lod ] );

	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	void Mesh::setDefault()
	{
		_shadowEnabled = false;

		_referenceCount = 0;
		_lod = 0;

		_meshData = NULL;
		_meshDataFileInfo= NULL;

		_meshDataPlus= NULL;
		_meshDataPlusFileInfo= NULL;
		_fatherItem = NULL;
	}
	//----------------------------------------------------------------
	void Mesh::destroy()
	{
		_referenceCount = 0;
		_lod = 0;

		if ( _meshData != NULL )
		{
			delete _meshData;
			_meshData = NULL ;
		}

		if ( _meshDataFileInfo != NULL )
		{
			delete _meshDataFileInfo;
			_meshDataFileInfo = NULL;
		}

		if ( _meshDataPlus != NULL )
		{
			delete _meshDataPlus;
			_meshDataPlus = NULL;
		}

		if ( _meshDataPlusFileInfo != NULL )
		{
			delete _meshDataPlusFileInfo;
			_meshDataPlusFileInfo =NULL;
		}
		setDefault();
	}
	//----------------------------------------------------------------
	void Mesh::addRef( bool force_to_load  )
	{
		++_referenceCount;

		if ( _referenceCount == 1 )
		{	
			// 这个时候需要载入

			assert( _meshData == NULL );
			assert( _fatherItem != NULL );

			vgAsyn::IoRequest* request = NULL;
			assert( _meshDataFileInfo != NULL );
			vgAsyn::FileInfo* fileinfo = _meshDataFileInfo->clone();

			request = 	new IoRequestMeshData( _fatherItem->getUniqueID() ,
				_lod , fileinfo , _shadowEnabled );

			if ( force_to_load )
			{
				request->setAsynchronousMode( false );
			}

			// 设定优先级
			if ( _lod == VGLOD_CLEAR )
			{
				request->setPriority( true );
			}

			request->sendRequestAndDoAsynHandlerFunc( true );
		}

	}
	//----------------------------------------------------------------
	void Mesh::releaseRef()
	{
		//assert( _referenceCount > 0 );

		if ( _referenceCount <= 0 )
		{
			assert(0);
			return;
		}

		if ( _referenceCount == 0 )
		{
			return;
		}

		--_referenceCount;

		if ( _referenceCount == 0 )
		{
			// 这个时候需要载出
			if ( _meshData != NULL )
			{
				delete _meshData;
				_meshData = NULL;
			}

			if ( _meshDataPlus != NULL )
			{
				delete _meshDataPlus;
				_meshDataPlus = NULL;
			}
		}
	}
	//----------------------------------------------------------------
	void Mesh::render( int tex_lod , bool trans_mode,
		RgbaQuad* colorval )
	{
		if ( _meshData != NULL )
		{
			_meshData->render( tex_lod, _shadowEnabled ? 1 : 0 ,
				trans_mode , colorval );
		}
	}
	//----------------------------------------------------------------




}// end of namespace vgMesh
