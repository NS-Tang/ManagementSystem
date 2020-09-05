/**由class ManagementSystemDlg调用.
* @file SystemDlg.h
* @author 张润生
*/
#pragma once
#include <vector>
#include "zrsMFC.h"


// SystemDlg 对话框

class SystemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SystemDlg)

public:
	SystemDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SystemDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SYSTEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSelectAll();
	afx_msg void OnBnClickedButtonSelectInvert();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonSaveAll();
	afx_msg void OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditModify();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDeleteAcount();
	afx_msg void OnBnClickedButtonChangePwd();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();

private:
	/**列标题vector.*/
	std::vector<CString> m_columnTitles;
	/**提供点击列标题排序功能的对象.*/
	zrs::MFC::SortingOnLvnColumnclickList m_sort;
	/**点击List Control中的行数.*/
	int m_Row = -1;
	/**点击List Control中的列数.*/
	int m_Col = -1;
public:
	CBrush m_bkBrush;
	/**List Control对象.*/
	CListCtrl m_list;
	/**点击List Control生成的文本框.*/
	CEdit m_edit;
	/**接收调用者传递的总账号信息map*/
	std::map<CString, CString> *m_pAcount;
	/**接收调用者传递当前账号的iterator*/
	std::map<CString, CString>::iterator *m_pIter;

private:
	/**保存.
	* @param isSaveAll [in] true则为全部保存，false为按Check保存
	*/
	void Save(_In_ BOOL isSaveAll);
	/**刷新列标题.
	* 根据m_columnTitles刷新列标题
	* @param nFormat [in] 传递给CListCtrl::InsertColumn的同名参数
	* @param nWidth [in] 传递给CListCtrl::InsertColumn的同名参数
	* @param nSubItem [in] 传递给CListCtrl::InsertColumn的同名参数
	*/
	void RefreshColumn(_In_ int nFormat = LVCFMT_LEFT, _In_ int nWidth = -1, _In_ int nSubItem = -1);
	/**设置一行List Control（即一个item）.
	* @param nItem [in] 传递给CListCtrl::SetItemText的同名参数
	* @param substrings [in] item的各项字符串的vector引用
	* @param start [in] 开始设置的行数，默认为0
	*/
	void SetItem(_In_ int nItem, _In_ std::vector<CString> & substrings, _In_ size_t start = 0);
	/**插入一行List Control（即一个item）.
	* @param nItem [in] 传递给CListCtrl::InsertItem的同名参数
	* @param substrings [in] item的各项字符串的vector引用
	*/
	void InsertItem(_In_ int nItem, _In_ std::vector<CString> & substrings);
	/**获取一行List Control（即一个item）.
	* @param nItem [in] 传递给CListCtrl::GetItemText的同名参数
	* @param substrings [out] item的各项字符串的vector引用
	*/
	void GetItem(_In_ int nItem, _Out_ std::vector<CString> & substrings);
};
