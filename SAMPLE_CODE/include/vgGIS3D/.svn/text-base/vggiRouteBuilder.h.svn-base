#include <gdal/ogr_feature.h>
#include <vgKernel/vgkVec3.h>
#include <vgGis3d/vggiPrerequisite.h>

namespace vgGIS3D
{
	class RouteBuilder
	{
	public:
		~RouteBuilder()
		{
			reset();
		}

		void render();

		void clear();

		void startRouteEdit();
		
		void endRouteEdit();

		bool addRoute( const vector<vgKernel::Vec3>& pointVec );

		bool saveToFile( string path, string layername );

		void reset();

	private:
		
		vector<RingStruct> m_rings;

	};
}