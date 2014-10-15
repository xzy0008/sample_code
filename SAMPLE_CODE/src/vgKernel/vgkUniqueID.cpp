

#include <vgStableHeaders.h>
#include <vgKernel/vgkUniqueID.h>
#include <rpcdce.h> 

namespace vgKernel {
	

	//----------------------------------------------------------------
	UniqueID::UniqueID( UuidStruct* uuid )
	{
		assert( uuid != NULL );
		memcpy( &_id1 , uuid , sizeof( unsigned long ) * 2 );
	}
	//----------------------------------------------------------------
	UniqueID::UniqueID( const UniqueID& unique_id )
	{
		assert( unique_id.isValid() );
		_id1 = unique_id._id1;
		_id2 = unique_id._id2;
	}
	//----------------------------------------------------------------
	String UniqueID::getString()
	{
		assert( isValid() );
		// enough buffer size;
		char buf[24];
		memset( buf , 0 , 24 );

		int ret = sprintf_s( buf , 24 , "%08x%08x", _id1 , _id2 );
		assert( ret == 16 );

		return buf;
	}
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	UniqueID* UniqueIDFactory::getUniqueIDPtr()
	{
		UUID   _tmp_uuid;   

		RPC_STATUS result = UuidCreate(&_tmp_uuid);   

		if( RPC_S_OK ==  result )   
		{   
			UniqueID *ret = new UniqueID( (UuidStruct*)&_tmp_uuid );
			return ret;
		}

		assert(0);
		return NULL;
	}
	//----------------------------------------------------------------
	UniqueID UniqueIDFactory::getUniqueID()
	{
		UUID   _tmp_uuid;   

		RPC_STATUS  result = UuidCreate(&_tmp_uuid);   

		assert( RPC_S_OK ==  result );

		return UniqueID( (UuidStruct*)&_tmp_uuid );
	}
	//----------------------------------------------------------------



	
}// end of namespace vgKernel
