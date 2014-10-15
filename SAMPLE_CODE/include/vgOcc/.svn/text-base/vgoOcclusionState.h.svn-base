#ifndef __VGOCCSTATE_H__
#define __VGOCCSTATE_H__

namespace vgOcclusion{
	
	
	class OcclusionState 
	{
	protected:
		int		m_nOcclusionQuery;
		int		m_nLastVisited;
		int		m_nLastRendered; 
		bool	m_bHasRendered;
	public:
		int&	GetOcclusionQuery()	{	return	m_nOcclusionQuery;	}
		int&	GetLastVisited()	{	return	m_nLastVisited;		}
		int&	GetLastRendered()	{	return	m_nLastRendered;	}
		bool&	GetFlagHasRendered(){	return	m_bHasRendered;		}
	public:
		OcclusionState()
			: m_nOcclusionQuery(0), m_nLastVisited(0) , m_nLastRendered(0), m_bHasRendered(false){}
	};//class	OcclusionState //zhu 2008-4-10 ÕÚµ²ÌÞ³ýÏà¹Ø
	
}

#endif