// SystemDlg.cpp: 实现文件
//

#include "stdafx.h"
#include <vector>
#include "afxdialogex.h"
#include "ManagementSystem.h"
#include "SystemDlg.h"
#include "ColumnDlg.h"
#include "ChangePassWordDlg.h"
#include "DeleteAcountDlg.h"


// SystemDlg 对话框

IMPLEMENT_DYNAMIC(SystemDlg, CDialogEx)

SystemDlg::SystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SYSTEM, pParent)
{

}

SystemDlg::~SystemDlg()
{
}

void SystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_EDIT_MODIFY, m_edit);
}


BEGIN_MESSAGE_MAP(SystemDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SELECT_ALL, &SystemDlg::OnBnClickedButtonSelectAll)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_INVERT, &SystemDlg::OnBnClickedButtonSelectInvert)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &SystemDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &SystemDlg::OnBnClickedButtonLoad)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &SystemDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &SystemDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_ALL, &SystemDlg::OnBnClickedButtonSaveAll)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &SystemDlg::OnLvnColumnclickList1)
	ON_WM_CTLCOLOR()
	ON_EN_KILLFOCUS(IDC_EDIT_MODIFY, &SystemDlg::OnEnKillfocusEditModify)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &SystemDlg::OnNMRClickList1)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_ACOUNT, &SystemDlg::OnBnClickedButtonDeleteAcount)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_PWD, &SystemDlg::OnBnClickedButtonChangePwd)
END_MESSAGE_MAP()


// SystemDlg 消息处理程序


void SystemDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog *pdlg = (CDialog *)AfxGetMainWnd();
	pdlg->DestroyWindow();
	CDialogEx::OnClose();
}


BOOL SystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);

	m_edit.ShowWindow(SW_HIDE);
	CRect rect;
	m_list.GetClientRect(&rect);
	int iLength = rect.Width();
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	m_sort.AddIcon(m_list);

	CString strBmpPath = _T("..\\ManagementSystem\\res\\SystemDlg.jpg");
	CImage img;
	img.Load(strBmpPath);
	MoveWindow(0, 0, img.GetWidth(), img.GetHeight());
	CBitmap bmpTmp;
	bmpTmp.Attach(img.Detach());
	m_bkBrush.CreatePatternBrush(&bmpTmp);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void SystemDlg::OnBnClickedButtonSelectAll()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int nItem = 0; nItem < m_list.GetItemCount(); nItem++)
	{
		m_list.SetCheck(nItem, TRUE);
	}
}


void SystemDlg::OnBnClickedButtonSelectInvert()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int nItem = 0; nItem < m_list.GetItemCount(); nItem++)
	{
		m_list.SetCheck(nItem, !m_list.GetCheck(nItem));
	}
}


void SystemDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	Save(false);
}


void SystemDlg::OnBnClickedButtonSaveAll()
{
	// TODO: 在此添加控件通知处理程序代码
	Save(true);
}


void SystemDlg::Save(_In_ BOOL isSaveAll)
{
	CFileDialog fDlg(FALSE, ".dat", "savedata", OFN_OVERWRITEPROMPT, "数据文件(*.dat)|*.txt|所有文件(*.*)|*.*||", NULL);
	if (fDlg.DoModal() == IDOK)
	{
		CStdioFile file(fDlg.GetPathName(), CFile::modeWrite | CFile::shareDenyWrite | CFile::modeCreate);

		CString string;

		zrs::MFC::ConcatenateSubstringsIntoString("\t", string, m_columnTitles);
		file.WriteString(string + "\n");

		for (int nItem = 0; nItem < m_list.GetItemCount(); nItem++)
		{
			if (isSaveAll || m_list.GetCheck(nItem))
			{
				CString string;
				std::vector<CString> substrings;
				GetItem(nItem, substrings);
				zrs::MFC::ConcatenateSubstringsIntoString("\t", string, substrings);
				file.WriteString(string + "\n");
			}
		}
		file.Close();
		MessageBox(fDlg.GetPathName());
	}
}


void SystemDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fDialog(TRUE, ".txt", "save", OFN_OVERWRITEPROMPT, "文本文档(*.txt)|*.txt|所有文件(*.*)|*.*||", NULL);
	if (fDialog.DoModal() == IDOK)
	{
		CStdioFile file(fDialog.GetPathName(), CFile::modeRead | CFile::shareDenyWrite);
		m_list.DeleteAllItems();

		CString string;

		m_columnTitles.clear();
		file.ReadString(string);
		zrs::MFC::DivideStringIntoSubstrings("\t", string, m_columnTitles);

		RefreshColumn(0, 200);


		for (int nItem = 0; file.ReadString(string); nItem++)
		{
			std::vector<CString>substrings;
			zrs::MFC::DivideStringIntoSubstrings("\t", string, substrings);
			InsertItem(nItem, substrings);
		}
		file.Close();
	}
}


void SystemDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CRect rc;
	CString strTemp;
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	m_Row = pNMListView->iItem;
	m_Col = pNMListView->iSubItem;

	if (pNMListView->iItem == -1)    //选择空白处，添加一行，并设置焦点为最后一行，第0列  
	{
		m_Row = m_list.GetItemCount();
		m_list.InsertItem(m_Row, strTemp);
		m_list.SetItemState(m_Row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_list.EnsureVisible(m_Row, FALSE);
	}

	m_list.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);
	m_edit.SetParent(&m_list);
	m_edit.MoveWindow(rc);
	m_edit.SetWindowText(m_list.GetItemText(m_Row, m_Col));
	m_edit.ShowWindow(SW_SHOW);
	m_edit.SetFocus();//设置Edit焦点  
	m_edit.ShowCaret();//显示光标  
	m_edit.SetSel(0, -1);//全选  

	*pResult = 0;
}


void SystemDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int nItem = 0; nItem < m_list.GetItemCount();)
	{
		if (m_list.GetCheck(nItem))
		{
			m_list.DeleteItem(nItem);
		}
		else
		{
			nItem++;
		}
	}
}


void SystemDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_sort.run(pNMLV->iSubItem, m_list);
}


HBRUSH SystemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void SystemDlg::OnEnKillfocusEditModify()
{
	// TODO: 在此添加控件通知处理程序代码
	CString string;
	m_edit.GetWindowText(string);
	m_list.SetItemText(m_Row, m_Col, string);
	m_edit.ShowWindow(SW_HIDE);
}


void SystemDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	auto iSubItem = pNMItemActivate->iSubItem;
	auto pHeaderCtrl = m_list.GetHeaderCtrl();
	ColumnDlg dlg;

	/**单击列，修改删除列*/
	if (iSubItem >= 0)
	{
		HDITEM hdi = { 0 };
		TCHAR szBuf[129] = { 0 };
		hdi.mask = HDI_TEXT;
		hdi.pszText = szBuf;
		hdi.cchTextMax = 128;

		pHeaderCtrl->GetItem(iSubItem, &hdi);
		dlg.m_columnHeading = hdi.pszText;

		dlg.DoModal();

		if (dlg.m_isDelete)//删除列
		{
			m_list.DeleteColumn(iSubItem);
			m_columnTitles.pop_back();
		}
		else//修改列
		{

			hdi.pszText = (LPSTR)(LPCTSTR)dlg.m_columnHeading;
			pHeaderCtrl->SetItem(iSubItem, &hdi);

			m_columnTitles[iSubItem] = dlg.m_columnHeading;
		}

	}
	/**单击空白列，添加列*/
	else
	{
		dlg.m_columnHeading = "请在此处输入增加的列标题";

		dlg.DoModal();
		if (dlg.m_isAdd)
		{
			m_list.InsertColumn(pHeaderCtrl->GetItemCount(), dlg.m_columnHeading, 0, 200);
			m_columnTitles.push_back(dlg.m_columnHeading);
		}
	}


	*pResult = 0;
}


void SystemDlg::RefreshColumn(_In_ int nFormat, _In_ int nWidth, _In_ int nSubItem)
{
	while (m_list.DeleteColumn(0)) {}
	for (auto iter = m_columnTitles.begin(); iter != m_columnTitles.end(); iter++)
	{
		m_list.InsertColumn(iter - m_columnTitles.begin(), *iter, nFormat, nWidth, nSubItem);
	}
}


void SystemDlg::InsertItem(_In_ int nItem, _In_ std::vector<CString> & substrings)
{
	m_list.InsertItem(nItem, substrings[0]);
	SetItem(nItem, substrings, 1);
}


void SystemDlg::SetItem(_In_ int nItem, _In_ std::vector<CString> & substrings, _In_ size_t start)
{
	for (auto iter = substrings.begin() + start; iter != substrings.end(); iter++)
	{
		m_list.SetItemText(nItem, iter - substrings.begin(), *iter);
	}
}


void SystemDlg::GetItem(_In_ int nItem, _Out_ std::vector<CString> & substrings)
{
	for (int i = 0; i < m_list.GetHeaderCtrl()->GetItemCount(); i++)
	{
		substrings.push_back(m_list.GetItemText(nItem, i));
	}
}


void SystemDlg::OnBnClickedButtonDeleteAcount()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteAcountDlg dlg;
	dlg.m_pAcount = m_pAcount;
	dlg.m_pIter = m_pIter;
	dlg.DoModal();
}

void SystemDlg::OnBnClickedButtonChangePwd()
{
	// TODO: 在此添加控件通知处理程序代码
	ChangePassWordDlg dlg;

	dlg.m_pAcount = m_pAcount;
	dlg.m_pIter = m_pIter;

	dlg.DoModal();
}
