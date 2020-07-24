
// CaesarCipher.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CCaesarCipherApp:
// 有关此类的实现，请参阅 CaesarCipher.cpp
//

class CCaesarCipherApp : public CWinApp
{
public:
	CCaesarCipherApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();
};

extern CCaesarCipherApp theApp;
