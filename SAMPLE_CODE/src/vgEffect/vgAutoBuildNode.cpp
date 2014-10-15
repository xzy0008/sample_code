#include <vgStableHeaders.h>
#include <vgEffect/vgAutoBuildNode.h>
#include <vgKernel/vgkRenderer.h>

namespace vgCore
{
	AutoBuildNode::AutoBuildNode() : vgKernel::Renderer(RENDERER_TYPE_AUTOBUILD)
	{
		m_pTopVertex = NULL;
		m_pMidVertex = NULL;

		m_pTopVert = NULL;
		m_pMidVert = NULL;

		m_initUnit = 1;

		return ;
	}

	AutoBuildNode::~AutoBuildNode()
	{
		if (m_pMidVertex != NULL)
		{
			delete [] m_pMidVertex;
		}

		if (m_pTopVertex != NULL)
		{
			delete [] m_pTopVertex;
		}
		
		if (m_pMidVert != NULL)
		{
			delete [] m_pMidVert; 
		}

		if (m_pTopVert != NULL)
		{
			delete [] m_pTopVert;
		}

		delete m_pTopNode;
		delete m_pMidNode;
		delete m_pBottomNode;

		return ;
	}
	
	void AutoBuildNode::render()
	{
		if (m_pTopNode != NULL)
		{
			m_pTopNode->Render();
		}

		if (m_pMidNode != NULL)
		{
			m_pMidNode->Render();
		}

		if (m_pBottomNode != NULL)
		{
			m_pBottomNode->Render();
		}
	}

	bool AutoBuildNode::constructFromObjectNodes(ObjectNode* top, ObjectNode* mid, ObjectNode* bottom)
	{
		assert(mid != NULL);

		this->m_pTopNode = top;
		this->m_pMidNode = mid;
		this->m_pBottomNode = bottom;
		
		m_uid = mid->getUniqueID();
		
		if (m_pTopVertex != NULL)
		{
			delete [] m_pTopVertex;
			m_pTopVertex = NULL;
		}


		if (m_pMidVertex != NULL)
		{
			delete [] m_pMidVertex;
			m_pMidVertex = NULL;
		}

		if (m_pMidVert != NULL)
		{
			delete [] m_pMidVert;
			m_pMidVert = NULL;
		}


		if (m_pTopVert != NULL)
		{
			delete [] m_pTopVert;
			m_pTopVert = NULL;
		}
		
		if (top != NULL)
		{
			m_pTopVertex = new VertexElementStruct[top->m_numOfVerts];

			m_pTopVert = new Vector3[top->m_numOfVertexs];
		
#ifdef VG_VBO_SUPPORT
			m_pTopNode->mapVertexBuffer();
#endif

			memcpy(m_pTopVertex, m_pTopNode->pVertex, sizeof(VertexElementStruct) * top->m_numOfVerts);
			memcpy(m_pTopVert, m_pTopNode->pVert, sizeof(Vector3) * top->m_numOfVertexs);

#ifdef VG_VBO_SUPPORT
			m_pTopNode->unmapVertexBuffer();
#endif 
		}

		if (mid != NULL)
		{
			m_pMidVert = new Vector3[mid->m_numOfVertexs];

			m_pMidVertex = new VertexElementStruct[mid->m_numOfVerts];

#ifdef VG_VBO_SUPPORT
			m_pMidNode->mapVertexBuffer();
#endif 

			memcpy(m_pMidVertex, m_pMidNode->pVertex, sizeof(VertexElementStruct) * mid->m_numOfVerts);
			memcpy(m_pMidVert, m_pMidNode->pVert, sizeof(Vector3) * mid->m_numOfVertexs);

#if VG_VBO_SUPPORT
			m_pMidNode->unmapVertexBuffer();
#endif 

		}

		m_yLevel = m_pMidNode->GetBoundryBox().getCenter().y;
		m_perHeight = abs( m_pMidNode->GetBoundryBox().maxPoint.y - m_pMidNode->GetBoundryBox().minPoint.y);

		TRACE("Y level is %f \n", m_yLevel);
		TRACE("Height is %f. \n", m_perHeight);

		updataBoundingBox();
		
		return true;
	}

	
	std::pair<bool, float> AutoBuildNode::testIntersectWithTriangles( const vgKernel::Ray& ray )
	{
		std::pair<bool, float> result;
		std::pair<bool, float> tmpResult;

		tmpResult = m_pMidNode->testIntersectWithTriangles(ray);
		result = tmpResult;

		if (m_pTopNode != NULL)
		{
			tmpResult = m_pTopNode->testIntersectWithTriangles(ray);

			if (result.first && tmpResult.first && tmpResult.second < result.second)
			{
				result = tmpResult;
			} 
			else if (!result.first && tmpResult.first)
			{
				result = tmpResult;
			}
			
			if (m_pBottomNode != NULL)
			{
				tmpResult = m_pBottomNode->testIntersectWithTriangles(ray);

				if (result.first && tmpResult.first && tmpResult.second < result.second)
				{
					result = tmpResult;
				} 
				else if (!result.first && tmpResult.first)
				{
					result = tmpResult;
				}
			}
			else
			{
				return result;
			}
		}
		else
		{
			return result;
		}

		return result;
	}


	void AutoBuildNode::translate(const float& x, const float& y, const float& z)
	{
		if (m_pTopNode != NULL)
		{
			m_pTopNode->translate(Vector3(x,y,z));
			for (int i=0; i<m_pTopNode->m_numOfVertexs; i++)
			{
				m_pTopVert[i].y += y;
			}

			for (int i=0; i<m_pTopNode->m_numOfVerts; i++)
			{
				m_pTopVertex[i].positionY += y;
			}
		}

		if (m_pMidNode != NULL)
		{
			m_pMidNode->translate(Vector3(x,y,z));
			for (int i=0; i<m_pMidNode->m_numOfVertexs; i++)
			{
				m_pMidVert[i].y += y;
			}

			for (int i=0; i<m_pMidNode->m_numOfVerts; i++)
			{
				m_pMidVertex[i].positionY += y;
			}
		}

		if (m_pBottomNode != NULL)
		{
			m_pBottomNode->translate(Vector3(x,y,z));
		}

		m_yLevel += y;

		updataBoundingBox();

		UpdatePos();

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}

	void AutoBuildNode::updataBoundingBox()
	{
		vgMath::Vector3	maxVertex(m_pMidNode->GetBoundryBox().maxPoint);
		vgMath::Vector3 minVertex(m_pMidNode->GetBoundryBox().minPoint);
		vgKernel::Box	box;

		box.setMaximum(vgKernel::Vec3(maxVertex.x, maxVertex.y, maxVertex.z) );
		box.setMinimum(vgKernel::Vec3(minVertex.x, minVertex.y, minVertex.z) );	

		m_boundingBox = box;
	
		if (m_pTopNode != NULL)
		{
			maxVertex = m_pTopNode->GetBoundryBox().maxPoint;
			minVertex = m_pTopNode->GetBoundryBox().minPoint;

			box.setMaximum(vgKernel::Vec3(maxVertex.x, maxVertex.y, maxVertex.z) );
			box.setMinimum(vgKernel::Vec3(minVertex.x, minVertex.y, minVertex.z) );	

			m_boundingBox.merge(box);
		}

		if (m_pBottomNode != NULL)
		{
			maxVertex = m_pBottomNode->GetBoundryBox().maxPoint;
			minVertex = m_pBottomNode->GetBoundryBox().minPoint;

			box.setMaximum(vgKernel::Vec3(maxVertex.x, maxVertex.y, maxVertex.z) );
			box.setMinimum(vgKernel::Vec3(minVertex.x, minVertex.y, minVertex.z) );	

			m_boundingBox.merge(box);
		}
	}

	bool AutoBuildNode::setSize(int size)
	{
		if (size < 1)
			return false;

		m_zeroHeight = m_pMidNode->GetBoundryBox().minPoint.y;
		m_upperHeight = m_pMidNode->GetBoundryBox().maxPoint.y;

		float topTranslateHeight = m_perHeight * (size - m_initUnit);

		if (size >= m_initUnit)
		{
#ifdef VG_VBO_SUPPORT
			m_pMidNode->mapVertexBuffer();
#endif 
 			for (int i=0; i<m_pMidNode->m_numOfVerts; i++)
 			{
 				if (m_pMidNode->pVertex[i].positionY == m_upperHeight)
 				{
 					m_pMidNode->pVertex[i].positionY = m_pMidVertex[i].positionY + m_perHeight * (size-m_initUnit); 
 					m_pMidNode->pVertex[i].texCoorT = m_pMidVertex[i].texCoorT + (size-m_initUnit) * (1 / m_initUnit); 
 				}
 			}

	 		for (int i=0; i<m_pMidNode->m_numOfVertexs; i++)
	 		{
	 			if (m_pMidNode->pVert[i].y == m_upperHeight)
	 			{
	 				m_pMidNode->pVert[i].y = m_pMidVert[i].y + m_perHeight * (size-m_initUnit);
	 			}
	 		}
#ifdef VG_VBO_SUPPORT
			m_pMidNode->unmapVertexBuffer();
#endif  
		}
		else if (size < m_initUnit)
		{
#ifdef VG_VBO_SUPPORT
			m_pMidNode->mapVertexBuffer();
#endif 

			for (int i=0; i<m_pMidNode->m_numOfVerts; i++)
			{
				if (m_pMidNode->pVertex[i].positionY != m_zeroHeight)
				{
					m_pMidNode->pVertex[i].positionY = m_pMidVertex[i].positionY - (m_pMidVertex[i].positionY-m_zeroHeight) * (1 - size / m_initUnit); //+ m_perHeight * (size-m_initUnit); 
					m_pMidNode->pVertex[i].texCoorT = m_pMidVertex[i].texCoorT * (size / m_initUnit); //+ (size-m_initUnit) * (1 / m_initUnit); 
				}
			}

			for (int i=0; i<m_pMidNode->m_numOfVertexs; i++)
			{
				if (m_pMidNode->pVert[i].y != m_zeroHeight)
				{
					m_pMidNode->pVert[i].y = m_pMidVert[i].y -  (m_pMidVert[i].y-m_zeroHeight)*(1 - size / m_initUnit); //+ m_perHeight * (size-m_initUnit);
				}
			}

#ifdef VG_VBO_SUPPORT
			m_pMidNode->unmapVertexBuffer();
#endif 
		}

		if (m_pTopNode != NULL)
		{
#ifdef VG_VBO_SUPPORT
			m_pTopNode->mapVertexBuffer();
#endif 
			for (int i=0; i<m_pTopNode->m_numOfVerts; i++)
			{
				m_pTopNode->pVertex[i].positionY = m_pTopVertex[i].positionY + topTranslateHeight; 
			}

			for (int i=0; i<m_pTopNode->m_numOfVertexs; i++)
			{
				m_pTopNode->pVert[i].y = m_pTopVert[i].y + topTranslateHeight;
			}
#ifdef VG_VBO_SUPPORT
			m_pTopNode->unmapVertexBuffer();
#endif
			m_pTopNode->ComputeBoundBox();
		}

 		m_pMidNode->ComputeBoundBox();
 
 		updataBoundingBox();

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		return true;
	}
}