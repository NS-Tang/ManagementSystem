
// ManagementSystemDlg.cpp: 实现文件
//

#include "stdafx.h"
#include <map>
#include "zrsMFC.h"
#include "ManagementSystem.h"
#include "ManagementSystemDlg.h"
#include "afxdialogex.h"
#include "SystemDlg.h"
#include "RegisterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CManagementSystemDlg 对话框



CManagementSystemDlg::CManagementSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CManagementSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CManagementSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LGN, &CManagementSystemDlg::OnBnClickedButtonLgn)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CManagementSystemDlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// CManagementSystemDlg 消息处理程序

BOOL CManagementSystemDlg::OnInitDialog()
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

	/**添加背景.*/
	CString strBmpPath = _T("..\\ManagementSystem\\res\\ManagementSystemDlg.jpg");
	CImage img;
	img.Load(strBmpPath);
	MoveWindow(0, 0, img.GetWidth(), img.GetHeight());
	CBitmap bmpTmp;
	bmpTmp.Attach(img.Detach());
	m_bkBrush.CreatePatternBrush(&bmpTmp);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CManagementSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CManagementSystemDlg::OnPaint()
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
HCURSOR CManagementSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/**点击「登录」按钮.*/
void CManagementSystemDlg::OnBnClickedButtonLgn()
{
	// TODO: 在此添加控件通知处理程序代码
	/**获取用户名密码.*/
	CString sun, spwd;
	GetDlgItemText(IDC_EDIT_UNAME, sun);
	GetDlgItemText(IDC_EDIT_PWD, spwd);
	/**读入账户信息，写入std::map<CString, CString> acount.*/
	CStdioFile file;
	file.Open("..\\acount.dat", CFile::modeRead | CFile::shareDenyWrite | CFile::modeCreate | CFile::modeNoTruncate);
	std::map<CString, CString> acount;
	zrs::MFC::GetAcount(file, acount);
	file.Close();
	/**查找用户名对应的iterator.*/
	auto iter = acount.find(sun);
	/**用户名不正确或与密码不对应.
	*按照一般登录系统设计惯例，这里不应分别提示用户名不正确还是与密码不对应*/
	if (iter == acount.end()
		||
		iter->second != spwd)
	{
		MessageBox(_T("用户名或密码不正确！"), _T("登录失败！"));
	}
	else
	{
		/**隐藏此窗口.*/
		ShowWindow(SW_HIDE);
		/**创建管理系统窗口对象.*/
		SystemDlg dlg;
		/**账户信息map和登录的账户所对应的iterator传入子窗口.*/
		dlg.m_pAcount = &acount;
		dlg.m_pIter = &iter;

		dlg.DoModal();
	}
}

/**添加背景.*/
HBRUSH CManagementSystemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd == this)
	{
		return m_bkBrush;
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

/**点击「注册」按钮.*/
void CManagementSystemDlg::OnBnClickedButtonRegister()
{
	// TODO: 在此添加控件通知处理程序代码
	/**获取用户名密码.*/
	CString sun, spwd;
	GetDlgItemText(IDC_EDIT_UNAME, sun);
	GetDlgItemText(IDC_EDIT_PWD, spwd);
	/**创建注册窗口对象.*/
	RegisterDlg dlg;
	/**账户信息map和登录的账户所对应的iterator传入子窗口.*/
	dlg.m_sun = sun;
	dlg.m_spwd = spwd;

	dlg.DoModal();

}
