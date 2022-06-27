//=====================================================================
//--------------File - ZHHK429_dll.h------------------
//
//-------Library for accessing the ZHHK429 Series II card-----------
//   Copyright (C) ZhengHong Aviation Tech Co., Ltd; 
//   http://www.zhhktech.com  029-84288198
//   DATE:2018-12-08  V9.5 
// 
//=====================================================================

#ifndef _ZHHK429_DLL_H_
#define _ZHHK429_DLL_H_

#include <windows.h>
#include <winioctl.h>

#ifdef WIN32
#ifdef API_EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif
#else
#define API
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define SD_MAX          4
#define LABEL_MAX       256
#define CHNO_TMAX       16
#define CHNO_RMAX       16
#define TRIGGER_TMAX    255         // ����FIFO����������ֵ
#define TRIGGER_RMAX    65535       // ����FIFO����������ֵ
#define FIFO_TMAX       255
#define FIFO_RMAX       65535
#define INTERVAL_MAX    0xFFFF      // ��ʱ���ʱ�����ֵ
#define TXDATA_MAX      0xFFFFFFFF
#define FIFOEmpty       0x00010000  // FIFO empty flag
#define FIFOFull        0x00020000  // FIFO full flag

// ========================================================= V9 Add Start
typedef void* DevInfoHandle;    // �豸��Ϣ���
typedef void* DevHandle;        // �豸���
typedef void (__stdcall *INT_HANDLER) (DevHandle hZHHK429);

#define VAL_SUCCESS   0
#define VAL_TRUE      1
#define VAL_FALSE     2
#define VAL_FAILED   -1
#define VAL_PARERR   -2
#define VAL_TIME_OUT -5
#define VAL_UNKNOWN_STATUS -4
#define ErrorDeviceHandleInvalid -1000
#define ErrorFindConfigurationSpace -1001
// ========================================================= V9 Add End

// type defines
typedef struct
{
    DWORD Cfg_BaudCounter;
    DWORD Cfg_ParityEnable;
    DWORD Cfg_ParityMode;
    DWORD Cfg_BusOrderEnable;
    DWORD Cfg_SDDecoderEnable;
    DWORD Cfg_SDDecoderData;
    DWORD Cfg_SelfTestEnable;
}ZHHK429_RX_CFG_STRUCT;

typedef struct
{
    DWORD LabelTable[4][256];
}ZHHK429_LABEL_TABLE_STRUCT;

typedef struct
{
    DWORD Cfg_BaudCounter;
    DWORD Cfg_ParityEnable;
    DWORD Cfg_ParityMode;
    DWORD Cfg_BusOrderEnable;
}ZHHK429_TX_CFG_STRUCT;


// Function Declaration
//************************************************************************
//********* COMMON OPERATION *********************************************
//************************************************************************
API int ZHHK429_Open (DevHandle *phZHHK429, DWORD CardId);
API int ZHHK429_Close (DevHandle hZHHK429);
API int ZHHK429_Reset (DevHandle hZHHK429);
API int ZHHK429_GetSerialNum (DevHandle hZHHK429, DWORD *SerialNum0, DWORD *SerialNum1);

API int ZHHK429_StartTimeTag (DevHandle hZHHK429, DWORD Enable, LPSYSTEMTIME CurSysTime);
API int ZHHK429_SetTimeTag (DevHandle hZHHK429, DWORD TimeTag);
API int ZHHK429_GetTimeTag (DevHandle hZHHK429, DWORD *TimeTag);

//************************************************************************
//********* RX ***********************************************************
//************************************************************************
API int ZHHK429_RX_Reset (DevHandle hZHHK429, DWORD ch);
API int ZHHK429_RX_Configure (DevHandle hZHHK429, DWORD ch, ZHHK429_RX_CFG_STRUCT *Cfg);
API int ZHHK429_RX_TriggerDepth (DevHandle hZHHK429, DWORD ch, DWORD TriggerDepth);
API int ZHHK429_RX_TimeTagMode (DevHandle hZHHK429, DWORD ch, DWORD Enable);
API int ZHHK429_RX_RecvEnable (DevHandle hZHHK429, DWORD ch, DWORD Enable);
API int ZHHK429_RX_LableFilterEnable (DevHandle hZHHK429, DWORD ch, DWORD Enable);
API int ZHHK429_RX_LableFilterTable (DevHandle hZHHK429, DWORD ch, ZHHK429_LABEL_TABLE_STRUCT *FilterTable);
API int ZHHK429_RX_BufferClr (DevHandle hZHHK429, DWORD ch);
API int ZHHK429_RX_BufferStatus (DevHandle hZHHK429, DWORD ch, DWORD *Status);
API int ZHHK429_RX_BufferData (DevHandle hZHHK429, DWORD ch, DWORD TimeTagMode, DWORD *Length, DWORD *DataBuf);

//************************************************************************
//********* TX ***********************************************************
//************************************************************************
API int ZHHK429_TX_Reset (DevHandle hZHHK429, DWORD ch);
API int ZHHK429_TX_Configure (DevHandle hZHHK429, DWORD ch, ZHHK429_TX_CFG_STRUCT *Cfg);
API int ZHHK429_TX_TriggerDepth (DevHandle hZHHK429, DWORD ch, DWORD TriggerDepth);
API int ZHHK429_TX_TimerIntervalWord (DevHandle hZHHK429, DWORD ch, DWORD Time);
API int ZHHK429_TX_TimerIntervalFrame (DevHandle hZHHK429, DWORD ch, DWORD Time);
API int ZHHK429_TX_BufferClr (DevHandle hZHHK429, DWORD ch, DWORD AreaBNA);
API int ZHHK429_TX_BufferStatus (DevHandle hZHHK429, DWORD ch, DWORD AreaBNA, DWORD *Status);
API int ZHHK429_TX_BufferData (DevHandle hZHHK429, DWORD ch, DWORD AreaBNA, DWORD Length, DWORD *DataBuf);
API int ZHHK429_TX_BufferAreaSet (DevHandle hZHHK429, DWORD ch, DWORD AreaBNA);
API int ZHHK429_TX_BufferAreaGet (DevHandle hZHHK429, DWORD ch, DWORD *AreaBNA);
API int ZHHK429_TX_BufferUpdate (DevHandle hZHHK429, DWORD ch, DWORD Length, DWORD *DataBuf);
API int ZHHK429_TX_Start (DevHandle hZHHK429, DWORD ch);
API int ZHHK429_TX_Stop (DevHandle hZHHK429, DWORD ch);

//************************************************************************
//********* Interrupt *****Just for ZHHK429-PCI/CPCI Series***************
//************************************************************************
//�����ж��߳�
API int ZHHK429_INT_Thread (DevHandle hZHHK429);
//�жϳ�ʼ��
API int ZHHK429_INT_Init (DevHandle hZHHK429, INT_HANDLER IntFunc);
//���ж�ʹ��
API int ZHHK429_INT_EnableGlobal (DevHandle hZHHK429, DWORD Enable);
//���ж�ʹ��
API int ZHHK429_INT_EnableBit (DevHandle hZHHK429, DWORD EnableBitVector);
//���ж�״̬λ
API int ZHHK429_INT_StatusClear (DevHandle hZHHK429, DWORD StatusClearVector);
//��ȡ�ж�״̬
API int ZHHK429_INT_Status (DevHandle hZHHK429, DWORD *Status);


#ifdef __cplusplus
}
#endif

#endif