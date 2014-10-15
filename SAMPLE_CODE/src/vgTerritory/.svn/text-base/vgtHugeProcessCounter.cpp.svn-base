


#include <vgStableHeaders.h>
#include <vgTerritory/vgtHugeProcessCounter.h>
#include <vgThreads/ScopedLock.h>


namespace vgTerritory {
	

	//----------------------------------------------------------------
	HugeProcess::Counter::Counter( long aimCount )
	{
		_count = 0;
		_aimCount = aimCount;
	}
	//----------------------------------------------------------------
	HugeProcess::Counter::~Counter()
	{

	}
	//----------------------------------------------------------------
	void HugeProcess::Counter::addCount()
	{
		ScopedLock lock( _sect );
		assert( _count <= _aimCount );

		++_count;

		assert( _count > 0 );
	}
	//----------------------------------------------------------------
	bool HugeProcess::Counter::checkCount()
	{
		ScopedLock lock( _sect );
		assert( _count >= 0 );
		assert( _count <= _aimCount );

		if ( _count == _aimCount )
		{
			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	long HugeProcess::Counter::getCount()
	{
		ScopedLock lock( _sect );
		assert( _count >= 0 );
		assert( _count <= _aimCount );

		return _count;
	}
	//----------------------------------------------------------------

	
	
}// end of namespace vgTerritory
