
#ifndef __VGSDKUTILITY_H__
#define __VGSDKUTILITY_H__


#include <vgSDK/vgSDKDefinition.h>
#include <vgKernel/vgkStringUtility.h>
#include <vgCam/vgcaCamManager.h>

namespace vgSDK{

	/**
	@date    2009/10/23  21:08
	@author  lss

	@brief   

	@see
	*/	


	class	 VGSDK_EXPORT SDKUtility
	{
	public:
		SDKUtility()	{}
		~SDKUtility()	{}

		// namespace vgCam
	public:
		static bool gotoCamera(string name);
		static bool immediateToViewCam( vgCam::ViewCam* viewCam );


		static bool	playVCR(string name);
		static bool	stopVCR( );
		static bool	continueVCR( );


		// namespace vgKernel
	public:

		// 设置多个物体的可见性
		static bool setStateVisible(vgKernel::StringVector& names, bool bState );

		// 设置单个物体的可见性
		static bool setStateVisbile( String name, bool bState ); 

		static void getNamesByPrefix(vgKernel::StringVector& prefixs,
			vgKernel::StringVector& findResultOut);
		static bool setState(vgKernel::StringVectorArr& allScheme, String labels, bool visible );
		static bool selectRenderersByNames(vgKernel::StringVector& names);
		static bool setRenderersTransparent(vgKernel::StringVector& renderers, bool tState );
		static void setPriority(string names, int nPriority);
		static void setRenderersPriority(vgKernel::StringVector& renderers, int nPriority);

		// 以下两个接口为碰撞检测相关
		static void setCollideEllipse( vgKernel::Vec3 vec );
		static void setCollideAheadRatio( float ratio );


		// 平移单个物体
		static void translate( String name, const vgKernel::Vec3& vec );

		//平移多个物体
		static void translate( vgKernel::StringVector& names, const vgKernel::Vec3& vec );



		// namespace vgMusic
	public:
		static bool turnOnMusic(bool bPlay);
		static bool turnOnSound3D(string sname, bool bsPlay, bool bsLoop);



	};

}//namespace vgSDK

#endif//__VGSDKUTILITY_H__
