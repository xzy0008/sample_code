
#ifndef   _VGBOX3_H_INCLUDED_
#define   _VGBOX3_H_INCLUDED_	
/**********************************************************************
*<
vgBox3.h:	三维包围盒的数据结构声明
主要内容是： 包围盒结构体
*>	
**********************************************************************/

#include "vgMath/vgVec3.h"

#include <string>
using namespace std;


namespace vgMath {

	class CBox3
	{
	public:
		CBox3()
			:m_maxPoint( (float)-INT_MAX)
			,m_minPoint( (float) INT_MAX)	{	}

		CBox3(CVector3 refMaxPoint, CVector3 refMinPoint)
			:m_maxPoint( refMaxPoint )
			,m_minPoint( refMinPoint )	{	}

		CBox3(CBox3& refBox)
			:m_maxPoint(refBox.m_maxPoint)
			,m_minPoint(refBox.m_minPoint)	{	}

	public:
		void	merge(CBox3& boxRef);
	
		void	merge(CVector3& pointRef);

	public:
		CVector3&	rightTop()
		{
			return m_maxPoint;
		}

		CVector3&	leftBottom()
		{
			return m_minPoint;
		}

		CVector3	center()
		{
			return  (m_maxPoint + m_minPoint) * 0.5f;
		}

		CVector3	size()
		{
			return m_maxPoint + m_minPoint * (-1.0f);
		}

	public:
		int write(FILE* pFile);
		
		int read(FILE* pFile);

		CBox3 formatAsVGBox();

	protected:
		CVector3	m_maxPoint;
		CVector3	m_minPoint;

	};// class CBox3

}// namespace vgMath

#endif	//_VGBOX3_H_INCLUDED_	