


#ifndef __VGCAVIEWCAM_H__
#define __VGCAVIEWCAM_H__
#include <vgCam/vgcaDefinition.h>
#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkSharePtr.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkQuat.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkInputSystem.h>
#include <vgKernel/vgkInputCodeDef.h>
#include <vgKernel/vgkRendererObserver.h>
#include <vgKernel/vgkRenderer.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>
#include <vgCam/vgcaViewFrustum.h>

namespace vgCam {


	using namespace vgKernel ;


	class ViewCam;

	typedef vgKernel::SharePtr<ViewCam> ViewCamPtr;

	typedef std::vector<ViewCamPtr> ViewCamPtrVector;


	/*
	5010 -- 5030之间为QuadTreeSceneMananger的管辖范围之内
	*/
	const vgKernel::RendererType RENDERER_TYPE_VIEWCAMERA = 5001;


	class  VGCA_EXPORT ViewCam:public vgKernel::Renderer
	{
		VGK_RENDERER_IN_DECLARE( ViewCam )
	public:
		ViewCam();
		virtual ~ViewCam();
	/************************************************************************/
	/*      相机位置相关                                                    */
	/************************************************************************/	
	private:
		// 专用于camerRecord的信息
		Vec3 m_Position;
		
		float m_HeadingDegrees;
		float m_PitchDegrees;
		
		float m_ForwardVelocity;
		float m_TurningVelocity;
		float m_PitchVelocity;

	public:
		//辅助变量
		Quat _combinedQuaternion;
		float  _tmpMatrix[16];
		Quat _tmpQuaternionHeading;
		Quat _tmpQuaternionPitch;


	public:


		Vec3 getPosition() 
		{
			return m_Position;
			
		}

		void setPosition( const Vec3& newpos )
		{
			m_Position = newpos;
			flushData();

			notifyOberversOnEvent(VG_OBS_SELECTCHAGNED, NULL);
		}

		void setCamData(const ViewCam& curcam);

		float getPitchDegrees()
		{
			return m_PitchDegrees;
		}
		float getHeadingDegrees()
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

		float getForwardVelocity()
		{
			return m_ForwardVelocity;
		}
		void setForwardVelocity(float par)
		{
			m_ForwardVelocity=par;
		}
		/************************************************************************/
		/*      Renderer相关                                                    */
		/************************************************************************/	

	private:
		UniqueID _uniqueID;
		String _ViewCamName;
		vgKernel::Box _dynamicBox;
		float _squaredDistanceToViewer;
	public:
		/**
		继承Renderer而来的接口
		*/
		virtual UniqueID getUniqueID()
		{
			return _uniqueID;
		}

		virtual void render()
		{

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
			m_Position+=Vec3(x,y,z);
			flushData();
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
			flushData();
			return _dynamicBox;
		}

		/**
		继承Renderer而来的接口
		*/
		virtual std::pair<bool, float> testIntersectWithTriangles( const vgKernel::Ray& ray );


		/**
		继承Renderer而来的接口
		*/
		virtual long getNumOfTriangles(){	return 0;}

		/**
		继承Renderer而来的接口
		*/
		virtual float setDistanceToViewer( const Vec3& viewer_pos  );


		/************************************************************************/
		/*      视景体相关                                                      */
		/************************************************************************/	

	private:
		
		void setupViewFrustum();

		//视景体数据成员
		float m_left,m_right,m_up,m_down,m_near,m_far,m_fov,m_aspectratio;//应该有默认的构造函数

		//一个相机对应一个视景体		
		ViewFrustum _frustum;	

		bool m_isVisible;

	public:

		void setFov(float fovpar);//适用于对称视景体,tan是角度还是弧度，有待于再验
		void setAspectRatio(float aspectratiopar);//适用于对称视景体
		void setNear(float nearpar);
		void setFar(float farpar);
		void setViewport(float leftpar,float rightpar,float uppar,float downpar);


		void	setToVisible(){m_isVisible=true;}
		void	setToUnvisible(){m_isVisible=false;}

		void	flushData();
		void	renderViewCamEntity();

		
		void	cloneCurrentCameraView();


		bool readFromStream( 
			vgKernel::StreamReaderPtr preader, int version,
			const String& version_info );
		bool writeToStream( 
			vgKernel::StreamWriterPtr pwriter, int version,
			const String& version_info );


	};



	VGK_RENDERER_OUT_DECLARE( ViewCam )




	
	
}// end of namespace vgCam
	


#endif // end of __VGCAVIEWCAM_H__