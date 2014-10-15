


#include <vgStableHeaders.h>
#include <vgKernel/vgkException.h>
#include <vgKernel/vgkLogManager.h>


namespace vgKernel {
	
	Exception::Exception(int num, const String& desc, const String& src) :
		line( 0 ),
		number( num ),
		description( desc ),
		source( src )
    {
        // Log this error - not any more, allow catchers to do it
        //LogManager::getSingleton().logMessage(this->getFullDescription());
    }

    Exception::Exception(int num, const String& desc, const String& src, 
		const char* typ, const char* fil, long lin) :
        line( lin ),
        number( num ),
		typeName(typ),
        description( desc ),
        source( src ),
        file( fil )
    {
        // Log this error, mask it from debug though since it may be caught and ignored
        if(LogManager::getSingletonPtr())
		{
            LogManager::getSingleton().logMessage(
				this->getFullDescription(), 
                LML_CRITICAL, true);
		}

    }

    Exception::Exception(const Exception& rhs)
        : line( rhs.line ), number( rhs.number ), description( rhs.description ), source( rhs.source ), file( rhs.file )
    {
    }

    void Exception::operator = ( const Exception& rhs )
    {
        description = rhs.description;
        number = rhs.number;
        source = rhs.source;
        file = rhs.file;
        line = rhs.line;
		typeName = rhs.typeName;
    }

    const String& Exception::getFullDescription(void) const
    {
		if (fullDesc.empty())
		{

			std::ostringstream desc;

#if _DEBUG
			desc <<  "VGES EXCEPTION(" << number << ":" << typeName << "): "
				<< description 
				<< " in " << source;

			if( line > 0 )
			{
				desc << " at " << file << " (line " << line << ")";
			}
#else
			desc << description ;
#endif

			fullDesc = desc.str();
		}

		return fullDesc;
    }

    int Exception::getNumber(void) const throw()
    {
        return number;
    }
	
	
}// end of namespace vgKernel
