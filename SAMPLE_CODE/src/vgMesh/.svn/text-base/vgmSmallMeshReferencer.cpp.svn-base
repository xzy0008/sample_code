


#include <vgStableHeaders.h>
#include <vgMesh/vgmMesh.h>
#include <vgMesh/vgmSmallMeshReferencer.h>
#include <vgMesh/vgmMeshItem.h>


namespace vgMesh {
	
	



	//----------------------------------------------------------------
	SmallMeshReferencer::SmallMeshReferencer()
	{
		_filterEnable = true;
		_loadFileSizeThreshold = VGM_SMALLMESH_DEFAULT_THRESHOLD;
	}
	//----------------------------------------------------------------
	SmallMeshReferencer::~SmallMeshReferencer()
	{

	}
	//----------------------------------------------------------------
	bool SmallMeshReferencer::filterSmallMeshes( MeshItem* itm )
	{
		if ( _filterEnable == false )
		{
			return false;
		}

		assert( itm != NULL );
		if ( itm == NULL )
		{
			return false;
		}

		Mesh* clearmesh = itm->getMeshByLod( VGLOD_CLEAR );

		if ( clearmesh->getMeshDataFileInfoRef()->_fileSize <= _loadFileSizeThreshold )
		{
			if ( checkExist( clearmesh ) )
			{
				//如果存在了，直接返回
				return true;
			}

			clearmesh->addRef( true );
			//clearmesh->getFatherMeshItem()->setLodMeshFlag( false );

			_smallMeshes.push_back( clearmesh );
		}

		return true;
	}
	//----------------------------------------------------------------
	bool SmallMeshReferencer::checkExist( Mesh* itm )
	{
		assert( itm != NULL );

		MeshPtrVector::iterator result;

		result = std::find( _smallMeshes.begin(),  _smallMeshes.end() , itm );

		if ( result == _smallMeshes.end() )
		{
			// nothing find
			return false;
		}

		return true;
	}
	//----------------------------------------------------------------
	void SmallMeshReferencer::unRefAllSmallMeshes()
	{
		MeshPtrVector::iterator iter  = _smallMeshes.begin();
		MeshPtrVector::iterator iter_end = _smallMeshes.end();

		for (  ; iter != iter_end ; ++ iter )
		{
			Mesh* itm = *iter;

			itm->releaseRef();
		}

		_smallMeshes.clear();
	}
	//----------------------------------------------------------------
	void SmallMeshReferencer::unRefBecauseOfImage()
	{
		MeshPtrVector::iterator iter = _smallMeshes.begin();
		MeshPtrVector::iterator iter_end = _smallMeshes.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			Mesh* me = *iter;
			me->releaseRef();
		}
	}
	//----------------------------------------------------------------
	void SmallMeshReferencer::addRefBecauseOfImage()
	{
		MeshPtrVector::iterator iter = _smallMeshes.begin();
		MeshPtrVector::iterator iter_end = _smallMeshes.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			Mesh* me = *iter;
			me->addRef( true );
		}
	}
	//----------------------------------------------------------------
	void SmallMeshReferencer::setFilterEnable( const bool& val )
	{
		_filterEnable = val;

		if ( _filterEnable == false )
		{
			unRefAllSmallMeshes();
		}
	}
	//----------------------------------------------------------------
	void SmallMeshReferencer::deleteSmallMesh( MeshItem* itm )
	{
		MeshPtrVector::iterator iter = _smallMeshes.begin();

		while ( iter != _smallMeshes.end() )
		{
			Mesh* meh = *iter;

			if ( meh == itm->getMeshByLod( VGLOD_CLEAR ) ||
				meh == itm->getMeshByLod( VGLOD_COARSE ) ||
				meh == itm->getMeshByLod( VGLOD_COARSE + 1)
				)
			{
				meh->releaseRef();
				iter = _smallMeshes.erase( iter );
			}
			else
			{
				++iter;
			}
		}
	}
	//----------------------------------------------------------------


	
}// end of namespace vgMesh
