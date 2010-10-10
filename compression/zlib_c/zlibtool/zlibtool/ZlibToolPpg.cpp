// ZlibToolPpg.cpp : Implementation of the CZlibToolPropPage property page class.

#include "stdafx.h"
#include "ZlibTool.h"
#include "ZlibToolPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CZlibToolPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CZlibToolPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CZlibToolPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CZlibToolPropPage, "ZLIBTOOL.ZlibToolPropPage.1",
	0xe88121a4, 0x9fa9, 0x11cf, 0x9d, 0x9f, 0, 0xaa, 0, 0x3a, 0x3a, 0xa3)


/////////////////////////////////////////////////////////////////////////////
// CZlibToolPropPage::CZlibToolPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CZlibToolPropPage

BOOL CZlibToolPropPage::CZlibToolPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ZLIBTOOL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolPropPage::CZlibToolPropPage - Constructor

CZlibToolPropPage::CZlibToolPropPage() :
	COlePropertyPage(IDD, IDS_ZLIBTOOL_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CZlibToolPropPage)
	m_level = 0;
	m_inputFile = _T("");
	m_outputFile = _T("");
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolPropPage::DoDataExchange - Moves data between page and properties

void CZlibToolPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CZlibToolPropPage)
	DDP_CBIndex(pDX, IDC_COMPRESS_LEVEL, m_level, _T("Level") );
	DDX_CBIndex(pDX, IDC_COMPRESS_LEVEL, m_level);
	DDP_Text(pDX, IDC_INPUT_FILE, m_inputFile, _T("InputFile") );
	DDX_Text(pDX, IDC_INPUT_FILE, m_inputFile);
	DDP_Text(pDX, IDC_OUTPUT_FILE, m_outputFile, _T("OutputFile") );
	DDX_Text(pDX, IDC_OUTPUT_FILE, m_outputFile);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolPropPage message handlers
