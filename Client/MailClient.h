
// MailClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

#ifndef _REVSTRUCT_H
#define _REVSTRUCT_H
#pragma pack( 1 )
typedef struct _REV_STRUCT{
	int size;
	char p[256];
} REV_STRUCT;
#endif

// CMailClientApp:
// �� Ŭ������ ������ ���ؼ��� MailClient.cpp�� �����Ͻʽÿ�.
//

class CMailClientApp : public CWinApp
{
public:
	CMailClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMailClientApp theApp;