#include <vgStableHeaders.h>
#include <vgGIS3D/vggiContourManager.h>
#include <vgGIS3D/vggiGisRenderCommmand.h>
#include <vgKernel/vgkRenderCommandManager.h>

namespace vgGIS3D
{
	ContourManager::ContourManager()
		:vgKernel::Singleton<ContourManager>(VGK_SINGLETON_LEFE_GIS3D)
	{
		m_enableRender = true;
	}

	ContourManager::~ContourManager()
	{
		for (int i=0; i<m_contourArray.size(); i++)
		{
			if (m_contourArray[i] != NULL)
			{
				delete m_contourArray[i];
			}
		}
	}

	bool ContourManager::initialise()
	{
		m_pContourRenderCommand = new ContourRenderCommand;

		vgKernel::RenderCommandFacade::AddCommand( m_pContourRenderCommand );
	
		return true;
	}

	bool ContourManager::shutdown()
	{
		if (m_pContourRenderCommand != NULL)
		{
			vgKernel::RenderCommandFacade::RemoveCommand(m_pContourRenderCommand);
			m_pContourRenderCommand = NULL;
		}

		return true;
	}

	bool ContourManager::addContour(Contour *newContour)
	{
		vector<Contour*>::iterator iter = m_contourArray.begin();
		vector<Contour*>::iterator iter_end = m_contourArray.end();

		if (find(iter, iter_end, newContour) != iter_end)
		{
			return false;
		}

		m_contourArray.push_back(newContour);

		return true;
	}

	bool ContourManager::removeContour(Contour *newContour)
	{
		vector<Contour*>::iterator iter = m_contourArray.begin();
		vector<Contour*>::iterator iter_end = m_contourArray.end();
		vector<Contour*>::iterator fiter;

		if ((fiter = find(iter, iter_end, newContour)) != iter_end)
		{
			delete (*fiter);
			m_contourArray.erase(fiter);
		}

		return false;
	}

	Contour* ContourManager::getContour(int i)
	{
		assert(i>=0 && i<m_contourArray.size());
		
		return m_contourArray[i];
	}

	Contour* ContourManager::getContourByName(string name)
	{
		for(int i=0; i<m_contourArray.size(); i++)
		{
			if (m_contourArray[i]->GetName() == name)
			{
				return m_contourArray[i];
			}
		}

		return NULL;
	}

	
	void ContourManager::traceAllContour()
	{
		for (int i=0; i<m_contourArray.size(); i++)
		{
			Contour *pContour = m_contourArray.at(i);
			
			TRACE("Contour %d \n", i);

			if (pContour == NULL)
			{
				continue;
			}

			CContourArray& conArr = pContour->getContoursArray();
			//获取等值线值列表数目
			int num=pContour->GetNumberOfValues();
			if (num==0)
			{
				return;
			}
			//获取等值线最小值
			float noisemin=pContour->GetValue(0);
			float noisemax=pContour->GetValue(num-1);
			//获取等值线值列表数目结束
			//设置颜色表最小值，最大值
			/* ColorTable.SetValueRange(pCon->GetDataOwner()->GetDataInfo().NoiseMin,pCon->GetDataOwner()->GetDataInfo().NoiseMax);*/
			// m_ColorTable.SetValueRange(noisemin,noisemax);
			if (conArr.GetCount() == 0)
			{
				return;
			}
			for (int indexCurList = 0; indexCurList < conArr.GetCount(); indexCurList ++)
			{
				/*float val = list.GetNext(valuepos);*/
				TRACE("Line %d\n", indexCurList);

				CCurveList* pCurveList = conArr.GetAt(indexCurList);
				if (!pCurveList)
				{
					continue;
				}
				//获取等值线的头位置
				POSITION pos = pCurveList->GetHeadPosition();
				//获取等值线值头位置结束
				//获取等值线的噪声值
				float noisevalue = pContour->GetValue(indexCurList);

				// 获取等值线颜色
				// COLORREF   m_LineColor=m_ColorTable.LookUpColor(noisevalue);
				// 等值线颜色结束

				while( pos != NULL )
				{
					CCurve* pCurve = pCurveList->GetNext( pos );

					if (!pCurve)
					{
						continue;
					}

					for (int indexPoint= 0; indexPoint < pCurve->GetCount(); indexPoint ++)
					{
						TRACE("(%f, %f, %f) ", pCurve->GetAt(indexPoint).x, 0, pCurve->GetAt(indexPoint).z);
					}

				} // End of while
			} // End of for
		}	// End of for

		return;
	}

	void ContourManager::render()
	{
		if (! m_enableRender)
		{
			return ;
		}

		glPushAttrib(GL_ALL_ATTRIB_BITS);

		for (int i=0; i<m_contourArray.size(); i++)
		{
			Contour *pContour = m_contourArray.at(i);
			
			if (pContour == NULL)
			{
				continue;
			}
			
			if (! pContour->GetVisiable())
			{
				continue ;
			}
			
			if (! pContour->useBind())
			{
				continue;
			}

			vgKernel::Box boundingBox = pContour->getBoundingBox();

			glColor3f(1.0, 0, 0);
			vgKernel::Vec3 maxPos = boundingBox.getMaximum();
			vgKernel::Vec3 minPos = boundingBox.getMinimum();

			glBegin(GL_LINES);
			{
				glVertex3f( maxPos.x , maxPos.y , maxPos.z );
				glVertex3f( minPos.x , maxPos.y , maxPos.z );

				glVertex3f( maxPos.x , maxPos.y , maxPos.z );
				glVertex3f( maxPos.x , minPos.y , maxPos.z );

				glVertex3f( maxPos.x , maxPos.y , maxPos.z );
				glVertex3f( maxPos.x , maxPos.y , minPos.z );

				glVertex3f( minPos.x , minPos.y , minPos.z );
				glVertex3f( maxPos.x , minPos.y , minPos.z );

				glVertex3f( minPos.x , minPos.y , minPos.z );
				glVertex3f( minPos.x , maxPos.y , minPos.z );

				glVertex3f( minPos.x , minPos.y , minPos.z );
				glVertex3f( minPos.x , minPos.y , maxPos.z );

				glVertex3f( minPos.x , maxPos.y , maxPos.z );
				glVertex3f( minPos.x , maxPos.y , minPos.z );

				glVertex3f( minPos.x , maxPos.y , maxPos.z );
				glVertex3f( minPos.x , minPos.y , maxPos.z );


				glVertex3f( maxPos.x , minPos.y , maxPos.z );
				glVertex3f( maxPos.x , minPos.y , minPos.z );

				glVertex3f( maxPos.x , minPos.y , maxPos.z );
				glVertex3f( minPos.x , minPos.y , maxPos.z );

				glVertex3f( maxPos.x , minPos.y , minPos.z );
				glVertex3f( maxPos.x , maxPos.y , minPos.z );

				glVertex3f( minPos.x , maxPos.y , minPos.z );
				glVertex3f( maxPos.x , maxPos.y , minPos.z );
			}
			glEnd();

			CContourArray& conArr = pContour->getContoursArray();
			//获取等值线值列表数目
			// int num=pContour->GetNumberOfValues();
			int num = conArr.GetCount();
			int num2 = pContour->GetNumberOfValues();

			num = num ? num2 : num < num2;

			if (num==0)
			{
				return;
			}
			//获取等值线最小值
			float noisemin=pContour->GetValue(0);
			float noisemax=pContour->GetValue(num-1);
			//获取等值线值列表数目结束
			//设置颜色表最小值，最大值
			/* ColorTable.SetValueRange(pCon->GetDataOwner()->GetDataInfo().NoiseMin,pCon->GetDataOwner()->GetDataInfo().NoiseMax);*/
			// m_ColorTable.SetValueRange(noisemin,noisemax);
			if (conArr.GetCount() == 0)
			{
				return;
			}
			for (int indexCurList = 0; indexCurList < num; indexCurList ++)
			{
				/*float val = list.GetNext(valuepos);*/
				CCurveList* pCurveList = conArr.GetAt(indexCurList);
				if (!pCurveList)
				{
					continue;
				}
				//获取等值线的头位置
				POSITION pos = pCurveList->GetHeadPosition();
				//获取等值线值头位置结束
				//获取等值线的噪声值
				float noisevalue = pContour->GetValue(indexCurList);
				vgKernel::ColorVal color = pContour->GetColorByValue(noisevalue);

				glColor3f(color.r, color.g, color.b);
			
				// glDisable(GL_DEPTH_TEST);

				while( pos != NULL )
				{
					CCurve* pCurve = pCurveList->GetNext( pos );

					if (!pCurve)
					{
						continue;
					}

					glDisable(GL_DEPTH_TEST);
	
					//glColor3f(1,1,0);
					//glLineWidth(2);
					// glColor3f(1.0f, 1.8f, 0.5f);
					
					glBegin(GL_LINE_STRIP);
					for (int indexPoint= 0; indexPoint < pCurve->GetCount(); indexPoint ++)
					{
						glVertex3f( pCurve->GetAt(indexPoint).x, pCurve->GetAt(indexPoint).y+0.1, pCurve->GetAt(indexPoint).z);
					}

					glEnd();

					glEnable(GL_DEPTH_TEST);

				} // End of while
			} // End of for

			pContour->unBind();
		}	// End of for
		
		glPopAttrib();

		return;
	}
}