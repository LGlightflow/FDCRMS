#pragma once


// SortDlg 对话框

class SortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SortDlg)

public:
	SortDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SortDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	// 升序单选按钮
	CButton ASort;
	// 降序单选按钮
	CButton DSort;
	// 按照消费日期排序单选按钮
	CButton DateSort;
	// 按照消费金额排序单选按钮
	CButton AmountSort;
	afx_msg void OnBnClickedRadio2();
	// 排序对话框左边分组
	int Sort_lgroup;
	// 排序对话框右边分组
	int Sort_rgroup;
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedOk();
};
