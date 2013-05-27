// Add.cpp : implementation file
//

#include "stdafx.h"
#include "KursRob.h"
#include "Add.h"
#include "afxdialogex.h"
#include "MainDlg.h"


// CAdd dialog

IMPLEMENT_DYNAMIC(CAdd, CDialogEx)

CAdd::CAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAdd::IDD, pParent)
	, mID(0)
	, mGanre(_T("Жанр литературы"))
	, mAuthor(_T("ФИО автора"))
	, mName(_T("Название книги"))
	, mNumPage(0)
	, mDateIss(_T("mm/dd/yyyy"))
	, mDateRet(_T("mm/dd/yyyy"))
{
}

CAdd::~CAdd()
{
}

void CAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mID);
	DDX_Text(pDX, IDC_EDIT6, mAuthor);
	DDX_Text(pDX, IDC_EDIT2, mName);
	DDX_Text(pDX, IDC_EDIT4, mNumPage);
	DDX_Text(pDX, IDC_EDIT3, mDateIss);
	DDX_Text(pDX, IDC_EDIT5, mDateRet);
	DDX_Text(pDX, IDC_EDIT7, mGanre);
}


BEGIN_MESSAGE_MAP(CAdd, CDialogEx)
END_MESSAGE_MAP()


// CAdd message handlers
