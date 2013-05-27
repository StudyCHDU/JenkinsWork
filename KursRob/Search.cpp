// Search.cpp : implementation file
//

#include "stdafx.h"
#include "KursRob.h"
#include "Search.h"
#include "afxdialogex.h"


// CSearch dialog

IMPLEMENT_DYNAMIC(CSearch, CDialogEx)

CSearch::CSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearch::IDD, pParent)
	, mSearch(_T(""))
	, mChoose(0)
{

}

CSearch::~CSearch()
{
}

void CSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mSearch);
	DDX_Radio(pDX, IDC_RADIO1, mChoose);
}


BEGIN_MESSAGE_MAP(CSearch, CDialogEx)
END_MESSAGE_MAP()


// CSearch message handlers
