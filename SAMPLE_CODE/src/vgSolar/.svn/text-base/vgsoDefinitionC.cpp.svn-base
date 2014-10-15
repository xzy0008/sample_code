


#include <vgStableHeaders.h>
#include <vgSolar/vgsoDefinition.h>

#include <vgSolar/vgsoSolarManager.h>
#include <vgSolar/vgsoSolarPlugin.h>
#include <vgSolar/vgsoDateTimeAndLocation.h>
#include <vgKernel/vgkPluginManager.h>
#include <vgKernel/vgkSelectManager.h>
#include <vgSolar/SolarConfig.h>

extern "C" void VGSO_EXPORT  VGK_PLUGIN_DLL_START(void)
{
	vgKernel::PluginManager::getSingleton().registerPlugin( 
		new vgSolar::SolarPlugin );
}

extern "C" void VGSO_EXPORT VGK_PLUGIN_DLL_END(void)
{
	vgKernel::SingletonManager::getSingleton().deleteSingletonInstance( 
		vgSolar::SolarManager::getSingletonPtr() );
}




 vgKernel::Vec3* SolarManager_getLightDirection()
{
	using namespace vgSolar;
	return SolarManager::getSingleton().getLightDirection();
}



 bool SolarManager_getShadowEnabled()
{
	using namespace vgSolar;
	return SolarManager::getSingleton().getShadowEnabled();
}


 bool SolarManager_turnOffShadowEffect()
 {
	 using namespace vgSolar;
	 return SolarManager::getSingleton().turnOffShadowEffect();

 }

bool SolarManager_turnOnShadowEffect(
									 vgKernel::RendererQueue* renderer_queue , 
									 vgKernel::Vec3* new_light_dir , 
									 bool force_to_load )
 {
	 using namespace vgSolar;
	 return SolarManager::getSingleton().turnOnShadowEffect( renderer_queue , 
		 new_light_dir, 
		 force_to_load 
		 );

 }


 bool SolarManager_changeLightDirection( const vgKernel::Vec3& new_light_dir )
{
	using namespace vgSolar;
	return SolarManager::getSingleton().changeLightDirection( new_light_dir);

}



 bool SolarManager_changeDateTimeAndLoc( vgSolar::DateTimeAndLocation* loc )
 {
	 using namespace vgSolar;
	 return SolarManager::getSingleton().changeDateTimeAndLoc( loc);

 }


vgKernel::ShadowCastObjectVec* SolarManager_getShadowCastObjects()
{
	using namespace vgSolar;
	return SolarManager::getSingleton().getShadowCastObjects();

}

 bool SolarManager_setSolarAnalysis( bool enable_it )
{
	using namespace vgSolar;
	return SolarManager::getSingleton().setSolarAnalysis(enable_it);

 }
 bool SolarManager_getSolarAnalysisEnable()
 {
	 using namespace vgSolar;
	 return SolarManager::getSingleton().getSolarAnalysisEnable();

 }


 void doDailogAndChangeSolarLightDirection()
 {
	 using namespace vgSolar;

	 CSolarConfig dlg(
		 &SolarManager::getSingleton().getCurrentDateAndTime() );

	 if ( dlg.DoModal() == IDOK )
	 {
		 bool changeok = 
			 SolarManager::getSingleton().changeDateTimeAndLoc(&dlg.getTimeAndLoc());

		 if ( changeok == false )
		 {
			 ::MessageBox( NULL , "太阳还没有出现" , "提示" ,  MB_OK );
		 }
	 }

 }


 void doDailogAndSolarAnalysis()
 {
	 using namespace vgKernel;
	 using namespace vgSolar;

	 if ( SelectManager::getSingleton().getSelectedItems().empty() )
	 {
		 vgKernel::ShadowCastObjectVec* vec = 
			 SolarManager::getSingleton().getShadowCastObjects();

		 if ( vec == NULL )
		 {
			 MessageBox( NULL, "没有投影的物体" , "提示", MB_OK );
			 return;
		 }

		 vgKernel::SelectManager::getSingleton().clearSelection();

		 vgKernel::ShadowCastObjectVec::iterator iter = vec->begin();
		 vgKernel::ShadowCastObjectVec::iterator iter_end = vec->end();

		 for( ; iter != iter_end ; ++ iter )
		 {
			 vgKernel::Renderer* ren = 
				 dynamic_cast<vgKernel::Renderer*>( *iter );

			 if ( ren != NULL )
			 {
				 vgKernel::SelectManager::getSingleton().addSelection( ren , false );
			 }	
		 }

		 vgKernel::SelectManager::getSingleton().updateBox();
	 }

	 if ( SelectManager::getSingleton().getSelectedItems().empty() )
	 {
		 MessageBox(NULL, "请选中物体"  , "提示", MB_OK );
		 return;
	 }

	 // TODO: Add your command handler code here
	 vgSolar::SolarManager::getSingleton().setSolarAnalysis(
		 !SolarManager::getSingleton().getSolarAnalysisEnable() );

 }