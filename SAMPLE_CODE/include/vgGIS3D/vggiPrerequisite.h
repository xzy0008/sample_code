#pragma once



#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkSharePtr.h>
#include <vgGis3d/vggiBox3d.h>
#include <vgGis3d/vggiRay3d.h>
#include <vgGis3d/vggiRayLine3d.h>
#include <vgGis3d/vggiDrawingDescriptor.h>

#include <vgGis3d/vggiCheckOgrError.h>



namespace vgGIS3D {

	struct RingStruct
	{		
		bool   operator==(   const   RingStruct&   other   )   
		{   
			if   (   _numPoints   ==   other._numPoints   &&   
				       _pointsBeginAddr   ==   other._pointsBeginAddr   )   
			{   
				return   true;   
			}   
			else   
			{   
				return   false;   
			}   
		} 

		RingStruct( int points = 0, double* addr = NULL)
		{
			_numPoints = points;
			_pointsBeginAddr = addr;
		}
		int _numPoints;
		double* _pointsBeginAddr; //x y z
		int _beginPointID;
		int _endPointID;
	};

	struct PointStruct
	{
		bool   operator==(   const   PointStruct&   other   )   
		{   
			if   (  pos   ==   other.pos  )   
			{   
				return   true;   
			}   
			else   
			{   
				return   false;   
			}   
		}

		PointStruct(int  id = 0, double press = 0.0)
		{
			ID = id;
			pressValue = press;
		}
		int ID;
		vgKernel::Vec3 pos;
		double  pressValue;

		//std::map <string, _variant_t>
	};

	typedef struct PipeLineLayer_t
	{
		std::vector <RingStruct>  pipeLineVec;
		int count ;
	}PipeLineLayer;


	typedef vgKernel::SharePtr<OGRFeature> OGRFeaturePtr;

	const int RENDERER_TYPE_GIS_LAYER	= 16152;

	const int RENDERER_TYPE_PIPELINE_LAYER	= 16153;




	//enum QueryType
	enum	QueryType
	{
		QUERY_NONE,
		GREEN_RATIO,
		PLOT_RATIO,
		TYPE_COUNT
	};

#define VG_GIS_STR				"Gis"

#define VG_GIS_FLOORPROP		"Floor_Prop"

#define VG_GIS_FOOLHEIGHTROP	"Floor_height"

#define VG_GIS_SHPPATH_STR		"Path"

#define VG_GIS_SHPMAT_STR		"Matrix"

#define VG_GIS_STYLE_FIELD		"vg_style"

#define VG_GIS_DEPTH			"Depth"

#define  VG_GIS_VISIBLE     "Visible"   //add by KingHJ @2010-05-11 shapeäÖÈ¾×´Ì¬±£´æ
}// end of namespace  
 