


#include <vgStableHeaders.h>

#include <vgEffect/vgDustsun.h>

#include <vgKernel/vgkRendererManager.h>
#include <vgKernel/vgkMath.h>

#include <vgMod/vgFileReaderMOD.h>
#include <vgMod/vgNodeManager.h>
#include <vgMod/vgObjNodeBaked.h>
#include <vgMod/vgobjframenode.h>
namespace vgMod {

	//----------------------------------------------------------------
	Dustsun::Dustsun()
	{
		dustsungpuprog = NULL; 

		sky = NULL;

		m_ratio =0.0;

		dusttimepos = 0;

	}
	//----------------------------------------------------------------
	Dustsun::~Dustsun()
	{
		if ( dustsungpuprog)
		{
			 delete dustsungpuprog;

			 dustsungpuprog = NULL;
		}

		if ( sky )
		{
			delete sky;

			sky = NULL;
		}



	}
	//----------------------------------------------------------------
	void Dustsun::Initdata( string modfile,  string lastsuntex, string dusttex, string origtex)
	{
		CFile pfile;

		MODFileHeader	m_fileHeader;

		vgKernel::StreamReaderPtr m_pfile;

		if (!pfile.Open(modfile.c_str(),CFile::modeRead )) 
		{
			MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, "Read File Failed" ,
				"error", MB_OK);
			return;
		}

		m_pfile = vgKernel::StreamReaderFactory::createFromCFile( &pfile,false);


		if ( m_pfile.isNull() == true )
		{
			return;
		}

		long filebeg = m_pfile->tell();


		//	Part 1：文件头，包括文件格式、模型数目、模型类型等6项
		if ( !m_fileHeader.read( m_pfile ) )
		{
			return;
		}

		vgKernel::StreamReader*	pcfile2 = m_pfile.getPointer();
		CFile*	pfile2 = ((vgKernel::CFileStreamReader*)pcfile2)->getCFilePointer();

		 sky = NULL;

		 for (int indexMod = 0; indexMod < m_fileHeader.uiObjectCount; indexMod++)
		 {	
			 //	Step0：定位文件指针到某个节点的数据块位置
			 pfile.Seek(m_fileHeader.arrModPosIndex[indexMod] , CFile::begin);

			 //	Step1：根据不同的节点类型，生成物体对象
			 if( m_fileHeader.uiFileVersion > VERSION_MOD(2008,5) )
			 {
				 uint ffff;
				 if ( indexMod == 4 )
				 {
					 ffff = m_fileHeader.arrModType[indexMod].nType;
				 }


				 if ( (m_fileHeader.arrModType[indexMod].nType & OBJ_KEYFRAME)  )
				 {
					 if ( (m_fileHeader.arrModType[indexMod].nType & OBJ_BAKED)  )
					 {
						 sky	=	new ObjectNodeBaked(m_fileHeader.uiFileVersion);
					 }
					 else
					 {
						 sky	=	new ObjFrameNode(m_fileHeader.uiFileVersion);
					 }

					 //pObjectNode	=	new ObjFrameNode(m_fileHeader.uiFileVersion);
				 }
				 else if ( !(m_fileHeader.arrModType[indexMod].nType & OBJ_BAKED)  )
				 {
					 sky	=	new ObjFrameNode(m_fileHeader.uiFileVersion);
				 }
				 else
				 {
					 sky	=	new ObjectNodeBaked(m_fileHeader.uiFileVersion);
				 }
			 }
			 else
			 {
				 if ( !m_fileHeader.arrModType[indexMod].bType  )
				 {
					 sky	=	new ObjFrameNode(m_fileHeader.uiFileVersion);
				 }
				 else
				 {
					 sky	=	new ObjectNodeBaked(m_fileHeader.uiFileVersion);
				 }
			 }

			//	Step2：按块大小读入内存
			sky->ReadObjectFromMod(pfile);

			sky->setName( string( sky->GetName() ) );

			sky->configureCommonData();
		}

		 pfile.Close();

		 dustsungpuprog = new vgCore::DustsunGpuProgram();

		 dustsungpuprog->init();

		 dustsungpuprog->setParametersOnce(lastsuntex, dusttex, origtex );
	}

	//----------------------------------------------------------------

	void Dustsun::dustsuneffect()
	{	
		_dustdlg.DoModal();	
	}

	//----------------------------------------------------------------
	void Dustsun::updatedustsun()
	{

	}
	//----------------------------------------------------------------
	void Dustsun::render()
	{
		if ( !sky )
		{
			return;
		}

		dusttimepos = _dustdlg.gettime();

		m_ratio = (float)dusttimepos / 60.0;

		if ( m_ratio >= 0.1 )
		{
			vgKernel::Vec3 corner1 = 
				vgKernel::RendererManager::getSingleton().getAllRendererBox().getCenter();

			GLfloat LightAmbient[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat LightDiffuse[]=		{ 1.0f*(1.1-m_ratio), 1.0f*(1.1-m_ratio), 1.0f*(1.1-m_ratio), 1.0f };
			GLfloat LightPosition[]=	{ corner1.x, corner1.y*10, corner1.z, 1.0f };

			glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
			glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
			glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// Position The Light
			glEnable(GL_LIGHT1);	


			GLfloat LightAmbient2[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
			GLfloat LightDiffuse2[]=		{ 1.0f*(1.1-m_ratio), 1.0f*(1.1-m_ratio), 1.0f*(1.1-m_ratio), 1.0f };
			GLfloat LightPosition2[]=	{ corner1.x, -corner1.y*10, corner1.z, 1.0f };

			glLightfv(GL_LIGHT2, GL_AMBIENT, LightAmbient2);		// Setup The Ambient Light
			glLightfv(GL_LIGHT2, GL_DIFFUSE, LightDiffuse2);		// Setup The Diffuse Light
			glLightfv(GL_LIGHT2, GL_POSITION,LightPosition2);	// Position The Light
			glEnable(GL_LIGHT2);	

			glEnable(GL_LIGHTING);
		}
		else
			glDisable( GL_LIGHTING );

		dustsungpuprog->setParametersEveryFrame( m_ratio );

		glPushMatrix();
		{
			dustsungpuprog->useBindBegin();

			sky->RenderWithoutTex(1,1,1);

			dustsungpuprog->useBindEnd();
		}
		glPopMatrix();

	}
	//----------------------------------------------------------------
}// end of namespace vgModel
