#pragma once


// MainMenuDlg 对话框

class MainMenuDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MainMenuDlg)

public:
	MainMenuDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainMenuDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	// 显示数据的列表
	CListCtrl MainList;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	// 输出主菜单的列表数据
	int PrintMainList();
	afx_msg void OnBnClickedButtonflash();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
};
