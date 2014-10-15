
/**
@date 	2010/03/30  10:15	
@author  KingHJ

@brief 	 管线阀门的类

@see    
*/

#pragma  once
#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkMath.h>
#include <vgGIS3D/vggiPipeGeometry.h>


namespace vgGIS3D
{
	class vgPipeValves:public vgPipeGeometry
	{
	public:		
		vgPipeValves(float pipeRadius, vgKernel::Vec3 centerPos)
			:vgPipeGeometry(pipeRadius, centerPos)
		{
			m_centerPoint = centerPos;
			m_pipeRadius = pipeRadius;
			quadyuanzhu =  gluNewQuadric();
			yuanhuan = gluNewQuadric();
			m_valvesCallList = 0;
			_box3d = Box3d::NULL_BOX;

			initialColors();
			getBoxPosVec();
		}

		~vgPipeValves();

	public:
		PipeGeoType getType() { return PIPEGEO_VALVES; }

	protected:
		float m_pipeRadius;		
		GLUquadricObj *quadyuanzhu;		
		GLUquadricObj *yuanhuan;
		vgKernel::Vec3 m_centerPoint;
		vector<vgKernel::Vec3> m_boxPosVec;

	public:
		GLuint m_valvesCallList;
		float colorInfo[2][3];

		Box3d _box3d;

	public:
		void initialColors()
		{
			colorInfo[0][0] = 0.5f;
			colorInfo[0][1] = 0.0f;
			colorInfo[0][2] = 1.0f;

			colorInfo[1][0] = 1.0f;
			colorInfo[1][1] = 0.0f;
			colorInfo[1][2] = 0.0f;
		}
		// 设置整体颜色
		void setSolidColor(bool updateNow = true);

		//还原到修改前颜色
		void revertSolidColor();

		void renderUsingDisplayList();

		void renderOnceForDisplayList();				

		void invalidateRendering();

		void getBoxPosVec();

		void mergeBox();

		virtual vgKernel::Box getEnvelope3f()
		{
			mergeBox();
			return _box3d.getBoxFloat(); 
		}

		virtual Box3d getEnvelope3d() 
		{
			mergeBox();
			return _box3d;
		}

		vgKernel::Vec3 getCenterPos()
		{
			return m_centerPoint;
		}
	};

	typedef vgKernel::SharePtr<vgPipeValves> PipeValvesPtr;
	//typedef std::vector <PipeValvesPtr> ValvesPtrVector;
}
