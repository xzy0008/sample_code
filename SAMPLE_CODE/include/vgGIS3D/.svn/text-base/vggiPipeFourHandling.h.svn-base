
/**
@date 	2010/04/04  15	:45
@author  KingHJ

@brief 	 管线四通节点的类

@see    
*/

#pragma  once
#include <vgGis/vggisDefinition.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkMath.h>
#include <vgGIS3D/vggiPipeGeometry.h>


namespace vgGIS3D
{
	class vgFourHandling:public vgPipeGeometry
	{
	public:		
		vgFourHandling(float pipeRadius, vgKernel::Vec3 centerPos)
			:vgPipeGeometry(pipeRadius, centerPos)
		{
			m_centerPoint = centerPos;
			m_pipeRadius = pipeRadius;
			quadyuanzhu =  gluNewQuadric();
			yuanhuan = gluNewQuadric();
			yuanqiu = gluNewQuadric();
			m_FourthCallList = 0;			

			initialColors();
			getBoxPosVec();
		}

		vgFourHandling(float pipeRadius, vgKernel::Vec3 centerPos, vector<vgKernel::Vec3> drectionVec, vector<double> tranAngleVec)
			:vgPipeGeometry(pipeRadius, centerPos, drectionVec, tranAngleVec)
		{
			m_centerPoint = centerPos;
			m_pipeRadius = pipeRadius;
			quadyuanzhu =  gluNewQuadric();
			yuanhuan = gluNewQuadric();
			yuanqiu = gluNewQuadric();
			m_FourthCallList = 0;	
			m_drecVec = drectionVec;
			m_angleVec = tranAngleVec;
			_box3d = Box3d::NULL_BOX;

			initialColors();
			getBoxPosVec();
		}

		~vgFourHandling();

	public:
		PipeGeoType getType() { return PIPEGEO_FOURHANDLING; }

	protected:
		float m_pipeRadius;		
		GLUquadricObj *quadyuanzhu;		
		GLUquadricObj *yuanhuan;
		GLUquadricObj *yuanqiu;
		vgKernel::Vec3 m_centerPoint;
		vector<vgKernel::Vec3> m_drecVec;
		vector<double> m_angleVec;
		vector<vgKernel::Vec3> m_boxPosVec;

	public:
		GLuint m_FourthCallList;

		float colorInfo[3];

		Box3d _box3d;

	public:
		void initialColors();

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

	typedef vgKernel::SharePtr<vgFourHandling> FourHandlingPtr;
	//typedef std::vector <PipeValvesPtr> ValvesPtrVector;
}
