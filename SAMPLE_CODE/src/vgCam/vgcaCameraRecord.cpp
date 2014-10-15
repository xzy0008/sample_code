



#include <vgStableHeaders.h>
#include <vgCam/vgcaCameraRecord.h>
#include <vgCam/vgcaCamManager.h>
#include <vgCam/vgcaRecordAction.h>
#include <vgKernel/vgkWriteUtility.h>
#include <vgKernel/vgkStringUtility.h>

namespace vgCam {

	VGK_RENDERER_IMPLEMENT( CameraRecord,RENDERER_TYPE_CAMRECORD )

	CameraRecord::CameraRecord(void)
	{
		b_load=false;
		b_play=false;//开始状态不播放
		b_pause=false;//也不暂停
	//	bFirstTime=true; 
		uiFrame=0;
		uiLastFrame=0;
		fLastTime=0;
		b_record=false;
		fTime=0;
		_uniqueID =vgKernel::UniqueIDFactory::getUniqueID();
		frameptr=NULL;
		frame_time=NULL;
		b_KeyVcr=false;
		offset_vcr=Vec3(0,0,0);
		_visible=false;

		_startPlayingFlag = false;
		b_playratio=1.0;
	}

	void CameraRecord::init()
	{
		b_load=false;
		b_play=false;
		uiFrame=0;
		uiLastFrame=0;
		fLastTime=0;
		b_record=false;
		fTime=0;
		frameptr=NULL;
		frame_time=NULL;
		b_KeyVcr=false;
		b_playratio=1.0;
	}

	CameraRecord::~CameraRecord(void)
	{
		if(frameptr)delete []frameptr;
		frameptr=NULL;
		if(frame_time)delete []frame_time;
		frame_time=NULL;
			
	}
	void CameraRecord::loadVCR( const String& filename )
	{
		const char* szFilename = filename.c_str();

		unsigned char * ucpBuffer = 0;
		unsigned char * ucpPtr = 0;
		FILE * f = fopen(szFilename, "rb");
		if(!f)
		{
			//APP->Log(COLOR_RED, "Could not open %s", szFilename);
			//assert(0);
			return ;
		}

		m_vcrFilePath = szFilename;
		m_vcrFileName = vgKernel::StringUtility::getFilenameFromAbsolutePath(m_vcrFilePath);

		fseek(f, 0, SEEK_END);
		int iEnd = ftell(f);
		fseek(f, 0, SEEK_SET);
		int iStart = ftell(f);
		unsigned int uiSize = iEnd - iStart;

		ucpBuffer = new unsigned char[uiSize];
		ucpPtr = ucpBuffer;
		if(!ucpBuffer)
		{
			//APP->Log(COLOR_RED, "Could not allocate memory");
			return ;
		}
		//Read file into buffer
		if(fread(ucpBuffer, 1, uiSize, f) != uiSize)
		{
			//APP->Log(COLOR_RED, "Could not read %s", szFilename);
			delete [] ucpBuffer;
			return ;
		}

		fclose(f);

		//Check out the header, it should be 10 bytes, MS3D000000
		if(memcmp(ucpPtr, "VGCAMTRACK", 10) != 0)
		{
			//APP->Log(COLOR_RED, "%s is not a valid Milkshape 3D file", szFilename);
			delete [] ucpBuffer;
			return ;
		}
		ucpPtr += 10;

		framenum = *(long *)ucpPtr;//从指针所指地址处取数值

		if ( framenum <= 0 )
		{
			assert(0);
		}

		ucpPtr += 4;

		fps = *(long *)ucpPtr;//从指针所指地址处取数值
		//fps=3;//为了检验差值效果特此设慢了。
		ucpPtr += 4;

		m_fTotalTime=(framenum-1)/fps;

		frameptr = new VCRFrame[framenum];

		memcpy(frameptr, ucpPtr, framenum * sizeof(VCRFrame));

#if 0
		bool isold = true;
		for ( int i = 0 ; i < framenum ; ++ i )
		{
			if ( frameptr[i]._head != 0 )
			{
				isold = false;
				break;
			}
		}

		if ( isold == true )
		{
			for ( int i = 0 ; i < framenum ; ++ i )
			{
				float hhh = frameptr[i].getQuat().getHeadDegrees();

				frameptr[i]._head = hhh;
			}
			float hhh = last.qt.getHeadDegrees();
		}
#else
		for ( int i = 0 ; i < framenum ; ++ i )
		{
			float hhh = frameptr[i].getQuat().getHeadDegrees();

			frameptr[i]._head = hhh;
		}
#endif

		ucpPtr += framenum * sizeof(VCRFrame);

		b_load=true;

		delete [] ucpBuffer;
		
	}
	void CameraRecord::beginRecording()//开始录制
	{
		b_record=true;
		b_play=false;
		mVCRFrameList.clear();
	}
	void CameraRecord::pauseRecording()//暂停录制
	{
		b_record=false;//还可以继续录制
		b_play=false;
	}
	void CameraRecord::finishRecording()//结束录制
	{
		b_record=false;
		//应该做点跟pause不同的东西
		b_play=false;
	}
	void CameraRecord::recordVCRproc()//每帧捕获采集相机信息
	{
		if (b_record==true)
		{
			VCRFrame temp;
			temp.pos=vgCam::CamManager::getSingleton().getCurrentPosition();
			Quat PitchQuat,HeadQuat,CombineQuat;
			//////////////////////////////////////////////////////////////////////////
			//PitchQuat.createFromAxisAngle(1.0f, 0.0f, 0.0f, /*cam->*/vgCam::CamManager::getSingleton().getPitchDegrees());
			//HeadQuat.createFromAxisAngle(0.0f, 1.0f, 0.0f, /*cam->*/vgCam::CamManager::getSingleton().getHeadingDegrees());

			//// Combine the pitch and heading rotations and store the results in q
			//CombineQuat= PitchQuat * HeadQuat;

			CombineQuat.fromEulerAnglesDegree( 
				vgCam::CamManager::getSingleton().getPitchDegrees() , 
				vgCam::CamManager::getSingleton().getHeadingDegrees() , 
				0 );

			float fRadian;Vec3 axis;



			temp._head = vgCam::CamManager::getSingleton().getHeadingDegrees();


			
			CombineQuat.toRadianAxis(fRadian,axis);

			temp.qt.m_w=fRadian;//不要误解了，这些是临时方便用，并不代表其四元数真正含义
			temp.qt.m_x=axis.x;
			temp.qt.m_y=axis.y;
			temp.qt.m_z=axis.z;
			//////////////////////////////////////////////////////////////////////////
			mVCRFrameList.push_back(temp);
		}

	}


	void CameraRecord::saveVCR(  const String& filename )//录制结束后，进行保存	//最后一次写入
	{
		const char* szFilename = filename.c_str();
 		FILE * f = fopen(szFilename, "wb");
 		if(!f)
 		{
 			//APP->Log(COLOR_RED, "Could not open %s", szFilename);
 			return ;
 		}
		if(mVCRFrameList.empty())
			return;
		char tag[12]="VGCAMTRACK";
		fwrite(tag,10,1,f);
		long framenum=mVCRFrameList.size()-1;
		fwrite((const void *)&framenum,sizeof(framenum) ,1,f);
		long fps =30;
		fwrite((const void *)&fps,sizeof(fps),1,f);




		VCRFrameList::iterator iter=mVCRFrameList.begin();
		VCRFrameList::iterator iter_end=mVCRFrameList.end();
		for (long i=0 ; iter != iter_end ; ++iter )
		{
			iter->index=i;
			
 			fwrite((const void *)&(*iter),sizeof(VCRFrame),1,f);
			i++;
		}
 		fclose(f); 

	}
	void CameraRecord::startPlaying()
	{
		b_play=true;
		uiFrame=0;
		m_Timer.Init();
		fTime=0;

		_startPlayingFlag = true;
	}
	void CameraRecord::startPlayingByTime(float fAnytime/* = 0.0f*/)
	{
		b_play=true;
		uiFrame=0;
		m_Timer.Init();
		fTime=fAnytime;
	}
	void CameraRecord::startPlayingByFrame(long uiAnyFrame)
	{
		float	fAnyTime = getTimeWithFrame(uiAnyFrame);
		startPlayingByTime(fAnyTime);
	}
	float	CameraRecord::getTimeWithFrame(long uiAnyFrame)
	{
		return	uiAnyFrame/fps;
	}
	void CameraRecord::stopPlaying()
	{
		b_play=false;
		uiFrame=0;
		fTime=0;
	}
	void CameraRecord::continuePlaying()
	{
/*		b_play=true;
		if(uiLastFrame>=framenum-3)
		{
			uiFrame=0;
			m_Timer.Init();
			fTime=0;
			return;
		}
		else 
			uiFrame=uiLastFrame;
		m_Timer.Init();
		fTime=fLastTime;//这里的fTime需要设成上次暂停时候纪录的数值*/
 		b_play=true;
 		uiFrame=uiLastFrame;
 		m_Timer.Init();
 		fTime=fLastTime;//这里的fTime需要设成上次暂停时候纪录的数值
	}

	void CameraRecord::acceleratePlaying()
	{
		b_playratio *= 2.0;
	}

	void CameraRecord::deceleratePlaying()
	{
		b_playratio /= 2.0;
	}

	void CameraRecord::switchVisible()
	{
		_visible=!_visible;
	}

	void CameraRecord::playByFrame(int uiFrame)
	{

		last.pos = 
			frameptr[uiFrame].pos;

		//-----------------------------------------
		//begin四元数插值，是对生成的四元数插值，插值之后也就是四元数了
		//-----------------------------------------
		last.qt = frameptr[ uiFrame ].getQuat();

		last.qt.normalize();


		float ddd = frameptr[0].getQuat().getPitchDegrees();

		float ppp = last.qt.getPitchDegrees();
		float hhh = last.qt.getHeadDegrees();

		vgCam::CamManager::getSingleton().setModelViewMatrix(
			last.pos+offset_vcr,last.qt.getPitchDegrees() ,
			last.qt.getHeadDegrees() );

		return;
	}

	void CameraRecord::playVCRproc()
	{
		if (vgCam::CamManager::getSingleton().getAviRecordCnt() != 0)
		{
			//float time;
			//TRACE("FrameId = %d \n", framenum - vgCam::CamManager::getSingleton().getAviRecordCnt());
			playByFrame(framenum - vgCam::CamManager::getSingleton().getAviRecordCnt());
			// playByTime()
			return ;
		}

		if ( framenum <= 0)
		{
			assert(0);
		}

		if ( !( b_load&&b_play&&b_pause==false) )//载入了，没有暂停，且处于播放状态
		{	
			return;
		}

		if (b_KeyVcr)	
		{
			fps = frame_time[uiFrame];//多段播放时候，fps不同，即时计算1.0 /frame_time[uiFrame]
		}
		//----------------------------------------------------------------
		if ( _startPlayingFlag == true )
		{
			_startPlayingFlag = false;
			m_Timer.Init();
			fTime = 0;

			doActionByActionType( RecordActionType_start );
		}
		//----------------------------------------------------------------

		fTime += m_Timer.GetSeconds() * fps * b_playratio;//当前所播放到的时间点
		fLastTime=fTime;
		float inter=fTime;
		uiFrame=floor(inter);
		uiLastFrame=uiFrame;
		float factor=(inter-uiFrame);

		assert( factor >= 0.0f );
		assert( factor <= 1.0f );

		if( uiFrame < framenum - 3 )
		{				
			//对uiFrame，inter，和uiFrame＋三者进行差值运算！
			last.pos = 
				frameptr[uiFrame].pos + factor * (frameptr[uiFrame+1].pos-frameptr[uiFrame].pos);

			//-----------------------------------------
			//begin四元数插值，是对生成的四元数插值，插值之后也就是四元数了
			//-----------------------------------------


			//默认采用小圆弧进行差值
			float aaa = abs(frameptr[uiFrame]._head - frameptr[uiFrame+1]._head);

			if (aaa > 180.0f)
			{
				if (frameptr[uiFrame]._head < frameptr[uiFrame+1]._head)
				{
					frameptr[uiFrame]._head += 360.0f;
				}
				else
				{
					frameptr[uiFrame+1]._head += 360.0f;
				}
			}



			last.qt= Quat::slerp( factor , 
				frameptr[ uiFrame ].getQuat() ,
				frameptr[ uiFrame + 1].getQuat() );

			//------------------------------------------
			// head进行插值
			//------------------------------------------
			last._head = frameptr[ uiFrame ]._head + 
				(frameptr[ uiFrame + 1]._head - frameptr[ uiFrame ]._head ) * factor;


			last.qt.normalize();


			float ddd = frameptr[0].getQuat().getPitchDegrees();

			float ppp = last.qt.getPitchDegrees();
			float hhh = last.qt.getHeadDegrees();

			if ( abs(last._head - 0.0f) > 1e-5 )
 			{
				if ( abs(hhh - last._head ) >= 5.0f )
				{
					hhh = last._head;
				}
			}


			vgCam::CamManager::getSingleton().setModelViewMatrix(
				last.pos+offset_vcr,last.qt.getPitchDegrees() ,
				hhh );

			return;

		}

		//------------------------------------------
		// 执行到末尾时, 只执行一次 
		//------------------------------------------
		last  = frameptr[framenum-3];
		fTime=0;
		b_play = false;


		//float dddddd = last.getQuat().getHeadDegrees();

		vgCam::CamManager::getSingleton().setModelViewMatrix(
			last.pos+offset_vcr,last.getQuat().getPitchDegrees() ,
			last.getQuat().getHeadDegrees() );


		vgCam::CamManager::getSingleton().setDefaultCamRecordPtr();

		//------------------------------------------
		// 开始执行finish事件.
		//------------------------------------------
		doActionByActionType( RecordActionType_finish );	

		return;
	}

	void CameraRecord::switchCamera(ViewCam *from,ViewCam *to, float _time, int frame)//相机切换2008.10.28
	{

		b_load=true;b_play=true;//enable play VCR

		framenum =4;//从指针所指地址处取数值

		fps = (framenum - 1) / _time;//从指针所指地址处取数值

		uiFrame=0;

		frameptr = new VCRFrame[framenum];


		frameptr[0].pos=from->getPosition();
		frameptr[1].pos=to->getPosition();
		frameptr[2].pos=to->getPosition();
		frameptr[3].pos=to->getPosition();

		//////////////////////////////////////////////////////////////////////////
		float radian1,radian2;
		
		Vec3 v1,v2;


		from->_tmpQuaternionPitch.createFromAxisAngle(1.0f, 0.0f, 0.0f, from->getPitchDegrees());
		from->_tmpQuaternionHeading.createFromAxisAngle(0.0f, 1.0f, 0.0f, from->getHeadingDegrees());
		from->_combinedQuaternion = from->_tmpQuaternionPitch * from->_tmpQuaternionHeading;
		from->_combinedQuaternion.toRadianAxis(radian1,v1);

		to->_tmpQuaternionPitch.createFromAxisAngle(1.0f, 0.0f, 0.0f,to->getPitchDegrees());
		to->_tmpQuaternionHeading.createFromAxisAngle(0.0f, 1.0f, 0.0f,to->getHeadingDegrees());
		to->_combinedQuaternion = to->_tmpQuaternionPitch * to->_tmpQuaternionHeading;
		to->_combinedQuaternion.toRadianAxis(radian2,v2);



		frameptr[0]._head = from->getHeadingDegrees();
		frameptr[1]._head = to->getHeadingDegrees();
		frameptr[2]._head = to->getHeadingDegrees();
		frameptr[3]._head = to->getHeadingDegrees();


		frameptr[0].qt=/**new */Quat(v1,radian1);
		frameptr[1].qt=/**new */Quat(v2,radian2);
		frameptr[2].qt=/**new */Quat(v2,radian2);
		frameptr[3].qt=/**new */Quat(v2,radian2);

		if (frame == 0)
		{
			m_Timer.Init();//启动
		}

	}

	void CameraRecord::switchCamera(ViewCam *from,ViewCam *to)//相机切换
	{
		createFromSwitchingViewCam( from , to );

		b_play=true;//enable play VCR
		m_Timer.Init();//启动
	}

	void CameraRecord::render()
	{
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_1D);
		glDisable(GL_DEPTH_TEST);

		glColor3f(100,0,0);

		if(framenum>0)
		{
			glBegin(GL_LINE_STRIP);
			for(int dnum=0;dnum<framenum-1;dnum++)
			{
				glVertex3f(frameptr[dnum].pos.x+offset_vcr.x,frameptr[dnum].pos.y+offset_vcr.y,frameptr[dnum].pos.z+offset_vcr.z);
			}
		}


		glEnd();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_1D);
		glEnable(GL_TEXTURE_2D);
		glPopAttrib();
		glPopMatrix();
	}


	void CameraRecord::reset()
	{
		if(frameptr)
		{
			delete []frameptr;
			frameptr=NULL;
		}
		if(frame_time)
		{
			delete []frame_time;
			frame_time=NULL;
		}
		mVCRFrameList.clear();

		b_load=false;
		b_play=false;//开始状态不播放
		b_pause=false;//也不暂停
		//	bFirstTime=true; 
		uiFrame=0;
		uiLastFrame=0;
		fLastTime=0;
		b_record=false;
		fTime=0;

		frameptr=NULL;
		frame_time=NULL;
		b_KeyVcr=false;
		offset_vcr=Vec3(0,0,0);

		framenum = 0;

		_startPlayingFlag = false;
		b_playratio=1.0;

		return;
	}

	void CameraRecord::createFromSwitchingViewCam( ViewCam *from, ViewCam *to )
	{
		//------------------------------------------
		// 重置当前相机
		//------------------------------------------
		reset();


		b_load=true;
		framenum =4;//从指针所指地址处取数值

		fps = 1;//从指针所指地址处取数值


		m_fTotalTime=(framenum-1)/fps;
		uiFrame=0;

		assert( frameptr == NULL );
		frameptr = new VCRFrame[framenum];


		frameptr[0].pos=from->getPosition();
		frameptr[1].pos=to->getPosition();
		frameptr[2].pos=to->getPosition();
		frameptr[3].pos=to->getPosition();


		Quat fromquat;
		fromquat.fromEulerAnglesDegree( from->getPitchDegrees() , from->getHeadingDegrees() , 0 );

		Quat toquat;
		toquat.fromEulerAnglesDegree( to->getPitchDegrees() , to->getHeadingDegrees() , 0 );


		frameptr[0]._head = from->getHeadingDegrees();
		frameptr[1]._head = to->getHeadingDegrees();
		frameptr[2]._head = to->getHeadingDegrees();
		frameptr[3]._head = to->getHeadingDegrees();



		frameptr[0].setQuat( fromquat );
		frameptr[1].setQuat( toquat );
		frameptr[2].setQuat( toquat );
		frameptr[3].setQuat( toquat );

		//float bbsd = to->getPitchDegrees();

		//float bbbbb = toquat.getPitchDegrees();

		return;
	}

	bool CameraRecord::readFromStream( vgKernel::StreamReaderPtr preader, int version, const String& version_info )
	{
		char strBuffer[200];
		preader->read( strBuffer, 200 );
		m_vcrFileName = String(strBuffer);

		preader->read( strBuffer, 200 );
		_ViewCamName = String(strBuffer);

		preader->read( &b_load, sizeof(bool) );
		preader->read( &b_record, sizeof(bool) );
		preader->read( &b_play, sizeof(bool) );	

		// 其他
		//读出偏移.2.12版本对偏移的支持
		//String	vgVersion = vgGlobal::GlobalFacade::getSingleton().getVgVersionRead();
		//if( vgVersion >= String("VRGIS.VERSION 2.12") )
		//{
		preader->read( &offset_vcr.x, sizeof(float) );	
		preader->read( &offset_vcr.y, sizeof(float) );	
		preader->read( &offset_vcr.z, sizeof(float) );	
		//}

		return true;
	}

	bool CameraRecord::writeToStream( vgKernel::StreamWriterPtr pwriter, int version, const String& version_info )
	{
		m_vcrFileName = 
			vgKernel::StringUtility::getFilenameFromAbsolutePath(m_vcrFilePath);

#define  BUF_SIZE  200

		VGK_STREAM_WRITESTR_ASSERT( pwriter , m_vcrFileName , BUF_SIZE );
		VGK_STREAM_WRITESTR_ASSERT( pwriter , _ViewCamName , BUF_SIZE );

		//pCfile->Write( _ViewCamName.c_str(), BUF_SIZE );

		pwriter->write( &b_load, sizeof(bool) );
		pwriter->write( &b_record, sizeof(bool) );
		pwriter->write( &b_play, sizeof(bool) );	
		// 其他
		// 写进偏移
		pwriter->write( &offset_vcr.x, sizeof(float) );	
		pwriter->write( &offset_vcr.y, sizeof(float) );	
		pwriter->write( &offset_vcr.z, sizeof(float) );

		return true;
	}
	//end of namespace
};
