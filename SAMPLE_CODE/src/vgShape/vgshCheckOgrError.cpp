


#include <vgStableHeaders.h>
#include <vgShape/vgshCheckOgrError.h>
#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>
#include <vgKernel/vgkException.h>


namespace vgShape {
	
	

	void CheckOgrError( const String& source , const String& file , const long& line )
	{
		String msg = CPLGetLastErrorMsg();

		if ( msg.empty() )
		{
			return;
		}
		else
		{
			std::ostringstream desc;

			desc <<  "- Ogr Error: " <<  msg
				<< "\n in " << source;

			if( line > 0 )
			{
				desc << " at " << file << " (line " << line << ")\n\n\n";
			}

			VGK_EXCEPT( vgKernel::Exception::ERR_RENDERINGAPI_ERROR,
				desc.str(),
				"CheckOgrError()");

			return;
		}
	}

	
}// end of namespace vgShape
