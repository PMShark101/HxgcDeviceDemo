//GFunctin.h

#ifndef _G_FUNCTION_H_
#define _G_FUNCTION_H_

#include <string>

/*
д�ļ�
����˵����

*/

int tool_WriteOneFile(const TCHAR* pi_tszFileName, unsigned char* pi_pbyBUF, int pio_iBufSize);

//�����Ա�������Ա��ַ���
bool GetSexByCodeA(const char* pi_pszSexCode, char* po_pszSex, int pi_SexLen);

//������������������ַ���
bool GetNationByCodeA(const char* pi_pwszNationCode, char* po_pwszNationName, int pi_iNationLen);

//��BGR��ʽ���ݽ���B��Rת��
int bgr2rgb(const unsigned char* pi_pbySrc, int pi_iSrcSize, unsigned char* po_pbyDst, int& pio_iDstSize, int pi_iWidth, int pi_iHeight);

//16�����ַ���ת�ֽ�����
int HexStringToByteArray(const TCHAR* pi_ptszHexStr, unsigned char* po_pbyBuffer, int pi_iBufferSize);

//�ֽ�����ת16�����ַ���
void ByteArryToHexString(unsigned char* pi_pbyBuffer, int pi_iBufferSize, TCHAR* po_ptszHexBuffer, int pi_iHexBufferLen);

#endif//_G_FUNCTION_H_
