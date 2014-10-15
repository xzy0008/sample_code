


#ifndef __VGKOPERATOR_H__
#define __VGKOPERATOR_H__

#include <vgKernel/vgkRenderer.h>

namespace vgKernel{


	class Operation
	{
	public:
		virtual void Redo ( Renderer *_render ){};
		virtual void Undo( Renderer *_render ){};

	};
	
	class vgkEditTrans : public Operation
	{
	public:
		vgkEditTrans( Vec3 _offset )
		{
			m_TransVec3 = _offset;
		}
	private:

		Vec3 m_TransVec3;
	public:
		virtual void Redo ( Renderer *_render )
		{
			_render->translate( m_TransVec3.x, m_TransVec3.y, m_TransVec3.z );
		}

		virtual void Undo( Renderer *_render )
		{
			_render->translate( (-1)*m_TransVec3.x, (-1)*m_TransVec3.y, (-1)*m_TransVec3.z );
		}
	};
	class vgkEditScale : public Operation
	{
	private:
		Vec3 m_ScaleVec3;
		Vec3 m_center;
	public:
		vgkEditScale( Vec3 _center, Vec3  _ScaleVec3)
		{
			m_ScaleVec3 = _ScaleVec3;

			m_center = _center;
		}
	public:
		virtual void Redo ( Renderer *_render )
		{
			_render->scale(m_center.x, m_center.y, m_center.z, 1-m_ScaleVec3.x, 1-m_ScaleVec3.y, 1-m_ScaleVec3.z);
		}

		virtual void Undo( Renderer *_render )
		{
			if ((1-m_ScaleVec3.x) &&
				(1-m_ScaleVec3.y)&&(1-m_ScaleVec3.z))
			{
				_render->scale(m_center.x, m_center.y, m_center.z, 1.0/(1-m_ScaleVec3.x), 1.0/(1-m_ScaleVec3.y), 1.0/(1-m_ScaleVec3.z));
			}
		}
	};	
	class vgkEditRotate : public Operation
	{
	private:
		Vec3 m_RotVec3;
		Vec3 m_center;
	public:
		vgkEditRotate( Vec3 _center, Vec3  _RotVec3)
		{
			m_RotVec3 = _RotVec3;

			m_center = _center;
		} 
	public:
		virtual void Redo ( Renderer *_render )
		{
			_render->rotate(m_RotVec3.x * 90, m_center.x ,m_center.y, m_center.z, 1, 0, 0);
			_render->rotate(m_RotVec3.y * 90, m_center.x ,m_center.y, m_center.z, 0, 1, 0);
			_render->rotate(m_RotVec3.z * 90, m_center.x ,m_center.y, m_center.z, 0, 0, 1);
		}

		virtual void Undo( Renderer *_render )
		{
			_render->rotate(m_RotVec3.x * -90, m_center.x ,m_center.y, m_center.z, 1, 0, 0);
			_render->rotate(m_RotVec3.y * -90, m_center.x ,m_center.y, m_center.z, 0, 1, 0);
			_render->rotate(m_RotVec3.z * -90, m_center.x ,m_center.y, m_center.z, 0, 0, 1);

		}
	};



//////////////////////////////////////////////////////////////////////////

	class OperationObserver : public vgKernel::RendererObserver
	{
	public:
		OperationObserver( vgKernel::Renderer* renderer )
		{
			m_Renderer = renderer;

			if ( renderer != NULL )
			{
				renderer->registerObserver( this );
			}
		}

		virtual ~OperationObserver(void)
		{
			delete m_Renderer;

			m_Renderer = NULL;
		}

		virtual bool onDelete()
		{
			m_Renderer = NULL;
			return true;
		}

		void onChanged(int eventId, void* param)
		{

		}

		vgKernel::Renderer* GetRender(){ return m_Renderer; }

	protected:

		vgKernel::Renderer* m_Renderer;
	};


	typedef std::deque<OperationObserver*> RendererOperatorObserverQueue;


	class vgkOperator
	{

	public:
		void execute();


		void unexecute();

	public:
		vgkOperator( RendererOperatorObserverQueue* renderqueue, Operation* operation )
		{
			_renderqueue = renderqueue;

			_operation = operation;
		}
		~vgkOperator()
		{
			_renderqueue->clear();

			delete _renderqueue;

			_renderqueue = NULL;

			delete _operation;

			_operation = NULL;
		}

	private:
		RendererOperatorObserverQueue *_renderqueue;

		Operation *_operation;

	};
}


#endif // end of __VGOPERATOR_H__