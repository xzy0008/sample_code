


#ifndef __VGSOSOLARMANAGER_H__
#define __VGSOSOLARMANAGER_H__



#include <vgSolar/vgsoDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSingleton.h>
#include <vgKernel/vgkShadowCastObject.h>
#include <vgSolar/vgsoDateTimeAndLocation.h>
#include <vgSolar/vgsoSolarAnalysis.h>
#include <vgKernel/vgkRenderer.h>



namespace vgSolar {


	using namespace vgKernel;

	/**
		@date 	2009/03/30  19:20	
		@author  Leven
	
		@brief 	
	
		@see    
	*/
	class  VGSO_EXPORT SolarManager 
		: public vgKernel::Singleton<vgSolar::SolarManager>
	{
		friend class vgKernel::Singleton<vgSolar::SolarManager>;
	private:
		SolarManager()
			: Singleton<SolarManager>( VGK_SINGLETON_LEFE_SOLARMGR ) 
		{
			VGK_TRACE(_T("SolarManager created."));
			_lightDir = vgKernel::Vec3( 0.1f, -0.5f, 0.1f );
			_shadowEnabled = false;
			_useComputerDateAndTime = true;
			_analysis = NULL;
		}

	public:
		~SolarManager()
		{
			VGK_TRACE(_T("SolarManager destroyed."));
		}

	protected:

		virtual bool initialise()
		{
			return true;
		}

		virtual bool shutdown()
		{
			if ( _analysis != NULL )
			{
				delete _analysis;
				_analysis = NULL;
			}
			return true;
		}
	
	public:

		virtual void reset(){};

		void renderEnd();

		void uninitBeforeOpenGLDestroy();

		// 注意，当_shadowEnabled为False时，直接返回NULL
		vgKernel::Vec3* getLightDirection()
		{
			if ( _shadowEnabled )
			{
				return &_lightDir;
			}
			
			return NULL;
		}

		//void setLightDirection( const vgKernel::Vec3& light_dir )
		//{
		//	assert(0);

		//	// 在这里开始每个都setup一下。
		//	_lightDir = light_dir;
		//}

		bool getShadowEnabled() const
		{
			return _shadowEnabled;
		}

		// 注意，date_loc不能为NULL
		bool turnOnShadowEffectWithDate( 
			vgKernel::RendererQueue* renderer_queue ,
			vgSolar::DateTimeAndLocation* date_loc ,
			bool force_to_load );


		// 当new_light_dir为NULL时，使用默认的或者是读取的数据进行light照射
		bool turnOnShadowEffect( vgKernel::RendererQueue* renderer_queue ,
			vgKernel::Vec3* new_light_dir ,
			bool force_to_load );

		bool turnOffShadowEffect();


		bool changeDateTimeAndLoc( DateTimeAndLocation* loc );

		// 注意，new_light_dir需要normalise
		bool changeLightDirection( const vgKernel::Vec3& new_light_dir );

		// 注意，返回为false时，表示没有渲染物体
		vgKernel::ShadowCastObjectVec* getShadowCastObjects()
		{
			if ( _shadowedObjects.empty() )
			{
				return NULL;
			}

			return &_shadowedObjects;
		}

		//const bool getUseComputerDateAndTime() const { return _useComputerDateAndTime; }
		//bool getUseComputerDateAndTime() { return _useComputerDateAndTime; }
		//void setUseComputerDateAndTime( bool val ) { _useComputerDateAndTime = val; }

		//const vgSolar::DateTimeAndLocation getCurrentDateAndTime() const { return _currentDateAndTime; }
		vgSolar::DateTimeAndLocation getCurrentDateAndTime() { return _currentDateAndTime; }
		//void setCurrentDateAndTime( const vgSolar::DateTimeAndLocation& val ) { _currentDateAndTime = val; }


		bool setSolarAnalysis( bool enable_it );

		bool getSolarAnalysisEnable() const
		{
			return _analysis != NULL;
		}

		// 用于内部使用，渲染cast条形状阴影体
		void renderShadowCastObjects();

		void readProject();

		void saveProject();

	private:

		


	private:
	
		bool _shadowEnabled;
		vgKernel::Vec3 _lightDir;
	
		vgKernel::ShadowCastObjectVec _shadowedObjects;

		bool _useComputerDateAndTime;

		// 当前的时间，用于计算日照的光线
		vgSolar::DateTimeAndLocation _currentDateAndTime;

		SolarAnalysis* _analysis;
	};
	
	
}// end of namespace vgSolar
	


#endif // end of __VGSOSOLARMANAGER_H__