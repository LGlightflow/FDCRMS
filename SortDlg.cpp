// SortDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FDCRMS_UI.h"
#include "SortDlg.h"
#include "afxdialogex.h"
#include "fdcrms.h"

// SortDlg 对话框

IMPLEMENT_DYNAMIC(SortDlg, CDialogEx)

SortDlg::SortDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, Sort_lgroup(0)
	, Sort_rgroup(0)
{

}

SortDlg::~SortDlg()
{
}

void SortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO3, ASort);
	DDX_Control(pDX, IDC_RADIO4, DSort);
	DDX_Control(pDX, IDC_RADIO1, DateSort);
	DDX_Control(pDX, IDC_RADIO2, AmountSort);
	DDX_Radio(pDX, IDC_RADIO1, Sort_lgroup);
	DDX_Radio(pDX, IDC_RADIO3, Sort_rgroup);
}


BEGIN_MESSAGE_MAP(SortDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &SortDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &SortDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &SortDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &SortDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO3, &SortDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDOK, &SortDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SortDlg 消息处理程序


void SortDlg::OnBnClickedRadio1() //按照消费时间排序
{
	UpdateData(TRUE);//更新界面值到变量中
	ASort.EnableWindow(TRUE);
	DSort.EnableWindow(TRUE);
	
	// TODO: 在此添加控件通知处理程序代码
}


void SortDlg::OnBnClickedRadio2()//按照消费金额排序
{	
	UpdateData(TRUE);
	ASort.EnableWindow(TRUE);
	DSort.EnableWindow(TRUE);
	// TODO: 在此添加控件通知处理程序代码
}


void SortDlg::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
}


void SortDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	extern char path[250];
	struct Node *List = CreateList();
	List = ReadList(List, path);
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() && ((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck()) {//选中消费日期 升序
		List = SortList_Date(List);
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() && ((CButton *)GetDlgItem(IDC_RADIO4))->GetCheck()) {//选中消费日期 降序
		List = SortList_Date(List);
		List = ReverseList(List);
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() && ((CButton *)GetDlgItem(IDC_RADIO3))->GetCheck()) {//选中消费金额 升序
		List = SortList_Amount(List);
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck() && ((CButton *)GetDlgItem(IDC_RADIO4))->GetCheck()) {//消费金额 降序
		List = SortList_Amount(List);
		List = ReverseList(List);
	}
	WriteList(List,path);
	free(List);
	EndDialog(0);
}
