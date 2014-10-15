


#ifndef __VGSOSOLARANALYSIS_H__
#define __VGSOSOLARANALYSIS_H__




#include <vgSolar/vgsoDefinition.h>

#include <vgKernel/vgkForward.h>
#include <vgKernel/vgkVec3.h>
#include <vgSolar/vgsoDateTimeAndLocation.h>
#include <vgKernel/vgkInputSystem.h>

	
namespace vgSolar {


	typedef std::vector<vgKernel::Vec3> Vec3Vector;

	/**
		@date 	2009/04/22  14:11	
		@author  leven
	
		@brief 	
	
		@see    
		*/
	class SolarAnalysis : public vgKernel::InputHandler
	{
	public:
		SolarAnalysis( vgSolar::DateTimeAndLocation date, 
			float begin_hour , float end_hour );
		virtual ~SolarAnalysis();

		virtual void OnMouseMove(UINT nFlags, CPoint position);
		virtual void OnLButtonDown(UINT nFlags, CPoint position);
		virtual void OnLButtonUp(UINT nFlags, CPoint position);
		virtual void OnLButtonDbClick(UINT nFlags, CPoint position);

		void render();


	private:

		void calcuateOnce();

		void clearStencilAndRenderOnce();
		void renderResults();


		// 根据DateAndLoc信息进行计算lightdirs
		void makeLightDirections();

		void invalidate();

		static void drawPoint( const vgKernel::Vec3& point );
		vgKernel::Vec3 get3dVecFrom2d( const CPoint& point_2d );

	private:

		vgKernel::Vec3 _mouseVec;
		
		// 当光线的length为0的时候，表示太阳没出来
		Vec3Vector _lightDirs;

		GLuint _resultTextureID;

		bool _calcuatedAlready;

		vgSolar::DateTimeAndLocation _nowLocation;

		int _viewSizeWidth;
		int _viewSizeHeight;

		float* _floatBuffer;

		int* _intBuffer;

		int _beginHour;
		int _beginMin;
		int _endHour;
		int _endMin;

	};
	
	
}// end of namespace vgSolar
	


#endif // end of __VGSOSOLARANALYSIS_H__