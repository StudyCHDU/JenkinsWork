
// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KursRob.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "afxdb.h"
#include "Add.h"
#include "Search.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDatabase db;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg dialog




CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mList);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CMainDlg::OnAdd)
	ON_COMMAND(ID_32772, &CMainDlg::OnUpdate)
	ON_COMMAND(ID_32773, &CMainDlg::OnDelete)
	ON_COMMAND(ID_32774, &CMainDlg::OnSearch)
	ON_COMMAND(ID_32775, &CMainDlg::OnFill)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CMainDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	CMainDlg::OpenBase();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMainDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMainDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainDlg::FillList(CString request)
{
	int n, i;
	mList.DeleteAllItems();
	n=mList.GetHeaderCtrl()->GetItemCount();
	for(i=n-1;i>-1;i--)
	{
		mList.DeleteColumn(i);
	}
	mList.SetTextColor(125);
	CRecordset rec(&db);
	rec.Open(CRecordset::snapshot, request);
	int count=rec.GetODBCFieldCount();
	CODBCFieldInfo info;
	for (i=0;i<count;i++)
	{
		rec.GetODBCFieldInfo(i,info);
		mList.InsertColumn(i,info.m_strName);
		switch(i) {
		case 0: mList.SetColumnWidth(i,25);
			break;
		case 1: mList.SetColumnWidth(i,90);
			break;
		case 2: mList.SetColumnWidth(i,90);
			break;
		case 3: mList.SetColumnWidth(i,130);
			break;
		case 4: mList.SetColumnWidth(i,40);
			break;
		case 5: mList.SetColumnWidth(i,80);
			break;
		case 6: mList.SetColumnWidth(i,80);
			break;
		default: mList.SetColumnWidth(i,80);
		}
	}

	//Выдиление всей строки
	DWORD ExStyle = mList.GetExtendedStyle();
	ExStyle |= LVS_EX_FULLROWSELECT;
	mList.SetExtendedStyle(ExStyle);
	mList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT|LVS_EX_INFOTIP|LVS_EX_GRIDLINES);

	CString buff;
	i = 0 ;
	IDnum = 0;
	while (!rec.IsEOF())
	{
		for (short j=0; j<count; j++)
		{ 
			rec.GetFieldValue(j,buff);
			if(j == 0) {
				mList.InsertItem(i, buff);
			}
			else {
				mList.SetItemText(i, j, buff);
			}
		}
		rec.MoveNext();	
		i++;
		IDnum = i;
   }
}

void CMainDlg::OpenBase() // открытие базы данных
{
	CFileDialog dlg(true,NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"MS Access File (.mdb)|*.mdb||");
	CString ConnStr;
	if(dlg.DoModal() == IDOK)
	{
		CString ConnStr;
		CString FilePath = dlg.GetPathName();
		ConnStr.Format(_T("ODBC;DRIVER={MICROSOFT ACCESS DRIVER (*.mdb)}; DSN=''; DBQ=%s"), FilePath);
		db.Open(NULL, FALSE, FALSE, ConnStr);
		CString strOpen = L"SELECT * FROM Books ORDER BY ID";
		FillList(strOpen);
	} else {
			db.Open(_T("MyBase"));
			CString strOpen = L"SELECT * FROM Books ORDER BY ID";
			FillList(strOpen);
		}
}

void CMainDlg::OnAdd()
{
	CAdd dlg;
	CString request;
	dlg.mID = IDnum + 1;
	if(dlg.DoModal() == IDOK) {
		request.Format(_T("Insert into Books values (%d, '%s', '%s', '%s', %d, '%s', '%s')"),dlg.mID, dlg.mGanre, dlg.mAuthor, dlg.mName, dlg.mNumPage, dlg.mDateIss, dlg.mDateRet); 
		db.ExecuteSQL(request);
		request = L"SELECT * FROM Books";
		FillList(request);	
	}
}


void CMainDlg::OnUpdate()
{
	POSITION poss = mList.GetFirstSelectedItemPosition();
	if(poss != NULL) {
		CAdd dlg;
		int nIndex = mList.GetNextSelectedItem(poss);
		dlg.mID = _ttoi(mList.GetItemText(nIndex, 0));
		dlg.mGanre = mList.GetItemText(nIndex, 1);
		dlg.mAuthor = mList.GetItemText(nIndex, 2);
		dlg.mName = mList.GetItemText(nIndex, 3);
		dlg.mNumPage = _ttoi(mList.GetItemText(nIndex, 4));
		dlg.mDateIss = mList.GetItemText(nIndex, 5);
		dlg.mDateRet = mList.GetItemText(nIndex, 6);
		if(dlg.DoModal() == IDOK) {
			CString query, str;
			int i;
			str = mList.GetItemText(nIndex, 0);
			i = _ttoi(str);
			query.Format(_T("UPDATE Books SET Ganre='%s', Author='%s', Name='%s', NumPage=%d, DateIss='%s', DateRet='%s' where ID = %d"), 
			dlg.mGanre, dlg.mAuthor, dlg.mName, dlg.mNumPage, dlg.mDateIss, dlg.mDateRet, i);
			db.ExecuteSQL(query);
			query = "SELECT * from Books";
			FillList(query);
		}
	} else
		MessageBox(_T("Выберите строку которую отредактировать."), _T("Сообщение"), MB_OK | MB_ICONINFORMATION);
}


void CMainDlg::OnDelete()
{
	POSITION poss = mList.GetFirstSelectedItemPosition();
	if(poss != NULL) {
	CString str;
	CString request;
	POSITION pos = mList.GetFirstSelectedItemPosition();
	int npos;
	while(pos)
	{
		npos = mList.GetNextSelectedItem(pos);	
		str = mList.GetItemText(npos,0);
		npos = _ttoi(str);
		request.Format(L"DELETE FROM Books WHERE ID = %d", npos);
		db.ExecuteSQL(request);
		request = "select * from Books";
		FillList(request);
	}
	} else
		MessageBox(_T("Выберите строку которую хотите удалить."), _T("Сообщение"), MB_OK | MB_ICONINFORMATION);
}


void CMainDlg::OnSearch()
{
	CSearch dlg;
	CString str, query;
	int choose;
	if(dlg.DoModal() == IDOK) {
		str = dlg.mSearch;
		choose = dlg.mChoose;
		switch(choose) {
		case 0:
			query = _T("SELECT * FROM Books WHERE Ganre LIKE '%")+ str + _T("%';");
			FillList(query);
			break;
		case 1:
			query = _T("SELECT * FROM Books WHERE Author LIKE '%")+ str + _T("%';");
			FillList(query);
			break;
		case 2:
			query = _T("SELECT * FROM Books WHERE Name LIKE '%")+ str + _T("%';");
			FillList(query);
			break;
		case 3:
			query = _T("SELECT * FROM Books WHERE DateIss LIKE '%")+ str + _T("%';");
			FillList(query);
			break;
		case 4:
			query = _T("SELECT * FROM Books WHERE DateRet LIKE '%")+ str + _T("%';");
			FillList(query);
			break;
		}
	}
}


void CMainDlg::OnFill()
{
	CString query;
	query = _T("SELECT * FROM Books ORDER BY ID;");
	FillList(query);
}


void CMainDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	POSITION poss = mList.GetFirstSelectedItemPosition();
	if(poss != NULL) {
		CAdd dlg;
		int nIndex = mList.GetNextSelectedItem(poss);
		dlg.mID = _ttoi(mList.GetItemText(nIndex, 0));
		dlg.mGanre = mList.GetItemText(nIndex, 1);
		dlg.mAuthor = mList.GetItemText(nIndex, 2);
		dlg.mName = mList.GetItemText(nIndex, 3);
		dlg.mNumPage = _ttoi(mList.GetItemText(nIndex, 4));
		dlg.mDateIss = mList.GetItemText(nIndex, 5);
		dlg.mDateRet = mList.GetItemText(nIndex, 6);
		if(dlg.DoModal() == IDOK) {
			CString query, str;
			int i;
			str = mList.GetItemText(nIndex, 0);
			i = _ttoi(str);
			query.Format(_T("UPDATE Books SET Ganre='%s', Author='%s', Name='%s', NumPage=%d, DateIss='%s', DateRet='%s' where ID = %d"), 
			dlg.mGanre, dlg.mAuthor, dlg.mName, dlg.mNumPage, dlg.mDateIss, dlg.mDateRet, i);
			db.ExecuteSQL(query);
			query = "SELECT * from Books";
			FillList(query);
		}
	} else
		MessageBox(_T("Выберите строку которую отредактировать."), _T("Сообщение"), MB_OK | MB_ICONINFORMATION);

	*pResult = 0;
}