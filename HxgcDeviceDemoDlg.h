
// HxgcDeviceDemoDlg.h : 头文件
//

#pragma once
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <set>
#include <thread>



typedef websocketpp::server<websocketpp::config::asio> server;
using websocketpp::connection_hdl;

// CHxgcDeviceDemoDlg 对话框
class CHxgcDeviceDemoDlg : public CDialogEx
{
// 构造
public:
	CHxgcDeviceDemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HXGCDEVICEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
    //初始化参数
    void InitParam();

    //加载设备动态库
    bool LoadSubModule();

    //释放设备动态库
    void FreeSubModule();

    //获得端口号
    int GetPortNum();

    //获得端口波特率
    int GetPortBaud();

    //绘制BMP图像
    void DrawPhotoBmpFormFile(const TCHAR* pi_ptszBmpFilePath, CDC* pi_pDC, CRect pi_rect);
protected:
    HINSTANCE m_hSubModuleA;
    HINSTANCE m_hSubModuleB;
    bool m_bSubModEnable;
    bool m_bPhotoEnable;

protected:
    //二代证相关API---------------------------------------------------------------------------------------
    typedef int (__stdcall *PF_SDT_GetCOMBaud)(int pi_iPort,unsigned int * po_puiBaudRate);
    typedef int (__stdcall *PF_SDT_SetCOMBaud)(int pi_iPort, unsigned int pi_uiCurrBaud, unsigned int pi_uiSetBaud);
    typedef int (__stdcall *PF_SDT_StartFindIDCard)(int pi_iPort, unsigned char* po_pbyManaInfo, int pi_iIfOpen);
    typedef int (__stdcall *PF_SDT_SelectIDCard)(int pi_iPort, unsigned char* po_pbyManaInfo, int pi_iIfOpen);
    typedef int (__stdcall *PF_SDT_ReadBaseMsg)(int pi_iPort, unsigned char* po_pbyCHMsg, unsigned int*  po_puiCHMsgLen, unsigned char* po_pbyPHMsg, unsigned int*  po_puiPHMsgLen, int pi_iIfOpen);
    typedef int	(__stdcall *PF_SDT_ReadBaseFPMsg)(int iPortID, unsigned char* po_pucCHMsg, unsigned int* po_puiCHMsgLen, unsigned char* po_pucPHMsg, unsigned int* po_puiPHMsgLen, unsigned char* po_pucFPMsg, unsigned int* po_puiFPMsgLen, int pi_iIfOpen);
    typedef int (__stdcall *PF_SDT_GetSAMIDToStr)(int iPortID,char* po_pcSAMID,int pi_iIfOpen);
    typedef int (__stdcall *PF_SDT_ReadNewAppMsg)(int iPortID,unsigned char* po_pucAppMsg,unsigned int* po_puiAppMsgLen,int pi_iIfOpen);

    PF_SDT_GetCOMBaud			m_pfn_SDT_GetCOMBaud;
    PF_SDT_SetCOMBaud			m_pfn_SDT_SetCOMBaud;
    PF_SDT_StartFindIDCard      m_pfn_SDT_StartFindIDCard;
    PF_SDT_SelectIDCard         m_pfn_SDT_SelectIDCard;
    PF_SDT_ReadBaseMsg          m_pfn_SDT_ReadBaseMsg;
    PF_SDT_ReadBaseFPMsg		m_pfn_SDT_ReadBaseFPMsg;
    PF_SDT_GetSAMIDToStr		m_pfn_SDT_GetSAMIDToStr;
    PF_SDT_ReadNewAppMsg		m_pfn_SDT_ReadNewAppMsg;

    //照片解码API---------------------------------------------------------------------------------------
    typedef int (*PF_unpack)(char* pi_szSrcWltData, char* pi_szDstPicData, int pi_iIsSaveToBmp);
    PF_unpack m_pfn_unpack;

private:
    // WebSocket服务器和连接管理
    server m_wsServer;
    std::set<connection_hdl, std::owner_less<connection_hdl>> m_connections;
    std::thread* m_pWsThread = nullptr;

    // WebSocket服务器方法
    void InitWebSocketServer();
    void OnOpen(connection_hdl hdl);
    void OnClose(connection_hdl hdl);
    void OnMessage(connection_hdl hdl, server::message_ptr msg);
    void SendMessageToClients(const std::string& message);

public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedButtonIdcardRead();
    afx_msg void OnBnClickedButtonIdcardClear();
    
public:
    CComboBox m_combo_dev_port;
    CComboBox m_combo_dev_baud;
    virtual ~CHxgcDeviceDemoDlg();
};
