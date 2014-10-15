#pragma once

#include <vgkernel/vgkRenderer.h>
#include <vgKernel/vgkVec3.h>
#include <vgTrigger/vgtrCommandAbstract.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgTrigger/vgtrDefinition.h>

namespace vgTrigger{
	
	const vgKernel::RendererType RENDERER_TYPE_TRIGGER = 8000;

	/**
		@action		creation
		@date 		2009/09/18  9:43	
		@author  	ZhouSC
	
		@brief 		触发器
	
		@see    
		*/
	class  VGTRI_EXPORT Trigger : public vgKernel::Renderer, vgKernel::RendererObserver
	{
		VGK_RENDERER_IN_DECLARE( Trigger )

	public:
		// Trigger();
		Trigger(vgKernel::Renderer* pInnerRenderer = NULL);
		
		~Trigger();

	public:
		bool initOnCreate();
		void setRenderer(vgKernel::Renderer *pRenderer);

		bool regeditEvent(CommandPtr cmdPtr);
		bool unregeditEvent(CommandPtr cmdPtr);

		// 渲染循环中进行位置判断
		bool positionCheck(vgKernel::Vec3& position);

		// 触发进入离开
		bool fireOnEntrence();
		bool fireOnExit();

		// 捕捉单击事件触发.
		bool fireOnClicked();		
	
		// 用户从vg读取，或者用户手动变更底层的renderer
		bool setInnerRendererByName(string rendererName);
		bool setInnerRenderer(vgKernel::Renderer *pInnerRenderer);

		bool getTriggerEnable() { return m_enable; }
		void setTriggerEnable(bool enable) { m_enable = enable; } 

		bool getInnerVisible() { return m_innerVisible; }
		void setInnerVisible(bool visible) 
		{
			if (m_pRendererImpl == NULL)
			{
				return ;
			}

			m_pRendererImpl->setVisible(visible);
			m_innerVisible = visible; 
		}

		String* getInnerNamePtr();
		CommandPtrArray* getCommandArrayPtr() { return &m_eventArray;}
		CommandPtr getCommandByName(String name);
		
		bool deleteCommandByName(String name);

	public:
		// 继承自Renderer的属性

		//virtual String getTypeDesc() {return m_TypeDesc;}

		virtual String getName() { return m_triggerName; }
		
		virtual String* getNamePtr() { return &m_triggerName; }

		virtual void setName( const String& newname ) {  m_triggerName = newname; }

		virtual void setVisible( const bool& visible ){ _visible = visible; }

		virtual bool getVisible(){ return _visible; }

		virtual vgKernel::UniqueID getUniqueID() 
		{ 
			if (m_pRendererImpl == NULL)
			{
				return vgKernel::UniqueID();
			}

			return m_pRendererImpl->getUniqueID();
		}

		virtual void moveTo( const vgKernel::Vec3& newpos )
		{
			if (m_pRendererImpl == NULL)
			{
				return ;
			}

			m_pRendererImpl->moveTo(newpos);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}

		virtual void moveTo(const float& x, const float& y, const float& z) 
		{
			if (m_pRendererImpl == NULL)
			{
				return ;
			}

			m_pRendererImpl->moveTo(x, y, z);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}

		virtual void translate(const float& x, const float& y, const float& z)
		{
			if (m_pRendererImpl == NULL)
			{
				return ;
			}

			m_pRendererImpl->translate(x, y, z);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z)
		{
			if (m_pRendererImpl == NULL)
			{
				return ;
			}

			m_pRendererImpl->rotateSelf(angle, x, y, z);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}

		virtual void scale(const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z)
		{
			if (m_pRendererImpl == NULL)
			{
				return ;
			}

			m_pRendererImpl->scale(cx, cy, cz, x, y, z);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}

		virtual void rotate(const float& angle, 
			const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z)
		{
			if (m_pRendererImpl == NULL)
			{
				return ;
			}

			m_pRendererImpl->rotate(angle, cx, cy, cz, x, y, z);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}

		virtual vgKernel::Box getBoundingBox()
		{
			if (m_pRendererImpl == NULL)
			{
				return vgKernel::Box();
			}

			return m_pRendererImpl->getBoundingBox();
		}

		virtual long getNumOfTriangles()
		{
			if (m_pRendererImpl == NULL)
			{
				return 0;
			}

			return m_pRendererImpl->getNumOfTriangles();
		}

		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  )
		{
			if (m_pRendererImpl == NULL)
			{
				return 0;
			}

			return m_pRendererImpl->setDistanceToViewer(viewer_pos);

		}
		virtual void  render()
		{
			return ;
		}

		virtual bool  testPointInObject(const vgKernel::Vec3& point) { return false; }

		virtual bool  testIntersectWithTriangles( const vgKernel::Segment3& segment )
		{
			if (m_pRendererImpl == NULL)
			{
				return false;
			}

			return m_pRendererImpl->testIntersectWithTriangles(segment);
		}

		virtual std::pair<bool, float> testIntersectWithTriangles( const vgKernel::Ray& ray )
		{
			if (m_pRendererImpl == NULL)
			{
				return std::make_pair(false, 0.f);
			}

			return m_pRendererImpl->testIntersectWithTriangles(ray);
		}

	public:
		// 继承自Observer的属性
		virtual bool onDelete();
		virtual void onChanged(int eventId, void *param) {}

	private:
		String m_TypeDesc;
		string m_triggerName;
		vgKernel::Renderer* m_pRendererImpl;

		bool m_enable;
		bool m_innerVisible;

		bool m_lastStateIsOut;

		// std::map<TriggerEventEnum, CommandPtrArrayPtr> m_eventMap;
		CommandPtrArray	m_eventArray;
	};

	typedef		std::vector<Trigger*>				TriggerArray;
	typedef		std::vector<Trigger*>::iterator		TriggerArrayItr;

	VGK_RENDERER_OUT_DECLARE( Trigger )

}//namespace vgMod
