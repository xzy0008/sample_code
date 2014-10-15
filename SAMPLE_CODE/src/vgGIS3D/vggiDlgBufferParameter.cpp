// vggiDlgBufferParameter.cpp : implementation file
//

#include <vgStableHeaders.h>
#include <vgGIS3D/vggiDlgBufferParameter.h>
#include <vgGIS3D/vggiGisDataManager.h>

// vggiDlgBufferParameter dialog

IMPLEMENT_DYNAMIC(DlgBufferParameter, CDialog)

DlgBufferParameter::DlgBufferParameter(CWnd* pParent /*=NULL*/)
	: CDialog(DlgBufferParameter::IDD, pParent)
	, m_rightRadius(0)
	, m_leftRadius(0)
	, m_bCheck(FALSE)
{
	m_bEnableSelLayer = false;
	m_selLayerName = "";
}

DlgBufferParameter::~DlgBufferParameter()
{
}

void DlgBufferParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BUFFER_LEFT_RADIUS, m_leftRadius);
	DDX_Text(pDX, IDC_BUFFER_RIGHT_RADIUS, m_rightRadius);
	DDX_Check(pDX, IDC_CHECK_LEFT_RIGHT_BUFFER, m_bCheck);
	DDX_Control(pDX, IDC_COMBO_SELECT_LAYER, m_selectLayer);
}


BEGIN_MESSAGE_MAP(DlgBufferParameter, CDialog)
	ON_BN_CLICKED(IDC_CHECK_LEFT_RIGHT_BUFFER, &DlgBufferParameter::OnBnClickedCheckLeftRightBuffer)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_LAYER, &DlgBufferParameter::OnCbnSelchangeComboSelectLayer)
END_MESSAGE_MAP()


// vggiDlgBufferParameter message handlers

BOOL DlgBufferParameter::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	( GetDlgItem( IDC_BUFFER_LEFT_RADIUS ) )->EnableWindow(true);
	( GetDlgItem( IDC_BUFFER_RIGHT_RADIUS ) )->EnableWindow(false);


	if ( m_bEnableSelLayer )
	{
		vgGIS3D::DataSourcePtrMap *pDataSource  = vgGIS3D::GisDataManager::getSingleton().getDataSources();

		vgGIS3D::DataSourcePtrMap::iterator iter = pDataSource->begin();
		vgGIS3D::DataSourcePtrMap::iterator iter_end = pDataSource->end();

		bool bHasItem = false;

		for ( ; iter != iter_end ;++iter )
		{
			vgGIS3D::DataSourcePtr pds = iter->second;

			vgGIS3D::LayerPtrVector *pVec = pds->getLayerPtrVector();

			for (int i=0; i<pVec->size(); i++)
			{
				bHasItem = true;
				m_selectLayer.AddString( pVec->at(i)->getName().c_str() );
			}
		}

		if ( bHasItem )
		{
			m_selectLayer.SetCurSel(0);

			CString layerName;
			m_selectLayer.GetLBText( 0, layerName );
			m_selLayerName = layerName.GetString();
		}

	}
	else
	{
		( GetDlgItem( IDC_COMBO_SELECT_LAYER ) )->EnableWindow( false );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void DlgBufferParameter::OnBnClickedCheckLeftRightBuffer()
{
	// TODO: Add your control notification handler code here
	m_bCheck = !m_bCheck;

	if ( m_bCheck )
	{
		( GetDlgItem( IDC_BUFFER_LEFT_RADIUS ) )->EnableWindow(true);
		( GetDlgItem( IDC_BUFFER_RIGHT_RADIUS ) )->EnableWindow(true);
	}
	else
	{
		( GetDlgItem( IDC_BUFFER_LEFT_RADIUS ) )->EnableWindow(true);
		( GetDlgItem( IDC_BUFFER_RIGHT_RADIUS ) )->EnableWindow(false);
	}
}

void DlgBufferParameter::OnCbnSelchangeComboSelectLayer()
{
	// TODO: Add your control notification handler code here
	CString layerName;

	int nSelIndex = 0;
	nSelIndex = m_selectLayer.GetCurSel();

	if ( -1 == nSelIndex )
	{
		m_selLayerName = "";
		return;
	}

	layerName.GetBuffer( m_selectLayer.GetLBTextLen( nSelIndex ) );
	m_selectLayer.GetLBText( m_selectLayer.GetCurSel(), layerName );

	m_selLayerName = layerName.GetString(); 
}