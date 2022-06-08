#pragma once
#include "fdcrms.h"

// SearchDlg 对话框

class SearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SearchDlg)

public:
	SearchDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SearchDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox cb_type;
	afx_msg void OnBnClickedRadio1();
	CDateTimeCtrl DateCtrl_s;
	CDateTimeCtrl DateCtrl_e;
	CEdit edit_amount;
	CEdit edit_ID;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
