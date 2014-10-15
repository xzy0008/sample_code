

#include <vgStableHeaders.h>
#include <vgTerritory/vgTerrainHugeImageRender.h>


#if 0


namespace vgTerritory {
	
	//void HugeImageRender::renderScene()
	//{
	//	static bool a = true;
	//	if ( a == true )
	//	{
	//		LogManager::getSingleton().logMessage( _T("rendering") );
	//		a = false;
	//	}

	//	glPushMatrix();
	//	glEnable(GL_TEXTURE_2D);

	//	glTranslatef( 0 , 0.2f , 0 );
	//	/// ¿ªÊ¼±éÀú
	//	for ( HugeImageBlockInfoVector::iterator iter = m_pHugeImageInfoVec->begin() ;
	//		iter != m_pHugeImageInfoVec->end() ; ++ iter )
	//	{
	//		const String& filename = iter->m_BlockFileName;

	//		iter->m_TexturePtr->useBind();

	//		//this->drawQuad( i->m_Vertex );
	//		glBegin(GL_QUADS);
	//		vgKernel::Vec3 v1 = iter->getVertexAsVector3( 0 );
	//		vgKernel::Vec3 v2 = iter->getVertexAsVector3( 1 );
	//		vgKernel::Vec3 v3 = iter->getVertexAsVector3( 2 );
	//		vgKernel::Vec3 v4 = iter->getVertexAsVector3( 3 );

	//		glTexCoord2i(0 , 0 );
	//		glVertex3fv( v1.v );
	//		glTexCoord2i(1 , 0 );
	//		glVertex3fv( v2.v );
	//		glTexCoord2i(1 , 1 );
	//		glVertex3fv( v3.v );
	//		glTexCoord2i(0 , 1 );
	//		glVertex3fv( v4.v );

	//		glEnd();

	//		if ( mFrustum.isVisible( v1 ) )
	//		{
	//			//ImagePtr pimg = ImageFactory::createFromTexturePtr(i->m_TexturePtr);

	//			TextureManager::getSingleton().reloadTexturePtr( iter->m_TexturePtr );

	//			//pimg.setNull();
	//		}
	//		else
	//		{
	//			TextureManager::getSingleton().unloadTexturePtr( iter->m_TexturePtr );
	//		}

	//	}

	//	glDisable(GL_TEXTURE_2D);
	//	glPopMatrix();




	//	/// render frustum
	//	glPushMatrix();
	//	glDisable(GL_TEXTURE_2D);

	//	//ColorValue::Yellow.useBind();

	//	//glBegin(GL_LINE_STRIP);
	//	//for ( int i =  0; i < 8 ; i ++ )
	//	//{
	//	//	vgKernel::Vec3 aai = mFrustum.getWorldCorner( i );
	//	//	
	//	//	for ( int j = 0 ; j < 8 ; j ++ )
	//	//	{
	//	//		glVertex3fv( aai.v );

	//	//		vgKernel::Vec3 aaj = mFrustum.getWorldCorner( j );
	//	//		glVertex3fv( aaj.v );
	//	//	}
	//	//}
	//	//glEnd();

	//	/// render frustum
	//	glDisable(GL_TEXTURE_2D);

	//	//ColorValue::Red.useBind();

	//	glColor3f(1,0,0);



	//	glBegin(GL_LINE_STRIP);
	//	for ( int i =  0; i < 12 ; i ++ )
	//	{
	//		vgKernel::Vec3 aai = mFrustum.getWorldCorner2( i );

	//		for ( int j = 0 ; j < 12 ; j ++ )
	//		{
	//			glVertex3fv( aai.v );

	//			vgKernel::Vec3 aaj = mFrustum.getWorldCorner2( j );
	//			glVertex3fv( aaj.v );
	//		}
	//	}
	//	glEnd();


	//	//ColorValue::Blue.useBind();

	//	//glBegin(GL_LINE_STRIP);


	//	//vgKernel::Vec3 p1 = mFrustum.mExtendPlanes[0].projectVector( vgKernel::Vec3::UNIT_Y );

	//	//glVertex3fv( vgKernel::Vec3)

	//	//for ( int i =  0; i < 8 ; i ++ )
	//	//{
	//	//	vgKernel::Vec3 aai = mFrustum.getWorldCorner( i );

	//	//	for ( int j = 0 ; j < 8 ; j ++ )
	//	//	{
	//	//		glVertex3fv( aai.v );

	//	//		vgKernel::Vec3 aaj = mFrustum.getWorldCorner( j );
	//	//		glVertex3fv( aaj.v );
	//	//	}
	//	//}
	//	//glEnd();



	//	glPopMatrix();

	//	/// render points
	//	//renderPointsInFrustum();

	//}
	//----------------------------------------------------------------
	bool HugeImageRender::initScene()
	{

		assert( isValid() );

		for ( HugeImageBlockInfoVector::const_iterator i = m_pHugeImageInfoVec->begin() ;
			i != m_pHugeImageInfoVec->end() ; ++ i )
		{
			LogManager::getSingleton().logMessage( i->getDetails() );
		}

		this->m_pHugeImageInfoVec->setRatio(15.0f);

		this->m_pHugeImageInfoVec->updateAllTexturePtr( true );

	
		this->updateFrustum();

		this->mCameraPos = vgKernel::Vec3::ZERO;
		this->mCameraLook = vgKernel::Vec3::UNIT_X;
		this->mCameraUp = vgKernel::Vec3::UNIT_Y;



		return true;
	}
	//----------------------------------------------------------------
	void HugeImageRender::updateFrustum()
	{

		float   proj[16];
		float   modl[16];		

		glGetFloatv( GL_PROJECTION_MATRIX, proj );
		glGetFloatv( GL_MODELVIEW_MATRIX, modl );

		mFrustum.setMatrix( Matrix4(proj) , Matrix4(modl) );

		mFrustum.setFarDist( 80 );

		
		//Matrix4  aaa = Matrix4::IDENTITY;

		//aaa.makeTransform( vgKernel::Vec3(1,1,1) , 
		//	vgKernel::Vec3::UNIT_SCALE , Quaternion() );

		//aaa.setTrans(vgKernel::Vec3(100,100,100));

#undef PI

		//aaa.makeInverseTransform( vgKernel::Vec3(1,1,1) , 
		//	vgKernel::Vec3::UNIT_SCALE , Quaternion(Math::PI * 0.5f, vgKernel::Vec3(1,0,0) )   );

		//mFrustum.setCustomMatrix( aaa );


		glPushMatrix();
		
		vgKernel::Vec3  center(1,0,10);
		vgKernel::Vec3  up( 0,1,0);

		up.normalise();
		center.normalise();

		glLoadIdentity();

		gluLookAt(0,0,0, center.x ,center.y , center.z , 
			up.x , up.y , up.z );

		glGetFloatv( GL_MODELVIEW_MATRIX, modl );

		mFrustum.setCustomMatrix( Matrix4( modl ) );

		glPopMatrix();

		mFrustum.turnOnCustomMatrix();

		//mFrustum.turnOffCustomMatrix();

		mFrustum.invalidateFrustum();

		mFrustum.updateFrustum();

		VG_TRACE(  mFrustum.getDetails() );
	}
	//----------------------------------------------------------------
	void HugeImageRender::renderPointsInFrustum()
	{
		glDisable(GL_TEXTURE_2D);

		glPushMatrix();

	
		//ColorValue::Red.useBind();
		glColor3f(1,0,0);

		glPointSize(5);

		glBegin(GL_POINTS);

		const int m_Points_Num = 30;
		const Real m_Points_Interval = 10.0f;

		int n = m_Points_Num / 2;

		for(int i = -n ; i != (n+1) ; i++)
		{
			for(int j = -n ; j != (n+1) ;j ++)
			{
				for(int k = -n ; k != (n+1) ; k++)
				{
					vgKernel::Vec3 v(m_Points_Interval * j ,
						m_Points_Interval * k , 
						m_Points_Interval * i);

					if ( mFrustum.isVisible( v ) )
					{
						glVertex3fv( v.v );
					}
					
				}
			}
		}
		glEnd();

		glPopMatrix();

	}
	
}// end of namespace vgTerritory


#endif
