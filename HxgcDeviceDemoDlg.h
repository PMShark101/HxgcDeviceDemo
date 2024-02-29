
// HxgcDeviceDemoDlg.h : ͷ�ļ�
//

#pragma once
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <set>
#include <thread>



typedef websocketpp::server<websocketpp::config::asio> server;
using websocketpp::connection_hdl;

// CHxgcDeviceDemoDlg �Ի���
class CHxgcDeviceDemoDlg : public CDialogEx
{
// ����
public:
	CHxgcDeviceDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HXGCDEVICEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
    //��ʼ������
    void InitParam();

    //�����豸��̬��
    bool LoadSubModule();

    //�ͷ��豸��̬��
    void FreeSubModule();

    //��ö˿ں�
    int GetPortNum();

    //��ö˿ڲ�����
    int GetPortBaud();

    //����BMPͼ��
    void DrawPhotoBmpFormFile(const TCHAR* pi_ptszBmpFilePath, CDC* pi_pDC, CRect pi_rect);
protected:
    HINSTANCE m_hSubModuleA;
    HINSTANCE m_hSubModuleB;
    bool m_bSubModEnable;
    bool m_bPhotoEnable;

protected:
    //����֤���API---------------------------------------------------------------------------------------
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

    //��Ƭ����API---------------------------------------------------------------------------------------
    typedef int (*PF_unpack)(char* pi_szSrcWltData, char* pi_szDstPicData, int pi_iIsSaveToBmp);
    PF_unpack m_pfn_unpack;

private:
    // WebSocket�����������ӹ���
    server m_wsServer;
    std::set<connection_hdl, std::owner_less<connection_hdl>> m_connections;
    std::thread* m_pWsThread = nullptr;

    // WebSocket����������
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
