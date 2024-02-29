//GFunctin.cpp

#include "stdafx.h"
#include "GFunctin.h"

/*
功能：
    将字节数组写入文件。
参数：
    pi_tszFileName
        文件路径。
    pi_pbyBUF
        写入字节数组。
    pio_iBufSize
        写入字节数组大小。
返回值：
	实际写入大小。
*/
int tool_WriteOneFile(const TCHAR* pi_tszFileName, unsigned char* pi_pbyBUF, int pio_iBufSize)
{
    int iWriteNum = 0;

    if(NULL == pi_tszFileName)
    {
        return iWriteNum;
    }

    if(NULL == pi_pbyBUF)
    {
        return iWriteNum;
    }

    if(pio_iBufSize <= 0)
    {
        return iWriteNum;
    }

    FILE* fpFile = NULL;

    fpFile = _tfopen(pi_tszFileName, _T("wb"));
    if(NULL == fpFile)
    {
        return iWriteNum;
    }

    iWriteNum = fwrite(pi_pbyBUF, 1, pio_iBufSize, fpFile);
    fflush(fpFile);
    fclose(fpFile);
    fpFile = NULL;

    return iWriteNum;
}

bool GetSexByCodeA(const char* pi_pszSexCode, char* po_pszSex, int pi_SexLen)
{
    if(NULL == pi_pszSexCode)
    {
        return false;
    }

    if(NULL == po_pszSex)
    {
        return false;
    }

    if(0 == strcmp("1", pi_pszSexCode))
    {
        strcpy(po_pszSex, "男");
    }
    else if(0 == strcmp("2", pi_pszSexCode))
    {
        strcpy(po_pszSex, "女");
    }
    else if(0 == strcmp("9", pi_pszSexCode))
    {
        strcpy(po_pszSex, "其他");
    }
    else
    {
        strcpy(po_pszSex, "未知");
    }

    return true;
}

bool GetNationByCodeA(const char* pi_pszNationCode, char* po_pszNationName, int pi_iNationLen)
{
    if(NULL == pi_pszNationCode)
    {
        return false;
    }

    if(NULL == po_pszNationName)
    {
        return false;
    }

    if(0 == strcmp("01", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "汉");
    }
    else if(0 == strcmp("02", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "蒙古");
    }
    else if(0 == strcmp("03", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "回");
    }
    else if(0 == strcmp("04", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "藏");
    }
    else if(0 == strcmp("05", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "维吾尔");
    }
    else if(0 == strcmp("06", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "苗");
    }
    else if(0 == strcmp("07", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "彝");
    }
    else if(0 == strcmp("08", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "壮");
    }
    else if(0 == strcmp("09", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "布依");
    }
    else if(0 == strcmp("10", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "朝鲜");
    }
    else if(0 == strcmp("11", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "满");
    }
    else if(0 == strcmp("12", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "侗");
    }
    else if(0 == strcmp("13", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "瑶");
    }
    else if(0 == strcmp("14", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "白");
    }
    else if(0 == strcmp("15", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "土家");
    }
    else if(0 == strcmp("16", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "哈尼");
    }
    else if(0 == strcmp("17", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "哈萨克");
    }
    else if(0 == strcmp("18", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "傣");
    }
    else if(0 == strcmp("19", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "黎");
    }
    else if(0 == strcmp("20", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "傈僳");
    }
    else if(0 == strcmp("21", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "佤");
    }
    else if(0 == strcmp("22", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "畲");
    }
    else if(0 == strcmp("23", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "高山");
    }
    else if(0 == strcmp("24", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "拉祜");
    }
    else if(0 == strcmp("25", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "水");
    }
    else if(0 == strcmp("26", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "东乡");
    }
    else if(0 == strcmp("27", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "纳西");
    }
    else if(0 == strcmp("28", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "景颇");
    }
    else if(0 == strcmp("29", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "柯尔克孜");
    }
    else if(0 == strcmp("30", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "土");
    }
    else if(0 == strcmp("31", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "达斡尔");
    }
    else if(0 == strcmp("32", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "仫佬");
    }
    else if(0 == strcmp("33", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "羌");
    }
    else if(0 == strcmp("34", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "布朗");
    }
    else if(0 == strcmp("35", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "撒拉");
    }
    else if(0 == strcmp("36", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "毛南");
    }
    else if(0 == strcmp("37", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "仡佬");
    }
    else if(0 == strcmp("38", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "锡伯");
    }
    else if(0 == strcmp("39", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "阿昌");
    }
    else if(0 == strcmp("40", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "普米");
    }
    else if(0 == strcmp("41", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "塔吉克");
    }
    else if(0 == strcmp("42", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "怒");
    }
    else if(0 == strcmp("43", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "乌孜别克");
    }
    else if(0 == strcmp("44", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "俄罗斯");
    }
    else if(0 == strcmp("45", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "鄂温克");
    }
    else if(0 == strcmp("46", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "德昂");
    }
    else if(0 == strcmp("47", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "保安");
    }
    else if(0 == strcmp("48", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "裕固");
    }
    else if(0 == strcmp("49", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "京");
    }
    else if(0 == strcmp("50", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "塔塔尔");
    }
    else if(0 == strcmp("51", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "独龙");
    }
    else if(0 == strcmp("52", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "鄂伦春");
    }
    else if(0 == strcmp("53", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "赫哲");
    }
    else if(0 == strcmp("54", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "门巴");
    }
    else if(0 == strcmp("55", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "珞巴");
    }
    else if(0 == strcmp("56", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "基诺");
    }
    else
    {
        strcpy(po_pszNationName, "未知");
    }

    return true;
}


/*
功能：
    对BGR格式数据进行B、R转换，只支持24位深度图像。
参数：
    pi_pbySrc
        bgr数据。
    pi_iSrcSize
        bgr数据大小。
    po_pbyDst
        返回转换后的rgb格式数据，需要开((pi_iWidth * 3 + 3) / 4) * 4 * pi_iHeight字节空间。
    pio_iDstSize
        传入开辟空间大小，函数执行成功后返回转换后的rgb格式数据大小。
    pi_iWidth
        图片宽度（像素）。
    pi_iHeight
        图片高度（像素）。
返回值：
	0 执行成功。
*/
int bgr2rgb(const unsigned char* pi_pbySrc, int pi_iSrcSize, unsigned char* po_pbyDst, int& pio_iDstSize, int pi_iWidth, int pi_iHeight)
{
    int iWidthSize = pi_iWidth * 3;
    int iDstWidthSize = ((pi_iWidth * 3 + 3) / 4) * 4;
    int iExternSize = ((pi_iWidth * 3 + 3) / 4) * 4 - pi_iWidth * 3;
    int iPosX = 0;
    int iPosY = 0;

    if(pi_iSrcSize != (iWidthSize * pi_iHeight))
    {
        return -1;    
    }

    if(pio_iDstSize < (iDstWidthSize * pi_iHeight))
    {
        return -2; 
    }
    memset(po_pbyDst, 0, pio_iDstSize);

    for(iPosY = 0;iPosY < pi_iHeight; iPosY++)
    {
        for (iPosX = 0;iPosX < pi_iWidth*3; iPosX += 3)
        {
            po_pbyDst[(iWidthSize + iExternSize) * iPosY + iPosX + 0] = pi_pbySrc[iWidthSize * iPosY + iPosX + 2];
            po_pbyDst[(iWidthSize + iExternSize) * iPosY + iPosX + 1] = pi_pbySrc[iWidthSize * iPosY + iPosX + 1];
            po_pbyDst[(iWidthSize + iExternSize) * iPosY + iPosX + 2] = pi_pbySrc[iWidthSize * iPosY + iPosX + 0]; 
        }
    }

    pio_iDstSize = iDstWidthSize * pi_iHeight;

    return 0;
}

/*
功能：
    十六进制字符串转字节数组。
参数：
    pi_ptszHexStr
        十六进制字符串。
    po_pbyBuffer
        字节数组Buffer。
    pi_iBufferSize
        字节数组Buffer大小。
返回值：
	实际转换大小。
*/
int HexStringToByteArray( const TCHAR* pi_ptszHexStr, unsigned char* po_pbyBuffer, int pi_iBufferSize )
{
    int iPos = 0;
    TCHAR *ptszBuffer = NULL;
    int iStrLen = 0;
    int iIdx = 0;
    int iArraySize = 0;

    TCHAR tszTemp[2 + 1] = {0};
    UINT uiTemp = 0;

    do
    {
        if(NULL == pi_ptszHexStr)
        {
            break;
        }

        iStrLen = _tcslen(pi_ptszHexStr);

        ptszBuffer = new TCHAR[iStrLen + 1];
        if(NULL == ptszBuffer)
        {
            break;;
        }
        memset(ptszBuffer, 0, (iStrLen + 1)*sizeof(TCHAR));

        //字符串去空格
        for(iPos = 0;iPos < iStrLen; iPos++)
        {
            if(pi_ptszHexStr[iPos] != _T(' '))
            {
                ptszBuffer[iIdx] = pi_ptszHexStr[iPos];
                iIdx++;
            }
        }

        iArraySize = _tcslen(ptszBuffer) / 2;//转换后字节数组字节数

        if(NULL == po_pbyBuffer)
        {
            //输出Buffer为空，不进行转换
            break;
        }

        if(pi_iBufferSize < iArraySize)
        {
            iArraySize = pi_iBufferSize;
        }

        //循环遍历字符串
        for(iPos = 0; iPos < iArraySize; iPos++)
        {
            tszTemp[0] = ptszBuffer[iPos*2];
            tszTemp[1] = ptszBuffer[iPos*2 + 1];

            _stscanf_s(tszTemp, _T("%X"), &uiTemp);//HexToByte

            po_pbyBuffer[iPos] = (unsigned char)uiTemp;
        }
    
    }while(0);
    
    if(NULL != ptszBuffer)//清理Buffer
    {
        delete ptszBuffer;
        ptszBuffer = NULL;
    }

    return iArraySize;
}

/*
功能：
    字节数组转十六进制字符串。
参数：
    pi_pbyBuffer
        字节数组。
    pi_iBufferSize
        字节数组大小。
    po_ptszHexBuffer
        十六进制字符串Buffer。
    pi_iHexBufferLen
        十六进制字符串Buffer长度。
返回值：
	无
*/
void ByteArryToHexString( unsigned char* pi_pbyBuffer, int pi_iBufferSize, TCHAR* po_ptszHexBuffer, int pi_iHexBufferLen )
{
    int iPos = 0;
    int iStrLen = 0;
    TCHAR tszTemp[2 + 1] = {0};
    unsigned char byTemp = 0;

    if((NULL == pi_pbyBuffer) || (0 == pi_iBufferSize) || (NULL == po_ptszHexBuffer))
    {
        return;
    }

    if(pi_iHexBufferLen < (pi_iBufferSize*2))
    {
        pi_iBufferSize = pi_iHexBufferLen / 2;
    }

    for(iPos = 0; iPos < pi_iBufferSize; iPos++)
    {
        byTemp = pi_pbyBuffer[iPos];

        _stprintf_s(tszTemp, _T("%02X"), byTemp);
        po_ptszHexBuffer[iPos*2] = tszTemp[0];
        po_ptszHexBuffer[iPos*2 + 1] = tszTemp[1];
    }
}
