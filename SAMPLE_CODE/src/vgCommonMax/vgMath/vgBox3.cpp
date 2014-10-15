
#include "vgStableHeaders.h"
#include "vgMath/vgBox3.h"

namespace vgMath {

	//----------------------------------------------------------------------------
	void	CBox3::merge( CBox3& boxRef )
	{
		m_maxPoint.enlarge(boxRef.m_maxPoint);
		m_minPoint.narrow(boxRef.m_minPoint);
	}

	//----------------------------------------------------------------------------
	void CBox3::merge( CVector3& pointRef )
	{
		m_maxPoint.enlarge( pointRef );
		m_minPoint.narrow( pointRef );
	}

	//----------------------------------------------------------------------------
	int CBox3::write( FILE* pFile )
	{
		size_t sizeBlock = sizeof(CVector3);
		sizeBlock += fwrite(&m_minPoint , sizeof(CVector3) , 1, pFile)*sizeof(CVector3);
		sizeBlock += fwrite(&m_maxPoint , sizeof(CVector3) , 1, pFile)*sizeof(CVector3);

		CVector3 midPoint = center();
		sizeBlock += fwrite(&midPoint , sizeof(CVector3) , 1, pFile)*sizeof(CVector3);

		return (int)sizeBlock;
	}

	//----------------------------------------------------------------------------
	int CBox3::read( FILE* pFile )
	{
		size_t sizeBlock = 0;

		sizeBlock += fread(&m_minPoint , sizeof(CVector3) , 1, pFile);
		sizeBlock += fread(&m_maxPoint , sizeof(CVector3) , 1, pFile);

		CVector3 midPoint;
		sizeBlock += fread(&midPoint , sizeof(CVector3) , 1, pFile);

		return (int)sizeBlock;
	}

	//----------------------------------------------------------------------------
	CBox3 CBox3::formatAsVGBox()
	{
		CBox3 tmpBox(*this);
		CVector3	maxPoint = this->m_maxPoint.formatAsVG();
		CVector3	minPoint = this->m_minPoint.formatAsVG();

		float tmpFloat = maxPoint.z;
		maxPoint.z = minPoint.z;
		minPoint.z = tmpFloat;

		return CBox3(maxPoint, minPoint);
	}
}// namespace vgMath