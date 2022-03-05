
// MFCTestCPPDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCTestCPP.h"
#include "MFCTestCPPDlg.h"
#include "afxdialogex.h"
#include <string.h>

#include<opencv2/opencv.hpp>
#include<iostream>

#include "MatToBMP.h"


using namespace std;
using namespace cv;



auto ConvertCVMatToBMP(cv::Mat frame) -> HBITMAP
{
	auto convertOpenCVBitDepthToBits = [](const int32_t value)
	{
		auto regular = 0u;

		switch (value)
		{
		case CV_8U:
		case CV_8S:
			regular = 8u;
			break;

		case CV_16U:
		case CV_16S:
			regular = 16u;
			break;

		case CV_32S:
		case CV_32F:
			regular = 32u;
			break;

		case CV_64F:
			regular = 64u;
			break;

		default:
			regular = 0u;
			break;
		}

		return regular;
	};

	auto imageSize = frame.size();
	assert(imageSize.width && "invalid size provided by frame");
	assert(imageSize.height && "invalid size provided by frame");

	if (imageSize.width && imageSize.height)
	{
		auto headerInfo = BITMAPINFOHEADER{};
		ZeroMemory(&headerInfo, sizeof(headerInfo));

		headerInfo.biSize = sizeof(headerInfo);
		headerInfo.biWidth = imageSize.width;
		headerInfo.biHeight = -(imageSize.height); // negative otherwise it will be upsidedown
		headerInfo.biPlanes = 1;// must be set to 1 as per documentation frame.channels();

		const auto bits = convertOpenCVBitDepthToBits(frame.depth());
		headerInfo.biBitCount = frame.channels() * bits;

		auto bitmapInfo = BITMAPINFO{};
		ZeroMemory(&bitmapInfo, sizeof(bitmapInfo));

		bitmapInfo.bmiHeader = headerInfo;
		bitmapInfo.bmiColors->rgbBlue = 0;
		bitmapInfo.bmiColors->rgbGreen = 0;
		bitmapInfo.bmiColors->rgbRed = 0;
		bitmapInfo.bmiColors->rgbReserved = 0;

		auto dc = GetDC(nullptr);
		assert(dc != nullptr && "Failure to get DC");
		auto bmp = CreateDIBitmap(dc,
			&headerInfo,
			CBM_INIT,
			frame.data,
			&bitmapInfo,
			DIB_RGB_COLORS);
		assert(bmp != nullptr && "Failure creating bitmap from captured frame");

		return bmp;
	}
	else
	{
		return nullptr;
	}
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//CvCapture* capture;
//CRect rect;
//CDC* pDC;
//HDC hDC;
//CWnd* pwnd;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedTestStatic();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_STN_CLICKED(IDC_TEST_STATIC, &CAboutDlg::OnStnClickedTestStatic)
END_MESSAGE_MAP()


// CMFCTestCPPDlg 对话框



CMFCTestCPPDlg::CMFCTestCPPDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTESTCPP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTestCPPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEST_STATIC, m_Picture);
}

BEGIN_MESSAGE_MAP(CMFCTestCPPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCTestCPPDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCTestCPPDlg::OnBnClickedCancel)
	ON_STN_CLICKED(IDC_TEST_STATIC, &CMFCTestCPPDlg::OnStnClickedTestStatic)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCTestCPPDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCTestCPPDlg 消息处理程序

BOOL CMFCTestCPPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_NORMAL);

	ShowWindow(SW_NORMAL);

	// TODO: 在此添加额外的初始化代码

	/*pwnd = GetDlgItem(IDC_TEST_STATIC);

	pDC = pwnd->GetDC();
	hDC = pDC->GetSafeHdc();
	pwnd->GetClientRect(&rect);*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCTestCPPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCTestCPPDlg::OnPaint()
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
HCURSOR CMFCTestCPPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCTestCPPDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//DialogEx::OnOK();
	VideoCapture capture(0);


	//HBITMAP hBmp = (HBITMAP)LoadImageW(NULL, TEXT("C:\\Users\\Lee Xiaopeng\\Desktop\\Temp File\\图片1.bmp"), IMAGE_BITMAP, 800, 800, LR_LOADFROMFILE); //加载位图文件到位图对象
	//m_Picture.SetBitmap(hBmp);

	if (!capture.isOpened())
	{
		CString str("无法打开摄像头！");
		MessageBox(str);
	}

	Mat frame;//定义一个Mat变量，用于存储每一帧的图像
	capture >> frame;  //读取当前帧
	MatToBMP mtb(frame);
	while (capture.isOpened())
	{

		capture >> frame;  //读取当前帧
		m_Picture.SetBitmap(mtb.mCreateDIBitmap(frame));
		m_Picture.SetCapture();
		//imshow("读取视频", frame);  //显示当前帧
		
	}
	
	CString str("dianji");
	MessageBox(str);
}


void CMFCTestCPPDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CAboutDlg::OnStnClickedTestStatic()
{
	// TODO: 在此添加控件通知处理程序代码

	
	
}


void CMFCTestCPPDlg::OnStnClickedTestStatic()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CMFCTestCPPDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	/*Mat img = imread("H:\\test\\test.jpg");
	if (img.empty())
	{
		MessageBox(_T("读取文件失败！"));
		return;
	}
	else
	{
		
	}
	MatToBMP mtb(img);
	m_Picture.SetBitmap(mtb.mCreateDIBitmap(img));*/


	HBITMAP hBmp = (HBITMAP)LoadImageW(NULL, (WCHAR *)("C:\\Users\\Lee Xiaopeng\\Desktop\\Temp File\\图片1.bmp"), IMAGE_BITMAP, 800, 800, LR_LOADFROMFILE); //加载位图文件到位图对象
	m_Picture.SetBitmap(hBmp);


}
