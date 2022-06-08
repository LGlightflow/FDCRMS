#pragma once
//#include <stdio.h>

// ChangeDlg 对话框

class ChangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChangeDlg)

public:
	ChangeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ChangeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl DateCtrl;
	CEdit edit_ID;
	CComboBox cb_type;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString stype, sID;
};
