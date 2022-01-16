
// RC4CipherDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "RC4Cipher.h"
#include "RC4CipherDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRC4CipherDlg 对话框



CRC4CipherDlg::CRC4CipherDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RC4CIPHER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRC4CipherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRC4CipherDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Empty, &CRC4CipherDlg::OnBnClickedEmpty)
	ON_BN_CLICKED(IDC_Encrypt, &CRC4CipherDlg::OnBnClickedEncrypt)
	ON_BN_CLICKED(IDC_Decrypt, &CRC4CipherDlg::OnBnClickedDecrypt)
END_MESSAGE_MAP()


// CRC4CipherDlg 消息处理程序

BOOL CRC4CipherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CRC4CipherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CRC4CipherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRC4CipherDlg::OnBnClickedEmpty()
{
	CString empty = "";
	SetDlgItemTextA(IDC_PlainText, empty);
	SetDlgItemTextA(IDC_Password, empty);
	SetDlgItemTextA(IDC_Cipher, empty);
	SetDlgItemTextA(IDC_CipherDecrypt, empty);
	SetDlgItemTextA(IDC_Stream, empty);
}

void CRC4CipherDlg::OnBnClickedEncrypt()
{
	CString plaintext, password, stream, cipher;

	GetDlgItemTextA(IDC_PlainText, plaintext);
	char* plainMsg = plaintext.GetBuffer(0);
	int plainMsgSize = plaintext.GetLength();

	GetDlgItemTextA(IDC_Password, password);
	char* passText = password.GetBuffer(0);
	int passSize = password.GetLength();

	// Init S-Box
	uint8_t S[256];
	for (int i = 0; i < 256; i++)
		S[i] = i;

	// Randomize S-Box using password
	uint8_t j = 0;
	for (int i = 0; i < 256; i++) {
		j = (j + S[i] + passText[i % passSize]) % 256;
		int tmp = S[j];
		S[j] = S[i];
		S[i] = tmp;
	}

	// Generate key stream
	uint8_t i = 0;
	j = 0;
	char* kstr = new char[plainMsgSize + 1]();

	for (int k = 0; k < plainMsgSize; k++) {
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		uint8_t tmp = S[j];
		S[j] = S[i];
		S[i] = tmp;
		kstr[k] = S[(S[i] + S[j]) % 256];
	}

	// Encrypt
	char* c = new char[plainMsgSize + 1]();
	for (int k = 0; k < plainMsgSize; k++) {
		c[k] = kstr[k] ^ plainMsg[k];
	}

	// Show result
	cipher = c;
	stream = kstr;

	SetDlgItemTextA(IDC_Cipher, cipher);
	SetDlgItemTextA(IDC_Stream, stream);
}


void CRC4CipherDlg::OnBnClickedDecrypt()
{
	CString plaintext, password, stream, cipher;

	// GetKey
	GetDlgItemTextA(IDC_Password, password);
	int ksize = password.GetLength();
	char* key = password.GetBuffer(0);

	// GetCipher
	GetDlgItemTextA(IDC_Cipher, cipher);
	int msgSize = cipher.GetLength();
	char* msgCipher = cipher.GetBuffer(0);

	// Init S-Box
	uint8_t S[256];
	for (int i = 0; i < 256; i++)
		S[i] = i;

	// Randomize S-Box using password
	uint8_t j = 0;
	for (int i = 0; i < 256; i++) {
		j = (j + S[i] + key[i % ksize]) % 256;
		int tmp = S[j];
		S[j] = S[i];
		S[i] = tmp;
	}

	// Generate key stream
	uint8_t i = 0;
	j = 0;
	char* kstr = new char[msgSize + 1]();

	for (int k = 0; k < msgSize; k++) {
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		uint8_t tmp = S[j];
		S[j] = S[i];
		S[i] = tmp;
		kstr[k] = S[(S[i] + S[j]) % 256];
	}

	// Decrypt
	char* m = new char[msgSize + 1]();
	for (int k = 0; k < msgSize; k++) {
		m[k] = msgCipher[k] ^ kstr[k];
	}

	// Show the result
	stream = kstr;
	plaintext = m;
	SetDlgItemTextA(IDC_Stream, stream);
	SetDlgItemTextA(IDC_CipherDecrypt, plaintext);
}
