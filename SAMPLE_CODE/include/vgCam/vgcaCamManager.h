#ifndef __VGCACAMMANAGER_H__
#define __VGCACAMMANAGER_H__
#include <vgCam/vgcaDefinition.h>
#include <vgKernel/vgkForward.h>

#include <vgKernel/vgkSingleton.h>
#include <vgCam/vgcaViewCam.h>
#include <vgCam/vgcaViewFrustum.h>
#include <vgCam/vgcaCameraRecord.h>
#include <vgKernel/vgkRendererHolder.h>	
#include <vgKernel/vgkBox.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkPlane.h>
#include <vgCam/vgcaCameraRecord.h>
#include <vgKernel/vgkCamMgrImpl.h>
#include <vgCam/vgcaFrameBuffer.h>
#include <vgCam/vgcaAviFile.h>
#include <vgCam/vgcaDlgAviProgress.h>
#include <vgImage/vgiCximageWrapper.h>
#include <vgKernel/vgkRenderCommand.h>

#include <vgKernel/vgkPropertyObserver.h>
namespace vgCam {
	/**
		@date 	2008/08/30  10:05	
		@author  leven;
	
		@brief 	
	
		@see    
	*/

	class VGCA_EXPORT  CamManager : 
		public vgKernel::Singleton<CamManager>,
		public vgKernel::InputHandler,
		public vgKernel::RendererHolder,
		public vgKernel::CamMgrImpl,
		public vgKernel::PropertyObserver
	{
		friend class vgKernel::Singleton<CamManager>;
	private:
		CamManager();

	public:

		virtual ~CamManager();
		
		virtual void onEvent(unsigned int eventId, void *param);

	protected:
		virtual bool initialise();

		virtual bool shutdown();

	public:


		bool clear();

		virtual void OnChar(int keyCode);

		void moveLeft();
		void moveRight();

		void moveLeft2(float offset);
		void moveRight2(float offset);

		void moveHigher(float offset);
		void moveLower(float offset);

		void moveUp();
		void moveDown();

		void moveForward();
		void moveBackward();

		void moveForwardTowardsDirection();
		void moveBackwardTowardsDirection();

		void moveForwardTowardsDirection2();
		void moveBackwardTowardsDirection2();

		void moveInDirection();

		void changeVelocity(GLfloat vel);
		void changeHeading(GLfloat degrees);
		void changePitch(GLfloat degrees);
		void fly( /*const bool& useMouseMode*/ );

		bool getMouseMode() {return m_bMouseMode;}

		void setMouseMode(bool MouseMode)  {m_bMouseMode = MouseMode;}

		void setMovingEnable( bool enable_it )
		{
			_canBeMoved = enable_it;
		}

		bool getMovingEnable() const 
		{
			return _canBeMoved;
		}


		virtual void OnKeyDown(int keyCode);

		virtual void OnMouseMove(UINT nFlags, CPoint position);

		virtual void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

		virtual void OnRBottonDown(UINT nFlags, CPoint position);

		virtual void OnRBottonUp(UINT nFlags, CPoint position);

		void setDefaultParameters();


		virtual Vec3 getCurrentPosition() 
		{
			return m_Position;
		}

		virtual Vec3* getCurrentPositionPtr()
		{
			return &m_Position;
		}

		virtual void setCurrentPosition( const Vec3& newpos )
		{
			m_Position = newpos;
		}

		virtual Vec3 getCurrentDirection()
		{
			return m_DirectionVector;
		}

		void setCenterOfScreen( const uint& centerx , 
			const uint& centery )
		{
			_centerX = centerx;
			_centerY = centery;
		}

		GLfloat getPitchDegrees()
		{
			return m_PitchDegrees;
		}
		GLfloat getHeadingDegrees()
		{
			return m_HeadingDegrees;
		}
		void setPitchDegrees(float par)
		{
			m_PitchDegrees=par;
		}
		void setHeadingDegrees(float par)
		{
			m_HeadingDegrees=par;
		}
		GLfloat getForwardVelocity()
		{
			return m_ForwardVelocity;
		}
		void setForwardVelocity(float par)
		{
			m_ForwardVelocity=par;
		}
		GLfloat getTurningVelocity()
		{
			return m_TurningVelocity;
		}
		void setTurningVelocity(float par)
		{
			m_TurningVelocity=par;
		}
		GLfloat getPitchVelocity()
		{
			return m_PitchVelocity;
		}
		void setPitchVelocity(float par)
		{
			m_PitchVelocity=par;
		}

		float getUpAndDownMultiply() const
		{
			return m_upAndDownMultiply;
		}

		void setUpAndDownMultiply( const float& newmultiply )
		{
			m_upAndDownMultiply = newmultiply;
		}

		ViewCamPtrVector* getViewCams()
		{
			return &_viewCams;
		}

		/**
			要进行碰撞检测, 需要放在rendermanager的renderbegin之后.
		*/
		void renderBegin();


		virtual bool onDeleteRenderer( vgKernel::Renderer *render );//chunyongma2008.9.8



		void setModelViewMatrix(const vgKernel::Vec3 postion,const float PDegrees,const float HDegrees );
		void setModelViewMatrix( const vgKernel::Vec3 &pos,
			Quat&qt );

		void clientfly( const bool& useMouseMode);//没有键盘响应
		void serverfly( const bool& useMouseMode );//没有更新视图

		void setupCamera();

		virtual bool isControlling()
		{
			return _isControlling;
		}


		ViewCam* getTopViewCam()
		{
			return _topViewCam;
		}

		ViewCam* getPerspectViewCam()
		{
			return _perspectViewCam;
		}

		//livenson add 2010.1.6 for mirror effect of water
		bool m_bIsDrawMirror;
		double m_WaterHeight;

	private:
		void mouseFunction();

		void setModelViewMatrix();
		//////////////////////////////////////////////////////////////////////////
		////相机的组织
		//////////////////////////////////////////////////////////////////////////

		void InitTopViewCam();
		void InitPerspectViewCam();

	private:
		bool m_isLBtnDown;

		CameraRecord* m_pVCR;

		CameraRecordPtr _currentRecord;

		CameraRecord _singleVCR; 

		bool m_bMouseMode;

		ViewCamPtrVector _viewCams;

		ViewCam*  _topViewCam;  // add by ZhouZY 2009-1-4 for switch to top view
		ViewCam*  _perspectViewCam; 

		CameraRecordPtrVector _VCRvector;

		// 分类索引
		unsigned int m_uiIndexViewCam;
	public:
		void renderVcr();
		void renderViewCams()
		{
			int i=0;
			for (;i<_viewCams.size();i++)
			{
				_viewCams[i]->renderViewCamEntity();
			}

		}

		ViewCam* getViewCamByName( const String& viewcam_name )
		{
			int i=0;
			for (;i<_viewCams.size();i++)
			{
				if ( _viewCams[i]->getName() == viewcam_name )
				{
					return _viewCams[i].getPointer();
				}
			}

			return NULL;
		}


		//	CameraRecord
	public:
		CameraRecord* getCurrentCameraRecord()
		{
			return m_pVCR;
		}
		void setCurrentCameraRecord(CameraRecord* par)
		{
			m_pVCR=par;
		}

		bool setCurrentCameraRecordPtr( CameraRecordPtr pcur_record )
		{
			if ( pcur_record.isNull() == true )
			{
				return false;
			}

			_currentRecord = pcur_record;
			m_pVCR = _currentRecord.getPointer();

			return true;
		}

		void setDefaultCamRecordPtr()
		{
			m_pVCR=&_singleVCR;


			if (getCurrentCameraRecord()->frameptr)
			{
				delete []getCurrentCameraRecord()->frameptr;
			}
			getCurrentCameraRecord()->init();

		}


		int getCameraRecordNum()
		{
			return _VCRvector.size();
		}

		CameraRecordPtrVector* getCameraRecords()
		{
			return &_VCRvector;
		}

		void addCameraRecord(CameraRecordPtr newone)
		{
			_VCRvector.push_back(newone);
		}

		CameraRecord* addCameraRecordFromFile( const String& vcr_name);

		CameraRecord*	getCameraRecordByName( const String& strRendererName);

		CameraRecordPtr	getCameraRecordPtrByName( const String& cam_name);

		void	beginRecordingVcr()
		{
			getCurrentCameraRecord()->beginRecording();
		}

		void	continueRunVcr()
		{
			getCurrentCameraRecord()->continuePlaying();
		}

		void	stopRunVcr()
		{
			getCurrentCameraRecord()->stopPlaying();
		}

	private:

		// 当前相机的信息
		GLfloat m_MaxPitchRate;
		GLfloat m_MaxHeadingRate;
		GLfloat m_HeadingDegrees;
		GLfloat m_PitchDegrees;
		GLfloat m_MaxForwardVelocity;
		GLfloat m_ForwardVelocity;

		GLfloat m_upAndDownMultiply;

		GLfloat m_TurningVelocity;
		GLfloat m_PitchVelocity;



		Quat _combinedQuaternion;

		GLfloat  _tmpMatrix[16];
		Quat _tmpQuaternionHeading;
		Quat _tmpQuaternionPitch;

		UINT	MouseX, MouseY;		// Coordinates for the mouse
		UINT	_centerX, _centerY;	// Coordinates for the center of the screen.

		/************************************************************************/
		/*      视景体和多通道相关                                              */
		/************************************************************************/	
	public:
		Vec3 m_DirectionVector;
		Vec3 m_Position;
		bool b3Channel;
		bool IsServer;
	private:
		
		//视景体数据成员

		//根据near ,far,fov,以及窗口的长宽的得到的m_aspectratio，near ,far,fov在构造函数已经给出数值，后面还可以调整
		//默认给出一套对称的视景体参数，然后其余通道在此基础上修正即可
		void initialFrustum();

		int    m_ChannelNum;
		float		m_window_width;
		float		m_window_height;
		float m_left,m_right,m_up,m_down,m_near,m_far,m_fov,m_aspectratio;//应该有默认的构造函数
		float	m_nearBase; 
		ViewFrustum _currentFrustum;
		float m_ratio;
		float m_hOffset;
		float m_vOffset;
	public:		

		void setAspectRatioByWindowSize(int cx, int cy);//设定m_window_width成员大小，顺便计算宽高比
		void setFov(float fovpar);//适用于对称视景体,tan是角度还是弧度，有待于再验
		float getFov(){return m_fov;}
		void setNear(float nearpar);
		float getNear(){return m_near;}
		void setFar(float farpar);
		float getFar(){return m_far;}
		void setViewport(float leftpar,float rightpar,float uppar,float downpar);
		void setupViewFrustum();//设定多通道的视景体
		float getAspectRatio() { return m_aspectratio; }		
		void setChannelNum(int par){m_ChannelNum=par;}

		ViewFrustum* getCurrentFrustum()
		{
			return &_currentFrustum;
		}

		void updateCurrentFrustum()
		{
			_currentFrustum.validateUpdate();
			_currentFrustum.calculateInEveryFrame();
		}
	public:
		// 新增一个相机的接口 [9/1/2008 zhu]
		ViewCam* saveCurrentCameraView();//新增加一个相机视点
		void immediateToViewCam(ViewCam *cam);

		bool addViewCam( ViewCam* cam )
		{
			_viewCams.push_back( ViewCamPtr( cam ) );
			return true;
		}

		bool addViewCamPtr( ViewCamPtr cam )
		{
			_viewCams.push_back( cam );
			return true;
		}

		bool dumpInfoToStream( vgKernel::StreamWriterPtr pwriter );
		bool readInfoFromStream( vgKernel::StreamReaderPtr preader );

		void copyRecordfile( const String& attachDataPath);


		void setPosByCurVcrSpecificFrame(int nowframenum);

		void setCollisionOnOff(bool onOff);

		bool getCollisionOnOff();

		void setEillipseVec(vgKernel::Vec3 newVec);

		Vec3 getEillipseVec();

		bool playContinuousRecords( const StringVector& records_names );
		bool playContinuousRecords2( const StringVector& records_names );


		// Avi 录制相关
	public:
		bool recordAviBegin();

		bool recordAviEnd();

		int getAviRecordCnt()
		{ 
			return m_nAviRecord; 
		}

		void setAviRecordCnt(int cnt)  
		{
			m_nAviRecord = cnt; 
		}

		String getCurrentAviCameraName()
		{
			return m_currentAviCameraName;
		}

		void setCurrentAviCameraName(const String& name)
		{
			m_currentAviCameraName = name;
		}

		void setExpBmpParam(String filePath, int width, int height);

		void setExpAviParam(String filePath, String cameraName, int height, int width, int compressId, int quality);
		
		void reset();

		void unLoadData();
	private:

		// 是否在录制AVI状态 0-正常渲染，1-导出一张截图，n-播放相机动画
		int m_nAviRecord;
		vgCam::FrameBuffer *m_pFrameBuffer;

		vgCam::CAviFile *m_paviFile;
		vgcaDlgAviProgress *m_pAviProgessDlg;

		int m_frameBufferWidth;
		int m_frameBufferHeight;

		int m_compressId;
		int m_quality;

		String m_aviCameraName;
		CString m_aviFilePath;
		int m_fileId;
		int m_fps;
		int m_frameBufferBindedFlag;

		// 是否在录制AVI状态 0-正常渲染，1-导出一张截图，n-播放相机动画
		//		int m_nAviRecord;
		float m_totalFrame;

		// BMP 文件导出相关
		String m_bmpFilePath;
		int    m_bmpWidth;
		int	   m_bmpHeight;

		String m_currentAviCameraName;

	private:

		// 是否可以移动,操作视角
		bool _canBeMoved;

		// 是否用户在移动鼠标或者按下键盘
		bool _isControlling;
		int _keyPressedMask;
		int _mouseMoveAndWheelCounter;


	private:
		
		// 嵌入渲染循环的操作
		vgKernel::RenderCommand *m_aviBegin;
		vgKernel::RenderCommand *m_aviEnd;
		vgKernel::RenderCommand *m_camBegin;

	public:
			void setViewFrustumParam(int ChanNum, float ratio, float hOffset, float vOffset);//设置多通道视景体有关的参数
			//float getWindowWidth();
			//float getWindowHeight();
			void channel3Enable(bool b_enable);

	};
	
	
}// end of namespace vgCam
	


#endif // end of __VGCACAMMANAGER_H__
