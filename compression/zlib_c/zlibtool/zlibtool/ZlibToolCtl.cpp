// ZlibToolCtl.cpp : Implementation of the CZlibToolCtrl OLE control class.

#include "stdafx.h"
#include "ZlibTool.h"
#include "ZlibToolCtl.h"
#include "ZlibToolPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CZlibToolCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CZlibToolCtrl, COleControl)
	//{{AFX_MSG_MAP(CZlibToolCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CZlibToolCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CZlibToolCtrl)
	DISP_PROPERTY_NOTIFY(CZlibToolCtrl, "InputFile", m_inputFile, OnInputFileChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CZlibToolCtrl, "OutputFile", m_outputFile, OnOutputFileChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CZlibToolCtrl, "Status", m_status, OnStatusChanged, VT_BSTR)
	DISP_PROPERTY_EX(CZlibToolCtrl, "Level", GetLevel, SetLevel, VT_I2)
	DISP_FUNCTION(CZlibToolCtrl, "Compress", Compress, VT_I2, VTS_NONE)
	DISP_FUNCTION(CZlibToolCtrl, "Decompress", Decompress, VT_I2, VTS_NONE)
	DISP_FUNCTION(CZlibToolCtrl, "Abort", Abort, VT_EMPTY, VTS_NONE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CZlibToolCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CZlibToolCtrl, COleControl)
	//{{AFX_EVENT_MAP(CZlibToolCtrl)
	EVENT_CUSTOM("Progress", FireProgress, VTS_I2)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CZlibToolCtrl, 1)
	PROPPAGEID(CZlibToolPropPage::guid)
END_PROPPAGEIDS(CZlibToolCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CZlibToolCtrl, "ZLIBTOOL.ZlibToolCtrl.1",
	0xe88121a3, 0x9fa9, 0x11cf, 0x9d, 0x9f, 0, 0xaa, 0, 0x3a, 0x3a, 0xa3)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CZlibToolCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DZlibTool =
		{ 0xe88121a1, 0x9fa9, 0x11cf, { 0x9d, 0x9f, 0, 0xaa, 0, 0x3a, 0x3a, 0xa3 } };
const IID BASED_CODE IID_DZlibToolEvents =
		{ 0xe88121a2, 0x9fa9, 0x11cf, { 0x9d, 0x9f, 0, 0xaa, 0, 0x3a, 0x3a, 0xa3 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwZlibToolOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CZlibToolCtrl, IDS_ZLIBTOOL, _dwZlibToolOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl::CZlibToolCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CZlibToolCtrl

BOOL CZlibToolCtrl::CZlibToolCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_ZLIBTOOL,
			IDB_ZLIBTOOL,
			afxRegApartmentThreading,
			_dwZlibToolOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl::CZlibToolCtrl - Constructor

//
// Note that my engine member has a pointer to this, m_pCtrl.
// I need this when issuing progress events.  That gets set
// up here in the ctor.
//

CZlibToolCtrl::CZlibToolCtrl()
{
	InitializeIIDs(&IID_DZlibTool, &IID_DZlibToolEvents);
	// TODO: Initialize your control's instance data here.
    m_Engine.m_pCtrl = this;
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl::~CZlibToolCtrl - Destructor

CZlibToolCtrl::~CZlibToolCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl::OnDraw - Drawing function

void CZlibToolCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	DoSuperclassPaint(pdc, rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl::DoPropExchange - Persistence support

void CZlibToolCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
//
// I have to do a propery exchange for these properties, or they
// won't show up in VB or Delphi property inspectors.
//
    PX_Short( pPX, _T("Level"), m_level, short( 6 ) );
    PX_String( pPX, _T("InputFile"), m_inputFile, "" );
    PX_String( pPX, _T("OutputFile"), m_outputFile, "" );
    PX_String( pPX, _T("Status"), m_status, "" );
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl::OnResetState - Reset control to default state

void CZlibToolCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl::AboutBox - Display an "About" box to the user

void CZlibToolCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_ZLIBTOOL);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CZlibToolCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("msctls_progress32");
	return COleControl::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl::IsSubclassedControl - This is a subclassed control

BOOL CZlibToolCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl::OnOcmCommand - Handle command messages

LRESULT CZlibToolCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl message handlers

int CZlibToolCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
//
// When in design mode, I set the progress bar to a 50%
// position to make it clear that it is a progress bar,
// not some other sort of field.  When running in an
// app , it starts off at 0.
//
    if ( AmbientUserMode() )
	    SendMessage( PBM_SETPOS, 0, 0 );
	else
	    SendMessage( PBM_SETPOS, 50, 0 );

	return 0;
}

void CZlibToolCtrl::OnInputFileChanged()
{
	// TODO: Add notification handler code
//
// This is kind of a tricky bit.  If the input file
// doesn't end in ".ZL", I assume it's a plain text
// file waiting to be compressed.  As a convenience
// to the programmer, I then create an output file
// name that just has ".ZL" appended to the end of
// the file name.  If the name already ends with the
// ".ZL" string, it seems reasonable to assume it is
// a file that has been compressed already.  To help
// in this case, I make a new name that has the '.ZL"
// removed.
//
	CString temp = m_inputFile;
	temp.MakeUpper();
	if ( temp.Right( 3 ) == _T( ".ZL" ) )
	    m_outputFile = m_inputFile.Left( m_inputFile.GetLength() - 3 );
	else
    	m_outputFile = m_inputFile + ".ZL";
	SendMessage( PBM_SETPOS, 0, 0 );
	BoundPropertyChanged( DISPID_UNKNOWN );
	SetModifiedFlag();
}

//
//  When I change the output file property, I want
//  programs like Delphi to take note of the fact
//  immediately.  To make that happen, I have to
//  have this handler in the control class, which
//  just raises the relevant flags.
//

void CZlibToolCtrl::OnOutputFileChanged()
{
	// TODO: Add notification handler code

	BoundPropertyChanged( DISPID_UNKNOWN );
	SetModifiedFlag();
}

//
// Simple enough.  Even thous m_level is an enumerated type,
// we just treat it as an integer here.
//
short CZlibToolCtrl::GetLevel()
{
	// TODO: Add your property handler here

	return m_level;
}

//
// When the user modifies the level property,
// I have to test to be sure it's in range.
// Other than that, it's easy to set.
//
void CZlibToolCtrl::SetLevel(short nNewValue)
{
	// TODO: Add your property handler here
    if ( nNewValue < 0 || nNewValue > 9 )
        return;
    m_level = nNewValue;

    SetModifiedFlag();
}

//
// This is the progress function called by the wrapper
// class.  Note that this *isn't* a member of CZlibToolCtrl,
// it's part of my wrapper class that does the work.  All
// it has to do is upate the progress bar for the embedded
// meter in this OCX, and fire a progress message to the
// host program.
//
void MyZlibEngine::progress( int percent )
{
	m_pCtrl->SendMessage( PBM_SETPOS, percent, 0 );
	m_pCtrl->FireProgress( percent );
}

//
// This is the status function called by the wrapper
// class.  I just store it in the m_status member of
// the OCX class, where the calling program will be
// able to get at it easily.
//
void MyZlibEngine::status( char *message )
{
    m_pCtrl->m_status = message;
}

//
// The compress and decompress member functions
// just use the engine wrapper member to do all the
// work.  They pass status and progress messages back
// to the OCX via the member functions defined earlier
// in this file.
//
short CZlibToolCtrl::Compress()
{
    return m_Engine.compress( m_inputFile, m_outputFile, m_level );
}

short CZlibToolCtrl::Decompress()
{
    return m_Engine.decompress( m_inputFile, m_outputFile );
}

//
// Aborting just means setting the abort flag in
// the wrapper class.
//
void CZlibToolCtrl::Abort()
{
	// TODO: Add your dispatch handler code here
	m_Engine.set_abort_flag( 1 );

}

//
// This function just ensures that programs such as
// Delphi and VB will be updated properly when the
// OCX status changes.
//
void CZlibToolCtrl::OnStatusChanged()
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}
