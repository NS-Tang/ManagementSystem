#pragma once
/**由class SystemDlg调用.
* @file DeleteAcountDlg.h
* @author 张润生
*/


// DeleteAcountDlg 对话框

class DeleteAcountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteAcountDlg)

public:
	DeleteAcountDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DeleteAcountDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETE_ACOUNT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	/**接收调用者传递的总账号信息map*/
	std::map<CString, CString> *m_pAcount;
	/**接收调用者传递当前账号的iterator*/
	std::map<CString, CString>::iterator *m_pIter;
};
