



#ifndef __VGSOUNDBACKGROUND2_H__
#define __VGSOUNDBACKGROUND2_H__
#include <vgSound/vgSoundDefinition.h>

#include "vgSound3D.h"
#include <afxmt.h>
#include <vfw.h>
#include <Digitalv.h>
#include <vgkernel/vgkRenderer.h>
#include <vgKernel/vgkUniqueID.h>


namespace vgSound {


	//复制文件的函数
	//extern BOOL CommonCopyFile(CString SourceFileName, CString DestFileName);

	const vgKernel::RendererType RENDERER_TYPE_SOUNDBACK = 5032;

	class  VGSOUND_EXPORT SoundBackground : public vgKernel::Renderer
	{
		VGK_RENDERER_IN_DECLARE( SoundBackground )
		friend class SoundManager;
	public:
		SoundBackground();

		virtual ~SoundBackground()
		{
			if (b_play)
			{
				stopPlaying();
			}			
		}

	public:

		virtual void render()
		{

		}

		void writeToFile( CFile *file );
		void writeToFile(vgKernel::StreamWriterPtr	file );

		void readFromFile( CFile *file );
		void readFromFile(vgKernel::StreamReaderPtr	file );

		

		String getFilePath(){ return filepath; }

		void reset();
		 
		void startPlaying();

		void stopPlaying();

		bool getPlayFlag(){ return b_play; }

		void setPlayFlag( bool play )
		{ 
			b_play = play; 
			this->notifyOberversOnEvent(vgKernel::VG_OBS_PROPCHANGED, NULL);
		}

		String getSoundName(){ return m_name; }

		// Renderer
		virtual String getName(){return m_name;} 

		virtual String* getNamePtr() {return &m_name;}

		virtual void setName( const String& newname ){ m_name = newname  ;}
		virtual vgKernel::UniqueID getUniqueID() { return _uniqueID;}

		virtual void moveTo(const float& x, const float& y, const float& z) {};

		virtual void translate(const float& x, const float& y, const float& z){};

		virtual void rotateSelf(const float& angle, const float& x, const float& y, const float& z) {};

		virtual void scale(const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z) {};

		virtual void rotate(const float& angle, const float& cx, const float& cy, const float& cz, 
			const float& x, const float& y, const float& z) {};


		virtual std::pair<bool, float> testIntersectWithTriangles( 
			const vgKernel::Ray& ray ) { std::pair<bool, float> testResult; return testResult;};

		virtual vgKernel::Box getBoundingBox() { return vgKernel::Box(); };

		virtual long getNumOfTriangles() { return 0;}

		/**
		注意,返回的是Distance的平方
		*/
		virtual float setDistanceToViewer( const vgKernel::Vec3& viewer_pos  ) { return 0;}


		void setFilePath(  const String &pp )	{ 	filepath = pp ;	}
	private:

		bool b_play;

		String filepath;

		String m_name;
		String m_nodeName;
		vgKernel::UniqueID	_uniqueID;
//////////////////////////////////////////////////////////////////////////

		MCI_DGV_OPEN_PARMS   mciOpen;   
		MCI_DGV_PLAY_PARMS   playParam; 		

		UINT wDeviceID;

	};

	VGK_RENDERER_OUT_DECLARE( SoundBackground )


}




#endif // end of __VGSOUNDBACKGROUND_H__