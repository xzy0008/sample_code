


#include <vgStableHeaders.h>
#include <vgCam/vgcaViewCam.h>
#include <vgCam/vgcaCamManager.h>

#include <vgKernel/vgkWriteUtility.h>


namespace vgCam {
	
	VGK_RENDERER_IMPLEMENT( ViewCam,RENDERER_TYPE_VIEWCAMERA )
	
	ViewCam::ViewCam()
	{
		// Initalize all our member varibles.

		m_HeadingDegrees		= 0.0f;
		m_PitchDegrees			= 0.0f;
		m_ForwardVelocity		= 1.0f;

		_uniqueID =vgKernel::UniqueIDFactory::getUniqueID();

		_dynamicBox._maxVertex=m_Position+Vec3(0.5,0.5,0.5);
		_dynamicBox._minVertex=m_Position+Vec3(-0.5,-0.5,-0.5);

		setVisible( false );	
	}

	ViewCam::~ViewCam()
	{

	}


//-add
	void ViewCam::setCamData( const ViewCam& curcam )
	{
		this->m_Position		= curcam.m_Position;

		this->m_ForwardVelocity = curcam.m_ForwardVelocity;
		this->m_HeadingDegrees	= curcam.m_HeadingDegrees;
		this->m_PitchDegrees	= curcam.m_PitchDegrees;
	}
	//----------------------------------------------------------------
	void ViewCam::setFov(float fovpar)//适用于对称视景体,tan是角度还是弧度，有待于再验
	{
		m_up=m_near*tan(fovpar/2);
		m_down=-m_near*tan(fovpar/2);
		m_left=m_down/m_aspectratio;
		m_right=-m_left;
	}
	void ViewCam::setAspectRatio(float aspectratiopar)//适用于对称视景体
	{
		m_left=m_down/m_aspectratio;
		m_right=m_up/m_aspectratio;
	}

	void ViewCam::setNear(float nearpar)
	{
		m_near=nearpar;
	}
	void ViewCam::setFar(float farpar)
	{
		m_far=farpar;
	}
	void ViewCam::setViewport(float leftpar,float rightpar,float uppar,float downpar)
	{
		m_left=leftpar;
		m_right=rightpar;
		m_up=uppar;
		m_down=downpar;
	}
	void ViewCam::flushData()
	{
		_dynamicBox._maxVertex=m_Position+Vec3(3,3,3);
		_dynamicBox._minVertex=m_Position+Vec3(-3,-3,-3);


	}
	void ViewCam::setupViewFrustum()
	{
		glFrustum(m_left,m_right,m_up,m_down,m_near,m_far);
	}
	//----------------------------------------------------------------

	void ViewCam::renderViewCamEntity()
	{
		//if (m_isVisible)
		{

			glDisable(GL_TEXTURE_2D);
			glPushMatrix();
			glTranslatef(getPosition().x, getPosition().y, getPosition().z);
			glTranslatef(0.0,0.0,-3.0);
			glColor3f(0.0,0.9,0.9);
			auxSolidCone(2,3);
 			glTranslatef(0.0,0.0,5.0);
 			auxSolidBox(4,4,4);
			glPopMatrix();
			glEnable(GL_TEXTURE_2D);
		}


	}
	void ViewCam::cloneCurrentCameraView()
	{
		setPosition(vgCam::CamManager::getSingleton().getCurrentPosition());
		setPitchDegrees(vgCam::CamManager::getSingleton().getPitchDegrees());
		setHeadingDegrees(vgCam::CamManager::getSingleton().getHeadingDegrees());
		setForwardVelocity(vgCam::CamManager::getSingleton().getForwardVelocity());


		//未完待续
		flushData();

	}


	float ViewCam::setDistanceToViewer( const Vec3& viewer_pos )
	{
		//------------------------------------------
		// 1.首先通过包围盒计算与视点的距离.
		//------------------------------------------
		float delta[3];

		for ( int i = 0 ; i < 3 ; ++ i )
		{
			float _cur = viewer_pos[i];
			float _max = _dynamicBox._maxVertex.v[i];
			float _min = _dynamicBox._minVertex.v[i];

			if ( _cur > _max )
			{
				delta[i] = _cur - _max;
			}
			else if ( _cur < _min )
			{
				delta[i] = _min - _cur;
			}
			else
			{
				delta[i] = 0.0f;
			}
		}

		_squaredDistanceToViewer = 
			delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];
		return _squaredDistanceToViewer;
	}




	bool ViewCam::readFromStream( vgKernel::StreamReaderPtr preader, int version, const String& version_info )
	{
		char strBuffer[200];
		preader->read( strBuffer, 200 );
		_ViewCamName = String(strBuffer);

		preader->read( &m_Position, sizeof(Vec3) );

		preader->read( &m_HeadingDegrees, sizeof(float) );
		preader->read( &m_PitchDegrees, sizeof(float) );	

		preader->read( &m_ForwardVelocity, sizeof(float) );
		preader->read( &m_PitchVelocity, sizeof(float) );
		preader->read( &m_TurningVelocity, sizeof(float) );	
		// 其他

		return true;
	}

	bool ViewCam::writeToStream( vgKernel::StreamWriterPtr pwriter, int version, const String& version_info )
	{
#define  BUF_SIZE  200

		VGK_STREAM_WRITESTR_ASSERT( pwriter , _ViewCamName , BUF_SIZE );


		pwriter->write( &m_Position, sizeof(Vec3) );

		pwriter->write( &m_HeadingDegrees, sizeof(float) );
		pwriter->write( &m_PitchDegrees, sizeof(float) );	

		pwriter->write( &m_ForwardVelocity, sizeof(float) );
		pwriter->write( &m_PitchVelocity, sizeof(float) );
		pwriter->write( &m_TurningVelocity, sizeof(float) );	
		// 其他

		return true;
	}

	std::pair<bool, float> ViewCam::testIntersectWithTriangles( const vgKernel::Ray& ray )
	{
		std::pair<bool, float> result = std::make_pair(false, 0.0f );
		return result;
	}
}// end of namespace vgCam
