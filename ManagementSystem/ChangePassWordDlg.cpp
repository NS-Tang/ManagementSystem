// ChangePassWordDlg.cpp: 实现文件
//

#include "stdafx.h"
#include <map>
#include "zrsMFC.h"
#include "ManagementSystem.h"
#include "ChangePassWordDlg.h"
#include "afxdialogex.h"


// ChangePassWordDlg 对话框

IMPLEMENT_DYNAMIC(ChangePassWordDlg, CDialogEx)

ChangePassWordDlg::ChangePassWordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CHANGE_PASSWORD, pParent)
{

}

ChangePassWordDlg::~ChangePassWordDlg()
{
}

void ChangePassWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChangePassWordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ChangePassWordDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ChangePassWordDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// ChangePassWordDlg 消息处理程序


void ChangePassWordDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	/**原密码*/
	CString original_pwd;
	/**新密码*/
	CString new_pwd;
	/**确认新密码*/
	CString new_pwd_confirm;

	GetDlgItemText(IDC_EDIT_ORIGINAL_PWD, original_pwd);
	GetDlgItemText(IDC_EDIT_NEW_PWD, new_pwd);
	GetDlgItemText(IDC_EDIT_NEW_PWD_CONFIRM, new_pwd_confirm);

	/**输入密码正确*/
	if (original_pwd == (*m_pIter)->second)
	{
		/**两次输入密码相同*/
		if (new_pwd == new_pwd_confirm)
		{
			/**新密码与原密码相同*/
			if (new_pwd == original_pwd)
			{
				MessageBox("新密码与原密码不可相同！");
			}
			else
			{
				(*m_pIter)->second = new_pwd;
				CStdioFile file;
				file.Open("..\\acount.dat", CFile::modeWrite | CFile::shareDenyWrite | CFile::modeCreate);
				zrs::MFC::SetAcount(file, *m_pAcount);
				file.Close();

				MessageBox("更改密码成功！");
				CDialogEx::OnOK();
			}
		}
		else
		{
			MessageBox("两次输入密码不相同！");
		}
	}
	else
	{
		MessageBox("原密码错误！");
	}
}


void ChangePassWordDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
