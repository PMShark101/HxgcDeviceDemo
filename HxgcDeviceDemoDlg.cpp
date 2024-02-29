
// HxgcDeviceDemoDlg.cpp : ʵ���ļ�
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
        // ע�⣺ws_server.run()��������ǰ�̣߳���������Ҫ�����߳��е�����
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
    // ���������ﴦ�����Կͻ��˵���Ϣ
}

void CHxgcDeviceDemoDlg::SendMessageToClients(const std::string& message) {
    for (auto it : connections) {
        ws_server.send(it, message, websocketpp::frame::opcode::text);
    }
}

// CHxgcDeviceDemoDlg �Ի���
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


// CHxgcDeviceDemoDlg ��Ϣ�������

BOOL CHxgcDeviceDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    int iPos = 0;
    CString strTemp;

    //���ö���֤COMBO�ؼ���������ʾ����
    m_combo_dev_port.InsertString(iPos, _T("USB"));

    //ѭ������COM���ݺͶ�Ӧ��ֵ��COM�˿�Ϊ1~16
    for(iPos = 1; iPos <= 16; iPos++)   
    {
        strTemp.Format(_T("COM%02d"), iPos);
        m_combo_dev_port.InsertString(iPos, strTemp);
    }
    m_combo_dev_port.SetCurSel(0);//Ĭ��USB��

    //���ò�����COMBO�ؼ���������ʾ����
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
    m_combo_dev_baud.SetCurSel(0);//Ĭ��115200

    //������ض�̬��
    if(!LoadSubModule())
    {
        MessageBox(_T("������ض�̬��ʧ��."), _T("����"), MB_ICONERROR);
        SendMessage(WM_CLOSE, NULL, NULL);//����ʧ�ܹرնԻ���
    }
    InitWebSocketServer();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHxgcDeviceDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
        if(m_bSubModEnable)//�ж϶�̬���Ƿ��Ѽ���
        {
            bRet = true;
            break;
        }

        m_hSubModuleA = LoadLibrary(_T("sdtapi.dll"));//����J10�豸��̬��
        if(NULL == m_hSubModuleA)
        {
            break;
        }

        //����֤���API---------------------------------------------------------------------------------------
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

        //��Ƭ����API---------------------------------------------------------------------------------------
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

    if(0 == iPort)  //�Ƿ�ΪUSB��
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
    HANDLE hBitmap = ::LoadImage(NULL, pi_ptszBmpFilePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);//���ļ�����ͼ��
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
        dcMem.CreateCompatibleDC(pi_pDC);//��������DC���������ڴ�DC
        CBitmap* pbmpHode = dcMem.SelectObject(&bmpMem);//�ڴ�DC����BMP

        COLORREF clrRgb = GetPixel(dcMem, 1, 1);//ȡ1,1������ɫ�������ڱ���Ƭ��Χ��ɫ
        BYTE byR = GetRValue(clrRgb);
        BYTE byG = GetGValue(clrRgb);
        BYTE byB = GetBValue(clrRgb);

        pi_pDC->SetStretchBltMode(HALFTONE);//����ճ������ģʽ
        pi_pDC->TransparentBlt(pi_rect.left, pi_rect.top, pi_rect.Width(), pi_rect.Height(), &dcMem, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(byR, byG, byB));

        //����
        dcMem.SelectObject(pbmpHode);
        bmpMem.Detach();
        dcMem.DeleteDC();
    }

    DeleteObject(hBitmap);
}

void CHxgcDeviceDemoDlg::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    //CDialogEx::OnOK();
}


void CHxgcDeviceDemoDlg::OnBnClickedCancel()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    FreeSubModule();

    CDialogEx::OnCancel();
}


void CHxgcDeviceDemoDlg::OnBnClickedButtonIdcardRead()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    int iPort = 0;
    int iResult = 0;
    int iIfOpen = 1;//�Զ����豸��־���������Ϊ1�����ڽӿ��ڲ��Զ�ʵ�ִ��豸�͹ر��豸���������������ӡ�
    CString strMsg = _T("");
    CString strIDBase = _T("");

    char szSAMID[64 + 1] = {0};

    unsigned char byCHMsg[256 + 1] = {0};      //���˻�����Ϣ
    unsigned int uiCHMsgSize = 0;               //���˻�����Ϣ�ֽ���
    unsigned char byPHMsg[1024 + 1] = {0};     //��Ƭ��Ϣ
    unsigned int uiPHMsgSize = 0;	            //��Ƭ��Ϣ�ֽ���
    unsigned char byFPMsg[1024 + 1] = {0};     //ָ����Ϣ
    unsigned int uiFPMsgSize = 0;               //ָ����Ϣ�ֽ���

    wchar_t wszName[15 + 1] = {0};          //����
    wchar_t wszSex[1 + 1] = {0};            //�Ա�
    wchar_t wszNation[2 + 1] = {0};         //����
    wchar_t wszBirth[8 + 1] = {0};         //��������
    wchar_t wszAddr[35 + 1] = {0};          //��ַ
    wchar_t wszID[18 + 1] = {0};            //���֤��
    wchar_t wszDept[15 + 1] = {0};          //ǩ������
    wchar_t wszStart[8 + 1] = {0};         //��Ч����ʼ
    wchar_t wszEnd[8 + 1] = {0};           //��Ч�ڽ���
    wchar_t BitmapFilePath[256 + 1] = {0};


//     int iPhotoWidth = 102;  //ͼƬ�����أ�
//     int iPhotoHeight = 126; //ͼƬ�ߣ����أ�
    int iIsSaveToBmp = 0;

    unsigned char byBgrBuffer[38556] = {0};    //�����ͼƬBGR����ֵ
    unsigned char byBmpBuffer[38862] = {0};    //�����ͼƬRGB����ֵ

    m_bPhotoEnable = false;

    unsigned int uiDevBaud = 0;
    unsigned int uiCurBaud = 0;

    do 
    {
        iPort = GetPortNum();       //��ö˿ں�
        ////////////////////////////////////////////////////////////////////
        //����Ϊ���ڲ���������
        if((iPort <= 16) && (iPort >= 1))//�Ƿ�Ϊ����
        {
            uiCurBaud = GetPortBaud();  //��õ�ǰ������
            uiDevBaud = uiCurBaud;
            iResult = m_pfn_SDT_SetCOMBaud(iPort, uiDevBaud, uiCurBaud);//���������豸�����ʣ��ж��豸�����ʺ͵�ǰ�������Ƿ���ͬ
            if(0x90 != iResult)
            {
                //����ʧ�ܣ�˵�������ʲ�ͨ����ȡ�豸������,
                iResult = m_pfn_SDT_GetCOMBaud(iPort, &uiDevBaud);
                if(0x90 != iResult)
                {
                    break;
                }

                //�޸��豸������
                iResult = m_pfn_SDT_SetCOMBaud(iPort, uiDevBaud, uiCurBaud);
                if(0x90 != iResult)
                {
                    break;
                }
            }
        }

#if 1
        //����豸SAMģ��ID��
        //PS ��SAMģ��IDΪ����֤�豸Ψһ��־ID��
        //PS2���˺�ͨ���������������豸���ж��豸�Ƿ�������������ֻ������Ϣ�Ļ�������Ӵ˺�����
        iResult = m_pfn_SDT_GetSAMIDToStr(iPort, szSAMID, iIfOpen);
        if(0x90 != iResult)
        {
            strMsg.Format(_T("��ȡSAMID��ʧ��.ErrCode = %d"), iResult);
            MessageBox(strMsg, _T("����"), MB_ICONERROR);
            break;
        }
#endif

        unsigned char byManaID[8] = {0};

        //Ѱ��
        iResult = m_pfn_SDT_StartFindIDCard(iPort, byManaID, iIfOpen);
        if(0x9F != iResult)
        {
            strMsg.Format(_T("Ѱ��ʧ��.ErrCode = %d"), iResult);
            MessageBox(strMsg, _T("����"), MB_ICONERROR);
            break;
        }

        //ѡ��
        memset(byManaID, 0, sizeof(byManaID));
        iResult = m_pfn_SDT_SelectIDCard(iPort, byManaID, iIfOpen);
        if(0x90 != iResult)
        {
            strMsg.Format(_T("ѡ��ʧ��.ErrCode = %d"), iResult);
            MessageBox(strMsg, _T("����"), MB_ICONERROR);
            break;
        }

        //��ȡ���֤���˻�����Ϣ����Ƭ��Ϣ��ָ����Ϣ��
        //PS��ָ����Ϣ��Ҫר�ŵ�ָ�Ʊȶ��豸������ֻ��ȡ���ܵ�ԭʼ���ݡ�
        iResult = m_pfn_SDT_ReadBaseFPMsg(iPort, byCHMsg, &uiCHMsgSize, byPHMsg, &uiPHMsgSize, byFPMsg, &uiFPMsgSize, iIfOpen);
        if(0x21 == iResult)//0501ģ��(һ����ģ��)�޷���ȡָ����Ϣ,�᷵��0x21����������м��ݴ�������ģ����Ͳ����ˣ�ʵ�ʿ��Բ�������
        {
            iResult = m_pfn_SDT_ReadBaseMsg(iPort, byCHMsg, &uiCHMsgSize, byPHMsg, &uiPHMsgSize, iIfOpen);//����ֻ������Ϣ����Ƭ������ָ����Ϣ�Ľӿ�
        }
        if(0x90 != iResult)
        {
            strMsg.Format(_T("��ȡ�����Ϣʧ��.ErrCode = %d"), iResult);
            MessageBox(strMsg, _T("����"), MB_ICONERROR);
            break;
        }

        //������Ƭ���ݣ����BGR��ʽ����
        //iIsSaveToBmp = 1;     //���ý����unpack�������ɽӿ��Զ�������Ϊzp.bmp��ͼƬ�ļ�����BMP�ļ���ֱ�Ӵ򿪣�����B��Rת��
        iIsSaveToBmp = 0;       //���Զ�����zp.bmpͼƬ

        //PS    ���������Ҫ������Ȩ�ļ���license.dat����Ҫȷ������ǰ����Ŀ¼�¡�license.dat�ļ���������ȷ������᷵��-22��-12�Ĵ���
        //PS2   ��������iIsSaveToBmp = 1�����ɽӿ��Զ�����zp.bmp�ļ�����ȷ�ϡ���ǰ����Ŀ¼������дȨ�ޣ����ӿڻ������WIN7����ϵͳ��ע����
        iResult = m_pfn_unpack((char*)byPHMsg, (char*)byBgrBuffer, iIsSaveToBmp);
        if(1 != iResult)
        {
            strMsg.Format(_T("��Ƭ����ʧ��.ErrCode = %d"), iResult);
            MessageBox(strMsg, _T("����"), MB_ICONERROR);
            break;
        }

        if(0 == iIsSaveToBmp)//���Զ�����zp.bmpͼƬ����Ҫ�Խ��������ݽ���B��Rת��
        {
            //ƴ��BMPͼƬ��ʽͷ��14�ֽ�
            unsigned char byBmpHead[14] = {0x42,0x4D,0xCE,0x97,0x00,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x00,0x00};
            memcpy_s(&byBmpBuffer[0], sizeof(byBmpBuffer), byBmpHead, 14);

            //ƴ��BMPͼ����Ϣ40�ֽ�                          
            unsigned char byBmpInfo[40] = {0x28,0x00,0x00,0x00,//�ṹ��ռ��40�ֽ�    
                0x66,0x00,0x00,0x00,//λͼ�Ŀ��102����
                0x7E,0x00,0x00,0x00,//λͼ�ĸ߶�126����
                0x01,0x00,          //Ŀ���豸�ļ������Ϊ1
                0x18,0x00,          //ÿ�����������λ��24
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00//......������Ϣʡ��Ϊ0
            };
            memcpy_s(&byBmpBuffer[14], sizeof(byBmpBuffer) - 14, byBmpInfo, 40);

            //��������BGR��ʽ���ݽ���B��R������ƴ�ӽӵ�BmpBufferͼ����Ϣ����
            int iRgbSize = sizeof(byBmpBuffer) - 54;
            iResult = bgr2rgb((unsigned char*)byBgrBuffer, sizeof(byBgrBuffer), &byBmpBuffer[54], iRgbSize, 102, 126);
            if(0 != iResult)
            {
                MessageBox(_T("��Ƭ����B��R����ʧ��."), _T("����"), MB_ICONERROR);
                break;
            }

            //д���ļ�
            int iBmpSize = 54 + iRgbSize;
            iResult = tool_WriteOneFile(DEF_PHOTO_BMP_FILE_NAME, byBmpBuffer, iBmpSize);
            if(iResult != iBmpSize)
            {
                MessageBox(_T("������Ƭ����ʧ��."), _T("����"), MB_ICONERROR);
                break;
            }
            m_bPhotoEnable = true;
        }

        //��ȡ������Ϣ���ݡ���Ϣ����UNICODE�洢�������ʽ�οɼ�������֤������Ϣ˵��.doc��
        memcpy_s(wszName,     sizeof(wszName),     &byCHMsg[0],   30);
        memcpy_s(wszSex,      sizeof(wszSex),      &byCHMsg[30],  2);
        memcpy_s(wszNation,   sizeof(wszNation),   &byCHMsg[32],  4);
        memcpy_s(wszBirth,    sizeof(wszBirth),    &byCHMsg[36],  16);
        memcpy_s(wszAddr,     sizeof(wszAddr),     &byCHMsg[52],  70);
        memcpy_s(wszID,       sizeof(wszID),       &byCHMsg[122], 36);
        memcpy_s(wszDept,     sizeof(wszDept),     &byCHMsg[158], 30);
        memcpy_s(wszStart,    sizeof(wszStart),    &byCHMsg[188], 16);
        memcpy_s(wszEnd,      sizeof(wszEnd),      &byCHMsg[204], 16);

        strIDBase = _T("�����ɹ�.\r\n\r\n");

#ifdef UNICODE
        //���뻷��ʹ��Unicode�ַ���
        strMsg.Format(L"������%s\r\n\r\n", wszName);
        strIDBase += strMsg;
        strMsg.Format(L"�Ա�%s\r\n\r\n", wszSex);
        strIDBase += strMsg;
        strMsg.Format(L"���壺%s\r\n\r\n", wszNation);
        strIDBase += strMsg;
        strMsg.Format(L"������%s\r\n\r\n", wszBirth);
        strIDBase += strMsg;
        strMsg.Format(L"סַ��%s\r\n\r\n", wszAddr);
        strIDBase += strMsg;
        strMsg.Format(L"���֤�ţ�%s\r\n\r\n", wszID);
        strIDBase += strMsg;
        strMsg.Format(L"ǩ�����أ�%s\r\n\r\n", wszDept);
        strIDBase += strMsg;
        strMsg.Format(L"��Ч����ʼ��%s\r\n\r\n", wszStart);
        strIDBase += strMsg;
        strMsg.Format(L"��Ч����ʼ��%s\r\n\r\n", wszEnd);
        strIDBase += strMsg;
#else
        //���뻷��ʹ�ö��ֽ��ַ���,��Ҫ�����ַ�ת��
        char szTemp[128 + 1] = {0};
        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszName, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("������%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszSex, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("�Ա�%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszNation, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("���壺%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszBirth, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("������%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszAddr, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("סַ��%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszID, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("���֤�ţ�%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszDept, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("ǩ�����أ�%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszStart, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("��Ч����ʼ��%s\r\n\r\n", szTemp);
        strIDBase += strMsg;

        memset(szTemp, 0, sizeof(szTemp));
        WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, wszEnd, -1, szTemp, 128, NULL, NULL);
        strMsg.Format("��Ч�ڽ�����%s\r\n\r\n", szTemp);
        strIDBase += strMsg;
#endif

    } while (0);

    SetDlgItemText(IDC_EDIT_IDCARD_DATA, strIDBase);

    CRect rectTemp;
    GetDlgItem(IDC_STATIC_IDCARD_PHOTO)->GetWindowRect(&rectTemp);
    ScreenToClient(&rectTemp);
    InvalidateRect(rectTemp);//ˢ������ʾͼƬ

    CString cstr = _T("���֤��Ϣ: ") + strIDBase; // ����strIDBase��һ��CString
    std::wstring wStr(cstr.GetString());
    std::string stdStr(wStr.begin(), wStr.end()); // ֱ��ת�����ܶ�ʧ��ASCII�ַ�

    // ʹ��nlohmann/json�⹹��JSON����
    nlohmann::json j;
    j["����"] = CW2A(wszName, CP_UTF8);
    j["�Ա�"] = CW2A(wszSex, CP_UTF8);
    j["����"] = CW2A(wszNation, CP_UTF8);
    j["��������"] = CW2A(wszBirth, CP_UTF8);
    j["סַ"] = CW2A(wszAddr, CP_UTF8);
    j["���֤��"] = CW2A(wszID, CP_UTF8);
    j["ǩ������"] = CW2A(wszDept, CP_UTF8);
    j["��Ч����ʼ"] = CW2A(wszStart, CP_UTF8);
    j["��Ч�ڽ���"] = CW2A(wszEnd, CP_UTF8);
    std::string message = j.dump();
    SendMessageToClients(stdStr);
}


void CHxgcDeviceDemoDlg::OnBnClickedButtonIdcardClear()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    m_bPhotoEnable = false;

    SetDlgItemText(IDC_EDIT_IDCARD_DATA, _T(""));

    CRect rectTemp;
    GetDlgItem(IDC_STATIC_IDCARD_PHOTO)->GetWindowRect(&rectTemp);
    ScreenToClient(&rectTemp);
    InvalidateRect(rectTemp);//ˢ������ʾͼƬ
}

CHxgcDeviceDemoDlg::~CHxgcDeviceDemoDlg() {
    // �����������κ���Դ�����綯̬������ڴ桢�򿪵��ļ������
}
