// SymmetryDlg.h : header file
//

#if !defined(AFX_SYMMETRYDLG_H__0639AD06_80BA_4457_83F9_D067D452CAAA__INCLUDED_)
#define AFX_SYMMETRYDLG_H__0639AD06_80BA_4457_83F9_D067D452CAAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSymmetryDlg dialog

#define IDC_EDIT_FILE  1000
#define IDC_EDIT_DIR  1001

class CSymmetryDlg : public CDialog
{
// Construction
public:
	CSymmetryDlg(CWnd* pParent = NULL);	// standard constructor
	CString	m_dir;
	CString	m_dir_file_ext;
	CString m_file_ext;
	CString m_file;
	CString m_ext;
// Dialog Data
	//{{AFX_DATA(CSymmetryDlg)
	enum { IDD = IDD_SYMMETRY_DIALOG };
	CString	m_dir_name;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSymmetryDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSymmetryDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnFileOpen();
	afx_msg void OnRun();
	afx_msg void OnAbout();
	afx_msg void OnExit();
	afx_msg void OnSelchangeComboUp();
	afx_msg void OnNote();
	afx_msg void OnOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYMMETRYDLG_H__0639AD06_80BA_4457_83F9_D067D452CAAA__INCLUDED_)
