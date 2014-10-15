
#include <vgStableHeaders.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgTrigger/vgtrTriggerManager.h>
#include <vgUIController/vgUIController.h>
#include <vgEntry/vgEntryFactory.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgCam/vgcaCamManager.h>

#include <vgTrigger/vgtrCommandMsg.h>
#include "vgTrigger/vgtrCommandAvi.h"
#include "vgTrigger/vgtrCommandKeyframe.h"
#include "vgTrigger/vgtrCommandSound.h"
#include "vgTrigger/vgtrCommandText2D.h"
#include <vgTrigger/vgtrCommandScript.h>
#include <vgTrigger/vgtrTriggerRenderCommand.h>
#include <vgKernel/vgkRenderCommandManager.h>

namespace vgTrigger{

	//----------------------------------------------------------------
	TriggerManager::TriggerManager()
		:Singleton<TriggerManager>(VGK_SINGLETON_LEFE_TRIGGER_EXT)
	{
		statusFlag = VG_INPUT_TRIGGER;

		vgKernel::InputSystem::getSingleton().registerHandle(this);

		m_pTriggerRenderBegin = new TriggerRenderCommand;

		vgKernel::RenderCommandFacade::AddCommand(m_pTriggerRenderBegin);
	}
	
	//----------------------------------------------------------------
	TriggerManager::~TriggerManager()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(m_pTriggerRenderBegin);
		m_pTriggerRenderBegin = NULL;
	}

	bool TriggerManager::shutdown()
	{
 		for (int i=0; i<m_triggerList.size(); i++)
 		{
 			if (m_triggerList.at(i) != NULL)
 			{
 				vgKernel::RendererManager::getSingleton().deleteRenderer(m_triggerList.at(i));
			}
 		}

		return true;
	}

 	bool TriggerManager::onDeleteRenderer( vgKernel::Renderer* renderer )
 	{
 		if (renderer->getType() != RENDERER_TYPE_TRIGGER)
 		{
 			return false;
 		}
 
		for (int i=0; i<m_triggerList.size(); i++)
		{
			if (m_triggerList[i] == renderer)
			{
				delete m_triggerList[i];

				m_triggerList[i] = NULL;
				
				return true;
			}
		}
 
 		return false;
 	}

	Trigger*	TriggerManager::addTrigger(vgKernel::Renderer *pRenderer)
	{		
		if (find(m_triggerList.begin(), m_triggerList.end(), pRenderer) == m_triggerList.end())
		{
			Trigger *pTrigger = new Trigger(pRenderer);
			vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( pTrigger );
			HTREEITEM	hRoot = vgUI::UIController::getSingleton().getEntryRootItemByType(STATIC_ENTRY_TRIGGER);

			vgUI::UIController::getSingleton().AddNode(hRoot , entry );
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRoot);
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRoot);
			m_triggerList.push_back(pTrigger);

			vgKernel::RendererManager::getSingleton().addRenderer(pTrigger);

			return pTrigger;
		}

		return NULL;
	}


	void TriggerManager::OnLButtonDown(UINT nFlags, CPoint position)
	{
		m_downPosition = position;
	}

	void TriggerManager::OnLButtonUp(UINT nFlags, CPoint position)
	{
		if ( ! m_triggerEnable )
		{
			return ;
		}

		if (abs(position.x-m_downPosition.x) + abs(position.y-m_downPosition.y) < 1e-1)
		{
			Trigger *pClickedTrigger = testClick(position);

			if (pClickedTrigger != NULL && pClickedTrigger->getTriggerEnable())
			{
				pClickedTrigger->fireOnClicked();
			}
		}
	}

	Trigger* TriggerManager::testClick(CPoint position)
	{
		using namespace vgKernel;

		Renderer* tmpMesh = NULL;
		Vec3 click_pos = vgKernel::Math::trans2DPointTo3DVec(position.x, position.y);
		Vec3 camera_pos = vgCam::CamManager::getSingleton().getCurrentPosition();
		vgKernel::Ray translatedRay;


		Vec3 click_dir = click_pos - camera_pos;
		click_dir.normalise();

		vgKernel::Ray click_ray(camera_pos , click_dir);
		std::pair<bool, float> result;

		vgKernel::RendererPackage* _culledRenderers = 
			RendererManager::getSingletonPtr()->getCulledRendererPackage();
		RendererPackage::iterator ipac = _culledRenderers->begin();
		RendererPackage::iterator ipac_end = _culledRenderers->end();

		RendererQueue resultQueue;

		//m_bufferMap.clear();
		float distance = 1e10f;

		for ( ; ipac != ipac_end; ++ ipac )
		{
			RendererQueue* que = &ipac->second;
			assert( que != NULL );

			RendererQueue::iterator iter  = que->begin();
			RendererQueue::iterator iter_end = que->end();

			for ( ; iter != iter_end ; ++ iter )
			{
				Renderer* cr = *iter;

				if ( (cr->isSelectable() == false || cr->getVisible() == false))
				{
					continue;
				}

				result = vgKernel::Math::intersects( click_ray, cr->getBoundingBox() );

				if (result.first && result.second < distance)
				{
					std::pair<bool, float> testres = 
						cr->testIntersectWithTriangles( click_ray );

					if ( testres.first == true && testres.second < distance )
					{

						if (find(resultQueue.begin(), resultQueue.end(), cr) != resultQueue.end())
						{
							//VGK_SHOW("Fixed \n");
							continue;
						}

						if (!resultQueue.empty() && tmpMesh != NULL)
						{
							resultQueue.pop_back();
						}

						resultQueue.push_back( cr );
						tmpMesh = cr;
						distance = testres.second;

						TRACE("Select %s Distance : %f \n", cr->getName().c_str(), distance);
					}
				}

			}
		}// end ipac

//  
//  		for (int i=0; i<m_triggerList.size(); i++)
//  		{
//  			vgKernel::Renderer *cr = m_triggerList[i];
//  
//  			result = vgKernel::Math::intersects( click_ray, cr->getBoundingBox() );
//  
//  			if (result.first && result.second < distance)
//  			{
//  				std::pair<bool, float> testres = 
//  					cr->testIntersectWithTriangles( click_ray );
//  
//  				if ( testres.first == true && testres.second < distance )
//  				{
//  
//  					if (find(resultQueue.begin(), resultQueue.end(), cr) != resultQueue.end())
//  					{
//  						//VGK_SHOW("Fixed \n");
//  
//  						continue;
//  					}
//  
//  					if (!resultQueue.empty() && tmpMesh != NULL)
//  					{
//  						resultQueue.pop_back();
//  					}
//  
//  					resultQueue.push_back( cr );
//  					tmpMesh = cr;
//  					distance = testres.second;
//  
//  					TRACE("Select %s Distance : %f \n", cr->getName().c_str(), distance);
//  				}
//  			}
//  		}

		if (resultQueue.size() == 1 && resultQueue[0]->getType() == RENDERER_TYPE_TRIGGER)
		{	
			return dynamic_cast<Trigger*>(resultQueue[0]);
		}

		return NULL;
	}

	void TriggerManager::checkOnEveryFrame()
	{
		vgKernel::Vec3 pos = 
			vgCam::CamManager::getSingleton().getCurrentPosition();
		
 		for (int i=0; i<m_triggerList.size(); i++)
 		{
 			if (m_triggerList.at(i) != NULL)
 			{
 				m_triggerList.at(i)->positionCheck(pos);
 			}
 		}
	}

	Trigger* TriggerManager::getCurrentSelectedTrigger()
	{
		vgKernel::RendererQueue queue = vgKernel::SelectManager::getSingleton().getSelectedItems();

		if (queue.size() == 1 && queue.at(0)->getType() == RENDERER_TYPE_TRIGGER)
		{
			return dynamic_cast<Trigger*>(queue.at(0));
		}

		return NULL;
	}

	Trigger* TriggerManager::getTriggerByName(string name)
	{
		for (int i=0; i<m_triggerList.size(); i++)
		{
			if (m_triggerList.at(i)->getName() == name)
			{
				return m_triggerList[i];
			}
		}

		return NULL;
	}

	bool TriggerManager::writeToVgFile(string savePath)
	{
		// 写入有多少Trigger
		
		// 顺序写入每个Trigger信息
		// Trigger名，Inner Renderer名
		// 有多少个Cmd
		// 顺序写入每个Cmd Cmd的名字，Cmd的类型，Cmd的信息
		FILE *fp;

		fp = fopen(savePath.c_str(), "wb+");
		
		int triggerCnt = m_triggerList.size();
		// 多少个Trigger
		fwrite(&triggerCnt, sizeof(triggerCnt), 1, fp);

		for (int i=0; i<triggerCnt; i++)
		{
			int triggerNameLen, rendererNameLen;
			
			triggerNameLen = m_triggerList[i]->getName().length();

			fwrite(&triggerNameLen, sizeof(triggerNameLen), 1, fp);
	
			fwrite(m_triggerList[i]->getName().c_str(), 
				triggerNameLen, 1, fp);

			rendererNameLen = m_triggerList[i]->getInnerNamePtr()->length();
			fwrite(&rendererNameLen, sizeof(rendererNameLen), 1, fp);

			fwrite(m_triggerList[i]->getInnerNamePtr()->c_str(), 
				rendererNameLen, 1, fp);

			CommandPtrArray* pCmdArray 
				= m_triggerList[i]->getCommandArrayPtr();
			
			int cmdCnt = pCmdArray->size();

			fwrite(&cmdCnt, sizeof(cmdCnt), 1, fp);

			for (int j=0; j<pCmdArray->size(); j++)
			{
				int ctp = pCmdArray->at(j)->getType();
				fwrite(&ctp, sizeof(ctp), 1, fp);

				pCmdArray->at(j)->saveToFile(fp);
			}	
		}

		fclose(fp);

		return true;
	}

	bool TriggerManager::readFromVgFile(string readPath)
	{
		
		FILE *fp;

		fp = fopen(readPath.c_str(), "rb");
		
		if (fp == NULL)
		{
			return false;
		}

		int triggerCnt;
		// 多少个Trigger
		fread(&triggerCnt, sizeof(triggerCnt), 1, fp);

		vgTrigger::Trigger *pTrigger;

		for (int i=0; i<triggerCnt; i++)
		{
			pTrigger = NULL;

			int triggerNameLen, rendererNameLen;
			char buffer[256], rendererName[256];
			
			fread(&triggerNameLen, sizeof(triggerNameLen), 1, fp);
			
			fread(buffer, triggerNameLen, 1, fp);
			
			fread(&rendererNameLen, sizeof(rendererNameLen), 1, fp);

			fread(rendererName, rendererNameLen, 1, fp);
			
			buffer[triggerNameLen] = '\0';
			rendererName[rendererNameLen] = '\0';

			vgKernel::Renderer *pRenderer = 
				vgKernel::RendererManager::getSingleton().getRendererbyName(rendererName);
			
			if (pRenderer != NULL)
			{
				pTrigger = addTrigger(pRenderer);

				pTrigger->setName(buffer);
			}
			else
			{
				assert(0);
			}
			
			TRACE("Read Trigger Name %s \n", buffer);

			int cmdCnt;

			fread(&cmdCnt, sizeof(cmdCnt), 1, fp);
			TRACE("Trigger has %d command \n", cmdCnt);

			for (int j=0; j<cmdCnt; j++)
			{
				int ctp;
				fread(&ctp, sizeof(ctp), 1, fp);
				
				CommandAbstract* pCommand = NULL;

				switch (ctp)
				{
				case TRIGGER_COMMAND_MSG:
					pCommand = new CommandMsg;
					break;

				case TRIGGER_COMMAND_TEXT2D:
					pCommand = new CommandText2D;
					break;

				case TRIGGER_COMMAND_SOUND3D:
					pCommand = new CommandSound;
					break;

				case TRIGGER_COMMAND_KEYFRAME:
					pCommand = new CommandKeyframe;
					break;

				case TRIGGER_COMMAND_AVI:
					pCommand = new CommandAvi;
					break;

				case TRIGGER_COMMAND_SCRIPT:
					pCommand = new CommandScript;
					break;
				}

				assert(pCommand != NULL);

				CommandPtr ptr(pCommand);
				ptr->readFromFile(fp);
				
				assert(pTrigger != NULL);

				pTrigger->regeditEvent(ptr);
			}	
		}

		fclose(fp);

		return true;
	}
}//namespace vgTrigger