#ifndef VGAUTOBUILD_H
#define VGAUTOBUILD_H

#include <vgCore/vgPrerequisites.h>
#include <vgMod/vgObjNode.h>
#include <vgkernel/vgkRenderer.h>
#include <vgMod/vgModelStruct.h>

namespace vgAutoBuild
{

	const vgKernel::RendererType RENDERER_TYPE_AUTOBUILD	    = 5103;


	class  VGDEP_EXPORT AutoBuildNode : public vgMod::Node, public vgKernel::Renderer
	{
		VGK_RENDERER_IN_DECLARE( AutoBuildNode )
	public:
		AutoBuildNode();

		virtual ~AutoBuildNode();

	// 继承自Node的成员
	public:
		
		virtual void	Initialize(){}
		virtual void	Render()	{  render(); }

		virtual void	WriteNodeToVG(CFile &fp);
		virtual void	ReadNodeFromVG(CFile &fp);

		virtual	unsigned long PositDataToNode(char *pBytes)	{ return 0; }
		
		//virtual bool	testIntersection( vgMath::Ray* ray )	{ return false;}// 用于精确单选(用box和ray相交判定)
		virtual bool	testIntersection( const vgCore::ImageRect& rect ,
			int *viewport , GLdouble* proj_mat , GLdouble* model_mat )	{return false;}// 用于精确框选(用box的8个点判断)

	// 继承自Renderer的成员
	public:
		virtual void  render();
		
		virtual bool constructFromObjectNodes(vgMod::ObjectNode* top, vgMod::ObjectNode* mid, vgMod::ObjectNode* bottom);

		virtual bool setSize(int size);
		
		void setUnit(float unit)
		{
			m_initUnit = unit;

			m_perHeight = m_perHeight / unit;

			m_size = m_initUnit;
		}

		float getUnit()
		{
			return m_initUnit;
		}

		int getSize()
		{
			return m_size;
		}

		virtual string getName()
		{
			return m_pMidNode->getName();
			//return m_nodeName;
		}
		
		virtual string GetName()
		{
			return m_pMidNode->GetName();
			//return m_nodeName;
		}

		virtual void translate(const float& x, const float& y, const float& z);

		virtual void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
		{
 			if (m_pTopNode != NULL)
 			{
				m_pTopNode->scale(cx, cy, cz, x, y, z);
 			}

			if (m_pMidNode != NULL)
			{
				m_pMidNode->scale(cx, cy, cz, x, y, z);
			}

			if (m_pBottomNode != NULL)
			{
				m_pBottomNode->scale(cx, cy, cz, x, y, z);
			}

			updataBoundingBox();
		}

		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z)
		{
			if (m_pTopNode != NULL)
			{
				m_pTopNode->rotate(angle, cx, cy, cz, x, y, z);
			}

			if (m_pMidNode != NULL)
			{
				m_pMidNode->rotate(angle, cx, cy, cz, x, y, z);
			}
 			
			if (m_pBottomNode != NULL)
			{
				m_pBottomNode->rotate(angle, cx, cy, cz, x, y, z);
			}

			updataBoundingBox();
		}
		
		virtual vgKernel::Box getBoundingBox()
		{
			return m_boundingBox;
		}


		virtual void setName( const String& newname )
		{ 
			return m_pMidNode->setName(newname);
			//m_nodeName = newname;
		}
		
		virtual void SetName( TCHAR* nameString )
		{
			return m_pMidNode->SetName(nameString);
		}

		virtual String* getNamePtr()
		{
			return m_pMidNode->getNamePtr();
			//return &m_nodeName;
		}

		virtual long getNumOfTriangles()
		{
			return m_pMidNode->getNumOfTriangles() + m_pBottomNode->getNumOfTriangles() + m_pTopNode->getNumOfTriangles();
		}

		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  )
		{
			return 0;
		}

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z)
		{
			vgKernel::Vec3 center = m_boundingBox.getCenter();

			m_pTopNode->rotate(angle, center.x, center.y, center.z, x, y, z);
			m_pMidNode->rotate(angle, center.x, center.y, center.z, x, y, z);
			m_pBottomNode->rotate(angle, center.x, center.y, center.z, x, y, z);
			
			updataBoundingBox();

			return ; 
		}

		virtual vgKernel::UniqueID getUniqueID()
		{
			return m_uid;
		}

		virtual	bool testIntersection( vgMath::Ray* ray )
		{
			TRACE("Test intersection in AUTOBUILDNODE. \n");
			return m_pMidNode->testIntersection(ray) | 
					m_pTopNode->testIntersection(ray) | 
					m_pBottomNode->testIntersection(ray);
		}
		
		std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray );

		bool destoryRenderResource();

		void updataBoundingBox();

	// 
	public:
		bool cloneFromAutobuildNode(AutoBuildNode *src_node);

	private:
		vgCore::VertexElementStruct*	m_pMidVertex;
		vgCore::VertexElementStruct*    m_pTopVertex;

		Vector3*				m_pTopVert;
		Vector3*				m_pMidVert;
		
		float					m_yLevel;
		float					m_perHeight;
		
		float					m_zeroHeight;
		float					m_upperHeight;

		float					m_initUnit;

	public:
		vgMod::ObjectNode *m_pTopNode;
		
		vgMod::ObjectNode *m_pMidNode;

		vgMod::ObjectNode *m_pBottomNode;

	private:
		vgKernel::UniqueID m_uid;

		vgKernel::Box m_boundingBox;
		
		int m_size;

// 		int m_maxSize;
// 
// 		int m_minSize;

// 		int m_peopleUnit;
// 
// 		String m_nodeName;

	};


	VGK_RENDERER_OUT_DECLARE( AutoBuildNode )
}
#endif
