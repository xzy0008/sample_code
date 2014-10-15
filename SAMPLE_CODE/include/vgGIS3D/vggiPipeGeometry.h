
/**
@date 	2010/04/03  10:15	
@author  KingHJ

@brief 	 管线几何体的基类

@see    
*/

#pragma  once
#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkBox.h>
#include <vgGIS3D/vggiBox3d.h>


namespace vgGIS3D
{
	enum PipeGeoType
	{
		PIPEGRO_NON,
		PIPEGEO_VALVES,
		PIPEGEO_TRIPLEHANDLING,
		PIPEGEO_FOURHANDLING
	};

	class VGG_EXPORT vgPipeGeometry
	{
	public:		
		vgPipeGeometry(float pipeRadius, vgKernel::Vec3 centerPos)
		{
			m_centerPoint = centerPos;
			m_pipeRadius = pipeRadius;
		}

		vgPipeGeometry(float pipeRadius, vgKernel::Vec3 centerPos, 
			vector<vgKernel::Vec3> drectionVec, vector<double> tranAngleVec)
		{

		}

		~vgPipeGeometry();

	protected:
		float m_pipeRadius;
		vgKernel::Vec3 m_centerPoint;

	public:
		virtual PipeGeoType getType() { return PIPEGRO_NON; }

	public:

		// 设置整体颜色
		virtual void setSolidColor(bool updateNow = true) = 0;

		//还原到修改前颜色
		virtual void revertSolidColor() = 0;

		virtual void renderUsingDisplayList() = 0;

		virtual void renderOnceForDisplayList() = 0;				

		virtual void invalidateRendering() = 0;

		virtual vgKernel::Vec3 getCenterPos() = 0;

		virtual vgKernel::Box getEnvelope3f() = 0;

		virtual Box3d getEnvelope3d() = 0;

	};

	typedef vgKernel::SharePtr<vgPipeGeometry> PipeGeoPtr;
	typedef std::vector <PipeGeoPtr> PipeGeoPtrVector;
}
