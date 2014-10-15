




#include <vgStableHeaders.h>
#include <vgTerritory/vgTerrainGpuProgram.h>
#include <vgCam/vgcaCamManager.h>


namespace vgTerritory {
	
	
		
	char *TerrainGpuProgram::vertex_source = "\
		float4 tex2D_bilinear( sampler2D tex, float2 t ) \
		{\
			float2 f = frac( t.xy * 1024.0f ); \
			float texelSize = 1.0f / 1024.0f;\
			\
			float4 t00 = tex2D( tex, t ); \
			float4 t10 = tex2D( tex, t + float2( texelSize, 0.0f ) ); \
			\
			float4 tA  = lerp( t00, t10, f.x );\
			\
			float4 t01 = tex2D( tex, t + float2( 0.0f, texelSize ) ); \
			float4 t11 = tex2D( tex, t + float2( texelSize, texelSize ) ); \
			\
			float4 tB  = lerp( t01, t11, f.x ); \
			\
			return lerp( tA, tB, f.y ); \
		}\
		struct vertex\
		{\
			float4 position  : POSITION;\
			/*float3 normal    : NORMAL;*/\
			/*float4 color0    : COLOR0;*/\
			float2 texcoord0 : TEXCOORD0;\
		};\
		struct fragment\
		{\
			float4 position  : POSITION;\
			float2 texcoord0 : TEXCOORD0;\
			float  fogFactor  : TEXCOORD1;\
			float4  Pos: TEXCOORD2;\
			float  clip0    : CLP0;\
			float  clip1    : CLP1;\
			float  clip2    : CLP2;\
			float  clip3    : CLP3;\
			float  clip4    : CLP4;\
		};\
		uniform float4x4 modelViewProj : state.matrix.mvp;\
		uniform float4x4 projMat : state.matrix.projection;\
		uniform float4x4 modeViewMat : state.matrix.modelview;\
		fragment main( vertex IN, \
			uniform sampler2D displacementTexture : TEXUNIT1,\
			uniform float4 displacementScaler,\
			uniform float4x4 revViewMat ,\
			uniform float4 uvParameter ,\
			uniform float4 clipPlaneParam0, \
			uniform float4 clipPlaneParam1, \
			uniform float4 clipPlaneParam2, \
			uniform float4 clipPlaneParam3 ,\
			uniform float4 userClipPlaneParam ,\
			uniform float2 fogParam, \
			uniform float4 OceanParam\
			)\
		{\
			const float heightScale = uvParameter.x;\
			const float displaceScale = uvParameter.y;\
			IN.position.y = 0.0f;\
			float4 modelviewpos = mul( modeViewMat, IN.position );\
			\
			/*modelviewpos.x -= globalOffset.x;*/\
			/*modelviewpos.z -= globalOffset.y;*/\
			float u = modelviewpos.x * displaceScale - uvParameter.z;\
			float v = modelviewpos.z * displaceScale - uvParameter.w;\
			\
			fragment OUT;\
			float4 displacement = tex2Dbias( displacementTexture, \
				float4( u , v , 0.0 , 0.0 ) );\
			/*float4 displacement = tex2D_bilinear( displacementTexture, \
			float2( u , v ) );*/\
			\
			float4 displacedPosition = \
				float4( IN.position.x, \
				( displacement.x * heightScale) + IN.position.y, \
				IN.position.z, \
				1.0 ); \
				\
			float4 resultPos = mul( modeViewMat , displacedPosition );\
			float4 resultPos2 = mul( revViewMat , resultPos );\
			OUT.position = mul( projMat, resultPos2 );\
			OUT.Pos.x=displacedPosition.y-OceanParam.y;\
			\
			\
			float3 eyePosition = resultPos2.xyz;\
			float fogDistance  = length(eyePosition);\
			OUT.fogFactor = 1.0 - ( (fogParam.y - fogDistance )/(fogParam.y - fogParam.x ));\
			\
			\
			/*uvParameter:[0] uScale [1] uBias [2] vScale [3] vBias*/\
			float texcoordX = u;\
			float texcoordZ = 1.0 - v;\
			\
			OUT.texcoord0 = float2(texcoordX ,  texcoordZ);\
			OUT.clip0 = dot( modelviewpos, userClipPlaneParam );\n\
			OUT.clip1 = dot( modelviewpos, clipPlaneParam0 );\n\
			OUT.clip2 = dot( modelviewpos, clipPlaneParam1 );\n\
			OUT.clip3 = dot( modelviewpos, clipPlaneParam2 );\n\
			OUT.clip4 = dot( modelviewpos, clipPlaneParam3 );\n\
			return OUT;\
		}";


	char *TerrainGpuProgram::pixel_source = "\
		float4 GetHeightPixel( float H ) \
		{\
			/*if(H<-70) return float4(0.0,0.0,0,1);\
			if(H<-60) return float4(0,0,0.1,1);\
			if(H<-50) return float4(0,0,0.15,1);\
			if(H<-43) return float4(0,0,0.195,1);\
			if(H<-38) return float4(0,0,0.234,1);\
			if(H<-33) return float4(0,0,0.251,1);\
			if(H<-29) return float4(0,0,0.289,1);\
			if(H<-26) return float4(0,0,0.321,1);\
			if(H<-23) return float4(0,0,0.335,1);\
			if(H<-20) return float4(0,0,0.374,1);\
			if(H<-18) return float4(0,0,0.405,1);\
			if(H<-16) return float4(0,0,0.446,1);\
			if(H<-14) return float4(0,0,0.478,1);\
			if(H<-12) return float4(0,0,0.512,1);\
			if(H<-10) return float4(0,0,0.542,1);\
			if(H<-9) return float4(0,0,0.587,1);\
			if(H<-8) return float4(0,0,0.621,1);\
			if(H<-7) return float4(0,0,0.654,1);\
			if(H<-6) return float4(0,0,0.694,1);\
			if(H<-5) return float4(0,0,0.723,1);\
			if(H<-4) return float4(0,0,0.761,1);\
			if(H<-3) return float4(0,0,0.802,1);\
			if(H<-2) return float4(0,0,0.839,1);\
			if(H<-1.2) return float4(0,0,0.867,1);\
			if(H<-0.6) return float4(0,0.2,0,1);\
			if(H<0) return float4(0,0.3,0,1);*/\
			if(H<=0.7)\
				return float4(0.1,0.5,0,1);\
			if(H<4)\
				return float4(0.2196,0.6588,0,1);\
			if(H<7) return float4(0.259,0.678,0,1);\
			if(H<10) return float4(0.302,0.702,0,1);\
			if(H<12) return float4(0.349,0.722,0,1);\
			if(H<14) return float4(0.388,0.749,0,1);\
			if(H<17) return float4(0.435,0.769,0,1);\
			if(H<20) return float4(0.494,0.8,0,1);\
			if(H<23) return float4(0.545,0.82,0,1);\
			if(H<27) return float4(0.588,0.839,0,1);\
			if(H<32) return float4(0.643,0.859,0,1);\
			if(H<38) return float4(0.714,0.89,0,1);\
			if(H<45) return float4(0.773,0.91,0,1);\
			if(H<53) return float4(0.847,0.941,0,1);\
			if(H<63) return float4(0.894,0.961,0,1);\
			if(H<75) return float4(0.965,0.98,0,1);\
			if(H<90) return float4(1,0.969,0,1);\
			if(H<107) return float4(1,0.898,0,1);\
			if(H<127) return float4(1,0.835,0,1);\
			if(H<152) return float4(1,0.769,0,1);\
			if(H<181) return float4(1,0.682,0,1);\
			if(H<216) return float4(1,0.616,0,1);\
			if(H<258) return float4(1,0.549,0,1);\
			if(H<309) return float4(1,0.482,0,1);\
			if(H<369) return float4(1,0.416,0,1);\
			if(H<441) return float4(1,0.349,0,1);\
			if(H<528) return float4(1,0.267,0,1);\
			if(H<631) return float4(1,0.2,0,1);\
			if(H<755) return float4(1,0.133,0,1);\
			if(H<903) return float4(1,0.067,0,1);\
			if(H<1082) return float4(1,0,0,1);\
			return float4(1,1,1,1);\
		}\
		struct FragmentIn\
		{\
		   float2 texCoord0  : TEXCOORD0;\
		   float  fogFactor : TEXCOORD1;\
		   float4  Pos: TEXCOORD2;\
		};\
		struct FragmentOut\
		{\
		   float4 color      : COLOR;\
		};\
		FragmentOut main(FragmentIn In, \
			uniform sampler2D decal,\
			uniform float4  bTexture,\
			uniform float4 fogColor )\
		{\
		   FragmentOut Out;\
		   float4 decalColor = tex2D(decal, In.texCoord0);\
		   /*if(bTexture.x==0.0)\
		   decalColor=GetHeightPixel(In.Pos.y);*/\
		   clip(In.Pos.x);\
			\
			float temp = In.fogFactor;\
			if( temp > 1.0 )\
			{ temp = 1.0; }\
			\
			Out.color.xyz = lerp( decalColor.xyz, fogColor.xyz, temp * fogColor.w );\
		   \
		   Out.color.w   = 1.0;\
		   return Out;\
		}";

	
	//----------------------------------------------------------------
	TerrainGpuProgram::TerrainGpuProgram()
	{
		setDefault();

	}
	void TerrainGpuProgram::setDefault()
	{
		g_decalTextureID = 0;

		_pUVParameter = NULL;
		mCgPixelProgram = NULL;
		mCgVertexProgram = NULL;

		_pReversedViewMat = NULL;

		_heightMapID = 0;

		g_fDisplacementScaler = 100.0f;
		g_fHeightMapSize = 2048 * 2.0f;

		mSupportPtr = NULL;

		_fogColor[0] = 1.0f;
		_fogColor[1] = 1.0f;
		_fogColor[2] = 1.0f;
		_fogColor[3] = 0.0f;

		_fogParam[0] = 1.0f;
		_fogParam[1] = 5000.0f;
		m_bIsMirror=false;
		m_WaterHeightClip=0.0f;
	}
	//----------------------------------------------------------------

	TerrainGpuProgram::~TerrainGpuProgram()
	{
		destroy();
	}
	//----------------------------------------------------------------
	void TerrainGpuProgram::useBindBegin()
	{

		float fdisplacementScaler[] = { g_fDisplacementScaler, g_fHeightMapSize, 0.0f, 1.0f };
		cgGLSetParameter4fv( g_CGparam_displacementScaler, fdisplacementScaler );

		//assert( _pUVParameter != NULL );

		cgGLSetParameter4fv( g_CGparam_uvParameter , _pUVParameter );
		if(this->_mbTexture)
			cgGLSetParameter4f(cgGetNamedParameter(mCgPixelProgram, "bTexture"),1.0,0,0,0);
		else
			cgGLSetParameter4f(cgGetNamedParameter(mCgPixelProgram, "bTexture"),0.0,0,0,0);
		if (vgCam::CamManager::getSingleton().m_bIsDrawMirror)
		{
			cgGLSetParameter4f(cgGetNamedParameter(mCgVertexProgram, "OceanParam"),1.0,vgCam::CamManager::getSingleton().m_WaterHeight/-2.0,0,0);
		}
		else
			cgGLSetParameter4f(cgGetNamedParameter(mCgVertexProgram, "OceanParam"),0.0,-1000.0,0,0);

		cgGLEnableTextureParameter( g_CGparam_displacementTexture );
		cgGLEnableTextureParameter( g_CGparam_decalTexture );
		//cgGLSetTextureParameter( g_CGparam_displacementTexture, _heightMapID );
		//cgGLSetTextureParameter(g_CGparam_decalTexture , g_decalTextureID );
		//cgGLSetTextureParameter(g_CGparam_decalTexture , _heightMapID );

		cgGLBindProgram( mCgPixelProgram );
		cgGLBindProgram( mCgVertexProgram );

		cgGLEnableProfile( mVertexProfile );
		cgGLEnableProfile( mPixelProfile );


		//cgGLSetTextureParameter(
		//	cgGetNamedParameter( mCgVertexProgram, "heightMap"), 
		//	_heightMapID );

	}
	//----------------------------------------------------------------
	void TerrainGpuProgram::useBindEnd()
	{
		cgGLDisableTextureParameter( g_CGparam_displacementTexture );
		cgGLDisableTextureParameter( g_CGparam_decalTexture );

		cgGLDisableProfile( mVertexProfile );
		cgGLDisableProfile( mPixelProfile );
	}
	//----------------------------------------------------------------
	bool TerrainGpuProgram::init()
	{
		vgKernel::GpuManager& gpuMgr = vgKernel::GpuManager::getSingleton();
		assert( mSupportPtr == NULL );
		mSupportPtr = gpuMgr.getGpuSupport();
		assert( mSupportPtr != NULL );

		this->mVertexProfile = mSupportPtr->getVertexProfile();
		this->mPixelProfile = mSupportPtr->getPixelProfile();

		assert( mVertexProfile == CG_PROFILE_VP40 );
		assert( mPixelProfile == CG_PROFILE_FP40 );

		mIsValid = true;

		/// ³õÊ¼»¯CGprogram³ÌÐò
		mCgVertexProgram = 	cgCreateProgram( 
			mSupportPtr->getGpuContextPointer()->getContext(),
			CG_SOURCE,
			vertex_source,
			mVertexProfile,
			NULL, NULL );


		mCgPixelProgram = 	cgCreateProgram( 
			mSupportPtr->getGpuContextPointer()->getContext(),
			CG_SOURCE,
			pixel_source,
			mPixelProfile,
			NULL, NULL );



		cgGLLoadProgram( mCgVertexProgram );
		cgGLLoadProgram( mCgPixelProgram );



		g_CGparam_displacementTexture = 
			cgGetNamedParameter( mCgVertexProgram, "displacementTexture");
		g_CGparam_displacementScaler  =
			cgGetNamedParameter( mCgVertexProgram, "displacementScaler");

		g_CGparam_uvParameter =
			cgGetNamedParameter( mCgVertexProgram, "uvParameter");

		g_CGparam_userClipPlaneParam = 
			cgGetNamedParameter( mCgVertexProgram , "userClipPlaneParam");
		g_CGparam_clipPlaneParam0 =
			cgGetNamedParameter( mCgVertexProgram, "clipPlaneParam0");
		g_CGparam_clipPlaneParam1 =
			cgGetNamedParameter( mCgVertexProgram, "clipPlaneParam1");
		g_CGparam_clipPlaneParam2 =
			cgGetNamedParameter( mCgVertexProgram, "clipPlaneParam2");
		g_CGparam_clipPlaneParam3 =
			cgGetNamedParameter( mCgVertexProgram, "clipPlaneParam3");

		g_CGparam_fogParam = 
			cgGetNamedParameter( mCgVertexProgram, "fogParam");

		g_CGparam_decalTexture = 
			cgGetNamedParameter( mCgPixelProgram , "decal" );

		g_CGparam_fogColor = 
			cgGetNamedParameter( mCgPixelProgram , "fogColor" );




		g_CGparam_ViewMat = 
			cgGetNamedParameter( mCgVertexProgram , "revViewMat" );
		return true;
	}
	//----------------------------------------------------------------
	void TerrainGpuProgram::destroy()
	{

		if ( mCgPixelProgram != NULL )
		{
			cgDestroyProgram(mCgPixelProgram);
			mCgPixelProgram = NULL;
		}

		if ( mCgVertexProgram != NULL )
		{
			cgDestroyProgram(mCgVertexProgram);
			mCgVertexProgram = NULL;
		}

		setDefault();
	}	
	//----------------------------------------------------------------
	void TerrainGpuProgram::setDecalUVParamsEveryFrame( 
		const GLuint& decal_map_id , float* uvparam )
	{
		_pUVParameter = uvparam;
		assert( _pUVParameter != NULL );

		g_decalTextureID = decal_map_id;
		//assert( decal_map_id != 0 );

		cgGLSetParameter4fv( g_CGparam_uvParameter , _pUVParameter );

		cgGLDisableTextureParameter( g_CGparam_decalTexture );

		cgGLSetTextureParameter(g_CGparam_decalTexture , g_decalTextureID );

		cgGLEnableTextureParameter( g_CGparam_decalTexture );

	}
	//----------------------------------------------------------------
	void TerrainGpuProgram::setViewMatrix( GLfloat* mat )
	{
		
		cgGLSetMatrixParameterfc(g_CGparam_ViewMat ,mat);
	}
	//----------------------------------------------------------------
	void TerrainGpuProgram::setHeightMapIdEveryFrame(
		const GLuint& height_map_id )
	{
		_heightMapID = height_map_id;


		cgGLDisableTextureParameter( g_CGparam_displacementTexture );

		cgGLSetTextureParameter(g_CGparam_displacementTexture , _heightMapID );

		cgGLEnableTextureParameter( g_CGparam_displacementTexture );
	}
	//----------------------------------------------------------------
	void TerrainGpuProgram::setClipPlaneParam( float* clip0 , 
		float* clip1 , float* clip2 , float* clip3 )
	{
		cgGLSetParameter4fv( g_CGparam_clipPlaneParam0 , clip0 );
		cgGLSetParameter4fv( g_CGparam_clipPlaneParam1 , clip1 );
		cgGLSetParameter4fv( g_CGparam_clipPlaneParam2 , clip2 );
		cgGLSetParameter4fv( g_CGparam_clipPlaneParam3 , clip3 );
	}
	//----------------------------------------------------------------
	void TerrainGpuProgram::setUserClipParam( float* clip_param )
	{
		cgGLSetParameter4fv( g_CGparam_userClipPlaneParam , clip_param );
	}
	//----------------------------------------------------------------
	void TerrainGpuProgram::setFogColor( float* color  )
	{
		memcpy( _fogColor , color , sizeof( float ) * 3 );

		cgGLSetParameter4fv( g_CGparam_fogColor , _fogColor );
	}
	//----------------------------------------------------------------
	void TerrainGpuProgram::setFogEnableFlag( const bool& enable_fog )
	{
		if ( enable_fog )
		{
			_fogColor[3] = 1.0f;
		}
		else
		{
			_fogColor[3] = 0.0f;
		}

		cgGLSetParameter4fv( g_CGparam_fogColor , _fogColor );
	}
	//----------------------------------------------------------------
	void TerrainGpuProgram::setFogStartAndEnd( const float& start , const float& end )
	{
		_fogParam[0] = start;
		_fogParam[1] = end;

		cgGLSetParameter2fv( g_CGparam_fogParam , _fogParam );

	}
	//----------------------------------------------------------------




}// end of namespace vgTerritory
