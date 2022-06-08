
// FDCRMS_UIDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "FDCRMS_UI.h"
#include "FDCRMS_UIDlg.h"
#include "afxdialogex.h"
#include "MainMenuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

char path[250] = "fee.dat";//默认路径
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFDCRMSUIDlg 对话框



CFDCRMSUIDlg::CFDCRMSUIDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FDCRMS_UI_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFDCRMSUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFDCRMSUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDWELCOME, &CFDCRMSUIDlg::OnStnClickedWelcome)
	ON_BN_CLICKED(IDC_BUTTON1_WELCOME, &CFDCRMSUIDlg::OnBnClickedButton1Welcome)
END_MESSAGE_MAP()


// CFDCRMSUIDlg 消息处理程序

BOOL CFDCRMSUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CFont cfont;
	CWnd* pWnd = GetDlgItem(IDWELCOME);
	cfont.CreatePointFont(600, _T("宋体"), NULL);
	pWnd->SetFont(&cfont);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFDCRMSUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFDCRMSUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFDCRMSUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFDCRMSUIDlg::OnStnClickedWelcome()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("欢迎！"));
}



void CFDCRMSUIDlg::OnBnClickedButton1Welcome()
{
	// TODO: 在此添加控件通知处理程序代码
	//进入主界面
	ShowWindow(SW_HIDE);//隐藏欢迎界面

	CString selectedPath;
	GetDlgItemText(IDC_MFCEDITBROWSE, selectedPath);//获取文件路径
	
	if (!selectedPath.IsEmpty()) {
		wchar_t *ptr;
		ptr = selectedPath.GetBuffer(selectedPath.GetLength() * sizeof(wchar_t));
		WideCharToMultiByte(CP_ACP, 0, (LPCTSTR)ptr, -1, path, sizeof(path), NULL, NULL);
	}
	else {
		MessageBox(_T("没有找到数据文件！尝试打开默认数据文件或新建文件"));
	}
	MainMenuDlg dlg;
	dlg.DoModal();
}
