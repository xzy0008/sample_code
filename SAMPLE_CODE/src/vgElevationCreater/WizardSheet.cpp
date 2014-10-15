// WizardSheet.cpp : Defines the class behaviors for the application.
//

#include <vgStableHeaders.h>
#include "WizardSheet.h"
#include "WizardSheetDlg.h"

#include "vgWizardPropertySheet.h"

#include <vgTerritory/vgtDemArea.h>


#include <gdal/ogr_api.h>
#include <gdal/ogr_spatialref.h>

#include <vgTerritory/vgtGeoUtility.h>

#include <vgTerritory/vgtGeoImage.h>
#include <vgTerritory/vgtGeoDemManager.h>

#include <vgImage/vgiCximageWrapper.h>
#include <vgImage/vgiImage.h>

#include <nvtt/nvtt.h>
#include <nvtt/nvtt_wrapper.h>


#include <vgImage/vgiFreeImageWrapper.h>
#include <vgTerritory/vgtGdalHelper.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWizardSheetApp

BEGIN_MESSAGE_MAP(CWizardSheetApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWizardSheetApp construction

CWizardSheetApp::CWizardSheetApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	//std::locale::global(std::locale("CHS"));
}


// The one and only CWizardSheetApp object

CWizardSheetApp theApp;


// CWizardSheetApp initialization

BOOL CWizardSheetApp::InitInstance()
{
	using namespace vgImage;

#if 1
	FreeImageWrapper img1;
	img1.loadFromFile("d:\\67-00.bmp");

	img1.resize( vgKernel::ImageSize(2000,2000) );

	//RGBQUAD dkd;
	//img1.getPixelColor( 0 , 0 , &dkd );


	//FreeImageWrapper img2;
	//img2.loadFromFile( "d:\\N-08-55_2000.bmp" );

	//bool pasok = img1.overlap2( img2 , 100 , 100 );

	//assert( pasok == true );

	//img1.clearColor( 0 ,  255 , 125 , 130 );

	//img1.saveToFile("d:\\4444444.tif",TIFF_NONE);
	img1.saveToFile("d:\\fzzzzzzzzzzzzzzz2.tif");

	

	int dd = 12;
#endif

#if 0
	GDALAllRegister();

	//vgKernel::StreamReaderPtr preader = 
	//	vgKernel::StreamReaderFactory::createFromFile("d:\\srtm_10_02.tif");

	//int nInDataLength  = preader->size();

	//char* pabyInData = new char[ nInDataLength ];

	//preader->read( pabyInData , nInDataLength );

	//preader.setNull();


	//FILE* ff = VSIFileFromMemBuffer( "/vsimem/work.dat", (GByte*)pabyInData, 
	//	nInDataLength, TRUE );
	//VSIFCloseL( ff ); 

	using namespace vgTerritory;

	bool dggdd = GdalHelper::createMemFile( "d:\\srtm_10_02.tif" );

	GDALDataset  *poDataset =
		(GDALDataset*)GDALOpen(  
		GdalHelper::getMemName( "d:\\srtm_10_02.tif" ).c_str(), GA_ReadOnly ); 

	assert( poDataset != NULL );

	int ddd = poDataset->GetRasterXSize();

	
	float *pafScanline;
	int   nXSize = poDataset->GetRasterXSize();
	int ysize = poDataset->GetRasterYSize();

	pafScanline = new float[ nXSize * ysize ];

	CPLErr ret = poDataset->RasterIO( GF_Read, 0, 0, nXSize, ysize, 
		pafScanline, nXSize, ysize, GDT_Float32, 1,NULL,
		0, 0 ,0);

	assert( ret == CE_None );

	CPLFree( pafScanline );
	
	delete poDataset;

	GdalHelper::deleteMemFile("d:\\srtm_10_02.tif");

#endif

#if 0
	FreeImageWrapper* frimg=new FreeImageWrapper;
	bool loadok = frimg->loadFromFile( "d:\\67-00.bmp" );
	assert( loadok == true );

	//BOOL convertok = frimg->convertToType( FIT_BITMAP );
	//assert( convertok == TRUE );

	//frimg->convertTo32Bits();

	//bool saveok = frimg->saveToFile( "d:\\aaaa.bmp" );
	//assert( saveok == true );

	frimg->saveToDdsFile("d:\\aaa.dds" , FreeImageWrapper::DDS_FORMAT_DXT3 , true );

	delete frimg;
#endif

	//int w = 15;
	//int h= 190;
	//char* buff = new char[ w * h * 3 ];

	//memset( buff , 255 , w * h  * 3 );

	//FreeImageWrapper fimg;
	//bool okk = fimg.createFromArray( buff , w , h , 24 );

	//assert( okk == true );

	//bool saveok = fimg.save("d:\\zzzzzzzzz.bmp");
	//assert( saveok == true );

	//////////////////////////////////////////////////////////////////////////

// 	_CrtSetBreakAlloc( 19929  );
// 	_CrtSetBreakAlloc( 19886 );
// 	_CrtSetBreakAlloc( 18532 );
// 	_CrtSetBreakAlloc( 18489 );
// 	_CrtSetBreakAlloc( 19595 );

	//fipImage img;

	//BOOL loadok = img.load( "d:\\N-08-55_2000.jpg" );
	//assert( loadok == TRUE );

	////img.flipHorizontal();
	//img.flipVertical();
	//img.save("d:\\aaaaa.bmp");

	//FREE_IMAGE_COLOR_TYPE t = img.getColorType();

	//FREE_IMAGE_FORMAT format =  fipImage::identifyFIF("d:\\N-08-55_2000.bmp");


	//fipImage img2;
	//BOOL look = img2.load( "d:\\aaa.png");

	//assert( look == TRUE );

	//FREE_IMAGE_COLOR_TYPE t2 = img2.getColorType();

	//img2.save( "d:\\aaa.bmp" );

	using namespace vgImage;

	//CximageWrapper img;
	//bool lok = img.loadFromFile("D:\\__temp\\___dem_ed0bd63f493a415d\\tahoedems2.png");

	//assert( lok == true );

	//img.saveToFile("d:\\ffff.bmp");

	//img.saveToFile("d:\\ffffffff.jpg");

	//img.saveToDdsFile("d:\\oooooooo.dds" ,CximageWrapper::DDS_FORMAT_DXT1 );

	//GDALAllRegister();

	//GDALDataset* data = (GDALDataset*)GDALOpen("d:\\aa.jpg" , GA_ReadOnly );




	//CxImage img;
	//bool loaddd=img.Load( "d:\\aa.bmp" , CXIMAGE_FORMAT_BMP);

	//bool saveok = img.Save("d:\\ggggggggg2.jp2" , CXIMAGE_FORMAT_JP2 );
	////bool saf = img.Save("d:\\fffa.jp2" , CXIMAGE_FORMAT_JP2 );
	//////////////////////////////////////////////////////////////////////////



	//GDALAllRegister();

	//GDALDataset* dataset  = (GDALDataset*)GDALOpen("D:\\___temp\\aa.tif" , 
	//	GA_ReadOnly);

	//int w = dataset->GetRasterXSize();
	//int h = dataset->GetRasterYSize();

	//int ddd = dataset->GetRasterCount();

	//int ddd444=42;


	//dataset->RasterIO()

	//long w;
	//long h;
	//CxImage::GetHeaderInfo("d:\\ggggggggg2.jp2" , CXIMAGE_FORMAT_JP2 ,
	//	w , h );




	//CWinApp::InitInstance();
	AfxEnableControlContainer();

#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif


	InitCommonControls();
	InitContextMenuManager ();
	InitShellManager ();


	//CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
	//CBCGPButton::EnableWinXPTheme ();


	WizardPropertySheet wiz("地形生成向导");

	_sheet = &wiz;

	wiz.DoModal();

	BCGCBProCleanUp ();

	return FALSE;


	//// Standard initialization
	//// If you are not using these features and wish to reduce the size
	//// of your final executable, you should remove from the following
	//// the specific initialization routines you do not need
	//// Change the registry key under which our settings are stored
	//// TODO: You should modify this string to be something appropriate
	//// such as the name of your company or organization
	////SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	//CWizardSheetDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with OK
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: Place code here to handle when the dialog is
	//	//  dismissed with Cancel
	//}

	//// Since the dialog has been closed, return FALSE so that we exit the
	////  application, rather than start the application's message pump.
	//return FALSE;
}
