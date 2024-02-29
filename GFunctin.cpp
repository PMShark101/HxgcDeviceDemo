//GFunctin.cpp

#include "stdafx.h"
#include "GFunctin.h"

/*
���ܣ�
    ���ֽ�����д���ļ���
������
    pi_tszFileName
        �ļ�·����
    pi_pbyBUF
        д���ֽ����顣
    pio_iBufSize
        д���ֽ������С��
����ֵ��
	ʵ��д���С��
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
        strcpy(po_pszSex, "��");
    }
    else if(0 == strcmp("2", pi_pszSexCode))
    {
        strcpy(po_pszSex, "Ů");
    }
    else if(0 == strcmp("9", pi_pszSexCode))
    {
        strcpy(po_pszSex, "����");
    }
    else
    {
        strcpy(po_pszSex, "δ֪");
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
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("02", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "�ɹ�");
    }
    else if(0 == strcmp("03", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("04", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("05", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "ά���");
    }
    else if(0 == strcmp("06", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("07", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("08", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "׳");
    }
    else if(0 == strcmp("09", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("10", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("11", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("12", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("13", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("14", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("15", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("16", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("17", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "������");
    }
    else if(0 == strcmp("18", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("19", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("20", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("21", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("22", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "�");
    }
    else if(0 == strcmp("23", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��ɽ");
    }
    else if(0 == strcmp("24", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("25", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "ˮ");
    }
    else if(0 == strcmp("26", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("27", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("28", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("29", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "�¶�����");
    }
    else if(0 == strcmp("30", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("31", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "���Ӷ�");
    }
    else if(0 == strcmp("32", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("33", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "Ǽ");
    }
    else if(0 == strcmp("34", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("35", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("36", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "ë��");
    }
    else if(0 == strcmp("37", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("38", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("39", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("40", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("41", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "������");
    }
    else if(0 == strcmp("42", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "ŭ");
    }
    else if(0 == strcmp("43", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "���α��");
    }
    else if(0 == strcmp("44", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����˹");
    }
    else if(0 == strcmp("45", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "���¿�");
    }
    else if(0 == strcmp("46", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "�°�");
    }
    else if(0 == strcmp("47", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("48", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "ԣ��");
    }
    else if(0 == strcmp("49", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��");
    }
    else if(0 == strcmp("50", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "������");
    }
    else if(0 == strcmp("51", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("52", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "���״�");
    }
    else if(0 == strcmp("53", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "����");
    }
    else if(0 == strcmp("54", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "�Ű�");
    }
    else if(0 == strcmp("55", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "���");
    }
    else if(0 == strcmp("56", pi_pszNationCode))
    {
        strcpy(po_pszNationName, "��ŵ");
    }
    else
    {
        strcpy(po_pszNationName, "δ֪");
    }

    return true;
}


/*
���ܣ�
    ��BGR��ʽ���ݽ���B��Rת����ֻ֧��24λ���ͼ��
������
    pi_pbySrc
        bgr���ݡ�
    pi_iSrcSize
        bgr���ݴ�С��
    po_pbyDst
        ����ת�����rgb��ʽ���ݣ���Ҫ��((pi_iWidth * 3 + 3) / 4) * 4 * pi_iHeight�ֽڿռ䡣
    pio_iDstSize
        ���뿪�ٿռ��С������ִ�гɹ��󷵻�ת�����rgb��ʽ���ݴ�С��
    pi_iWidth
        ͼƬ��ȣ����أ���
    pi_iHeight
        ͼƬ�߶ȣ����أ���
����ֵ��
	0 ִ�гɹ���
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
���ܣ�
    ʮ�������ַ���ת�ֽ����顣
������
    pi_ptszHexStr
        ʮ�������ַ�����
    po_pbyBuffer
        �ֽ�����Buffer��
    pi_iBufferSize
        �ֽ�����Buffer��С��
����ֵ��
	ʵ��ת����С��
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

        //�ַ���ȥ�ո�
        for(iPos = 0;iPos < iStrLen; iPos++)
        {
            if(pi_ptszHexStr[iPos] != _T(' '))
            {
                ptszBuffer[iIdx] = pi_ptszHexStr[iPos];
                iIdx++;
            }
        }

        iArraySize = _tcslen(ptszBuffer) / 2;//ת�����ֽ������ֽ���

        if(NULL == po_pbyBuffer)
        {
            //���BufferΪ�գ�������ת��
            break;
        }

        if(pi_iBufferSize < iArraySize)
        {
            iArraySize = pi_iBufferSize;
        }

        //ѭ�������ַ���
        for(iPos = 0; iPos < iArraySize; iPos++)
        {
            tszTemp[0] = ptszBuffer[iPos*2];
            tszTemp[1] = ptszBuffer[iPos*2 + 1];

            _stscanf_s(tszTemp, _T("%X"), &uiTemp);//HexToByte

            po_pbyBuffer[iPos] = (unsigned char)uiTemp;
        }
    
    }while(0);
    
    if(NULL != ptszBuffer)//����Buffer
    {
        delete ptszBuffer;
        ptszBuffer = NULL;
    }

    return iArraySize;
}

/*
���ܣ�
    �ֽ�����תʮ�������ַ�����
������
    pi_pbyBuffer
        �ֽ����顣
    pi_iBufferSize
        �ֽ������С��
    po_ptszHexBuffer
        ʮ�������ַ���Buffer��
    pi_iHexBufferLen
        ʮ�������ַ���Buffer���ȡ�
����ֵ��
	��
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
