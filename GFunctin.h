//GFunctin.h

#ifndef _G_FUNCTION_H_
#define _G_FUNCTION_H_

#include <string>

/*
写文件
参数说明：

*/

int tool_WriteOneFile(const TCHAR* pi_tszFileName, unsigned char* pi_pbyBUF, int pio_iBufSize);

//根据性别代码获得性别字符串
bool GetSexByCodeA(const char* pi_pszSexCode, char* po_pszSex, int pi_SexLen);

//根据民族代码获得民族字符串
bool GetNationByCodeA(const char* pi_pwszNationCode, char* po_pwszNationName, int pi_iNationLen);

//对BGR格式数据进行B、R转换
int bgr2rgb(const unsigned char* pi_pbySrc, int pi_iSrcSize, unsigned char* po_pbyDst, int& pio_iDstSize, int pi_iWidth, int pi_iHeight);

//16进制字符串转字节数组
int HexStringToByteArray(const TCHAR* pi_ptszHexStr, unsigned char* po_pbyBuffer, int pi_iBufferSize);

//字节数组转16进制字符串
void ByteArryToHexString(unsigned char* pi_pbyBuffer, int pi_iBufferSize, TCHAR* po_ptszHexBuffer, int pi_iHexBufferLen);

#endif//_G_FUNCTION_H_
