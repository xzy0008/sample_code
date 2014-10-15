#include "StdAfx.h"
#include "WaterLight.h"

namespace VR_Ocean
{

CLight::CLight(void) : ColorArray( 0 ), BasicPos( 0 ), Indices( 0 )
{
	ColorArray = new float[ 12*4 ];
	Vertices = new float[ 12*3 ];
	Indices = new unsigned int[ 12 ];

	ColorArray[0] = 0.05f; ColorArray[1] = 0.05f; ColorArray[2] = 0.05f; ColorArray[3] = 0.05f;
	ColorArray[6*4 + 0] = 0.25f; ColorArray[6*4 + 1] = 0.25f; ColorArray[6*4 + 2] = 0.25f; ColorArray[6*4 + 3] = 0.25f;
	
	//
	//第0组数据在渲染时应当改变，故在这时不写入数组
	//
	Vertices[1] = 0.0f;
	Vertices[6*3 + 0] = 0.0f; Vertices[6*3 + 2] = 0.0f; Vertices[6*3 + 1] = 0.0f;

	for( int i = 1; i <= 5 ; ++i )
	{
		float Val=( 6 - i )*0.03f + 0.05f;
		//Val=0.13;
		ColorArray[ ( 6 - i )*4 + 0 ] = Val;
		ColorArray[ ( 6 - i )*4 + 1 ] = Val;
		ColorArray[ ( 6 - i )*4 + 2 ] =Val; 
		ColorArray[ ( 6 - i )*4 + 3 ] = ( 6 - i )*0.043f ;

		ColorArray[ ( 6 + i )*4 + 0 ] = Val;
		ColorArray[ ( 6 + i )*4 + 1 ] = Val;
		ColorArray[ ( 6 + i )*4 + 2 ] = Val; 
		ColorArray[ ( 6 + i )*4 + 3 ] = ( 6 - i )*0.043f ;

		Vertices[ ( 6 - i )*3 + 0 ] = i*0.5f; 
		Vertices[ ( 6 - i )*3 + 1 ] = 0.0f;
		Vertices[ ( 6 - i )*3 + 2 ] = 0.0f; 
		Vertices[ ( 6 + i )*3 + 0 ] = -i*0.5f; 
		Vertices[ ( 6 + i )*3 + 1 ] = 0.0f;
		Vertices[ ( 6 + i )*3 + 2 ] = 0.0f; 
	}

	for( int i = 0; i < 12; ++i )
	{
		Indices[i] = i;
	}
}

CLight::~CLight()
{
	if( ColorArray )
		delete[] ColorArray;
	if( Indices )
		delete[] Indices;
	if( Vertices )
		delete[] Vertices;
}

void CLight::update()
{

}

void CLight::renderGLScene( V4 p)
{
	glDisable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);

	V4 pos=p;
	static float offset_factor = 0.0f;
	static int flag = 0;
	if( offset_factor < -5.0f )
		flag = 0;
	if( offset_factor > 5.0f )
		flag = 1;
	if( 0 == flag ) 
		offset_factor += 0.15f;
	if( 1 == flag )	
		offset_factor -= 0.15f;
	int RayNum=6;

	for( float i = 0; i <RayNum ; ++i )
	{
			pos.x = 4.5*cos(i/(float)RayNum*2*PI);
			pos.y = 4.5*sin(i/(float)RayNum*2*PI);

			if( i/2 == 0 )
				drawLight( pos, offset_factor, i/(float)RayNum*360);
			else
				drawLight( pos, -offset_factor, i/(float)RayNum*360);
	}
	for( float i = 0; i <RayNum/2 ; ++i )
	{
		pos.x = 2*cos((i+0.25)/(float)RayNum*4*PI);
		pos.y = 2*sin((i+0.25)/(float)RayNum*4*PI);

		if( i/2 == 0 )
			drawLight( pos, offset_factor, (i+0.25)/(float)RayNum*720);
		else
			drawLight( pos, -offset_factor, (i+0.25)/(float)RayNum*720);
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_TEXTURE_2D );

	glDisable(GL_ALPHA_TEST);
}

void CLight::drawLight( const V4 pos, float pp, float theta )
{
	//
	// 改写第0组数据使光线动起来
	//
	Vertices[0] = pp; Vertices[2] = -180.0f; 

	glPushMatrix();
	glTranslatef( pos.x, pos.y, pos.z );
	glRotatef(theta+90,0,0,1);
		glBegin(GL_TRIANGLE_FAN);
		for(int i=0;i<12;i++)
		{
			glColor4f(ColorArray[0+i*4],ColorArray[1+4*i],ColorArray[2+4*i],ColorArray[3+4*i]);
			glVertex3f(Vertices[0+3*i],Vertices[1+3*i],Vertices[2+3*i]);
		}
		glEnd();
	glPopMatrix();
}

}
