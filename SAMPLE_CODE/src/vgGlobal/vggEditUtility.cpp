


#include <vgStableHeaders.h>
#include <vgGlobal/vggEditUtility.h>

#include <vgGlobal/vggSystemFacade.h>

#include <vgKernel/vgkInputSystem.h>

#include <vgMod/vgObjFrameNode.h>

#include <DlgFindObject.h>
#include <DlgTranslateAll.h>

namespace vgGlobal{

	bool EditUtility::m_bSetSelTransprent = false;
	bool EditUtility::m_bSetSelUnTransprent = false;
	bool EditUtility::m_bSingleFaceRenderSel = false;
	bool EditUtility::m_bSingleFaceRenderAll = false;

	bool EditUtility::m_bTranslateMode = false;
	bool EditUtility::m_bRotateMode = false;
	bool EditUtility::m_bScaleMode = false;

	bool EditUtility::m_bSelectModeInclude = false;
	bool EditUtility::m_bSelectModeIntersect = true;

	//----------------------------------------------------------------
	bool EditUtility::translate()
	{
		vgKernel::SelectManager::getSingleton().setEditMode( vgKernel::ATrans );

		m_bTranslateMode = !m_bTranslateMode;
		m_bRotateMode = false;
		m_bScaleMode = false;

		if ( !m_bTranslateMode )
		{
			vgKernel::SelectManager::getSingleton().setEditMode( vgKernel::Default );
		}

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::rotate()
	{
		vgKernel::SelectManager::getSingleton().setEditMode( vgKernel::ARot );

		m_bRotateMode = !m_bRotateMode;
		m_bTranslateMode = false;
		m_bScaleMode = false;

		if ( !m_bRotateMode )
		{
			vgKernel::SelectManager::getSingleton().setEditMode( vgKernel::Default );
		}

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::scale()
	{
		vgKernel::SelectManager::getSingleton().setEditMode( vgKernel::AScal );

		m_bScaleMode = !m_bScaleMode;
		m_bTranslateMode = false;
		m_bRotateMode = false;

		if ( !m_bScaleMode )
		{
			vgKernel::SelectManager::getSingleton().setEditMode( vgKernel::Default );
		}

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::updateTranslate()
	{
		return m_bTranslateMode;
	}

	//----------------------------------------------------------------
	bool EditUtility::updateRotate()
	{
		return m_bRotateMode;
	}

	//----------------------------------------------------------------
	bool EditUtility::updateScale()
	{
		return m_bScaleMode;
	}

	//----------------------------------------------------------------
	bool EditUtility::undo()
	{
		vgKernel::SelectManager::getSingleton().Undo();

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::redo()
	{
		vgKernel::SelectManager::getSingleton().Redo();

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::selectionAll()
	{
		vgKernel::SelectManager::getSingleton().selectAllObject();
		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::clearSelection()
	{
		vgKernel::SelectManager::getSingleton().clearSelection();

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::selectionReverse()
	{
		vgKernel::SelectMode* pMode = 
			vgKernel::SelectManager::getSingleton().getSelectMode();
		assert( pMode != NULL );

		pMode->selectRegionMode = vgKernel::SRM_Reverse;
		vgKernel::SelectManager::getSingleton().setSelectMode( pMode );

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::FindObject()
	{
		CDlgFindObject dlg;
		dlg.DoModal();

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::selectShapeRect()
	{
		vgKernel::SelectMode* pMode = 
			vgKernel::SelectManager::getSingleton().getSelectMode();
		assert( pMode != NULL );

		pMode->selectRegionShape = vgKernel::SRS_Rect;
		vgKernel::SelectManager::getSingleton().setSelectMode( pMode );

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::selectShapePolygon()
	{
		vgKernel::SelectMode* pMode = 
			vgKernel::SelectManager::getSingleton().getSelectMode();
		assert( pMode != NULL );

		pMode->selectRegionShape = vgKernel::SRS_Polygon;
		vgKernel::SelectManager::getSingleton().setSelectMode( pMode );

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::selectRegionNew()
	{
		vgKernel::SelectMode* pMode = 
			vgKernel::SelectManager::getSingleton().getSelectMode();
		assert( pMode != NULL );

		pMode->selectRegionMode = vgKernel::SRM_New;
		vgKernel::SelectManager::getSingleton().setSelectMode( pMode );

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::selectRegionAdd()
	{
		vgKernel::SelectMode* pMode = 
			vgKernel::SelectManager::getSingleton().getSelectMode();
		assert( pMode != NULL );

		pMode->selectRegionMode = vgKernel::SRM_Add;
		vgKernel::SelectManager::getSingleton().setSelectMode( pMode );

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::selectRegionSubtract()
	{
		vgKernel::SelectMode* pMode = 
			vgKernel::SelectManager::getSingleton().getSelectMode();
		assert( pMode != NULL );

		pMode->selectRegionMode = vgKernel::SRM_Subtract;
		vgKernel::SelectManager::getSingleton().setSelectMode( pMode );

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::selectRegionIntersect()
	{
		vgKernel::SelectMode* pMode = 
			vgKernel::SelectManager::getSingleton().getSelectMode();
		assert( pMode != NULL );

		pMode->selectRegionMode = vgKernel::SRM_Intersection;
		vgKernel::SelectManager::getSingleton().setSelectMode( pMode );

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::selectModeInclude()
	{
		vgKernel::SelectMode* pMode = 
			vgKernel::SelectManager::getSingleton().getSelectMode();
		assert( pMode != NULL );

		pMode->isInclude = true;
		vgKernel::SelectManager::getSingleton().setSelectMode( pMode );

		m_bSelectModeInclude = true;
		m_bSelectModeIntersect = false;

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::selectModeIntersect()
	{
		vgKernel::SelectMode* pMode = 
			vgKernel::SelectManager::getSingleton().getSelectMode();
		assert( pMode != NULL );

		pMode->isInclude = false;
		vgKernel::SelectManager::getSingleton().setSelectMode( pMode );

		m_bSelectModeInclude = false;
		m_bSelectModeIntersect = true;

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::translateAll()
	{
		CDlgTranslateAll	tranDlg;

		tranDlg.DoModal();

		vgKernel::RendererManager::getSingleton().translateAllRenderers(
			tranDlg.getTranslateVec() );

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::translateSeleted()
	{
		CDlgTranslateAll tranDlg;
		tranDlg.DoModal();

		/*vgGlobal::SystemFacade::translateRenderers( 
			&vgKernel::SelectManager::getSingleton().getSelectedItems() , tranDlg.getTranslateVec() );*/

		translateRenderers(&vgKernel::SelectManager::getSingleton().getSelectedItems(), 
			tranDlg.getTranslateVec() );

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::setSelTransparent()
	{
		if ( vgGlobal::EditUtility::setSelectNodesToTransparent( true ) )
		{
			m_bSetSelTransprent = true;
			m_bSetSelUnTransprent = false;
		}
		
		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::setSelUnTransparent()
	{
		if ( vgGlobal::EditUtility::setSelectNodesToTransparent( false ) )
		{
			m_bSetSelTransprent = false;
			m_bSetSelUnTransprent = true;
		}
		
		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::updateSetSelTransprant()
	{
		return m_bSetSelTransprent;
	}

	//----------------------------------------------------------------
	bool EditUtility::updateSetSelUnTransprant()
	{
		return m_bSetSelUnTransprent;
	}

	//----------------------------------------------------------------
	bool EditUtility::SingleFaceRenderSelected()
	{
		vgKernel::RendererQueue& selectedBuffer = vgKernel::SelectManager::
			getSingleton().getSelectedItems();
		if (selectedBuffer.empty())
		{
			AfxMessageBox("请选择单面渲染的MOD模型！");
			vgKernel::SelectManager::getSingleton().clearSelection();
			return false;
		}

		m_bSingleFaceRenderSel = !m_bSingleFaceRenderSel;

		vgKernel::RendererQueue::iterator iter = selectedBuffer.begin();
		vgKernel::RendererQueue::iterator end = selectedBuffer.end();
		for (; iter != end; iter++)
		{
			vgMod::ObjFrameNode* pNode = dynamic_cast<vgMod::ObjFrameNode*>(*iter);

			if ( pNode == NULL )
			{
				continue;
			}
			assert( pNode != NULL );
			
			pNode->setRenderDoubleSidesState( !m_bSingleFaceRenderSel );  //false 为单面渲染
		}

		m_bSingleFaceRenderAll = false;
		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::updateSingleFaceRenderSelect()
	{
		return m_bSingleFaceRenderSel;
	}

	//----------------------------------------------------------------
	bool EditUtility::SingleFaceRenderAll()
	{
		vgKernel::RendererQueue*	selectedBuffer = vgKernel::RendererManager::
			getSingleton().getRendererQueueByType(vgMod::RENDERER_TYPE_MODOJBECT,false);

		if ( !selectedBuffer || selectedBuffer->empty())
		{
			return false;
		}

		m_bSingleFaceRenderAll = !m_bSingleFaceRenderAll;

		vgKernel::RendererQueue::iterator iter = selectedBuffer->begin();
		vgKernel::RendererQueue::iterator end = selectedBuffer->end();
		for (; iter != end; iter++)
		{
			vgMod::ObjFrameNode* pNode = dynamic_cast<vgMod::ObjFrameNode*>(*iter);

			if ( pNode == NULL )
			{
				continue;
			}
			assert( pNode != NULL );

			pNode->setRenderDoubleSidesState( !m_bSingleFaceRenderAll );
		}

		m_bSingleFaceRenderSel = false;
		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::updateSingleFaceRenderAll()
	{
		return m_bSingleFaceRenderAll;
	}


	/************************************************************************/
	/* 私有成员                                                             */
	/************************************************************************/

	//----------------------------------------------------------------
	bool EditUtility::setSelectNodesToTransparent( bool bSet )
	{
		vgKernel::RendererQueue& selectedBuffer = vgKernel::SelectManager::
			getSingleton().getSelectedItems();
		if (selectedBuffer.empty())
		{
			AfxMessageBox("请选择需要半透明的模型！");
			return false;
		}

		vgKernel::RendererQueue::iterator iter = selectedBuffer.begin();
		vgKernel::RendererQueue::iterator end = selectedBuffer.end();
		for (; iter != end; iter++)
		{
			vgKernel::TransparentObject* pNode = 
				dynamic_cast<vgKernel::TransparentObject*>(*iter);

			if ( pNode == NULL )
			{
				continue;
			}
			assert( pNode != NULL );

			pNode->setTransparent( bSet );
		}

		return true;
	}

	//----------------------------------------------------------------
	bool EditUtility::translateRenderers(vgKernel::RendererQueue* queue,
		                                 const vgKernel::Vec3& trans_vec  )
	{
		if ( queue == NULL )
		{
			return false;
		}

		vgKernel::RendererQueue*	pQuene = queue;

		vgKernel::RendererQueue::iterator	iter_quene = pQuene->begin();
		vgKernel::RendererQueue::iterator	iter_queneEnd = pQuene->end();
		for (; iter_quene != iter_queneEnd; iter_quene++)
		{
			vgKernel::Renderer*	pRenderer = *iter_quene;
			if (pRenderer)
			{
				pRenderer->translate( trans_vec.x, trans_vec.y, trans_vec.z );
			}
		}

		return true;
	}

}//namespace vgXXX
