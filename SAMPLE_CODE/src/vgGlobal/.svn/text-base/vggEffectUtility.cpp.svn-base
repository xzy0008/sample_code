


#include <vgStableHeaders.h>
#include <vgGlobal/vggEffectUtility.h>

#include <vgMod/vgModMisc.h>
#include <vgMod/vgTriggerManager.h>

#include <vgKernel/vgkSelectManager.h>
#include <vgKernel/vgkInputSystem.h>

#include <vgMovingManager.h>

#include <DlgTriggerConfig.h>


namespace vgGlobal{

	//----------------------------------------------------------------
	bool EffectUtility::addFountain()
	{
		vgMod::ModMisc::getSingleton().setStatus( VG_STATUS_FOUNTAIN );

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::addFire()
	{
		vgMod::ModMisc::getSingleton().setStatus( VG_STATUS_FIRE );

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::addSmoke()
	{
		vgMod::ModMisc::getSingleton().setStatus( VG_STATUS_SMOKE );

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::beginRain()
	{
		vgCore::MovingManager::getSingleton().getClimate()->rainon();

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::endRain()
	{
		vgCore::MovingManager::getSingleton().getClimate()->rainoff();

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::beginSnow()
	{
		vgCore::MovingManager::getSingleton().getClimate()->snowon();

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::endSnow()
	{
		vgCore::MovingManager::getSingleton().getClimate()->snowoff();

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::configDynbillboard()
	{
		vgMod::ModMisc::getSingleton().getDlgDynBillboard()->DoModal();

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::generateDynbillboard()
	{
		vgMod::ModMisc::getSingleton().setStatus( VG_STATUS_DYNBILLBOARD_GENERATE );

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::configPlanting()
	{
		vgMod::ModMisc::getSingleton().getDlgTreeSet()->DoModal();

		return true;
	}

#if 0
	//----------------------------------------------------------------
	bool EffectUtility::beginPlanting()
	{
		vgMod::ModMisc::getSingleton().setStatus( VG_STATUS_PLANT_TREE );

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::plantInLine()
	{
		vgMod::ModMisc::getSingleton().setStatus( VG_STATUS_PLANT_IN_LINE );

		return true;
	}

#endif
	//----------------------------------------------------------------
	bool EffectUtility::setAsTrigger()
	{
		vgKernel::RendererQueue& selectedBuffer = vgKernel::SelectManager::
			getSingleton().getSelectedItems();
		if (selectedBuffer.empty())
		{
			AfxMessageBox("请选择单面渲染的MOD模型！");
			vgKernel::SelectManager::getSingleton().clearSelection();
			return false;
		}

		//m_bSetAsTrigger = !m_bSetAsTrigger;


		vgKernel::RendererQueue::iterator iter = selectedBuffer.begin();
		vgKernel::RendererQueue::iterator end = selectedBuffer.end();
		for (; iter != end; iter++)
		{
			vgMod::TriggerManager::getSingleton().addTrigger(*iter);
		}

		return true;
	}

	//----------------------------------------------------------------
	bool EffectUtility::configTrigger()
	{
		CDlgTriggerConfig	dlg;
		dlg.DoModal();

		return true;
	}
}//namespace vgXXX