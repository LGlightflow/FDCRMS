// PropertyDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FDCRMS_UI.h"
#include "PropertyDlg.h"
#include "afxdialogex.h"
#include "fdcrms.h"

// PropertyDlg 对话框

IMPLEMENT_DYNAMIC(PropertyDlg, CDialogEx)

PropertyDlg::PropertyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

PropertyDlg::~PropertyDlg()
{
}

void PropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, DateCtrl);
	DDX_Control(pDX, IDC_COMBO_type, cb_type);
}


BEGIN_MESSAGE_MAP(PropertyDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &PropertyDlg::OnBnClickedOk)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &PropertyDlg::OnDtnDatetimechangeDatetimepicker1)
END_MESSAGE_MAP()


// PropertyDlg 消息处理程序


void PropertyDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	CTime CDate;
	DateCtrl.GetTime(CDate); //把控件填的时间输入到了CDate
	//int year = CDate.GetYear();
	//int month = CDate.GetMonth();
	//int day = CDate.GetDay();
	//syear.Format(_T("%d"),year);
	//smonth.Format(_T("%d"), month);
	//sday.Format(_T("%d"),day);	 
	
	//从编辑框取得值
	GetDlgItemText(IDC_EDIT_ID,sID);
	GetDlgItemText(IDC_EDIT_amount, samount);
	//GetDlgItemText(IDC_EDIT_type, stype);
	GetDlgItemText(IDC_COMBO_type,stype);
	GetDlgItemText(IDC_EDIT_method, smethod);
	GetDlgItemText(IDC_EDIT_site, ssite);
	GetDlgItemText(IDC_EDIT_detail, sdetail);

	/*数据域处理*/
	struct data Data;
	char rID[25], rtype[10], rmethod[10], rsite[10], rdetail[50];

	wchar_t *ptr;

	ptr = sID.GetBuffer(sID.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rID, sizeof(rID), NULL, NULL);

	float ramount = _tstof(samount);

	ptr = stype.GetBuffer(stype.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rtype, sizeof(rtype), NULL, NULL);

	ptr = smethod.GetBuffer(smethod.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rmethod, sizeof(rmethod), NULL, NULL);

	ptr = ssite.GetBuffer(ssite.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rsite, sizeof(rsite), NULL, NULL);

	ptr = sdetail.GetBuffer(sdetail.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rdetail, sizeof(rdetail), NULL, NULL);

	/*
	int ryear = _ttof(syear);
	int rmonth = _ttof(smonth);
	int rday = _ttof(sday);
	
	Data.date.year = ryear;
	Data.date.month = rmonth;
	Data.date.day = rday;
	*/
	Data.date.year = CDate.GetYear();
	Data.date.month = CDate.GetMonth();
	Data.date.day = CDate.GetDay();
	Data.amount = ramount;
	strcpy(Data.ID, rID);
	strcpy(Data.type, rtype);
	strcpy(Data.method, rmethod);
	strcpy(Data.site, rsite);
	strcpy(Data.detail, rdetail);
	/*数据域处理*/

	extern char path[250];
	struct Node *List = CreateList();
	ReadList(List,path);
	InsertNode(List,Data);
	WriteList(List,path);
	free(List);
	EndDialog(0);//正常退出窗口
}




BOOL PropertyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	cb_type.AddString(_T("食品"));
	cb_type.AddString(_T("日用品"));
	cb_type.AddString(_T("服装"));
	cb_type.AddString(_T("电器"));
	cb_type.AddString(_T("水电煤气"));
	cb_type.AddString(_T("房贷"));
	cb_type.AddString(_T("学费"));
	cb_type.AddString(_T("交通费"));
	cb_type.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void PropertyDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
