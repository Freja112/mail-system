
// MailClientDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "login.h"
#include "MailView.h"
#include "MailSend.h"





// CMailClientDlg ��ȭ ����
class CMailClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMailClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAILCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lMenu;
	CString LoginID;
	CStatic m_cStaticID;
	afx_msg void OnLbnSelchangeMenu();
	afx_msg void OnBnClickedExit();
	CListCtrl m_ListC;
	Login dlg;
	afx_msg void OnNMClickSubmenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkSubmenu(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDel();
	int index;
};
