

#include <vgStableHeaders.h>
#include <vgMod/vgNode.h>
//#include <vgMod/vgQuadtreeSceneManager.h>

namespace vgMod
{
	void NodeAbstract::Render()
	{	
		/*if (m_isInMemory)
		{
			QuadtreeSceneManager &mgr = QuadtreeSceneManager::getSingleton();

			if (mgr.GetNodeForRender(m_id))
			{
				mgr.GetNodeForRender(m_id)->Render();
			}			
		}
		else
			return;*/
	}

	
	void NodeAbstract::deleteData()
	{
//		if (m_isInMemory)	
//		{
//			m_isInMemory = false;
//
//			QuadtreeSceneManager &mgr = QuadtreeSceneManager::getSingleton();
//
////			mgr.UnloadNode(m_id);	
//		}
//		else
//			return;
	}
	
	//////////////////////////////////////////////////////////////////////////
	
	Node::Node()
	{
		setDefault();

	}

	Node::Node( CategoryType category )
	 :m_category(category)	
	{
		setDefault();
	}

	void	Node::UpdatePos()
	{
		m_Position	= m_BoundryBox.getCenter();
		/*m_Position.x = (m_BoundryBox.maxPoint.x + m_BoundryBox.minPoint.x) / 2;
		m_Position.y = (m_BoundryBox.maxPoint.y + m_BoundryBox.minPoint.y) / 2;
		m_Position.z = (m_BoundryBox.maxPoint.z + m_BoundryBox.minPoint.z) / 2;*/
		
		m_prePositon = m_Position;

  		/*vgCore::QuadtreeSceneManager &mgr = 
  					vgCore::QuadtreeSceneManager::getSingleton();
 
  		if (mgr.GetNodeAbstract(m_id))
  		{
  	  		mgr.GetNodeAbstract(m_id)->GetBoundryBox() = m_BoundryBox;
  			
			mgr.GetNodeAbstract(m_id)->m_Position = m_Position;
		}*/
		
	}


	
	void	Node::RotatePoint(float baseU, float baseV, float angle, float *pointU, float *pointV)
	{
		float U1; 
		float V1;
		U1=*pointU;
		V1=*pointV;
		double angle1=GetAngle(baseU, baseV, U1, V1);
		double disp=CallDisp(baseU, baseV, U1, V1);
		U1=baseU + disp * cos(angle + angle1);
		V1=baseV + disp * sin(angle + angle1);
		*pointU=U1;
		*pointV=V1;
	}

	double	Node::GetAngle( float baseU , float baseV , float pointU , float pointV )
	{
		double r, angl;
		//如果基点和计算点是同一个点
		if(fabs(baseU-pointU)<=0.001 && fabs(baseV-pointV)<=0.001)
			return 0;
		if(fabs(baseU-pointU)<=0.001)   //如果两个点在一个竖直的直线上
		{
			if(pointV>baseV)
				angl=(double)(PI/2);
			else
				angl=(double)(PI*3/2);
			return angl;

		}
		else
		{
			//得到两点距离
			r=(double)sqrt((pointU-baseU)*(pointU-baseU) + (pointV-baseV)*(pointV-baseV));
			double kk=(pointU-baseU)/r;

			//	2008年8月7日9:16:21 add by ma 解决旋转时出现的破面问题
			if (kk <= -0.9999 )
			{
				angl = 3.14159;
			}
			else if (kk >= 0.9999)
			{
				angl = 0;
			}
			else
				angl=(double)acos(kk);
			
			
			if(pointV<baseV)
				angl=(double)(PI*2)-angl;
			return angl;
		}
	}

	double	Node::CallDisp( float U1, float V1, float U2, float V2 )
	{
		return (double)sqrt((U1-U2)*(U1-U2) + (V1-V2)*(V1-V2));	
	}

	void Node::setDefault()
	{
		//	属性
		m_id			= -1;
		strcpy(this->m_LayerName, (""));	
		strcpy(this->m_name, (""));		
		m_Scale.reset(1.0, 1.0, 1.0);
		m_Rotation.reset(0.0, 0.0, 0.0);
		m_RenderTypeInt		= 0;

		//	状态
		m_propid		= -1;
		m_isDeleted		= false;
		m_isSelected	= false;
		m_isVisible		= true;

		//	数据
		m_numOfVerts	= 0;
		m_numOfMat		= 0;
		pMats			= NULL;
	}
}