// SearchDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FDCRMS_UI.h"
#include "SearchDlg.h"
#include "afxdialogex.h"
#include "fdcrms.h"
//#include "MainMenuDlg.h"

// SearchDlg 对话框

IMPLEMENT_DYNAMIC(SearchDlg, CDialogEx)

SearchDlg::SearchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

SearchDlg::~SearchDlg()
{
}

void SearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_type2, cb_type);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, DateCtrl_s);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, DateCtrl_e);
	DDX_Control(pDX, IDC_EDIT_amount, edit_amount);
	DDX_Control(pDX, IDC_EDIT_ID, edit_ID);
}


BEGIN_MESSAGE_MAP(SearchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &SearchDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &SearchDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_CHECK1, &SearchDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &SearchDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDOK, &SearchDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SearchDlg 消息处理程序


void SearchDlg::OnBnClickedRadio1() //日期单选按钮
{
	// TODO: 在此添加控件通知处理程序代码
	DateCtrl_s.EnableWindow(TRUE);
	DateCtrl_e.EnableWindow(TRUE);
	edit_amount.EnableWindow(FALSE);
	cb_type.EnableWindow(FALSE);

	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1)) { //日期单选和家庭成员勾选同时选中
		edit_ID.EnableWindow(TRUE);
	}
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK2)) {//日期单选和消费品类勾选同时选中
		cb_type.EnableWindow(TRUE);
	}
}


void SearchDlg::OnBnClickedRadio2()//金额单选按钮
{
	// TODO: 在此添加控件通知处理程序代码
	//金额选中，日期、成员、品类都false
	DateCtrl_s.EnableWindow(FALSE);
	DateCtrl_e.EnableWindow(FALSE);
	edit_ID.EnableWindow(FALSE);
	cb_type.EnableWindow(FALSE);
	edit_amount.EnableWindow(TRUE);

}


void SearchDlg::OnBnClickedCheck1()//家庭成员勾选按钮
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck()&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1)) { //日期单选和家庭成员勾选同时选中
		edit_ID.EnableWindow(TRUE);
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK1)) { //日期单选选中 家庭成员没选中
		edit_ID.EnableWindow(FALSE);
	}
}


void SearchDlg::OnBnClickedCheck2()//消费品类勾选按钮
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck()&& BST_CHECKED == IsDlgButtonChecked(IDC_CHECK2)) {//日期单选和消费品类勾选同时选中
		cb_type.EnableWindow(TRUE);
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK2)) {//日期单选选中，消费品类没选中
		cb_type.EnableWindow(FALSE);
	}
}


BOOL SearchDlg::OnInitDialog()
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


void SearchDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK(); //关闭对话框，必须注释掉这一句，否则存文件报错（调试结果是传了空结点到写文件函数中）
	extern char path[250];
	struct Node *List = CreateList();
	List = ReadList(List, path);
	struct Node* SearchList = CreateList();
	struct Node* PtMove = List->next;
	if (((CButton *)GetDlgItem(IDC_RADIO2))->GetCheck()) { //选中消费金额
		
		CString samount;
		GetDlgItemText(IDC_EDIT_amount,samount);
		float ramount = _tstof(samount);


		while (PtMove != NULL) {
			if (PtMove->data.amount == ramount) {
				InsertNode(SearchList,PtMove->data);
			}
			PtMove = PtMove->next;
		}

	}
	else if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK1) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK2)) { //日期单选选中 家庭成员、消费品类没选中
		CTime CDate_s,CDate_e;
		DateCtrl_s.GetTime(CDate_s);
		DateCtrl_e.GetTime(CDate_e);
		int rdate_s = CDate_s.GetYear()*10000+CDate_s.GetMonth()*100+CDate_s.GetDay();
		int rdate_e = CDate_e.GetYear() * 10000 + CDate_e.GetMonth() * 100 + CDate_e.GetDay();
		while (PtMove != NULL) {
			int date_Node = PtMove->data.date.day + PtMove->data.date.month * 100 + PtMove->data.date.year * 10000;
			if (date_Node >= rdate_s && date_Node <= rdate_e) {
				InsertNode(SearchList, PtMove->data);
			}
			PtMove = PtMove->next;
		}
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1) && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK2)) { //日期 家庭成员单选选中, 消费品类没选中
		CTime CDate_s, CDate_e;
		DateCtrl_s.GetTime(CDate_s);
		DateCtrl_e.GetTime(CDate_e);
		int rdate_s = CDate_s.GetYear() * 10000 + CDate_s.GetMonth() * 100 + CDate_s.GetDay();
		int rdate_e = CDate_e.GetYear() * 10000 + CDate_e.GetMonth() * 100 + CDate_e.GetDay();
		
		CString sID;
		GetDlgItemText(IDC_EDIT_ID, sID);
		char rID[25];
		wchar_t *ptr;
		ptr = sID.GetBuffer(sID.GetLength() * sizeof(wchar_t));
		WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rID, sizeof(rID), NULL, NULL);
		

		while (PtMove != NULL) {
			int date_Node = PtMove->data.date.day + PtMove->data.date.month * 100 + PtMove->data.date.year * 10000;
			if (date_Node >= rdate_s && date_Node <= rdate_e && strcmp(PtMove->data.ID,rID)==0) {
				InsertNode(SearchList, PtMove->data);
			}
			PtMove = PtMove->next;
		}
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() && BST_UNCHECKED == IsDlgButtonChecked(IDC_CHECK1) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK2)) { //日期 家庭成员单选选中, 消费品类没选中
		CTime CDate_s, CDate_e;
		DateCtrl_s.GetTime(CDate_s);
		DateCtrl_e.GetTime(CDate_e);
		int rdate_s = CDate_s.GetYear() * 10000 + CDate_s.GetMonth() * 100 + CDate_s.GetDay();
		int rdate_e = CDate_e.GetYear() * 10000 + CDate_e.GetMonth() * 100 + CDate_e.GetDay();

		CString stype;
		GetDlgItemText(IDC_COMBO_type2, stype);//注意combobox的控件名字
		char rtype[25];
		wchar_t *ptr;
		ptr = stype.GetBuffer(stype.GetLength() * sizeof(wchar_t));
		WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rtype, sizeof(rtype), NULL, NULL);

		while (PtMove != NULL) {
			int date_Node = PtMove->data.date.day + PtMove->data.date.month * 100 + PtMove->data.date.year * 10000;
			if (date_Node >= rdate_s && date_Node <= rdate_e && strcmp(PtMove->data.type, rtype) == 0) {
				InsertNode(SearchList, PtMove->data);
			}
			PtMove = PtMove->next;
		}
	}
	else if (((CButton *)GetDlgItem(IDC_RADIO1))->GetCheck() && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK1) && BST_CHECKED == IsDlgButtonChecked(IDC_CHECK2)) { //日期 家庭成员 消费品类选中
		CTime CDate_s, CDate_e;
		DateCtrl_s.GetTime(CDate_s);
		DateCtrl_e.GetTime(CDate_e);
		int rdate_s = CDate_s.GetYear() * 10000 + CDate_s.GetMonth() * 100 + CDate_s.GetDay();
		int rdate_e = CDate_e.GetYear() * 10000 + CDate_e.GetMonth() * 100 + CDate_e.GetDay();

		CString stype, sID;
		GetDlgItemText(IDC_COMBO_type2, stype);
		GetDlgItemText(IDC_EDIT_ID, sID);
		char rtype[10],rID[25];
		wchar_t *ptr;
		ptr = stype.GetBuffer(stype.GetLength() * sizeof(wchar_t));
		WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rtype, sizeof(rtype), NULL, NULL);
		ptr = sID.GetBuffer(sID.GetLength() * sizeof(wchar_t));
		WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rID, sizeof(rID), NULL, NULL);

		while (PtMove != NULL) {
			int date_Node = PtMove->data.date.day + PtMove->data.date.month * 100 + PtMove->data.date.year * 10000;
			if (date_Node >= rdate_s && date_Node <= rdate_e && strcmp(PtMove->data.type, rtype) == 0 && strcmp(PtMove->data.ID, rID) == 0) {
				InsertNode(SearchList, PtMove->data);
			}
			PtMove = PtMove->next;
		}
	}
	else {
		MessageBox(_T("查询失败，查询方式不符合要求！"));//选择查询失败
	}

	if (SearchList->next == NULL) {
		MessageBox(_T("没有查询到相关数据！"));//弹窗
	}

	char path_temp[250];
	strcpy(path_temp, path);
	strcat(path_temp, "t");
	WriteList(SearchList, path_temp);
	FreeList(List);
	FreeList(SearchList);

	EndDialog(0);
}
