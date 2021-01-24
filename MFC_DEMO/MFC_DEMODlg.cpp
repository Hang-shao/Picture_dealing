// MFC_DEMODlg.cpp : 实现文件
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio/videoio.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include <opencv2\tracking.hpp>
#include <stdio.h>
#include <string>
#include "stdafx.h"
#include "MFC_DEMO.h"
#include "MFC_DEMODlg.h"
#include "afxdialogex.h"
#include "NewForm.h"
#include "newform2.h"
#include "newform6.h"


//#include "CEncryptionMFCDlg.h"
using namespace cv;
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
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
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFC_DEMODlg 对话框
CMFC_DEMODlg::CMFC_DEMODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_DEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_DEMODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_DEMODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32774, &CMFC_DEMODlg::On32774)
	ON_COMMAND(ID_32789, &CMFC_DEMODlg::On32789)
	ON_COMMAND(ID_32790, &CMFC_DEMODlg::On32790)
	ON_COMMAND(ID_32794, &CMFC_DEMODlg::On32794)
	ON_COMMAND(ID_32795, &CMFC_DEMODlg::On32795)
	ON_COMMAND(ID_32796, &CMFC_DEMODlg::On32796)
	ON_COMMAND(ID_32798, &CMFC_DEMODlg::On32798)
	ON_STN_CLICKED(IDCANCEL, &CMFC_DEMODlg::OnStnClickedCancel)
	ON_COMMAND(ID_32799, &CMFC_DEMODlg::On32799)
	ON_COMMAND(ID_32793, &CMFC_DEMODlg::On32793)
	ON_COMMAND(ID_32807, &CMFC_DEMODlg::On32807)   //直方图
	ON_COMMAND(ID_32815, &CMFC_DEMODlg::On32815)   //加密
	ON_COMMAND(ID_32826, &CMFC_DEMODlg::On32826)   //实时图像边缘检测
	ON_COMMAND(ID_32811, &CMFC_DEMODlg::On32811)
	ON_COMMAND(ID_32816, &CMFC_DEMODlg::On32816) // 退出
	ON_COMMAND(ID_32812, &CMFC_DEMODlg::On32812)
	ON_COMMAND(ID_32813, &CMFC_DEMODlg::On32813)
	ON_COMMAND(ID_32814, &CMFC_DEMODlg::On32814)
	ON_COMMAND(ID_32819, &CMFC_DEMODlg::VIDEO_deal_fun)  //打开摄像头
	ON_COMMAND(ID_32820, &CMFC_DEMODlg::On32820)  //清理背景分割结果
	ON_COMMAND(ID_32821, &CMFC_DEMODlg::On32821)  //灰度化
	ON_COMMAND(ID_32822, &CMFC_DEMODlg::On32822)  //模糊化

	//ON_COMMAND(ID_32825, &CMFC_DEMODlg::On32825)  //打开视频
END_MESSAGE_MAP()


// CMFC_DEMODlg 消息处理程序

BOOL CMFC_DEMODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMenu menu;

	menu.LoadMenuA(IDR_MENU2);
	SetMenu(&menu);

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO: 在此添加额外的初始化代码
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	namedWindow("view2", WINDOW_AUTOSIZE);
	HWND hWnd2 = (HWND)cvGetWindowHandle("view2");
	HWND hParent2 = ::GetParent(hWnd2);
	::SetParent(hWnd2, GetDlgItem(IDD_DIALOG1)->m_hWnd);
	::ShowWindow(hParent2, SW_HIDE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC_DEMODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC_DEMODlg::OnPaint()
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
HCURSOR CMFC_DEMODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//显示到第一个Pic控件
void CMFC_DEMODlg::ShowPic_1(Mat input_1)
{
	Mat imagedst; // Mat是在矩阵中存储图片的数据结构
	CRect rect;  //定义矩阵类，记录一个矩形信息（四个坐标点等）
	/* GetDlgItem(IDC_STATIC)：获取控件IDC_STATIC句柄
	   GetClientRect(&rect)：获取句柄指向控件区域的大小
	*/
	GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
	//获取图像大小（长、宽、高等）
	Rect dst(rect.left, rect.top, rect.right, rect.bottom); 
	//调整图像大小，含有格式转换
	resize(input_1, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
}
//显示到第二个Pic控件
void CMFC_DEMODlg::ShowPic_2(Mat input_2)
{
	Mat imagedst;
	CRect rect2;
	GetDlgItem(IDD_DIALOG1)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input_2, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view2", imagedst);
}

//打开
void CMFC_DEMODlg::On32774()
{
    open2();
}
//退出
void CMFC_DEMODlg::On32816()
{
	OnCancel();
}

//另存为
void CMFC_DEMODlg::On32811()
{
	// TODO: 在此添加命令处理程序代码
	save2();
}
void CMFC_DEMODlg::OnCancel()
{
	DestroyWindow();
	//exit(0);
	CDialogEx::OnCancel();
}
// 实时视频处理
static void refineSegments(const Mat& img, Mat& mask, Mat& dst);
void CMFC_DEMODlg::VIDEO_deal_fun()
{
	bool update_bg_model = true;
	Mat tmp_frame, bgmask, out_frame, foreground, bw, gray;;
	cap.open(0);
	if (!cap.isOpened())
	{
		AfxMessageBox("打开摄像头失败！");
		exit(-1);
	}
	cap >> tmp_frame;
	if (tmp_frame.empty())
	{
		AfxMessageBox("读取帧失败！");
		exit(-1);
	}
	Ptr<BackgroundSubtractorMOG2> bgsubtractor = createBackgroundSubtractorMOG2();
	bgsubtractor->setVarThreshold(10);
	for (;;)
	{
		cap >> tmp_frame;
		if (tmp_frame.empty())
			break;
		bgsubtractor->apply(tmp_frame, bgmask, update_bg_model ? -1 : 0);
		ShowPic_1(tmp_frame);
		if (num_32820 == 1)
		{
			refineSegments(tmp_frame, bgmask, out_frame); // 背景分割
			ShowPic_2(out_frame);
		}
		else if (num_32821 == 1)
		{
			cvtColor(tmp_frame, out_frame, CV_BGR2GRAY); //灰度化
			ShowPic_2(out_frame);
		}
		else if (num_32822 == 1)
		{
			blur(tmp_frame, out_frame, Size(7, 7));//模糊化
			ShowPic_2(out_frame);
		}
		else if (num_32826 == 1)
		{
			GaussianBlur(tmp_frame, out_frame, cvSize(3,3), 2, 2, BORDER_DEFAULT);//高斯平滑
			Canny(tmp_frame, out_frame,20,100,3);//边缘检测
			ShowPic_2(out_frame);
		}
		else 
		{
			printf("OK!");
		}
		waitKey(30);
	}
	cap.release();//释放资源
}

/*模糊化*/
void CMFC_DEMODlg::On32822()
{
	num_32822 = 1;
}

/*灰度化*/
void CMFC_DEMODlg::On32821()
{
	num_32821 = 1;
}

/*清理背景分割结果*/
void CMFC_DEMODlg::On32820()
{
	num_32820 = 1;
}
static void refineSegments(const Mat& img, Mat& mask, Mat& dst)
{
	int niters = 3;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Mat temp;
	dilate(mask, temp, Mat(), Point(-1, -1), niters);  // 膨胀：求核区域像素最大值，可以填补凹洞
	erode(temp, temp, Mat(), Point(-1, -1), niters * 2); // 腐蚀：求核区域最小值，能消除凸起
	dilate(temp, temp, Mat(), Point(-1, -1), niters);  // 膨胀：求核区域像素最大值，可以填补凹洞
	/*findContours( InputOutputArray image, OutputArrayOfArrays contours,
					OutputArray hierarchy, int mode,  
                    int method, Point offset=Point());
	*/
	findContours(temp, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);  // 轮廓提取
	dst = Mat::zeros(img.size(), CV_8UC3);
	if (contours.size() == 0)
		return;
	int idx = 0, largestComp = 0;
	double maxArea = 0;
	for (; idx >= 0; idx = hierarchy[idx][0])
	{
		const vector<Point>& c = contours[idx];
		double area = fabs(contourArea(Mat(c)));  // 求绝对值
		if (area > maxArea)
		{
			maxArea = area;
			largestComp = idx;
		}
	}
	Scalar color(0, 0, 255); //将图像设置成单一灰度和颜色
	drawContours(dst, contours, largestComp, color, FILLED, LINE_8, hierarchy); // 轮廓填充
}

//灰度化
void CMFC_DEMODlg::On32789()
{
	// TODO: 在此添加命令处理程序代码
	out=ImageGray1();
	ShowPic_2(out);
}

//二值化
void CMFC_DEMODlg::On32790()
{
	ImageEZH1();		
}

//均值滤波
void CMFC_DEMODlg::On32794()
{
	ImageJZ1();
}

//高斯滤波
void CMFC_DEMODlg::On32795()
{
	// TODO: 在此添加命令处理程序代码
	 ImageGS1();
}

//拉普拉斯滤波
void CMFC_DEMODlg::On32796()
{
	// TODO: 在此添加命令处理程序代码
	out = ImageLPLS1();
	ShowPic_2(out);

}

//canny算子
void CMFC_DEMODlg::On32798()
{
	 ImageCANNY1();
}

void CMFC_DEMODlg::OnStnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
}

//sobel算子
void CMFC_DEMODlg::On32799()
{
	// TODO: 在此添加命令处理程序代码
	 ImageSOBEL();
}

//直方图
void CMFC_DEMODlg::On32807()
{
	// TODO: 在此添加命令处理程序代码
	SonWnd_2.WndCreate(this);
}
//混沌加密
void CMFC_DEMODlg::On32815()
{
	// TODO: 在此添加命令处理程序代码
	SonWnd_3.WndCreate(this);
}
//频域滤波
void CMFC_DEMODlg::On32793()
{
	// TODO: 在此添加命令处理程序代码
	SonWnd.WndCreate2(this);
}

//实时图像边缘检测
void CMFC_DEMODlg::On32826()
{
	num_32826 = 1;
}

//彩色线性
void CMFC_DEMODlg::On32812()
{
	// TODO: 在此添加命令处理程序代码
	ImageHUIDU();
}

//灰度分段线性
void CMFC_DEMODlg::On32813()
{
	// TODO: 在此添加命令处理程序代码
	ImageHUIDU_2();
}

//灰度非线性
void CMFC_DEMODlg::On32814()
{
	// TODO: 在此添加命令处理程序代码
	ImageHUIDU_3();
}