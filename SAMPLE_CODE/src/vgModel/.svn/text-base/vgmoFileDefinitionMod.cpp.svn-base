


#include <vgStableHeaders.h>
#include <vgModel/vgmoFileDefinitionMod.h>


namespace vgModel {
	
	
	
	

	ModIndex::ModIndex( int numofobjs )
	{
		assert( numofobjs != 0 );
		_numberOfObjects = numofobjs;
		_objectsPos = new long[_numberOfObjects];
		_bakedFlag = new bool[_numberOfObjects];
		_keyframeFlag = new bool[ _numberOfObjects ];
		memset( _objectsPos , 0 , _numberOfObjects * sizeof( long ) );
		memset( _bakedFlag , 0 , _numberOfObjects * sizeof( bool ) );
		memset( _keyframeFlag , 0 , _numberOfObjects * sizeof( bool ) );
	}

	ModIndex::~ModIndex()
	{
		if ( _objectsPos != NULL )
		{
			delete _objectsPos;
			_objectsPos = NULL;
		}

		if ( _bakedFlag != NULL )
		{
			delete _bakedFlag;
			_bakedFlag = NULL;
		}
	}
}// end of namespace vgModel
