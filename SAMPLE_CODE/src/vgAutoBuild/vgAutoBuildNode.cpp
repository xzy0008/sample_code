#include <vgStableHeaders.h>
#include <vgAutoBuild/vgAutoBuildNode.h>

#include <vgKernel/vgkRenderer.h>




namespace vgAutoBuild
{
	VGK_RENDERER_IMPLEMENT( AutoBuildNode , RENDERER_TYPE_AUTOBUILD)

	AutoBuildNode::AutoBuildNode() 
	{
		m_pTopVertex = NULL;
		m_pMidVertex = NULL;

		m_pTopVert = NULL;
		m_pMidVert = NULL;

		m_pMidNode = NULL;
		m_pTopNode = NULL;
		m_pBottomNode = NULL;

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

	bool AutoBuildNode::constructFromObjectNodes(vgMod::ObjectNode* top, vgMod::ObjectNode* mid, vgMod::ObjectNode* bottom)
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
			m_pTopVertex = new vgCore::VertexElementStruct[top->m_numOfVerts];

			m_pTopVert = new vgMath::Vector3[top->m_numOfVertexs];
		

			m_pTopNode->mapVertexBuffer();


			memcpy(m_pTopVertex, m_pTopNode->pVertex, sizeof(vgCore::VertexElementStruct) * top->m_numOfVerts);
			memcpy(m_pTopVert, m_pTopNode->pVert, sizeof(vgMath::Vector3) * top->m_numOfVertexs);


			m_pTopNode->unmapVertexBuffer();

		}

		if (mid != NULL)
		{
			m_pMidVert = new vgMath::Vector3[mid->m_numOfVertexs];

			m_pMidVertex = new vgCore::VertexElementStruct[mid->m_numOfVerts];


			m_pMidNode->mapVertexBuffer();


			memcpy(m_pMidVertex, m_pMidNode->pVertex, sizeof(vgCore::VertexElementStruct) * mid->m_numOfVerts);
			memcpy(m_pMidVert, m_pMidNode->pVert, sizeof(vgMath::Vector3) * mid->m_numOfVertexs);


			m_pMidNode->unmapVertexBuffer();


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
			m_pTopNode->translate(vgMath::Vector3(x,y,z));
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
			m_pMidNode->translate(vgMath::Vector3(x,y,z));
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
			m_pBottomNode->translate(vgMath::Vector3(x,y,z));
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

			m_pMidNode->mapVertexBuffer();

 			for (int i=0; i<m_pMidNode->m_numOfVerts; i++)
 			{
 				//if (m_pMidNode->pVertex[i].positionY == m_upperHeight)
				if (abs(m_pMidNode->pVertex[i].positionY - m_upperHeight) < 1e-2)
				{
 					m_pMidNode->pVertex[i].positionY = m_pMidVertex[i].positionY + m_perHeight * (size-m_initUnit); 
 					m_pMidNode->pVertex[i].texCoorT = m_pMidVertex[i].texCoorT + (size-m_initUnit) * (1 / m_initUnit); 
 				}
 			}

	 		for (int i=0; i<m_pMidNode->m_numOfVertexs; i++)
	 		{
	 			//if (m_pMidNode->pVert[i].y == m_upperHeight)
				if (abs(m_pMidNode->pVert[i].y - m_upperHeight) < 1e-2)
				{
	 				m_pMidNode->pVert[i].y = m_pMidVert[i].y + m_perHeight * (size-m_initUnit);
	 			}
	 		}

			m_pMidNode->unmapVertexBuffer();
 
		}
		else if (size < m_initUnit)
		{

			m_pMidNode->mapVertexBuffer();


			for (int i=0; i<m_pMidNode->m_numOfVerts; i++)
			{
				//if (m_pMidNode->pVertex[i].positionY != m_zeroHeight)
				if (abs(m_pMidNode->pVertex[i].positionY - m_zeroHeight) > 1e-2)
				{
					m_pMidNode->pVertex[i].positionY = m_pMidVertex[i].positionY - (m_pMidVertex[i].positionY-m_zeroHeight) * (1 - size / m_initUnit); //+ m_perHeight * (size-m_initUnit); 
					m_pMidNode->pVertex[i].texCoorT = m_pMidVertex[i].texCoorT * (size / m_initUnit); //+ (size-m_initUnit) * (1 / m_initUnit); 
				}
			}

			for (int i=0; i<m_pMidNode->m_numOfVertexs; i++)
			{
				//if (m_pMidNode->pVert[i].y != m_zeroHeight)
				if (abs(m_pMidNode->pVert[i].y - m_zeroHeight) > 1e-2)
				{
					m_pMidNode->pVert[i].y = m_pMidVert[i].y -  (m_pMidVert[i].y-m_zeroHeight)*(1 - size / m_initUnit); //+ m_perHeight * (size-m_initUnit);
				}
			}


			m_pMidNode->unmapVertexBuffer();

		}

		if (m_pTopNode != NULL)
		{

			m_pTopNode->mapVertexBuffer();

			for (int i=0; i<m_pTopNode->m_numOfVerts; i++)
			{
				m_pTopNode->pVertex[i].positionY = m_pTopVertex[i].positionY + topTranslateHeight; 
			}

			for (int i=0; i<m_pTopNode->m_numOfVertexs; i++)
			{
				m_pTopNode->pVert[i].y = m_pTopVert[i].y + topTranslateHeight;
			}

			m_pTopNode->unmapVertexBuffer();

			m_pTopNode->ComputeBoundBox();
		}

 		m_pMidNode->ComputeBoundBox();
 
 		updataBoundingBox();

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		
		m_size = size;

		return true;
	}

	void AutoBuildNode::WriteNodeToVG(CFile &fp)
	{
		int flag;
	// 		vgMod::ObjectNode *m_pTopNode;
	// 
	// 		vgMod::ObjectNode *m_pMidNode;
	// 
	// 		vgMod::ObjectNode *m_pBottomNode;
		ULONGLONG filePos = fp.GetPosition();
		stringstream outString;

// 		outString.flush();
// 		outString << "File begin pos"<< filePos <<"\n";
// 		VGK_SHOW(outString.str());
// 		outString.str(0);

		if (m_pTopNode != NULL)
		{
			flag = 1;
			fp.Write(&flag, sizeof(int));
			m_pTopNode->WriteNodeToVG(fp);
		}
		else
		{
			flag = 0;
			fp.Write(&flag, sizeof(int));
		}

		if (m_pMidNode != NULL)
		{
			flag = 1;
			fp.Write(&flag, sizeof(int));
			m_pMidNode->WriteNodeToVG(fp);
		}
		else
		{
			flag = 0;
			fp.Write(&flag, sizeof(int));
		}

		if (m_pBottomNode != NULL)
		{
			flag = 1;
			fp.Write(&flag, sizeof(int));
			m_pBottomNode->WriteNodeToVG(fp);
		}
		else
		{
			flag = 0;
			fp.Write(&flag, sizeof(int));
		}

// 		vgCore::VertexElementStruct*	m_pMidVertex;
// 		vgCore::VertexElementStruct*    m_pTopVertex;

		filePos = fp.GetPosition();
// 		outString.flush();
// 		outString << "File Vertex pos"<< filePos <<"\n";
// 		VGK_SHOW(outString.str());
// 		outString.str(0);

		fp.Write(m_pMidVertex, sizeof(vgCore::VertexElementStruct) * m_pMidNode->m_numOfVerts);


		if (m_pTopVertex != NULL)
		{
			flag = 1;

			fp.Write(&flag, sizeof(int));
			fp.Write(m_pTopVertex, sizeof(vgCore::VertexElementStruct) * m_pTopNode->m_numOfVerts);
		}
		else
		{
			flag = 0;
			fp.Write(&flag, sizeof(int));
		}


// 		Vector3*				m_pMidVert;
// 		Vector3*				m_pTopVert;
		filePos = fp.GetPosition();
// 		outString.flush();
// 		outString << "File vert pos"<< filePos <<"\n";
// 		VGK_SHOW(outString.str());
// 		outString.str(0);

		fp.Write(m_pMidVert, sizeof(Vector3) * m_pMidNode->m_numOfVertexs);

		if (m_pTopVert != NULL)
		{
			flag = 1;
			fp.Write(&flag, sizeof(int));
			fp.Write(m_pTopVert, sizeof(Vector3) * m_pTopNode->m_numOfVertexs);
		}
		else
		{
			flag = 0;
			fp.Write(&flag, sizeof(int));
		}

// 		float					m_yLevel;
// 		float					m_perHeight;
// 
// 		float					m_zeroHeight;
// 		float					m_upperHeight;
// 
// 		float					m_initUnit;
		
		filePos = fp.GetPosition();
// 		outString.flush();
// 		outString << "File attribute pos"<< filePos <<"\n";
// 		VGK_SHOW(outString.str());

// 		outString.flush();
// 		outString	<< "Level       "<< m_yLevel     << "\n"
// 					<< "Perheight   "<< m_perHeight  << "\n"
// 					<< "ZeroHeight  "<< m_zeroHeight << "\n"
// 					<< "UpperHeight "<< m_upperHeight<< "\n"
// 					<< "unit        "<< m_initUnit   << "\n";
// 		VGK_SHOW(outString.str());
// 		outString.str(0);

		fp.Write(&m_yLevel, sizeof(float));
		fp.Write(&m_perHeight, sizeof(float));
		fp.Write(&m_zeroHeight, sizeof(float));
		fp.Write(&m_upperHeight, sizeof(float));
		fp.Write(&m_initUnit, sizeof(float));
		fp.Write(&m_size, sizeof(int));
// 		vgKernel::UniqueID m_uid;
		fp.Write(&m_uid, sizeof(vgKernel::UniqueID)); 

// 		flag = m_nodeName.length();
// 
// 		fp.Write(&flag, sizeof(int));
// 
// 		const char* buffer = m_nodeName.c_str();
// 
// 		fp.Write(buffer, sizeof(char) * flag);
// 		
// 		fp.Write(&m_size, sizeof(int));
	}

	void AutoBuildNode::ReadNodeFromVG(CFile &fp)
	{
		// 		vgMod::ObjectNode *m_pTopNode;
		// 
		// 		vgMod::ObjectNode *m_pMidNode;
		// 
		// 		vgMod::ObjectNode *m_pBottomNode;

		stringstream outString;
		ULONGLONG filePos = fp.GetPosition();
		
/*		outString.flush();*/
/*		outString << "File begin pos"<< filePos <<"\n";*/
// 		VGK_SHOW(outString.str());
// 		outString.str(0);

		int flag;

		fp.Read(&flag, sizeof(int));
		if (flag == 1)
		{
#if 1
			m_pTopNode = new vgMod::ObjectNode;
			m_pTopNode->ReadNodeFromVG(fp);
#else
			m_pTopNode = vgMod::ObjectNode::ReadNodeFromVGByType(fp);
#endif
		}
		else
		{
			m_pTopNode = NULL;
		}

		fp.Read(&flag, sizeof(int));
		if (flag == 1)
		{
#if 1
			m_pMidNode = new vgMod::ObjectNode;
			m_pMidNode->ReadNodeFromVG(fp);
#else
			m_pMidNode = vgMod::ObjectNode::ReadNodeFromVGByType(fp);
#endif
		}
		else
		{
			m_pMidNode = NULL;
		}

		fp.Read(&flag, sizeof(int));
		if (flag == 1)
		{
#if 1
			m_pBottomNode = new vgMod::ObjectNode;
			m_pBottomNode->ReadNodeFromVG(fp);
#else
			m_pBottomNode = vgMod::ObjectNode::ReadNodeFromVGByType(fp);
#endif
		}
		else
		{
			m_pBottomNode = NULL;
		}

		// 		vgCore::VertexElementStruct*	m_pMidVertex;
		// 		vgCore::VertexElementStruct*    m_pTopVertex;
		filePos = fp.GetPosition();
// 		outString.flush();
// 		outString << "File Vertex pos"<< filePos <<"\n";
// 		VGK_SHOW(outString.str());
// 		outString.str(0);

		m_pMidVertex = new vgCore::VertexElementStruct[m_pMidNode->m_numOfVerts];
		fp.Read(m_pMidVertex, sizeof(vgCore::VertexElementStruct) * m_pMidNode->m_numOfVerts);
		
		fp.Read(&flag, sizeof(int));
		if (flag == 1)
		{
			m_pTopVertex = new vgCore::VertexElementStruct[m_pTopNode->m_numOfVerts];

			fp.Read(m_pTopVertex, sizeof(vgCore::VertexElementStruct) * m_pTopNode->m_numOfVerts);
		}

		filePos = fp.GetPosition();
// 		outString.flush();
// 		outString << "File vert pos"<< filePos <<"\n";
// 		VGK_SHOW(outString.str());
// 		outString.str(0);


		// 		Vector3*				m_pMidVert;
		// 		Vector3*				m_pTopVert;
		m_pMidVert = new Vector3[m_pMidNode->m_numOfVertexs];

		fp.Read(m_pMidVert, sizeof(Vector3) * m_pMidNode->m_numOfVertexs);

		fp.Read(&flag, sizeof(int));
		if (flag == 1)
		{
			m_pTopVert = new Vector3[m_pTopNode->m_numOfVertexs];
			fp.Read(m_pTopVert, sizeof(Vector3) * m_pTopNode->m_numOfVertexs);
		}
		

		// 		float					m_yLevel;
		// 		float					m_perHeight;
		// 
		// 		float					m_zeroHeight;
		// 		float					m_upperHeight;
		// 
		// 		float					m_initUnit;
		// 
		filePos = fp.GetPosition();
// 		outString.flush();
// 		outString << "File attribute pos"<< filePos <<"\n";
// 		VGK_SHOW(outString.str());

		fp.Read(&m_yLevel, sizeof(float));
		fp.Read(&m_perHeight, sizeof(float));
		fp.Read(&m_zeroHeight, sizeof(float));
		fp.Read(&m_upperHeight, sizeof(float));
		fp.Read(&m_initUnit, sizeof(float));
		fp.Read(&m_size, sizeof(int));

// 		outString.flush();
// 		outString << "Level       "<< m_yLevel     << "\n"
// 				  << "Perheight   "<< m_perHeight  << "\n"
// 				  << "ZeroHeight  "<< m_zeroHeight << "\n"
// 				  << "UpperHeight "<< m_upperHeight<< "\n"
// 				  << "unit        "<< m_initUnit   << "\n";
//  		VGK_SHOW(outString.str());
//  		outString.str("");

		// 		vgKernel::UniqueID m_uid;
		fp.Read(&m_uid, sizeof(vgKernel::UniqueID)); 
		
 		updataBoundingBox();
// 
// 		fp.Read(&flag, sizeof(int));
// 		
// 		char *buffer = new char[flag];
// 		fp.Read(buffer, flag * sizeof(char));
// 
// 		m_nodeName = buffer;
// 		
// 		fp.Read(&m_size, sizeof(int));

	}

	bool AutoBuildNode::cloneFromAutobuildNode(AutoBuildNode *src_node)
	{
		if (src_node->m_pTopNode != NULL)
		{
			m_pTopNode = new vgMod::ObjectNode;
			m_pTopNode->cloneFromObjectNode(src_node->m_pTopNode);
		}
		else
		{
			m_pTopNode = NULL;
		}

		if (src_node->m_pMidNode != NULL)
		{
			m_pMidNode = new vgMod::ObjectNode;
			m_pMidNode->cloneFromObjectNode(src_node->m_pMidNode);
		}
		else
		{
			m_pMidNode = NULL;
		}

		if (src_node->m_pBottomNode != NULL)
		{
			m_pBottomNode = new vgMod::ObjectNode;
			m_pBottomNode->cloneFromObjectNode(src_node->m_pBottomNode);
		}
		else
		{
			m_pBottomNode = NULL;
		}

// 
// 		vgCore::VertexElementStruct*	m_pMidVertex;
// 		vgCore::VertexElementStruct*    m_pTopVertex;

		m_pMidVertex = new vgCore::VertexElementStruct[m_pMidNode->m_numOfVerts];
		memcpy(m_pMidVertex, src_node->m_pMidVertex, sizeof(vgCore::VertexElementStruct) * m_pMidNode->m_numOfVerts);

		assert(m_pMidVertex != NULL);
		
		TRACE("TAG --- 1 \n");
		if (src_node->m_pTopVert != NULL)
		{
			m_pTopVertex = new vgCore::VertexElementStruct[m_pTopNode->m_numOfVerts];
			memcpy(m_pTopVertex, src_node->m_pTopVertex, sizeof(vgCore::VertexElementStruct) * m_pTopNode->m_numOfVerts);
		}
		else
		{
			m_pTopVert = NULL;
		}
		
		TRACE("TAG --- 2 \n");
// 		Vector3*				m_pTopVert;
// 		Vector3*				m_pMidVert;

		m_pMidVert = new Vector3[m_pMidNode->m_numOfVertexs];
		memcpy(m_pMidVert, src_node->m_pMidVert, sizeof(Vector3) * m_pMidNode->m_numOfVertexs);
		TRACE("TAG --- 2.5 \n");
		if (src_node->m_pTopVert != NULL)
		{
			m_pTopVert = new Vector3[m_pTopNode->m_numOfVertexs];
			memcpy(m_pTopVert, src_node->m_pTopVert, sizeof(Vector3) * m_pTopNode->m_numOfVertexs);
		}
		else
		{
			m_pTopVert = NULL;
		}
		TRACE("TAG --- 3 \n");
		m_yLevel = src_node->m_yLevel;

		m_perHeight	= src_node->m_perHeight;

		m_zeroHeight = src_node->m_zeroHeight;

		m_upperHeight = src_node->m_upperHeight;

		m_initUnit = src_node->m_initUnit;

		m_size = src_node->m_size;

		m_uid = vgKernel::UniqueIDFactory::getUniqueID();
		
		updataBoundingBox();
	
		return true;
	}
}