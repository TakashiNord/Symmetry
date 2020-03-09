; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAboutDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Symmetry.h"

ClassCount=4
Class1=CSymmetryApp
Class2=CSymmetryDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_SYMMETRY_DIALOG
Class4=Symalgo
Resource4=IDR_MENU1

[CLS:CSymmetryApp]
Type=0
HeaderFile=Symmetry.h
ImplementationFile=Symmetry.cpp
Filter=N
LastObject=CSymmetryApp

[CLS:CSymmetryDlg]
Type=0
HeaderFile=SymmetryDlg.h
ImplementationFile=SymmetryDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=MY_EXIT

[CLS:CAboutDlg]
Type=0
HeaderFile=SymmetryDlg.h
ImplementationFile=SymmetryDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=13
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342177294
Control9=IDC_STATIC,static,1342177283
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342177294
Control13=IDC_STATIC,static,1342177294

[DLG:IDD_SYMMETRY_DIALOG]
Type=1
Class=CSymmetryDlg
ControlCount=22
Control1=IDCANCEL,button,1342242816
Control2=IDFILEOPEN,button,1342242817
Control3=IDRUN,button,1342242816
Control4=IDC_STATIC,static,1342177280
Control5=IDC_STATIC,static,1342177280
Control6=IDDIR,edit,1350633600
Control7=IDC_STATIC,static,1342177280
Control8=IDC_STATIC,button,1342308359
Control9=IDBYX,button,1342242825
Control10=IDBYY,button,1342177289
Control11=IDBYXY,button,1342177289
Control12=IDC_STATIC,static,1342177294
Control13=IDFILE,combobox,1344339970
Control14=IDC_STATIC,button,1342210567
Control15=IDC_STATIC,static,1342177294
Control16=IDC_STATIC,static,1342177280
Control17=IDC_STATIC,static,1342179342
Control18=IDC_STATIC,static,1342177280
Control19=IDC_STATIC,static,1342177280
Control20=IDC_STATIC,static,1342177280
Control21=IDC_STATIC,static,1342308352
Control22=IDC_COMBO_UP,combobox,1344339971

[MNU:IDR_MENU1]
Type=1
Class=CSymmetryDlg
Command1=IDOPEN
Command2=IDNOTE
Command3=MY_EXIT
Command4=IDALGO
Command5=MY_ABOUT
CommandCount=5

[CLS:Symalgo]
Type=0
HeaderFile=Symalgo.h
ImplementationFile=Symalgo.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDALGO

