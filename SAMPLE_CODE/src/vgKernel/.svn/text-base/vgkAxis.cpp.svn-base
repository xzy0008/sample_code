

#include <vgStableHeaders.h>

#include <vgKernel/vgkAxis.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkRay.h>
#include <vgKernel/vgkAxis.h>

#include <gl/glut.h>
#include <vgKernel/vgkCamMgrImpl.h>
#include <vgKernel/vgkCamMgrHolder.h>



#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

namespace vgKernel {
	vgAxis::vgAxis(void)
	{
		m_editMode = Default;

		m_needUpdate = false;

		m_Centre = Vec3(0.0,0.0,0.0);
		
		//m_Size = 200.0;
		m_Size = 35;
		m_SizeScale = 1;

		m_RotSpeed = 0.1;
		m_ScalSpeed = 0.1;
		//////////////////////构造平面XY///////////////
		constructionPoints[0] = Vec3(100000,0,m_Centre.z);
		constructionPoints[1] = Vec3(0,100000,m_Centre.z);
		constructionPoints[2] = Vec3(-100000,-100000,m_Centre.z);
		//////////////////////构造平面XZ///////////////
		constructionPoints[3] = Vec3(100000,m_Centre.y,0);
		constructionPoints[4] = Vec3(0,m_Centre.y,100000);
		constructionPoints[5] = Vec3(-100000,m_Centre.y,-100000);
		//////////////////////构造平面YZ///////////////
		constructionPoints[6] = Vec3(m_Centre.x, 100000,0);
		constructionPoints[7] = Vec3(m_Centre.x, 0,100000);
		constructionPoints[8] = Vec3(m_Centre.x, -100000, -100000);
		//////////////////////轴十字面/////////////////////////
		constpoints[0] = Vec3(1.0/2.0, 0.0, 1.0/10.0);
		constpoints[1] = Vec3(1.0,     0.0, 1.0/10.0);
		constpoints[2] = Vec3(1.0,     0.0, -1.0/10.0);
		constpoints[3] = Vec3(1.0/2.0, 0.0, -1.0/10.0);
		constpoints[4] = Vec3(1.0/2.0, -1.0/10.0, 0.0);
		constpoints[5] = Vec3(1.0,     -1.0/10.0, 0.0);
		constpoints[6] = Vec3(1.0,     1.0/10.0,  0.0);
		constpoints[7] = Vec3(1.0/2.0, 1.0/10.0,  0.0);
		constpoints[8] = Vec3(-1.0/10.0, 1.0,  0.0);
		constpoints[9] = Vec3(-1.0/10.0, 1.0/2.0,  0.0);
		constpoints[10] = Vec3(1.0/10.0, 1.0/2.0,  0.0);
		constpoints[11] = Vec3(1.0/10.0, 1.0,      0.0);
		constpoints[12] = Vec3(0.0,     1.0,       1.0/10.0);
		constpoints[13] = Vec3(0.0,     1.0/2.0,   1.0/10.0);
		constpoints[14] = Vec3(0.0,     1.0/2.0,   -1.0/10.0);
		constpoints[15] = Vec3(0.0,     1.0,       -1.0/10.0);
		constpoints[16] = Vec3(-1.0/10.0, 0.0,     1.0/2.0);
		constpoints[17] = Vec3(-1.0/10.0, 0.0,     1.0);
		constpoints[18] = Vec3(1.0/10.0,  0.0,     1.0);
		constpoints[19] = Vec3(1.0/10.0,  0.0,     1.0/2.0);
		constpoints[20] = Vec3(0.0,     1.0/10.0,       1.0/2.0);
		constpoints[21] = Vec3(0.0,     1.0/10.0,       1.0);
		constpoints[22] = Vec3(0.0,     -1.0/10.0,      1.0);
		constpoints[23] = Vec3(0.0,     -1.0/10.0,      1.0/2.0);
		////////////////////平移平面/////////////////////////////////
		constpoints[24] = Vec3(0.0,0.0,0.0);
		constpoints[25] = Vec3(0.0, 0.0, 1.0/2.0);
		constpoints[26] = Vec3(0.0, 1.0/2.0, 0.0);
		constpoints[27] = Vec3(1.0/2.0, 0.0, 0.0);
		constpoints[28] = Vec3(1.0/2.0, 1.0/2.0, 0.0);
		constpoints[29] = Vec3(1.0/2.0, 0.0, 1.0/2.0);
		constpoints[30] = Vec3(0.0, 1.0/2.0, 1.0/2.0);
		constpoints[31] = Vec3(1.0/2.0, 1.0/2.0, 1.0/2.0);
		///////////////////////缩放平面///////////////////
		constpoints[32] = Vec3(0.0, 1.0/4.0, 1.0/4.0);
		constpoints[33] = Vec3(1.0/4.0, 0.0, 1.0/4.0);
		constpoints[34] = Vec3(1.0/4.0, 1.0/4.0, 0.0);
		///////////////////////////////////////////////////
		constpoints[35] = Vec3(1.25, 0.0,     0.0);
		constpoints[36] = Vec3(1.0,  1.0/16,  0.0);
		constpoints[37] = Vec3(1.0,  -1.0/16, 0.0);
		constpoints[38] = Vec3(1.0,  0.0,     1.0/16);
		constpoints[39] = Vec3(1.0,  0.0,     -1.0/16);

		constpoints[40] = Vec3(0.0,    1.25,    0.0);
		constpoints[41] = Vec3(1.0/16, 1.0,     0.0);
		constpoints[42] = Vec3(-1.0/16,1.0,     0.0);
		constpoints[43] = Vec3(0.0,    1.0,         1.0/16);
		constpoints[44] = Vec3(0.0,    1.0,         -1.0/16);

		constpoints[45] = Vec3(0.0,    0.0,    1.25);
		constpoints[46] = Vec3(1.0/16, 0.0,    1.0);
		constpoints[47] = Vec3(-1.0/16,0.0,    1.0);
		constpoints[48] = Vec3(0.0,    1.0/16, 1.0);
		constpoints[49] = Vec3(0.0,    -1.0/16,1.0);
		/////////////////x轴///////////////////////////
		AxisX.tri1 = vgTriangle(constpoints[0] * m_Size, constpoints[1] * m_Size, constpoints[2] * m_Size);
		AxisX.tri2 = vgTriangle(constpoints[2] * m_Size, constpoints[3] * m_Size, constpoints[0] * m_Size);
		AxisX.tri3 = vgTriangle(constpoints[4] * m_Size, constpoints[5] * m_Size, constpoints[6] * m_Size);
		AxisX.tri4 = vgTriangle(constpoints[6] * m_Size, constpoints[7] * m_Size, constpoints[4] * m_Size);
		/////////////////y轴///////////////////////////
		AxisY.tri1 = vgTriangle(constpoints[8] * m_Size, constpoints[9] * m_Size, constpoints[10] * m_Size);
		AxisY.tri2 = vgTriangle(constpoints[10] * m_Size, constpoints[11] * m_Size, constpoints[8] * m_Size);
		AxisY.tri3 = vgTriangle(constpoints[12] * m_Size, constpoints[13] * m_Size, constpoints[14] * m_Size);
		AxisY.tri4 = vgTriangle(constpoints[14] * m_Size, constpoints[15] * m_Size, constpoints[12] * m_Size);
		/////////////////z轴///////////////////////////
		AxisZ.tri1 = vgTriangle(constpoints[16] * m_Size, constpoints[17] * m_Size, constpoints[18] * m_Size);
		AxisZ.tri2 = vgTriangle(constpoints[18] * m_Size, constpoints[19] * m_Size, constpoints[16] * m_Size);
		AxisZ.tri3 = vgTriangle(constpoints[20] * m_Size, constpoints[21] * m_Size, constpoints[22] * m_Size);
		AxisZ.tri4 = vgTriangle(constpoints[22] * m_Size, constpoints[23] * m_Size, constpoints[20] * m_Size);
		///////////////////平移xy面/////////////////////////////////////
		AxisPlaneXY.tri1 = vgTriangle(constpoints[24] * m_Size,constpoints[27] * m_Size,constpoints[28] * m_Size);
		AxisPlaneXY.tri2 = vgTriangle(constpoints[28] * m_Size,constpoints[26] * m_Size,constpoints[24] * m_Size);
		///////////////////平移xz面//////////////////////////////////////
		AxisPlaneXZ.tri1 = vgTriangle(constpoints[24] * m_Size,constpoints[25] * m_Size,constpoints[29] * m_Size);
		AxisPlaneXZ.tri2 = vgTriangle(constpoints[29] * m_Size,constpoints[27] * m_Size,constpoints[24] * m_Size);
		///////////////////平移yz面//////////////////////////////////////
		AxisPlaneYZ.tri1 = vgTriangle(constpoints[24] * m_Size,constpoints[26] * m_Size,constpoints[30] * m_Size);
		AxisPlaneYZ.tri2 = vgTriangle(constpoints[30] * m_Size,constpoints[25] * m_Size,constpoints[24] * m_Size);
		///////////////////缩放三角面//////////////////////////////////////
		CapPlane = vgTriPlane(constpoints[25] * m_Size, constpoints[26] * m_Size, constpoints[27] * m_Size);
		ScalPlaneXYZ = vgTriPlane(constpoints[32] * m_Size, constpoints[33] * m_Size, constpoints[34] * m_Size);
		ScalPlaneX = vgTriPlane(constpoints[27] * m_Size, constpoints[33] * m_Size, constpoints[34] * m_Size); 
		ScalPlaneY = vgTriPlane(constpoints[26] * m_Size, constpoints[32] * m_Size, constpoints[34] * m_Size);
		ScalPlaneZ = vgTriPlane(constpoints[25] * m_Size, constpoints[32] * m_Size, constpoints[33] * m_Size);
		/////////////////////////旋转轴////////////////////////////////////////////////////////////
		RotAxisPlaneX.tri1 = vgTriangle(constpoints[35] * m_Size,constpoints[36] * m_Size,constpoints[37] * m_Size);
		RotAxisPlaneX.tri2 = vgTriangle(constpoints[35] * m_Size,constpoints[38] * m_Size,constpoints[39] * m_Size);
		RotAxisPlaneY.tri1 = vgTriangle(constpoints[40] * m_Size,constpoints[41] * m_Size,constpoints[42] * m_Size);
		RotAxisPlaneY.tri2 = vgTriangle(constpoints[40] * m_Size,constpoints[43] * m_Size,constpoints[44] * m_Size);
		RotAxisPlaneZ.tri1 = vgTriangle(constpoints[45] * m_Size,constpoints[46] * m_Size,constpoints[47] * m_Size);
		RotAxisPlaneZ.tri2 = vgTriangle(constpoints[45] * m_Size,constpoints[48] * m_Size,constpoints[49] * m_Size);
		////////////////////////三个构造平面//////////////////////////////
		m_planeXY = vgTriangle(constructionPoints[0], constructionPoints[1], constructionPoints[2]);
		m_planeXZ = vgTriangle(constructionPoints[3], constructionPoints[4], constructionPoints[5]);
		m_planeYZ = vgTriangle(constructionPoints[6], constructionPoints[7], constructionPoints[8]);
		//////////////////////////////////////////////////////////////////
	}
	vgAxis::~vgAxis(void)
	{
	}
	Vec3 vgAxis::Trans2DTo3D(CPoint &point)
	{
		GLint viewport[4];
		GLdouble modelview[16];
		GLdouble projection[16];
		GLfloat winX,winY,winZ;
		GLdouble object_x,object_y,object_z;

		glGetIntegerv(GL_VIEWPORT, viewport);
		winX=(float)point.x;                           /*OGL中的窗口x坐标*/
		winY=(float)viewport[3]-(float)point.y - 1.0f; /*OGL中的窗口y坐标*/

		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);  /*视图矩阵*/
		glGetDoublev(GL_PROJECTION_MATRIX, projection);/*投影矩阵*/

		glReadPixels(point.x,                          /*x坐标*/
			int(winY),                                 /*y坐标*/
			1,1,                                       /*读取一个像素*/
			GL_DEPTH_COMPONENT,                        /*获得深度信息*/
			GL_FLOAT,                                  /*数据类型为浮点型*/
			&winZ);                                    /*获得的深度值保存在winZ中*/

		gluUnProject((GLdouble)winX,
			(GLdouble)winY,
			(GLdouble)winZ,
			modelview,
			projection,
			viewport,
			&object_x,
			&object_y,
			&object_z);
		return Vec3(object_x,object_y,object_z);

	}
	void vgAxis::Init()
	{
		for(int i=0; i<50; i++)
		{
			points[i] = constpoints[i]*m_Size;
		}
	}
	void vgAxis::RenderAxisCone(const char& renderMode)
	{

		if(renderMode == 1)
		{
			glColor3f(1.0,0.0,0.0);

			glutSolidCone( m_Size/16.0,m_Size/4.0, 20.0, 20.0);
		}
		else if(renderMode == 2)
		{
			glColor3f(0.0,1.0,0.0);
			glutSolidCone( m_Size/16.0,m_Size/4.0, 20.0,20.0);
		}
		else if(renderMode == 3)
		{
			glColor3f(0.0,0.0,1.0);
			glutSolidCone( m_Size/16.0,m_Size/4.0, 20.0, 20.0);
		}
		else if(renderMode == 4)
		{
			glColor3f(1.0,1.0,0.0);
			glutSolidCone( m_Size/16.0,m_Size/4.0, 20.0, 20.0);
		}
	}
	void vgAxis::Render()
	{
		//glEnable(GL_BLEND);
		glPushAttrib(GL_CURRENT_BIT);
		glDisable(GL_BLEND);

		//glCullFace(GL_);
		glDisable(GL_CULL_FACE);
		glDisable(GL_ALPHA_TEST);
		glLineWidth(2.0);
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		glDisable(GL_DEPTH_TEST);
#if 0
		glBegin(GL_LINES);
		{
			/*x轴 红*/
			if(capMode == CTransX)
				glColor3f(1.0,1.0,0.0);
			else
				glColor3f(1.0,0.0,0.0);

			glVertex3f(m_Centre.x, m_Centre.y, m_Centre.z);
			glVertex3f(m_Centre.x+m_Size, m_Centre.y,m_Centre.z);	

			/*y轴 绿*/
			if(capMode == CTransY)
				glColor3f(1.0,1.0,0.0);
			else
				glColor3f(0.0,1.0,0.0);

			glVertex3f(m_Centre.x, m_Centre.y, m_Centre.z);
			glVertex3f(m_Centre.x, m_Centre.y+m_Size,m_Centre.z );	

			/*z轴 蓝*/
			if(capMode == CTransZ)
				glColor3f(1.0,1.0,0.0);
			else
				glColor3f(0.0,0.0,1.0);

			glVertex3f(m_Centre.x, m_Centre.y, m_Centre.z);
			glVertex3f(m_Centre.x, m_Centre.y,m_Centre.z+m_Size );
		}
		glEnd();

		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(m_Centre.x+m_Size,m_Centre.y,m_Centre.z);
		glRotatef(90,0.0,1.0,0.0);

		if(capMode == CRotX)
			RenderAxisCone(4);
		else
			RenderAxisCone(1);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(m_Centre.x,m_Centre.y+m_Size,m_Centre.z);
		glRotatef(-90,1.0,0.0,0.0);

		if(capMode == CRotY)
			RenderAxisCone(4);
		else
			RenderAxisCone(2);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0,0.0,1.0);
		glTranslatef(m_Centre.x,m_Centre.y,m_Centre.z+m_Size);
		glRotatef(90,0.0,0.0,1.0);

		if(capMode == CRotZ)
			RenderAxisCone(4);
		else
			RenderAxisCone(3);
		glPopMatrix();

		if(capMode == CTransXY)
		{
			AxisPlaneXY.Render();
		}
		else if(capMode == CTransXZ)
		{
			AxisPlaneXZ.Render();
		}
		else if(capMode == CTransYZ)
		{
			AxisPlaneYZ.Render();
		}
		else if(capMode == CScalXYZ)
		{
			ScalPlaneXYZ.Render(1);
			ScalPlaneX.Render(2);
			ScalPlaneY.Render(2);
			ScalPlaneZ.Render(2);
		}
		else if(capMode == CScalX)
		{
			ScalPlaneXYZ.Render(2);
			ScalPlaneX.Render(1);
			ScalPlaneY.Render(2);
			ScalPlaneZ.Render(2);
		}
		else if(capMode == CScalY)
		{
			ScalPlaneXYZ.Render(2);
			ScalPlaneX.Render(2);
			ScalPlaneY.Render(1);
			ScalPlaneZ.Render(2);
		}
		else if(capMode == CScalZ)
		{
			ScalPlaneXYZ.Render(2);
			ScalPlaneX.Render(2);
			ScalPlaneY.Render(2);
			ScalPlaneZ.Render(1);
		}
#endif
		glBegin(GL_LINES);
		{
			/*x轴 红*/
			if(capMode == CTransX &&
				( GetEditMode() == ATrans || GetEditMode() == Default ) )
				glColor3f(1.0,1.0,0.0);
			else
				glColor3f(1.0,0.0,0.0);

			glVertex3f(m_Centre.x, m_Centre.y, m_Centre.z);
			glVertex3f(m_Centre.x+m_Size, m_Centre.y,m_Centre.z);	

			/*y轴 绿*/
			if(capMode == CTransY &&
				( GetEditMode() == ATrans || GetEditMode() == Default ) )
				glColor3f(1.0,1.0,0.0);
			else
				glColor3f(0.0,1.0,0.0);

			glVertex3f(m_Centre.x, m_Centre.y, m_Centre.z);
			glVertex3f(m_Centre.x, m_Centre.y+m_Size,m_Centre.z );	

			/*z轴 蓝*/
			if(capMode == CTransZ &&
				( GetEditMode() == ATrans || GetEditMode() == Default ) )
				glColor3f(1.0,1.0,0.0);
			else
				glColor3f(0.0,0.0,1.0);

			glVertex3f(m_Centre.x, m_Centre.y, m_Centre.z);
			glVertex3f(m_Centre.x, m_Centre.y,m_Centre.z+m_Size );
		}
		glEnd();


		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(m_Centre.x+m_Size,m_Centre.y,m_Centre.z);
		glRotatef(90,0.0,1.0,0.0);

		if(capMode == CRotX &&
			( GetEditMode() == ARot || GetEditMode() == Default ) )
			RenderAxisCone(4);
		else
			RenderAxisCone(1);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(m_Centre.x,m_Centre.y+m_Size,m_Centre.z);
		glRotatef(-90,1.0,0.0,0.0);

		if(capMode == CRotY &&
			( GetEditMode() == ARot || GetEditMode() == Default ) )
			RenderAxisCone(4);
		else
			RenderAxisCone(2);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0,0.0,1.0);
		glTranslatef(m_Centre.x,m_Centre.y,m_Centre.z+m_Size);
		glRotatef(90,0.0,0.0,1.0);

		if(capMode == CRotZ &&
			( GetEditMode() == ARot || GetEditMode() == Default ) )
			RenderAxisCone(4);
		else
			RenderAxisCone(3);
		glPopMatrix();



		if(capMode == CTransXY &&
			( GetEditMode() == ATrans || GetEditMode() == Default ) )
		{
			AxisPlaneXY.Render();
		}
		else if(capMode == CTransXZ &&
			( GetEditMode() == ATrans || GetEditMode() == Default ) )
		{
			AxisPlaneXZ.Render();
		}
		else if(capMode == CTransYZ &&
			( GetEditMode() == ATrans || GetEditMode() == Default ) )
		{
			AxisPlaneYZ.Render();
		}

		else if(capMode == CScalXYZ &&
			( GetEditMode() == AScal || GetEditMode() == Default ) )
		{
			ScalPlaneXYZ.Render(1);
			ScalPlaneX.Render(2);
			ScalPlaneY.Render(2);
			ScalPlaneZ.Render(2);
		}
		else if(capMode == CScalX &&
			( GetEditMode() == AScal || GetEditMode() == Default ) )
		{
			ScalPlaneXYZ.Render(2);
			ScalPlaneX.Render(1);
			ScalPlaneY.Render(2);
			ScalPlaneZ.Render(2);
		}
		else if(capMode == CScalY &&
			( GetEditMode() == AScal || GetEditMode() == Default ) )
		{
			ScalPlaneXYZ.Render(2);
			ScalPlaneX.Render(2);
			ScalPlaneY.Render(1);
			ScalPlaneZ.Render(2);
		}
		else if(capMode == CScalZ &&
			( GetEditMode() == AScal || GetEditMode() == Default ) )
		{
			ScalPlaneXYZ.Render(2);
			ScalPlaneX.Render(2);
			ScalPlaneY.Render(2);
			ScalPlaneZ.Render(1);
		}

		glEnable(GL_DEPTH_TEST);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
		glLineWidth(1.0);
		glPopAttrib();
		//glPopMatrix();

// 		const GLenum& errorCode = glGetError();
// 		if (errorCode == GL_NO_ERROR)
// 		{
// 			//TRACE("No error \n");
// 		}else{
// 			const uchar* str = gluErrorString( errorCode );
// 			char buffer[200];
// 			sprintf(buffer, "Error Message : %s\n", str);
// 			//TRACE("GL Error msg: %s \n", buffer);
// 		}
	}
	void vgAxis::MoveTo(const Vec3& pos )
	{
		m_Centre = m_Centre+pos;
		//TRACE("Axis move %.2f %.2f %.2f \n", pos.x, pos.y, pos.z);
		//m_Size=((m_camera.g_eye[0]-m_Centre.x)*(m_camera.g_eye[0]-m_Centre.x) 
		//	+ (m_camera.g_eye[1]-m_Centre.y)*(m_camera.g_eye[1]-m_Centre.y)
		//	+ (m_camera.g_eye[2]-m_Centre.x)*(m_camera.g_eye[2]-m_Centre.x))/100;//根据距离远近调整大小
		Update();
	}

	void vgAxis::SetCenter(const Vec3& pos)
	{
		m_Centre = pos;
		Update();
	}

	/*void vgAxis::SetSize( const float& size )
	{
		m_Size = size;
		Update();
	}*/
	/*通过判断射线与哪一个面相交来确定修改模式*/
	BOOL vgAxis::IsIntersectWith( const Ray& ray )
	{
		if(AxisX.IsIntersectWith(ray))
		{
			capMode = CTransX;
			return TRUE;
		}
		else if(AxisY.IsIntersectWith(ray))
		{
			capMode = CTransY;
			return TRUE;
		}
		else if(AxisZ.IsIntersectWith(ray))
		{
			capMode = CTransZ;
			return TRUE;
		}
		else if(CapPlane.IsIntersectWith(ray))
		{
			if(ScalPlaneXYZ.IsIntersectWith(ray))
			{
				capMode = CScalXYZ;
				return TRUE;
			}
			else if(ScalPlaneX.IsIntersectWith(ray))
			{
				capMode = CScalX;
				return TRUE;
			}
			else if(ScalPlaneY.IsIntersectWith(ray))
			{
				capMode = CScalY;
				return TRUE;
			}
			else if(ScalPlaneZ.IsIntersectWith(ray))
			{
				capMode = CScalZ;
				return TRUE;
			}

		}
		else if(AxisPlaneXY.IsIntersectWith(ray))
		{
			capMode = CTransXY;
			return TRUE;
		}
		else if(AxisPlaneXZ.IsIntersectWith(ray))
		{
			capMode = CTransXZ;
			return TRUE;
		}
		else if(AxisPlaneYZ.IsIntersectWith(ray))
		{
			capMode = CTransYZ;
			return TRUE;
		}
		else if(RotAxisPlaneX.IsIntersectWith(ray))
		{
			capMode = CRotX;
			return TRUE;
		}
		else if(RotAxisPlaneY.IsIntersectWith(ray))
		{
			capMode = CRotY;
			return TRUE;
		}
		else if(RotAxisPlaneZ.IsIntersectWith(ray))
		{
			capMode = CRotZ;
			return TRUE;
		}
		return FALSE;
	}

	void vgAxis::Update()
	{

		for(int i=0; i<50; i++)
		{
			points[i] = constpoints[i] * m_Size + m_Centre;
		}

		/////////////////x轴///////////////////////////
		//AxisX.tri1 = vgTriangle(points[0], points[1], points[2]);
		AxisX.tri1.p0 = points[0];
		AxisX.tri1.p1 = points[1];
		AxisX.tri1.p2 = points[2];
		//AxisX.tri2 = vgTriangle(points[2], points[3], points[0]);
		AxisX.tri2.p0 = points[2];
		AxisX.tri2.p1 = points[3];
		AxisX.tri2.p2 = points[0];
		//AxisX.tri3 = vgTriangle(points[4], points[5], points[6]);
		AxisX.tri3.p0 = points[4];
		AxisX.tri3.p1 = points[5];
		AxisX.tri3.p2 = points[6];
		//AxisX.tri4 = vgTriangle(points[6], points[7], points[4]);
		AxisX.tri4.p0 = points[6];
		AxisX.tri4.p1 = points[7];
		AxisX.tri4.p2 = points[4];
		/////////////////y轴///////////////////////////
		//AxisY.tri1 = vgTriangle(points[8], points[9], points[10]);
		AxisY.tri1.p0 = points[8];
		AxisY.tri1.p1 = points[9];
		AxisY.tri1.p2 = points[10];
		//AxisY.tri2 = vgTriangle(points[10], points[11], points[8]);
		AxisY.tri2.p0 = points[10];
		AxisY.tri2.p1 = points[11];
		AxisY.tri2.p2 = points[8];
		//AxisY.tri3 = vgTriangle(points[12], points[13], points[14]);
		AxisY.tri3.p0 = points[12];
		AxisY.tri3.p1 = points[13];
		AxisY.tri3.p2 = points[14];
		//AxisY.tri4 = vgTriangle(points[14], points[15], points[12]);
		AxisY.tri4.p0 = points[14];
		AxisY.tri4.p1 = points[15];
		AxisY.tri4.p2 = points[12];
		/////////////////z轴///////////////////////////
		//AxisZ.tri1 = vgTriangle(points[16], points[17], points[18]);
		AxisZ.tri1.p0 = points[16];
		AxisZ.tri1.p1 = points[17];
		AxisZ.tri1.p2 = points[18];
		//AxisZ.tri2 = vgTriangle(points[18], points[19], points[16]);
		AxisZ.tri2.p0 = points[18];
		AxisZ.tri2.p1 = points[19];
		AxisZ.tri2.p2 = points[16];
		//AxisZ.tri3 = vgTriangle(points[20], points[21], points[22]);
		AxisZ.tri3.p0 = points[20];
		AxisZ.tri3.p1 = points[21];
		AxisZ.tri3.p2 = points[22];
		//AxisZ.tri4 = vgTriangle(points[22], points[23], points[20]);
		AxisZ.tri4.p0 = points[22];
		AxisZ.tri4.p1 = points[23];
		AxisZ.tri4.p2 = points[20];
		///////////////////xy面/////////////////////////////////////
		//AxisPlaneXY.tri1 = vgTriangle(points[24],points[27],points[28]);
		AxisPlaneXY.tri1.p0 = points[24];
		AxisPlaneXY.tri1.p1 = points[27];
		AxisPlaneXY.tri1.p2 = points[28];
		//AxisPlaneXY.tri2 = vgTriangle(points[28],points[26],points[24]);
		AxisPlaneXY.tri2.p0 = points[28];
		AxisPlaneXY.tri2.p1 = points[26];
		AxisPlaneXY.tri2.p2 = points[24];
		///////////////////xz面//////////////////////////////////////
		//AxisPlaneXZ.tri1 = vgTriangle(points[24],points[25],points[29]);
		AxisPlaneXZ.tri1.p0 = points[24];
		AxisPlaneXZ.tri1.p1 = points[25];
		AxisPlaneXZ.tri1.p2 = points[29];
		//AxisPlaneXZ.tri2 = vgTriangle(points[29],points[27],points[24]);
		AxisPlaneXZ.tri2.p0 = points[29];
		AxisPlaneXZ.tri2.p1 = points[27];
		AxisPlaneXZ.tri2.p2 = points[24];
		///////////////////yz面//////////////////////////////////////
		//AxisPlaneYZ.tri1 = vgTriangle(points[24],points[26],points[30]);
		AxisPlaneYZ.tri1.p0 = points[24];
		AxisPlaneYZ.tri1.p1 = points[26];
		AxisPlaneYZ.tri1.p2 = points[30];
		//AxisPlaneYZ.tri2 = vgTriangle(points[30],points[25],points[24]);
		AxisPlaneYZ.tri2.p0 = points[30];
		AxisPlaneYZ.tri2.p1 = points[25];
		AxisPlaneYZ.tri2.p2 = points[24];
		////////////////////////////////////////////////////////////////
		//ScalPlaneXYZ =  vgTriPlane(points[25], points[26], points[27]);
		CapPlane.tri.p0 = points[25];
		CapPlane.tri.p1 = points[26];
		CapPlane.tri.p2 = points[27];

		ScalPlaneXYZ.tri.p0 = points[32];
		ScalPlaneXYZ.tri.p1 = points[33];
		ScalPlaneXYZ.tri.p2 = points[34];

		ScalPlaneX.tri.p0 = points[27];
		ScalPlaneX.tri.p1 = points[33];
		ScalPlaneX.tri.p2 = points[34];

		ScalPlaneY.tri.p0 = points[26];
		ScalPlaneY.tri.p1 = points[32];
		ScalPlaneY.tri.p2 = points[34];

		ScalPlaneZ.tri.p0 = points[25];
		ScalPlaneZ.tri.p1 = points[32];
		ScalPlaneZ.tri.p2 = points[33];

		RotAxisPlaneX.tri1.p0 = points[35];
		RotAxisPlaneX.tri1.p1 = points[36];
		RotAxisPlaneX.tri1.p2 = points[37];

		RotAxisPlaneX.tri2.p0 = points[35];
		RotAxisPlaneX.tri2.p1 = points[38];
		RotAxisPlaneX.tri2.p2 = points[39];

		RotAxisPlaneY.tri1.p0 = points[40];
		RotAxisPlaneY.tri1.p1 = points[41];
		RotAxisPlaneY.tri1.p2 = points[42];

		RotAxisPlaneY.tri2.p0 = points[40];
		RotAxisPlaneY.tri2.p1 = points[43];
		RotAxisPlaneY.tri2.p2 = points[44];

		RotAxisPlaneZ.tri1.p0 = points[45];
		RotAxisPlaneZ.tri1.p1 = points[46];
		RotAxisPlaneZ.tri1.p2 = points[47];

		RotAxisPlaneZ.tri2.p0 = points[45];
		RotAxisPlaneZ.tri2.p1 = points[48];
		RotAxisPlaneZ.tri2.p2 = points[49];
	}
	/*****************************************/
	/*    更新构造面的位置和坐标轴的大小     */
	/*****************************************/
	void vgAxis::UpdatePlane()
	{
		//m_Size=sqrtf((m_camera.g_eye[0]-m_Centre.x)*(m_camera.g_eye[0]-m_Centre.x)
		//	+ (m_camera.g_eye[1]-m_Centre.y)*(m_camera.g_eye[1]-m_Centre.y)
		// 	//	+ (m_camera.g_eye[2]-m_Centre.z)*(m_camera.g_eye[2]-m_Centre.z))/10.0;//根据距离远近调整大小
		


		//m_Size=((m_camera.g_eye[0]-m_Centre.x)*(m_camera.g_eye[0]-m_Centre.x) 
		//	+ (m_camera.g_eye[1]-m_Centre.y)*(m_camera.g_eye[1]-m_Centre.y)
		//	+ (m_camera.g_eye[2]-m_Centre.x)*(m_camera.g_eye[2]-m_Centre.x))/100;//根据距离远近调整大小

// 		m_Size=((eyePosition->x-m_Centre.x)*(eyePosition->x-m_Centre.x) 
// 			+ (eyePosition->y-m_Centre.y)*(eyePosition->y-m_Centre.y)
// 			+ (eyePosition->z-m_Centre.x)*(eyePosition->z-m_Centre.x))/100;//根据距离远近调整大小
		
		Update();
		//constructionPoints[0] = Vec3(m_Centre.x+100000,  m_Centre.y,        m_Centre.z);
		//constructionPoints[1] = Vec3(m_Centre.x,         m_Centre.y+100000, m_Centre.z);
		//constructionPoints[2] = Vec3(m_Centre.x-100000,  m_Centre.y-100000, m_Centre.z);
		constructionPoints[0].x = m_Centre.x + 100000;
		constructionPoints[0].y = m_Centre.y;
		constructionPoints[0].z = m_Centre.z;
		constructionPoints[1].x = m_Centre.x; 
		constructionPoints[1].y = m_Centre.y + 100000;
		constructionPoints[1].z = m_Centre.z;
		constructionPoints[2].x = m_Centre.x - 100000; 
		constructionPoints[2].y = m_Centre.y - 100000;
		constructionPoints[2].z = m_Centre.z;

		//constructionPoints[3] = Vec3(m_Centre.x+100000,  m_Centre.y, m_Centre.z);
		//constructionPoints[4] = Vec3(m_Centre.x,         m_Centre.y, m_Centre.z+100000);
		//constructionPoints[5] = Vec3(m_Centre.x-100000,  m_Centre.y, m_Centre.z-100000);
		constructionPoints[3].x = m_Centre.x + 100000;
		constructionPoints[3].y = m_Centre.y;
		constructionPoints[3].z = m_Centre.z;
		constructionPoints[4].x = m_Centre.x; 
		constructionPoints[4].y = m_Centre.y;
		constructionPoints[4].z = m_Centre.z + 100000;
		constructionPoints[5].x = m_Centre.x - 100000; 
		constructionPoints[5].y = m_Centre.y;
		constructionPoints[5].z = m_Centre.z - 100000;

		//constructionPoints[6] = Vec3(m_Centre.x, m_Centre.y+100000, m_Centre.z);
		//constructionPoints[7] = Vec3(m_Centre.x, m_Centre.y,        m_Centre.z+100000);
		//constructionPoints[8] = Vec3(m_Centre.x, m_Centre.y-100000, m_Centre.z-100000);
		constructionPoints[6].x = m_Centre.x;
		constructionPoints[6].y = m_Centre.y + 100000;
		constructionPoints[6].z = m_Centre.z;
		constructionPoints[7].x = m_Centre.x; 
		constructionPoints[7].y = m_Centre.y;
		constructionPoints[7].z = m_Centre.z + 100000;
		constructionPoints[8].x = m_Centre.x; 
		constructionPoints[8].y = m_Centre.y - 100000;
		constructionPoints[8].z = m_Centre.z - 100000;
		//m_planeXY = vgTriangle(constructionPoints[0], constructionPoints[1], constructionPoints[2]);
		//m_planeXZ = vgTriangle(constructionPoints[3], constructionPoints[4], constructionPoints[5]);
		//m_planeYZ = vgTriangle(constructionPoints[6], constructionPoints[7], constructionPoints[8]);
		m_planeXY.p0 = constructionPoints[0];
		m_planeXY.p1 = constructionPoints[1];
		m_planeXY.p2 = constructionPoints[2];
		m_planeXZ.p0 = constructionPoints[3];
		m_planeXZ.p1 = constructionPoints[4];
		m_planeXZ.p2 = constructionPoints[5];
		m_planeYZ.p0 = constructionPoints[6];
		m_planeYZ.p1 = constructionPoints[7];
		m_planeYZ.p2 = constructionPoints[8];
	}
	/***************************************************/
	/*    鼠标移动时，根据捕捉状态返回编辑参数         */
	/***************************************************/
	void vgAxis::OnMouseMove( UINT nFlags, CPoint point )
	{

		static uint cnt;
		 //static CPoint lastPoint = point;
		
		Vec3 position = CamMgrHolder::getSingleton().getCamManager()->getCurrentPosition();

		Vec3 posaim = Trans2DTo3D(point);
	//	Vec3 poscam = Vec3(m_camera.g_eye[0],m_camera.g_eye[1],m_camera.g_eye[2]);
		
		Vec3 poscam = position;

		Vec3 dir = posaim - poscam;

		Ray lookray = Ray(poscam, dir);

		float diss;
		Vec3 pos1;
		
		////TRACE("%d Mode %d\n", cnt++, capMode);

		if (nFlags == 9)  /*ctrl组合*/
		{		
			if(capMode == CTransX)                           /*如果是x轴*/
			{
				if(m_planeXY.InterSect(lookray,diss) && diss >0.0)/*如果和xy构造面相交*/
				{
					pos1 = lookray.getPoint(diss);           /*得到交点*/
					m_Trans = pos1 - m_Trans;                /*平移量*/
					m_Trans.y = 0.0;                         /*锁定y轴*/
					m_Trans.z = 0.0;                  

					MoveTo(m_Trans);
					m_Trans = pos1;

					m_needUpdate = true;
					return ;
				}
				else if(m_planeXZ.InterSect(lookray,diss) && diss >0.0)/*如果和xz构造面相交*/
				{
					pos1 = lookray.getPoint(diss);           /*得到交点*/
					m_Trans = pos1 - m_Trans;                /*平移量*/

					m_Trans.y = 0.0;                         /*锁定y轴*/
					m_Trans.z = 0.0;     

					MoveTo(m_Trans);
					m_Trans = pos1;
					
					m_needUpdate = true;
					return ;
				}
			}

			else if(capMode == CTransY)                      /*如果是y轴*/
			{
				////TRACE("Inner Y %d Mode %d\n", cnt++, capMode);
				// debug here
				if(m_planeXY.InterSect(lookray,diss) && diss >0.0)
				{
					////TRACE("Inner1 Y %d Mode %d\n", cnt++, capMode);

					pos1 = lookray.getPoint(diss);           /*得到交点*/
					m_Trans = pos1 - m_Trans;                /*平移量*/

					m_Trans.x = 0.0;                         /*锁定x轴*/
					m_Trans.z = 0.0;

					MoveTo(m_Trans);
					m_Trans = pos1;
		
					m_needUpdate = true;
				}
				else if(m_planeYZ.InterSect(lookray,diss) && diss >0.0)
				{
					////TRACE("Inner2 Y %d Mode %d\n", cnt++, capMode);

					pos1 = lookray.getPoint(diss);           /*得到交点*/
					m_Trans = pos1 - m_Trans;                /*平移量*/

					m_Trans.x = 0.0;                         /*锁定x轴*/
					m_Trans.z = 0.0;

					MoveTo(m_Trans);
					m_Trans = pos1;

					m_needUpdate = true;
				}
			}

			else if(capMode == CTransZ)                      /*如果是z轴*/
			{
				if(m_planeXZ.InterSect(lookray,diss) && diss >0.0)
				{
					pos1 = lookray.getPoint(diss);           /*得到交点*/
					m_Trans = pos1 - m_Trans;                /*平移量*/

					m_Trans.x = 0.0;                         /*锁定x轴*/
					m_Trans.y = 0.0;

					MoveTo(m_Trans);
					m_Trans = pos1;

					m_needUpdate = true;
				}
				else if(m_planeYZ.InterSect(lookray,diss) && diss >0.0)
				{
					pos1 = lookray.getPoint(diss);           /*得到交点*/
					m_Trans = pos1 - m_Trans;                /*平移量*/

					m_Trans.x = 0.0;                         /*锁定x轴*/
					m_Trans.y = 0.0;

					MoveTo(m_Trans);
					m_Trans = pos1;

					m_needUpdate = true;
				}
			}

			else if(capMode == CTransXY)                          /*如果是xy*/
			{
				if(m_planeXY.InterSect(lookray,diss) && diss >0.0)/*只计算和XY构造面的交点*/
				{
					pos1 = lookray.getPoint(diss);                /*得到交点*/
					m_Trans = pos1 - m_Trans;                     /*平移量*/
					m_Trans.z = 0.0;

					MoveTo(m_Trans);
					m_Trans = pos1;

					m_needUpdate = true;
				}
			}

			else if(capMode == CTransXZ)                       /*如果是xz*/
			{
				if(m_planeXZ.InterSect(lookray,diss) && diss >0.0)
				{
					pos1 = lookray.getPoint(diss);            /*得到交点*/
					m_Trans = pos1 - m_Trans;                 /*平移量*/
					m_Trans.y = 0.0;

					MoveTo(m_Trans);
					m_Trans = pos1;

					m_needUpdate = true;
				}
			}
			else if(capMode == CTransYZ)                      /*如果是yz*/
			{
				if(m_planeYZ.InterSect(lookray,diss) && diss >0.0)
				{
					pos1 = lookray.getPoint(diss);            /*得到交点*/
					m_Trans = pos1 - m_Trans;                 /*平移量*/
					m_Trans.x = 0.0;

					MoveTo(m_Trans);
					m_Trans = pos1;

					m_needUpdate = true;
				}
			}

			else if(capMode == CScalXYZ)         /*当绕全轴缩放，得到缩放矢量*/
			{
				m_Scaled = point.y - m_Scaled;
				m_Scal = Vec3(m_Scaled*m_ScalSpeed,m_Scaled*m_ScalSpeed,m_Scaled*m_ScalSpeed);
				m_Scaled = point.y;

				m_needUpdate = true;
			}
			else if(capMode == CScalX)         /*当绕x缩放，得到缩放矢量*/
			{
				m_Scaled = point.y - m_Scaled;
				m_Scal = Vec3(m_Scaled*m_ScalSpeed,0,0);
				m_Scaled = point.y;

				m_needUpdate = true;
			}
			else if(capMode == CScalY)         /*当绕y缩放，得到缩放矢量*/
			{
				m_Scaled = point.y - m_Scaled;
				//m_Scal = Vec3(1.0,m_Scaled*m_ScalSpeed,1.0);
				m_Scal = Vec3(0, m_Scaled*m_ScalSpeed, 0);
				m_Scaled = point.y;

				m_needUpdate = true;

				return;
			}
			else if(capMode == CScalZ)         /*当绕z缩放，得到缩放矢量*/
			{
				m_Scaled = point.y - m_Scaled;
				m_Scal = Vec3(0,0,m_Scaled*m_ScalSpeed);
				m_Scaled = point.y;

				m_needUpdate = true;
				return ;
			}
			else if(capMode == CRotX)         /*当绕x旋转，得到旋转矢量*/
			{
				m_Roted = point.y - m_Roted;
				m_Rot = Vec3(m_Roted*m_RotSpeed,0.0,0.0);
				m_Roted = point.y;

				m_needUpdate = true;
				return ;
			}
			else if(capMode == CRotY)         /*当绕y旋转，得到旋转矢量*/
			{
				m_Roted = point.y - m_Roted;
				m_Rot = Vec3(0.0,m_Roted*m_RotSpeed,0.0);
				m_Roted = point.y;
				
				m_needUpdate = true;
				return ;
			}
			else if(capMode == CRotZ)         /*当绕z旋转，得到旋转矢量*/
			{
				m_Roted = point.y - m_Roted;
				m_Rot = Vec3(0.0,0.0,m_Roted*m_RotSpeed);
				//m_Rot.z = m_Rot.z + m_Roted * 1;
				m_Roted = point.y;

				m_needUpdate = true;
				return ;
			}

		}
		else   
		{/*在移动后再做捕捉判断，不然会出现移动过程中捕捉错误的情况*/
			IsIntersectWith(lookray);   
		}
	}

	void vgAxis::OnMouseMove( vgKernel::EditMode editMode, CPoint point, bool bHasOperate )
	{
		static uint cnt;

		Vec3 position = CamMgrHolder::getSingleton().getCamManager()->getCurrentPosition();
		Vec3 posaim = Trans2DTo3D(point);
		Vec3 poscam = position;

		Vec3 dir = posaim - poscam;

		Ray lookray = Ray(poscam, dir);

		float diss;
		Vec3 pos1;

		if ( bHasOperate )
		{

			if ( editMode == vgKernel::ATrans )
			{
				if(capMode == CTransX)                           /*如果是x轴*/
				{
					if(m_planeXY.InterSect(lookray,diss) && diss >0.0)/*如果和xy构造面相交*/
					{
						pos1 = lookray.getPoint(diss);           /*得到交点*/
						m_Trans = pos1 - m_Trans;                /*平移量*/
						m_Trans.y = 0.0;                         /*锁定y轴*/
						m_Trans.z = 0.0;                  

						MoveTo(m_Trans);
						m_Trans = pos1;

						m_needUpdate = true;
						return ;
					}
					else if(m_planeXZ.InterSect(lookray,diss) && diss >0.0)/*如果和xz构造面相交*/
					{
						pos1 = lookray.getPoint(diss);           /*得到交点*/
						m_Trans = pos1 - m_Trans;                /*平移量*/

						m_Trans.y = 0.0;                         /*锁定y轴*/
						m_Trans.z = 0.0;     

						MoveTo(m_Trans);
						m_Trans = pos1;

						m_needUpdate = true;
						return ;
					}
				}

				else if(capMode == CTransY)                      /*如果是y轴*/
				{
					////TRACE("Inner Y %d Mode %d\n", cnt++, capMode);
					// debug here
					if(m_planeXY.InterSect(lookray,diss) && diss >0.0)
					{
						////TRACE("Inner1 Y %d Mode %d\n", cnt++, capMode);

						pos1 = lookray.getPoint(diss);           /*得到交点*/
						m_Trans = pos1 - m_Trans;                /*平移量*/

						m_Trans.x = 0.0;                         /*锁定x轴*/
						m_Trans.z = 0.0;

						MoveTo(m_Trans);
						m_Trans = pos1;

						m_needUpdate = true;
					}
					else if(m_planeYZ.InterSect(lookray,diss) && diss >0.0)
					{
						////TRACE("Inner2 Y %d Mode %d\n", cnt++, capMode);

						pos1 = lookray.getPoint(diss);           /*得到交点*/
						m_Trans = pos1 - m_Trans;                /*平移量*/

						m_Trans.x = 0.0;                         /*锁定x轴*/
						m_Trans.z = 0.0;

						MoveTo(m_Trans);
						m_Trans = pos1;

						m_needUpdate = true;
					}
				}

				else if(capMode == CTransZ)                      /*如果是z轴*/
				{
					if(m_planeXZ.InterSect(lookray,diss) && diss >0.0)
					{
						pos1 = lookray.getPoint(diss);           /*得到交点*/
						m_Trans = pos1 - m_Trans;                /*平移量*/

						m_Trans.x = 0.0;                         /*锁定x轴*/
						m_Trans.y = 0.0;

						MoveTo(m_Trans);
						m_Trans = pos1;

						m_needUpdate = true;
					}
					else if(m_planeYZ.InterSect(lookray,diss) && diss >0.0)
					{
						pos1 = lookray.getPoint(diss);           /*得到交点*/
						m_Trans = pos1 - m_Trans;                /*平移量*/

						m_Trans.x = 0.0;                         /*锁定x轴*/
						m_Trans.y = 0.0;

						MoveTo(m_Trans);
						m_Trans = pos1;

						m_needUpdate = true;
					}
				}
				else if(capMode == CTransXY)                          /*如果是xy*/
				{
					if(m_planeXY.InterSect(lookray,diss) && diss >0.0)/*只计算和XY构造面的交点*/
					{
						pos1 = lookray.getPoint(diss);                /*得到交点*/
						m_Trans = pos1 - m_Trans;                     /*平移量*/
						m_Trans.z = 0.0;

						MoveTo(m_Trans);
						m_Trans = pos1;

						m_needUpdate = true;
					}
				}

				else if(capMode == CTransXZ)                       /*如果是xz*/
				{
					if(m_planeXZ.InterSect(lookray,diss) && diss >0.0)
					{
						pos1 = lookray.getPoint(diss);            /*得到交点*/
						m_Trans = pos1 - m_Trans;                 /*平移量*/
						m_Trans.y = 0.0;

						MoveTo(m_Trans);
						m_Trans = pos1;

						m_needUpdate = true;
					}
				}
				else if(capMode == CTransYZ)                      /*如果是yz*/
				{
					if(m_planeYZ.InterSect(lookray,diss) && diss >0.0)
					{
						pos1 = lookray.getPoint(diss);            /*得到交点*/
						m_Trans = pos1 - m_Trans;                 /*平移量*/
						m_Trans.x = 0.0;

						MoveTo(m_Trans);
						m_Trans = pos1;

						m_needUpdate = true;
					}
				}
			}
			else if ( editMode == vgKernel::ARot )
			{
				if(capMode == CRotX)         /*当绕x旋转，得到旋转矢量*/
				{
					m_Roted = point.y - m_Roted;
					m_Rot = Vec3(m_Roted*m_RotSpeed,0.0,0.0);
					m_Roted = point.y;

					m_needUpdate = true;
					return ;
				}
				else if(capMode == CRotY)         /*当绕y旋转，得到旋转矢量*/
				{
					m_Roted = point.y - m_Roted;
					m_Rot = Vec3(0.0,m_Roted*m_RotSpeed,0.0);
					m_Roted = point.y;

					m_needUpdate = true;
					return ;
				}
				else if(capMode == CRotZ)         /*当绕z旋转，得到旋转矢量*/
				{
					m_Roted = point.y - m_Roted;
					m_Rot = Vec3(0.0,0.0,m_Roted*m_RotSpeed);
					//m_Rot.z = m_Rot.z + m_Roted * 1;
					m_Roted = point.y;

					m_needUpdate = true;
					return ;
				}
			}
			else if ( editMode == vgKernel::AScal )
			{
				if(capMode == CScalXYZ)         /*当绕全轴缩放，得到缩放矢量*/
				{
					m_Scaled = point.y - m_Scaled;
					m_Scal = Vec3(m_Scaled*m_ScalSpeed,m_Scaled*m_ScalSpeed,m_Scaled*m_ScalSpeed);
					m_Scaled = point.y;

					m_needUpdate = true;
				}
				else if(capMode == CScalX)         /*当绕x缩放，得到缩放矢量*/
				{
					m_Scaled = point.y - m_Scaled;
					m_Scal = Vec3(m_Scaled*m_ScalSpeed,0,0);
					m_Scaled = point.y;

					m_needUpdate = true;
				}
				else if(capMode == CScalY)         /*当绕y缩放，得到缩放矢量*/
				{
					m_Scaled = point.y - m_Scaled;
					//m_Scal = Vec3(1.0,m_Scaled*m_ScalSpeed,1.0);
					m_Scal = Vec3(0, m_Scaled*m_ScalSpeed, 0);
					m_Scaled = point.y;

					m_needUpdate = true;

					return;
				}
				else if(capMode == CScalZ)         /*当绕z缩放，得到缩放矢量*/
				{
					m_Scaled = point.y - m_Scaled;
					m_Scal = Vec3(0,0,m_Scaled*m_ScalSpeed);
					m_Scaled = point.y;

					m_needUpdate = true;
					return ;
				}
			}
		}

		else
		{
			IsIntersectWith(lookray);
		}


	}
	/************************************************************************/
	/*               鼠标右键松开时，放弃所有选择方式                       */
	/************************************************************************/
	void vgAxis::OnRButtonUp( UINT nFlags, CPoint point )
	{
		capMode = CEmpty;
	}
	/************************************************************************/
	/*               鼠标左键松开时，更新构造面位置                         */
	/************************************************************************/

	void vgAxis::OnLButtonUp( UINT nFlags, CPoint point )
	{
		UpdatePlane();
		// update by chunyongma@08/10/5
		ResetUpdate();
	}
	/************************************************************************/
	/*   鼠标左键按下时，首先判断射线与哪一个构造面相交，并记录下交点坐标   */
	/************************************************************************/

	void vgAxis::OnLButtonDown( UINT nFlags, CPoint point )
	{
		m_Roted = point.y;
		m_Scaled = point.y;
		Vec3 posaim = Trans2DTo3D(point);

		//Vec3 poscam = Vec3(m_camera.g_eye[0],m_camera.g_eye[1],m_camera.g_eye[2]);

		Vec3 poscam = CamMgrHolder::getSingleton().getCamManager()->getCurrentPosition();
		Vec3 dir = posaim - poscam;

		Ray lookray = Ray(poscam, dir);

		float dis;

		if(capMode == CTransX)                                   /*如果是x轴*/
		{
			if(m_planeXY.InterSect(lookray,dis) && dis >0.0)     /*如果射线与XY面相交*/
			{
				m_Trans = lookray.getPoint(dis);                 /*得到交点*/
			}
			else if(m_planeXZ.InterSect(lookray,dis) && dis >0.0)/*如果射线与XZ面相交*/
			{
				m_Trans = lookray.getPoint(dis);                 /*得到交点*/
			}
		}
		else if(capMode == CTransY)
		{
			if(m_planeXY.InterSect(lookray,dis) && dis >0.0)
			{
				m_Trans = lookray.getPoint(dis);          
			}
			else if(m_planeYZ.InterSect(lookray,dis) && dis >0.0)
			{
				m_Trans = lookray.getPoint(dis);           
			}
		}
		else if(capMode == CTransZ)
		{
			if(m_planeXZ.InterSect(lookray,dis) && dis >0.0)
			{
				m_Trans = lookray.getPoint(dis);   
			}
			else if(m_planeYZ.InterSect(lookray,dis) && dis >0.0)
			{
				m_Trans = lookray.getPoint(dis);          
			}
		}
		else if(capMode == CTransXY)
		{
			if(m_planeXY.InterSect(lookray,dis) && dis >0.0)
			{
				m_Trans = lookray.getPoint(dis);        
			}
		}
		else if(capMode == CTransXZ)
		{
			if(m_planeXZ.InterSect(lookray,dis) && dis >0.0)
			{
				m_Trans = lookray.getPoint(dis);        
			}
		}
		else if(capMode == CTransYZ)
		{
			if(m_planeYZ.InterSect(lookray,dis) && dis >0.0)
			{
				m_Trans = lookray.getPoint(dis);       
			}
		}
	}
	/************************************************************************/
	/*            End of OnLButtonDown()                                    */
	/************************************************************************/

	void vgAxis::SetRotSpeed( const float& rotSpeed )
	{
		m_RotSpeed = rotSpeed;
	}

	void vgAxis::SetScalSpeed( const float& scalSpeed )
	{
		m_ScalSpeed = scalSpeed;
	}

	float vgAxis::GetSize()
	{
		return m_Size;
	}

	float vgAxis::GetRotSpeed()
	{
		return m_RotSpeed;
	}
	float vgAxis::GetScalSpeed()
	{
		return m_ScalSpeed;
	}

	const Vec3& vgAxis::GetTrans()
	{
		return m_Trans;
	}

	const Vec3& vgAxis::GetRot()
	{
		return m_Rot;
	}

	const Vec3& vgAxis::GetScal()
	{
		return m_Scal;
	}

	vgAxis::CaptureMod vgAxis::GetcapMod()
	{
		return capMode;
	}
	void vgAxis::Axis::Render()
	{

	}
	/************************************************************************/
	/*                     判断射线是否与一条轴相交                         */
	/************************************************************************/

	BOOL vgAxis::Axis::IsIntersectWith( const Ray& ray )
	{
		if(tri1.InterSect(ray)|| tri2.InterSect(ray)||tri3.InterSect(ray)||tri4.InterSect(ray))
			return TRUE;
		else
			return FALSE;
	}
	/************************************************************************/
	/*                     绘制一个三角形                                   */
	/************************************************************************/

	void vgTriangle::Render()
	{

		glBegin(GL_TRIANGLES);
		glVertex3f(p0.x, p0.y, p0.z);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glEnd();
	}
	/************************************************************************/
	/*         绘制两个三角形组成的面，半透明并有边线                       */
	/************************************************************************/

	void vgAxis::AxisPlane::Render()
	{
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0,1.0,0.0,0.5);
		glBegin(GL_LINES);
		glVertex3f(tri1.p1.x, tri1.p1.y, tri1.p1.z);
		glVertex3f(tri1.p2.x, tri1.p2.y, tri1.p2.z);
		glVertex3f(tri2.p1.x, tri2.p1.y, tri2.p1.z);
		glVertex3f(tri2.p0.x, tri2.p0.y, tri2.p0.z);
		glEnd();
		tri1.Render();
		tri2.Render();
		glDisable(GL_BLEND);

	}

	BOOL vgAxis::AxisPlane::IsIntersectWith( const Ray& ray )
	{
		if(tri1.InterSect(ray) || tri2.InterSect(ray))
			return TRUE;
		else
			return FALSE;
	}
	/************************************************************************/
	/*                   绘制一个三角面，半透明并有边线                     */
	/************************************************************************/

	void vgAxis::vgTriPlane::Render(const char& renderMode)
	{
		if(renderMode == 1)
		{
			glEnable (GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0,1.0,0.0,0.5);
			glBegin(GL_LINE_LOOP);
			glVertex3f(tri.p0.x, tri.p0.y, tri.p0.z);
			glVertex3f(tri.p1.x, tri.p1.y, tri.p1.z);
			glVertex3f(tri.p2.x, tri.p2.y, tri.p2.z);
			glEnd();
			tri.Render();
			glDisable(GL_BLEND);
		}
		else if(renderMode == 2)
		{
			glEnable (GL_BLEND);
			glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0,1.0,0.0,0.3);
			glBegin(GL_LINE_LOOP);
			glVertex3f(tri.p0.x, tri.p0.y, tri.p0.z);
			glVertex3f(tri.p1.x, tri.p1.y, tri.p1.z);
			glVertex3f(tri.p2.x, tri.p2.y, tri.p2.z);
			glEnd();
			tri.Render();
			glDisable(GL_BLEND);
		}
	}
	/************************************************************************/
	/*                    判断射线与三角面是否相交                          */
	/************************************************************************/

	BOOL vgAxis::vgTriPlane::IsIntersectWith( const Ray& ray )
	{
		if(tri.InterSect(ray))
			return TRUE;
		else
			return FALSE;
	}	
	
}// end of namespace vgKernel
