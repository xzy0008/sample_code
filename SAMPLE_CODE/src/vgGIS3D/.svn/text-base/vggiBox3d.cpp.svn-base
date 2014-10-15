



#include <vgStableHeaders.h>
#include <vgGis3d/vggiBox3d.h>


namespace vgGIS3D {
	
	const Box3d Box3d::NULL_BOX( 
		-std::numeric_limits<double>::infinity(), 
		-std::numeric_limits<double>::infinity(), 
		-std::numeric_limits<double>::infinity(), 
		std::numeric_limits<double>::infinity(), 
		std::numeric_limits<double>::infinity(), 
		std::numeric_limits<double>::infinity() );


	//----------------------------------------------------------------
	String Box3d::getDetails()
	{
		std::ostringstream o;
		o << "Box3d: {" 
			<< "minVertex: " << _minVertex.getDetails() 
			<< " , maxVertex: " << _maxVertex.getDetails() << " }";

		return o.str();
	}

	void Box3d::matrixTranslation( const vgKernel::Mat4& mat )
	{
		double x, y, z;
		Vec3d pointBuffer[8];

		for (int i=0; i<8; i++)
		{
			pointBuffer[i] = getCorner(i);
		}

		for (int i=0; i<8; i++)
		{
			x = mat._m[0] * pointBuffer[i].x + mat._m[4] * pointBuffer[i].y + mat._m[8] * pointBuffer[i].z + mat._m[12];
			y = mat._m[1] * pointBuffer[i].x + mat._m[5] * pointBuffer[i].y + mat._m[9] * pointBuffer[i].z + mat._m[13];
			z = mat._m[2] * pointBuffer[i].x + mat._m[6] * pointBuffer[i].y + mat._m[10] * pointBuffer[i].z + mat._m[14];

			pointBuffer[i].x = x;
			pointBuffer[i].y = y;
			pointBuffer[i].z = z;
		}

		_minVertex = pointBuffer[0];
		_maxVertex = pointBuffer[0];
		_minVertex.z = z;

		for (int i=0; i<8; i++)
		{
			if (_minVertex.x > pointBuffer[i].x)
			{
				_minVertex.x = pointBuffer[i].x;
			}
			if (_minVertex.y > pointBuffer[i].y)
			{
				_minVertex.y = pointBuffer[i].y;
			}
			if (_minVertex.z > pointBuffer[i].z)
			{
				_minVertex.z = pointBuffer[i].z;
			}

			if (_maxVertex.x < pointBuffer[i].x)
			{
				_maxVertex.x = pointBuffer[i].x;
			}
			if (_maxVertex.y < pointBuffer[i].y)
			{
				_maxVertex.y = pointBuffer[i].y;
			}
			if (_maxVertex.z < pointBuffer[i].z)
			{
				_maxVertex.z = pointBuffer[i].z;
			}
		}
	}
	//----------------------------------------------------------------

	
	
}// end of namespace vgShape
