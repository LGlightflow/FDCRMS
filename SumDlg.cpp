// SumDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FDCRMS_UI.h"
#include "SumDlg.h"
#include "afxdialogex.h"
#include "fdcrms.h"

// SumDlg 对话框

IMPLEMENT_DYNAMIC(SumDlg, CDialogEx)

SumDlg::SumDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

SumDlg::~SumDlg()
{
}

void SumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_type2, cb_type);
	DDX_Control(pDX, IDC_EDIT_ID, edit_ID);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, DateCtrl_start);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, DateCtrl_end);
}


BEGIN_MESSAGE_MAP(SumDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &SumDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &SumDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDOK, &SumDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SumDlg 消息处理程序


BOOL SumDlg::OnInitDialog()
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


void SumDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	cb_type.EnableWindow(FALSE);
	edit_ID.EnableWindow(TRUE);
	
}


void SumDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	edit_ID.EnableWindow(FALSE);
	cb_type.EnableWindow(TRUE);
}


void SumDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	float sum = 0; long long date_s, date_e,date_Node;
	
	CString Csum,Printsum;
	extern char path[250];
	struct Node *List = CreateList();
	List = ReadList(List, path);
	struct Node *PtMove = List->next;

	CTime CDate_start, CDate_end;
	DateCtrl_start.GetTime(CDate_start);
	DateCtrl_end.GetTime(CDate_end);
	date_s = CDate_start.GetYear()*10000+CDate_start.GetMonth()*100+CDate_start.GetDay();
	date_e = CDate_end.GetYear() * 10000 + CDate_end.GetMonth() * 100 + CDate_end.GetDay();


	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck()) { //选中家庭成员

		char SumID[25];
		wchar_t *ptr;
		CString CsumID;
		GetDlgItemText(IDC_COMBO_type2, CsumID);
		ptr = CsumID.GetBuffer(CsumID.GetLength() * sizeof(wchar_t));
		WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, SumID, sizeof(SumID), NULL, NULL);
		while (PtMove != NULL){
			date_Node = PtMove->data.date.day + PtMove->data.date.month * 100 + PtMove->data.date.year * 10000;
			if (date_Node >= date_s && date_Node <= date_e && strcmp(SumID, PtMove->data.ID) == 0) {
				sum = sum + PtMove->data.amount;
			}
			PtMove = PtMove->next;
		}

	}else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck()) {//选中消费品类

		char SumType[10];
		wchar_t *ptr;
		CString Csumtype;
		GetDlgItemText(IDC_COMBO_type2, Csumtype);
		ptr = Csumtype.GetBuffer(Csumtype.GetLength() * sizeof(wchar_t));
		WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1,SumType ,sizeof(SumType), NULL, NULL);
		while (PtMove != NULL){
			date_Node = PtMove->data.date.day + PtMove->data.date.month * 100 + PtMove->data.date.year * 10000;
			if (date_Node >= date_s && date_Node <= date_e && strcmp(SumType, PtMove->data.type) == 0) {
				sum = sum + PtMove->data.amount;
			}
			PtMove = PtMove->next;
		}
	}
	else {
		while (PtMove != NULL) {
			date_Node = PtMove->data.date.day + PtMove->data.date.month * 100 + PtMove->data.date.year * 10000;
			if (date_Node >= date_s && date_Node <= date_e) {
				sum = sum + PtMove->data.amount;
			}
			PtMove = PtMove->next;
		} 
	}
	FreeList(List);
	Printsum.Format(_T("所统计的总金额为%.2f元"),sum);
	MessageBox(Printsum);
	EndDialog(0);//正常退出窗口
}

