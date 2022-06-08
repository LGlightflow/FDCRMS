// ChangeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FDCRMS_UI.h"
#include "ChangeDlg.h"
#include "afxdialogex.h"
#include "fdcrms.h"
#include "Property_ChgDlg.h"
// ChangeDlg 对话框

IMPLEMENT_DYNAMIC(ChangeDlg, CDialogEx)

ChangeDlg::ChangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{

}

ChangeDlg::~ChangeDlg()
{
}

void ChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, DateCtrl);
	DDX_Control(pDX, IDC_EDIT_ID, edit_ID);
	DDX_Control(pDX, IDC_COMBO_type2, cb_type);
}


BEGIN_MESSAGE_MAP(ChangeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChangeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ChangeDlg 消息处理程序


BOOL ChangeDlg::OnInitDialog()
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


void ChangeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CTime CDate;
	DateCtrl.GetTime(CDate);
	int rdate = CDate.GetYear() * 10000 + CDate.GetMonth() * 100 + CDate.GetDay();
	
	GetDlgItemText(IDC_COMBO_type2, stype);
	GetDlgItemText(IDC_EDIT_ID, sID);
	char rtype[10], rID[25];
	wchar_t *ptr;
	ptr = stype.GetBuffer(stype.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rtype, sizeof(rtype), NULL, NULL);
	ptr = sID.GetBuffer(sID.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rID, sizeof(rID), NULL, NULL);

	extern char path[250];
	struct Node *List = CreateList();
	List = ReadList(List, path);
	struct Node* PtMove = List->next;
	PtMove = List->next;
	struct Node* PtMove_pre = List;

	while (PtMove!=NULL){ //查找需要修改的数据
		int date_Node = PtMove->data.date.day + PtMove->data.date.month * 100 + PtMove->data.date.year * 10000;
		if (date_Node = rdate  && strcmp(PtMove->data.type, rtype) == 0 && strcmp(PtMove->data.ID, rID) == 0){
			break;
		}
		PtMove = PtMove->next;
		PtMove_pre = PtMove_pre->next;
	}

	if (PtMove == NULL) {
		MessageBox(_T("没有找到相关的数据！"));
		return;
	}

	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck()) {//选中修改按钮
		Property_ChgDlg dlg;
		dlg.DoModal();

		if (PtMove != NULL&&dlg.flag==1) {
			wchar_t *ptr;

			if (!dlg.sID.IsEmpty()) {
				ptr = dlg.sID.GetBuffer(dlg.sID.GetLength() * sizeof(wchar_t));
				WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, PtMove->data.ID, sizeof(PtMove->data.ID), NULL, NULL);
			}

			if (!dlg.samount.IsEmpty()) {
				PtMove->data.amount = _tstof(dlg.samount);
			}

			if (!dlg.stype.IsEmpty()) {
				ptr = stype.GetBuffer(dlg.stype.GetLength() * sizeof(wchar_t));
				WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, PtMove->data.type, sizeof(PtMove->data.type), NULL, NULL);
			}

			if (!dlg.smethod.IsEmpty()) {
				ptr = dlg.smethod.GetBuffer(dlg.smethod.GetLength() * sizeof(wchar_t));
				WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, PtMove->data.method, sizeof(PtMove->data.method), NULL, NULL);
			}

			if (!dlg.ssite.IsEmpty()) {
				ptr = dlg.ssite.GetBuffer(dlg.ssite.GetLength() * sizeof(wchar_t));
				WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, PtMove->data.site, sizeof(PtMove->data.site), NULL, NULL);
			}

			if (!dlg.sdetail.IsEmpty()) {
				ptr = dlg.sdetail.GetBuffer(dlg.sdetail.GetLength() * sizeof(wchar_t));
				WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, PtMove->data.detail, sizeof(PtMove->data.detail), NULL, NULL);
			}

			PtMove->data.date.year = dlg.syear;
			PtMove->data.date.month = dlg.smonth;
			PtMove->data.date.day = dlg.sday;
			MessageBox(_T("修改成功！！"));
		}
		
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck()) {//选中删除
		
		PtMove_pre->next = PtMove->next;
		free(PtMove);
		MessageBox(_T("删除成功！！"));//弹窗
	}
	else {
		MessageBox(_T("修改失败！！"));//弹窗
	}
	WriteList(List, path);
	free(List);
	EndDialog(0);
	CDialogEx::OnOK();
}
