#include <vgStableHeaders.h>
#include <vgChannel/vgchNurbsCorrectImpl.h>
#include <vgConfig/vgcXMLConfigManager.h>

#ifndef PI 
#define PI 3.1415926
#endif

namespace vgChannel
{
	// stack <CPoint>   Pointinchose;

	NurbsCorrectImpl::NurbsCorrectImpl()
		: ifLoadIn(false), m_correctparam(0.005), m_clipplane(0.0)
	{

		m_nurb = gluNewNurbsRenderer();
		gluNurbsProperty(m_nurb, GLU_SAMPLING_TOLERANCE, 32.0);
		gluNurbsProperty(m_nurb, GLU_DISPLAY_MODE, GLU_FILL);
		gluNurbsProperty(m_nurb, GLU_CULLING, GL_TRUE);
		
		m_callListId = GL_INVALID_VALUE;

		CString strExtension = _T(".xml");

		char exebuf[512];
		DWORD getret = GetModuleFileName( NULL , exebuf , 512 );

		assert( getret < 512 );
		assert( getret > 0 );

		String exestr( exebuf );
		String exepath = exestr.substr( 0 , 
			exestr.find_last_of("\\/")  + 1);

		CString path;
		path.Format("%s", exepath.c_str());

		Xmlfilename =  _T("Channel");		//@FengYK	2009/10/31 10:21
		str_FileName = path + Xmlfilename + strExtension ;
		Xmlsectionname = _T("Geometric correction Configuration");	

		ifLoadIn = vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(str_FileName);
		if (ifLoadIn&&vgConfig::XMLConfigManager::getSingleton().FindSection(Xmlsectionname))
		{			
			initXmlParams();
		}
		else
		{
			initNurbs();
		}

		m_callListId = glGenLists(1);
		recomplieCallList();///??????????????????????

		m_nurbsLittleCorrectEnable = false;
	}

	NurbsCorrectImpl::~NurbsCorrectImpl()
	{
		if (m_callListId != GL_INVALID_VALUE)
		{
			glDeleteLists(1, m_callListId);
		}
	}

	void NurbsCorrectImpl::initNurbs()
	{
		float height = 2.8;
		float width = 2.1;

		float theta = 30;

		float z = width/2 / tan(theta * PI / 180); 

		float bh = -height / 2;
		float bw = -width /2;

		float deltaH = height / 2;
		float deltaW = width / 2;

		m_left = 1e10;
		m_right = 1e-10;
		m_bottom = 1e10;
		m_top = 1e-10;

		//m_nearOS = z;

		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
			{
				m_cps[j][i][0] = bw + deltaW * i; 
				m_cps[j][i][1] = bh + deltaH * j;
				m_cps[j][i][2] = -z;
				m_cps[j][i][3] = 1.f;
				

				if (m_top < m_cps[j][i][1])
				{
					m_top = m_cps[j][i][1];
				}

				if (m_bottom > m_cps[j][i][1])
				{
					m_bottom = m_cps[j][i][1];
				}

				if (m_left > m_cps[j][i][0])
				{
					m_left = m_cps[j][i][0];
				}

				if (m_right < m_cps[j][i][0])
				{
					m_right = m_cps[j][i][0];
				}
			}
		}

		m_cps[1][1][1] += 0;
		
		m_cps[0][1][1] += .3;
		m_cps[0][1][3] =  1;
		
	
		m_cps[2][1][1] += 0.1;
		m_cps[2][1][3] = 1;
		
		m_top += 0.1;

		m_fps.x = 0.0;
		m_fps.y = -m_bottom/2;
		m_fps.z = 0.0;
	}

	void NurbsCorrectImpl::initXmlParams()
	{	
		vgConfig::XMLConfigManager::getSingleton().GetCurrentValue(Xmlsectionname);	

		m_height = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_height"));
		m_width = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_width"));
		m_theta = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_theta"));		

		float z = m_width/2 / tan(m_theta * PI / 180); 

		float bh = -m_height / 2;
		float bw = -m_width /2;

		float deltaH = m_height / 2;
		float deltaW = m_width / 2;

		m_left = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_left"));
		m_right = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_right"));
		m_bottom = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_bottom"));
		m_top = vgConfig::XMLConfigManager::
			getSingleton().GetFloatValue(Xmlsectionname, _T("m_top"));

		m_nearOS = z; 

		if (ReadCtrlInfer())
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					m_cps[i][j][0] = Xml_cps[i][j][0];
					m_cps[i][j][1] = Xml_cps[i][j][1];
					m_cps[i][j][2] = Xml_cps[i][j][2];
					m_cps[j][i][3] = 1.f;
					TRACE ("VAL %f \n", m_cps[i][j][0]);
					TRACE ("VAL %f \n", m_cps[i][j][1]);
				}
			}
		}
		else
		{
			for (int i=0; i<3; i++)
			{
				for (int j=0; j<3; j++)
				{
					m_cps[j][i][0] = bw + deltaW * i; 
					m_cps[j][i][1] = bh + deltaH * j;
					m_cps[j][i][2] = -z;
					m_cps[j][i][3] = 1.f;

				}
			}

		}	


		m_fps.x = 0.0;
		m_fps.y = -m_bottom/2;
		m_fps.z = 0.0;
	}

	CtrlPt NurbsCorrectImpl::getControlPoint(int x, int y)
	{
		CtrlPt pt;

		pt.x = m_cps[x][y][0];
		pt.y = m_cps[x][y][1];
		pt.z = m_cps[x][y][2];
		pt.w = m_cps[x][y][3];

		return pt;
	}

	void NurbsCorrectImpl::setControlPoint(int x, int y, CtrlPt pt)
	{
		m_cps[x][y][0] = pt.x;
		m_cps[x][y][1] = pt.y;
		m_cps[x][y][2] = pt.z;
		m_cps[x][y][3] = pt.w;

		recomplieCallList();
	}

	FurstumVal NurbsCorrectImpl::getFrustumVal()
	{
		FurstumVal fval;
		
		fval.bottom = m_bottom;
		fval.top = m_top;
		fval.left = m_left;
		fval.right = m_right;

		return fval;
	}

	void NurbsCorrectImpl::setFrustum(FurstumVal fval)
	{
		m_left = fval.left;
		m_right = fval.right;
		m_bottom = fval.bottom;
		m_top = fval.top;

		recomplieCallList();
	}

	void NurbsCorrectImpl::setLittleCorrectEnable(bool b)
	{
		m_nurbsLittleCorrectEnable = b; 
		
		if (! m_nurbsLittleCorrectEnable)
		{
			recomplieCallList();
		}
	}

	bool NurbsCorrectImpl::blendPixel()
	{
		if (m_nurbsLittleCorrectEnable)
		{
			NurbsLittleCorrect();

			return true;
		}
		
		if (m_callListId == GL_INVALID_VALUE)
		{
			assert(0);
			return false;
		}

		glCallList(m_callListId);
	

		if (glGetError() != GL_NO_ERROR)
		{
			assert(0);

			return false;
		}
		
		return true;

		GLfloat knot[] = {0,0,0,1,1,1};
		float tps[3][3][2] = {{{0,0},{.5,0},{1,0}},
		{{0,.5},{.5,.5},{1,.5}},
		{{0,1},{.5,1},{1,1}}};

		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 		glMatrixMode(GL_PROJECTION);
		
		glPushMatrix();
 		glLoadIdentity();
 
 		//glFrustum(gs_left, gs_right, gs_bottom, gs_top, m_nearOS-0.0001,100);
 		glOrtho(m_left, m_right, m_bottom, m_top, 0, 100);
 		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

 		glLoadIdentity();
 		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gluBeginSurface(m_nurb);
		gluNurbsSurface(m_nurb,6,knot,6,knot,2,3*2,&tps[0][0][0],3,3,GL_MAP2_TEXTURE_COORD_2);
		gluNurbsSurface(m_nurb,6,knot,6,knot,4,3*4,&m_cps[0][0][0],3,3,GL_MAP2_VERTEX_4);
		gluEndSurface(m_nurb);


		glPointSize(5);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glBegin(GL_POINTS);
		glColor3f(0,1.0, 0);
		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
			{
				glColor3f(0,1.0, 0);

				glVertex3f(m_cps[i][j][0], m_cps[i][j][1], m_cps[i][j][2]);
			}

		}

		glColor3f(0,0,0);
		glEnd();

		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		
		if (glGetError() != GL_NO_ERROR)
		{
			assert(0);

			return false;
		}

		return true;
	}

	bool NurbsCorrectImpl::recomplieCallList()
	{
// 		if (m_callListId != GL_INVALID_VALUE)
// 		{
// 			glDeleteLists(1, m_callListId);
// 			m_callListId = GL_INVALID_VALUE;
// 		}

		

		GLfloat knot[] = {0,0,0,1,1,1};
		float tps[3][3][2] = {{{0,0},{.5,0},{1,0}},
		{{0,.5},{.5,.5},{1,.5}},
		{{0,1},{.5,1},{1,1}}};

		glNewList(m_callListId, GL_COMPILE_AND_EXECUTE);

			glClearColor(0,0,0,0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glMatrixMode(GL_PROJECTION);
			glPushMatrix();

			glLoadIdentity();

			//glFrustum(gs_left, gs_right, gs_bottom, gs_top, m_nearOS-0.0001,100);
			glOrtho(m_left, m_right, m_bottom, m_top, 0, 100);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();

			glLoadIdentity();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			gluBeginSurface(m_nurb);
			gluNurbsSurface(m_nurb,6,knot,6,knot,2,3*2,&tps[0][0][0],3,3,GL_MAP2_TEXTURE_COORD_2);
			gluNurbsSurface(m_nurb,6,knot,6,knot,4,3*4,&m_cps[0][0][0],3,3,GL_MAP2_VERTEX_4);
			gluEndSurface(m_nurb);

 
  			glPointSize(5);
  			glDisable(GL_LIGHTING);
  			glDisable(GL_TEXTURE_2D);
  
//   			glBegin(GL_POINTS);
//   			glColor3f(0,1.0, 0);
//   			for (int i=0; i<3; i++)
//   			{
//   				for (int j=0; j<3; j++)
//   				{
//   					glColor3f(0,1.0, 0);
//   
//   					glVertex3f(m_cps[i][j][0], m_cps[i][j][1], m_cps[i][j][2]);
//   				}
//   
//   			}
//   
//   			glColor3f(0,0,0);
//  			glEnd();
			
			glPopMatrix();

			glMatrixMode(GL_PROJECTION);
			glPopMatrix();

		glEndList();

		if (glGetError() != GL_NO_ERROR)
		{
			assert(0);

			return false;
		}

		return true;
	}

	bool NurbsCorrectImpl::NurbsLittleCorrect()
	{
		GLfloat knot[] = {0,0,0,1,1,1};
		float tps[3][3][2] = {{{0,0},{.5,0},{1,0}},
		{{0,.5},{.5,.5},{1,.5}},
		{{0,1},{.5,1},{1,1}}};

		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
	
		glLoadIdentity();
		
		//glFrustum(gs_left, gs_right, gs_bottom, gs_top, m_nearOS-0.0001,100);
		glOrtho(m_left, m_right, m_bottom, m_top, 0, 100);
		glMatrixMode(GL_MODELVIEW);
	
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gluBeginSurface(m_nurb);
		gluNurbsSurface(m_nurb,6,knot,6,knot,2,3*2,&tps[0][0][0],3,3,GL_MAP2_TEXTURE_COORD_2);
		gluNurbsSurface(m_nurb,6,knot,6,knot,4,3*4,&m_cps[0][0][0],3,3,GL_MAP2_VERTEX_4);
		gluEndSurface(m_nurb);


		glPointSize(10);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);

		if (!m_pointInChoose.empty())
		{
			index = m_pointInChoose.top();
		}

		glBegin(GL_POINTS);
		glColor3f(0, 1.0, 0.0);

		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
			{
				if ((index.x == i)&&(index.y == j))
				{
					glColor3f(0.0, 0.0, 1.0);
					glVertex3f(m_cps[i][j][0]/3, m_cps[i][j][1]/3, m_cps[i][j][2]/3);
				}
				else
				{
					glColor3f(1.0, 0.0, 0.0);
					//glVertex3f(m_cps[i][j][0], m_cps[i][j][1], m_cps[i][j][2]);
					glVertex3f(m_cps[i][j][0]/3, m_cps[i][j][1]/3, m_cps[i][j][2]/3);
				}
			}
		}		

		glEnd();
		glFlush();
		if (glGetError() != GL_NO_ERROR)
		{
			return false;
		}

		return true;

	}

	bool NurbsCorrectImpl::MoveContrlPoint(vgKernel::Vec3 click_point)
	{	
		for (int i = 0; i <3; i ++ )
		{
			for (int j = 0; j < 3; j++)
			{
				if ((click_point.x > m_cps[i][j][0]/3 - 0.05)&&(click_point.x < m_cps[i][j][0]/3 + 0.05)&&
					(click_point.y > m_cps[i][j][1]/3 - 0.05)&&(click_point.y < m_cps[i][j][1]/3 + 0.05))
				{
					float dx = click_point.x - m_cps[i][j][0]/3;
					float dy = click_point.y - m_cps[i][j][1]/3;
					m_cps[i][j][0] = m_cps[i][j][0] + dx;
					m_cps[i][j][1] = m_cps[i][j][1] + dy;				
				}
			}
		}
		
		return true;
	}

	void NurbsCorrectImpl::Ifchose(vgKernel::Vec3 click_point)
	{
		for (int i = 0; i <3; i ++ )
		{
			for (int j = 0; j < 3; j++)			
				if ((click_point.x > m_cps[i][j][0]/3 - 0.05)&&(click_point.x < m_cps[i][j][0]/3 + 0.05)&&
					(click_point.y > m_cps[i][j][1]/3 - 0.05)&&(click_point.y < m_cps[i][j][1]/3 + 0.05))
				{
					index.x = i;
					index.y = j;
					m_pointInChoose.push(index);
				}
		}

	}

	void NurbsCorrectImpl::GetCorrectParam(float  param1, float param2)
	{
		m_correctparam = param1;
		m_clipplane = param2;
	}

	void NurbsCorrectImpl::moveUp()
	{
		if (!m_pointInChoose.empty())
		{
			index = m_pointInChoose.top();
			m_cps[index.x][index.y][1] += m_correctparam;			
		}

		//m_top += m_clipplane;
	}

	void NurbsCorrectImpl::moveDown()
	{
		if (!m_pointInChoose.empty())
		{
			index = m_pointInChoose.top();
			m_cps[index.x][index.y][1] -= m_correctparam;
		}	

		//m_bottom += m_clipplane;
	}

	void NurbsCorrectImpl::moveLeft()
	{
		if (!m_pointInChoose.empty())
		{
			index = m_pointInChoose.top();
			m_cps[index.x][index.y][0] -= m_correctparam;
		}	

		//m_left += m_clipplane;
	}

	void NurbsCorrectImpl::moveRight()
	{
		if (!m_pointInChoose.empty())
		{
			index = m_pointInChoose.top();
			m_cps[index.x][index.y][0] += m_correctparam;
		}

		//m_right += m_clipplane;
	}

	void NurbsCorrectImpl::SetCtrlPointToSave()
	{
		if (!CtrlPointValue.empty())
		{
			CtrlPointValue.clear();
		}

		for (int i = 0; i < 3; i ++)
		{
			for (int j = 0; j < 3; j ++)
			{
				CString value1, value2, value3, keyvalue;
				value1.Format("%f", m_cps[i][j][0]);
				value2.Format("%f", m_cps[i][j][1]);
				value3.Format("%f", m_cps[i][j][2]);
				keyvalue = value1 + _T(",") + value2 + _T(",")  + value3;
				CtrlPointValue.push_back(keyvalue);		
			}
		}	
	}

	bool NurbsCorrectImpl::ReadCtrlInfer()
	{
		if (vgConfig::XMLConfigManager::getSingleton().FindSection(_T("Contrl Point Infermation")))
		{
			parameValue = vgConfig::XMLConfigManager::getSingleton().GetCurrentValue(_T("Contrl Point Infermation"));			
			int k = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int  j =0; j<3; j++ )
				{
					std::string tmps = parameValue._Currentkeyvalue[k].GetString();
					float x, y, z;
					sscanf_s(tmps.c_str(), "%f,%f,%f", &x, &y, &z);
					Xml_cps[i][j][0] = x;
					Xml_cps[i][j][1] = y;
					Xml_cps[i][j][2] = z;
					k++;
				}

			}
			return true;
		}
		else
		{
			return false;
		}
	}

	void NurbsCorrectImpl::SetParamkeyToXml()
	{
		if (!ParamKeyName.empty())
		{
			ParamKeyName.clear();
		}

		ParamKeyName.push_back(_T("m_width"));
		ParamKeyName.push_back(_T("m_height"));
		ParamKeyName.push_back(_T("m_theta"));	 
		ParamKeyName.push_back(_T("m_left"));
		ParamKeyName.push_back(_T("m_right"));
		ParamKeyName.push_back(_T("m_bottom"));
		ParamKeyName.push_back(_T("m_top"));
	}

	void NurbsCorrectImpl::SetparamValueToXml()
	{
		if (!Newkeyvalue.empty())
		{
			Newkeyvalue.clear();
		}

		Newkeyvalue.push_back(TurnFloatToCstr(m_height));
		Newkeyvalue.push_back(TurnFloatToCstr(m_width));
		Newkeyvalue.push_back(TurnFloatToCstr(m_theta));
		Newkeyvalue.push_back(TurnFloatToCstr(m_left));
		Newkeyvalue.push_back(TurnFloatToCstr(m_right));
		Newkeyvalue.push_back(TurnFloatToCstr(m_bottom));
		Newkeyvalue.push_back(TurnFloatToCstr(m_top));

	}

	CString NurbsCorrectImpl::TurnFloatToCstr(float floatValue)
	{
		CString keyvalue;
		keyvalue.Format("%f", floatValue);
		return keyvalue;

	}

	void NurbsCorrectImpl::GetCtrlKey()
	{
		if (!CtrlpointKey.empty())
		{
			CtrlpointKey.clear();
		}
		CtrlpointKey.push_back(_T("00"));
		CtrlpointKey.push_back(_T("01"));
		CtrlpointKey.push_back(_T("02"));
		CtrlpointKey.push_back(_T("10"));
		CtrlpointKey.push_back(_T("11"));
		CtrlpointKey.push_back(_T("12"));
		CtrlpointKey.push_back(_T("20"));
		CtrlpointKey.push_back(_T("21"));
		CtrlpointKey.push_back(_T("22"));

	}

	void NurbsCorrectImpl::SavePramaToXml()
	{	

		SetparamValueToXml();
		SetParamkeyToXml();	
		vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(str_FileName);
		for (int i = 0; i < Newkeyvalue.size(); i ++)
		{
			vgConfig::XMLConfigManager::getSingleton().AddKeys(_T("Geometric correction Configuration"), 
				ParamKeyName[i], Newkeyvalue[i]);
		}

		GetCtrlKey();
		SetCtrlPointToSave();	

		for (int i = 0; i < CtrlPointValue.size(); i++)
		{
			vgConfig::XMLConfigManager::getSingleton().AddKeys(_T("Contrl Point Infermation"), 
				CtrlpointKey[i], CtrlPointValue[i]);
		}		

		vgConfig::XMLConfigManager::getSingleton().SaveXML(str_FileName);
	}

	void NurbsCorrectImpl::ReturnToOriPrama()
	{
		Xmlsectionname = _T("Geometric correction Configuration");
		if (vgConfig::XMLConfigManager::getSingleton().LoadXmlDocument(str_FileName)&&
			vgConfig::XMLConfigManager::getSingleton().FindSection(Xmlsectionname))
		{
			initXmlParams();

			vgChannel::FurstumVal fval = getFrustumVal();
			setFrustum(fval);		
		}
	}

}
