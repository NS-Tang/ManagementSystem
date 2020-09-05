// RegisterDlg.cpp: 实现文件
//

#include "stdafx.h"
#include <vector>
#include <map>
#include "ManagementSystem.h"
#include "RegisterDlg.h"
#include "afxdialogex.h"
#include "zrsMFC.h"


// RegisterDlg 对话框

IMPLEMENT_DYNAMIC(RegisterDlg, CDialogEx)

RegisterDlg::RegisterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_REGISTER, pParent)
{

}

RegisterDlg::~RegisterDlg()
{
}

void RegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RegisterDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &RegisterDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &RegisterDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// RegisterDlg 消息处理程序


void RegisterDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CStdioFile file;
	/**账户名密码存储的map.*/
	std::map<CString, CString> acount;
	file.Open("..\\acount.dat", CFile::modeReadWrite | CFile::shareDenyWrite | CFile::modeCreate | CFile::modeNoTruncate);
	zrs::MFC::GetAcount(file, acount);

	CString pwd;
	GetDlgItemText(IDC_EDIT_REGISTER_PWD, pwd);
	CString pwdConfirm;
	GetDlgItemText(IDC_EDIT_REGISTER_PWD_COFIRM, pwdConfirm);
	if (pwd == pwdConfirm)
	{
		CString uname;
		GetDlgItemText(IDC_EDIT_REGISTER_UNAME, uname);
		/**若已有这个用户名*/
		if (acount.count(uname))
		{
			MessageBox("用户名已存在！");
		}
		else
		{
			file.SeekToEnd();
			file.WriteString(uname + "\t" + pwd + "\n");
			MessageBox("注册成功！");
			file.Close();
			CDialogEx::OnOK();
		}
	}
	else
	{
		MessageBox("两次输入密码不相同！");
	}
}


void RegisterDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


BOOL RegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_EDIT_REGISTER_UNAME, m_sun);
	SetDlgItemText(IDC_EDIT_REGISTER_PWD, m_spwd);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
