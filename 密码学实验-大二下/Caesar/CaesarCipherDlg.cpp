#include "pch.h"
#include "framework.h"
#include "CaesarCipher.h"
#include "CaesarCipherDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCaesarCipherDlg 对话框

CCaesarCipherDlg::CCaesarCipherDlg(CWnd* pParent)
	: CDialogEx(IDD_CAESARCIPHER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCaesarCipherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCaesarCipherDlg, CDialogEx)
		ON_WM_SYSCOMMAND()
		ON_WM_PAINT()
		ON_WM_QUERYDRAGICON()
		ON_BN_CLICKED(IDC_BUTTON1, &CCaesarCipherDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCaesarCipherDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

BOOL CCaesarCipherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE); // 设置大图标
	SetIcon(m_hIcon, FALSE); // 设置小图标

	CButton* radio1 = (CButton*)GetDlgItem(IDC_RADIO1);
	radio1->SetCheck(1);

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CCaesarCipherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCaesarCipherDlg::OnPaint()
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

HCURSOR CCaesarCipherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCaesarCipherDlg::OnBnClickedButton1()
{
	const auto chk_radio_1 = ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck();
	const auto chk_radio_2 = ((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck();

	int key_int = 0;
	CString key, message;
	char cipher[1000] = { 0 };

	GetDlgItemTextA(IDC_EDIT3, key);
	GetDlgItemTextA(IDC_EDIT1, message);
	int msg_len = message.GetLength();

	if (chk_radio_1 == 1 && chk_radio_2 == 0)
		key_int = _ttoi(key);
	else if (chk_radio_1 == 0 && chk_radio_2 == 1)
		key_int = 26 - _ttoi(key);

	for(int i = 0; i < msg_len; i++)
	{
		char tmp = (char)message[i];
		if ((tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
		{
			if ((tmp <= 122 && tmp + key_int > 122) || (tmp <= 90 && tmp + key_int > 90))
				cipher[i] = (char)message[i] - 26 + key_int;
			else
				cipher[i] = (char)message[i] + key_int;
		}
		else
			cipher[i] = (char)message[i];
	}

	SetDlgItemTextA(IDC_EDIT2, CString(cipher));
}


void CCaesarCipherDlg::OnBnClickedButton2()
{
	CString empty("");
	SetDlgItemTextA(IDC_EDIT1, empty);
	SetDlgItemTextA(IDC_EDIT2, empty);
	SetDlgItemTextA(IDC_EDIT3, empty);
}
