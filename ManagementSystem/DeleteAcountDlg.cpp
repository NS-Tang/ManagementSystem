// DeleteAcountDlg.cpp: 实现文件
//

#include "stdafx.h"
#include <map>
#include "zrsMFC.h"
#include "ManagementSystem.h"
#include "DeleteAcountDlg.h"
#include "afxdialogex.h"


// DeleteAcountDlg 对话框

IMPLEMENT_DYNAMIC(DeleteAcountDlg, CDialogEx)

DeleteAcountDlg::DeleteAcountDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELETE_ACOUNT, pParent)
{

}

DeleteAcountDlg::~DeleteAcountDlg()
{
}

void DeleteAcountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DeleteAcountDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &DeleteAcountDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DeleteAcountDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// DeleteAcountDlg 消息处理程序


void DeleteAcountDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString pwd;
	GetDlgItemText(IDC_EDIT_DELETE_ACOUNT_PWD, pwd);
	if ((*m_pIter)->second == pwd)
	{
		m_pAcount->erase(*m_pIter);
		CStdioFile file;
		file.Open("..\\acount.dat", CFile::modeWrite | CFile::shareDenyWrite | CFile::modeCreate);
		zrs::MFC::SetAcount(file, *m_pAcount);

		MessageBox("注销成功！");
		CDialogEx::OnOK();
	}
	else
	{
		MessageBox("密码错误!");
	}
}


void DeleteAcountDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
