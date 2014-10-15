// dlgCoordTransform.cpp : 实现文件
//


#include "vgStableHeaders.h"
#include "vgGIS/dlgCoordTransform.h"
/*#include "gdal/ogr_avc.h"*/
#include <vgKernel/vgkVec3.h>
#include <vgKernel/vgkCoordSystem.h>

// CdlgCoordTransform 对话框

IMPLEMENT_DYNAMIC(CdlgCoordTransform, CDialog)



CdlgCoordTransform::CdlgCoordTransform(CWnd* pParent /*=NULL*/)
	: CDialog(CdlgCoordTransform::IDD, pParent)
	, strSourceCoordPath(_T(""))
	, strTargetCoordPath(_T(""))
	, strSourceParam(_T(""))
	, strTargetParam(_T(""))
{

}

CdlgCoordTransform::~CdlgCoordTransform()
{

}

void CdlgCoordTransform::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SOURPATH, strSourceCoordPath);
	DDX_Text(pDX, IDC_EDIT_TARGETPATH, strTargetCoordPath);
	DDX_Text(pDX, IDC_EDIT_SOURCE_PARAM, strSourceParam);
	DDX_Text(pDX, IDC_EDIT_TARGET_PARAM, strTargetParam);
}


BEGIN_MESSAGE_MAP(CdlgCoordTransform, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_SOURCE_PATH, &CdlgCoordTransform::OnBnClickedBtnSourcePath)
	ON_BN_CLICKED(IDC_BTN_TARGET_PATH, &CdlgCoordTransform::OnBnClickedBtnTargetPath)
	ON_BN_CLICKED(IDOK, &CdlgCoordTransform::OnBnClickedOk)
END_MESSAGE_MAP()


// CdlgCoordTransform 消息处理程序

void CdlgCoordTransform::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	delete this;
}

void CdlgCoordTransform::OnBnClickedBtnSourcePath()
{
#if 0
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"project files(*.prj)|*.prj|";

	CFileDialog dlg (TRUE, "prj", NULL,
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters);	

	std::string fileName;

	if( dlg.DoModal ()==IDOK )
	{
		fileName = dlg.GetPathName();
		strSourceCoordPath = dlg.GetPathName();
		UpdateData(false);

		CString strFileName = dlg.GetFileName();

		//读取prj文件，数据读入
		const char  *pszPrjFile = fileName.c_str();

		FILE	*fp;
		fp = VSIFOpen( pszPrjFile, "r" );

		if( fp != NULL )
		{
			char **papszLines;

			VSIFClose( fp );

			papszLines = CSLLoad( pszPrjFile );

			if( vg_SourceSPF.importFromESRI( papszLines ) == OGRERR_NONE )
			{
				double dsemiMaj = vg_SourceSPF.GetSemiMajor();//长半轴
				double dsemiMor = vg_SourceSPF.GetSemiMinor();//短半轴
				double dFlat = vg_SourceSPF.GetInvFlattening();//偏心率

				const char *pszProjection = vg_SourceSPF.GetAttrValue("PROJECTION");
				const char *pDatum = vg_SourceSPF.GetAttrValue("DATUM");			//大地基准面
				const char *pGeoCS = vg_SourceSPF.GetAttrValue( "GEOGCS" );			//获得地理坐标系统
				const char *pSpheroid = vg_SourceSPF.GetAttrValue("SPHEROID");		//椭球体

				char **unitname = new (char* [32]);
				char **primeMerdian = new (char* [64]);
				char **angularUnit = new (char* [32]);

				double dUnits = vg_SourceSPF.GetLinearUnits(unitname);
				double dPrimeMedia = vg_SourceSPF.GetPrimeMeridian(primeMerdian);
				double dAngularUnit = vg_SourceSPF.GetAngularUnits(angularUnit);

				double dfalseEasting = vg_SourceSPF.GetProjParm(SRS_PP_FALSE_EASTING, 0.00000, NULL);
				double dfalseNorthing = vg_SourceSPF.GetProjParm(SRS_PP_FALSE_NORTHING, 0.00000, NULL);
				double dcentral_Meridian = vg_SourceSPF.GetProjParm(SRS_PP_CENTRAL_MERIDIAN, 0.00000, NULL);
				double dScale_Factor = vg_SourceSPF.GetProjParm(SRS_PP_SCALE_FACTOR, 0.00000, NULL);
				double dLatit_Origin = vg_SourceSPF.GetProjParm(SRS_PP_LATITUDE_OF_ORIGIN, 0.00000, NULL);
				double dStand_parallel_1 = vg_SourceSPF.GetProjParm(SRS_PP_STANDARD_PARALLEL_1, 0.00000, NULL);	//标准纬线1
				double dStand_parallel_2 = vg_SourceSPF.GetProjParm(SRS_PP_STANDARD_PARALLEL_2, 0.00000, NULL);	//标准纬线2
				double dlongitude_center = vg_SourceSPF.GetProjParm(SRS_PP_LONGITUDE_OF_CENTER, 0.00000, NULL);	//经线中心
				double dlatitude_center = vg_SourceSPF.GetProjParm(SRS_PP_LATITUDE_OF_CENTER, 0.00000, NULL);	//纬线中心

				strSourceParam.Format("文件名称:%s,\r\n\r\n投影系名称:%s,\r\n东偏移值:%f,\r\n北偏移值:%f,\r\n中央经线:%f,\r\n缩放比例:%f,\r\n纬度原点:%f,\r\n标准纬线1:%f,\r\n标准纬线2:%f,\r\n纬线中心:%f,\r\n经线中心:%f,\r\n单位:%s(%.9f),\r\n\r\n地理坐标系统:%s,\r\n角度单位:%s(%.9f),\r\n本初子午线:%s(%.7f),\r\n大地基准面:%s,\r\n椭球体:%s,\r\n长半轴:%f,\r\n短半轴:%f,\r\n偏心率:%f",
					strFileName,
					pszProjection, 
					dfalseEasting, 
					dfalseNorthing,
					dcentral_Meridian,
					dScale_Factor,
					dLatit_Origin,
					dStand_parallel_1,
					dStand_parallel_2,
					dlongitude_center,
					dlatitude_center,
					*unitname,
					dUnits,
					pGeoCS,
					*angularUnit,
					dAngularUnit,
					*primeMerdian,
					dPrimeMedia,
					pDatum,
					pSpheroid,
					dsemiMaj,
					dsemiMor,
					dFlat);
				UpdateData(false);

				delete unitname;
				delete primeMerdian;
				delete angularUnit;
			}
		}
	}
#endif
}

void CdlgCoordTransform::OnBnClickedBtnTargetPath()
{
#if 0
	// TODO: 在此添加控件通知处理程序代码
	char szFilters[]=
		"project files(*.prj)|*.prj|";

	CFileDialog dlg (TRUE, "prj", NULL,
		OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters);

	std::string fileName;

	if( dlg.DoModal ()==IDOK )
	{
		fileName = dlg.GetPathName();
		strTargetCoordPath = dlg.GetPathName();
		UpdateData(false);

		CString strFileName = dlg.GetFileName();

		//AfxMessageBox(fileName.c_str());
		//读取prj文件，数据读入

		const char  *pszPrjFile = fileName.c_str();

		FILE	*fp;
		fp = VSIFOpen( pszPrjFile, "r" );

		if( fp != NULL )
		{
			char	**papszLines;
			VSIFClose( fp );

			papszLines = CSLLoad( pszPrjFile );

			if( vg_TargetSPF.importFromESRI( papszLines ) == OGRERR_NONE )
			{
				//char    *pszWKT = NULL;
				//vg_TargetSPF.exportToWkt( &pszWKT );
				//printf( "%s", pszWKT );
				//strTargetParam.Format("%s",pszWKT);

				double dsemiMaj = vg_TargetSPF.GetSemiMajor();//长半轴
				double dsemiMor = vg_TargetSPF.GetSemiMinor();//短半轴
				double dFlat = vg_TargetSPF.GetInvFlattening();//偏心率

				const char *pszProjection = vg_TargetSPF.GetAttrValue("PROJECTION");//获得投影系统名称
				const char *pDatum = vg_TargetSPF.GetAttrValue("DATUM");			//大地基准面
				const char *pGeoCS = vg_TargetSPF.GetAttrValue( "GEOGCS" );			//获得地理坐标系统
				const char *pSpheroid = vg_TargetSPF.GetAttrValue("SPHEROID");		//椭球体

				char **unitname = new (char* [32]);									//单位
				char **primeMerdian = new (char* [64]);								//本初子午线
				char **angularUnit = new (char* [32]);								//角度单位

				double dUnits = vg_TargetSPF.GetLinearUnits(unitname);				//获得单位
				double dPrimeMedia = vg_TargetSPF.GetPrimeMeridian(primeMerdian);	//获得本初子午线
				double dAngularUnit = vg_TargetSPF.GetAngularUnits(angularUnit);	//获得角度单位

				double dfalseEasting = vg_TargetSPF.GetProjParm(SRS_PP_FALSE_EASTING, 0.00000, NULL);			//东偏移值
				double dfalseNorthing = vg_TargetSPF.GetProjParm(SRS_PP_FALSE_NORTHING, 0.00000, NULL);			//北偏移值
				double dcentral_Meridian = vg_TargetSPF.GetProjParm(SRS_PP_CENTRAL_MERIDIAN, 0.00000, NULL);	//中央经线值
				double dScale_Factor = vg_TargetSPF.GetProjParm(SRS_PP_SCALE_FACTOR, 0.00000, NULL);			//缩放比例
				double dLatit_Origin = vg_TargetSPF.GetProjParm(SRS_PP_LATITUDE_OF_ORIGIN, 0.00000, NULL);		//纬度原点
				double dStand_parallel_1 = vg_TargetSPF.GetProjParm(SRS_PP_STANDARD_PARALLEL_1, 0.00000, NULL);	//标准纬线1
				double dStand_parallel_2 = vg_TargetSPF.GetProjParm(SRS_PP_STANDARD_PARALLEL_2, 0.00000, NULL);	//标准纬线2
				double dlongitude_center = vg_TargetSPF.GetProjParm(SRS_PP_LONGITUDE_OF_CENTER, 0.00000, NULL);	//经线中心
				double dlatitude_center = vg_TargetSPF.GetProjParm(SRS_PP_LATITUDE_OF_CENTER, 0.00000, NULL);	//纬线中心


				strTargetParam.Format("文件名称:%s,\r\n\r\n投影系名称:%s,\r\n东偏移值:%f,\r\n北偏移值:%f,\r\n中央经线:%f,\r\n缩放比例:%f,\r\n纬度原点:%f,\r\n标准纬线1:%f,\r\n标准纬线2:%f,\r\n纬线中心:%f,\r\n经线中心:%f,\r\n单位:%s(%.9f),\r\n\r\n地理坐标系统:%s,\r\n角度单位:%s(%.9f),\r\n本初子午线:%s(%.7f),\r\n大地基准面:%s,\r\n椭球体:%s,\r\n长半轴:%f,\r\n短半轴:%f,\r\n偏心率:%f",
					strFileName,
					pszProjection, 
					dfalseEasting, 
					dfalseNorthing,
					dcentral_Meridian,
					dScale_Factor,
					dLatit_Origin,
					dStand_parallel_1,
					dStand_parallel_2,
					dlongitude_center,
					dlatitude_center,
					*unitname,
					dUnits,
					pGeoCS,
					*angularUnit,
					dAngularUnit,
					*primeMerdian,
					dPrimeMedia,
					pDatum,
					pSpheroid,
					dsemiMaj,
					dsemiMor,
					dFlat);

				UpdateData(false);

				delete unitname;
				delete primeMerdian;
				delete angularUnit;
			}
		}
	}
#endif
}

void CdlgCoordTransform::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if ( strSourceCoordPath.GetLength() == 0 )
	{
		AfxMessageBox("请选择原投影坐标系！");
		return;
	}
	if ( strTargetCoordPath.GetLength() == 0 )
	{
		AfxMessageBox("请选择目标投影坐标系！");
		return;
	}
	
	if (&vg_SourceSPF == NULL)
	{
		AfxMessageBox("原投影坐标系为空！");
	}

	if (&vg_TargetSPF == NULL)
	{
		AfxMessageBox("目标投影坐标系为空！");
	}
	
 	vgKernel::Vec3 vgCoord = vgKernel::CoordSystem::getSingleton().getProjectionCoord();
 
 	double originX = (double)vgCoord.x;
 	double originY = (double)vgCoord.y;
 	double originZ = (double)vgCoord.z;

	OGRCoordinateTransformation *pvg_coordTrans = NULL;

	pvg_coordTrans = OGRCreateCoordinateTransformation(&vg_SourceSPF, &vg_TargetSPF);
	
	//CString strResult;

	if (pvg_coordTrans != NULL)
	{
		pvg_coordTrans->Transform( 1, &originX, &originY, &originZ) ;
		//strResult.Format("转换结果:(x:%f, y:%f, z:%f)", originX, originY, originZ);
		//AfxMessageBox(strResult);
		vgKernel::Vec3 resCoord;
		resCoord.x = originX;
		resCoord.y = originY;
		resCoord.z = originZ;
		//将转换后的值设为场景原点坐标
		vgKernel::CoordSystem::getSingleton().setProjectionCoord(resCoord);
		AfxMessageBox("转换完成！");
		
	}
	else
	{
		AfxMessageBox("转换失败！");
	}

	OnOK();
}
