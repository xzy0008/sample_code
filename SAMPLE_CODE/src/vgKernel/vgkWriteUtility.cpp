


#include <vgStableHeaders.h>
#include <vgKernel/vgkWriteUtility.h>


namespace vgKernel {
	
	
	
	
	//----------------------------------------------------------------
	bool WriteUtility::writeStringToCFile( CFile* cfile , const String& str , 
		const int& write_length , const bool& alert /*= false*/ )
	{
		assert( cfile != NULL );

		if ( str.size() >= write_length )
		{
			assert( 0 );
			return false;
		}

		char* buffer= new char[ write_length ];
		memset( buffer , 0 , write_length );

		strcpy( buffer  ,str.c_str() );

		try
		{
			cfile->Write( buffer , write_length );
		}
		catch (...)
		{
			delete[] buffer;
			if ( alert )
			{
				std::ostringstream o ;
				o << "Ð´Èë×Ö·û´®Ê§°Ü, ×Ö·û´®:" << str << " ,ÓûÐ´Èë³¤¶È: " << write_length
					<< " , CFile Address:" << cfile; 

				MessageBox( NULL , o.str().c_str() , "Write Error" , 
					MB_OK );
			}

			return false;
		}
		

		delete[] buffer;

		return true;
	}
	//----------------------------------------------------------------
	bool WriteUtility::writeStringToStream( vgKernel::StreamWriterPtr pwriter , 
		const String& str, int write_length )
	{
		assert( pwriter.isNull() == false  );

		if ( str.size() >= write_length )
		{
			assert( 0 && "str.size() >= write_length" );
			return false;
		}

		char* buffer= new char[ write_length ];
		memset( buffer , 0 , write_length );

		strcpy( buffer, str.c_str() );

		int writenum;
		try
		{
			writenum = pwriter->write( buffer , write_length );
		}
		catch (...)
		{
			delete[] buffer;
			return false;
		}

		delete[] buffer;

		if ( writenum == write_length )
		{
			return true;
		}

		assert(0);
		return false;
	}
	//----------------------------------------------------------------



}// end of namespace vgKernel
