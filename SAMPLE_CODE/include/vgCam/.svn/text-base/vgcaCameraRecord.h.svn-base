


#ifndef __VGCACAMERARECORD_H__
#define __VGCACAMERARECORD_H__

#include <vgCam/vgcaDefinition.h>
#include <vgKernel/vgkTimer.h>
#include <vgCam/vgcaViewCam.h>
#include <vgCam/vgcaActionHolder.h>
#include <vgCam/vgcaCameraRecordFrame.h>


namespace vgCam {

	using namespace vgKernel;

	const vgKernel::RendererType RENDERER_TYPE_CAMRECORD = 5050;


	class  VGCA_EXPORT CameraRecord:
		public vgKernel::Renderer, public ActionHolder
	{
		VGK_RENDERER_IN_DECLARE( CameraRecord )

		friend class CamManager;
	public:
		CameraRecord(void);
		virtual ~CameraRecord(void);

	public:
		//读写相关
		VCRFrame *frameptr;
		float *frame_time;
		bool b_KeyVcr;
		long framenum;
		float fps;//2008.10.28

		String	m_vcrFileName;
		String	m_vcrFilePath;
		//状态控制变量
		bool b_load;//是否载入
		bool b_record;//是否启用录制
		bool b_play;//是否播放
		bool b_pause;//是否暂停
		float b_playratio;//控制播放速度

		//渲染相关
		float m_fTotalTime;
		float fTime;//从片头开始播放到的时刻
		vgKernel::Timer m_Timer;
		long uiFrame;//现在应该播放的帧号
		long uiLastFrame;//现在应该播放的帧号
		float fLastTime;//从片头开始播放到的时刻

		//录制相关

		VCRFrameList mVCRFrameList;	

		// vcr的平移 [11/11/2008 zhu]
		Vec3 offset_vcr;
		//bool b_visible;


		/************************************************************************/
		/* 实现继承render的成员和接口                                                                     
		/************************************************************************/	
	public:


		/**
		继承Renderer而来的接口
		*/
		virtual UniqueID getUniqueID()
		{
			return _uniqueID;
		}

		/**
		继承Renderer而来的接口
		*/
		virtual String getName()
		{
			return _ViewCamName;
		}

		virtual String* getNamePtr()
		{
			return &_ViewCamName;
		}
		/**
		继承Renderer而来的接口
		*/
		virtual void setName( const String& newname )
		{
			_ViewCamName = newname;
		}
		/**
		继承Renderer而来的接口
		*/
		void translate(const float& x, const float& y, const float& z)
		{
			offset_vcr=Vec3(x,y,z);
			return;
		}

		/**
		继承Renderer而来的接口
		*/
		void rotateSelf(const float& angle, const float& x, const float& y, const float& z){return;}


		/**
		继承Renderer而来的接口
		*/
		void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z){ return;}
		/**
		继承Renderer而来的接口
		*/
		void rotate(const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z){ return;}


		/**
		继承Renderer而来的接口
		*/
		virtual vgKernel::Box getBoundingBox()
		{
			return _dynamicBox;
		}

		/**
		继承Renderer而来的接口
		*/
		virtual std::pair<bool, float> testIntersectWithTriangles( const vgKernel::Ray& ray )
		{
			std::pair<bool, float> result = vgKernel::Math::intersects( ray, _dynamicBox );
			return result;
		}


		/**
		继承Renderer而来的接口
		*/
		virtual long getNumOfTriangles(){	return 0;}

		/**
		继承Renderer而来的接口
		*/
		virtual float setDistanceToViewer( const Vec3& viewer_pos  ){	return 0;}
		virtual void	render();

		/************************************************************************/
		/* end                                                                     
		/************************************************************************/

		void init();

		void loadVCR( const String& filename );

		void saveVCR( const String& filename);//录制结束后，进行保存


		
		void startPlaying(); 
		void stopPlaying();
		void continuePlaying();


		void acceleratePlaying();
		void deceleratePlaying();

		void switchVisible();

		void beginRecording();//开始录制
		void pauseRecording();//暂停录制
		void finishRecording();//结束录制


		void switchCamera(ViewCam *from, ViewCam *to);
		void switchCamera(ViewCam *from, ViewCam *to, float _time, int frame);

		String	getVcrFileName()				 {	return m_vcrFileName ; }
		String	getVcrFilePath()				 {	return m_vcrFilePath ; }

		void	setVcrFilePath(String vcrPath)	 
		{	
			m_vcrFilePath = vcrPath; 
			m_vcrFileName = vcrPath;
			m_vcrFileName.substr( m_vcrFileName.find_last_of("\\/")+1, String::npos);
		}

		bool getPlayingFlag()
		{
			return b_play;
		}

		vgKernel::Vec3 getOffset() { return offset_vcr; }

		bool readFromStream( 
			vgKernel::StreamReaderPtr preader, int version,
			const String& version_info );
		bool writeToStream( 
			vgKernel::StreamWriterPtr pwriter, int version,
			const String& version_info );


		//----------------------------------------------------------------
		void	reset();
		//----------------------------------------------------------------

		void	startPlayingByTime(float fAnytime = 0.0f);
		void	startPlayingByFrame(long uiAnyFrame);

	
		int getFrameNum() const
		{
			return framenum;
		}

		bool getFrameInfoByIndex( const int& frame_index ,
			Vec3& out_position , Quat& out_quat )
		{
			if( frame_index < 0 || frame_index >= getFrameNum() )
			{
				return false;
			}

			out_position = frameptr[ frame_index ].getPosition();
			out_quat = frameptr[ frame_index ].getQuat();

			return true;
		}

		void createFromSwitchingViewCam(ViewCam *from, ViewCam *to);

	private:

		bool _startPlayingFlag;

		VCRFrame last;	

		float sethead;
		float setpitch;

		void playVCRproc(/*Camera *cam*/);//加上了精确的时钟控制
		float	getTimeWithFrame(long uiAnyFrame);
		void recordVCRproc(/*Camera *cam*/);//每帧捕获采集相机信息
		void playByFrame(int uiFrame);

		UniqueID _uniqueID;
		String _ViewCamName;
		vgKernel::Box _dynamicBox;
		float _squaredDistanceToViewer;
	};


	VGK_RENDERER_OUT_DECLARE( CameraRecord )

	typedef vgKernel::SharePtr<CameraRecord> CameraRecordPtr;
	typedef std::vector<CameraRecordPtr> CameraRecordPtrVector;


}


#endif // end of __VGCACAMERARECORD_H__