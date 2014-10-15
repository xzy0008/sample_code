
#include <vgStableHeaders.h>

#include "vgtex/tvgBillboardSet.h"


namespace vgCore {

	//----------------------------------------------------------------
	void BillboardSet::drawList() const
	{
		for ( BillboardMap::const_iterator iter = mBillboardMap.begin() ;
			iter != mBillboardMap.end() ;
			++ iter )
		{
			iter->second->draw();
		}
	}
	//----------------------------------------------------------------
	String BillboardSet::getDetails() const
	{
		String result("---- BillboardSet Details begin ---");
		for ( BillboardMap::const_iterator iter = mBillboardMap.begin() ;
			iter != mBillboardMap.end() ;
			++ iter )
		{
			result += iter->second->getDetails();
		}
		result += "---- BillboardSet Details end ---";
		return result;
	}
	//----------------------------------------------------------------
	bool BillboardSet::removeBillboardPtr( const StringPtr& uniname )
	{
		BillboardMap::iterator iter =
			mBillboardMap.find( uniname );
		if ( iter == mBillboardMap.end() )
		{
			return false;
		}
		mBillboardMap.erase( iter );
		return true;
	}
	//----------------------------------------------------------------
	bool BillboardSet::removeBillboardPtr( const String& uniname )
	{
		StringPtr pname( new String(uniname) );

		BillboardMap::iterator iter =
			mBillboardMap.find( pname );
		if ( iter == mBillboardMap.end() )
		{
			return false;
		}
		mBillboardMap.erase( iter );
		return true;
	}
	//----------------------------------------------------------------
	void BillboardSet::addBillboardPtr( const BillboardPtr& pbbd ,
		const bool& replace /*= true */ )
	{
		if ( replace == true )
		{
			mBillboardMap[ pbbd->getUniqueNamePtr() ] = pbbd;
			return;
		}
		else
		{
			StringPtr uname = pbbd->getUniqueNamePtr();
			BillboardMap::iterator iter =
				mBillboardMap.find( uname );
			if ( iter == mBillboardMap.end() )
			{
				mBillboardMap.insert( iter , std::make_pair( uname , pbbd ) );
			}
			return;
		}
	}
	//----------------------------------------------------------------
	void BillboardSet::addBillboardPtr( const String& uniname ,
		const String& texUniName ,  const Vector3& pos /*= Vector3::ZERO */,  
		const bool& replace /*= true */ )
	{
		BillboardPtr pbbd( new Billboard( uniname , texUniName , pos ) );
		this->addBillboardPtr( pbbd , replace );
	}
	//----------------------------------------------------------------
	void BillboardSet::addBillboardPtr( const String& uniname , 
		const TexturePtr& ptex ,  const Vector3& pos /*= Vector3::ZERO */, 
		const bool& replace /*= true */ )
	{
		BillboardPtr pbbd( new Billboard( uniname , ptex , pos ) );
		this->addBillboardPtr( pbbd , replace );
	}
	//----------------------------------------------------------------
	void BillboardSet::setListRenderType( const Billboard::RenderTypes& type )
	{
		for ( BillboardMap::const_iterator iter = mBillboardMap.begin() ;
			iter != mBillboardMap.end() ;
			++ iter )
		{
			iter->second->setRenderType( type );
		}
	}
	//----------------------------------------------------------------
	BillboardPtr BillboardSet::getBillboardPtr( const StringPtr& pUniName )
	{
		BillboardMap::iterator iter =
			mBillboardMap.find( pUniName );

		if ( iter == mBillboardMap.end() )
		{
			/// return raw null pointer
			return BillboardPtr();
		}
		return iter->second;
	}
	//----------------------------------------------------------------


	//----------------------------------------------------------------
	std::istream& operator >> ( std::istream& in , BillboardSet& bbdset )
	{
		int num = 0;
		char buf[255];

		in >> num ;
		in.getline( buf , 255 , '\n' );

		for ( int i = 0 ; i < num ; ++ i )
		{
			BillboardPtr bbd( new Billboard );

			// try catch!!!!!

			in >> (*bbd);

			bbdset.addBillboardPtr( bbd );
		}

		return in;
	}

	std::ostream& operator << ( std::ostream& out , BillboardSet& bbdset )
	{
		out << bbdset.mBillboardMap.size() << '\n';

		BillboardSet::BillboardMap::iterator iter_end = bbdset.mBillboardMap.end();

		for ( BillboardSet::BillboardMap::iterator iter = bbdset.mBillboardMap.begin() ;
			iter != iter_end;
			++ iter )
		{
			out << (*iter->second);
		}

		return out;	
	}

}// end of namespace vgCore
