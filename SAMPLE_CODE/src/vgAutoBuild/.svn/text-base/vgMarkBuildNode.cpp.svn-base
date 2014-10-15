#include <vgStableHeaders.h>
#include <vgAutoBuild/vgMarkBuildNode.h>
#include <vgKernel/vgkMath.h>
#include <vgKernel/vgkOpenGLSupport.h>
#include <gl/glut.h>
#include "InforCommentDlg.h"

namespace vgAutoBuild
{
	VGK_RENDERER_IMPLEMENT( MarkBuildNode , RENDERER_TYPE_LANDMARKBUILD )

	MarkBuildNode::MarkBuildNode(vgKernel::Vec3 polygon)
		: _uniqueID( vgKernel::UniqueIDFactory::getUniqueID() )
	{
		m_innerPoint = polygon;
		
		_callListId = 0;

		m_markEnable = true;

		FlickerObject::setFlickerState(true, 2, 100);
	
		FlickerObject::setForeColor(78, 255, 0, 78);
		FlickerObject::setBackColor(78, 255, 0, 204);
		
		computeBoundingBox();
	}

	void MarkBuildNode::invalidateRendering()
	{
		if ( _callListId != 0 )
		{
			VGK_CHECK_OPENGL_ERROR();

			glDeleteLists( _callListId , 1 );
			_callListId = 0;

			VGK_CHECK_OPENGL_ERROR();
		}
	}

	void MarkBuildNode::renderUsingDisplayList()
	{
		//assert(0);

		VGK_CHECK_OPENGL_ERROR();

		if ( _callListId == 0 )
		{
			_callListId = glGenLists( 1 );   
			assert( _callListId != 0 );

			glNewList( _callListId, GL_COMPILE );
			renderOnceForDisplayList();
			glEndList();	
		}
		VGK_CHECK_OPENGL_ERROR();

		assert( _callListId != 0 );

		glPushMatrix();
		glCallList( _callListId );
		glPopMatrix();
	}

	void MarkBuildNode::renderOnceForDisplayList()
	{

		VGK_CHECK_OPENGL_ERROR();

		glDisable( GL_TEXTURE_2D );
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#if 0
		glColor4f( 0.305, 1.0, 0.0, 0.5);
#else
		glColor4f( FlickerObject::getCurrentColor().red/255, 
			FlickerObject::getCurrentColor().green/255, 
			FlickerObject::getCurrentColor().blue/255, 
			FlickerObject::getCurrentColor().alpha/255 );
#endif
		glPushMatrix();
#if 1
		glBegin( GL_QUADS );
		    // Bottom Face
		    glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z-2);
			glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z-2);
			glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z+2);
			glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z+2);

			// Front Face
			glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z+2);
			glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z+2);
			glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z+5);
			glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z+5);
			// Back Face
			glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z-2);
			glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z-5);
			glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z-5);
			glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z-2);
			// Right face
			glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z-2);
			glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z-5);
			glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z+5);
			glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z+2);
			// Left Face
			glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z-2);
			glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z+2);
			glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z+5);
			glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z-5);
			// Top Face
			glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z-5);
			glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z+5);
			glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z+5);
			glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z-5);
	    glEnd();
#endif
		glTranslatef(m_innerPoint.x,m_innerPoint.y+5,m_innerPoint.z);

		glutSolidSphere(5,10,10);

		glPopMatrix();
		VGK_CHECK_OPENGL_ERROR();


	}

	void MarkBuildNode::renderWithoutDisplayList()
	{
		VGK_CHECK_OPENGL_ERROR();

		glPushMatrix();

		glDisable( GL_TEXTURE_2D );
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glColor4f( FlickerObject::getCurrentColor().red/255.0f, 
			FlickerObject::getCurrentColor().green/255.0f, 
			FlickerObject::getCurrentColor().blue/255.0f, 
			FlickerObject::getCurrentColor().alpha/255.0f );

		glPushMatrix();

		glBegin( GL_QUADS );
		// Bottom Face
		glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z-2);
		glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z-2);
		glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z+2);
		glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z+2);

		// Front Face
		glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z+2);
		glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z+2);
		glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z+5);
		glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z+5);
		// Back Face
		glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z-2);
		glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z-5);
		glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z-5);
		glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z-2);
		// Right face
		glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z-2);
		glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z-5);
		glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z+5);
		glVertex3f(m_innerPoint.x+2, m_innerPoint.y-12+25, m_innerPoint.z+2);
		// Left Face
		glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z-2);
		glVertex3f(m_innerPoint.x-2, m_innerPoint.y-12+25, m_innerPoint.z+2);
		glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z+5);
		glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z-5);
		// Top Face
		glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z-5);
		glVertex3f(m_innerPoint.x-5, m_innerPoint.y+12+25, m_innerPoint.z+5);
		glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z+5);
		glVertex3f(m_innerPoint.x+5, m_innerPoint.y+12+25, m_innerPoint.z-5);
		glEnd();

		glTranslatef(m_innerPoint.x,m_innerPoint.y+5,m_innerPoint.z);

		glutSolidSphere(5,10,10);

		glPopMatrix();
		VGK_CHECK_OPENGL_ERROR();
		
		glPopMatrix();

	}

	void MarkBuildNode::initialise()
	{
		_callListId = 0;

		FlickerObject::setFlickerState(true, 2, 100);

		FlickerObject::setForeColor(78, 255, 0, 78);
		FlickerObject::setBackColor(78, 255, 0, 204);

		computeBoundingBox();
	}

	void MarkBuildNode::translate( const float& x, const float& y, const float& z )
	{
		return;

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		//TRACE("translate Matrix \n");

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

		this->notifyOberversOnEvent(VG_OBS_PROPCHANGED, NULL);

	}

	void MarkBuildNode::rotateSelf( const float& angle, const float& x, const float& y, const float& z )
	{
		return;

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(-_dynamicBox.getCenter().x, -_dynamicBox.getCenter().y, -_dynamicBox.getCenter().z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createRotationMatrix(angle, x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(_dynamicBox.getCenter().x, _dynamicBox.getCenter().y, _dynamicBox.getCenter().z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);
	}

	void MarkBuildNode::rotate( const float& angle, const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z )
	{
		return;

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;

		vgKernel::Math::createTranslationMatrix(-cx, -cy, -cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createRotationMatrix(angle, x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(cx, cy,cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

	}

	void MarkBuildNode::scale( const float& cx, const float& cy, const float& cz, const float& x, const float& y, const float& z )
	{
		return;

		vgKernel::Mat4 tran;
		vgKernel::Mat4 tmp;


		vgKernel::Math::createTranslationMatrix(-cx, -cy, -cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createScaleMatrix(x, y, z, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		vgKernel::Math::createTranslationMatrix(cx, cy,cz, tran);
		vgKernel::Math::multiplyMatrix(tran, _matrix, tmp);
		_matrix = tmp;

		_dynamicBox = _staticBox;
		_dynamicBox.matrixTranslation(_matrix);

	}

	float MarkBuildNode::setDistanceToViewer( const vgKernel::Vec3& viewer_pos )
	{
		//------------------------------------------
		// 1.首先通过包围盒计算与视点的距离.
		//------------------------------------------
		float delta[3];

		for ( int i = 0 ; i < 3 ; ++ i )
		{
			float _cur = viewer_pos[i];
			float _max = _dynamicBox._maxVertex.v[i];
			float _min = _dynamicBox._minVertex.v[i];

			if ( _cur > _max )
			{
				delta[i] = _cur - _max;
			}
			else if ( _cur < _min )
			{
				delta[i] = _min - _cur;
			}
			else
			{
				delta[i] = 0.0f;
			}
		}

		_squaredDistanceToViewer = 
			delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2];

		// 2.更新_distanceLod

		return _squaredDistanceToViewer;

	}

	void MarkBuildNode::render()
	{
		if (!m_markEnable)
		{
			return;
		}

		if( getVisible() == false )
		{
			return;
		}
		renderWithoutDisplayList();
	}

	void MarkBuildNode::computeBoundingBox()
	{
		_dynamicBox._maxVertex = m_innerPoint + vgKernel::Vec3(5, 37, 5);
		_dynamicBox._minVertex = m_innerPoint + vgKernel::Vec3(-5, 0, -5);
	}

	void MarkBuildNode::fireClicked()
	{
		CInforCommentDlg *dlg = new CInforCommentDlg(this);
		dlg->Create(CInforCommentDlg::IDD, NULL);
		dlg->ShowWindow(SW_SHOW); 

	}

	void MarkBuildNode::writeToFile( CFile &fp )
	{
		fp.Write(&_uniqueID, sizeof(vgKernel::UniqueID));

		int length= _meshName.size();
		fp.Write(&length, sizeof(int));//文件名长度
		fp.Write(_meshName.c_str(), length);//文件名

		fp.Write(&m_markEnable, sizeof(bool));
		fp.Write(&m_innerPoint, sizeof(vgKernel::Vec3));
	}

	bool MarkBuildNode::readFromFile( CFile &fp )
	{
		fp.Read(&_uniqueID, sizeof(vgKernel::UniqueID));

		int length;
		char tempBuffer[255];
		fp.Read(&length , sizeof(int));
		fp.Read(tempBuffer, length);//文件名
		tempBuffer[length] = '\0';
		_meshName = tempBuffer;

		fp.Read(&m_markEnable, sizeof(bool));
		fp.Read(&m_innerPoint, sizeof(vgKernel::Vec3));

		return true;
	}

}
