


#include <vgStableHeaders.h>
#if 0
#include <vgGlobal/vggGlobalFacade.h>

#include <vgKernel/vgkStringVector.h>

#include <vgAsyn/vgaFileHandle.h>
#include <vgImage/vgiImageManager.h>
#include <vgImage/vgiTextureManager.h>
#include <vgImage/vgiFileWriterVgi.h>
#include <vgMesh/vgmMeshManager.h>
#include <vgMesh/vgmFileHandleVgm.h>


#include <vgKernel/vgkRendererManager.h>

#include <vgEntry/vgEntryFactory.h>
#include <vgUIController/vgUIController.h>


#include <vgModel/vgmoModelManager.h>

#include <vgGlobal/vggVgmeshUtility.h>
#include <vgGlobal/vggVgmodUtility.h>
#include <vgGlobal/vggGlobalUtility.h>

//#include <vgPlugin/vgplTerritoryUtility.h>

#include <vgCam/vgcaCamManager.h>
#include <vgCam/vgcaViewCam.h>
#include <vgCam/vgcaCameraRecord.h>

#include <vgSound/vgSoundManager.h>

#include <vgModel/vgmoFileHandleVmd.h>
#include <vgModel/vgmoModelManager.h>

#include <vgTerritory/vgtDefinition.h>
#include <vgKernel/vgkPluginManager.h>

#include <vgDeprecatedMFCDLL/AutoLoadDialog.h>

namespace vgGlobal {
#define FILE_LENGTH 64

	//----------------------------------------------------------------
	void	GlobalFacade::importImageFile()
	{
		CString DefExt;

		DefExt.Format("%s","vgi�ļ�(*.vgi)|*.vgi|");

		CFileDialog dlg(true,"vgi",
			NULL,OFN_HIDEREADONLY|
			OFN_CREATEPROMPT|
			OFN_NONETWORKBUTTON|
			OFN_ALLOWMULTISELECT|   
			OFN_FILEMUSTEXIST,
			DefExt);

		DWORD   MAXFILE = 0xFFFF;   
		dlg.m_ofn.nMaxFile = MAXFILE; 

		char*  pc = new char[MAXFILE];   

		dlg.m_ofn.lpstrFile = pc;   
		dlg.m_ofn.lpstrFile[0] = NULL;   
		dlg.m_ofn.lpstrTitle = "vgi�ļ�����";

		if( dlg.DoModal() != IDOK )
		{
			std::ostringstream oEnd;
			oEnd<< "-----------------------------------------------------------\n" 
				<< "\t\t�˳�ִ�� ����VGI����\n"
				<< "-----------------------------------------------------------\n" ;
			VGK_SHOW( oEnd.str() );
			return;
		}

		POSITION posi;   
		vgKernel::StringVector strVec;

		posi = dlg.GetStartPosition();   

		while( posi != NULL )
		{   
			strVec.push_back( dlg.GetNextPathName(posi).GetBuffer(0));
		}   

		delete[] pc;

		//------------------------------------------
		// ��ʼ����
		//------------------------------------------
		std::ostringstream o;
		o << "\n��ʼ����vgi�ļ�\n... \n";
		VGK_SHOW( o.str() );
		int nErrorFileCount = 0;

		vgKernel::StringVector::iterator iter = strVec.begin();
		vgKernel::StringVector::iterator iter_end = strVec.end();

		for ( ; iter != iter_end ; ++ iter )
		{
			if( 
				//importImageFileOnly(*iter) 
				vgGlobal::MeshUtility::importImageFileOnly(*iter)
				)
			{
				std::ostringstream oEnd;
				oEnd << "\t�ɹ������ļ�:"<< *iter << " \n";
				VGK_SHOW( oEnd.str() );
			}
			else
			{
				std::ostringstream oEnd;
				oEnd << "\t�����ļ�:"<< *iter << " ʧ��\n";
				VGK_SHOW( oEnd.str() );
				nErrorFileCount++;
				continue;
			}
			/*vgImage::FileHandleVgi* filehandle =
				vgImage::ImageManager::getSingleton().addImageAndAssociateWithIoServer(
				*iter );

			if( filehandle == NULL )
			{
				std::ostringstream o;
				o << "�����ļ�:" << *iter << "ʱ���ִ���.";
				::MessageBox(NULL , o.str().c_str() , "Error" , MB_OK );
				continue;
			}

			bool add_rest = 
				vgImage::TextureManager::getSingleton().addTexture( filehandle );

			if( add_rest == false )
			{
				std::ostringstream o;
				o << "�����ļ�:" << *iter << "ʱ���ִ���.";
				::MessageBox(NULL , o.str().c_str() , "Error" , MB_OK );
				continue;
			}*/
			
		}

		//VGK_SHOW("VGI �ļ�������� \n");
		std::ostringstream oEnd;
		oEnd << "...\nvgi�ļ��������,�ɹ������ļ�" << strVec.size()- nErrorFileCount << "��,"
			<< nErrorFileCount << "������ʧ��\n";
		VGK_SHOW( oEnd.str() );

		// ���һ����Ⱦ����
		vgMesh::MeshManager::getSingleton().clearPrevRenderQueue();


		//vgAsyn::MainThreadMessageManager::getSingleton().clearAllData();
	}
	
	//----------------------------------------------------------------
	void	GlobalFacade::saveModelFileOnly()
	{
		CString DefExt;

		DefExt.Format("%s","vgm�ļ�(*.vgm)|*.vgm|");

		CFileDialog dlgmodelFile(false,"vgm",NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);

		dlgmodelFile.m_ofn.lpstrTitle="����vgm�ļ�";

		if(dlgmodelFile.DoModal()==IDOK)
		{
			String FilePathName = dlgmodelFile.GetPathName();

			vgKernel::StringVectorPtr ret = vgMesh::MeshManager::getSingleton().saveItemsToVgm( FilePathName );

			if ( ret.isNull() == true )
			{
				::MessageBox(NULL , "����ʧ��" , "Error" , MB_OK );
			}
		}

		return;
	}
	
	//----------------------------------------------------------------
	void	GlobalFacade::saveModelAndImage()
	{
		CString DefExt;

		DefExt.Format("%s","vgm�ļ�(*.vgm)|*.vgm|");

		CFileDialog dlgmodelFile(false,"vgm",NULL,OFN_HIDEREADONLY|OFN_CREATEPROMPT|OFN_NONETWORKBUTTON,DefExt);

		dlgmodelFile.m_ofn.lpstrTitle="����vgm�ļ�";

		if(dlgmodelFile.DoModal()==IDOK)
		{
			String FilePathName = dlgmodelFile.GetPathName();

			vgKernel::StringVectorPtr texlist = 
				vgMesh::MeshManager::getSingleton().saveItemsToVgm( FilePathName );

			if ( texlist.isNull() == true )
			{
				::MessageBox(NULL , "����ʧ��" , "Error" , MB_OK );
				return;
			}

			// ����vgi�ļ�·��
			String vgipath = FilePathName.substr( 0 , FilePathName.find_last_of(".") );
			vgipath += ".vgi";

			bool savevgi = 
				vgImage::FileWriterVgi::writeToVgiFileFromTextureNames( texlist , vgipath );

			if ( savevgi == false )
			{
				::MessageBox(NULL , "����vgiʧ��" , "Error" , MB_OK );
				return;
			}
			else
			{
				std::ostringstream o;
				o << "ģ�ͺ������ļ��Ѿ��ɹ����浽:"
					<< FilePathName << ", " << vgipath;
				::MessageBox(NULL , o.str().c_str() , "��ʾ" , 
					MB_OK | MB_ICONINFORMATION );
			}
		}

		return;
	}
	
	//----------------------------------------------------------------
	bool	GlobalFacade::saveModelAndImage(String savePath)
	{
		//// vgm��vgi�����и�棬����ֻ���ļ��ռ� update by lss when 2008-11-5 16:18:15
		//String	fileExt = vgKernel::StringUtility::getFileExtension(savePath);
		//if ( fileExt == String("VG") || fileExt == String("vg"))
		//{
		//	CFile	cFile;
		//	if (!cFile.Open(savePath.c_str(),CFile::modeRead )) 
		//	{
		//		MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, "Write File Failed" ,"error", MB_OK);
		//	}

		//	//  vg�ļ��汾У��
		//	char	vgfileheader[20];
		//	cFile.Read(vgfileheader, 20);
		//	String strheader( vgfileheader );
		//	
		//	//// �°汾����
		//	if ( (strheader>= String("VRGIS.VERSION 2.0")) 
		//		&&(strheader< String("VRGIS.VERSION 2.11")) 
		//		)
		//	{
		//		cFile.Close();
		//		collectModelAndImage(savePath);
		//		return;
		//	}
		//}

		// ���£��ɰ汾����vgm��vgi
		String VgmPathName(savePath);
		VgmPathName.erase( VgmPathName.find_last_of("\\.")+1, std::string::npos);
		VgmPathName = VgmPathName + "vgm";

		vgKernel::StringVectorPtr texlist = 
			vgMesh::MeshManager::getSingleton().saveItemsToVgm( VgmPathName );

		if ( texlist.isNull() == true )
		{

#if VGK_LANG_CHS
			std::ostringstream oEnd;
			oEnd<< "\t����VGM:" << VgmPathName
				<< "ʧ��.\n";
#else
			std::ostringstream oEnd;
			oEnd<< "\tFail: " << VgmPathName
				<< " \n";

#endif
			VGK_SHOW( oEnd.str() );

			::MessageBox(NULL , "VGM����ʧ��" , "Error" , MB_OK );
			return false;
		}
		else
		{
#if VGK_LANG_CHS
			std::ostringstream oEnd;
			oEnd<< "\t����VGM:" << VgmPathName
				<< "�ɹ����.\n";
#else
			std::ostringstream oEnd;
			oEnd<< "\tSuccess: " << VgmPathName
				<< " \n";

#endif
			VGK_SHOW( oEnd.str() );
		}

		// ����vgi�ļ�·��
		String vgipath = savePath.substr( 0 , savePath.find_last_of(".") );
		vgipath += ".vgi";

		bool savevgi = 
			vgImage::FileWriterVgi::writeToVgiFileFromTextureNames( texlist , vgipath );

		if ( savevgi == false )
		{
			return false;
		}

		return true;
	}


	
	//----------------------------------------------------------------
	bool	GlobalFacade::importModelFileOnly(String VgmPathName)
	{
		if ( vgKernel::SystemUtility::checkFileExist( VgmPathName ) == false )
		{
			return false;
		}

		// Part 1������vgm
		vgMesh::FileHandleVgm* vgmhandle 
			= new vgMesh::FileHandleVgm( VgmPathName );

		bool opened = vgmhandle->open();

		if( opened == false )
		{
			delete vgmhandle;
			::MessageBox(NULL , "�����ļ�ʧ��" , "��ʾ" , 
				MB_OK | MB_ICONINFORMATION );
			//MessageBox("�����ļ�ʧ��");
			return false;
		}

		bool addres = 
			vgMesh::MeshManager::getSingleton().addItemsAndRegisterFileHandlerVgm( vgmhandle );


		if ( addres == false)
		{
			delete vgmhandle;
			::MessageBox(NULL , "�����ļ�ʧ��" , "��ʾ" , 
				MB_OK | MB_ICONINFORMATION );
			//MessageBox("�����ļ�ʧ��");
			return false;
		}


		//	Part 2����UI������vgBaseEntry
		/*std::ostringstream o;
		o << "����"<< vgmhandle->getFilePath() << "�ļ��ɹ� \n";
		VGK_SHOW( o.str() );*/
		vgMesh::MeshItemMap* items = vgmhandle->getMeshItemsPtr();
		assert( items != NULL );

	//----------progress position------------------//
		long nodeNum = items->size();
		long nCurPos = 0;
		float nStep = 0;
	//---------------------------------------------//

		vgMesh::MeshItemMap::iterator iter = items->begin();
		vgMesh::MeshItemMap::iterator iter_end = items->end();

		HTREEITEM	hRootVGM = vgUI::UIController::getSingleton().getEntryRootItemByType(MODEL_VGM);
		for ( ; iter != iter_end ; ++ iter )
		{
			String shortname = vgKernel::StringUtility::getFilenameFromAbsolutePath(
				vgmhandle->getFilePath() );
			vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( iter->second );
			vgUI::UIController::getSingleton().AddNode( shortname, entry, hRootVGM);
			//vgUI::UIController::getSingleton().OnChanged(VG_OBS_NEWMESHITEM, vgmhandle->getMeshItemsPtr());


			vgKernel::RendererQueue* queue = 
				vgKernel::RendererManager::getSingleton().addRenderer( iter->second );

			assert( queue != NULL );

			//----------progress position------------------//
			nStep = (float)nCurPos/(float)nodeNum;
			nCurPos++;			 
			CAutoLoadDialog::SetPosWithRange(70, 90, nStep);
			//---------------------------------------------//

		}
		if (hRootVGM != NULL)
		{
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(hRootVGM );
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(hRootVGM);
		}

		return true;
	}

	
	//----------------------------------------------------------------
	bool	GlobalFacade::importImageFileOnly(String VgiPathName)
	{
		if ( vgKernel::SystemUtility::checkFileExist( VgiPathName ) == false )
		{
			return false;
		}

		vgImage::FileHandleVgi* filehandle =
			vgImage::ImageManager::getSingleton().addImageAndAssociateWithIoServer(
			VgiPathName );

		if( filehandle == NULL )
		{
			std::ostringstream o;
			o << "�����ļ�:" << VgiPathName << "ʱ���ִ���.";
			::MessageBox(NULL , o.str().c_str() , "Error" , MB_OK );
			return false;
		}

		bool add_rest = 
			vgImage::TextureManager::getSingleton().addTexture( filehandle );

		if( add_rest == false )
		{
			std::ostringstream o;
			o << "�����ļ�:" << VgiPathName << "ʱ���ִ���.";
			::MessageBox(NULL , o.str().c_str() , "Error" , MB_OK );
			return false;
		}

		//------------------------------------------
		// ��ʼ�����������ļ�
		//------------------------------------------
		vgImage::FileHandleVgi* tmp = filehandle->openNextFile();
		while ( tmp != NULL )
		{
			vgImage::FileHandleVgi* filehandle =
				vgImage::ImageManager::getSingleton().addImageAndAssociateWithIoServer(
				tmp );

			if( filehandle == NULL )
			{
				std::ostringstream o;
				o << "�����ļ�:" << tmp->getFilePath() << "����.";
				::MessageBox(NULL , o.str().c_str() , "Error" , MB_OK );
			}
			else
			{
				bool add_rest = 
					vgImage::TextureManager::getSingleton().addTexture( filehandle );

				if( add_rest == false )
				{
					std::ostringstream o;
					o << "�����ļ�:" << VgiPathName << "ʱ���ִ���.";
					::MessageBox(NULL , o.str().c_str() , "Error" , MB_OK );
				}
			}

			tmp = tmp->openNextFile();
		}


		// ���һ����Ⱦ����
		vgMesh::MeshManager::getSingleton().clearPrevRenderQueue();

		return true;
	}

	
	//----------------------------------------------------------------
	void	GlobalFacade::importModelAndImage(String readPath)
	{
		// ��vgm��vgi�ļ��б���д��vg�ļ�
		CFile	cFile;
		if (!cFile.Open(readPath.c_str(),CFile::modeRead )) 
		{
			MessageBox( AfxGetApp()->m_pMainWnd->m_hWnd, "read File Failed" ,"error", MB_OK);
			return;
		}

		//  vg�ļ��汾У��
		char	vgfileheader[20];
		cFile.Read(vgfileheader, 20);
		String strheader( vgfileheader );


		if ( (strheader < String("VRGIS.VERSION 2.0")) )
		{
			cFile.Close();

			string VgiPathName(readPath);
			VgiPathName.erase( VgiPathName.find_last_of("\\.")+1, std::string::npos);
			VgiPathName = VgiPathName + "vgi";
			if(importImageFileOnly(VgiPathName) )
			{
				std::ostringstream o;
#if VGK_LANG_CHS
				o << "\t�ɹ������ļ�:"<< VgiPathName << " \n";
#else
				o << "\tImport VGI\t"<< VgiPathName << " successfully\n";
#endif				

				VGK_SHOW( o.str() );
			}

			if(importModelFileOnly(readPath) )
			{
				std::ostringstream o;

#if VGK_LANG_CHS
				o << "\t�ɹ������ļ�:"<< readPath << " \n";
#else
				o << "\tImport VGM\t:"<< readPath << " successfully\n";
#endif
				VGK_SHOW( o.str() );
			}
			else
			{
				std::ostringstream oEnd;

#if VGK_LANG_CHS
				oEnd << "\t�����ļ�:"<< readPath << " ʧ��\n";
#else
				oEnd << "\tImport VGM\t"<< readPath << " failed\n";
#endif

				VGK_SHOW( oEnd.str() );
			}



			return;
		}

		else if( 
			(strheader>= String("VRGIS.VERSION 2.0")) 
			&&(strheader<  String("VRGIS.VERSION 2.11")) 
			)
		{// �°汾
			cFile.Seek(-4, CFile::end);
			int nFileListPos = 0;
			cFile.Read( &nFileListPos, sizeof(int));
			cFile.Seek(nFileListPos,CFile::begin );

			int nFileCount = 0;
			char strFileName[128];
			String stringFileName;

			String destiPath(readPath);
			destiPath.erase( destiPath.find_last_of("\\/"), std::string::npos);
			destiPath += "\\";
			destiPath += "vgm";
			destiPath += "\\";

			// vgm�б�
			cFile.Read( &nFileCount, sizeof(int));
			vgKernel::StringVector strVecVgm;
			for(int fileListIndex = 0; fileListIndex <nFileCount ; fileListIndex ++)
			{
				cFile.Read( strFileName, FILE_LENGTH);
				stringFileName = String( strFileName );
				stringFileName = destiPath + strFileName;
				strVecVgm.push_back(stringFileName);
			}

			destiPath = readPath;
			destiPath.erase( destiPath.find_last_of("\\/"), std::string::npos);
			destiPath += "\\";
			destiPath += "vgi";
			destiPath += "\\";

			// vgi�б�
			cFile.Read( &nFileCount, sizeof(int));
			vgKernel::StringVector strVecVgi;
			for(int fileListIndex = 0; fileListIndex <nFileCount ; fileListIndex ++ )
			{
				cFile.Read( strFileName, FILE_LENGTH);
				stringFileName = String( strFileName );
				stringFileName = destiPath + strFileName;
				strVecVgi.push_back(stringFileName);
			}



			// Part 2: vgi
			if (!strVecVgi.empty())
			{
				std::ostringstream o;
#if VGK_LANG_CHS
				o << "\n\n��ʼ����vgi�ļ�\n... \n";
#else
				o << "\n\nbegin import vgi:\n... \n";
#endif					
				VGK_SHOW( o.str() );


				int nErrorFileCount = 0;
				for ( vgKernel::StringVector::iterator iter = strVecVgi.begin(); 
					iter != strVecVgi.end()	; ++ iter )
				{
					if(importImageFileOnly(*iter) )
					{
						std::ostringstream o;
#if VGK_LANG_CHS
						o << "\t�ɹ������ļ�:"<< *iter << " \n";
#else
						o << "\tSuccess: "<< *iter << " successfully\n";
#endif
						VGK_SHOW( o.str() );
					}
					else
					{
						std::ostringstream oEnd;
#if VGK_LANG_CHS
						oEnd << "\t�����ļ�:"<< *iter << " ʧ��\n";
#else
						oEnd << "\tFail: "<< *iter << " \n";
#endif
						VGK_SHOW( oEnd.str() );
						nErrorFileCount++;

					}

				}// for


				std::ostringstream oEnd;
#if VGK_LANG_CHS
				oEnd << "...\n" << "vgi�ļ��������,�ɹ������ļ�" 
					<< strVecVgi.size()- nErrorFileCount << "��,"
					<< nErrorFileCount << "������ʧ��\n";
#else
				oEnd << "...\n" << "vgi import completed, success " 
					<< strVecVgm.size()- nErrorFileCount << " files, "
					<< nErrorFileCount << " failed\n";
#endif			
				VGK_SHOW( oEnd.str() );


			}//vgi�ļ��б��ǿ�


			// Part 1: vgm
			if (!strVecVgm.empty())
			{
				std::ostringstream o;
#if VGK_LANG_CHS
				o << "\n\n��ʼ����vgm�ļ�\n... \n";
#else
				o << "\n\nbegin import vgm:\n... \n";
#endif					
				VGK_SHOW( o.str() );

				int nErrorFileCount = 0;
				for ( vgKernel::StringVector::iterator iter = strVecVgm.begin(); 
					iter != strVecVgm.end()	; ++ iter )
				{
					if(importModelFileOnly(*iter) )
					{
						std::ostringstream o;
#if VGK_LANG_CHS
						o << "\t�ɹ������ļ�:"<< *iter << " \n";
#else
						o << "\tImport VGM\t:"<< *iter << " successfully\n";
#endif
						VGK_SHOW( o.str() );
					}
					else
					{
						std::ostringstream oEnd;
#if VGK_LANG_CHS
						oEnd << "\t�����ļ�:"<< *iter << " ʧ��\n";
#else
						oEnd << "\tImport VGM\t"<< *iter << " failed\n";
#endif
						VGK_SHOW( oEnd.str() );
						nErrorFileCount++;

					}


				}


				std::ostringstream oEnd;
#if VGK_LANG_CHS
				oEnd << "...\n" << "vgm�ļ��������,�ɹ������ļ�" 
					<< strVecVgm.size()- nErrorFileCount << "��,"
					<< nErrorFileCount << "������ʧ��\n";
#else
				oEnd << "...\n" << "vgm import completed, success " 
					<< strVecVgm.size()- nErrorFileCount << " files, "
					<< nErrorFileCount << " failed\n";
#endif			
				VGK_SHOW( oEnd.str() );

			}//vgm�ļ��б��ǿ�





			//vgCore::CityplanManager::getSingleton().readFromFile( &cFile, string("dddd") );
		}

		else if (strheader >=  String("VRGIS.VERSION 2.11"))
		{
			cFile.Close();

			string VgiPathName(readPath);
			VgiPathName.erase( VgiPathName.find_last_of("\\.")+1, std::string::npos);
			VgiPathName = VgiPathName + "vgi";
			if(importImageFileOnly(VgiPathName) )
			{
				/*std::ostringstream o;
				o << "\t�ɹ������ļ�:"<< VgiPathName << " \n";
				VGK_SHOW( o.str() );*/
				std::ostringstream o;
#if VGK_LANG_CHS
				o << "\t�ɹ������ļ�:"<< VgiPathName << " \n";
#else
				o << "\tSuccess: "<< VgiPathName << " \n";
#endif
				VGK_SHOW( o.str() );
			}

			string VgmPathName(readPath);
			VgmPathName.erase( VgmPathName.find_last_of("\\.")+1, std::string::npos);
			VgmPathName = VgmPathName + "vgm";
			if(importModelFileOnly(VgmPathName) )
			{
				/*std::ostringstream o;
				o << "\t�ɹ������ļ�:"<< VgmPathName << " \n";
				VGK_SHOW( o.str() );*/
				std::ostringstream o;
#if VGK_LANG_CHS
				o << "\t�ɹ������ļ�:"<< VgmPathName << " \n";
#else
				o << "\tSuccess: "<< VgmPathName << " \n";
#endif
				VGK_SHOW( o.str() );
			}
			else
			{
				/*std::ostringstream oEnd;
				oEnd << "\t�����ļ�:"<< VgmPathName << " ʧ��\n";
				VGK_SHOW( oEnd.str() );*/
				std::ostringstream oEnd;
#if VGK_LANG_CHS
				oEnd << "\t�����ļ�:"<< VgmPathName << " ʧ��\n";
#else
				oEnd << "\tFail: "<< VgmPathName << " \n";
#endif
				VGK_SHOW( oEnd.str() );
			}


			return;
		}

		cFile.Close();
	}//importModelAndImage(String)





	//----------------------------------------------------------------
	bool	GlobalFacade::importVtrFile( const String& file_name)
	{
		if ( !VGK_DLL_CHECK_LOAD( VGT_DLL_NAME ) )
		{
			return false;
		}

		VGK_DLL_RUN_CLASSFUNC( VGT_DLL_NAME ,
			TerrainManager, openVtrFile )( file_name );


		//bool has_create_node = 
		//	vgPlugin::TerritoryUtility::hasTerrainData();

		//bool openok = 
		//	vgPlugin::TerritoryUtility::openVtrFile( file_name );

		//if ( openok == true )
		//{
		//	if ( has_create_node == false )
		//	{
		//		// ���ӵ��νڵ�
		//		vgUI::UIController::getSingleton().ClearSelection();
		//	}
		//}

		return true;
	}


	//----------------------------------------------------------------
	bool	GlobalFacade::import3DMusicFile( const String& file_name)
	{
		vgSound::Sound3D* _sound = 
			vgSound::SoundManager::getSingleton().create3DSoundFromCurrentPos( file_name );

		if ( _sound == NULL )
		{
			return false;
		}


		HTREEITEM	h3DSound = vgUI::UIController::getSingleton().getEntryRootItemByType(SOUND_3D);

		vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( _sound );
		vgUI::UIController::getSingleton().AddNode( h3DSound, entry );

		if (h3DSound != NULL)
		{
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(h3DSound );
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(h3DSound);
		}


		return true;
	}

	
	//----------------------------------------------------------------
	bool	GlobalFacade::importBackgroundMusicFile( const String& file_name)
	{
		vgSound::SoundManager::getSingleton().setBackgroundMusicFromCurrentPos( file_name );

		HTREEITEM	h3DSound = vgUI::UIController::getSingleton().getEntryRootItemByType(SOUND_3D);
		if (h3DSound != NULL)
		{
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->Expand(h3DSound );
			vgUI::UIController::getSingleton().GetWorkSpaceBar()->EnsureVisible(h3DSound);
		}
		return true;
	}


	//----------------------------------------------------------------
	bool	GlobalFacade::importVmdFileOnly( const String& file_name)
	{
		vgModel::FileHandleVmd* vgmhandle 
			= new vgModel::FileHandleVmd( file_name );

		bool opened = vgmhandle->open();

		if( opened == false )
		{
			delete vgmhandle;

			return false;
		}

		bool addres = 
			vgModel::ModelManager::getSingleton().addItemsAndRegisterFileHandlerVmd( vgmhandle );


		if ( addres == false)
		{
			delete vgmhandle;

			return false;
		}

		//------------------------------------------
		// ��UI������vgBaseEntry
		//------------------------------------------

		vgModel::ModelItemMap* items = vgmhandle->getModelItemsPtr();
		assert( items != NULL );

		vgModel::ModelItemMap::iterator iter = items->begin();
		vgModel::ModelItemMap::iterator iter_end = items->end();

		for ( ; iter != iter_end ; ++ iter )
		{
			//String shortname = vgKernel::StringUtility::getFilenameFromAbsolutePath(
			//	vgmhandle->getFilePath() );
			//vgBaseEntry* entry = vgEntryFactory::createEntryFromRenderer( iter->second );
			//vgUI::UIController::getSingleton().AddNode( shortname, entry, hRootVGM);
			//vgUI::UIController::getSingleton().OnChanged(VG_OBS_NEWMESHITEM, vgmhandle->getMeshItemsPtr());


			vgKernel::RendererQueue* queue = 
				vgKernel::RendererManager::getSingleton().addRenderer( iter->second );

			assert( queue != NULL );
		}

		return true;
	}
}// end of namespace vgGlobal

#endif