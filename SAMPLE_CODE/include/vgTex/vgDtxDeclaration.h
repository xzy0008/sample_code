


#ifndef __VGDTXDECLARATION_H__
#define __VGDTXDECLARATION_H__

#include <vgKernel/vgkSharePtr.h>

	/**
	@date 	2009/05/22  8:34	
	@author  YUXIN

	@brief 	

	@see    
	*/


#define  DTX_FILENAME_LENGTH 64
#define  DTX_FILEPATH_LENGTH 256

	class DtxHeader
	{
	public:
		DtxHeader()
		{
			setDefault();
		}
		~DtxHeader()
		{

		}

	public:
		int		framecount;
		long	totaltime;
		int		ratio;

	private:
		void setDefault()
		{
			framecount = 0;
			totaltime  = 0;
			ratio	   = 1;
		}

	};

	class SingleFrame 
	{
	public:
		SingleFrame()
		{
			setDefault();
		}
		~SingleFrame()
		{

		}

	public:

		int		frameId;
		long	timelength;
		char    filename[DTX_FILENAME_LENGTH];
	
	private:
		void setDefault()
		{
			frameId    = 0;
			timelength = 0;
			memset(filename, 0, DTX_FILENAME_LENGTH);
		}

	};


	class FrameInfor
	{
	public:
		FrameInfor()
		{
			setDefault();
		}
		~FrameInfor()
		{

		}

	public:

		SingleFrame  frame;
		char		 filepath[DTX_FILEPATH_LENGTH];
	
	private:
		void setDefault()
		{
			memset(filepath, 0, DTX_FILEPATH_LENGTH);
		}

	};

	typedef std::vector<SingleFrame> FrameVector;

	typedef vgKernel::SharePtr<FrameVector> FrameVectorPtr;
	
	typedef std::vector<FrameInfor> FrameInforVecor;

	typedef vgKernel::SharePtr<FrameInforVecor> FrameInforVectorPtr;


#endif // end of __VGKFRAMEVECTOR_H__