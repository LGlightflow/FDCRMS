#pragma once


// PropertyDlg 属性对话框

class PropertyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(PropertyDlg)

public:
	PropertyDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PropertyDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	//CComboBox combo_year;
	//CComboBox combo_month;
public:
	//CComboBox combo_day;
	//afx_msg void OnCbnSelchangeCombo1year();
	virtual BOOL OnInitDialog();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	CString syear,smonth,sday, sID, samount, stype, smethod, ssite, sdetail; //创建对象获取数据
	CDateTimeCtrl DateCtrl;
	// 消费品类下拉框
	CComboBox cb_type;
};
