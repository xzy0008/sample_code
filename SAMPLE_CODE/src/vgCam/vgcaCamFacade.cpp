


#include <vgStableHeaders.h>
#include <vgCam/vgcaCamFacade.h>
#include <vgCam/vgcaCamManager.h>
#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkSelectManager.h>


#undef PI

namespace vgCam {
	
	
	
	
	//----------------------------------------------------------------
	bool CamFacade::gotoCameraByName( const String& cam_name )
	{
		vgKernel::Renderer* pRenderer = 
			vgKernel::RendererManager::getSingleton().getRendererbyName( cam_name );

		if (pRenderer != NULL)
		{	
			if (pRenderer->getType() !=  vgCam::RENDERER_TYPE_VIEWCAMERA)
			{
				MessageBox( NULL , "请选择相机!","VR-GIS",MB_OK );

				return false;
			}

			gotoCamera( (vgCam::ViewCam*)pRenderer );

			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	bool CamFacade::gotoCamera( vgCam::ViewCam* cam )
	{
		if ( cam == NULL )
		{
			return false;
		}

		vgCam::ViewCam *to,from;
		to = cam;

		from.cloneCurrentCameraView();
		to->setToUnvisible();

		vgCam::CamManager::getSingleton().setDefaultCamRecordPtr();
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera(&from,to);

		return true;
	}
	//----------------------------------------------------------------
	bool CamFacade::gotoRenderer( Renderer* renderer )
	{
		if ( renderer == NULL )
		{
			return false;
		}

		if ( renderer->getType() != vgCam::RENDERER_TYPE_VIEWCAMERA )
		{
			gotoBox( renderer->getBoundingBox() );

			return true;
		}

		//------------------------------------------
		// 此时转到camera,需要特别处理
		//------------------------------------------
		return gotoCamera( (vgCam::ViewCam*)renderer );
	}
	//----------------------------------------------------------------
	bool CamFacade::gotoBox( const vgKernel::Box& box )
	{
		vgCam::ViewCam to,from;

		//----------------------------------------------------------------
		using namespace vgKernel;
		Vec3 halfsiz = box.getHalfSize();
		float len = halfsiz.length() / 2;
		Vec3 center = box.getCenter();

		//----------------------------------------------------------------
		vgKernel::Box nowbox( 
			box._maxVertex.x + len , 
			box._maxVertex.y + len , 
			box._maxVertex.z + len , 
			box._minVertex.x - len , 
			box._minVertex.y - len , 
			box._minVertex.z - len );

		to.cloneCurrentCameraView();
		//to.setPosition( 1.5 * nowbox._maxVertex - 0.5 * nowbox._minVertex);
		to.setPosition( center + nowbox.getHalfSize() );

		vgKernel::Vec3 vec1=nowbox._minVertex-nowbox._maxVertex;


		float sethead;
		sethead=270-180/ vgKernel::Math::PI*asin(vec1[2]/sqrt(vec1[0]*vec1[0]+vec1[2]*vec1[2]));
		if (sethead>180)
		{
			sethead-=360;
		}


		if (( vec1[0]*vec1[0]+vec1[2]*vec1[2] ) == 0 )
		{
			sethead = 0;
		}




		to.setHeadingDegrees(sethead);
		float setpitch=180/ vgKernel::Math::PI*asin(-vec1[1]/vec1.length());
		to.setPitchDegrees(setpitch);

		//float xzlen = sqrt( halfsiz.x * halfsiz.x + halfsiz.z * halfsiz.z );

		//float head = -asin( halfsiz.z / xzlen );
		//float pitch = atan2( halfsiz.y , xzlen );

		//to.setHeadingDegrees( head );
		//to.setPitchDegrees( pitch );

		from.cloneCurrentCameraView();
		vgCam::CamManager::getSingleton().setDefaultCamRecordPtr();
		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera(&from,&to);

		return true;
	}
	//----------------------------------------------------------------
	bool CamFacade::gotoSelectedObject()
	{
		vgKernel::RendererQueue& sel =
			vgKernel::SelectManager::getSingleton().getSelectedItems();

		if ( sel.size() == 1 )
		{
			vgKernel::Renderer* renderer = sel[0];

			if ( renderer->getType() ==  vgCam::RENDERER_TYPE_VIEWCAMERA)
			{
				return gotoSelectedCamera();
			}
		}

		return gotoBox( vgKernel::SelectManager::getSingleton().getSelectedBox() );
	}
	//----------------------------------------------------------------
	bool CamFacade::gotoSelectedCamera()
	{
		vgKernel::RendererQueue& sel =
			vgKernel::SelectManager::getSingleton().getSelectedItems();

		if ( sel.size() != 1 )
		{
			MessageBox( NULL , "请选择单一相机","提示",MB_OK );
			return false;
		}

		vgKernel::Renderer* renderer = sel[0];

		if ( renderer->getType() !=  vgCam::RENDERER_TYPE_VIEWCAMERA)
		{
			MessageBox( NULL, "请选择相机!","VR-GIS",MB_OK );

			return false;
		}

		vgCam::ViewCam from;

		vgCam::ViewCam *to = (vgCam::ViewCam *)renderer;

		from.cloneCurrentCameraView();
		to->setToUnvisible();

		vgCam::CamManager::getSingleton().getCurrentCameraRecord()->switchCamera(&from,to);
		//vgCam::CamManager::getSingleton().ImmediateToViewCam(to);// 静态直接跳转



		vgKernel::SelectManager::getSingleton().clearSelection();

		return true;
	}
	//----------------------------------------------------------------
	bool CamFacade::gotoObject( const String& obj_name )
	{
		vgKernel::Renderer* pRenderer = 
			vgKernel::RendererManager::getSingleton().getRendererbyName( obj_name );

		if ( pRenderer == NULL )
		{
			return false;
		}

		return gotoRenderer( pRenderer );
	}
	//----------------------------------------------------------------
	bool CamFacade::playVCR( const String& name )
	{
		vgCam::CameraRecord* pVCR = 
			vgCam::CamManager::getSingleton().getCameraRecordByName(name);

		if (pVCR != NULL )
		{
			vgCam::CamManager::getSingleton().setCurrentCameraRecord(pVCR);

			vgCam::CamManager::getSingleton().getCurrentCameraRecord()->startPlaying();

			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	bool CamFacade::stopVCR( const String& vcrname )
	{
		vgCam::CameraRecord* pVCR = vgCam::CamManager::getSingleton().getCameraRecordByName(vcrname);

		if (pVCR != NULL )
		{
			vgCam::CamManager::getSingleton().setCurrentCameraRecord(pVCR);
			int nowframenum=vgCam::CamManager::getSingleton().getCurrentCameraRecord()->uiFrame;
			vgCam::CameraRecord* nowVCR=vgCam::CamManager::getSingleton().getCurrentCameraRecord();
			vgCam::CamManager::getSingleton().setPosByCurVcrSpecificFrame(nowframenum);

			vgCam::CamManager::getSingleton().getCurrentCameraRecord()->stopPlaying();

			return true;
		}
		return false;
	}
	//----------------------------------------------------------------
	bool CamFacade::continueVCR( const String& vcrname )
	{
		vgCam::CameraRecord* pVCR = vgCam::CamManager::getSingleton().getCameraRecordByName(vcrname);

		if (pVCR != NULL )
		{
			vgCam::CamManager::getSingleton().setCurrentCameraRecord(pVCR);

			vgCam::CamManager::getSingleton().getCurrentCameraRecord()->continuePlaying();

			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	bool CamFacade::stopVCRSeries( )
	{
		vgCam::CameraRecord* pVCR = vgCam::CamManager::getSingleton().getCurrentCameraRecord();

		assert(pVCR);
		if (pVCR != NULL )
		{
			pVCR->stopPlaying();

			return true;
		}

		return false;
	}

	//----------------------------------------------------------------
	bool CamFacade::continueVCRSeries( )
	{
		vgCam::CameraRecord* pVCR = vgCam::CamManager::getSingleton().getCurrentCameraRecord();

		if (pVCR != NULL )
		{
			pVCR->continuePlaying();

			return true;
		}

		return false;
	}
	//----------------------------------------------------------------
	bool CamFacade::accelerateVCR( const String& vcrname )
	{
		vgCam::CameraRecord* pVCR = 
			vgCam::CamManager::getSingleton().getCameraRecordByName(vcrname);

		if (pVCR != NULL )
		{
			vgCam::CamManager::getSingleton().setCurrentCameraRecord(pVCR);

			vgCam::CamManager::getSingleton().getCurrentCameraRecord()->acceleratePlaying();

			return true;
		}

		return false;

	}

	//----------------------------------------------------------------
	bool CamFacade::decelerateVCR( const String& vcrname )
	{
		vgCam::CameraRecord* pVCR = 
			vgCam::CamManager::getSingleton().getCameraRecordByName(vcrname);

		if (pVCR != NULL )
		{
			vgCam::CamManager::getSingleton().setCurrentCameraRecord(pVCR);

			vgCam::CamManager::getSingleton().getCurrentCameraRecord()->deceleratePlaying();

			return true;
		}

		return false;

	}






}// end of namespace vgCam
