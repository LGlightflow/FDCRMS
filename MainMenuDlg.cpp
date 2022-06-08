// MainMenuDlg.cpp: 实现文件
//
#include <afxpriv.h>
#include "stdafx.h"
#include "FDCRMS_UI.h"
#include "MainMenuDlg.h"
#include "PropertyDlg.h"
#include "SumDlg.h"
#include "SortDlg.h"
#include "SearchDlg.h"
#include "ChangeDlg.h"
#include "afxdialogex.h"
#include "fdcrms.h"
#include "locale.h" //处理中文乱码
// MainMenuDlg 对话框

IMPLEMENT_DYNAMIC(MainMenuDlg, CDialogEx)

MainMenuDlg::MainMenuDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

MainMenuDlg::~MainMenuDlg()
{
}

void MainMenuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, MainList);
}


BEGIN_MESSAGE_MAP(MainMenuDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &MainMenuDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &MainMenuDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_flash, &MainMenuDlg::OnBnClickedButtonflash)
	ON_BN_CLICKED(IDC_BUTTON3, &MainMenuDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &MainMenuDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &MainMenuDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// MainMenuDlg 消息处理程序


void MainMenuDlg::OnClose() //窗口关闭自动执行
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog* pdlg =(CDialog*) AfxGetMainWnd(); //获取欢迎窗口的指针
	pdlg->DestroyWindow();//销毁主窗口

	CDialogEx::OnClose();
}


BOOL MainMenuDlg::OnInitDialog()//窗口初始化自动执行
{
	CDialogEx::OnInitDialog();
	

	// TODO:  在此添加额外的初始化
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);//最小化出现图标
	PrintMainList();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void MainMenuDlg::OnBnClickedButton2()//查询
{
	// TODO: 在此添加控件通知处理程序代码
	SearchDlg dlg;
	dlg.DoModal();


	extern char path[250];
	char path_temp[250];
	strcpy(path_temp, path);
	strcat(path_temp, "t");
	struct Node *List = CreateList();
	List = ReadList(List, path_temp);
	struct Node *PtMove = List->next;
	if (PtMove == NULL) {
		free(List);
		return;
	}


	MainList.DeleteAllItems();
	while (MainList.DeleteColumn(0));
	MainList.SetExtendedStyle(LVS_EX_FULLROWSELECT);//设置样式,整行选择
	MainList.InsertColumn(0, _T("消费日期"), 0, 100);
	MainList.InsertColumn(1, _T("成员身份"), 0, 100);
	MainList.InsertColumn(2, _T("消费金额"), 0, 100);
	MainList.InsertColumn(3, _T("消费品类"), 0, 100);
	MainList.InsertColumn(4, _T("支出方式"), 0, 100);
	MainList.InsertColumn(5, _T("消费场所"), 0, 100);
	MainList.InsertColumn(6, _T("商品详情"), 0, 100);


	CString date_l, ID_l, amount_l, type_l, method_l, site_l, detail_l;
	int i = 0;
	while (PtMove != NULL) {
		date_l.Format(_T("%d年%d月%d日"), PtMove->data.date.year, PtMove->data.date.month, PtMove->data.date.day);
		ID_l.Format(_T("%s"), CStringW(PtMove->data.ID));
		amount_l.Format(_T("%.2f 元"), PtMove->data.amount);
		type_l.Format(_T("%s"), CStringW(PtMove->data.type));
		method_l.Format(_T("%s"), CStringW(PtMove->data.method));
		site_l.Format(_T("%s"), CStringW(PtMove->data.site));
		detail_l.Format(_T("%s"), CStringW(PtMove->data.detail));//CStringW解决乱码
		MainList.InsertItem(i, date_l);//设置第一列，不设置的话后面的列都不显示
		MainList.SetItemText(i, 1, ID_l);
		MainList.SetItemText(i, 2, amount_l);
		MainList.SetItemText(i, 3, type_l);
		MainList.SetItemText(i, 4, method_l);
		MainList.SetItemText(i, 5, site_l);
		MainList.SetItemText(i, 6, detail_l);
		i = i + 1;
		PtMove = PtMove->next;
	}
	FreeList(List);
	List->next = NULL;//写入空文件
	WriteList(List,path_temp);
}


void MainMenuDlg::OnBnClickedButton5()//点击新增数据后的操作，获取子窗口输入的值并新增数据
{
	// TODO: 在此添加控件通知处理程序代码
	PropertyDlg dlg;
	dlg.DoModal(); //弹窗
	
	/*  
	CString cstr;
	char *rID = (LPSTR)(LPCTSTR)dlg.sID;
	float ramount = _tstof(dlg.samount);
	char *rtype = (LPSTR)(LPCTSTR)dlg.stype;
	char *rmethod = (LPSTR)(LPCTSTR)dlg.smethod;
	char *rsite = (LPSTR)(LPCTSTR)dlg.ssite;
	char *rdetail = (LPSTR)(LPCTSTR)dlg.sdetail;
	int ryear = _ttof(dlg.syear);
	int rmonth = _ttof(dlg.smonth);
	int rday = _ttof(dlg.sday);
	
	char *rID = new char[25];//把Cstring转换为char*
	sprintf(rID, "%hs", dlg.sID.GetBuffer());//如果直接强转换，只能读到首元素，但现在只能读取英文,sID是中文，说明可能转换的时候出错
	float ramount = _tstof(dlg.samount);
	char *rtype = new char[20];
	sprintf(rtype, "%s", dlg.stype.GetBuffer());
	char *rmethod = new char[20];
	sprintf(rmethod, "%s", dlg.smethod.GetBuffer());
	char *rsite = new char[20];
	sprintf(rsite, "%s", dlg.ssite.GetBuffer());
	char *rdetail = new char[50];
	sprintf(rdetail, "%s", dlg.sdetail.GetBuffer());
	int ryear = _ttof(dlg.syear);
	int rmonth = _ttof(dlg.smonth);
	int rday = _ttof(dlg.sday);
	*/

	/* 
	//以下将cstring转为char[]且解决中文乱码问题
	char rID[25],rtype[10],rmethod[10],rsite[10],rdetail[50];
	wchar_t *ptr;
	ptr = dlg.sID.GetBuffer(dlg.sID.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rID, sizeof(rID), NULL, NULL);

	float ramount = _tstof(dlg.samount);

	ptr = dlg.stype.GetBuffer(dlg.stype.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rtype, sizeof(rtype), NULL, NULL);

	ptr = dlg.smethod.GetBuffer(dlg.smethod.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rmethod, sizeof(rmethod), NULL, NULL);

	ptr = dlg.ssite.GetBuffer(dlg.ssite.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rsite, sizeof(rsite), NULL, NULL);

	ptr = dlg.sdetail.GetBuffer(dlg.sdetail.GetLength() * sizeof(wchar_t));
	WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, rdetail, sizeof(rdetail), NULL, NULL);

	int ryear = _ttof(dlg.syear);
	int rmonth = _ttof(dlg.smonth);
	int rday = _ttof(dlg.sday);


	MainList.DeleteAllItems();
	while(MainList.DeleteColumn(0));
	MainList.SetExtendedStyle(LVS_EX_FULLROWSELECT);//设置样式,整行选择
	MainList.InsertColumn(0, _T("消费日期"), 0, 100);
	MainList.InsertColumn(1, _T("成员身份"), 0, 100);
	MainList.InsertColumn(2, _T("消费金额"), 0, 100);
	MainList.InsertColumn(3, _T("消费品类"), 0, 100);
	MainList.InsertColumn(4, _T("支出方式"), 0, 100);
	MainList.InsertColumn(5, _T("消费场所"), 0, 100);
	MainList.InsertColumn(6, _T("商品详情"), 0, 100);


	char path[250] = "";
	strcat(path, "fee.dat");

	struct Node *List = CreateList();
	List = ReadList(List, path);
	struct data Data;
	Data.date.year = ryear;
	Data.date.month = rmonth;
	Data.date.day = rday;
	Data.amount = ramount;
	strcpy(Data.ID,rID);
	strcpy(Data.type,rtype);
	strcpy(Data.method,rmethod);
	strcpy(Data.site, rsite);
	strcpy(Data.detail,rdetail);
	InsertNode(List,Data);

	struct Node *PtMove = List->next;
	int i = 0;
	CString date_l, ID_l, amount_l, type_l, method_l, site_l, detail_l;


	while (PtMove != NULL) {
		date_l.Format(_T("%d年%d月%d日"), PtMove->data.date.year, PtMove->data.date.month, PtMove->data.date.day);
		ID_l.Format(_T("%s"), CStringW(PtMove->data.ID));
		amount_l.Format(_T("%.2f"), PtMove->data.amount);
		type_l.Format(_T("%s"), CStringW(PtMove->data.type));
		method_l.Format(_T("%s"), CStringW(PtMove->data.method));
		site_l.Format(_T("%s"), CStringW(PtMove->data.site));
		detail_l.Format(_T("%s"), CStringW(PtMove->data.detail));//CStringW解决乱码
		MainList.InsertItem(i, date_l);//设置第一列，不设置的话后面的列都不显示
		MainList.SetItemText(i, 1, ID_l);
		MainList.SetItemText(i, 2, amount_l);
		MainList.SetItemText(i, 3, type_l);
		MainList.SetItemText(i, 4, method_l);
		MainList.SetItemText(i, 5, site_l);
		MainList.SetItemText(i, 6, detail_l);
		i = i + 1;
		PtMove = PtMove->next;
	}
	*/;

	PrintMainList();
}




//刷新按钮
void MainMenuDlg::OnBnClickedButtonflash()
{
	PrintMainList();
	// TODO: 在此添加控件通知处理程序代码
}

//排序按钮
void MainMenuDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	SortDlg dlg;
	dlg.DoModal();
	PrintMainList();
}

//统计按钮
void MainMenuDlg::OnBnClickedButton4()
{
	SumDlg dlg;
	dlg.DoModal();

	// TODO: 在此添加控件通知处理程序代码
}


void MainMenuDlg::OnBnClickedButton6()//修改
{
	// TODO: 在此添加控件通知处理程序代码
	ChangeDlg dlg;
	dlg.DoModal();
	PrintMainList();
}





// 输出主菜单的列表数据
int MainMenuDlg::PrintMainList()
{
	// TODO: 在此处添加实现代码.
	MainList.DeleteAllItems();
	while (MainList.DeleteColumn(0));
	MainList.SetExtendedStyle(LVS_EX_FULLROWSELECT);//设置样式,整行选择
	MainList.InsertColumn(0, _T("消费日期"), 0, 100);
	MainList.InsertColumn(1, _T("成员身份"), 0, 100);
	MainList.InsertColumn(2, _T("消费金额"), 0, 100);
	MainList.InsertColumn(3, _T("消费品类"), 0, 100);
	MainList.InsertColumn(4, _T("支出方式"), 0, 100);
	MainList.InsertColumn(5, _T("消费场所"), 0, 100);
	MainList.InsertColumn(6, _T("商品详情"), 0, 100);


	//char path[250] = "";
	//strcat(path, "fee.dat");
	extern char path[250];
	struct Node *List = CreateList();
	List = ReadList(List, path);

	struct Node *PtMove = List->next;
	int i = 0;

	CString date_l, ID_l, amount_l, type_l, method_l, site_l, detail_l;
	while (PtMove != NULL) {
		date_l.Format(_T("%d年%d月%d日"), PtMove->data.date.year, PtMove->data.date.month, PtMove->data.date.day);
		ID_l.Format(_T("%s"), CStringW(PtMove->data.ID));
		amount_l.Format(_T("%.2f"), PtMove->data.amount);
		type_l.Format(_T("%s"), CStringW(PtMove->data.type));
		method_l.Format(_T("%s"), CStringW(PtMove->data.method));
		site_l.Format(_T("%s"), CStringW(PtMove->data.site));
		detail_l.Format(_T("%s"), CStringW(PtMove->data.detail));//CStringW解决乱码
		MainList.InsertItem(i, date_l);//设置第一列，不设置的话后面的列都不显示
		MainList.SetItemText(i, 1, ID_l);
		MainList.SetItemText(i, 2, amount_l);
		MainList.SetItemText(i, 3, type_l);
		MainList.SetItemText(i, 4, method_l);
		MainList.SetItemText(i, 5, site_l);
		MainList.SetItemText(i, 6, detail_l);
		i = i + 1;
		PtMove = PtMove->next;
	}
	FreeList(List);

	return 0;
}

