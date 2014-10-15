#pragma once

#define maxfloat 1000000.0;

#include <vgKernel/vgkAxis.h>
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkRay.h>


#include <vgKernel/vgkAxis.h>
#include <vgKernel/vgkMath.h>



namespace vgKernel {


	enum EditMode{ ATrans, ARot, AScal, Default }; //add by ZhouZY 2009-11-11 9:37

	class vgTriangle
	{
	public:
		vgTriangle(){}
		~vgTriangle(){}
		Vec3 p0,p1,p2;
		float interlength;
		vgTriangle(const Vec3& point0,const Vec3& point1,const Vec3& point2)
		{
			p0 = point0;
			p1 = point1;
			p2 = point2;
		}
		void Render();
		BOOL InterSect(const Ray& ray, float& distance)//计算射线与三角形相交关系
		{
			std::pair<bool, float> result = vgKernel::Math::intersects( ray , p0 , p1 , p2 );
			distance = result.second;
			if(result.first == true)
				return TRUE;
			else
				return FALSE;
		}
		BOOL InterSect(const Ray& ray)//计算射线与三角形相交关系
		{
			std::pair<bool, float> result = vgKernel::Math::intersects( ray , p0 , p1 , p2 );
			if(result.first == true)
				return TRUE;
			else
				return FALSE;
		}
	};

	class vgPlane
	{
	public:
		vgTriangle tri1,tri2;
		vgPlane(){};
		vgPlane(const vgTriangle& t1, const vgTriangle& t2)
		{
			tri1 = t1;
			tri2 = t2;
		}
		vgPlane(const Vec3& v1, const Vec3& v2, const Vec3& v3, const Vec3& v4)
		{
			tri1 = vgTriangle(v1,v2,v3);
			tri2 = vgTriangle(v3,v4,v1);
		}
		BOOL InterSect(const Ray& ray, float& distance)//计算射线与三角形相交关系
		{
			std::pair<bool, float> result1 = vgKernel::Math::intersects( ray , tri1.p0 , tri1.p1 ,tri1.p2);
			std::pair<bool, float> result2 = vgKernel::Math::intersects( ray , tri2.p0 , tri2.p1 ,tri2.p2);
			if(result1.first == true && result1.second>0.0)
			{
				distance = result1.second;
				return TRUE;
			}
			else if(result1.first == true && result1.second>0.0)
			{
				distance = result2.second;
				return TRUE;
			}			
			else
				return FALSE;
		}
	};
	class vgAxis
	{
	private:
		//enum EditMod{ATrans,ARot,AScal} editMode;
		enum CaptureMod{CTransX,CTransY,CTransZ,CTransXY,CTransXZ,CTransYZ,
			CScalX,CScalY,CScalZ,CScalXY,CScalXZ,CScalYZ,CScalXYZ,
			CRotX,CRotY,CRotZ,CEmpty} capMode;

		Vec3	 m_Trans,   m_Rot,   m_Scal;
		float    m_Roted,   m_Scaled;
		float    m_RotSpeed,  m_ScalSpeed;           /*用于调节鼠标移动量与物体状态改变量的比例关系*/
		vgTriangle m_planeXY,  m_planeXZ,  m_planeYZ;  /*“无限大的”的构造平面*/
		float m_Size, m_SizeScale;
		Vec3 m_Centre;
		Vec3 points[50];
		Vec3 constpoints[50];
		Vec3 constructionPoints[9];

		bool m_needUpdate;

		vgKernel::EditMode  m_editMode;  //add by ZhouZY 2009-11-11 9:37

		class Axis
		{
			friend class vgAxis;
		private:
			vgTriangle tri1,tri2;//每条轴有四个三角面组成一对相互垂直的面，用来测试捕捉
			vgTriangle tri3,tri4;
		public:
			void Render();
			BOOL IsIntersectWith(const Ray& ray); //给定一条射线，判断其是否穿过轴
			Axis(){}
			~Axis(){}
		};

		Axis AxisX,AxisY,AxisZ;


		class AxisPlane
		{
			friend class vgAxis;
		private:
			vgTriangle tri1,tri2;//每个面有两个三角面组成，用来测试捕捉
		public:
			void Render();
			BOOL IsIntersectWith(const Ray& ray); //给定一条射线，判断其是否穿过轴
			AxisPlane(){}
			~AxisPlane(){}
		};
		AxisPlane AxisPlaneXY,AxisPlaneXZ,AxisPlaneYZ,//移动判断面
			RotAxisPlaneX,RotAxisPlaneY,RotAxisPlaneZ;   //旋转判断面

		class vgTriPlane
		{
			friend class vgAxis;
		private:
			vgTriangle tri;
		public:
			void Render(const char& renderMode);
			BOOL IsIntersectWith(const Ray& ray);
			vgTriPlane(const Vec3& p0,const Vec3& p1,const Vec3& p2)
			{
				tri =vgTriangle(p0,p1,p2);
			};
			vgTriPlane(){};
			~vgTriPlane(){};
		};
		vgTriPlane CapPlane,ScalPlaneXYZ,ScalPlaneX,ScalPlaneY,ScalPlaneZ;

	public:

		
		bool NeedUpdate()
		{
			return m_needUpdate;
		}

		void ResetUpdate()
		{
			m_Rot.x = 0;
			m_Rot.y = 0;
			m_Rot.z = 0;

			m_Scal.x = 0;
			m_Scal.y = 0;
			m_Scal.z = 0;

			m_needUpdate = false;
		}

		Vec3 GetCenter()
		{
			return m_Centre;
		}

		void Update();

		void UpdatePlane();

		Vec3 Trans2DTo3D(CPoint &point);

		void Init();

		void Render();                  //绘制坐标轴

		void RenderAxisCone(const char& renderMode);

		void MoveTo(const Vec3& pos);   //移动坐标轴到指定位置

		void SetCenter(const Vec3& pos);

		//void SetSize(const float& size); //设置坐标轴大小，使之占据屏幕一定比例
		void SetSize( const float& size )
		{
			m_Size = size*m_SizeScale;
			Update();
		}
		void ChangeSizeScale( const float& sizeScale )
		{
			m_SizeScale += sizeScale;
			if (m_SizeScale<0.1f)
			{
				m_SizeScale = 0.1f;
			}
		}
		void SetRotSpeed(const float& rotSpeed);

		void SetScalSpeed(const float& scalSpeed);

		float GetSize();

		float GetRotSpeed();

		float GetScalSpeed();

		void SetEditMode( vgKernel::EditMode editMode )
		{
			m_editMode = editMode;
		}

		vgKernel::EditMode GetEditMode()
		{
			return m_editMode; 
		}

		CaptureMod GetcapMod();

		const Vec3& GetTrans();

		const Vec3& GetRot();

		const Vec3& GetScal();

		BOOL IsIntersectWith(const Ray& ray);

		void OnMouseMove(UINT nFlags, CPoint point);

		void OnMouseMove( vgKernel::EditMode editMode, CPoint point, bool bHasOperate );

		void OnRButtonUp(UINT nFlags, CPoint point);

		void OnLButtonUp(UINT nFlags, CPoint point);

		void OnLButtonDown(UINT nFlags, CPoint point);

		vgAxis();
		~vgAxis();
	};	
	
}// end of namespace vgKernel
