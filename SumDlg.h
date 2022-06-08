#pragma once


// SumDlg 对话框

class SumDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SumDlg)

public:
	SumDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SumDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox cb_type;
	afx_msg void OnBnClickedRadio1();
	CEdit edit_ID;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedOk();
	CDateTimeCtrl DateCtrl_start;
	CDateTimeCtrl DateCtrl_end;
};
