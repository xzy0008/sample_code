 
#include <vgStableHeaders.h>
#include <vgKernel/vgkInputSystem.h>

#define DIRECTINPUT_VERSION 0x0800
/// 初始化DirectX相关文件
#include <dinput.h>
#include <vgKernel/vgkRenderCommandManager.h>

#pragma message("  now input dinput8.lib...")
#pragma comment(lib,"dinput8.lib")

#pragma message("  now input dxguid.lib...")
#pragma  comment(lib, "dxguid.lib")


namespace vgKernel {

	bool InputSystem::initialise(const HINSTANCE& appInstance, const HWND& hwnd)
	{
		HRESULT		hr;
	
		// Initialise Device ------------------------------------------------
		if( FAILED( hr = DirectInput8Create( GetModuleHandle( NULL ), DIRECTINPUT_VERSION,
			IID_IDirectInput8, ( VOID** )&m_lpDI, NULL ) ) )
		{
			VGK_TRACE("Failed on Create Device");
			return false;
		}

		// Initialise KeyBoard ----------------------------------------------
		ASSERT( this->m_mouse == NULL );
		// Retrieve a pointer to an IDirectInputDevice8 interface 
		if( FAILED( hr = m_lpDI->CreateDevice( GUID_SysKeyboard, &m_keyboard, NULL ) ) )
		{	
			VGK_TRACE("Failed on Get Keyboard");
			return false;
		}

		if( FAILED( hr = m_keyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
		{
			VGK_TRACE("Failed on Set DataFormat");
			return false;
		}

		if ( FAILED(m_keyboard->SetCooperativeLevel(hwnd, 
			DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)) )
		{
			VGK_TRACE("Failed on SetCooperativeLevel");
			return false;
		}

		memset(m_KeyLastStateBuffer, 0, sizeof(m_KeyLastStateBuffer));
		memset(m_KeyStateBuffer, 0, sizeof(m_KeyStateBuffer));

		VGK_TRACE("KeyBoard initialised successfully \n");
		
		// Initialise Mouse ---------------------------------------------------
// 		ASSERT( this->m_mouse == NULL );
// 
// 		if (FAILED(m_lpDI->CreateDevice(GUID_SysMouse, &m_mouse, NULL)))
// 		{
// 			return false;
// 		}
// 
// 		if (FAILED(m_mouse->SetDataFormat(&c_dfDIMouse)))
// 		{
// 			return false;
// 		}
// 
// 		if (FAILED(m_mouse->SetCooperativeLevel(hwnd,  DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
// 		{
// 			return false;
// 		}
// 
// 		ZeroMemory( &m_mouseState, sizeof( m_mouseState ) );
// 		ZeroMemory( &m_mouseLastState, sizeof( m_mouseLastState ) );

		return true;
	}
	
	bool InputSystem::UpdateInput()
	{
		if (! m_enable)
			return false;

		if ( m_keyboard == NULL )
		{
			return false;

		}
		// KeyBoard --------------------------------------------------------
		if (FAILED(m_keyboard->GetDeviceState(sizeof(m_KeyStateBuffer), (LPVOID)m_KeyStateBuffer)))
		{
			if (FAILED(m_keyboard->Acquire()))
			{
				return false;
			}
			if (FAILED(m_keyboard->GetDeviceState(sizeof(m_KeyStateBuffer), (LPVOID)m_KeyStateBuffer)))
			{
				//assert(0);
				return false;
			}

			//return false;
		}

 		for (int i=0; i<256; i++)
 		{
 			if ((m_KeyStateBuffer[i] & 0x80))
 			{
 				////TRACE("Pressed %d handleList Size is %d\n", eventHanleList.size(), i);
  				for (int j=0; j<eventHanleList.size(); j++)
  				{
  					if (eventHanleList[j]->GetHandleStatus() & statusFlag)
  					{
  						eventHanleList[j]->OnKeyDown(i);
  					}
  				}
 			}
   			else if ((m_KeyLastStateBuffer[i] & 0x80))
   			{
				//VGK_TRACE_SHORT("On char \n");
				for (int j=0; j<eventHanleList.size(); j++)
				{
					if (eventHanleList[j]->GetHandleStatus() & statusFlag)
					{
						eventHanleList[j]->OnChar(i);
					}
				}
			}
			m_KeyLastStateBuffer[i] = m_KeyStateBuffer[i];
 		}

		// memcpy(m_KeyLastStateBuffer, m_KeyStateBuffer, 256);
		
		//// mouse -----------------------------------------------------------
		//
		//CPoint mousePoint;
		//int i;

		//if (FAILED(m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
		//{
		//	if (FAILED(m_mouse->Acquire()))
		//	{
		//		return false;
		//	}
		//	if (FAILED(m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
		//	{
		//		return false;
		//	}
		//}	
		//
		//GetCursorPos(&mousePoint);
		//HWND inHwnd = WindowFromPoint(mousePoint);
		//
		//if (m_clientHwnd && m_clientHwnd == inHwnd)
		//{
		//	ScreenToClient(m_clientHwnd, &mousePoint);
		//}
		//else
		//{
		//	return false;
		//}


		//if ((m_mouseState.lX != 0 || m_mouseState.lY !=0))
		//{
		//	for (i=0; i<eventHanleList.size(); i++)
		//	{
		//		if (eventHanleList[i]->GetHandleStatus() & statusFlag)
		//		{
		//			eventHanleList[i]->OnMouseMove(mousePoint);
		//		}
		//	}
		//}
		//
		//if ((m_mouseState.rgbButtons[0] & 0x80) && !(m_mouseLastState.rgbButtons[0] & 0x80))
		//{
		//	clickTime = GetTickCount();
		//
		//	if (clickTime - lastTime <800 && lastClickUpPoint == mousePoint && m_mouseState.lX == 0 && m_mouseState.lY == 0)
		//	{
		//		////TRACE("Double Click \n");
		//		for (i=0; i<eventHanleList.size(); i++)
		//		{
		//			if (eventHanleList[i]->GetHandleStatus() & statusFlag)
		//			{
		//				eventHanleList[i]->OnLButtonDbClick(mousePoint);
		//			}
		//		}
		//	}
		//	else
		//	{
		//		////TRACE("LButton Down \n");
		//		for (i=0; i<eventHanleList.size(); i++)
		//		{
		//			if (eventHanleList[i]->GetHandleStatus() & statusFlag)
		//			{
		//				eventHanleList[i]->OnLButtonDown(mousePoint);
		//			}
		//		}
		//	}

		//	m_mouseLastState.rgbButtons[0] = m_mouseState.rgbButtons[0];
		//	lastTime = clickTime;
		//}
		//else if (!(m_mouseState.rgbButtons[0] & 0x80) && (m_mouseLastState.rgbButtons[0] & 0x80))
		//{
		//	////TRACE("LButton Up & click \n");
		//	m_mouseLastState.rgbButtons[0] = m_mouseState.rgbButtons[0];
		//	lastClickUpPoint = mousePoint;

		//	for (i=0; i<eventHanleList.size(); i++)
		//	{
		//		if (eventHanleList[i]->GetHandleStatus() & statusFlag)
		//		{
		//			eventHanleList[i]->OnLButtonUp(mousePoint);
		//		}
		//	}
		//}

		//if ((m_mouseState.rgbButtons[1] & 0x80) && (m_mouseState.rgbButtons[1] & 0x01))
		//{
		//	//TRACE("RButton Down \n");
		//}
		//else if (m_mouseLastState.rgbButtons[1] & 0x80)
		//{
		//	//TRACE("RButton Up & click \n");
		//}

		//memcpy(&m_mouseLastState, &m_mouseState, sizeof(m_mouseState));

		return true;
	}

	bool InputSystem::registerHandle(InputHandler *handle)
	{
		using namespace std;
		vector<InputHandler*>::iterator iter = eventHanleList.begin();
		vector<InputHandler*>::iterator end = eventHanleList.end();

		while (iter != end)
		{
			if (*iter == handle)
			{
				return false;
			}
			iter ++;
		}

		eventHanleList.push_back(handle);
		return true;
	}

	bool InputSystem::removeHandle(InputHandler *handle)
	{
		using namespace std;
		vector<InputHandler*>::iterator iter = eventHanleList.begin();
		vector<InputHandler*>::iterator end = eventHanleList.end();

		while (iter != end)
		{
			if (*iter == handle)
			{
				eventHanleList.erase(iter);
				return true;
			}
			iter ++;
		}

		return false;
	}

	void InputSystem::OnMouseMove(UINT nFlags, CPoint position)
	{
		for (int i=0; i<eventHanleList.size(); i++)
		{
			if (eventHanleList[i]->GetHandleStatus() & statusFlag)
			{
				eventHanleList[i]->OnMouseMove(nFlags, position);
			}
		}
	}

	void InputSystem::OnLButtonDown(UINT nFlags, CPoint position)
	{
		for (int i=0; i<eventHanleList.size(); i++)
		{
			if (eventHanleList[i]->GetHandleStatus() & statusFlag)
			{
				eventHanleList[i]->OnLButtonDown(nFlags, position);
			}
		}
	}

	void InputSystem::OnLButtonUp(UINT nFlags, CPoint position)
	{
		for (int i=0; i<eventHanleList.size(); i++)
		{
			if (eventHanleList[i]->GetHandleStatus() & statusFlag)
			{
				eventHanleList[i]->OnLButtonUp(nFlags, position);
			}
		}
	}

	void InputSystem::OnLButtonDbClick(UINT nFlags, CPoint position)
	{
		for (int i=0; i<eventHanleList.size(); i++)
		{
			if (eventHanleList[i]->GetHandleStatus() & statusFlag)
			{
				eventHanleList[i]->OnLButtonDbClick(nFlags, position);
			}
		}
	}

	void InputSystem::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		for (int i=0; i<eventHanleList.size(); i++)
		{
			if (eventHanleList[i]->GetHandleStatus() & statusFlag)
			{
				eventHanleList[i]->OnMouseWheel(nFlags, zDelta, pt);
			}
		}
	}

	void InputSystem::OnRButtonDown(UINT nFlags, CPoint position)
	{
		for (int i=0; i<eventHanleList.size(); i++)
		{
			if (eventHanleList[i]->GetHandleStatus() & statusFlag)
			{
				eventHanleList[i]->OnRBottonDown(nFlags, position);
			}
		}
	}

	void InputSystem::OnRButtonUp(UINT nFlags, CPoint position)
	{
		for (int i=0; i<eventHanleList.size(); i++)
		{
			if (eventHanleList[i]->GetHandleStatus() & statusFlag)
			{
				eventHanleList[i]->OnRBottonUp(nFlags, position);
			}
		}
	}

	bool InputSystem::shutdown()
	{

		if ( m_lpDI == NULL )
		{
			return true;
		}
		if (FAILED(m_lpDI->Release()))
		{
			assert(0);
			return false;
		}
		return true;
	}

	InputSystem::InputSystem() : Singleton<InputSystem>(VGK_SINGLETON_LEFE_INPUTSYSTEM)
	{
		m_mouse = NULL;
		m_keyboard = NULL;
		m_clientHwnd = NULL;

		setDefaultStatus();


		m_lpDI = NULL;
		m_mouse = NULL;

		m_enable = true;

		m_pUpdateCmd = new UpdateInputCmd;

		vgKernel::RenderCommandFacade::AddCommand(m_pUpdateCmd);

		VGK_TRACE("InputSystem Created \n");
	}

	InputSystem::~InputSystem()
	{
		vgKernel::RenderCommandFacade::RemoveCommand(m_pUpdateCmd);
		m_pUpdateCmd = NULL;

		TRACE("Destory Input System Command. \n");

		VGK_TRACE("InputSystem Destoryed \n");

	}
}// end of namespace vgKernel
