// Property_ChgDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FDCRMS_UI.h"
#include "Property_ChgDlg.h"
#include "afxdialogex.h"
#include "fdcrms.h"

// Property_ChgDlg 对话框

IMPLEMENT_DYNAMIC(Property_ChgDlg, CDialogEx)

Property_ChgDlg::Property_ChgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{

}

Property_ChgDlg::~Property_ChgDlg()
{
}

void Property_ChgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, DateCtrl);
	DDX_Control(pDX, IDC_COMBO_type, cb_type);
}


BEGIN_MESSAGE_MAP(Property_ChgDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &Property_ChgDlg::OnBnClickedOk)
	
	ON_BN_CLICKED(2, &Property_ChgDlg::OnBnClicked2)
END_MESSAGE_MAP()


// Property_ChgDlg 消息处理程序


BOOL Property_ChgDlg::OnInitDialog()
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


void Property_ChgDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	//CDialogEx::OnOK();
	
	CTime CDate;
	DateCtrl.GetTime(CDate); //把控件填的时间输入到了CDate
	GetDlgItemText(IDC_EDIT_ID, sID);
	GetDlgItemText(IDC_EDIT_amount, samount);
	GetDlgItemText(IDC_COMBO_type, stype);
	GetDlgItemText(IDC_EDIT_method, smethod);
	GetDlgItemText(IDC_EDIT_site, ssite);
	GetDlgItemText(IDC_EDIT_detail, sdetail);
	
	syear = CDate.GetYear();
	smonth = CDate.GetMonth();
	sday = CDate.GetDay();
	flag = 1;

	EndDialog(0);//正常退出窗口
	
}


void Property_ChgDlg::OnBnClicked2()
{	
	flag = 0;
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}
