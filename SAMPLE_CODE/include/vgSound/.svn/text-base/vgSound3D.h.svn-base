


#ifndef __VG3DSOUND_H__
#define __VG3DSOUND_H__


#include <vgSound/vgSoundDefinition.h>

//#include <vgPrerequisites.h>

#include <vgKernel/vgkForward.h>
#include <mmsystem.h>
#include <dsound.h>
#include "vgSound3DWaveHeader.h"



#include <vgKernel/vgkRendererObserver.h>
#include <vgkernel/vgkRenderer.h>
#include <vgKernel/vgkUniqueID.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkStreamReader.h>
#include <vgKernel/vgkStreamWriter.h>



namespace vgSound {

	/*
	5010 -- 5030之间为QuadTreeSceneMananger的管辖范围之内
	*/
	const vgKernel::RendererType RENDERER_TYPE_SOUND = 5031;


	class  VGSOUND_EXPORT Sound3D :public vgKernel::Renderer
	{
		VGK_RENDERER_IN_DECLARE( Sound3D )
		friend class SoundManager;
	public:
		Sound3D();
		virtual ~Sound3D();
	public:

		virtual void render()
		{

		}

		
		//void Render();
		bool loadWaveFile(String szWaveFile);
		bool startPlaying(bool bLoop);
		bool setVolume(long lVolume=DSBVOLUME_MAX);
		bool setSoundPos(float x,float y,float z);
		bool setSoundPram(float fMinDistance,float fMaxDistance);
		bool stopPlaying();
		bool setAbsolutePos( float x, float y, float z );
	
		void writeToFile( CFile *file );
		void writeToFile(vgKernel::StreamWriterPtr pfile);

		void readFromFile( CFile *file);
		void readFromFile(vgKernel::StreamReaderPtr pfile);

		void setPlayFlag( bool play ){ b_play = play; }

		bool getPlayFlag(){ return b_play; }

		void setPlayState( bool play )
		{ 
			b_play = play; 
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}

		bool getPlayState(){ return b_play; }
		
		vgKernel::Vec3 getSoundPos()
		{
			return m_AbsolutePosition;
		}	

		float getAttenuation()
		{
			return m_shuaijian;
		}

		void setAttenuation( float attent )
		{
			m_shuaijian = attent;
		}

		
		String getWavePath( ){ return m_wavepath; }


	public:
		virtual String getName(){return m_name;} 

		virtual String* getNamePtr() {return &m_name;}

		virtual void setName( const String& newname ){ m_name = newname  ;}

		virtual vgKernel::UniqueID getUniqueID(){return _uniqueID;} ;

		virtual void translate(const float& x, const float& y, const float& z)
		{
			m_AbsolutePosition.x += x;

			m_AbsolutePosition.y += y;

			m_AbsolutePosition.z += z;

			GenBoundaryBox( m_AbsolutePosition );

			this->notifyOberversOnEvent(vgKernel::VG_OBS_SELECTCHAGNED, NULL);
		} ;

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z) {};

		virtual void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z){} ;

		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z){} ;


		virtual std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray ) 
		{
			std::pair<bool, float> result = vgKernel::Math::intersects( ray, _dynamicBox );
			return result;
		}

		virtual vgKernel::Box getBoundingBox() { return _dynamicBox;}

		virtual long getNumOfTriangles() {return 0;}

		/**
		注意,返回的是Distance的平方
		*/
		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  ) 
		{return 0;}

		void setWavePath( const String &path){ m_wavepath = path; }
		void GenBoundaryBox( vgKernel::Vec3 &pp);

		bool GetSecondaryBuffer(FILE* fp);
		bool LoadDataInBuffer(FILE *fp);
	private:
		IDirectSoundBuffer *m_pDirectSoundBuf;

		IDirectSound3DBuffer8 *pDirectSound3DBuf8;

		DS3DBUFFER              dsBufferParams;



		vgKernel::Vec3 m_RelativePosition;

		vgKernel::Vec3 m_AbsolutePosition;

		float m_shuaijian;

		String m_wavepath;

		String m_name;

		vgKernel::UniqueID _uniqueID;

		vgKernel::Box _dynamicBox;

		bool b_play;
	};

	VGK_RENDERER_OUT_DECLARE( Sound3D )

	typedef vgKernel::SharePtr<Sound3D> Sound3DPtr;
	typedef std::vector<Sound3DPtr> Sound3DPtrVec;

}

#endif // end of __VG3DSOUND_H__
