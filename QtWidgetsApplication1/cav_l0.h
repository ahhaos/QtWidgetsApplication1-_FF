#ifndef _CAV_L0_Header_
#define _CAV_L0_Header_
/******************************************************************************
 * 文件:			CAV_L0.h
 *
 * 版权所有@2013,版权归北京石竹科技有限公司(CAV)所有.
 * 使用此软件受石竹科技许可(最新版本),中国政府或法律和
 * 石竹科技销售条款和条件(最新版本)限制.
 *
 *
 *
 * 功能描述:
 *	零层头文件.
 *
 *
 *****************************************************************************/
/*! \file CAV_L0.h 
 *  \brief Top-level header file for the CAT Layer 0 API 
 *
 *  This is the header file for the CAT Layer 0 API, with definitions of
 *  constants, types, and function prototypes.
 */

/* Need the following includes for functions that use memset.
   For Windows (MSVS) include string.h, memory.h, and malloc.h.
   For INTEGRITY or VxWorks 5.5 include string.h and stdlib.h.
*/
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define     MAX_NUMBER_DEVICES					16
#define		GET_DEVNUM_NUM(x)					((x & 0xF0000)>>16)
#define     GET_DEVNUM_TYPE(x)					((x& 0xFF000000) >> 24)

/********** Version Constant **********/
#define CAV_L0_API_VERSION	0x02000004  /* Version 2.0.0.4 */

/********** Type Definitions **********/
/*! \brief Basic 32-bit unsigned integer type */
typedef unsigned int  CAV_L0_UINT32;

/*! \brief Basic 16-bit unsigned integer type */
typedef unsigned short  CAV_L0_UINT16;

/*! \brief Basic 8-bit unsigned integer type */
typedef unsigned char  CAV_L0_UINT8;

/* Calling convention:
 *		__stdcall for Windows
 *		<nothing> for Linux, VxWorks, Integrity
 */
#define CAV_L0_CALL_CONV	/*__stdcall*/	 	/*!< \brief Function calling convention */
#define EXPORT_DLL		__declspec(dllexport)

/*! \brief Function pointer typedef for user interrupt handler */
EXPORT_DLL typedef void (CAV_L0_CALL_CONV *CAV_L0_PUSERISRR)(void);

/********** Expected sizes of data types/structures **********/
#define CAV_L0_UINT32_SIZE		4	/*!< \brief Expected size for \ref CAV_L0_UINT32 type */

/********** Constants **********/
/* PCI Vendor and Device IDs */
#define CAV_PCI_VENDOR_ID				0x7971
#define CAV_1553B_PCI_DEVICE_ID			0x1553
#define CAV_A429_PCI_DEVICE_ID			0x429

#define CAV_PCI_DEVICE_BAR0				0x0
#define CAV_PCI_DEVICE_BAR2				0x2

#define CAV_PCI_DEVICE_ID_TEST1553		0x0001
#define CAV_PCI_DEVICE_ID_TESTA429		0x0014  // TEST-A429 uses PCI-1553 board with ARINC bit file
#define CAV_PCI_DEVICE_ID_PMCA429		0x0110


/* Device ID Constants - Backplane Type (4 bits) -	(DEVID & 0xF0000000) */
#define CAV_DEVID_BACKPLANETYPE_SIMULATED	0x00000000
#define CAV_DEVID_BACKPLANETYPE_PCI			0x10000000
#define CAV_DEVID_BACKPLANETYPE_USB			0x20000000


/* Device ID Constants - Board Type (8 bits) -		(DEVID & 0x0FF00000) */
#define CAV_DEVID_BOARDTYPE_SIM1553			0x00000000
#define CAV_DEVID_BOARDTYPE_TEST1553		0x00100000
#define CAV_DEVID_BOARDTYPE_PMC1553			0x00200000
#define CAV_DEVID_BOARDTYPE_PC104P1553		0x00300000
#define CAV_DEVID_BOARDTYPE_PCI1553			0x00400000
#define CAV_DEVID_BOARDTYPE_PCCD1553		0x00500000
#define CAV_DEVID_BOARDTYPE_PCI104E1553		0x00600000
#define CAV_DEVID_BOARDTYPE_XMCE4L1553		0x00700000
#define CAV_DEVID_BOARDTYPE_ECD54_1553		0x00800000
#define CAV_DEVID_BOARDTYPE_PCIE4L1553		0x00900000


#define CAV_DEVID_BOARDTYPE_SIMA429			0x01000000
#define CAV_DEVID_BOARDTYPE_TESTA429		0x01100000
#define CAV_DEVID_BOARDTYPE_PMCA429			0x01200000
#define CAV_DEVID_BOARDTYPE_PC104PA429		0x01300000
#define CAV_DEVID_BOARDTYPE_PCIA429			0x01400000
#define CAV_DEVID_BOARDTYPE_PCCDA429		0x01500000
#define CAV_DEVID_BOARDTYPE_PCI104EA429		0x01600000
#define CAV_DEVID_BOARDTYPE_XMCE4LA429		0x01700000
#define CAV_DEVID_BOARDTYPE_ECD54_A429		0x01800000
#define CAV_DEVID_BOARDTYPE_PCIE4LA429		0x01900000
#define CAV_DEVID_BOARDTYPE_USBA429			0x02000000
#define CAV_DEVID_BOARDTYPE_PXIA429        0x02100000 ///add 2018-01-30 by hanlm
#define CAV_PCI_DEVICE_ID_PMCMA4			0x0210

#define		CAV_L1_A429_PE_ROOT_CSR						0x10000	/* A429 ROOT PE CONTROL REG */
#define		CAV_L1_A429_PE_ROOT_STS			0x10004
#define		CAV_L1_PE_ROOT_IDVER						0x10008

/*board type*/
#define  CAV_A429_PMC		0x12
#define  CAV_A429_PCI		0x14
#define  CAV_A429_USB		0x15
#define  CAV_A429_PXI		0x16
#define  CAV_A429_MPCIE     0x17
#define  CAV_A429_PCIE      0x18



/* Device ID Constants - Product (backplane | board type) 
 * For defining DEVID in user applications.
 */
#define CAV_PRODUCT_SIM1553		CAV_DEVID_BACKPLANETYPE_SIMULATED | CAV_DEVID_BOARDTYPE_SIM1553
#define CAV_PRODUCT_TEST1553	CAV_DEVID_BACKPLANETYPE_PCI | CAV_DEVID_BOARDTYPE_TEST1553

#define CAV_PRODUCT_SIMA429		CAV_DEVID_BACKPLANETYPE_SIMULATED | CAV_DEVID_BOARDTYPE_SIMA429
#define CAV_PRODUCT_TESTA429	CAV_DEVID_BACKPLANETYPE_PCI | CAV_DEVID_BOARDTYPE_TESTA429
#define CAV_PRODUCT_PMCA429		CAV_DEVID_BACKPLANETYPE_PCI | CAV_DEVID_BOARDTYPE_PMCA429
#define CAV_PRODUCT_USB429		CAV_DEVID_BACKPLANETYPE_USB | CAV_DEVID_BOARDTYPE_USBA429


/* Device ID Constants - Board Number (4 bits) -	(DEVID & 0x000F0000) */
#define CAV_DEVID_BOARDNUM_01				0x00000000
#define CAV_DEVID_BOARDNUM_02				0x00010000
#define CAV_DEVID_BOARDNUM_03				0x00020000
#define CAV_DEVID_BOARDNUM_04				0x00030000
#define CAV_DEVID_BOARDNUM_05				0x00040000
#define CAV_DEVID_BOARDNUM_06				0x00050000
#define CAV_DEVID_BOARDNUM_07				0x00060000
#define CAV_DEVID_BOARDNUM_08				0x00070000
#define CAV_DEVID_BOARDNUM_09				0x00080000
#define CAV_DEVID_BOARDNUM_10				0x00090000
#define CAV_DEVID_BOARDNUM_11				0x000A0000
#define CAV_DEVID_BOARDNUM_12				0x000B0000
#define CAV_DEVID_BOARDNUM_13				0x000C0000
#define CAV_DEVID_BOARDNUM_14				0x000D0000
#define CAV_DEVID_BOARDNUM_15				0x000E0000
#define CAV_DEVID_BOARDNUM_16				0x000F0000

/* Device ID Constants - Channel Type (8 bits) -	(DEVID & 0x0000FF00) */
#define CAV_DEVID_CHANNELTYPE_GLOBALS		0x00000100
#define CAV_DEVID_CHANNELTYPE_1553			0x00001000
#define CAV_DEVID_CHANNELTYPE_A429			0x00002000

/* Device ID Constants - Channel Number (8 bits) -	(DEVID & 0x000000FF) */
#define CAV_DEVID_CHANNELNUM_01				0x00000000
#define CAV_DEVID_CHANNELNUM_02				0x00000001
#define CAV_DEVID_CHANNELNUM_03				0x00000002
#define CAV_DEVID_CHANNELNUM_04				0x00000003
#define CAV_DEVID_CHANNELNUM_05				0x00000004
#define CAV_DEVID_CHANNELNUM_06				0x00000005
#define CAV_DEVID_CHANNELNUM_07				0x00000006
#define CAV_DEVID_CHANNELNUM_08				0x00000007
#define CAV_DEVID_CHANNELNUM_09				0x00000008
#define CAV_DEVID_CHANNELNUM_10				0x00000009
#define CAV_DEVID_CHANNELNUM_11				0x0000000A
#define CAV_DEVID_CHANNELNUM_12				0x0000000B
#define CAV_DEVID_CHANNELNUM_13				0x0000000C
#define CAV_DEVID_CHANNELNUM_14				0x0000000D
#define CAV_DEVID_CHANNELNUM_15				0x0000000E
#define CAV_DEVID_CHANNELNUM_16				0x0000000F
#define CAV_DEVID_CHANNELNUM_17				0x00000010
#define CAV_DEVID_CHANNELNUM_18				0x00000011
#define CAV_DEVID_CHANNELNUM_19				0x00000012
#define CAV_DEVID_CHANNELNUM_20				0x00000013
#define CAV_DEVID_CHANNELNUM_21				0x00000014
#define CAV_DEVID_CHANNELNUM_22				0x00000015
#define CAV_DEVID_CHANNELNUM_23				0x00000016
#define CAV_DEVID_CHANNELNUM_24				0x00000017
#define CAV_DEVID_CHANNELNUM_25				0x00000018
#define CAV_DEVID_CHANNELNUM_26				0x00000019
#define CAV_DEVID_CHANNELNUM_27				0x0000001A
#define CAV_DEVID_CHANNELNUM_28				0x0000001B
#define CAV_DEVID_CHANNELNUM_29				0x0000001C
#define CAV_DEVID_CHANNELNUM_30				0x0000001D
#define CAV_DEVID_CHANNELNUM_31				0x0000001E
#define CAV_DEVID_CHANNELNUM_32				0x0000001F
#define CAV_DEVID_CHANNELNUM_33				0x00000020
#define CAV_DEVID_CHANNELNUM_34				0x00000021


/* Device ID Constants ?ARINC Bank Number (8 bits) - (DEVID & 0x000000FF) */
#define CAV_DEVID_BANK_01					0x00000000
#define CAV_DEVID_BANK_02					0x00000001
#define CAV_DEVID_BANK_03					0x00000002
#define CAV_DEVID_BANK_04					0x00000003

/* Memory sizes by board type and channel type for SIMULATED devices */
#define CAV_MEMSIZE_SIM1553_CHAN			0x100000	/* 1MB for a SIM1553 channel */
#define CAV_MEMSIZE_SIMA429_CHAN			0x100000	/* 1MB for a SIMA429 channel */


/* API Number of Labels per ARINC Word (first 8 bits of word) */

#define		CAV_DDR_MEM_READ_ADDR_REG					0x0004
#define		CAV_DDR_MEM_WRITE_ADDR_REG					0x0008
#define		CAV_DDR_MEM_DATA_REG						0x000C

/* Layer 0 Error Codes (1 to 999) */
#define CAV_SUCCESS						0		/*!< \brief Function call completed without error. */
#define CAV_FAILURE						1		/*!< \brief Function call completed with error. */
#define CAV_ERR_MEM_MAP_SIZE			2		/*!< \brief Invalid memory map size. */
#define CAV_ERR_NO_DEVICE				3		/*!< \brief Device not found */
#define CAV_ERR_CANT_OPEN_DEV			4		/*!< \brief Can't open device */
#define CAV_ERR_DEV_NOT_INITED			5		/*!< \brief Device not initialized */
#define CAV_ERR_DEV_ALREADY_OPEN		6		/*!< \brief Device already open */
#define CAV_ERR_UNSUPPORTED_BACKPLANE	7		/*!< \brief Unsupported backplane in DevID */
#define CAV_ERR_UNSUPPORTED_BOARDTYPE	8		/*!< \brief Unsupported board type in DevID */
#define CAV_ERR_UNSUPPORTED_CHANNELTYPE 9		/*!< \brief Unsupported channel type in DevID */
#define CAV_ERR_CANT_OPEN_DRIVER		10		/*!< \brief Can't open driver */
#define CAV_ERR_CANT_SET_DRV_OPTIONS	11		/*!< \brief Can't set driver options */
#define CAV_ERR_CANT_GET_DEV_INFO		12		/*!< \brief Can't get device info */
#define CAV_ERR_INVALID_BOARD_NUM		13		/*!< \brief Invalid board number */
#define CAV_ERR_INVALID_CHANNEL_NUM		14		/*!< \brief Invalid channel number */
#define CAV_ERR_DRIVER_READ_FAIL		15		/*!< \brief Driver read memory failure */
#define CAV_ERR_DRIVER_WRITE_FAIL		16		/*!< \brief Driver write memory failure */
#define CAV_ERR_DEVICE_CLOSE_FAIL		17		/*!< \brief Device close failure */
#define CAV_ERR_DRIVER_CLOSE_FAIL		18		/*!< \brief Driver close failure */
#define API_ERR_NO_DATA_AVAILABLE       19

/********** Exported Function Prototypes **********/
EXPORT_DLL extern void CAV_L0_CALL_CONV CAV_L0_msSleep(CAV_L0_UINT32 msDelay);
EXPORT_DLL extern CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_MapMemory(CAV_L0_UINT32 devID);
EXPORT_DLL extern CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_UnmapMemory(CAV_L0_UINT32 devID);
EXPORT_DLL extern CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_ReadMem32(CAV_L0_UINT32 devID, CAV_L0_UINT32 offset, CAV_L0_UINT32 *data, CAV_L0_UINT32 count);
EXPORT_DLL extern CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_WriteMem32(CAV_L0_UINT32 devID, CAV_L0_UINT32 offset, CAV_L0_UINT32 *data, CAV_L0_UINT32 count);
EXPORT_DLL extern CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_ReadSetupMem32(CAV_L0_UINT32 devID, CAV_L0_UINT32 offset, CAV_L0_UINT32 *data, CAV_L0_UINT32 count);
EXPORT_DLL extern CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_WriteSetupMem32(CAV_L0_UINT32 devID, CAV_L0_UINT32 offset, CAV_L0_UINT32 *data, CAV_L0_UINT32 count);
EXPORT_DLL extern CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_ReadMem16(CAV_L0_UINT32 devID, CAV_L0_UINT32 offset, CAV_L0_UINT16 *data, CAV_L0_UINT32 count);
EXPORT_DLL extern CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_WriteMem16(CAV_L0_UINT32 devID, CAV_L0_UINT32 offset, CAV_L0_UINT16 *data, CAV_L0_UINT32 count);
EXPORT_DLL extern CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_AttachIntHandler(CAV_L0_UINT32 devID, CAV_L0_UINT32 chanRegOffset, CAV_L0_PUSERISRR pUserISR);
EXPORT_DLL extern CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_DetachIntHandler(CAV_L0_UINT32 devID);



/* A429 Read and Write DDR Memory */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_A429_WriteDDRMem32(CAV_L0_UINT32 devID, CAV_L0_UINT32 offset,CAV_L0_UINT32 *data, CAV_L0_UINT32 count);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_A429_ReadDDRMem32(CAV_L0_UINT32 devID, CAV_L0_UINT32 offset, CAV_L0_UINT32 *data, CAV_L0_UINT32 count);

EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_A429_read_usb (CAV_L0_UINT32 devnum, CAV_L0_UINT32 *lpbuffer, CAV_L0_UINT32 word_addr, CAV_L0_UINT32 count);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L0_A429_write_usb(CAV_L0_UINT32 devnum, CAV_L0_UINT32 *lpbuffer, CAV_L0_UINT32 word_addr, CAV_L0_UINT32 count);
#ifdef __cplusplus
}
#endif

#endif

