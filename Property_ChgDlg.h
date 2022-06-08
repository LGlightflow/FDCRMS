#pragma once


// Property_ChgDlg 对话框

class Property_ChgDlg : public CDialogEx
{
	DECLARE_DYNAMIC(Property_ChgDlg)

public:
	Property_ChgDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Property_ChgDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox cb_type;
	afx_msg void OnBnClickedOk();
	CDateTimeCtrl DateCtrl;
	CString /*syear, smonth, sday,*/ sID, samount, stype, smethod, ssite, sdetail; //创建对象获取数据
	int syear, smonth, sday;
	afx_msg void OnBnClicked2();
	int flag = 0;//0表示没有获取到改变后的数据(取消键)，1表示获取成功成功，回传给父窗口
};
