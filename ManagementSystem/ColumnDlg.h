#pragma once
/**由class SystemDlg调用.
* @file ColumnDlg.h
* @author 张润生
*/


// ColumnDlg 对话框

class ColumnDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ColumnDlg)

public:
	ColumnDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ColumnDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COLUMN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonColumnOk();
	afx_msg void OnBnClickedButtonColumnRestore();
	afx_msg void OnBnClickedButtonColumnDelete();
	/**存储父窗口传递的列标题.*/
	CString m_columnHeading;
	/**传递给父窗口是否删除列.*/
	BOOL m_isDelete = false;
	BOOL m_isAdd = false;
	afx_msg void OnClose();
};
