// ZlibToolCtl.h : Declaration of the CZlibToolCtrl OLE control class.

/////////////////////////////////////////////////////////////////////////////
// CZlibToolCtrl : See ZlibToolCtl.cpp for implementation.

#include "zlibengn.h"

class CZlibToolCtrl;

//
// The excitement all shows up here, where I defined a
// specific implementation of the wrapper class.  It has
// a couple of member functions used to provide user
// interface information, plus a pointer back to the
// OCX class, which needs information as well.
//
class MyZlibEngine : public ZlibEngine {
    public :
        virtual void progress( int percent );
        virtual void status( char *message );
        CZlibToolCtrl *m_pCtrl;
};

class CZlibToolCtrl : public COleControl
{
	DECLARE_DYNCREATE(CZlibToolCtrl)

// Constructor
public:
	CZlibToolCtrl();

// Overrides

	// Drawing function
	virtual void OnDraw(
				CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);

	// Persistence
	virtual void DoPropExchange(CPropExchange* pPX);

	// Reset control state
	virtual void OnResetState();

// Implementation
protected:
	~CZlibToolCtrl();
        friend class MyZlibEngine; //Need to FireProgress()
	short m_level;             // Added to support the Zlib interface
        MyZlibEngine m_Engine;     // The Zlib wrapper class object

	DECLARE_OLECREATE_EX(CZlibToolCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CZlibToolCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CZlibToolCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CZlibToolCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	//{{AFX_MSG(CZlibToolCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CZlibToolCtrl)
	CString m_inputFile;
	afx_msg void OnInputFileChanged();
	CString m_outputFile;
	afx_msg void OnOutputFileChanged();
	CString m_status;
	afx_msg void OnStatusChanged();
	afx_msg short GetLevel();
	afx_msg void SetLevel(short nNewValue);
	afx_msg short Compress();
	afx_msg short Decompress();
	afx_msg void Abort();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CZlibToolCtrl)
	void FireProgress(short percent_complete)
		{FireEvent(eventidProgress,EVENT_PARAM(VTS_I2), percent_complete);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CZlibToolCtrl)
	dispidInputFile = 1L,
	dispidOutputFile = 2L,
	dispidLevel = 4L,
	dispidStatus = 3L,
	dispidCompress = 5L,
	dispidDecompress = 6L,
	dispidAbort = 7L,
	eventidProgress = 1L,
	//}}AFX_DISP_ID
	};
};

