// ColumnDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ManagementSystem.h"
#include "ColumnDlg.h"
#include "afxdialogex.h"


// ColumnDlg 对话框

IMPLEMENT_DYNAMIC(ColumnDlg, CDialogEx)

ColumnDlg::ColumnDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_COLUMN, pParent)
{

}

ColumnDlg::~ColumnDlg()
{
}

void ColumnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ColumnDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COLUMN_OK, &ColumnDlg::OnBnClickedButtonColumnOk)
	ON_BN_CLICKED(IDC_BUTTON_COLUMN_RESTORE, &ColumnDlg::OnBnClickedButtonColumnRestore)
	ON_BN_CLICKED(IDC_BUTTON_COLUMN_DELETE, &ColumnDlg::OnBnClickedButtonColumnDelete)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// ColumnDlg 消息处理程序


BOOL ColumnDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_EDIT_COLUMN, m_columnHeading);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void ColumnDlg::OnBnClickedButtonColumnOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT_COLUMN, m_columnHeading);
	m_isAdd = true;
	CDialogEx::OnOK();
}


void ColumnDlg::OnBnClickedButtonColumnRestore()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_COLUMN, m_columnHeading);
}


void ColumnDlg::OnBnClickedButtonColumnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isDelete = true;
	CDialogEx::OnOK();
}


void ColumnDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_isAdd = false;
	m_isDelete = false;
	CDialogEx::OnClose();
}
