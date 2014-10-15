#pragma once


#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>

	
namespace vgGIS3D {
 
	void CheckOgrError( const String& source , const String& file , const long& line );
 
	
}// end of namespace vgShape
	

//#if _DEBUG
#define VGGI_CHECK_OGR_ERROR() vgGIS3D::CheckOgrError( \
	"", __FILE__, __LINE__ );
//#else
//#define VGSH_CHECK_OGR_ERROR() 
//#endif

 