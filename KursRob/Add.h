#pragma once


// CAdd dialog

class CAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CAdd)

public:
	CAdd(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdd();

// Dialog Data
	enum { IDD = IDD_ADD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int mID;
	CString mAuthor;
	CString mName;
	int mNumPage;
	CString mDateIss;
	CString mDateRet;
	CString mGanre;
};
