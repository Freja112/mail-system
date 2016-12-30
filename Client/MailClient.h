
// MailClient.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.

#ifndef _REVSTRUCT_H
#define _REVSTRUCT_H
#pragma pack( 1 )
typedef struct _REV_STRUCT{
	int size;
	char p[256];
} REV_STRUCT;
#endif

// CMailClientApp:
// 이 클래스의 구현에 대해서는 MailClient.cpp을 참조하십시오.
//

class CMailClientApp : public CWinApp
{
public:
	CMailClientApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CMailClientApp theApp;