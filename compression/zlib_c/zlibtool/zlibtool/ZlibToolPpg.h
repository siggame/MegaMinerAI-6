// ZlibToolPpg.h : Declaration of the CZlibToolPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CZlibToolPropPage : See ZlibToolPpg.cpp.cpp for implementation.

class CZlibToolPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CZlibToolPropPage)
	DECLARE_OLECREATE_EX(CZlibToolPropPage)

// Constructor
public:
	CZlibToolPropPage();

// Dialog Data
	//{{AFX_DATA(CZlibToolPropPage)
	enum { IDD = IDD_PROPPAGE_ZLIBTOOL };
	int	m_level;
	CString	m_inputFile;
	CString	m_outputFile;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CZlibToolPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
