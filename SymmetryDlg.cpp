// SymmetryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Symmetry.h"
#include "SymmetryDlg.h"
//////////////////////////
#include "Tsym.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSymmetryDlg dialog

CSymmetryDlg::CSymmetryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSymmetryDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSymmetryDlg)
	m_dir_name = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSymmetryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSymmetryDlg)
	DDX_Text(pDX, IDDIR, m_dir_name);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSymmetryDlg, CDialog)
	//{{AFX_MSG_MAP(CSymmetryDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDFILEOPEN, OnFileOpen)
	ON_BN_CLICKED(IDRUN, OnRun)
	ON_COMMAND(MY_ABOUT, OnAbout)
	ON_COMMAND(MY_EXIT, OnExit)
	ON_CBN_SELCHANGE(IDC_COMBO_UP, OnSelchangeComboUp)
	ON_COMMAND(IDNOTE, OnNote)
	ON_COMMAND(IDOPEN, OnOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSymmetryDlg message handlers

BOOL CSymmetryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//Установка текущей папки и заполнение бокса с файлами...
	LPTSTR lpszCurDir;
	CComboBox *cbptr;
	TCHAR tchBuffer[MAX_PATH];
	CEdit *ebptr;
	char csCurDir[300]; csCurDir[0]='\0';

	lpszCurDir=tchBuffer;
	::GetCurrentDirectory(MAX_PATH, lpszCurDir);

	strcpy(csCurDir,lpszCurDir);
	strcat(csCurDir,"\\*.*");

	DlgDirListComboBox((LPTSTR)csCurDir,IDFILE,0,DDL_READWRITE|DDL_READONLY|DDL_ARCHIVE);

	ebptr=(CEdit *)GetDlgItem(IDDIR);
	ebptr->SetWindowText(lpszCurDir);

	//Установка переключателя
	//CButton *bbptr=(CButton *)GetDlgItem(IDBYX);
	//bbptr->SetCheck(1);

	//Заполнение Фильтра
	cbptr=(CComboBox *)GetDlgItem(IDC_COMBO_UP);
	cbptr->InsertString( 0, "*.*" );
	cbptr->InsertString( 1, "*.up" );
	cbptr->InsertString( 2, "*.upa" );
	cbptr->InsertString( 3, "*.dat" );
	cbptr->InsertString( 4, "*.ptp" );
	cbptr->InsertString( 5, "*.txt" );
	cbptr->SetTopIndex(0);
	//int nIndex = cbptr->SelectString(0, "*.*");
        //ASSERT(nIndex != CB_ERR);

	//UpdateData(TRUE);
	UpdateWindow();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSymmetryDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSymmetryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSymmetryDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


//
void CSymmetryDlg::OnAbout()
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


//
void CSymmetryDlg::OnNote()
{
	// TODO: Add your command handler code here
   int cTxtlen ;
   PSTR pszMem ;

   int i ;
   char info[500];
   char szDirName[255];
   char szFileNameIn[350];

   CEdit *ebptr=(CEdit *)GetDlgItem(IDDIR);
   CComboBox *cbptr=(CComboBox *)GetDlgItem(IDFILE);

   /*====================================================================================*/
   // Получение имени файла+расширение
   cTxtlen=GetWindowTextLength();
   pszMem=(PSTR) VirtualAlloc((LPVOID)NULL,(DWORD)(cTxtlen+1),MEM_COMMIT,PAGE_READWRITE);
   cbptr->GetWindowText(pszMem,cTxtlen+1);

   // Получение папки
   szDirName[0]='\0';
   ebptr->GetLine(-1,szDirName);
   //strcpy(szDirName,m_dir_name);
   //AfxMessageBox(szDirName);

   // Получение папки+файла+расширение
   szFileNameIn[0]='\0';
   strcpy(szFileNameIn,szDirName);
   strcat(szFileNameIn,"\\");
   strcat(szFileNameIn,pszMem);
   //AfxMessageBox(szFileNameIn);

   info[0]='\0';
   strcpy(info,"notepad \"");
   strcat(info,szFileNameIn);
   strcat(info,"\"");
   i=WinExec(info,SW_SHOW);
   if (i < 32) AfxMessageBox((LPCTSTR)"WinExec failed",MB_OK|MB_ICONSTOP,0);

   VirtualFree(pszMem,0,MEM_RELEASE);

  return ;
}

//
void CSymmetryDlg::OnOpen()
{
	// TODO: Add your command handler code here
	CSymmetryDlg::OnFileOpen();
}
//
void CSymmetryDlg::OnExit()
{
	// TODO: Add your command handler code here
	CDialog::OnCancel();
}


//
void CSymmetryDlg::OnOK()
{
	// TODO: Add extra validation here
}


//
void CSymmetryDlg::OnSelchangeComboUp()
{
	// TODO: Add your control notification handler code here

	int i ;
	CComboBox *cbptr;
	CEdit *ebptr;
	//LPTSTR lpszCurDir;
	//TCHAR tchCurDir[MAX_PATH];
	char strCurDir[255]; strCurDir[0]='\0';
	char csCurDir[300]; csCurDir[0]='\0';

	ebptr=(CEdit *)GetDlgItem(IDDIR);

	//lpszCurDir=tchCurDir;
	ebptr->GetLine(-1,strCurDir);

	strcpy(csCurDir,strCurDir);
	//AfxMessageBox(csCurDir);

	cbptr=(CComboBox *)GetDlgItem(IDC_COMBO_UP);
	i=cbptr->GetCurSel() ;

	switch (i) {
	  case 1 : strcat(csCurDir,"\\*.up");
	  break;
	  case 2 : strcat(csCurDir,"\\*.upa");
	  break;
	  case 3 : strcat(csCurDir,"\\*.dat");
	  break;
	  case 4 : strcat(csCurDir,"\\*.ptp");
	  break;
	  case 5 : strcat(csCurDir,"\\*.txt");
	  break;
	  default : strcat(csCurDir,"\\*.*");
	  break;
	}

        // Delete all the items from the combo box.
        cbptr=(CComboBox *)GetDlgItem(IDFILE);
        cbptr->ResetContent();
        cbptr->Dir(DDL_READWRITE|DDL_READONLY|DDL_ARCHIVE,_T(csCurDir));
        DlgDirListComboBox((LPTSTR)csCurDir,IDFILE,0,DDL_READWRITE|DDL_READONLY|DDL_ARCHIVE);

}


//
void CSymmetryDlg::OnFileOpen()
{
   // TODO: Add your control notification handler code here
   int result;
   char szFileName[255]; szFileName[0]='\0';
   char strCurDir[300]; strCurDir[0]='\0';
   char *ptr;
   CEdit *ebptr;
   CComboBox *cbptr;

   cbptr=(CComboBox *)GetDlgItem(IDFILE);
   ebptr=(CEdit *)GetDlgItem(IDDIR);
   ebptr->GetLine(-1,strCurDir);

   //LPTSTR lpszCurDir;
   //::GetCurrentDirectory(MAX_PATH, lpszCurDir);

    /*Создание и Открытие диалогового окна OPEN FILE*/
    CFileDialog mFileOpen(TRUE);
    mFileOpen.m_ofn.lpstrFilter=(LPSTR)"Up файлы (*.up)\0*.up\0Upa файлы (*.upa)\0*.upa\0Dat файлы (*.dat)\0*.dat\0Ptp файлы (*.ptp)\0*.ptp\0Txt файлы (*.txt)\0*.txt\0Все файлы (*.*)\0*.*\0";
    mFileOpen.m_ofn.Flags= OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
    mFileOpen.m_ofn.lpstrInitialDir=(LPTSTR)strCurDir;
    result= mFileOpen.DoModal();

    if (result==IDCANCEL) { MessageBeep(0); return ; }

    /*получение имени файла с расширением (title.ext)*/
    m_file_ext=mFileOpen.GetFileName();
    /*получение имени файла и отдельно расширение (title).(ext)*/
    m_file=mFileOpen.GetFileTitle();
    m_ext=mFileOpen.GetFileExt();
    /*получение  [путь+файл] */
    m_dir_file_ext=mFileOpen.GetPathName();
    /*выделение [пути] из [путь+файл]*/

    /*m_dir=mFileOpen.GetFolderPath(); strcpy(strCurDir,m_dir); */
    //AfxMessageBox(m_dir);

    ptr=strrchr(m_dir_file_ext,'\\');
    strCurDir[0]='\0';
    if (ptr) {
      strncpy(strCurDir,m_dir_file_ext,ptr-m_dir_file_ext);
      strCurDir[ptr-m_dir_file_ext]='\0';
     }

    /*
    SetCurrentDirectory(strCurDir);
    lpszCurDir=tchBuffer;
    ::GetCurrentDirectory(MAX_PATH,lpszCurDir);
    */

    ebptr->SetWindowText(strCurDir);

    strcat(strCurDir,"\\*.");
    strcat(strCurDir,m_ext);

    //AfxMessageBox(strCurDir);

    cbptr->ResetContent();
    cbptr->Dir(DDL_READWRITE|DDL_READONLY|DDL_ARCHIVE,_T(strCurDir));
    DlgDirListComboBox((LPTSTR)strCurDir,IDFILE,0,DDL_READWRITE|DDL_READONLY|DDL_ARCHIVE);

    strcpy(szFileName,m_file_ext);
    cbptr->SetWindowText((LPTSTR)szFileName);

}

//
void CSymmetryDlg::OnRun()
{
   // TODO: Add your control notification handler code here
   long int nKadrs ;
   char info[500];
   int i_xy;
   FILE *ff;
   int cTxtlen ;
   PSTR pszMem ;
   char *ptr;
   char szDirName[255];
   char szFileNameIn[350], szFileNameOut[350];
   char szFileName[81], str_ext[4], szExt[25];
   int iRun;

   CEdit *ebptr=(CEdit *)GetDlgItem(IDDIR);
   CComboBox *cbptr=(CComboBox *)GetDlgItem(IDFILE);
   CButton *bbptr;

   /**/
   iRun=UpdateData(TRUE);
   if (iRun==0) return;

   i_xy=-1; str_ext[0]='\0';

   bbptr=(CButton *)GetDlgItem(IDBYX);
   iRun=bbptr->GetCheck();
   if (iRun==1) { i_xy=1; strcpy(str_ext,"_x"); }

   bbptr=(CButton *)GetDlgItem(IDBYY);
   iRun=bbptr->GetCheck();
   if (iRun==1) { i_xy=2; strcpy(str_ext,"_y"); }

   bbptr=(CButton *)GetDlgItem(IDBYXY);
   iRun=bbptr->GetCheck();
   if (iRun==1) { i_xy=3; strcpy(str_ext,"_xy"); }

   if (i_xy==-1)
   {
      AfxMessageBox("Выберите соответствующее отображение",MB_OK|MB_ICONEXCLAMATION, 0 );
      return ;
   };

   /*====================================================================================*/
   // Получение имени файла+расширение
   cTxtlen=GetWindowTextLength();
   pszMem=(PSTR) VirtualAlloc((LPVOID)NULL,(DWORD)(cTxtlen+1),MEM_COMMIT,PAGE_READWRITE);
   cbptr->GetWindowText(pszMem,cTxtlen+1);

   // Получение папки
   szDirName[0]='\0';
   strcpy(szDirName,m_dir_name);
   //AfxMessageBox(szDirName);

   // Получение папки+файла+расширение
   szFileNameIn[0]='\0';
   strcpy(szFileNameIn,szDirName);
   strcat(szFileNameIn,"\\");
   strcat(szFileNameIn,pszMem);
   //AfxMessageBox(szFileNameIn);

   /*====================================================================================*/

   // Проверка на существование исх. файла
   ff=fopen(szFileNameIn,"r");
   if (ff==NULL) {
 	 info[0]='\0';
 	 sprintf(info,"Файл Данных:=\n %s \n\t не найден !\n преобразование прервано....",szFileNameIn);
 	 AfxMessageBox((LPCTSTR)info,MB_OK|MB_ICONSTOP,0);
 	 return ;
   }
   fclose(ff);

   // Формирование имени файла
   szExt[0]='\0';
   strcpy(szExt,".up");
   szFileName[0]='\0';
   ptr=strrchr(pszMem,'.');
   if (ptr) {
 	  strncpy(szFileName,pszMem,ptr-pszMem);
 	  szFileName[ptr-pszMem]='\0';
 	  szExt[0]='\0';
 	  strcpy(szExt,ptr);
    }
   //AfxMessageBox(ptr);
   szFileNameOut[0]='\0';
   strcpy(szFileNameOut,szDirName);
   strcat(szFileNameOut,"\\");
   strcat(szFileNameOut,szFileName);
   strcat(szFileNameOut,str_ext);
   strcat(szFileNameOut,szExt);
   //AfxMessageBox(szFileNameOut);

   // Проверка на существование исх. файла
   ff=fopen(szFileNameOut,"r");
   if (ff!=NULL) {
 	 fclose(ff);
         info[0]='\0';
 	 sprintf(info,"Файл:=\n %s \n\t уже существует! \n Перезаписать существующий ?",szFileNameOut);
 	 iRun=AfxMessageBox((LPCTSTR)info,MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1,0);
         if (iRun==IDNO) {
         	VirtualFree(pszMem,0,MEM_RELEASE);
         	return ;
          }
    }

   /*Основной алгоритм*/
   Tsym tc;
   nKadrs=tc.main(szFileNameIn,szFileNameOut,i_xy);

   switch (nKadrs)
   {
     case -1 :
       MessageBeep(0);
       info[0]='\0';
       sprintf(info,"Невозможно открыть файл:\n %s \n на 'чтение' \n",szFileNameIn );
       AfxMessageBox((LPCTSTR)info,MB_OK|MB_ICONSTOP,0);
     break ;
     case -2 :
       MessageBeep(0);
       info[0]='\0';
       sprintf(info,"Невозможно записать файл:\n %s \n Проверьте права доступа или ошибка системы",szFileNameOut );
       AfxMessageBox((LPCTSTR)info,MB_OK|MB_ICONSTOP,0);
     break ;
     case -3 :
       MessageBeep(0);
       info[0]='\0';
       sprintf(info,"Проверьте передаваемые параметры:\n %s \n %s \n %d",szFileNameIn,szFileNameOut,i_xy );
       AfxMessageBox((LPCTSTR)info,MB_OK|MB_ICONSTOP,0);
     break ;
     default :
       info[0]='\0';
       sprintf(info,"Файл:=\n %s \n\t записан на диск \n Преобразование завершено...\n Число преобразованных адресов =%ld",szFileNameOut,nKadrs);
       AfxMessageBox((LPCTSTR)info,MB_OK|MB_ICONINFORMATION,0);
     break;
   }

   //Обновление результатов
//   cbptr->ResetContent();
//   cbptr->Dir(DDL_READWRITE|DDL_READONLY|DDL_ARCHIVE,_T("*.*"));
//   DlgDirListComboBox((LPTSTR)csCurDir,IDFILE,0,DDL_READWRITE|DDL_READONLY|DDL_ARCHIVE);

   cbptr->SelectString(0,pszMem);

   VirtualFree(pszMem,0,MEM_RELEASE);

   return ;
}

/////////////////////////////////////////////////////////////////////////////

