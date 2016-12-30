#pragma once
#include "MailJoin.h"

// Login 대화 상자입니다.

class Login : public CDialogEx
{
	DECLARE_DYNAMIC(Login)

public:
	Login(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Login();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();
	CString m_sID;
	CString m_sPW;
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonJoin();
};
