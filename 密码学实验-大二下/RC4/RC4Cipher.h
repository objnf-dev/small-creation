
// RC4Cipher.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CRC4CipherApp:
// 有关此类的实现，请参阅 RC4Cipher.cpp
//

class CRC4CipherApp : public CWinApp
{
public:
	CRC4CipherApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CRC4CipherApp theApp;
