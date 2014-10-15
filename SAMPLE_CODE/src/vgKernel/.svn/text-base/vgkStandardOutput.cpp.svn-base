



#include <vgStableHeaders.h>
#include <vgKernel/vgkStandardOutput.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkTrace.h>

namespace vgKernel {
	
	
	StandardOutputFunc StandardOutput::_stdout = 
		StandardOutput::DefaultOutput;
	
	
	//----------------------------------------------------------------
	void StandardOutput::dumpToOutput( const String& str )
	{
		if ( _stdout != NULL )
		{
			(*_stdout)( str.c_str());
		}
	}
	//----------------------------------------------------------------
	vgKernel::StandardOutputFunc StandardOutput::getOutputFunc()
	{
		return _stdout;
	}
	//----------------------------------------------------------------
	void StandardOutput::redirectOutput( StandardOutputFunc func )
	{
		_stdout = func;
	}
	//----------------------------------------------------------------
	void StandardOutput::DefaultOutput( const char* str )
	{
		vgKernel::Trace::createShow( str );
	}
	//----------------------------------------------------------------
	void StandardOutput::restoreToDefaultOutput()
	{
		_stdout = DefaultOutput;
	}

	void StandardOutput::dumpToOutputW( const std::wstring& wstr )
	{
		std::string str = vgKernel::StringUtility::convertWStringToString( wstr );

		dumpToOutput( str );
	}
	//----------------------------------------------------------------


}// end of namespace vgKernel
