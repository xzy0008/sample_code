
#ifndef    _SPECIALEFFECT_H_INCLUDED_
#define    _SPECIALEFFECT_H_INCLUDED_

//#include <vgStableHeaders.h>
#include <vgMod/vgNode.h>

#include <vgMath/vgfBoundingBox.h>

#include <vgKernel/vgkRendererObserver.h>

#include <vgKernel/vgkRenderer.h>

// defines
//#define		PI				 3.14159265


//////////////////////////////////////////////////////////////////////////
// classes
namespace vgMod
{
	using namespace vgMod;
	/*
	5010 -- 5030之间为QuadTreeSceneMananger的管辖范围之内
	*/
	const vgKernel::RendererType RENDERER_TYPE_PARTICLE = 5011;
	
	//const CategoryType NODE_TYPE_PARTICLE	= 30;

	enum	E_PARTICLE_TYPE
	{
		PARTICLE_FOUNTAIN = 31,
		PARTICLE_FIRE,
		PARTICLE_SMOKE,
		PARTICLE_FLAG,
		PARTICLE_OTHER
	};

	class  vgParticle : public  Node, public vgKernel::Renderer
	{
	public:
		//	Part 0 :新增属性，相对class Node
		String _meshName;
		vgKernel::UniqueID _uniqueID;
		float	_squaredDistanceToViewer;

		
	public:
		//	新增属性，相对class Node
		int		  m_nParticleCount;		// 粒子数
		BOOL      m_bStopSE;			// 隐藏标记
		BOOL      m_bSwitchSE;			// 隐藏/显示模式切换
		enum   CONST2
		{
			PARTICLECOUNT = 2000,		// 缺省粒子数
		};
		string m_texturename;			// 材质名字

		float	m_height;
		float	m_width;
		float	m_speed;
		float	m_PartLenth;
		float   m_PartWidth;

		E_PARTICLE_TYPE	m_eSubType;
	public:
		//	访问自定义的属性
		void SetHeight(float height)	
		{	
			m_height =	height;

			translate( Vector3(0,0,0) );
		}
		void SetWidth (float width )	
		{	
			m_width	=	width;
			translate( Vector3(0,0,0) );

		}
		void SetSpeed (float speed )	{	m_speed	=	speed;	}
		void SetPartLength(float length){	m_PartLenth	=	length;	}
		void SetPartWidth (float width)	{	m_PartWidth	=	width;	}
		
		void SetCount(GLuint count = PARTICLECOUNT)	{	m_nParticleCount  = count ; }
		void StopSpecialEffect(BOOL m_bStopSE)		{	m_bStopSE = m_bStopSE;}

		E_PARTICLE_TYPE	getSubType()				{	return m_eSubType;}
		void	setSubType(E_PARTICLE_TYPE ptype)	{	m_eSubType = ptype;}

	public:
		//	实现父类的纯虚函数
		virtual	unsigned long	PositDataToNode( char *data);
		virtual	void	WriteNodeToVG(CFile &fp);
		virtual	void	translate( Vector3 offset );


		virtual	void	Render()								{	return; }
		virtual	void	scale(Vector3 Scale)					{	return; }		
		virtual	void	rotate(short axis, float angle)			{	return; }
		virtual	bool	testIntersection( vgMath::Ray* ray )	{	return false;	}
		virtual	bool	testIntersection( const vgCore::ImageRect& rect ,
			int *viewport , GLdouble* proj_mat , GLdouble* model_mat )	{	return false;	}

	public:
		//	实现父类的虚函数
		virtual	BoundingBox	ComputeBoundBox();

	public:
		//	自定义的其它功能函数
		vgParticle();
		~vgParticle();
			
#if 1
	public:
		//	继承Renderer而来的接口
		virtual String getName()
		{
			return _meshName;
		}

		virtual String* getNamePtr()
		{
			return &_meshName;
		}

		virtual void setName( const String& newname )
		{
			_meshName = newname;
		}

		virtual vgKernel::UniqueID getUniqueID()
		{
			return _uniqueID;
		}

		virtual void translate(const float& x, const float& y, const float& z)
		{
			translate(Vector3(x,y,z));
		}

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z)
		{

		}

		virtual void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
		{

		}

		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) 
		{

		}

		virtual std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray );

		virtual vgKernel::Box getBoundingBox()
		{
			vgMath::Vector3	maxVertex(GetBoundryBox().maxPoint);
			vgMath::Vector3 minVertex(GetBoundryBox().minPoint);
			vgKernel::Box	box;
			box.setMaximum(vgKernel::Vec3(maxVertex.x, maxVertex.y, maxVertex.z) );
			box.setMinimum(vgKernel::Vec3(minVertex.x, minVertex.y, minVertex.z) );
			return box;
		}

		virtual long getNumOfTriangles()
		{
			return m_numOfFaces;
		}

		/**
		注意,返回的是Distance的平方
		*/
		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  );

		virtual void	render(){	Render();}

	
	protected:
		void	configTextureName();
#endif		

	};// class  vgParticle
	
}// namespace vgCore

#endif  //   _SPECIALEFFECT_H_INCLUDED_