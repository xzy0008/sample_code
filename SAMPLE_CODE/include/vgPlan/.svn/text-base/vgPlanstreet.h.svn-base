

#ifndef __VGPLANSTREET__
#define __VGPLANSTREET__

#include <gdal/ogrsf_frmts.h>
#include <gdal/ogr_api.h>

#include <vgkernel/vgkInputSystem.h>
/*#include <vgAutoplan/vgPlanpolygon.h>*/

#include <vgplan/vgPlanstreetLine.h>

namespace vgPlan
{
	class vgPlanstreetLine;

	class vgPlanstreet : public vgKernel::InputHandler
	{
	public:
		vgPlanstreet(){};

		~vgPlanstreet()    
		{
 
 			for ( int i  =0;  i < streetpolys.size(); i++ )
 			{
 				delete streetpolys[i];
 				streetpolys[i] = NULL;
 			}
 
 			streetpolys.clear();
		}

		virtual void setdefault();


		void render();

	public:

		void addstreetLine( vgPlanstreetLine *pp );

		vector<vgPlanstreetLine *>* getstreetpolys(){ return &streetpolys; }

		OGRGeometry* getgeometry(){ return geo; }

		void setgeometry( OGRGeometry *pp){ geo = pp; }

		void genuniongeometry();
		
		void setName(string name)
		{
			m_streetName = name;
		}

		string getName()
		{
			return m_streetName;
		}

	private:
		vector<vgPlanstreetLine *> streetpolys;

		bool b_genover;

		OGRGeometry *geo;

		string m_streetName;

	};


}

#endif