// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "vgStableHeaders.h"
#include "resource.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("VRG")

//-----------------------------------------------------------------------------
typedef std::vector<AcDbPoint*> APointPtrVec;

typedef std::wstring String;


bool getElevationFromStr( const String& input_str , double& out_double )
{
	String content = input_str;

	String::size_type dotpos = content.find_first_of( _T("." ) );

	if ( dotpos == String::npos )
	{
		return false;
	}

	String::size_type p2 = content.find_first_not_of( _T("0123456789") , dotpos + 1);

	String::size_type p1 = content.find_last_not_of( _T("0123456789") , dotpos - 1 );

	if ( p1 == String::npos )
	{
		p1 = -1;
	}


	String numstr = content.substr( p1 + 1 , p2 );

	double d = 0.0;

	try
	{
		std::wstringstream o;
		o << numstr.c_str();



		o >> d;

		if ( d == 0.0 )
		{
			return false;
		}


	}
	catch (...)
	{
		return false;
	}

	out_double = d;

	return true;
}




//----- ObjectARX EntryPoint
class CArxProject2App : public AcRxArxApp {

public:
	CArxProject2App () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}


	// - vgPluginCad._MyCommand1 command (do not rename)
	static void vgPluginCad_HelloWorld(void)
	{
		// Add your code for command vgPluginCad._MyCommand1 here

		MessageBox( NULL , _T("HelloWorld" ) , _T("Test " ), MB_OK );
	}

	// - vgPluginCad._tGrid command (do not rename)
	static void vgPluginCad_tGrid(void)
	{



		APointPtrVec points;

		AcDbDatabase *mybase=new AcDbDatabase(Adesk::kFalse);


#if 0
		CAdUiFileDialog dlgmodelFile(TRUE, _T("dwg"));
#endif
		CString DefExt;

		DefExt.Format( _T("%s"), _T("dwg文件(*.dwg)|*.dwg|所有文件(*.*)|*.*|") );

		CAdUiFileDialog dlgmodelFile(true, _T("dwg"),
			NULL,OFN_HIDEREADONLY|
			OFN_CREATEPROMPT|
			OFN_NONETWORKBUTTON|
			OFN_ALLOWMULTISELECT|   
			OFN_FILEMUSTEXIST,
			DefExt);
		if( dlgmodelFile.DoModal() != IDOK )
		{
			return;
		}

		String filename = dlgmodelFile.GetPathName().GetBuffer(0);

		//String filename = String("D:\\西环路+老城区.dwg");


		String prename = filename.substr( 0 , 
			filename.find_last_of( _T(".")));

		String savename = prename + _T("_new.dwg");

		AcDbLine *pLine; //定义指向直线对象的指针
		AcDbArc *pArc; //定义指向圆弧对象的指针
	
		Acad::ErrorStatus eStatus;

		eStatus = mybase->readDwgFile(  filename.c_str() );

		if ( eStatus != Acad::eOk )
		{
			MessageBox( NULL , _T("Read input file error!" ) , _T("Error" ), MB_OK );

			return;
		}

		AcDbBlockTableRecord *pBlockTblRec=NULL;
		AcDbBlockTable *pBlockTable=NULL;

		eStatus = mybase->getBlockTable( pBlockTable, AcDb::kForRead) ;

		if ( eStatus != Acad::eOk )
		{
			MessageBox( NULL , _T("Read input file error!" ) , _T("Error" ), MB_OK );

			return;
		}

		pBlockTable->getAt(ACDB_MODEL_SPACE,pBlockTblRec,AcDb::kForRead);
		acutPrintf ( _T( "working\\n" ) );
		//定义浏览器指针
		AcDbBlockTableRecordIterator *pBlockTblRecIterator = NULL;
		pBlockTblRec->newIterator( pBlockTblRecIterator );
		
		//遍历块表记录
		AcDbEntity *pEnt = NULL; //定义指向实体的指针
		int i=1;
		for (pBlockTblRecIterator->start();!pBlockTblRecIterator->done();pBlockTblRecIterator->step())
		{
			pBlockTblRecIterator->getEntity( pEnt, AcDb::kForWrite );

			if ( pEnt == NULL )
			{
				continue;
			}

			if ( pEnt->isKindOf( AcDbMText::desc() ))
			{
				AcDbMText* text  = (AcDbMText*)pEnt;
				String content = text->contents();//text->text();

				//acutPrintf( content.c_str() );

				AcGePoint3d location;

				location = text->location();

				double elev = 0.0;

				bool ret = getElevationFromStr( content , elev );

				if ( ret == false )
				{
					continue;
				}

				location[Z] = elev;

				AcDbPoint* point = new AcDbPoint( location );

				points.push_back( point );

				acutPrintf( _T("\n vertex location is : %0.3f, %0.3f, %0.3f : %s"),
					location[X], location[Y], location[Z] , content.c_str() );

			}

			if(pEnt->isKindOf(AcDbText::desc()))
			{
				AcDbText* text  = (AcDbText*)pEnt;

				AcGePoint3d location;

				location = text->position();

				//text->close();

				String content = text->textString();//text->textStringConst();

				double elev = 0.0;

				bool ret = getElevationFromStr( content , elev );

				if ( ret == false )
				{
					continue;
				}

				location[Z] = elev;

				AcDbPoint* point = new AcDbPoint( location );

				points.push_back( point );

				acutPrintf(_T("\n vertex location is : %0.3f, %0.3f, %0.3f : %s"),
					location[X], location[Y], location[Z] , text->textString()/*textStringConst()*/ );

				//acutPrintf("第%d个实体是AcDbText\n",i );
			}

			//if (pEnt->isKindOf (AcDbMText::desc ()))
			//{ 
			//	AcDbMText *pt = (AcDbMText *) pEnt;
			//	TCHAR *s = pt->contents ();
			//	acutPrintf (s);
			//	delete s;
			//}

			
#if 0
			if(pEnt->isKindOf(AcDb2dPolyline ::desc()))
			{
				//AcString name;

				AcDb2dPolyline * pyline = (AcDb2dPolyline * ) pEnt;

				int vertex_num = 0/*pyline->numVerts()*/;

				double elev = pyline->elevation();
				//
				//acutPrintf("第%d个实体是AcDb2dPolyline, elevation: %lf\n",i , elev  );

				AcDbObjectIterator *pertIter= pyline->vertexIterator();
				pyline->close(); // Finished with the pline header.

				AcDb2dVertex *pertex;
				AcGePoint3d location;
				AcDbObjectId ertexObjId;

				for (int ertexNumber = 0; !pertIter->done();
					ertexNumber++, pertIter->step())
				{
					ertexObjId = pertIter->objectId();
					acdbOpenObject(pertex, ertexObjId,
						AcDb::kForRead);

					location = pertex->position();
					pertex->close();

					AcDbPoint* point = new AcDbPoint( location );
					points.push_back( point );

					//acutPrintf("\n vertex # %d's location is : %0.3f, %0.3f, %0.3f", ertexNumber,
						//location[X], location[Y], location[Z]);
				}

				delete pertIter;


				//for ( int i = 0 ; i < vertex_num ; i++ )
				//{
				//	AcGePoint3d p;

				//	Acad::ErrorStatus ret = pyline->getPointAt( i , p );

				//	assert( ret == Acad::eOk );

				//	acutPrintf("\t [ %d ] -- x: %lf , y : %lf , z : %lf \n", i , p.x , p.y , p.z  );

				//}
			}
			//else if(pEnt->isKindOf(AcDbArc::desc()))
			//{
			//	acutPrintf("第%d个实体是AcDbArc！\n",i);
			//	//acutPrintf("\\n\\n");
			//}
			//else
			//	acutPrintf("第%d个实体是未知类型实体！\n",i);

#endif

			i++;
		}


		//------------------------------------------
		// 处理points
		//------------------------------------------
		// 创建新的图形数据库，分配内存空间 
		{
			AcDbDatabase *pDb = new AcDbDatabase(); 

			AcDbBlockTable *pBlkTbl; 
			pDb->getSymbolTable(pBlkTbl, AcDb::kForRead); 

			AcDbBlockTableRecord *pBlkTblRcd; 
			pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, 
				AcDb::kForWrite); 
			pBlkTbl->close(); 

			// 创建两个圆 

			APointPtrVec::iterator iter = points.begin();
			APointPtrVec::iterator iter_end = points.end();

			for ( ; iter != iter_end ; ++ iter )
			{
				AcDbPoint* p = *iter;

				pBlkTblRcd->appendAcDbEntity( p ); 

				p->close();
			}

			pBlkTblRcd->close();
			
			pDb->saveAs( savename.c_str() );

			delete pDb;
		}

		acutPrintf( _T("done") );

		MessageBox( NULL , _T("Success To Transform From Vector To Grid!" ) , _T("Finish" ), MB_OK );




#if 0
		// Add your code for command VRGArxProject2._t here

		//acdbHostApplicationServices()->workingDatabase();

		AcDbDatabase *pDb = new AcDbDatabase(Adesk::kFalse);

		Acad::ErrorStatus ret /*= pDb->readDwgFile( ( "d:\\005.dwg" ) )*/;

		eOkVerify(  pDb->readDwgFile( ( "d:\\005.dwg" ) ) );

		//assert( ret == Acad::eOk );

		//acdbHostApplicationServices()->setWorkingDatabase( pDb );

		AcDbLayerTable* pTable = NULL;
		ret = pDb->getLayerTable( pTable , AcDb::kForRead );

		assert( ret == Acad::eOk );


		AcDbLayerTableIterator* tableiter = NULL;

		ret = pTable->newIterator( tableiter );
		assert( ret == Acad::eOk );

		//tableiter->

		std::wostringstream o;

		for ( tableiter->start() ; !tableiter->done() ; tableiter->step() )
		{
			AcDbLayerTableRecord* record = NULL;

			ret = tableiter->getRecord( record ,  AcDb::kForRead );
			assert( ret == Acad::eOk );

			AcString str;

			record->getName( str );


			o << str.constPtr() << "  ";
		}


		MessageBox( NULL ,  o.str().c_str() , ("asfdadf " ), MB_OK );

		//AcDbBlockTable *pBlkTbl; 
		//pDb->getSymbolTable(pBlkTbl, AcDb::kForRead); 

		//AcDbBlockTableRecord *pBlkTblRcd; 
		//pBlkTbl->getAt(ACDB_MODEL_SPACE, pBlkTblRcd, 
		//	AcDb::kForWrite); 
		//pBlkTbl->close(); 

		//// 创建两个圆 
		//AcDbCircle *pCir1 = new AcDbCircle(AcGePoint3d(1,1,1),  
		//	AcGeVector3d(0,0,1), 1.0); 
		//AcDbCircle *pCir2 = new AcDbCircle(AcGePoint3d(4,4,4),  
		//	AcGeVector3d(0,0,1), 2.0); 
		//pBlkTblRcd->appendAcDbEntity(pCir1); 
		//pCir1->close(); 

#endif


	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CArxProject2App)

ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject2App, vgPluginCad, _HelloWorld,	HelloWorld, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CArxProject2App, vgPluginCad, _tGrid,		tGrid,		 ACRX_CMD_TRANSPARENT, NULL)
