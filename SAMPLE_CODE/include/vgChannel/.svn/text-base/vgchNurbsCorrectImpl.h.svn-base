#pragma once
#include <vgConfig/vgcXMLConfigManager.h>

#include "vgChannel/vgNurbsParamDlg.h"
#include <stack>


namespace vgChannel
{
	typedef struct CtrlPt_t
	{
		float x;
		float y;
		float z;
		float w;
	}CtrlPt;
	
	typedef struct FrustumVal_t
	{
		float left;
		float right;
		float top;
		float bottom;
	}FurstumVal;

	class NurbsCorrectImpl
	{
	public:

		NurbsCorrectImpl();		//@FengYK	2009/10/31 10:32
		~NurbsCorrectImpl();
		
		void initNurbs();
		void initXmlParams();	//@FengYK	2009/10/31 10:32

		bool blendPixel();
		
		CtrlPt getControlPoint(int x, int y);
		FurstumVal getFrustumVal();

		void setControlPoint(int x, int y, CtrlPt pt);
		void setFrustum(FurstumVal fval);
		bool recomplieCallList();

		bool NurbsLittleCorrect();
		bool MoveContrlPoint(vgKernel::Vec3 click_point);
		void GetCorrectParam(float param1, float param2 );
		void Ifchose(vgKernel::Vec3 click_point);
		bool IfFrustumPoint(vgKernel::Vec3 click_point);
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();

		bool getLittleCorrectEnable() { return m_nurbsLittleCorrectEnable; }
		void setLittleCorrectEnable(bool b);

		void SetparamToXml();	//@FengYK 2009/10/31 10:35
		bool ReadCtrlInfer();
		void SetCtrlPointToSave();
		void  SetParamkeyToXml();
		void SetparamValueToXml();
		void GetCtrlKey();
		CString TurnFloatToCstr(float floatValue);
		void SavePramaToXml();
		void ReturnToOriPrama();

	private:
		bool  m_nurbsLittleCorrectEnable;

		// 裁剪面计算信息
		float m_top;
		float m_bottom;
		float m_left;
		float m_right;

		float m_nearOS;		
		float m_width;
		float m_height;
		float m_theta;

		CPoint index;

		GLUnurbs* m_nurb;
		float m_correctparam;
		float m_clipplane;

		float fps_dx;
		float fps_dy;

		bool ifLoadIn;	//@FengYK	2009/10/31	10:38
	

		// 控制点坐标
		float m_cps[3][3][4];
		float Xml_cps[3][3][4];//@FengYK	2009/10/31	10:38
		//裁剪面微调的对应点坐标
		vgKernel::Vec3 m_fps;//???????????
		// 纹理控制点坐标
		// float m_tps[3][3][2];
		std::stack<CPoint>   m_pointInChoose;

		CString Xmlfilename ;	//@FengYK	2009/10/31	10:38
		CString Xmlsectionname ;
		CXmlProfile m_Profile;
		CString str_FileName;
		// 显示列表优化
		GLuint m_callListId;

		vgConfig::SectionData parameValue;	//@FengYK	2009/10/31	10:38
		std::vector<CString> CtrlPointValue;
		std::vector<CString> ParamKeyName;
		std::vector<CString> Newkeyvalue;
		std::vector<CString> CtrlpointKey;
	};	
}