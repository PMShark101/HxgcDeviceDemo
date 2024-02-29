
// HxgcDeviceDemoDlg.cpp : 实现文件
//
#include <iostream>
#include "stdafx.h"
#include "HxgcDeviceDemo.h"
#include "HxgcDeviceDemoDlg.h"
#include "afxdialogex.h"
#include "GFunctin.h"

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <boost/bind.hpp>
#include <json/include/nlohmann/json.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;
using websocketpp::connection_hdl;

std::set<connection_hdl, std::owner_less<connection_hdl>> connections;
server ws_server;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//Websocket
void CHxgcDeviceDemoDlg::InitWebSocketServer() {
    try {
        ws_server.set_access_channels(websocketpp::log::alevel::all);
        ws_server.clear_access_channels(websocketpp::log::alevel::frame_payload);

        ws_server.init_asio();
        ws_server.set_open_handler(bind(&CHxgcDeviceDemoDlg::OnOpen, this, ::_1));
        ws_server.set_close_handler(bind(&CHxgcDeviceDemoDlg::OnClose, this, ::_1));
        ws_server.set_message_handler(bind(&CHxgcDeviceDemoDlg::OnMessage, this, ::_1, ::_2));

        ws_server.listen(9002);
        ws_server.start_accept();

        //ws_server.run();
        // 注意：ws_server.run()将阻塞当前线程，您可能需要在新线程中调用它
        std::thread([this]() { ws_server.run(); }).detach();
    }
    catch (websocketpp::exception const& e) {
        std::cerr << e.what() << std::endl;
    }
}

void CHxgcDeviceDemoDlg::OnOpen(connection_hdl hdl) {
    connections.insert(hdl);
}

void CHxgcDeviceDemoDlg::OnClose(connection_hdl hdl) {
    connections.erase(hdl);
}

void CHxgcDeviceDemoDlg::OnMessage(connection_hdl hdl, server::message_ptr msg) {
    // 可以在这里处理来自客户端的消息
}

void CHxgcDeviceDemoDlg::SendMessageToClients(const std::string& message) {
    for (auto it : connections) {
        ws_server.send(it, message, websocketpp::frame::opcode::text);
    }
}

// CHxgcDeviceDemoDlg 对话框
#define DEF_PHOTO_BMP_FILE_NAME _T("zp1.bmp")

CHxgcDeviceDemoDlg::CHxgcDeviceDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHxgcDeviceDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    InitParam();
}

void CHxgcDeviceDemoDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_DEV_PORT, m_combo_dev_port);
    DDX_Control(pDX, IDC_COMBO_DEV_BAUD, m_combo_dev_baud);
}

BEGIN_MESSAGE_MAP(CHxgcDeviceDemoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CHxgcDeviceDemoDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &CHxgcDeviceDemoDlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_BUTTON_IDCARD_READ, &CHxgcDeviceDemoDlg::OnBnClickedButtonIdcardRead)
    ON_BN_CLICKED(IDC_BUTTON_IDCARD_CLEAR, &CHxgcDeviceDemoDlg::OnBnClickedButtonIdcardClear)
END_MESSAGE_MAP()


// CHxgcDeviceDemoDlg 消息处理程序

BOOL CHxgcDeviceDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    int iPos = 0;
    CString strTemp;

    //设置二代证COMBO控件数据项显示内容
    m_combo_dev_port.InsertString(iPos, _T("USB"));

    //循环设置COM内容和对应数值，COM端口为1~16
    for(iPos = 1; iPos <= 16; iPos++)   
    {
        strTemp.Format(_T("COM%02d"), iPos);
        m_combo_dev_port.InsertString(iPos, strTemp);
    }
    m_combo_dev_port.SetCurSel(0);//默认USB口

    //设置波特率COMBO控件数据项显示内容
    iPos = 0;
    m_combo_dev_baud.InsertString(iPos, _T("115200"));
    m_combo_dev_baud.SetItemData(iPos++, 115200);
    m_combo_dev_baud.InsertString(iPos, _T("57600"));
    m_combo_dev_baud.SetItemData(iPos++, 57600);
    m_combo_dev_baud.InsertString(iPos, _T("38400"));
    m_combo_dev_baud.SetItemData(iPos++, 38400);
    m_combo_dev_baud.InsertString(iPos, _T("19200"));
    m_combo_dev_baud.SetItemData(iPos++, 19200);
    m_combo_dev_baud.InsertString(iPos, _T("9600"));
    m_combo_dev_baud.SetItemData(iPos++, 9600);
    m_combo_dev_baud.SetCurSel(0);//默认115200

    //加载相关动态库
    if(!LoadSubModule())
    {
        MessageBox(_T("加载相关动态库失败."), _T("错误"), MB_ICONERROR);
        SendMessage(WM_CLOSE, NULL, NULL);//加载失败关闭对话框
    }
    InitWebSocketServer();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHxgcDeviceDemoDlg::OnPaint()
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

    RECT rectTemp;
    CDC* pDC = GetDC();
    if (m_bPhotoEnable)
    {
        GetDlgItem(IDC_STATIC_IDCARD_PHOTO)->GetWindowRect(&rectTemp);
        ScreenToClient(&rectTemp);

        DrawPhotoBmpFormFile(DEF_PHOTO_BMP_FILE_NAME, pDC, rectTemp);
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHxgcDeviceDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CHxgcDeviceDemoDlg::InitParam()
{
    m_hSubModuleA = NULL;
    m_hSubModuleB = NULL;
    m_bSubModEnable = false;
    m_bPhotoEnable = false;
    m_pfn_SDT_GetCOMBaud = NULL;
    m_pfn_SDT_SetCOMBaud = NULL;
    m_pfn_SDT_StartFindIDCard = NULL;
    m_pfn_SDT_SelectIDCard = NULL;
    m_pfn_SDT_ReadBaseMsg = NULL;
    m_pfn_SDT_ReadBaseFPMsg = NULL;
    m_pfn_SDT_GetSAMIDToStr = NULL;
    m_pfn_SDT_ReadNewAppMsg = NULL;

    m_pfn_unpack = NULL;
}

bool CHxgcDeviceDemoDlg::LoadSubModule()
{
    bool bRet = false;

    do 
    {
        if(m_bSubModEnable)//判断动态库是否已加载
        {
            bRet = true;
            break;
        }

        m_hSubModuleA = LoadLibrary(_T("sdtapi.dll"));//加载J10设备动态库
        if(NULL == m_hSubModuleA)
        {
            break;
        }

        //二代证相关API---------------------------------------------------------------------------------------
        m_pfn_SDT_GetCOMBaud = (PF_SDT_GetCOMBaud)GetProcAddress(m_hSubModuleA, "SDT_GetCOMBaud");
        if(NULL == m_pfn_SDT_GetCOMBaud)
        {
            break;
        }

        m_pfn_SDT_SetCOMBaud = (PF_SDT_SetCOMBaud)GetProcAddress(m_hSubModuleA, "SDT_SetCOMBaud");
        if(NULL == m_pfn_SDT_SetCOMBaud)
        {
            break;
        }

        m_pfn_SDT_StartFindIDCard = (PF_SDT_StartFindIDCard)GetProcAddress(m_hSubModuleA, "SDT_StartFindIDCard");
        if(NULL == m_pfn_SDT_StartFindIDCard)
        {
            break;
        }

        m_pfn_SDT_SelectIDCard = (PF_SDT_SelectIDCard)GetProcAddress(m_hSubModuleA, "SDT_SelectIDCard");
        if(NULL == m_pfn_SDT_SelectIDCard)
        {
            break;
        }

        m_pfn_SDT_ReadBaseMsg = (PF_SDT_ReadBaseMsg)GetProcAddress(m_hSubModuleA, "SDT_ReadBaseMsg");
        if(NULL == m_pfn_SDT_ReadBaseMsg)
        {
            break;
        }

        m_pfn_SDT_ReadBaseFPMsg = (PF_SDT_ReadBaseFPMsg)GetProcAddress(m_hSubModuleA, "SDT_ReadBaseFPMsg");
        if(NULL == m_pfn_SDT_ReadBaseFPMsg)
        {
            break;
        }

        m_pfn_SDT_GetSAMIDToStr = (PF_SDT_GetSAMIDToStr)GetProcAddress(m_hSubModuleA, "SDT_GetSAMIDToStr");
        if(NULL == m_pfn_SDT_GetSAMIDToStr)
        {
            break;
        }

        m_pfn_SDT_ReadNewAppMsg = (PF_SDT_ReadNewAppMsg)GetProcAddress(m_hSubModuleA, "SDT_ReadNewAppMsg");
        if(NULL == m_pfn_SDT_ReadNewAppMsg)
        {
            break;
        }

        //照片解码API---------------------------------------------------------------------------------------
        m_hSubModuleB = LoadLibrary(_T("DLL_File.dll"));
        if(NULL == m_hSubModuleA)
        {
            break;
        }

        m_pfn_unpack = (PF_unpack)GetProcAddress(m_hSubModuleB, "unpack");
        if(NULL == m_pfn_unpack)
        {
            break;
        }

        bRet = true;

    } while (0);

    if(!bRet)
    {
        FreeSubModule();
    }

    return bRet;
}

void CHxgcDeviceDemoDlg::FreeSubModule()
{
    if(NULL != m_hSubModuleA)
    {
        FreeLibrary(m_hSubModuleA);
        m_hSubModuleA = NULL;

        m_pfn_SDT_StartFindIDCard = NULL;
        m_pfn_SDT_SelectIDCard = NULL;
        m_pfn_SDT_ReadBaseMsg = NULL;
        m_pfn_SDT_ReadBaseFPMsg = NULL;
        m_pfn_SDT_GetSAMIDToStr = NULL;
        m_pfn_SDT_ReadNewAppMsg = NULL;
    }

    if(NULL != m_hSubModuleB)
    {
        FreeLibrary(m_hSubModuleB);
        m_hSubModuleB = NULL;

        m_pfn_unpack = NULL;
    }
}

int CHxgcDeviceDemoDlg::GetPortNum()
{
    int iPort = m_combo_dev_port.GetCurSel();

    if(0 == iPort)  //是否为USB口
    {
        iPort = 1001;
    }

    return iPort;
}


int CHxgcDeviceDemoDlg::GetPortBaud()
{
    int iPos = m_combo_dev_baud.GetCurSel();
    int iBaud = m_combo_dev_baud.GetItemData(iPos);

    return iBaud;
}

void CHxgcDeviceDemoDlg::DrawPhotoBmpFormFile(const TCHAR* pi_ptszBmpFilePath, CDC *pi_pDC, CRect pi_rect)
{
    HANDLE hBitmap = ::LoadImage(NULL, pi_ptszBmpFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//从文件加载图像
    if (NULL == hBitmap)
    {
        return;
    }

    CBitmap bmpMem;
    if (bmpMem.Attach(hBitmap))
    {
        BITMAP bmpInfo;
        CDC dcMem;
        bmpMem.GetBitmap(&bmpInfo);
        dcMem.CreateCompatibleDC(pi_pDC);//依附窗口DC创建兼容内存DC
        CBitmap* pbmpHode = dcMem.SelectObject(&bmpMem);//内存DC加载BMP

        COLORREF clrRgb = GetPixel(dcMem, 1, 1);//取1,1像素颜色，用于遮蔽照片周围白色
        BYTE byR = GetRValue(clrRgb);
        BYTE byG = GetGValue(clrRgb);
        BYTE byB = GetBValue(clrRgb);

        pi_pDC->SetStretchBltMode(HALFTONE);//设置粘贴像素模式
        pi_pDC->TransparentBlt(pi_rect.left, pi_rect.top, pi_rect.Width(), pi_rect.Height(), &dcMem, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(byR, byG, byB));

        //清理
        dcMem.SelectObject(pbmpHode);
        bmpMem.Detach();
        dcMem.DeleteDC();
    }

    DeleteObject(hBitmap);
}

void CHxgcDeviceDemoDlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    //CDialogEx::OnOK();
}


void CHxgcDeviceDemoDlg::OnBnClickedCancel()
{
    // TODO: 在此添加控件通知处理程序代码
    FreeSubModule();

    CDialogEx::OnCancel();
}


void CHxgcDeviceDemoDlg::OnBnClickedButtonIdcardRead()
{
    // TODO: 在此添加控件通知处理程序代码
    int iPort = 0;
    int iResult = 0;
    int iIfOpen = 1;//自动打开设备标志。如果设置为1，则在接口内部自动实现打开设备和关闭设备，无需调用者再添加。
    CString strMsg = _T("");
    CString strIDBase = _T("");

    char szSAMID[64 + 1] = {0};

    unsigned char byCHMsg[256 + 1] = {0};      //个人基本信息
    unsigned int uiCHMsgSize = 0;               //个人基本信息字节数
    unsigned char byPHMsg[1024 + 1] = {0};     //照片信息
    unsigned int uiPHMsgSize = 0;	            //照片信息字节数
    unsigned char byFPMsg[1024 + 1] = {0};     //指纹信息
    unsigned int uiFPMsgSize = 0;               //指纹信息字节数

    wchar_t wszName[15 + 1] = {0};          //姓名
    wchar_t wszSex[1 + 1] = {0};            //性别
    wchar_t wszNation[2 + 1] = {0};         //民族
    wchar_t wszBirth[8 + 1] = {0};         //出生日期
    wchar_t wszAddr[35 + 1] = {0};          //地址
    wchar_t wszID[18 + 1] = {0};            //身份证号
    wchar_t wszDept[15 + 1] = {0};          //签发机关
    wchar_t wszStart[8 + 1] = {0};         //有效期起始
    wchar_t wszEnd[8 + 1] = {0};           //有效期截至
    wchar_t BitmapFilePath[256 + 1] = {0};


//     int iPhotoWidth = 102;  //图片宽（像素）
//     int iPhotoHeight = 126; //图片高（像素）
    int iIsSaveToBmp = 0;

    unsigned char byBgrBuffer[38556] = {0};    //解码后图片BGR编码值
    unsigned char byBmpBuffer[38862] = {0};    //解码后图片RGB编码值

    m_bPhotoEnable = false;

    unsigned int uiDevBaud = 0;
    unsigned int uiCurBaud = 0;

    do 
    {
        iPort = GetPortNum();       //获得端口号
        ////////////////////////////////////////////////////////////////////
        //以下为串口波特率设置
        if((iPort <= 16) && (iPort >= 1))//是否为串口
        {
            uiCurBaud = GetPortBaud();  //获得当前波特率
            uiDevBaud = uiCurBaud;
            iResult = m_pfn_SDT_SetCOMBaud(iPort, uiDevBaud, uiCurBaud);//尝试设置设备波特率，判断设备波特率和当前波特率是否相同
            if(0x90 != iResult)
            {
                //设置失败，说明波特率拨通，获取设备波特率,
                iResult = m_pfn_SDT_GetCOMBaud(iPort, &uiDevBaud);
                if(0x90 != iResult)
                {
                    break;
                }

                //修改设备波特率
                iResult = m_pfn_SDT_SetCOMBaud(iPort, uiDevBaud, uiCurBaud);
                if(0x90 != iResult)
                {
                    break;
                }
            }
        }

#if 1
        //获得设备SAM模块ID。
        //PS ：SAM模块ID为二代证设备唯一标志ID；
        //PS2：此函通常用来数来区分设备或判断设备是否连接正常；若只读卡信息的话无需添加此函数。
        iResult = m_pfn_SDT_GetSAMIDToStr(iPort, szSAMID, iIfOpen);
        if(0x90 != iResult)
        {
            strMsg.Format(_T("获取SAMID号失败.ErrCode = %d"), iResult);
            MessageBox(strMsg, _T("错误"), MB_ICONERROR);
            break;
        }
#endif

        unsigned char byManaID[8] = {0};

        //寻卡
        iResult = m_pfn_SDT_StartFindIDCard(iPort, byManaID, iIfOpen);
        if(0x9F != iResult)
        {
            strMsg.Format(_T("寻卡失败.ErrCode = %d"), iResult);
            MessageBox(strMsg, _T("错误"), MB_ICONERROR);
            break;
        }

        //选卡
        memset(byManaID, 0, sizeof(byManaID));
        iResult = m_pfn_SDT_SelectIDCard(iPort, byManaID, iIfOpen);
        if(0x90 != iResult)
        {
            strMsg.Format(_T("选卡失败.ErrCode = %d"), iResult);
            MessageBox(strMsg, _T("错误"), MB_ICONERROR);
            break;
        }

        //读取身份证个人基本信息、照片信息和指纹信息；
        //PS：指纹信息需要专门的指纹比对设备，这里只获取加密的原始数据。
        iResult = m_pfn_SDT_ReadBaseFPMsg(iPort, byCHMsg, &uiCHMsgSize, byPHMsg, &uiPHMsgSize, byFPMsg, &uiFPMsgSize, iIfOpen);
        if(0x21 == iResult)//0501模块(一种老模块)无法读取指纹信息,会返回0x21错误，这里进行兼容处理；这种模块早就不用了，实际可以不做处理。
        {
            iResult = m_pfn_SDT_ReadBaseMsg(iPort, byCHMsg, &uiCHMsgSize, byPHMsg, &uiPHMsgSize, iIfOpen);//采用只读卡信息和照片，不读指纹信息的接口
        }
        if(0x90 != iResult)
        {
            strMsg.Format(_T("读取身份信息失败.ErrCode = %d"), iResult);
            MessageBox(strMsg, _T("错误"), MB_ICONERROR);
            break;
        }

        //解码照片数据，获得BGR格式数据
        //iIsSaveToBmp = 1;     //调用解码库unpack函数后，由接口自动生成名为zp.bmp的图片文件，该BMP文件可直接打开，不用B、R转换
        iIsSaveToBmp = 0;       //不自动生成zp.bmp图片

        //PS    ：解码库需要依赖授权文件（license.dat）；要确保“当前工作目录下”license.dat文件存在且正确，否则会返回-22和-12的错误
        //PS2   ：若设置iIsSaveToBmp = 1，即由接口自动生成zp.bmp文件，请确认“当前工作目录”具有写权限，否侧接口会崩溃（WIN7以上系统需注意此项）
        iResult = m_pfn_unpack((char*)byPHMsg, (char*)byBgrBuffer, iIsSaveToBmp);
        if(1 != iResult)
        {
            strMsg.Format(_T("照片解码失败.ErrCode = %d"), iResult);
            MessageBox(strMsg, _T("错误"), MB_ICONERROR);
            break;
        }

        if(0 == iIsSaveToBmp)//不自动生成zp.bmp图片，需要对解码后的数据进行B、R转换
        {
            //拼接BMP图片格式头，14字节
            unsigned char byBmpHead[14] = {0x42,0x4D,0xCE,0x97,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00};
            memcpy_s(&byBmpBuffer[0], sizeof(byBmpBuffer), byBmpHead, 14);

            //拼接BMP图像信息40字节                          
            unsigned char byBmpInfo[40] = {0x28,0x00,0x00,0x00,//结构所占用40字节    
                0x66,0x00,0x00,0x00,//位图的宽度102像素
                0x7E,0x00,0x00,0x00,//位图的高度126像素
                0x01,0x00,          //目标设备的级别必须为1
                0x18,0x00,          //每个像素所需的位数24
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00//......其他信息省略为0
            };
            memcpy_s(&byBmpBuffer[14], sizeof(byBmpBuffer) - 14, byBmpInfo, 40);

            //将解码后的BGR格式数据进行B、R互换，拼接接到BmpBuffer图像信息后面
            int iRgbSize = sizeof(byBmpBuffer) - 54;
            iResult = bgr2rgb((unsigned char*)byBgrBuffer, sizeof(byBgrBuffer), &byBmpBuffer[54], iRgbSize, 102, 126);
            if(0 != iResult)
            {
                MessageBox(_T("照片数据B、R互换失败."), _T("错误"), MB_ICONERROR);
                break;
            }

            //写入文件
            int iBmpSize = 54 + iRgbSize;
            iResult = tool_WriteOneFile(DEF_PHOTO_BMP_FILE_NAME, byBmpBuffer, iBmpSize);
            if(iResult != iBmpSize)
            {
                MessageBox(_T("保存照片数据失败."), _T("错误"), MB_ICONERROR);
                break;
            }
            m_bPhotoEnable = true;
        }

        //截取个人信息数据。信息采用UNICODE存储，具体格式参可见《二代证机读信息说明.doc》
        memcpy_s(wszName,     sizeof(wszName),     &byCHMsg[0],   30);
        memcpy_s(wszSex,      sizeof(wszSex),      &byCHMsg[30],  2);
        memcpy_s(wszNation,   sizeof(wszNation),   &byCHMsg[32],  4);
        memcpy_s(wszBirth,    sizeof(wszBirth),    &byCHMsg[36],  16);
        memcpy_s(wszAddr,     sizeof(wszAddr),     &byCHMsg[52],  70);
        memcpy_s(wszID,       sizeof(wszID),       &byCHMsg[122], 36);
        memcpy_s(wszDept,     sizeof(wszDept),     &byCHMsg[158], 30);
        memcpy_s(wszStart,    sizeof(wszStart),    &byCHMsg[188], 16);
        memcpy_s(wszEnd,      sizeof(wszEnd),      &byCHMsg[204], 16);

        strIDBase = _T("读卡成功.\r\n\r\n");

#ifdef UNICODE
        //编译环境使用Unicode字符集
        strMsg.Format(L"姓名：%s\r\n\r\n", wszName);
        strIDBase += strMsg;
        strMsg.Format(L"性别：%s\r\n\r\n", wszSex);
        strIDBase += strMsg;
        strMsg.Format(L"民族：%s\r\n\r\n", wszNation);
        strIDBase += strMsg;
        strMsg.Format(L"出生：%s\r\n\r\n", wszBirth);
        strIDBase += strMsg;
        strMsg.Format(L"住址：%s\r\n\r\n", wszAddr);
        strIDBase += strMsg;
        strMsg.Format(L"身份证号：%s\r\n\r\n", wszID);
        strIDBase += strMsg;
        strMsg.Format(L"签发机关：%s\r\n\r\n", wszDept);
        strIDBase += strMsg;
        strMsg.Format(L"有效期起始：%s\r\n\r\n", wszStart);
        strIDBase += strMsg;
        strMsg.Format(L"有效期起始：%s\r\n\r\n", wszEnd);
        strIDBase += strMsg;
#else
        //编译环境使用多字节字符集,需要进行字符转换
        char szTemp[128 + 1] = {0};
        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszName, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("姓名：%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszSex, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("性别：%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszNation, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("民族：%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszBirth, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("出生：%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszAddr, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("住址：%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszID, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("身份证号：%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszDept, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("签发机关：%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszStart, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("有效期起始：%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszEnd, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("有效期结束：%s\r\n\r\n", szTemp);
        strIDBase += strMsg;
#endif

    } while (0);

    SetDlgItemText(IDC_EDIT_IDCARD_DATA, strIDBase);

    CRect rectTemp;
    GetDlgItem(IDC_STATIC_IDCARD_PHOTO)->GetWindowRect(&rectTemp);
    ScreenToClient(&rectTemp);
    InvalidateRect(rectTemp);//刷新以显示图片

    CString cstr = _T("身份证信息: ") + strIDBase; // 假设strIDBase是一个CString
    std::wstring wStr(cstr.GetString());
    std::string stdStr(wStr.begin(), wStr.end()); // 直接转换可能丢失非ASCII字符

    // 使用nlohmann/json库构造JSON对象
    nlohmann::json j;
    j["姓名"] = CW2A(wszName, CP_UTF8);
    j["性别"] = CW2A(wszSex, CP_UTF8);
    j["民族"] = CW2A(wszNation, CP_UTF8);
    j["出生日期"] = CW2A(wszBirth, CP_UTF8);
    j["住址"] = CW2A(wszAddr, CP_UTF8);
    j["身份证号"] = CW2A(wszID, CP_UTF8);
    j["签发机关"] = CW2A(wszDept, CP_UTF8);
    j["有效期起始"] = CW2A(wszStart, CP_UTF8);
    j["有效期截至"] = CW2A(wszEnd, CP_UTF8);
    std::string message = j.dump();
    SendMessageToClients(stdStr);
}


void CHxgcDeviceDemoDlg::OnBnClickedButtonIdcardClear()
{
    // TODO: 在此添加控件通知处理程序代码
    m_bPhotoEnable = false;

    SetDlgItemText(IDC_EDIT_IDCARD_DATA, _T(""));

    CRect rectTemp;
    GetDlgItem(IDC_STATIC_IDCARD_PHOTO)->GetWindowRect(&rectTemp);
    ScreenToClient(&rectTemp);
    InvalidateRect(rectTemp);//刷新以显示图片
}

CHxgcDeviceDemoDlg::~CHxgcDeviceDemoDlg() {
    // 在这里清理任何资源，比如动态分配的内存、打开的文件句柄等
}
