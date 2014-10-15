
#include <vgStableHeaders.h>
#include <vgCam/vgcaCamManager.h>

#include <vgKernel/vgkRendererManager.h>

#include <vgKernel/vgkSystemUtility.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgCam/vgcaContinuousRecordAction.h>

#include <vgPhys/vgphPhysManager.h>
#include <vgCam/vgcaRenderCommand.h>
#include <vgKernel/vgkRenderCommandManager.h>

#include <vgKernel/vgkPropertyManager.h>
#include <vgKernel/vgkVec2.h>

#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)



namespace vgCam { 

#undef PI

	using namespace std;
	
	//float CollisionPacket::s_veryCloseDistance = 0.005f;
	
	//----------------------------------------------------------------
	CamManager::CamManager() 
		: Singleton<CamManager>( VGK_SINGLETON_LEFE_CAMMGR )
	{
		_topViewCam = new ViewCam();
		InitTopViewCam();

		_perspectViewCam = new ViewCam();
		InitPerspectViewCam();

		_keyPressedMask = 0;
		_isControlling = false;
		_mouseMoveAndWheelCounter = 0;

		// Initalize all our member varibles.
		m_MaxPitchRate			= 0.0f;
		m_MaxHeadingRate		= 0.0f;
		
		m_HeadingDegrees		= 0.0f;
		m_PitchDegrees			= 0.0f;
		
		m_MaxForwardVelocity	= 0.0f;
		m_ForwardVelocity		= 1.0f;

		m_PitchVelocity			= 0.1f;
		m_TurningVelocity		= 0.5f/*0.1f*/;

		m_upAndDownMultiply = 1.0f;

		m_ChannelNum=0;
		
		m_near= m_nearBase = 0.6f;
		m_far=1000000/*10000000*/; 
		m_fov=45/*60*/;
		m_aspectratio=1.33f;

		m_pVCR=&_singleVCR;
		b3Channel= false;
		IsServer= false;

		_canBeMoved = true;

		MouseX = 0;
		MouseY = 0;		
		_centerX = 0;
		_centerY = 0;

		// 响应CAMERA模式下的输入事件
		statusFlag = VG_INPUTMODE_CAMERA;
		// 向InputSystem注册，InputSystem会转发相应消息给CamManager
		vgKernel::InputSystem::getSingleton().registerHandle(this);
		setDefaultParameters();

		m_bMouseMode = false;

		m_uiIndexViewCam	= 0;
		m_ratio = 7/8;
		m_hOffset = 0;
		m_vOffset = 0;

#if 0
		m_colPacket.eRadius.x = .25;
		m_colPacket.eRadius.y = .5;
		m_colPacket.eRadius.z = .25;

		m_colPacket.continueVelocity = Vec3(0,0,0);

		m_enableCollisionDetection = false;

		VGK_TRACE(_T("CamManager created."));

		using namespace vgKernel;

		//------------------------------------------
		// 目前只支持mod物体!
		//------------------------------------------

		_renderersCollision.insert( std::make_pair( 
			vgCore::RENDERER_TYPE_MODOJBECT , RendererQueue() ));

#endif

		m_nAviRecord = 0;
		m_frameBufferBindedFlag = 0;
		m_pFrameBuffer = NULL;
		m_paviFile = NULL;


		m_pAviProgessDlg = NULL;
		
		m_bIsDrawMirror=false;
		m_WaterHeight=0.0;

		m_aviBegin = new RenderAviBegin;
		m_aviEnd = new RenderAviEnd;
		m_camBegin = new RenderBegin;

		vgKernel::RenderCommandFacade::AddCommand( m_aviBegin );
		vgKernel::RenderCommandFacade::AddCommand( m_aviEnd );
		vgKernel::RenderCommandFacade::AddCommand( m_camBegin) ;

		if (! vgKernel::PropertyManager::getSingleton().registerPropertyObserver("PROP_SCREEN_SIZE", this))
		{
			vgKernel::Property<vgKernel::Vec2> *screenSizeProp
				= new vgKernel::Property<vgKernel::Vec2>("PROP_SCREEN_SIZE");

			screenSizeProp->setValue(vgKernel::Vec2(1,1));
			vgKernel::PropertyManager::getSingleton().addProperty(screenSizeProp);
			vgKernel::PropertyManager::getSingleton().registerPropertyObserver("PROP_SCREEN_SIZE", this);	
		}
	}

	CamManager::~CamManager()
	{
		vgKernel::RenderCommandFacade::RemoveCommand( m_aviBegin );
		vgKernel::RenderCommandFacade::RemoveCommand( m_aviEnd );
		vgKernel::RenderCommandFacade::RemoveCommand( m_camBegin) ;

		m_camBegin = NULL;
		m_aviEnd = NULL;
		m_aviBegin = NULL;

		if ( _topViewCam != NULL )
		{
			delete _topViewCam;
			_topViewCam = NULL;
		}

		if (_perspectViewCam != NULL)
		{
			delete _perspectViewCam;
			_perspectViewCam = NULL;
		}

		TRACE("Destory Cam Render Command. \n");
		clear();

		VGK_TRACE(_T("CamManager destroyed."));
	}

	bool CamManager::initialise()
	{
		return true;
	}

	void CamManager::onEvent(unsigned int eventId, void *param)
	{
		if (eventId == UnTypedProperty::PROPERTY_ON_CHANGE)
		{
			vgKernel::Vec2 *pSize = (vgKernel::Vec2*)param;
			assert(pSize != NULL);

			setAspectRatioByWindowSize(pSize->x, pSize->y);
		}
	}

	//----------------------------------------------------------------
	bool CamManager::shutdown()
	{
		return true;
	}

	void CamManager::fly(void)
	{//2008-11-3 9:03:43 设置相机参数并更新界面 lss begin：
		setModelViewMatrix();
		_currentFrustum.updateCameraBox();

		if ( _canBeMoved == false )
		{
			return;
		}

		if (m_bMouseMode == true )
		{
			mouseFunction();
		}

		//add by ZhouZY 2009-11-4 16:14
		//当平台失去焦点后不再响应键盘,当其它视图（节点，属性，输出）处于当前激活状态下不再响应键盘
		if( !vgKernel::InputSystem::getSingleton().GetEnable() ) 
		{
			return;
		}

		/**
			VK_UP --> 1
			VK_DOWN	--> 1 << 1
			VK_PRIOR	--> 1 << 2
			VK_NEXT	 --> 1 << 3
			VK_LEFT		--> 1 << 4
			VK_RIGHT	--> 1 << 5
			VK_HOME	--> 1 << 6
			VK_END		--> 1 << 7
			VK_OEM_PLUS		--> 1 << 8
			VK_OEM_MINUS		--> 1 << 9
			W		--> 1 << 10
			S		--> 1 << 11
			A		--> 1 << 12
			D		--> 1 << 13
			*/

#define VGCAM_MASK_VK_UP	1
#define VGCAM_MASK_VK_DOWN	(1 << 1)
#define VGCAM_MASK_VK_PRIOR	(1 << 2)
#define VGCAM_MASK_VK_NEXT	(1 << 3)
#define VGCAM_MASK_VK_LEFT	(1 << 4)
#define VGCAM_MASK_VK_RIGHT	(1 << 5)
#define VGCAM_MASK_VK_HOME	(1 << 6)
#define VGCAM_MASK_VK_END	(1 << 7)
#define VGCAM_MASK_VK_OEM_PLUS	(1 << 8)
#define VGCAM_MASK_VK_OEM_MINUS	(1 << 9)
#define VGCAM_MASK_W	(1 << 10)
#define VGCAM_MASK_S	(1 << 11)
#define VGCAM_MASK_A	(1 << 12)
#define VGCAM_MASK_D	(1 << 13)
#define VGCAM_MASK_VK_ESCAPE (1 << 14)


		if( KEY_DOWN(VK_UP) )
		{
			_keyPressedMask |= VGCAM_MASK_VK_UP;
			moveForward();
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}
		else
		{
			_keyPressedMask &= ~VGCAM_MASK_VK_UP;
		}

		if(KEY_DOWN(VK_DOWN))
		{
			_keyPressedMask |= VGCAM_MASK_VK_DOWN;
			moveBackward();
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_VK_DOWN;
		}

		//Add by kinghj ESC退出右键快捷视图模式
		if( KEY_DOWN(VK_ESCAPE) )
		{
			_keyPressedMask |= VGCAM_MASK_VK_ESCAPE;
			m_bMouseMode = false;
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}
		else
		{
			_keyPressedMask &= ~VGCAM_MASK_VK_ESCAPE;
		}

		if( KEY_DOWN(VK_PRIOR) )
		{
			_keyPressedMask |= VGCAM_MASK_VK_PRIOR;
			//ChangePitch(-0.2f);
			changePitch(-m_PitchVelocity);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_VK_PRIOR;
		}

		if(KEY_DOWN(VK_NEXT ))
		{
			_keyPressedMask |= VGCAM_MASK_VK_NEXT;
			//ChangePitch(0.2f);
			changePitch(m_PitchVelocity);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_VK_NEXT;
		}

		if(KEY_DOWN(VK_LEFT))
		{
			_keyPressedMask |= VGCAM_MASK_VK_LEFT;
			//ChangeHeading(-10.0f);
			changeHeading(-m_TurningVelocity);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_VK_LEFT;
		}

		if(KEY_DOWN(VK_RIGHT))
		{
			_keyPressedMask |= VGCAM_MASK_VK_RIGHT;
			//ChangeHeading(10.0f);
			changeHeading(m_TurningVelocity);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_VK_RIGHT;
		}

		if ( KEY_DOWN( VK_HOME ) == true )
		{
			_keyPressedMask |= VGCAM_MASK_VK_HOME;
			moveUp();
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_VK_HOME;
		}

		if ( KEY_DOWN( VK_END ) == true )
		{
			_keyPressedMask |= VGCAM_MASK_VK_END;
			moveDown();
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_VK_END;
		}

		if(KEY_DOWN(VK_OEM_PLUS) == TRUE)
		{
			_keyPressedMask |= VGCAM_MASK_VK_OEM_PLUS;
			changeVelocity(0.1f);	
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_VK_OEM_PLUS;
		}

		if(KEY_DOWN(VK_OEM_MINUS) == TRUE)
		{
			_keyPressedMask |= VGCAM_MASK_VK_OEM_MINUS;
			changeVelocity(-0.1f);
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_VK_OEM_MINUS;
		}

		if ( KEY_DOWN(0x0057/*W*/) )
		{
			_keyPressedMask |= VGCAM_MASK_W;
			moveForwardTowardsDirection();
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_W;
		}

		if ( KEY_DOWN(0x0053/*S*/) )
		{
			_keyPressedMask |= VGCAM_MASK_S;
			moveBackwardTowardsDirection();
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_S;
		}

		if(KEY_DOWN(65/*A*/) == TRUE)
		{
			_keyPressedMask |= VGCAM_MASK_A;
			moveLeft();
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		}
		else
		{
			_keyPressedMask &= ~ VGCAM_MASK_A;
		}

		if(KEY_DOWN(68/*D*/) == TRUE )
		{
			_keyPressedMask |= VGCAM_MASK_D;
			moveRight();
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
			//2008-11-3 9:03:43 设置相机参数并更新界面 lss end
		}
		else
		{
			_keyPressedMask &=~ VGCAM_MASK_D;
		}

		if ( _mouseMoveAndWheelCounter > 0 )
		{
			--_mouseMoveAndWheelCounter;
		}

		_isControlling = (_keyPressedMask != 0) ||
			(m_bMouseMode == true) ||
			( _mouseMoveAndWheelCounter != 0 );
	}

	void CamManager::OnKeyDown(int keyCode)
	{

		return;


		if(keyCode == vgKernel::InputCode::UP)
		{
			moveForward();
		}

		if(keyCode == vgKernel::InputCode::DOWN)
		{
			moveBackward();
		}

		if( keyCode == vgKernel::InputCode::PG_UP )
		{
			changePitch(-0.2f * m_PitchVelocity);
		}

		if(keyCode == vgKernel::InputCode::PG_DOWN)
		{
			changePitch(0.2f * m_PitchVelocity);
		}

		if(keyCode == vgKernel::InputCode::LEFT)
		{
			changeHeading(-1.0f * m_TurningVelocity);
		}

		if(keyCode == vgKernel::InputCode::RIGHT)
		{
			changeHeading(1.0f * m_TurningVelocity);
		}

		if (
			(keyCode == vgKernel::InputCode::HOME)
			||(keyCode == vgKernel::InputCode::Q)
			)
		{
			moveUp();
		}

		if (
			(keyCode == vgKernel::InputCode::END)
			||(keyCode == vgKernel::InputCode::E)
			)	
		{
			moveDown();
		}

		if(keyCode == vgKernel::InputCode::ADD)
		{
			changeVelocity(0.1f);
		}

		if(keyCode == vgKernel::InputCode::SUBTRACT)
		{
			changeVelocity(-0.1f);
		}

		if (keyCode == vgKernel::InputCode::W)
		{
			moveForwardTowardsDirection();
		}

		if (keyCode == vgKernel::InputCode::S)
		{
			moveBackwardTowardsDirection();
		}

		if(keyCode == vgKernel::InputCode::A)
		{
			moveLeft();
		}

		if(keyCode == vgKernel::InputCode::D)
		{
			moveRight();
		}	

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}

	void CamManager::OnMouseMove(UINT nFlags, CPoint position)
	{
		static CPoint s_lastPostion;
		static bool first = true;

		if ( !first && (nFlags & MK_CONTROL) && (nFlags & MK_MBUTTON) )
		{
			float offsetx = position.x - s_lastPostion.x; 
			float offsety = position.y - s_lastPostion.y;

			_mouseMoveAndWheelCounter = 10;

			if ( offsetx != 0 )
			{
				changeHeading(offsetx);
			}

			if ( offsety != 0)
			{
				changePitch(offsety);
			}
		}
		else if (!first && (nFlags & MK_RBUTTON))
		{
			float offsetx = position.x - s_lastPostion.x; 
			float offsety = position.y - s_lastPostion.y;

			_mouseMoveAndWheelCounter = 10;

			if ( offsetx != 0 )
			{
				changeHeading(offsetx);
			}

			if ( offsety != 0)
			{
				changePitch(offsety);
			}
		}
		else if (!first && (nFlags & MK_MBUTTON))
		{
			float offsetx = position.x - s_lastPostion.x; 
			float offsety = position.y - s_lastPostion.y;

			_mouseMoveAndWheelCounter = 10;

			if (s_lastPostion.x != position.x)
			{
				moveLeft2(offsetx);
			}

			if (s_lastPostion.y != position.y)
			{
				moveHigher(offsety);
			}

			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}

		first = false;
		s_lastPostion = position;
	}

	void CamManager::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
	{
		if ( _canBeMoved == false )
		{
			return;
		}

		_mouseMoveAndWheelCounter = 10;


		if (zDelta > 0)
		{
			moveForwardTowardsDirection2();
		}
		else
		{
			moveBackwardTowardsDirection2();
		}
		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}

	void CamManager::OnRBottonDown(UINT nFlags, CPoint position)
	{
		//m_bMouseMode = true;

		//ShowCursor(false);
	}

	void CamManager::OnRBottonUp(UINT nFlags, CPoint position)
	{
		//m_bMouseMode = false;
		//ShowCursor(true);
	}

	void CamManager::changePitch(GLfloat degrees)
	{
		if(fabs(degrees) < fabs(m_MaxPitchRate))
		{
			// Our pitch is less than the max pitch rate that we 
			// defined so lets increment it.
			m_PitchDegrees += degrees;
		}
		else
		{
			// Our pitch is greater than the max pitch rate that
			// we defined so we can only increment our pitch by the 
			// maximum allowed value.
			if(degrees < 0)
			{
				// We are pitching down so decrement
				m_PitchDegrees -= m_MaxPitchRate;
			}
			else
			{
				// We are pitching up so increment
				m_PitchDegrees += m_MaxPitchRate;
			}
		}

		// We don't want our pitch to run away from us. Although it
		// really doesn't matter I prefer to have my pitch degrees
		// within the range of -360.0f to 360.0f
		if(m_PitchDegrees > 360.0f)
		{
			m_PitchDegrees -= 360.0f;
		}
		else if(m_PitchDegrees < -360.0f)
		{
			m_PitchDegrees += 360.0f;
		}
	}

	void CamManager::changeHeading(GLfloat degrees)
	{
		if(fabs(degrees) < fabs(m_MaxHeadingRate))
		{
			// Our Heading is less than the max heading rate that we 
			// defined so lets increment it but first we must check
			// to see if we are inverted so that our heading will not
			// become inverted.
			if(m_PitchDegrees > 90 && m_PitchDegrees < 270 || (m_PitchDegrees < -90 && m_PitchDegrees > -270))
			{
				m_HeadingDegrees -= degrees;
			}
			else
			{
				m_HeadingDegrees += degrees;
			}
		}
		else
		{
			// Our heading is greater than the max heading rate that
			// we defined so we can only increment our heading by the 
			// maximum allowed value.
			if(degrees < 0)
			{
				// Check to see if we are upside down.
				if((m_PitchDegrees > 90 && m_PitchDegrees < 270) || (m_PitchDegrees < -90 && m_PitchDegrees > -270))
				{
					// Ok we would normally decrement here but since we are upside
					// down then we need to increment our heading
					m_HeadingDegrees += m_MaxHeadingRate;
				}
				else
				{
					// We are not upside down so decrement as usual
					m_HeadingDegrees -= m_MaxHeadingRate;
				}
			}
			else
			{
				// Check to see if we are upside down.
				if(m_PitchDegrees > 90 && m_PitchDegrees < 270 || (m_PitchDegrees < -90 && m_PitchDegrees > -270))
				{
					// Ok we would normally increment here but since we are upside
					// down then we need to decrement our heading.
					m_HeadingDegrees -= m_MaxHeadingRate;
				}
				else
				{
					// We are not upside down so increment as usual.
					m_HeadingDegrees += m_MaxHeadingRate;
				}
			}
		}

		// We don't want our heading to run away from us either. Although it
		// really doesn't matter I prefer to have my heading degrees
		// within the range of -360.0f to 360.0f
		if(m_HeadingDegrees > 360.0f)
		{
			m_HeadingDegrees -= 360.0f;
		}
		else if(m_HeadingDegrees < -360.0f)
		{
			m_HeadingDegrees += 360.0f;
		}
	}

	void CamManager::changeVelocity(GLfloat vel)
	{
		//降低旋转加速度，精简加速度控制	2008-11-3 9:33:45 update by lss

		if (  vel<0 && m_ForwardVelocity > fabs(vel)*2.0f 
			||vel>0 && m_ForwardVelocity < m_MaxForwardVelocity-fabs(vel) )
		{//避免速度降至0或增至15
			m_ForwardVelocity	+= vel;
			m_TurningVelocity	+= vel*0.1 ;
			m_PitchVelocity		+= vel*0.1;
		}

		if(m_TurningVelocity < fabs(vel) )
		{
			m_TurningVelocity = fabs(vel);
		}
		if(m_PitchVelocity < fabs(vel) )
		{
			m_PitchVelocity = fabs(vel);
		}
	}

	void CamManager::moveLeft()
	{
		//float theta = ( m_HeadingDegrees )/180.0f * PI;

		////float dddd = sin((90 )/180.0f * PI);

		//float xlen = -distance * sin( theta );
		//float zlen = -distance * cos( theta );

		//m_Position.z -= xlen;
		//m_Position.x += zlen;

// 		m_Position.x += m_DirectionVector.z * 5;
// 		m_Position.z -= m_DirectionVector.x * 5;

		vgKernel::Vec3 dir;

		// 场景处于顶视图下满足if条件
		if ( vgKernel::Math::Abs( m_DirectionVector.z ) < 0.000001 &&
			vgKernel::Math::Abs( m_DirectionVector.x ) < 0.000001 )
		{
			dir.x += -1.0 * m_ForwardVelocity * 5;
			dir.z -= 0.0;
		}
		else
		{
			dir.x += m_DirectionVector.z * 5;
			dir.z -= m_DirectionVector.x * 5;
		}

		m_Position = vgPhys::PhysMananger::getSingleton().collisionWithCamera(m_Position, dir, getCurrentFrustum()->getCameraBox());


	}

	void CamManager::moveRight()
	{
// 		m_Position.x -= m_DirectionVector.z * 5;
// 		m_Position.z += m_DirectionVector.x * 5;
	
		vgKernel::Vec3 dir;

		// 场景处于顶视图下满足if条件
		if ( vgKernel::Math::Abs( m_DirectionVector.z ) < 0.000001 &&
			vgKernel::Math::Abs( m_DirectionVector.x ) < 0.000001 )
		{
			dir.x -= -1.0 * m_ForwardVelocity * 5;
			dir.z += 0.0;
		}
		else
		{
			dir.x -= m_DirectionVector.z * 5;
			dir.z += m_DirectionVector.x * 5;
		}

		m_Position = vgPhys::PhysMananger::getSingleton().collisionWithCamera(m_Position, dir, getCurrentFrustum()->getCameraBox());

	}

	void CamManager::moveForward()
	{
		vgKernel::Vec3 dir = m_DirectionVector;
		dir.y = 0;

		m_Position = vgPhys::PhysMananger::getSingleton().collisionWithCamera(m_Position, dir, getCurrentFrustum()->getCameraBox());
	}

	void CamManager::moveBackward()
	{
		vgKernel::Vec3 dir = - m_DirectionVector;
		dir.y = 0;
		m_Position = vgPhys::PhysMananger::getSingleton().collisionWithCamera(m_Position, dir, getCurrentFrustum()->getCameraBox());

	}

	void CamManager::moveInDirection()
	{
		// Increment our position by the vector
		m_Position.x += m_DirectionVector.x;
		m_Position.y += m_DirectionVector.y;
		m_Position.z += m_DirectionVector.z;
	}

	void CamManager::setDefaultParameters()
	{
		// Now set up our max values for the camera
		m_MaxForwardVelocity = 15.0f;
		m_MaxPitchRate = 5.0f;
		m_MaxHeadingRate = 5.0f;
		m_PitchDegrees = 0.0f;
		m_HeadingDegrees = 0.0f;
	}
	//----------------------------------------------------------------
	void CamManager::setModelViewMatrix()
	{
		// Make the Quaternions that will represent our rotations
		if (m_bIsDrawMirror)
		{//livenson add 2010.01.06 for mirror effect of water
			_tmpQuaternionPitch.createFromAxisAngle(1.0f, 0.0f, 0.0f, -m_PitchDegrees);
		}
		else
			_tmpQuaternionPitch.createFromAxisAngle(1.0f, 0.0f, 0.0f, m_PitchDegrees);
		_tmpQuaternionHeading.createFromAxisAngle(0.0f, 1.0f, 0.0f, m_HeadingDegrees);

		// Combine the pitch and heading rotations and store the results in q
		_combinedQuaternion = _tmpQuaternionPitch * _tmpQuaternionHeading;

		_combinedQuaternion.createMatrix(_tmpMatrix);

		// Let OpenGL set our new prespective on the world!
		glMultMatrixf(_tmpMatrix);

		// Create a matrix from the pitch Quaternion and get the j vector 
		// for our direction.
		_tmpQuaternionPitch.createMatrix(_tmpMatrix);
		m_DirectionVector.y = _tmpMatrix[9];


		// Combine the heading and pitch rotations and make a matrix to get
		// the i and j vectors for our direction.
		_combinedQuaternion = _tmpQuaternionHeading * _tmpQuaternionPitch;
		_combinedQuaternion.createMatrix(_tmpMatrix);
		m_DirectionVector.x = _tmpMatrix[8];
		m_DirectionVector.z = -_tmpMatrix[10];


		//m_DirectionVector.x = _tmpMatrix[8];
		//m_DirectionVector.y = _tmpMatrix[9];
		//m_DirectionVector.z = -_tmpMatrix[10];

		// Scale the direction by our speed.
		m_DirectionVector *= m_ForwardVelocity;

		// Translate to our new position.
		if (m_bIsDrawMirror)
		{//livenson add 2010.01.06 for mirror effect of water
			glTranslatef(-m_Position.x, m_Position.y, -m_Position.z);
		}
		else
			glTranslatef(-m_Position.x, -m_Position.y, -m_Position.z);
	}
	void CamManager::setModelViewMatrix(const vgKernel::Vec3 postion,const float PDegrees,const float HDegrees )
	{

		setCurrentPosition( postion );
		setHeadingDegrees( HDegrees );
		setPitchDegrees( PDegrees );

		setModelViewMatrix();
		return;

#if 0
		// Make the Quaternions that will represent our rotations
		_tmpQuaternionPitch.createFromAxisAngle(1.0f, 0.0f, 0.0f, PDegrees);
		_tmpQuaternionHeading.createFromAxisAngle(0.0f, 1.0f, 0.0f, HDegrees);

		// Combine the pitch and heading rotations and store the results in q
		_combinedQuaternion = _tmpQuaternionPitch * _tmpQuaternionHeading;
		_combinedQuaternion.createMatrix(_tmpMatrix);

		// Let OpenGL set our new prespective on the world!
		glMultMatrixf(_tmpMatrix);


		//////////////////////////////////////////////////////////////////////////
		_tmpQuaternionPitch.createMatrix(_tmpMatrix);
		m_DirectionVector.y = _tmpMatrix[9];


		// Combine the heading and pitch rotations and make a matrix to get
		// the i and j vectors for our direction.
		_combinedQuaternion = _tmpQuaternionHeading * _tmpQuaternionPitch;
		_combinedQuaternion.createMatrix(_tmpMatrix);
		m_DirectionVector.x = _tmpMatrix[8];
		m_DirectionVector.z = -_tmpMatrix[10];


		//m_DirectionVector.x = _tmpMatrix[8];
		//m_DirectionVector.y = _tmpMatrix[9];
		//m_DirectionVector.z = -_tmpMatrix[10];

		// Scale the direction by our speed.
		m_DirectionVector *= m_ForwardVelocity;
		//////////////////////////////////////////////////////////////////////////


		// Translate to our new position.
		glTranslatef(-postion.x, -postion.y, -postion.z);

		//------------------------------------------
		// 设置
		//------------------------------------------
		setCurrentPosition( postion );
		setHeadingDegrees( HDegrees );
		setPitchDegrees( PDegrees );

#endif
	}
	void CamManager::setModelViewMatrix( const vgKernel::Vec3 &pos, Quat&qt )
	{

		return setModelViewMatrix( pos , qt.getPitchDegrees() , 
			qt.getPitchDegrees() );


		//qt.createMatrix(_tmpMatrix);

		//// Let OpenGL set our new prespective on the world!
		//glMultMatrixf(_tmpMatrix);
		////glMultTransposeMatrixf(_tmpMatrix);


		//// Create a matrix from the pitch Quaternion and get the j vector 
		//// for our direction.
		////		_tmpQuaternionPitch.createMatrix(_tmpMatrix);
		//m_DirectionVector.y = _tmpMatrix[9];
		//m_DirectionVector.x = _tmpMatrix[8];
		//m_DirectionVector.z = -_tmpMatrix[10];



		//m_DirectionVector *= m_ForwardVelocity;

		//m_Position=pos;

		//// Translate to our new position.
		//glTranslatef(-m_Position.x, -m_Position.y, -m_Position.z);
	}
	//----------------------------------------------------------------
	void CamManager::mouseFunction()
	{
		GLfloat DeltaMouse;
		POINT pt;

		GetCursorPos(&pt);

		MouseX = pt.x;
		MouseY = pt.y;

		if(MouseX < _centerX)
		{
			DeltaMouse = GLfloat(_centerX - MouseX);

			changeHeading(-0.2f * DeltaMouse);

		}
		else if(MouseX > _centerX)
		{
			DeltaMouse = GLfloat(MouseX - _centerX);

			changeHeading(0.2f * DeltaMouse);
		}

		if(MouseY < _centerY)
		{
			DeltaMouse = GLfloat(_centerY - MouseY);

			changePitch(-0.2f * DeltaMouse);
		}
		else if(MouseY > _centerY)
		{
			DeltaMouse = GLfloat(MouseY - _centerY);

			changePitch(0.2f * DeltaMouse);
		}

		MouseX = _centerX;
		MouseY = _centerY;

		SetCursorPos(_centerX, _centerY);
	}
	
	void CamManager::moveHigher(float offset)
	{
		Vec3 left(-m_DirectionVector.z, 0, m_DirectionVector.x);
		Vec3 upVec = left.crossProduct(m_DirectionVector);

		upVec.normalise();

		m_Position += upVec * offset;
	}

	void CamManager::moveLower(float offset)
	{
		Vec3 left(-m_DirectionVector.z, 0, m_DirectionVector.x);
		Vec3 upVec = left.crossProduct(m_DirectionVector);

		upVec.normalise();

		m_Position -= upVec * offset;
	}

	void CamManager::moveLeft2(float offset)
	{
		// 场景处于顶视图下满足if条件
		if ( vgKernel::Math::Abs( m_DirectionVector.z ) < 0.000001 &&
			vgKernel::Math::Abs( m_DirectionVector.x ) < 0.000001 )
		{
			m_Position.x += -1.0 * m_ForwardVelocity * offset;
			m_Position.z -= 0.0;
		}
		else
		{
			m_Position.x += m_DirectionVector.z * offset;
			m_Position.z -= m_DirectionVector.x * offset;
		}
	}

	void CamManager::moveRight2(float offset)
	{
		// 场景处于顶视图下满足if条件
		if ( vgKernel::Math::Abs( m_DirectionVector.z ) < 0.000001 &&
			vgKernel::Math::Abs( m_DirectionVector.x ) < 0.000001 )
		{
			m_Position.x -= -1.0 * m_ForwardVelocity * offset;
			m_Position.z += 0.0;
		}
		else
		{
			m_Position.x -= m_DirectionVector.z  * offset;
			m_Position.z += m_DirectionVector.x  * offset;
		}
	}

	void CamManager::moveForwardTowardsDirection2()
	{
		// m_Position += m_DirectionVector * 150;
		m_Position += m_DirectionVector * m_ForwardVelocity * 20;
	}

	void CamManager::moveBackwardTowardsDirection2()
	{
		// m_Position -= m_DirectionVector * 150;
		m_Position -= m_DirectionVector * m_ForwardVelocity * 20;
	}

	//----------------------------------------------------------------
	void CamManager::moveUp()
	{
		vgKernel::Vec3 dir;

		dir.x = 0;
		dir.y = m_ForwardVelocity*m_upAndDownMultiply;
		dir.z = 0;

		m_Position = vgPhys::PhysMananger::getSingleton().collisionWithCamera(m_Position, dir, getCurrentFrustum()->getCameraBox());
	}

	//----------------------------------------------------------------
	void CamManager::moveDown()
	{	
		vgKernel::Vec3 dir;

		dir.x = 0;
		dir.y = -(m_ForwardVelocity*m_upAndDownMultiply);
		dir.z = 0;

		m_Position = vgPhys::PhysMananger::getSingleton().collisionWithCamera(m_Position, dir, getCurrentFrustum()->getCameraBox());
	}

	//----------------------------------------------------------------
	void CamManager::moveForwardTowardsDirection()
	{
		//m_Position += m_DirectionVector * 15;
		vgKernel::Vec3 dir = m_DirectionVector * 15;

		m_Position = vgPhys::PhysMananger::getSingleton().collisionWithCamera(m_Position, dir, getCurrentFrustum()->getCameraBox());

	}
	//----------------------------------------------------------------
	void CamManager::moveBackwardTowardsDirection()
	{
		//m_Position -= m_DirectionVector * 15;
		vgKernel::Vec3 dir = -m_DirectionVector * 15;

		m_Position = vgPhys::PhysMananger::getSingleton().collisionWithCamera(m_Position, dir, getCurrentFrustum()->getCameraBox());

	}

	void CamManager::clientfly( const bool& useMouseMode )
	{
		setModelViewMatrix();

	}

	void CamManager::serverfly( const bool& useMouseMode )
	{
		if ( useMouseMode == true )
		{
			mouseFunction();
		}
	}

	ViewCam* CamManager::saveCurrentCameraView()//新增加一个相机视点
	{
		ViewCam* newone = new ViewCam();

		std::ostringstream o;
		o << "ViewCam" << m_uiIndexViewCam++/*_viewCams.size()*/;

		newone->setName( o.str() );

		newone->cloneCurrentCameraView();

		_viewCams.push_back( ViewCamPtr(newone));

		return newone;

	}
	void CamManager::immediateToViewCam(ViewCam *cam)
	{
		setCurrentPosition(cam->getPosition());
		setPitchDegrees(cam->getPitchDegrees());
		setHeadingDegrees(cam->getHeadingDegrees());
		setForwardVelocity(cam->getForwardVelocity());
	}
	//----------------------------------------------------------------
	bool CamManager::onDeleteRenderer( vgKernel::Renderer *render )
	{
		using namespace std;
		if (
				(render->getType() != RENDERER_TYPE_VIEWCAMERA)
			&&	(render->getType() != RENDERER_TYPE_CAMRECORD) 
			)
		{
			return false;
		}

		std::vector<ViewCamPtr>::iterator iter_ViewCam	= _viewCams.begin();
		std::vector<ViewCamPtr>::iterator iterEnd_ViewCam= _viewCams.end();
		std::vector<CameraRecordPtr>::iterator iter_Record = _VCRvector.begin();
		std::vector<CameraRecordPtr>::iterator iterEnd_Record = _VCRvector.end();
		switch (render->getType())
		{
		case RENDERER_TYPE_VIEWCAMERA:
			for( ; iter_ViewCam != iterEnd_ViewCam; iter_ViewCam++ )
			{
				if ((*iter_ViewCam).getPointer() == render)
				{
					_viewCams.erase( iter_ViewCam );
					break;
				}
			}
			break;

		case RENDERER_TYPE_CAMRECORD:
			setDefaultCamRecordPtr();
			for( ; iter_Record != iterEnd_Record; iter_Record++ )
			{
				if ((*iter_Record).getPointer() == render) 
				{
					_VCRvector.erase( iter_Record );
					break;
				}
			}
			break;

		default:
			break;
		}//switch

		return true;
	}
	//----------------------------------------------------------------
	void CamManager::initialFrustum()
	{
		if (m_window_width==0)
			m_aspectratio=0.75;
		else
			m_aspectratio=m_window_height/m_window_width;

		float tana=tan(m_fov/2* vgKernel::Math::PI/180);
		m_up=m_near*tana;
		m_down=-m_near*tana;
		if (m_aspectratio!=0)
		{
			m_left=m_down/m_aspectratio;
			m_right=-m_left;
		}

	}
	void CamManager::setAspectRatioByWindowSize(int cx, int cy)
	{
		m_window_width = cx;
		m_window_height = cy;
	}
	void CamManager::setFov(float fovpar)//适用于对称视景体,tan是角度还是弧度，有待于再验
	{
		m_fov=fovpar;
		//this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}

	void CamManager::setNear(float nearpar)
	{
		m_near=nearpar;
		//this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
	void CamManager::setFar(float farpar)
	{
		m_far=farpar;
		//this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
	}
	void CamManager::setViewport(float leftpar,float rightpar,float downpar,float uppar)
	{
		m_left=leftpar;
		m_right=rightpar;
		m_down=downpar;
		m_up=uppar;		
	}

	void CamManager::setupViewFrustum()//设定视景体，包含多通道
	{
		glMatrixMode(GL_PROJECTION);		
		glLoadIdentity();
		//默认给出一套对称的视景体参数，然后其余通道在此基础上修正即可
		initialFrustum();

		if(m_ChannelNum==0)//考虑到扩展性，完全可以用这个通道，让用户自定义通道特性，让用户自己去算，然后setviewport吧
		{	
			//glFrustum(-2,2,-1.5,1.5,3,1000);
		}
		else if(m_ChannelNum==1)//必须保证只能执行一次
		{	
			float offset;
			//offset=(m_right-m_left)*7/8;
			offset = (m_right - m_left) * m_ratio;	//@FengYK	2009/10/28	21:41
			setViewport(m_left+offset,m_right+offset,m_down,m_up);
		}
		else if(m_ChannelNum==-1)
		{
			float offset;
			//offset=(m_right-m_left)*7/8;
			offset = (m_right - m_left) * m_ratio;
			setViewport(m_left-offset,m_right-offset,m_down,m_up);
		}
		else if (m_ChannelNum == 11)
		{
			float offset;
			offset = (m_right - m_left) * m_ratio;
			setViewport(m_left+offset, m_right+offset, m_down, m_up);
		}
		else if (m_ChannelNum == -11)
		{
			float offset;
			offset = (m_right - m_left) * m_ratio;
			setViewport(m_left-offset, m_right-offset, m_down, m_up);
		}
		else if (m_ChannelNum == 10)
		{

		}

		//glFrustum(m_left,m_right,m_down,m_up,m_near,m_far);//无论如何都执行该通道！
		glFrustum(m_left+m_hOffset, m_right+m_hOffset, m_down, m_up, m_near+m_vOffset, m_far+m_vOffset);//@FengYK  2009/10/28 21:44

		::glMatrixMode(GL_MODELVIEW);
		::glLoadIdentity();
		glTranslatef(0,-m_WaterHeight,0);
		if(m_bIsDrawMirror)
			glScalef(1,-1,1);
	}
	void CamManager::setupCamera()
	{

		CameraRecord* cam = getCurrentCameraRecord();

		if (b3Channel==false)//非多机模式
		{
			// 录制相机AVI视频状态
			if (m_nAviRecord > 0)
			{
				getCameraRecordByName(m_currentAviCameraName)->playVCRproc();

				m_nAviRecord --;

				return ;
			}

			if ( (cam->getPlayingFlag() == true ) )
			{
				cam->playVCRproc();
			}
			else
			{
				fly(/*false*/);

				if (getCurrentCameraRecord()->b_record==true)
				{
					getCurrentCameraRecord()->recordVCRproc();
				}
			}

			//if(getCurrentCameraRecord()->b_play==false)//非播放动画状态
			//{
			//	fly(/*false*/);

			//	if (getCurrentCameraRecord()->b_record==true)
			//	{
			//		getCurrentCameraRecord()->recordVCRproc();
			//	}

			//}
			//else//播放动画状态
			//{
			//	getCurrentCameraRecord()->playVCRproc();
			//}
		}
		else//多机同步模式
		{

			//assert(0);
			// server
			if (m_ChannelNum == 0)
			{
				if ( (cam->getPlayingFlag() == true ) )
				{
					cam->playVCRproc();
				}
				else
				{
					fly();
				}
			}
			else
			{
				// client,原本在此设置相机的位置信息，现改为在收到消息的时候设置相机的位置等信息

				setModelViewMatrix();
				//setModelViewMatrix(package.position, package.pitchDegree, package.headDegree);
			}

#if 0

			if (getSingleton().IsServer)
			{
				//在服务器端，虚拟的相机接收键盘的对其更新,通过发送给客户机，让其异步更新		
				serverfly(false);//里面的gluLookAt已经屏蔽了,就是不对画面产生影响

			}
			//每台参与三通道的机器肯定包含客户机器				
			{	
				//-----------------------------------------
				//begin
				//-----------------------------------------
				//////////////////////////////////////////////////////////////////////////
				//客户端的接收并修改相机参数
				//客户端的缓冲区更新相机信息


				//vgCore::CameraNode &cam=scenetree->GetCurrentCamera();
				int tempindex=ChannelClient::getInstance()->index;
				int readindex;
				if (tempindex==0)
					readindex=31;
				else
					readindex=tempindex-1;

				ViewerControl nn=ChannelClient::getInstance()->pbuffer[readindex];

				//客户端不响应键盘的处理方式
				setModelViewMatrix(nn.pos,nn.pitchdegrees,nn.headdegrees);	

				//-----------------------------------------
				//end
				//-----------------------------------------

			}
#endif
		}
	}

	//----------------------------------------------------------------
	bool CamManager::dumpInfoToStream( vgKernel::StreamWriterPtr pwriter )
	{
		pwriter->write( &m_Position, sizeof(Vec3) );

		pwriter->write( &m_HeadingDegrees, sizeof(float) );
		pwriter->write( &m_PitchDegrees, sizeof(float) );	

		pwriter->write( &m_ForwardVelocity, sizeof(float) );
		pwriter->write( &m_PitchVelocity, sizeof(float) );
		pwriter->write( &m_TurningVelocity, sizeof(float) );	
		pwriter->write( & m_upAndDownMultiply , sizeof( float ) );

		return true;
	}
	//----------------------------------------------------------------
	bool CamManager::readInfoFromStream( vgKernel::StreamReaderPtr preader )
	{
		preader->read( &m_Position, sizeof(Vec3) );

		preader->read( &m_HeadingDegrees, sizeof(float) );
		preader->read( &m_PitchDegrees, sizeof(float) );	

		preader->read( &m_ForwardVelocity, sizeof(float) );
		preader->read( &m_PitchVelocity, sizeof(float) );
		preader->read( &m_TurningVelocity, sizeof(float) );	

		preader->read( &m_upAndDownMultiply , sizeof( float ) );

		this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);

		return true;
	}
	//----------------------------------------------------------------
	void CamManager::copyRecordfile( const String& attachDataPath)
	{
		using namespace std;
		String desFilePath, srcFilePath, fileName;
		
		std::vector<CameraRecordPtr>::iterator vcrItr = _VCRvector.begin();
		std::vector<CameraRecordPtr>::iterator vcrItrEnd = _VCRvector.end();
		for( ; vcrItr != vcrItrEnd; ++vcrItr )
		{			
			srcFilePath = (*vcrItr)->getVcrFilePath();
			fileName = vgKernel::StringUtility::getFilenameFromAbsolutePath(srcFilePath);

			if ( srcFilePath != "" )
			{
				desFilePath = attachDataPath + fileName;

				bool save_ret = vgKernel::SystemUtility::copyFile( srcFilePath, desFilePath );

				assert( save_ret == true );
			}

		}
		return;
	}
	//------------------------------------------------------------------
	void CamManager::renderVcr()
	{
		using namespace std;
		std::vector<CameraRecordPtr>::iterator vcrItr = _VCRvector.begin();
		std::vector<CameraRecordPtr>::iterator vcrItrEnd = _VCRvector.end();
		for( ; vcrItr != vcrItrEnd; ++vcrItr )
		{	
		
			if((*vcrItr)->getVisible()==true)
				(*vcrItr)->render();
		}
	}
	void CamManager::setPosByCurVcrSpecificFrame(int nowframenum)
	{
		//int nowframenum=vgCam::CamManager::getSingleton().getCurrentCameraRecord()->uiFrame;
		vgCam::CameraRecord* nowVCR=vgCam::CamManager::getSingleton().getCurrentCameraRecord();
		setCurrentPosition(
			m_pVCR->frameptr[nowframenum].pos+m_pVCR->offset_vcr);//  [11/20/2008 zhu]

		setPitchDegrees( 
			m_pVCR->frameptr[nowframenum].getQuat().getPitchDegrees() );
		setHeadingDegrees(
			m_pVCR->frameptr[nowframenum].getQuat().getHeadDegrees() );

		return;
		
		//vgCam::CamManager::getSingleton().setModelViewMatrix(
		//	last.pos+offset_vcr,last.qt.getPitchDegrees() ,
		//	last.qt.getHeadDegrees() );

#if 0
		vgKernel::Quat qt0=m_pVCR->frameptr[nowframenum].qt,Aq;
		Aq.createFromAxisRadian(qt0.m_x,qt0.m_y,qt0.m_z,qt0.m_w);
		Aq.normalize();
		vgKernel::Vec3 from(1,0,0),from1(0,0,-1);
		vgKernel::Vec3 to,to1;
		vgKernel::Mat4 mat;
		Aq.createMatrix(mat._m);

		to=mat*from;
		to1=mat*from1;

		float sethead;
		if (to.v[0]>0)
		{
			sethead=180/PI*asin(to.v[2]/sqrt(to.v[0]*to.v[0]+to.v[2]*to.v[2]));
		}
		else
		{
			sethead=180-180/PI*asin(to.v[2]/sqrt(to.v[0]*to.v[0]+to.v[2]*to.v[2]));
		}

		float setpitch=180/PI*asin(-to1.v[1]);

		setHeadingDegrees(sethead);
		setPitchDegrees(setpitch);

#endif
	}

#if 0
	void CamManager::collideAndSlide(const Vec3& position, const Vec3& vel
		/*, const Vec3& gravity*/)
	{
		m_colPacket.foundCollision = false;

		// Do collision detection:
		m_colPacket.R3Position = position;
		m_colPacket.R3Velocity = vel;
		// calculate position and velocity in eSpace
		Vec3 eSpacePosition = m_colPacket.R3Position/
			m_colPacket.eRadius;
		Vec3 eSpaceVelocity = m_colPacket.R3Velocity/
			m_colPacket.eRadius;
		// Iterate until we have our final position.
		m_collisionRecursionDepth = 0;

		Vec3 finalPosition = collideWithWorld(eSpacePosition,
			eSpaceVelocity);

		// Convert final result back to R3:
		finalPosition = finalPosition*m_colPacket.eRadius;
		// 
		// 		// Move the entity (application specific function)
		// 		MoveTo(finalPosition);

		m_colPacket.newPositon = finalPosition;
	}

	Vec3 CamManager::collideWithWorld(const Vec3& pos,
		const Vec3& vel)
	{
		TRACE(" %d recursion \n", m_collisionRecursionDepth);

		// All hard-coded distances in this function is
		// scaled to fit the setting above..
		float unitScale = 1;
		float veryCloseDistance = 0.005f * unitScale;
		// do we need to worry?
		if (m_collisionRecursionDepth>3)
			return pos;
		// Ok, we need to worry:
		m_colPacket.velocity = vel;
		m_colPacket.normalizedVelocity = vel;
		m_colPacket.normalizedVelocity.normalise();
		m_colPacket.basePoint = pos;
		m_colPacket.foundCollision = false;
		m_colPacket.continueVelocity = Vec3(0,0,0);

		// Check for collision (calls the collision routines)
		// Application specific!!
		collisionDetection(m_colPacket);
		// If no collision we just move along the velocity
		if (m_colPacket.foundCollision == false) {
			return pos + vel;
		}


		vgKernel::Vec3 destinationPoint = m_colPacket.basePoint + m_colPacket.velocity;
		vgKernel::Vec3 newBasePoint = m_colPacket.basePoint;

		if (m_colPacket.nearestDistance>=CollisionPacket::s_veryCloseDistance + 1)
		{
			Vec3 V = vel;
			V.setLength(m_colPacket.nearestDistance-CollisionPacket::s_veryCloseDistance-1);
			newBasePoint = m_colPacket.basePoint + V;
			// Adjust polygon intersection point (so sliding
			// plane will be unaffected by the fact that we
			// move slightly less than collision tells us)
			V.normalise();
			m_colPacket.intersectionPoint -= (CollisionPacket::s_veryCloseDistance) * V;
		}

		// Determine the sliding plane
		Vec3 slidePlaneOrigin = m_colPacket.intersectionPoint;
		Vec3 slidePlaneNormal = newBasePoint-m_colPacket.intersectionPoint;
		slidePlaneNormal.normalise();
		vgKernel::Plane slidingPlane(slidePlaneNormal, slidePlaneOrigin);
		// Again, sorry about formatting.. but look carefully ;)
		Vec3 newDestinationPoint = destinationPoint - slidingPlane.getDistance(destinationPoint) * slidePlaneNormal;
		// Generate the slide vector, which will become our new
		// velocity vector for the next iteration
		Vec3 newVelocityVector = newDestinationPoint - m_colPacket.intersectionPoint;
		// Recurse:
		// dont recurse if the new velocity is very small
		if (newVelocityVector.length() < CollisionPacket::s_veryCloseDistance) {
			TRACE(" Len < closeDistance return \n ");
			return newBasePoint;
		}
		m_collisionRecursionDepth++;

		// m_colPacket.continueVelocity = newVelocityVector * m_colPacket.eRadius;

		return collideWithWorld(newBasePoint,newVelocityVector);
	}

	void CamManager::collisionDetection(CollisionPacket& collistionPacket)
	{

		m_colPacket.nearestDistance = FLT_MAX;


		vgKernel::RendererPackage::iterator iter = _renderersCollision.begin();
		vgKernel::RendererPackage::iterator iter_end = _renderersCollision.end();

		for ( ; iter != iter_end ; ++iter )
		{
			assert (iter->first == vgCore::RENDERER_TYPE_MODOJBECT);

			vgKernel::RendererQueue* pQueue = &iter->second;

			vgKernel::RendererQueue::iterator qiter = pQueue->begin();
			vgKernel::RendererQueue::iterator qiter_end = pQueue->end();

			for ( ; qiter != qiter_end ; ++qiter )
			{			
				vgCore::ObjectNode* curleaf = (vgCore::ObjectNode*)(*qiter);
				if (curleaf == NULL)
					continue;

				for (int i =0 ; i < curleaf->m_numOfFaces; i++)
				{
					int k0 = curleaf->pShadowFaces[i].vertIndex[0];
					int k1 = curleaf->pShadowFaces[i].vertIndex[1];
					int k2 = curleaf->pShadowFaces[i].vertIndex[2];
					int ni = curleaf->pShadowFaces[i].normal;

					vgKernel::Vec3 p1, p2, p3, normal;

					p1.x = curleaf->pVert[k0].x / m_colPacket.eRadius.x;
					p1.y = curleaf->pVert[k0].y / m_colPacket.eRadius.y;
					p1.z = curleaf->pVert[k0].z / m_colPacket.eRadius.z;

					p2.x = curleaf->pVert[k1].x / m_colPacket.eRadius.x;
					p2.y = curleaf->pVert[k1].y / m_colPacket.eRadius.y;
					p2.z = curleaf->pVert[k1].z / m_colPacket.eRadius.z;

					p3.x = curleaf->pVert[k2].x / m_colPacket.eRadius.x;
					p3.y = curleaf->pVert[k2].y / m_colPacket.eRadius.y;
					p3.z = curleaf->pVert[k2].z / m_colPacket.eRadius.z;

					Vec3 edge1 = p1 - p2;
					Vec3 edge2 = p1 - p3;

					Vec3 newNormal = edge1.crossProduct(edge2);
					if (newNormal.dotProduct(normal) < 0)
					{
						newNormal = -newNormal;
					}
					//   					
					normal = newNormal;
					normal.normalise();

					checkTriangle(&m_colPacket, p1, p2, p3, normal);
				}
			}
		}
	}

	// Assumes: p1,p2 and p3 are given in ellisoid space:
	void CamManager::checkTriangle(CollisionPacket* colPackage,
		const vgKernel::Vec3& p1,const vgKernel::Vec3& p2,const vgKernel::Vec3& p3, const vgKernel::Vec3& normal)
	{
		// Make the plane containing this triangle.
		vgKernel::Plane trianglePlane(normal, p1);
		//  
		float dir = 1.0;

		// Is triangle front-facing to the velocity vector?
		// We only check front-facing triangles
		// (your choice of course)
		if (trianglePlane.isFrontFacingTo(
			colPackage->normalizedVelocity)) {
				// Get interval of plane intersection:
				double t0, t1;
				bool embeddedInPlane = false;
				// Calculate the signed distance from sphere
				// position to triangle plane
				double signedDistToTrianglePlane =
					trianglePlane.getDistance(colPackage->basePoint);

				// cache this as we’re going to use it a few times below:
				float normalDotVelocity =
					trianglePlane._normal.dotProduct(colPackage->velocity);
				// if sphere is travelling parrallel to the plane:
				if (normalDotVelocity == 0.0f) {
					if (fabs(signedDistToTrianglePlane) >= 1.0f) {
						// Sphere is not embedded in plane.
						// No collision possible:
						return;
					}
					else {
						// sphere is embedded in plane.
						// It intersects in the whole range [0..1]
						embeddedInPlane = true;
						t0 = 0.0;
						t1 = 1.0;
					}

				}
				else {
					// N dot D is not 0. Calculate intersection interval:
					t0=(-dir-signedDistToTrianglePlane)/normalDotVelocity;
					t1=( dir-signedDistToTrianglePlane)/normalDotVelocity;

					// Swap so t0 < t1
					if (t0 > t1) {
						double temp = t1;
						t1 = t0;
						t0 = temp;
					}
					// Check that at least one result is within range:
					if (t0 > 1.0f || t1 < 0.0f) {
						// Both t values are outside values [0,1]
						// No collision possible:
						return;
					}
					// Clamp to [0,1]
					if (t0 < 0.0) t0 = 0.0;
					if (t1 < 0.0) t1 = 0.0;
					if (t0 > 1.0) t0 = 1.0;
					if (t1 > 1.0) t1 = 1.0;
				}
				// OK, at this point we have two time values t0 and t1
				// between which the swept sphere intersects with the
				// triangle plane. If any collision is to occur it must
				// happen within this interval.
				vgKernel::Vec3 collisionPoint;
				bool foundCollison = false;
				float t = 1.0;
				// First we check for the easy case - collision inside
				// the triangle. If this happens it must be at time t0
				// as this is when the sphere rests on the front side
				// of the triangle plane. Note, this can only happen if
				// the sphere is not embedded in the triangle plane.
				if (!embeddedInPlane) {
					vgKernel::Vec3 planeIntersectionPoint =
						(colPackage->basePoint-trianglePlane._normal)
						+ t0*colPackage->velocity;
					if (vgKernel::Math::checkPointInTriangle(planeIntersectionPoint,
						p1,p2,p3))
					{
						foundCollison = true;
						t = t0;
						collisionPoint = planeIntersectionPoint;
					}
				}
				// if we haven’t found a collision already we’ll have to
				// sweep sphere against points and edges of the triangle.
				// Note: A collision inside the triangle (the check above)
				// will always happen before a vertex or edge collision!
				// This is why we can skip the swept test if the above
				// gives a collision!
				if (foundCollison == false) {
					// some commonly used terms:
					vgKernel::Vec3 velocity = colPackage->velocity;
					vgKernel::Vec3 base = colPackage->basePoint;
					float velocitySquaredLength = velocity.squaredLength();
					float a,b,c; // Params for equation
					float newT;
					// For each vertex or edge a quadratic equation have to
					// be solved. We parameterize this equation as
					// a*t^2 + b*t + c = 0 and below we calculate the
					// parameters a,b and c for each test.
					// Check against points:
					a = velocitySquaredLength;
					// P1
					b = 2.0*(velocity.dotProduct(base-p1));
					c = (p1-base).squaredLength() - 1.0;
					if (vgKernel::Math::getLowestRoot(a,b,c, t, &newT)) {
						t = newT;
						foundCollison = true;
						collisionPoint = p1;
					}
					// P2
					b = 2.0*(velocity.dotProduct(base-p2));
					c = (p2-base).squaredLength() - 1.0;
					if (vgKernel::Math::getLowestRoot(a,b,c, t, &newT)) {
						t = newT;
						foundCollison = true;
						collisionPoint = p2;
					}
					// P3
					b = 2.0*(velocity.dotProduct(base-p3));
					c = (p3-base).squaredLength() - 1.0;
					if (vgKernel::Math::getLowestRoot(a,b,c, t, &newT)) {
						t = newT;
						foundCollison = true;
						collisionPoint = p3;
					}// Check agains edges:
					// p1 -> p2:
					vgKernel::Vec3 edge = p2-p1;
					vgKernel::Vec3 baseToVertex = p1 - base;
					float edgeSquaredLength = edge.squaredLength();
					float edgeDotVelocity = edge.dotProduct(velocity);
					float edgeDotBaseToVertex = edge.dotProduct(baseToVertex);
					// Calculate parameters for equation
					a = edgeSquaredLength*-velocitySquaredLength +
						edgeDotVelocity*edgeDotVelocity;
					b = edgeSquaredLength*(2*velocity.dotProduct(baseToVertex))-
						2.0*edgeDotVelocity*edgeDotBaseToVertex;
					c = edgeSquaredLength*(1-baseToVertex.squaredLength())+
						edgeDotBaseToVertex*edgeDotBaseToVertex;
					// Does the swept sphere collide against infinite edge?
					if (vgKernel::Math::getLowestRoot(a,b,c, t, &newT)) {
						// Check if intersection is within line segment:
						float f=(edgeDotVelocity*newT-edgeDotBaseToVertex)/
							edgeSquaredLength;
						if (f >= 0.0 && f <= 1.0) {
							// intersection took place within segment.
							t = newT;
							foundCollison = true;
							collisionPoint = p1 + f*edge;
						}
					}
					// p2 -> p3:
					edge = p3-p2;
					baseToVertex = p2 - base;
					edgeSquaredLength = edge.squaredLength();
					edgeDotVelocity = edge.dotProduct(velocity);
					edgeDotBaseToVertex = edge.dotProduct(baseToVertex);
					a = edgeSquaredLength*-velocitySquaredLength +
						edgeDotVelocity*edgeDotVelocity;
					b = edgeSquaredLength*(2*velocity.dotProduct(baseToVertex))-
						2.0*edgeDotVelocity*edgeDotBaseToVertex;
					c = edgeSquaredLength*(1-baseToVertex.squaredLength())+
						edgeDotBaseToVertex*edgeDotBaseToVertex;
					if (vgKernel::Math::getLowestRoot(a,b,c, t, &newT)) {
						float f=(edgeDotVelocity*newT-edgeDotBaseToVertex)/
							edgeSquaredLength;
						if (f >= 0.0 && f <= 1.0) {
							t = newT;
							foundCollison = true;
							collisionPoint = p2 + f*edge;
						}
					}
					// p3 -> p1:
					edge = p1-p3;
					baseToVertex = p3 - base;

					edgeSquaredLength = edge.squaredLength();
					edgeDotVelocity = edge.dotProduct(velocity);

					edgeDotBaseToVertex = edge.dotProduct(baseToVertex);
					a = edgeSquaredLength*-velocitySquaredLength +
						edgeDotVelocity*edgeDotVelocity;
					b = edgeSquaredLength*(2*velocity.dotProduct(baseToVertex))-
						2.0*edgeDotVelocity*edgeDotBaseToVertex;
					c = edgeSquaredLength*(1-baseToVertex.squaredLength())+
						edgeDotBaseToVertex*edgeDotBaseToVertex;
					if (vgKernel::Math::getLowestRoot(a,b,c, t, &newT)) {
						float f=(edgeDotVelocity*newT-edgeDotBaseToVertex)/
							edgeSquaredLength;
						if (f >= 0.0 && f <= 1.0) {
							t = newT;
							foundCollison = true;
							collisionPoint = p3 + f*edge;
						}
					}
				}

				// Set result:
				if (foundCollison == true) {
					// distance to collision: ’t’ is time of collision
					float distToCollision = t*colPackage->velocity.length();
					// Does this triangle qualify for the closest hit?
					// it does if it’s the first hit or the closest
					if (colPackage->foundCollision == false ||
						distToCollision < colPackage->nearestDistance) {
							// Collision information nessesary for sliding
							colPackage->nearestDistance = distToCollision;
							colPackage->intersectionPoint=collisionPoint;
							colPackage->foundCollision = true;
					}
				}
		} // if not backface
	}


	//----------------------------------------------------------------

	void CamManager::caluateCollisionPackage()
	{

		// 清空结果集
		RendererPackage::iterator iter = _renderersCollision.begin();
		RendererPackage::iterator iter_end = _renderersCollision.end();

		for ( ; iter != iter_end ; ++iter )
		{
			iter->second.clear();
		}

		RendererPackage& culledrenderers = 
			*RendererManager::getSingleton().getCulledRendererPackage();

		vgKernel::RendererPackage::iterator ipac = culledrenderers.begin();
		vgKernel::RendererPackage::iterator ipac_end = culledrenderers.end();

		//vgKernel::RendererPackage::iterator outipac = _renderersCollision.begin();

		vgKernel::Box cameraBox = getCurrentFrustum()->getCameraBox();

		for ( ; ipac != ipac_end ; ++ipac )
		{
			if ( ipac->first != vgCore::RENDERER_TYPE_MODOJBECT )
			{
				continue;
			}

			RendererQueue* pQueue = &ipac->second;

			RendererQueue::iterator iter = pQueue->begin();
			RendererQueue::iterator iter_end = pQueue->end();

			for ( ; iter != iter_end ; ++iter )
			{			
				Renderer* curleaf = *iter;

				if (cameraBox.intersects(curleaf->getBoundingBox()))
				{
					_renderersCollision[ vgCore::RENDERER_TYPE_MODOJBECT ].push_back(
						curleaf );
				}
			}
		}

		return;
	}

#endif

	void CamManager::OnChar(int keyCode)
	{

		if(keyCode == vgKernel::InputCode::SPACE )
		{
			if(vgCam::CamManager::getSingleton().getCurrentCameraRecord()!=NULL&&vgCam::CamManager::getSingleton().getCurrentCameraRecord()!=&vgCam::CamManager::getSingleton()._singleVCR)
			{
				if(vgCam::CamManager::getSingleton().getCurrentCameraRecord()->b_play)
				{
					int nowframenum=vgCam::CamManager::getSingleton().getCurrentCameraRecord()->uiFrame;

					if (nowframenum > 0)
					{
						vgCam::CameraRecord* nowVCR=vgCam::CamManager::getSingleton().getCurrentCameraRecord();
						vgCam::CamManager::getSingleton().setPosByCurVcrSpecificFrame(nowframenum);

						vgCam::CamManager::getSingleton().getCurrentCameraRecord()->stopPlaying();
					}

					return ;
				}
				else
				{
					vgCam::CamManager::getSingleton().getCurrentCameraRecord()->continuePlaying();
					return ;
				}
			}

		}
	}
	//----------------------------------------------------------------
	void CamManager::renderBegin()
	{
		//if ( getCollisionOnOff() )
		//{
		//	caluateCollisionPackage();
		//}
	}

	//----------------------------------------------------------------
	bool CamManager::clear()
	{
#if 0
		// added by zsc for collision detection
		RendererPackage::iterator ico = _renderersCollision.begin();
		RendererPackage::iterator ico_end = _renderersCollision.end();

		for ( ; ico != ico_end ; ++ ico )
		{
			RendererQueue* curqueue = &ico->second;

			curqueue->clear();
		}

		_renderersCollision.clear();
#endif

		_viewCams.clear();

		return true;
	}

	CameraRecord* CamManager::getCameraRecordByName(
		const String& strRendererName )
	{
		using namespace std;
		std::vector<CameraRecordPtr>::iterator vcrItr = _VCRvector.begin();
		std::vector<CameraRecordPtr>::iterator vcrItrEnd = _VCRvector.end();

		for( ; vcrItr != vcrItrEnd; ++vcrItr )
		{	
			CameraRecord* record = (*vcrItr).getPointer();
			assert( record != NULL );

			if( record->getName() == strRendererName )
				return	record;
		}

		return	NULL;
	}
	//----------------------------------------------------------------
	bool CamManager::playContinuousRecords( const StringVector& records_names )
	{
		int siz = records_names.size();

		if ( siz == 0 )
		{
			return false;
		}

		//------------------------------------------
		// 首先得到这个record队列
		//------------------------------------------
		CameraRecordPtrVector revec;

		for ( int  i = 0 ; i < siz ; ++ i )
		{
			CameraRecordPtr precord = getCameraRecordPtrByName(
				records_names[i] );

			if ( precord.isNull() == false )
			{
				revec.push_back( precord );
			}
		}

		//------------------------------------------
		// 开始插入中间变换的record
		//------------------------------------------
		if ( revec.size() > 1 )
		{
			for ( int i = 0 ; i < revec.size() - 1; ++ i )
			{
				ViewCam from;
				ViewCam to;
				from.cloneCurrentCameraView();
				to.cloneCurrentCameraView();

				Quat q;
				Vec3 p;
				vgKernel::Vec3 offset;

				bool getok = revec[i]->getFrameInfoByIndex( 
					revec[i]->getFrameNum() - 1 , // 最后一帧
					p , q );

				offset = revec[i]->getOffset();
				p += offset;

				assert( getok == true );

				// 设置from
				from.setHeadingDegrees( q.getHeadDegrees() );
				from.setPitchDegrees( q.getPitchDegrees() );
				from.setPosition( p );

				getok = revec[ i+1 ]->getFrameInfoByIndex( 
					0, // 第一帧
					p , q );

				offset = revec[ i+1 ]->getOffset();
				p += offset;

				assert( getok == true );

				// 设置to
				to.setHeadingDegrees( q.getHeadDegrees() );
				to.setPitchDegrees( q.getPitchDegrees() );
				to.setPosition( p );

				CameraRecordPtr tmp( new CameraRecord );
				tmp->createFromSwitchingViewCam( &from , &to );
				revec.insert( revec.begin() + i + 1, tmp );

				i += 1;
			}
		}



		int revec_size = revec.size();

		if ( revec_size == 0 )
		{
			return false;
		}
		else if ( revec_size == 1 )
		{
			// 什么也不做
		}
		else if( revec_size > 1 )
		{
			for ( int i = 0 ; i < revec_size - 1; ++ i )
			{
				ContinuousRecordAction* pa = 
					new ContinuousRecordAction( revec[i] , revec[ i + 1 ] );

				revec[i]->registerAction( ActionPtr( pa ) );
			}
		}

		//------------------------------------------
		// 开始播放
		//------------------------------------------
		if ( revec.empty() == false )
		{
			setCurrentCameraRecordPtr( revec[0] );
			revec[0]->startPlaying();
		}

		return true;
	}

	//----------------------------------------------------------------
	bool CamManager::playContinuousRecords2( const StringVector& records_names )
	{
		int siz = records_names.size();

		if ( siz == 0 )
		{
			return false;
		}

		//------------------------------------------
		// 首先得到这个record队列
		//------------------------------------------
		CameraRecordPtrVector revec;

		for ( int  i = 0 ; i < siz ; ++ i )
		{
			CameraRecordPtr precord = getCameraRecordPtrByName(
				records_names[i] );

			if ( precord.isNull() == false )
			{
				revec.push_back( precord );
			}
		}


#if 0

		
		//------------------------------------------
		// 开始插入中间变换的record
		//------------------------------------------
		if ( revec.size() > 1 )
		{
			for ( int i = 0 ; i < revec.size() - 1; ++ i )
			{
				ViewCam from;
				ViewCam to;
				from.cloneCurrentCameraView();
				to.cloneCurrentCameraView();

				Quat q;
				Vec3 p;

				bool getok = revec[i]->getFrameInfoByIndex( 
					revec[i]->getFrameNum() - 1 , // 最后一帧
					p , q );

				assert( getok == true );

				// 设置from
				from.setHeadingDegrees( q.getHeadDegrees() );
				from.setPitchDegrees( q.getPitchDegrees() );
				from.setPosition( p );

				getok = revec[ i+1 ]->getFrameInfoByIndex( 
					0, // 第一帧
					p , q );

				assert( getok == true );

				// 设置to
				to.setHeadingDegrees( q.getHeadDegrees() );
				to.setPitchDegrees( q.getPitchDegrees() );
				to.setPosition( p );

				CameraRecordPtr tmp( new CameraRecord );
				tmp->createFromSwitchingViewCam( &from , &to );
				revec.insert( revec.begin() + i + 1, tmp );

				i += 1;
			}
		}

#endif


		int revec_size = revec.size();
		
		if ( revec_size == 0 )
		{
			return false;
		}
		else if ( revec_size == 1 )
		{
			// 什么也不做
		}
		else if( revec_size > 1 )
		{
			for ( int i = 0 ; i < revec_size - 1; ++ i )
			{
				ContinuousRecordAction* pa = 
					new ContinuousRecordAction( revec[i] , revec[ i + 1 ] );

				revec[i]->registerAction( ActionPtr( pa ) );
			}
		}

		//------------------------------------------
		// 开始播放
		//------------------------------------------
		if ( revec.empty() == false )
		{
			setCurrentCameraRecordPtr( revec[0] );
			revec[0]->startPlaying();
		}

		return true;
	}
	//----------------------------------------------------------------
	CameraRecordPtr CamManager::getCameraRecordPtrByName( const String& cam_name )
	{
		std::vector<CameraRecordPtr>::iterator vcrItr = _VCRvector.begin();
		std::vector<CameraRecordPtr>::iterator vcrItrEnd = _VCRvector.end();

		for( ; vcrItr != vcrItrEnd; ++vcrItr )
		{	
			if( (*vcrItr)->getName() == cam_name )
				return	*vcrItr;
		}

		return	CameraRecordPtr();
	}

	void CamManager::setCollisionOnOff( bool onOff )
	{
		vgPhys::PhysMananger::getSingleton().setCollisionEnable(onOff);
	}

	bool CamManager::getCollisionOnOff()
	{
		return vgPhys::PhysMananger::getSingleton().getCollisionEnable();
	}

	void CamManager::setEillipseVec(vgKernel::Vec3 newVec)
	{
		vgPhys::PhysMananger::getSingleton().setEillipseVec(newVec);
	}

	vgKernel::Vec3 CamManager::getEillipseVec()
	{
		return vgPhys::PhysMananger::getSingleton().getEillipseVec();
	}

	//----------------------------------------------------------------
	// AVI 相关

	bool CamManager::recordAviBegin()
	{
		if (m_nAviRecord == 0)
		{
			if (m_paviFile != NULL)
			{
				LONG fileSize = m_paviFile->GetCurrentFileSize();

				delete m_paviFile;
				m_paviFile = NULL;

				CString outString;
				outString.Format("保存AVI文件成功.文件大小 %ul", fileSize);
				AfxMessageBox(outString);

				if (m_pAviProgessDlg != NULL)
				{
					delete m_pAviProgessDlg;
					m_pAviProgessDlg = NULL;
				}
			}

			return false;
		}
		else if (m_nAviRecord == -1)
		{
			glPushAttrib(GL_VIEWPORT_BIT);

			if (m_pFrameBuffer != NULL)
			{
				delete m_pFrameBuffer;
			}
			m_pFrameBuffer = new vgCam::FrameBuffer( m_bmpWidth, m_bmpHeight );
			m_pFrameBuffer->create();

			m_pFrameBuffer->bind();
			m_frameBufferBindedFlag = -1;
		}
		else
		{
			int totalFrame = vgCam::CamManager::getSingleton().getCameraRecordByName(m_aviCameraName)->framenum;
			//int frameId = totalFrame - vgCam::CamManager::getSingleton().getAviRecordCnt();
			int frameId = totalFrame - m_nAviRecord;

			if (m_paviFile->GetCurrentFileSize() > 1800000000L)
			{
				delete m_paviFile;
				m_paviFile = NULL;

				int compressId = m_compressId;
				CString filePrefix;

				if (AfxExtractSubString(filePrefix, m_aviFilePath.GetString(), 0, _T('.')))
				{	
					CString tmp;
					tmp.Format("%d", ++m_fileId);
					filePrefix += tmp;
					filePrefix += ".avi";			
				}
				else
				{
					AfxMessageBox("拆分失败");
					vgCam::CamManager::getSingleton().setAviRecordCnt(0);

					return false;
				}

				if (compressId == 1)
				{
					//paviFile = new vgCam::CAviFile(m_aviFilePath, mmioFOURCC('M','S','V','C'), fps);

					m_paviFile = new CAviFile(filePrefix, mmioFOURCC('M','S','V','C'), m_fps);
				}
				else if (compressId == 2)
				{
					m_paviFile = new CAviFile(filePrefix, mmioStringToFOURCC("CVID", 0), m_fps);
				}
				else if (compressId == 3)
				{
					m_paviFile = new CAviFile(filePrefix, mmioFOURCC('M','P','G','4'), m_fps);
				}
				else
				{
					m_paviFile = new CAviFile(filePrefix, 0, m_fps);
				}

				m_paviFile->SetQuality(m_quality);
			} // end file if

			glPushAttrib(GL_VIEWPORT_BIT);

			if (m_pFrameBuffer != NULL)
			{
				delete m_pFrameBuffer;
			}
			m_pFrameBuffer = new vgCam::FrameBuffer( m_frameBufferWidth, m_frameBufferHeight );
			m_pFrameBuffer->create();

			m_pFrameBuffer->bind();
			m_frameBufferBindedFlag = 1;
		}

		return true;
	}

	bool CamManager::recordAviEnd()
	{
		if (m_frameBufferBindedFlag == -1)
		{
			m_frameBufferBindedFlag = 0;

			char* buf = new char[ 3 * m_bmpWidth * m_bmpHeight ];
			glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
			glReadPixels(0, 0, m_bmpWidth, m_bmpHeight , GL_BGR , GL_UNSIGNED_BYTE , buf);

			vgImage::CximageWrapper bmpimg;

			bmpimg.createFromArray(buf, m_bmpWidth, m_bmpHeight);

			bmpimg.saveToFile(m_bmpFilePath);

			delete[] buf;

			m_pFrameBuffer->unbind();

			m_pFrameBuffer->destroy();

			glPopAttrib();

			vgCam::CamManager::getSingleton().setAviRecordCnt(0);
		}

		if (m_frameBufferBindedFlag == 1)
		{
			m_frameBufferBindedFlag = 0;

			BYTE* buf = new BYTE[ 3 * m_frameBufferWidth * m_frameBufferHeight ];
			glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
			glReadPixels(0, 0, m_frameBufferWidth, m_frameBufferHeight , GL_BGR , GL_UNSIGNED_BYTE , buf);

			//m_pAviGenerator->AddFrame(buf);

			if (FAILED(m_paviFile->AppendNewFrame(m_frameBufferWidth, m_frameBufferHeight, buf,24)))
			{
				AfxMessageBox(m_paviFile->GetLastErrorMessage());
			}


			m_pFrameBuffer->unbind();

			m_pFrameBuffer->destroy();

			glPopAttrib();

			int progress = (float)(m_totalFrame - vgCam::CamManager::getSingleton().getAviRecordCnt()) / m_totalFrame * 100;
			m_pAviProgessDlg->setProgress(progress);

			delete[] buf;
		}

		return true;
	}

	void CamManager::setExpAviParam(String filePath, String cameraName, int height, int width, int compressId, int quality)
	{
		m_fileId = 0;

		m_aviFilePath = filePath.c_str();
		m_aviCameraName = cameraName;

		m_frameBufferHeight = height;
		m_frameBufferWidth  = width;

		if (m_aviFilePath.GetLength() == 0)
		{
			AfxMessageBox("空路径");
			return;    
		}

		m_frameBufferWidth = m_frameBufferWidth / 4 * 4;
		m_frameBufferHeight = m_frameBufferHeight / 4 * 4;

		vgCam::CameraRecord* record = vgCam::CamManager::getSingleton().getCameraRecordByName(m_aviCameraName);

		if (record == NULL)
		{
			AfxMessageBox("相机不存在");
			return ;
		}

		float totalTime = record->m_fTotalTime;
		float fps = record->fps;
		m_fps = fps;

		m_totalFrame = record->framenum;

		if (m_paviFile != NULL)
		{
			delete m_paviFile;
			m_paviFile = NULL;
		}

		// 不使用压缩，导出帧速为fps，从相机VCR中得到，一般为32帧
		m_compressId = compressId;
		if (compressId == 1)
		{
			//paviFile = new vgCam::CAviFile(m_aviFilePath, mmioFOURCC('M','S','V','C'), fps);

			m_paviFile = new CAviFile(m_aviFilePath, mmioFOURCC('M','S','V','C'), fps);
		}
		else if (compressId == 2)
		{
			m_paviFile = new CAviFile(m_aviFilePath, mmioStringToFOURCC("CVID", 0), fps);
		}
		else if (compressId == 3)
		{
			m_paviFile = new CAviFile(m_aviFilePath, mmioFOURCC('M','P','G','4'), fps);
		}
		else
		{
			m_paviFile = new CAviFile(m_aviFilePath, 0, fps);
		}

		m_quality = quality;
		m_paviFile->SetQuality(quality);

		setAviRecordCnt(m_totalFrame); 
		setCurrentAviCameraName(m_aviCameraName);

		m_pAviProgessDlg = new vgcaDlgAviProgress;
		m_pAviProgessDlg->Create(IDD_AVI_PROGRESS);
		m_pAviProgessDlg->ShowWindow(SW_SHOW);
	}

	void CamManager::setExpBmpParam(String filePath, int width, int height)
	{
		m_bmpFilePath = filePath;
		m_bmpWidth = width;
		m_bmpHeight = height;

		m_bmpWidth = m_bmpWidth / 4 * 4;
		m_bmpHeight = m_bmpHeight / 4 * 4;

		if (m_bmpFilePath.length() == 0)
		{
			::MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, "保存文件失败，路径不能为空!",
				"VR-GIS Platform V2.0", MB_OK | MB_ICONWARNING );

			return ;
		}

		// 设置为记录一张BMP图片
		m_nAviRecord = -1;
	}

	//---------------------------------------------------------------------------------

	void CamManager::unLoadData()
	{

		if ( m_pFrameBuffer != NULL)
		{
			delete m_pFrameBuffer;

			m_pFrameBuffer = NULL;
		}

		if ( m_paviFile != NULL)
		{
			delete m_paviFile;

			m_paviFile = NULL;
		}

		if ( m_pAviProgessDlg != NULL)
		{
			delete m_pAviProgessDlg;
			m_pAviProgessDlg = NULL;
		}
		
		m_pVCR = NULL;

		_viewCams.clear();

		_VCRvector.clear();

	}
	//---------------------------------------------------------------------------------
	void CamManager::reset()
	{

		unLoadData();

		_keyPressedMask = 0;
		_isControlling = false;
		_mouseMoveAndWheelCounter = 0;

		// Initalize all our member varibles.
		m_MaxPitchRate			= 0.0f;
		m_MaxHeadingRate		= 0.0f;

		m_HeadingDegrees		= 0.0f;
		m_PitchDegrees			= 0.0f;

		m_MaxForwardVelocity	= 0.0f;
		m_ForwardVelocity		= 1.0f;

		m_PitchVelocity			= 0.1f;
		m_TurningVelocity		= 0.5f/*0.1f*/;

		m_upAndDownMultiply = 1.0f;

		m_ChannelNum=0;

		m_near= m_nearBase = 0.6f;
		m_far=1000000/*10000000*/;
		m_fov=45/*60*/;
		m_aspectratio=1.33f;

		m_pVCR=&_singleVCR;
		b3Channel= false;
		IsServer= false;

		_canBeMoved = true;

		MouseX = 0;
		MouseY = 0;		

		setDefaultParameters();

		m_bMouseMode = false;

		m_uiIndexViewCam	= 0;


#if 0
		m_colPacket.eRadius.x = .25;
		m_colPacket.eRadius.y = .5;
		m_colPacket.eRadius.z = .25;

		m_colPacket.continueVelocity = Vec3(0,0,0);

		m_enableCollisionDetection = false;

		VGK_TRACE(_T("CamManager created."));

		using namespace vgKernel;

		//------------------------------------------
		// 目前只支持mod物体!
		//------------------------------------------

		_renderersCollision.insert( std::make_pair( 
			vgCore::RENDERER_TYPE_MODOJBECT , RendererQueue() ));

#endif

		m_nAviRecord = 0;
		m_frameBufferBindedFlag = 0;
		m_pFrameBuffer = NULL;
		m_paviFile = NULL;

		m_pAviProgessDlg = NULL;

		m_Position = Vec3(0,0,0);


	}


	//----------------------------------------------------------------
	CameraRecord* CamManager::addCameraRecordFromFile( const String& vcr_name)
	{
		CameraRecord*	newone = new CameraRecord();

		String _name = vgKernel::StringUtility::getFilenameWithoutExtFromAbsPath(vcr_name);
		newone->setName( _name );

		newone->setVcrFilePath(vcr_name);
		newone->loadVCR(vcr_name);

		addCameraRecord( CameraRecordPtr(newone) );

		return newone;
	}

	//----------------------------------------------------------------
	//设置多通道视景体有关的参数	@FengYK 2009/10/28	20:23
	void CamManager::setViewFrustumParam(int ChanNum, float ratio, float hOffset, float vOffset)
	{
		m_ChannelNum = ChanNum;
		m_ratio = ratio;
		m_hOffset = hOffset;
		m_vOffset = vOffset;
		//setupViewFrustum();
	}
	
	//----------------------------------------------------------------
	void CamManager::InitTopViewCam()
	{
		assert( _topViewCam != NULL );
		if ( _topViewCam == NULL )
		{
			return;
		}

		_topViewCam->setPosition( Vec3( 0, 1000, 0 ) );
		_topViewCam->setPitchDegrees( 90.0 );
		_topViewCam->setHeadingDegrees( 0.0 );
		_topViewCam->setForwardVelocity( getForwardVelocity() );
		_topViewCam->flushData();
	}
	//----------------------------------------------------------------
	void CamManager::InitPerspectViewCam()
	{
		assert( _perspectViewCam != NULL );
		if ( _perspectViewCam == NULL )
		{
			return;
		}

		_perspectViewCam->setPosition( Vec3( 0, 500, 0 ) );
		_perspectViewCam->setPitchDegrees( 45.0 );
		_perspectViewCam->setHeadingDegrees( 0.0 );
		_perspectViewCam->setForwardVelocity( getForwardVelocity() );
		_perspectViewCam->flushData();
	}
	//----------------------------------------------------------------
	/*float CamManager::getWindowWidth()
	{
		return m_window_width;
	}

	float CamManager::getWindowHeight()
	{
		return m_window_height;
	}*/
	
	void CamManager::channel3Enable(bool b_enable)
	{
		b3Channel = b_enable;
	}
}// end of namespace vgCam
