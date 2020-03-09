// Symmetry.h : main header file for the SYMMETRY application
//

#if !defined(AFX_SYMMETRY_H__F6B5B79A_D35E_4289_A17B_0C6CC3FE305F__INCLUDED_)
#define AFX_SYMMETRY_H__F6B5B79A_D35E_4289_A17B_0C6CC3FE305F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSymmetryApp:
// See Symmetry.cpp for the implementation of this class
//

class CSymmetryApp : public CWinApp
{
public:
	CSymmetryApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSymmetryApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSymmetryApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYMMETRY_H__F6B5B79A_D35E_4289_A17B_0C6CC3FE305F__INCLUDED_)
