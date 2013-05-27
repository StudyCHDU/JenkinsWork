
// MainDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CMainDlg dialog
class CMainDlg : public CDialogEx
{
// Construction
public:
	CMainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_KURSROB_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void FillList(CString zapros);
	void OpenBase();
	CListCtrl mList;
	int IDnum;
	afx_msg void OnAdd();
	afx_msg void OnUpdate();
	afx_msg void OnDelete();
	afx_msg void OnSearch();
	afx_msg void OnFill();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
