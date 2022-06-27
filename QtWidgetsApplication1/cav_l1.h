/******************************************************************************
 * 文件:			CAV_L1.h
 *
 * 版权所有@2013,版权归北京石竹科技有限公司(CAV)所有.
 * 使用此软件受石竹科技许可(最新版本),中国政府或法律和
 * 石竹科技销售条款和条件(最新版本)限制.
 *
 *
 * 功能描述:
 *	   一层头文件.
 *
 *****************************************************************************/
/*! \file CAV_L1.h
 *  \brief Top-level header file for the CAV Layer 1 API
 */
#ifndef _CAV_L1_Header_
#define _CAV_L1_Header_

#include "cav_l0.h"

#ifdef __cplusplus
extern "C" {
#endif



#define		MAX_NUMBER_DEVICES							16
#define		GET_DEVNUM_NUM(x)							((x & 0xF0000)>>16)
/********** Constants **********/
/* L1 API Version Constant */
#define		CAV_L1_API_VERSION							0x02000204  /* Version 2.0.2.4 */

/* Memory offsets (BYTE offsets) */
#define		CAV_L1_MA4_START_A429_CHANNELS				0x00300000  /* Offset to first A429 channel on PMC-MA4 board (after Global Registers) */

/********** Global Device Registers **********/
#define		CAV_L1_GLOBAL_PRODIDREV						0x10008
#define		CAV_L1_GLOBAL_CAPREG						0x10010
#define		CAV_L1_GLOBAL_MEMSIZE						0x10068


/********** Common Device Registers **********/
/* All Alta devices will have these registers in the same locations */
#define		CAV_L1_PE_ROOT_IDVER						0x10008
#define		CAV_L1_PE_BITSTATUS							0x1002C
#define		CAV_L1_IPCORE_INUSE							0x10030

/********** Common Device Startup Options *********/
/* DEVICE API Only Definitions */
#define		CAV_L1_API_DEVICEINIT_NOMEMTEST				0x00000002
#define		CAV_L1_API_DEVICEINIT_ROOTPERESET			0x80000000

#define		CAV_L1_1553_PE_SC_CSR_DATARDY				0x80000000
#define		CAV_L1_A429_IPCORECSR_CHAN_RESET			0x80000000


/*******************************************/
/********** A429 Device Registers **********/
#define		CAV_L1_A429_CHAN_REGS						0x10000
#define		CAV_A429_CHAN_REGS_SIZE						0x0100					

/* A429 Root PE Registers */
#define		CAV_L1_A429_PE_ROOT_CSR						0x10000	/* A429 ROOT PE CONTROL REG */
#define     CAV_L1_A429_PE_TEMP                         0x10060 //温度寄存器
#define		CAV_L1_A429_PECSR_HWINTON					0x00000001
#define		CAV_L1_A429_PECSR_SGON						0x00000010
#define		CAV_L1_A429_PECSR_CLKTRGON					0x00000020
#define		CAV_L1_A429_PECSR_FRCTRGIN					0x00000040
#define		CAV_L1_A429_PECSR_FRCTRGOUT					0x00000080
#define		CAV_L1_A429_PECSR_RDIRIGTM					0x00000100
#define		CAV_L1_A429_PECSR_ZEROTT					0x00000200
#define		CAV_L1_A429_PECSR_SETTT						0x00000400
#define		CAV_L1_A429_PECSR_READTT					0x00000800
#define		CAV_L1_A429_PECSR_USE_EC					0x00001000
#define		CAV_L1_A429_PECSR_EC_FRQIN_1MHZ				0x00002000
#define		CAV_L1_A429_PECSR_EC_FRQIN_5MHZ				0x00004000
#define		CAV_L1_A429_PECSR_EC_FRQIN_10MHZ			0x00008000
#define		CAV_L1_A429_PECSR_SGCHNUM					16
#define		CAV_L1_A429_PECSR_PB_SETTT					0x00100000
#define		CAV_L1_A429_PECSR_PB_READTT					0x00200000
#define		CAV_L1_A429_PECSR_TRIGINLOWTOHIGH			0x00400000
#define		CAV_L1_A429_PECSR_PBON						0x00800000
#define		CAV_L1_A429_PECSR_NOCLKRST					0x01000000
#define		CAV_L1_A429_PECSR_SKPPCBTMBKUP				0x02000000
#define		CAV_L1_A429_PECSR_BITFAIL_INT				0x20000000
#define		CAV_L1_A429_PECSR_RUNIBIT					0x40000000
#define		CAV_L1_A429_PECSR_DEVICE_RESET				0x80000000
#define		CAV_L1_A429_PE_ROOT_STS						0x10004
#define		CAV_L1_A429_PESTS_INTPND					0x00000001
#define		CAV_L1_A429_PESTS_IRIGDET					0x00000400
#define		CAV_L1_A429_PESTS_IRIGLOCK					0x00000800
#define		CAV_L1_A429_PESTS_LOOPFAIL					0x00002000
#define		CAV_L1_A429_PESTS_BITTIMEMASK				0x001F0000	
#define		CAV_L1_A429_PESTS_FR_EN						0x04000000
#define		CAV_L1_A429_PESTS_SC_EN						0x08000000
#define		CAV_L1_A429_PE_ROOT_IDVER					CAV_L1_PE_ROOT_IDVER
#define		CAV_L1_A429_PE_TXRX_CHANCONFIG				0x000C
#define		CAV_L1_A429_PE_RXP_CNTR						0x10014
#define		CAV_L1_A429_PE_TXP_CNTR						0x10018
#define		CAV_L1_A429_PE_TIMEHIGH						0x1001C
#define		CAV_L1_A429_PE_TIMELOW						0x10020
#define		CAV_L1_A429_PE_IRIGTIMEHIGH					0x0024
#define		CAV_L1_A429_PE_IRIGTIMELOW					0x0028
#define		CAV_L1_A429_PE_BITSTATUS					CAV_L1_PE_BITSTATUS
#define		CAV_L1_A429_BIT_MEMTESTFAIL					0x00000002
#define		CAV_L1_A429_BIT_PROCFAIL					0x00000004
#define		CAV_L1_A429_BIT_TTAGFAIL					0x00000008
#define		CAV_L1_A429_BIT_POSTFAIL					0x01000000
#define		CAV_L1_A429_BIT_PBITFAIL					0x02000000
#define		CAV_L1_A429_BIT_IBITFAIL					0x04000000
#define		CAV_L1_A429_BIT_POSTINPROG					0x10000000
#define		CAV_L1_A429_BIT_PBITINPROG					0x20000000
#define		CAV_L1_A429_BIT_IBITINPROG					0x40000000
#define		CAV_L1_A429_PE_SC_CSR_RX1					0x0034
#define		CAV_L1_A429_PE_SC_DATA_RX1					0x0038
#define		CAV_L1_A429_PE_SC_CSR_RX2					0x003C
#define		CAV_L1_A429_PE_SC_DATA_RX2					0x0040
#define		CAV_L1_A429_PE_SC_CSR_DATARDY				0x40000000
#define		CAV_L1_A429_PE_SC_CSR_TRG_ANYACT			0x00000001

#define		CAV_L1_A429_PE_MCRXP_DATATBLPTR				0x10080
#define		CAV_L1_A429_PE_MCRXP_TOTAL_RXPS				0x10084
#define		CAV_L1_A429_PE_MCRXP_CUR_RXP_CNT			0x10088 
#define		CAV_L1_A429_PE_MCRXP_API_INDEX				0x1008C 

#define		CAV_L1_A429_PE_PB_1ST_TIME_HIGH				0x00F8
#define		CAV_L1_A429_PE_PB_1ST_TIME_LOW				0x00FC
/*support PCI /PMC/USB */
#define     CAV_L1_CAPTURE_POSITION                     0x10054
#define		CAV_L1_CAPTURE_SPEED						0x10098
#define		CAV_L1_CAPTURE_LIMIT_VALUE					0x10074
#define		CAV_L1_SINGAL_CAPTURE_CSR					0x10034
#define		CAV_L1_CAPTURE_DATA							0x10038
/*end*/
/*support MiniPCIE/PCIE*/
#define		CAV_L1_SINGAL_CAPTURE_CSR_Updata			0x12520
#define     CAV_L1_CAPTURE_POSITION_Updata              0x12524

#define		CAV_L1_CAPTURE_LIMIT_VALUE_Updata			0x1252C

#define		CAV_L1_CAPTURE_DATA_Updata					0x12530
#define		CAV_L1_CAPTURE_SPEED_Updata					0x12534

#define   CAV_L1_A429_SC_CHANNEL_OFFSET					0x18	
/*end*/
/* A429 Root Variable Voltage */
#define		CAV_L1_A429_VARIABLE_VOLT					0x12500
#define   CAV_L1_A429_VVOLT_CHANNEL_OFFSET              0x4


/* A429 Root Interrupt Registers */
#define		CAV_L1_A429_IQ_START_IQP					0x12300
#define		CAV_L1_A429_IQ_CURR_IQP						0x12304
#define		CAV_L1_A429_IQ_SEQNUM						0x12308
#define		CAV_L1_A429_IQ_API_INDEX					0x12310
#define		CAV_L1_A429_IQ_RESERVE						0x12314
#define		CAV_L1_A429_IQ_RESV_API						0x1232C

/* a429 Interrupt offsets(BYTE offsets)*/
#define		CAV_L1_A429_IQ_NEXT_PTR						0x0000
#define		CAV_L1_A429_IQ_TYPE							0x0004
#define		CAV_L1_A429_IQ_INFO							0x0008

/* A429 Root Signal Generator (SG) Registers */
#define		CAV_L1_A429_ROOT_SG_REGS					0x0130
#define		CAV_L1_A429_SGREG_1ST_SGCB_PTR				0x0130
#define		CAV_L1_A429_SGREG_CUR_SGCB_PTR				0x0134
#define		CAV_L1_A429_SGREG_USER_COUNTER				0x0138
#define		CAV_L1_A429_SGREG_PE_COUNTER				0x013C
#define		CAV_L1_A429_SGREG_PE_OFFSET					0x0140

/* A429 SG Control Block Offsets (BYTE offsets) */
#define		CAV_L1_A429_SGCB_NEXTPTR					0x0000
#define		CAV_L1_A429_SGCB_CSR						0x0004
#define		CAV_L1_A429_SGCB_TIMEHIGH					0x0008
#define		CAV_L1_A429_SGCB_TIMELOW					0x000C
#define		CAV_L1_A429_SGCB_VECCOUNT					0x0010
#define		CAV_L1_A429_SGCB_VECTORS					0x0014

/* A429 SG Vector Constants */
#define		CAV_L1_A429_SG_VECTOR_GND0					0
#define		CAV_L1_A429_SG_VECTOR_LOW					1
#define		CAV_L1_A429_SG_VECTOR_HIGH					2
#define		CAV_L1_A429_SG_VECTOR_GND1					3

/* A429 Root Receive (RX) Registers */
//#define CAV_L1_A429_ROOT_RX_REGS		0x0200  /*modify by lichao for our IPCORE*/
#define		CAV_L1_A429_ROOT_RX_REGS					0x0040
#define		CAV_L1_A429_RXREG_CHAN_SIZE					0x00100
#define		CAV_L1_A429_RXREG_SETUP1					0x0000
#define		CAV_L1_A429_RXREG_SETUP1_RXON				0x00000001
#define		CAV_L1_A429_RXREG_SETUP1_MCRX				0x00000002

#define		CAV_L1_A429_RXREG_SETUP1_717SYNCON			0x00008000
#define		CAV_L1_A429_RXREG_SETUP1_MSB1ST				0x00000008
#define		CAV_L1_A429_RXREG_SETUP1_PARITYODD			0x00000010
#define		CAV_L1_A429_RXREG_SETUP1_PARITYON			0x00000020
#define		CAV_L1_A429_RXREG_SETUP1_MODEBITS			6
#define		CAV_L1_A429_RXREG_SETUP1_ZEROBITDEF			8
#define		CAV_L1_A429_RXREG_SETUP1_ONEBITDEF			12
#define		CAV_L1_A429_RXREG_SETUP1_HLFBITRATE			16
#define		CAV_L1_A429_RXREG_SETUP1_BPW				26

#define		CAV_L1_A429_RXREG_SETUP2					0x0004
#define		CAV_L1_A429_RXREG_RXPCNT					0x0008
#define		CAV_L1_A429_RXREG_CURPTR					0x000C	 
#define		CAV_L1_A429_RXREG_LABELCVTPTR				0x0010   
#define		CAV_L1_A429_RXREG_DATATBLPTR				0x0014	 
#define		CAV_L1_A429_RXREG_MASK1						0x0018   
#define		CAV_L1_A429_RXREG_COMPARE1					0x001C   
#define		CAV_L1_A429_RXREG_MASK2						0x0020   
#define		CAV_L1_A429_RXREG_COMPARE2					0x0024   
#define		CAV_L1_A429_RXP_HDR_CURRENT_RXPCNT			0x0028
#define		CAV_L1_A429_RXP_HDR_API_TAIL_INDEX			0x002C	 
#define		CAV_L1_A429_RXREG_RESERVED_11				0x0030	


/*A429 IO*/
#define     CAV_L1_A429REG_SDISC_OUT                0x10044
#define     CAV_L1_A429REG_SDISC_IN                 0x10048
#define     CAV_L1_A429REG_DDISC_OUT                0x1004C
#define     CAV_L1_A429REG_DDISC_IN                 0x10050

/* A429 API Init Option Values for CAV_L1_A429_RX_Channel_Init() */
#define		CAV_L1_A429_API_RX_MCON						0x00000001
#define		CAV_L1_A429_API_RX_LABELCVTON				0x00000002

/* A429 Root Transmit (TX) Registers */
#define		CAV_L1_A429_ROOT_TX_REGS					0x0000			
#define		CAV_L1_A429_TXREG_CHAN_SIZE					0x0040		
#define		CAV_L1_A429_TXREG_1ST_TXCB_PTR				0x0000
#define		CAV_L1_A429_TXREG_CUR_TXCB_PTR				0x0004
#define		CAV_L1_A429_TXREG_TX_CSR1					0x0008
#define		CAV_L1_A429_TXREG_TX_CSR1_STOP				0x00000000
#define		CAV_L1_A429_TXREG_TX_CSR1_START				0x00000001
#define		CAV_L1_A429_TXREG_TX_CSR1_STOPPED			0x00000002
#define		CAV_L1_A429_TXREG_TX_CSR1_PBMODE			0x00000010
#define		CAV_L1_A429_TXREG_TX_CSR1_PB_WAITFORTRG		0x00000020
#define		CAV_L1_A429_TXREG_TX_CSR1_INTONTXSTOP		0x00004000
#define		CAV_L1_A429_TXREG_TX_CSR2					0x000C
#define		CAV_L1_A429_TXREG_TX_CSR2_MSB1ST			0x00000008
#define		CAV_L1_A429_TXREG_TX_CSR2_HISLEWRATE		0x00000020
#define		CAV_L1_A429_TXREG_TX_CSR2_LOWSLEWRATE		0x00000000
#define		CAV_L1_A429_TXREG_TX_CSR2_MODEBITS			6
#define		CAV_L1_A429_TXREG_CSR2_ZEROBITDEF			8
#define		CAV_L1_A429_TXREG_CSR2_ONEBITDEF			12
#define		CAV_L1_A429_TXREG_CSR2_HLFBITRATE			16
#define		CAV_L1_A429_TXREG_CSR2_BPW					26
#define		CAV_L1_A429_TXREG_TXP_COUNT					0x0010
#define     CAV_L1_A429_TXREG_APERIODIC_TXP				0x0014
#define		CAV_L1_A429_APIAPERIODICSET					0x04000000
#define		CAV_L1_A429_TXREG_API_TXCB_PTR				0x0018
#define		CAV_L1_A429_TXREG_API_TXCB_SIZE				0x001C
#define		CAV_L1_A429_TXREG_API_TAILPTR				0x0020
#define		CAV_L1_A429_TXREG_API_FUN_MARK				0x0024   /*function mark  AD:1  voltage:2   717:4*/
#define     CAV_L1_A429_CH_TX_EN						0x0000000C

/*function mark bute offsets*/
#define      CAV_L1_A429_TXP_AD                          0x1
#define      CAV_L1_A429_TXP_Voltage                     0x2
#define      CAV_L1_A429_TXP_A717                        0x4
/*TXP control byte offsets*/
#define     CAV_L1_A429_TXP_CONTROL_PARITYON			0x00000020 
#define     CAV_L1_A429_TXP_CONTROL_PARITYODD			0x00000010 

#define     CAV_L1_A429_RX_PARITYON			0x00000020 
#define     CAV_L1_A429_RX_PARITYODD			0x00000010 

#define     CAV_L1_A429_TX_PARITYON			0x00000020 
#define     CAV_L1_A429_TX_PARITYODD			0x00000010 
/* A429 RX SETUP1 MODEBITS Values */
#define		CAV_L1_A429_RXREG_SETUP1_MODEBITS_429PHY	0
//#define		CAV_L1_A429_RXREG_SETUP1_MODEBITS_5VRAW		1
#define		CAV_L1_A429_RXREG_SETUP1_MODEBITS_5V717		1

/* A429 TX CSR2 MODEBITS Values */
#define		CAV_L1_A429_RXREG_SETUP1_MODEBITS_429PHY	0
#define		CAV_L1_A429_TXREG_SETUP2_MODEBITS_5V717		1
//#define		CAV_L1_A429_TXREG_SETUP2_MODEBITS_5V717		0
#define     CAV_L1_A429_TXREG_SETUP2_RATE717            1         


/******* A429 Extended Memory Definitions and Data Structure Offsets (Byte Offsets) *******/
/* API Number of Labels per ARINC Word (first 8 bits of word) */
#define		CAV_L1_A429_API_NUMOF429LABELS				256

#define		CAV_DDR_MEM_READ_ADDR_REG					0x0004
#define		CAV_DDR_MEM_WRITE_ADDR_REG					0x0008
#define		CAV_DDR_MEM_DATA_REG						0x000C
	
/* A429 Receive Packet (RXP) Offsets (BYTE offsets) */
#define		CAV_L1_A429_RXP_SIZE						0x0010
#define		CAV_L1_A429_RXP_CONTROL						0x0000
#define		CAV_L1_A429_RXP_CONTROL_TRGOUT				0x20000000
#define		CAV_L1_A429_RXP_CONTROL_INTERRUPT			0x40000000
#define		CAV_L1_A429_RXP_CONTROL_DECERROR			0x80000000
#define		CAV_L1_A429_RXP_TIMEHIGH					0x0004
#define		CAV_L1_A429_RXP_TIMELOW 					0x0008
#define		CAV_L1_A429_RXP_DATA						0x000C

/* A429 RXP Data Table Offsets (BYTE offsets) */
#define		CAV_L1_A429_RXP_HDR_TOTAL_RXPCNT			0x0000


/* A429 Transmit (TX) Control Block Offsets (BYTE offsets */
#define		CAV_L1_A429_TXCB_SIZE						0x0040
#define		CAV_L1_A429_TXCB_NEXTPTR					0x0000
#define		CAV_L1_A429_TXCB_NO_NEXT_TXCB				0xFFFFFFFF
#define		CAV_L1_A429_TXCB_TXTIMEVALUE				0x0004
#define		CAV_L1_A429_TXCB_TXTIMEINCREMENT			0x0008
#define		CAV_L1_A429_TXCB_CONTROL					0x000C
#define		CAV_L1_A429_TXCB_CONTROL_STOPONTXBCOMP		0x00000010
#define		CAV_L1_A429_TXCB_CONTROL_INTONTXBCOMP		0x00000100
#define		CAV_L1_A429_TXCB_TXPPTR						0x0010
#define		CAV_L1_A429_TXCB_TXPCOUNT					0x0014
#define		CAV_L1_A429_TXCB_PECOUNT					0x0018
#define     CAV_L1_A429_TXCB_MOU                        0x001C
#define		CAV_L1_A429_TXCB_APITXCBNUM					0x002C
#define		CAV_L1_A429_TXCB_APINUMTXPS					0x0030
#define		CAV_L1_A429_TXCB_API1STTXPPTR				0x0034

/* A429 Transmit Packet (TXP) Offsets (BYTE offsets) */
#define		CAV_L1_A429_TXP_SIZE						0x0010
#define		CAV_L1_A429_TXP_CONTROL						0x0000
#define		CAV_L1_A429_TXP_CONTROL_DELAYONLY			0x00000001
#define		CAV_L1_A429_TXP_CONTROL_TRIGIN				0x00000002
#define		CAV_L1_A429_TXP_CONTROL_TRIGOUT				0x00000004
#define		CAV_L1_A429_TXP_CONTROL_INTERRUPT			0x00000008
#define		CAV_L1_A429_TXP_CONTROL_PARITYODD			0x00000010
#define		CAV_L1_A429_TXP_CONTROL_PARITYON			0x00000020
#define		CAV_L1_A429_TXP_RESERVED					0x0004
#define		CAV_L1_A429_TXP_DELAY						0x0008
#define		CAV_L1_A429_TXP_DATA						0x000C

/* A429 Playback (PB) Control Block Offsets (BYTE offsets */
#define		CAV_L1_A429_PBCB_SIZE						0x0040
#define		CAV_L1_A429_PBCB_NEXTPTR					0x0000
#define		CAV_L1_A429_PBCB_NO_NEXT_PBCB				0xFFFFFFFF
#define		CAV_L1_A429_PBCB_CONTROL					0x000C
#define		CAV_L1_A429_PBCB_CONTROL_STOPONPBCBCOMP		0x00000010
#define		CAV_L1_A429_PBCB_CONTROL_INTONPBCBCOMP		0x00000100
#define		CAV_L1_A429_PBCB_PXPPTR						0x0010
#define		CAV_L1_A429_PBCB_PXPCOUNT					0x0014
#define		CAV_L1_A429_PBCB_PECOUNT					0x0018
#define		CAV_L1_A429_PBCB_APIPBCBNUM					0x002C
#define		CAV_L1_A429_PBCB_APINUMPXPS					0x0030
#define		CAV_L1_A429_PBCB_API1STPBPPTR				0x0034

/* A429 Playback: API Option Bit for CAV_L1_A429_PB_RXPWrite() */
#define		CAV_L1_A429_PB_API_ATON						0x80000000

/* A429 Playback Transmit Packet (PXP) Offsets (BYTE offsets) */
#define		CAV_L1_A429_PXP_SIZE						0x0010
#define		CAV_L1_A429_PXP_CONTROL						0x0000
#define		CAV_L1_A429_PXP_TIMEHIGH					0x0004
#define		CAV_L1_A429_PXP_TIMELOW 					0x0008
#define		CAV_L1_A429_PXP_DATA						0x000C

/* A429 Interrupt Offsets (BYTE offsets) */
#define		CAV_L1_A429_IQP_NEXTPTR						0x0000
#define		CAV_L1_A429_IQP_TYPESEQ						0x0004
#define		CAV_L1_A429_IQP_TYPESEQ_SEQNUM				0x000000FF
#define		CAV_L1_A429_IQP_TYPESEQ_CHNUM				0x00000F00
#define		CAV_L1_A429_IQP_TYPESEQ_SG					0x00010000

#define		CAV_L1_A429_IQP_TYPESEQ_CVTRXP				0x00040000
#define		CAV_L1_A429_IQP_TYPESEQ_BIT					0x00100000
#define		CAV_L1_A429_IQP_TYPESEQ_TXPBCB				0x02000000
#define		CAV_L1_A429_IQP_TYPESEQ_TXPBSTOP			0x08000000
#define		CAV_L1_A429_IQP_TYPESEQ_TXPBXP				0x10000000
#define		CAV_L1_A429_IQP_TYPESEQ_MCRXP				0x20000000
#define		CAV_L1_A429_IQP_TYPESEQ_CHRXP				0x40000000
#define		CAV_L1_A429_IQP_TYPESEQ_MSKRXP				0x80000000
#define		CAV_L1_A429_IQP_DSPTR						0x0008


/*********************************************/
/********** Memory Sizes (in BYTES) **********/
#define		CAV_L1_A429_CHAN_MEM_SIZE					0x8000000
///MINIPCIE的内存空间
#define		CAV_L1_MINIPCIEA429_CHAN_MEM_SIZE					0x400000
#define		CAV_L1_MINIPCIEA429A429_USER_MEM_START					0x200000

#define		CAV_L1_SIMA429_CHAN_SIZE					0x100000	/* SIM-A429 Board */
#define		CAV_L1_TESTA429_CHAN_SIZE					0x100000	/* TEST-A429 Board */
#define		CAV_L1_PMCA429_CHAN_SIZE					0x100		/* PMC-A429 Board */ 
#define		CAV_L1_PCIA429_CHAN_SIZE					0x100000	/* PCI-A429 Board */
#define		CAV_L1_PC104PA429_CHAN_SIZE					0x100000	/* PC104P-A429 Board */
#define		CAV_L1_PCCDA429_CHAN_SIZE					0x100000	/* PCCD-A429 Board */
#define		CAV_L1_PCI104EA429_CHAN_SIZE				0x100000	/* PCI104E-A429 Board */
#define		CAV_L1_XMCE4LA429_CHAN_SIZE					0x100000	/* XMCE4L-A429 Board */
#define		CAV_L1_ECD54_A429_CHAN_SIZE					0x100000	/* ECD54-A429 Board */
#define		CAV_L1_PCIE4LA429_CHAN_SIZE					0x100000	/* PCIE4L-A429 Board */

#define		CAV_L1_PMCMA4_CHAN_SIZE						0x080000	/* PMC-MA4 1553/ARINC Board */


#define		CAV_L1_A429_USER_MEM_START					0x0000
#define		CAV_L1_A429_IQ_ENTRY_SIZE					0x0010

/********* Layer 1 Error Codes (1000 to 1999) *********/
#define		CAV_ERR_BAD_INPUT							1000		/*!< \brief Bad input parameters. */
#define		CAV_ERR_MEM_TEST_FAIL						1001		/*!< \brief Failed memory test. */
#define		CAV_ERR_MEM_MGT_NO_INIT						1002		/*!< \brief Memory Management not initialized for the device ID */
#define		CAV_ERR_MEM_MGT_INIT						1003		/*!< \brief Memory Management already initialized for the device ID */
#define		CAV_ERR_MEM_MGT_NO_MEM						1004		/*!< \brief Not enough memory available */
#define		CAV_ERR_BAD_DEV_TYPE						1005		/*!< \brief Bad device type in device ID */
#define		CAV_ERR_RT_FT_UNDEF							1006		/*!< \brief RT Filter Table not defined */
#define		CAV_ERR_RT_SA_UNDEF							1007		/*!< \brief RT Subaddress not defined */
#define		CAV_ERR_RT_SA_CDP_UNDEF						1008		/*!< \brief RT SA CDP not defined */
#define		CAV_ERR_IQ_NO_NEW_ENTRY						1009		/*!< \brief No new entry in interrupt queue */
#define		CAV_ERR_NO_BCCB_TABLE						1010		/*!< \brief BCCB Table Pointer is zero */
#define		CAV_ERR_BCCB_ALREADY_ALLOCATED				1011		/*!< \brief BCCB already allocated */
#define		CAV_ERR_BCCB_NOT_ALLOCATED					1012		/*!< \brief BCCB has not been allocated */
#define		CAV_ERR_BUFFER_FULL							1013		/*!< \brief 1553-ARINC PB (CDP/PCB or RXP/PXP) buffer is full */
#define		CAV_ERR_TIMEOUT								1014		/*!< \brief Timeout error. */
#define		CAV_ERR_BAD_CHAN_NUM						1015		/*!< \brief Bad channel number or channel does not exist on this board */
#define		CAV_ERR_BITFAIL								1016		/*!< \brief Built-In Test failure */
#define		CAV_ERR_DEVICEINUSE							1017		/*!< \brief Device in use already */
#define		CAV_ERR_NO_TXCB_TABLE						1018		/*!< \brief TXCB Table Pointer is zero */
#define		CAV_ERR_TXCB_ALREADY_ALLOCATED				1019		/*!< \brief TXCB already allocated */
#define		CAV_ERR_TXCB_NOT_ALLOCATED					1020		/*!< \brief TXCB has not been allocated */
#define		CAV_ERR_PBCB_TOOMANYPXPS					1021		/*!< \brief PBCB Too Many PXPs For PCBC Allocation */
#define		CAV_ERR_NORXCHCVT_ALLOCATED					1022		/*!< \brief RX CH - No CVT Option Defined at Init */


/*717 register*/

#define		CAV_L1_A717_RXREG_CSR           0x0028
#define		CAV_L1_A717_RXREG_SYNC1			0x0034
#define		CAV_L1_A717_RXREG_SYNC2			0x0038
#define		CAV_L1_A717_RXREG_SYNC3			0x003C
#define		CAV_L1_A717_RXREG_SYNC4			0x0040
#define     CAV_L1_A429_RXREG_RxpCount     0x0044

#define    CAV_L1_A429_Channel34                         0x2700


/*717 channel num define*/

#if 0
#define    CAV_L1_A717_Channel_01           32
#define    CAV_L1_A717_Channel_02           33
#define    CAV_L1_A717_Channel_03           33
#define    CAV_L1_A717_Channel_04           34

#endif


/*!!!!!!!!!!!!!!!!!!!!!!!!!!*/

/*! \brief A429 Receive Packet structure */
typedef struct CAV_l1_a429_rxp {
	CAV_L0_UINT32 Control;						/*!< \brief Control Word */
	CAV_L0_UINT32 TimeHigh;						/*!< \brief Timestamp, upper 32-bits */
	CAV_L0_UINT32 TimeLow;						/*!< \brief Timestamp, lower 32-bits */
	CAV_L0_UINT32 Data;							/*!< \brief ARINC word */
} CAV_L1_A429_RXP;

typedef struct CAV_l1_a429_rxp_division {
	CAV_L0_UINT32 Control;						/*!< \brief Control Word */
	CAV_L0_UINT32 TimeHigh;						/*!< \brief Timestamp, upper 32-bits */
	CAV_L0_UINT32 TimeLow;						/*!< \brief Timestamp, lower 32-bits */
	CAV_L0_UINT32 Label_num;							/*!< \brief ARINC Label */
	CAV_L0_UINT32 Data_block;                   /*9~31*/
	CAV_L0_UINT32 parity_bit;					/*32*/
} CAV_L1_A429_RXP_Division;

/*! \brief A429 Transmit Packet structure */
typedef struct CAV_l1_a429_txp {
	CAV_L0_UINT32 Control;						/*!< \brief Control Word */
	CAV_L0_UINT32 Reserved;						/*!< \brief Reserved Word */
	CAV_L0_UINT32 Delay;						/*!< \brief Delay Word (100ns LSB) */
	CAV_L0_UINT32 Data;							/*!< \brief ARINC word */
} CAV_L1_A429_TXP;

/*! \brief A429 Transmit Control Block structure */
typedef struct CAV_l1_a429_txcb {
	CAV_L0_UINT32 TxcbNum;						/*!< \brief TXCB number */
	CAV_L0_UINT32 NextTxcbNum;					/*!< \brief Next TXCB number */
	CAV_L0_UINT32 Control;						/*!< \brief Control Word */
	CAV_L0_UINT32 TotalTxpCount;				/*!< \brief Number of TxP for this block */
	CAV_L0_UINT32 CurrTxpIndex;					/*!< \brief Index to current TxP */
	CAV_L0_UINT32 TxPeriod1ms;				/*!< \brief TX Period, 500us LSB */
	CAV_L0_UINT32 SendTxpCount;              /*send data count*/
} CAV_L1_A429_TXCB;
typedef struct TX_Aperiodic_set
{
	CAV_L0_UINT32 parityOn;
	CAV_L0_UINT32 parityOdd;
}CAV_L1_Tx_Parity;

typedef struct TX_Bit_Direction
{
	CAV_L0_UINT32 highBitPriority;
	CAV_L0_UINT32 LabelReversal;
}CAV_L1_TX_BitDirection;
typedef struct RX_Bit_Direction
{
	CAV_L0_UINT32 highBitPriority;
	CAV_L0_UINT32 LabelReversal;
}CAV_L1_RX_BitDirection;

typedef struct Data_structure
{
	CAV_L0_UINT32 Label_num;
	CAV_L0_UINT32 Data_block;
}CAV_L1_DataStructure;
/********** Exported Function Prototypes **********/
/* General */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_DevicePresent(CAV_L0_UINT32 devID,
													CAV_L0_UINT32 *config);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_InitDevice(CAV_L0_UINT32 devID,
												 CAV_L0_UINT32 startupOptions);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_CloseDevice(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_GetVersionInfo(CAV_L0_UINT32 devID,
									CAV_L0_UINT32 *peVersion,
									CAV_L0_UINT32 *layer0ApiVersion,
									CAV_L0_UINT32 *layer1ApiVersion);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_GetBoardInfo(CAV_L0_UINT32 devID,
									CAV_L0_UINT32 *prodIDandRev,
									CAV_L0_UINT32 *capabilitiesReg,
									CAV_L0_UINT32 *memorySize);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_msSleep(CAV_L0_UINT32 milliSecTick);


/***** Internal Functions ******/
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV Internal_GetChannelRegOffset(CAV_L0_UINT32 devID,
										   CAV_L0_UINT32 *pChannel,
										   CAV_L0_UINT32 *pChannelRegOffset);

/* Memory Management */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_InitMemMgmt(CAV_L0_UINT32 devID, 
												  CAV_L0_UINT32 startupOptions);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_CloseMemMgmt(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_MemoryAlloc(CAV_L0_UINT32 devID,
								 CAV_L0_UINT32 memSize,
								 CAV_L0_UINT32 *pMemOffset);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_MemoryFree(CAV_L0_UINT32 devID,
								CAV_L0_UINT32 memStart,
								CAV_L0_UINT32 memSize);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_GetMemoryAvailable(CAV_L0_UINT32 devID,
										CAV_L0_UINT32 *memAvailable);

/* BIT */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_BIT_MemoryTest(CAV_L0_UINT32 devID,
									   CAV_L0_UINT32 start,
									   CAV_L0_UINT32 end,
									   CAV_L0_UINT32 *addr,
									   CAV_L0_UINT32 *exp,
									   CAV_L0_UINT32 *act);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_BIT_InitiatedBIT(CAV_L0_UINT32 devID,
													  CAV_L0_UINT32 *bitStatus);

/* Interrupts */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_INT_HandlerAttach(CAV_L0_UINT32 devID,
									   CAV_L0_PUSERISRR pUserISR);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_INT_HandlerDetach(CAV_L0_UINT32 devID);


/********** A429 Functions **********/
/* A429 General */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_InitDefault(CAV_L0_UINT32 devID,
													   CAV_L0_UINT32 numIQEntries);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_InitDefault_ExtendedOptions(CAV_L0_UINT32 devID, 
																	   CAV_L0_UINT32 numIQEntries, 
																	   CAV_L0_UINT32 startupOptions);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_InitDevice(CAV_L0_UINT32 devID,
													  CAV_L0_UINT32 numIQEntries);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_GetConfig(CAV_L0_UINT32 devID,
													 CAV_L0_UINT32 *pChanConfig);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_GetPEInfo(CAV_L0_UINT32 devID,
													 CAV_L0_UINT32 *peInfo);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TimeSet(CAV_L0_UINT32 devID,
												   CAV_L0_UINT32 timeHigh,
												   CAV_L0_UINT32 timeLow);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TimeGet(CAV_L0_UINT32 devID,
												   CAV_L0_UINT32 *pTimeHigh,
												   CAV_L0_UINT32 *pTimeLow);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_PBTimeSet(CAV_L0_UINT32 devID, 
													 CAV_L0_UINT32 timeHigh, 
													 CAV_L0_UINT32 timeLow);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_PBTimeGet(CAV_L0_UINT32 devID, 
													 CAV_L0_UINT32 *pTimeHigh, 
													 CAV_L0_UINT32 *pTimeLow);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TimeClear(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SC_IsSupport(CAV_L0_UINT32 devID,
																   CAV_L0_UINT32 ChanNum,
																   CAV_L0_UINT32* IsSupport);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SC_ArmTrigger(CAV_L0_UINT32 devID,
														 CAV_L0_UINT32 bitRate,
														 CAV_L0_UINT32 triggerPosition);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SC_ReadBuffer(CAV_L0_UINT32 devID,
														 CAV_L0_UINT8 *buffer);

EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SC_ArmTrigger_Updata(CAV_L0_UINT32 devID,
																	CAV_L0_UINT32 ChanNum,
																	CAV_L0_UINT32 bitRate,
																	CAV_L0_UINT32 triggerPosition);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SC_ReadBuffer_Updata(CAV_L0_UINT32 devID,
																	CAV_L0_UINT32 ChanNum,
																	CAV_L0_UINT8 *buffer);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_Global_I2C_ReadTemp(CAV_L0_UINT32 devID,
														  float *temp);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_Channel_Voltage_IsSupport(CAV_L0_UINT32 devID,
																   CAV_L0_UINT32 ChanNum,
																   CAV_L0_UINT32* IsSupport);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV  CAV_L1_Set_Channel_Voltage(CAV_L0_UINT32 devID, 
																	  CAV_L0_UINT32 ChanNum,
																	  CAV_L0_UINT32 value);

EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_Channel_A717_IsSupport(CAV_L0_UINT32 devID,
																				CAV_L0_UINT32 ChanNum,
																				CAV_L0_UINT32* IsSupport);

/* A429 Interrupt */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_INT_EnableInt(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_INT_DisableInt(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_INT_CheckDeviceIntPending(CAV_L0_UINT32 devID,
																	  CAV_L0_UINT32 *pIsIntPending);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_INT_IQ_ReadEntry(CAV_L0_UINT32 devID,
															CAV_L0_UINT32 *pType,
															CAV_L0_UINT32 *pInfo);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_INT_IQ_ReadNewEntries(CAV_L0_UINT32 devID,
																 CAV_L0_UINT32 maxNumEntries,
																 CAV_L0_UINT32 *pNumEntries,
																 CAV_L0_UINT32 *pType,
																 CAV_L0_UINT32 *pInfo);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_INT_SetIntSeqNum(CAV_L0_UINT32 devID,
															CAV_L0_UINT32 seqNum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_INT_GetIntSeqNum(CAV_L0_UINT32 devID,
															CAV_L0_UINT32 *pSeqNum);

/* A429 Transmit */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_Init(CAV_L0_UINT32 devID,
														   CAV_L0_UINT32 TxChanNum,
														   CAV_L0_UINT32 BitRateHz,
														   CAV_L0_UINT32 numTXCB,
														    CAV_L1_TX_BitDirection *BitDir);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_Close(CAV_L0_UINT32 devID,
															CAV_L0_UINT32 TxChanNum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_CB_TXPAllocate(CAV_L0_UINT32 devID,
																	 CAV_L0_UINT32 TxChanNum,
																	 CAV_L0_UINT32 msgnum,
																	 CAV_L0_UINT32 numTXP);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_CB_TXPFree(CAV_L0_UINT32 devID,
																 CAV_L0_UINT32 TxChanNum,
																 CAV_L0_UINT32 msgnum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_CB_Write(CAV_L0_UINT32 devID,
															   CAV_L0_UINT32 TxChanNum,
															   CAV_L0_UINT32 msgnum,
															   CAV_L1_A429_TXCB *txcb);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_CB_Read(CAV_L0_UINT32 devID,
															  CAV_L0_UINT32 TxChanNum,
															  CAV_L0_UINT32 msgnum,
															  CAV_L1_A429_TXCB *txcb);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_CB_TXPWrite(CAV_L0_UINT32 devID,
																  CAV_L0_UINT32 TxChanNum,
																  CAV_L0_UINT32 msgnum,
																  CAV_L0_UINT32 txpNum,
																  CAV_L1_A429_TXP *pTxp);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_CB_TXPRead(CAV_L0_UINT32 devID,
																 CAV_L0_UINT32 TxChanNum,
																 CAV_L0_UINT32 msgnum,
																 CAV_L0_UINT32 txpNum,
																 CAV_L1_A429_TXP *pTxp);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_Start(CAV_L0_UINT32 devID,
															CAV_L0_UINT32 TxChanNum,
															CAV_L0_UINT32 msgnum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_Stop(CAV_L0_UINT32 devID,
														   CAV_L0_UINT32 TxChanNum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_IsRunning(CAV_L0_UINT32 devID,
																CAV_L0_UINT32 TxChanNum,
																CAV_L0_UINT32 *pIsRunning);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_Enable(CAV_L0_UINT32 devID,
																		CAV_L0_UINT32 TxChanNum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_SendLabel(CAV_L0_UINT32 devID,
																CAV_L0_UINT32 TxChanNum,
																CAV_L1_DataStructure *DataStructure,
																CAV_L1_Tx_Parity *parity);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_SendData(CAV_L0_UINT32 devID,
																		   CAV_L0_UINT32 TxChanNum,
																		   CAV_L0_UINT32 Data,
																		   CAV_L1_Tx_Parity *parity);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_Disable(CAV_L0_UINT32 devID,
																		   CAV_L0_UINT32 TxChanNum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_SetConfig(CAV_L0_UINT32 devID,
																CAV_L0_UINT32 TxChanNum,
																CAV_L0_UINT32 CSR1,
																CAV_L0_UINT32 CSR2);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_GetConfig(CAV_L0_UINT32 devID,
																CAV_L0_UINT32 TxChanNum,
																CAV_L0_UINT32 *pCSR1,
																CAV_L0_UINT32 *pCSR2);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_GetTXCBTxpCount(CAV_L0_UINT32 devID,
																	  CAV_L0_UINT32 TxChanNum,
																	  CAV_L0_UINT32 msgnum,
																	  CAV_L0_UINT32 *txpCnt);

EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_SendFrameConfig(CAV_L0_UINT32 devID,
																			 CAV_L0_UINT32 TxChanNum,
																			  CAV_L0_UINT32 msgnum,
																			CAV_L0_UINT32 TxPeriod1ms,
																			CAV_L0_UINT32 nums,
																			CAV_L0_UINT32 SendFrameCount);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_SendDataConfig(CAV_L0_UINT32 devID,
																				CAV_L0_UINT32 TxChanNum,
																				CAV_L0_UINT32 msgnum,
																				CAV_L0_UINT32 datanum,
																				CAV_L1_DataStructure *DataStructure);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV  CAV_L1_A429_TX_Channel_Setup(CAV_L0_UINT32 devID,
																		CAV_L0_UINT32 TxChanNum,
																		CAV_L0_UINT32 msgnum,
																		CAV_L0_UINT32 datanum,
																		CAV_L1_Tx_Parity *parity);

/* A429 Receive */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_Init(CAV_L0_UINT32 devID,
														   CAV_L0_UINT32 RxChanNum,
														   CAV_L0_UINT32 numRxP,
														   CAV_L0_UINT32 options,
														   CAV_L1_RX_BitDirection *BitDir);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_Setup(CAV_L0_UINT32 devID,
															CAV_L0_UINT32 RxChanNum,
															CAV_L0_UINT32 parityon,
															CAV_L0_UINT32 parityodd);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_Close(CAV_L0_UINT32 devID,
															CAV_L0_UINT32 RxChanNum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_Start(CAV_L0_UINT32 devID,
															CAV_L0_UINT32 RxChanNum,
															CAV_L0_UINT32 IntEnableType);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_Stop(CAV_L0_UINT32 devID,
														   CAV_L0_UINT32 RxChanNum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_ReadNewRxPs(CAV_L0_UINT32 devID,
																  CAV_L0_UINT32 RxChanNum,
																  CAV_L0_UINT32 maxNumRxPs,
																  CAV_L0_UINT32 *pNumRxPs,
																  CAV_L1_A429_RXP *pRxPBuffer);

EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_ReadNewRxPs_Label(CAV_L0_UINT32 devID,
																			 CAV_L0_UINT32 RxChanNum,
																			 CAV_L0_UINT32 maxNumRxPs,
																			 CAV_L0_UINT32 *pNumRxPs,
																			 CAV_L1_A429_RXP_Division *pRxPBuffer);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_ReadRxP(CAV_L0_UINT32 devID,
															  CAV_L0_UINT32 RxChanNum,
															  CAV_L0_UINT32 RxP_index,
															  CAV_L1_A429_RXP *pRxP);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_CVTReadRxP(CAV_L0_UINT32 devID,
																  CAV_L0_UINT32 RxChanNum, 
																  CAV_L0_UINT32 labelIndex,  
																  CAV_L1_A429_RXP *pRxP);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_WriteRxP(CAV_L0_UINT32 devID,
															   CAV_L0_UINT32 RxChanNum,
															   CAV_L0_UINT32 RxP_index,
															   CAV_L1_A429_RXP *pRxP);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_CVTWriteRxP(CAV_L0_UINT32 devID,
																  CAV_L0_UINT32 RxChanNum, 
																  CAV_L0_UINT32 labelIndex,  
																  CAV_L1_A429_RXP *pRxP);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_SetConfig(CAV_L0_UINT32 devID,
																CAV_L0_UINT32 RxChanNum,
																CAV_L0_UINT32 Setup1,
																CAV_L0_UINT32 Setup2);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_GetConfig(CAV_L0_UINT32 devID,
																CAV_L0_UINT32 RxChanNum,
																CAV_L0_UINT32 *pSetup1,
																CAV_L0_UINT32 *pSetup2);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_SetMaskCompare(CAV_L0_UINT32 devID,
																	 CAV_L0_UINT32 RxChanNum,
																	 CAV_L0_UINT32 mask1,
																	 CAV_L0_UINT32 compare1,
																	 CAV_L0_UINT32 mask2,
																	 CAV_L0_UINT32 compare2);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RX_Channel_GetMaskCompare(CAV_L0_UINT32 devID,
																	 CAV_L0_UINT32
																	 RxChanNum,
																	 CAV_L0_UINT32 *pMask1,
																	 CAV_L0_UINT32 *pCompare1,
																	 CAV_L0_UINT32 *pMask2,
																	 CAV_L0_UINT32 *pCompare2);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A717_RX_Channel_SetConfig(CAV_L0_UINT32 devID,
																		   CAV_L0_UINT32 RxChanNum,
																		   CAV_L0_UINT32 Csr,
																		   CAV_L0_UINT32 Sync1,
																		   CAV_L0_UINT32 Sync2,
																		   CAV_L0_UINT32 Sync3,
																		   CAV_L0_UINT32 Sync4);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A717_RX_Channel_GetConfig(CAV_L0_UINT32 devID,
																		   CAV_L0_UINT32  RxChanNum,
																		   CAV_L0_UINT32 *Csr,
																		   CAV_L0_UINT32 *pSync1,
																		   CAV_L0_UINT32 *pSync2,
																		   CAV_L0_UINT32 *pSync3,
																		   CAV_L0_UINT32 *pSync4);

EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A717_RX_Channel_Setup(CAV_L0_UINT32 devID,
																	   CAV_L0_UINT32  RxChanNum,
																	   CAV_L0_UINT32 BitRateHz);
/* A429 Multi-Channel Receive */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RXMC_BufferCreate(CAV_L0_UINT32 devID,
															 CAV_L0_UINT32 numRxP);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RXMC_BufferFree(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RXMC_ReadNewRxPs(CAV_L0_UINT32 devID,
														   CAV_L0_UINT32 maxNumRxPs,
														   CAV_L0_UINT32 *pNumRxPs,
														   CAV_L1_A429_RXP *pRxPBuffer);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RXMC_ReadNewRxPs_Label(CAV_L0_UINT32 devID,
																	   CAV_L0_UINT32 maxNumRxPs,
																	   CAV_L0_UINT32 *pNumRxPs,
																	   CAV_L1_A429_RXP_Division *pRxPBuffer);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RXMC_ReadRxP(CAV_L0_UINT32 devID,
														CAV_L0_UINT32 RxP_index,
														CAV_L1_A429_RXP *pRxP);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_RXMC_WriteRxP(CAV_L0_UINT32 devID,
														CAV_L0_UINT32 RxP_index,
														CAV_L1_A429_RXP *pRxP);

/* A429 Playback */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_Init(CAV_L0_UINT32 devID,
															  CAV_L0_UINT32 TxChanNum,
															  CAV_L0_UINT32 BitRateHz,
															  CAV_L0_UINT32 numTXCB);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_Close(CAV_L0_UINT32 devID,
															   CAV_L0_UINT32 TxChanNum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_CB_PXPAllocate(CAV_L0_UINT32 devID,
																		CAV_L0_UINT32 TxChanNum,
																		CAV_L0_UINT32 PBCBnum,
																		CAV_L0_UINT32 numPXP);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_CB_PXPFree(CAV_L0_UINT32 devID,
																	CAV_L0_UINT32 TxChanNum,
																	CAV_L0_UINT32 PBCBnum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_CB_Write(CAV_L0_UINT32 devID,
																 CAV_L0_UINT32 TxChanNum,
																 CAV_L0_UINT32 PBCBnum,
																 CAV_L1_A429_TXCB *txcb);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_CB_Read(CAV_L0_UINT32 devID,
																 CAV_L0_UINT32 TxChanNum,
																 CAV_L0_UINT32 PBCBnum,
																 CAV_L1_A429_TXCB *txcb);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_CB_PXPRead(CAV_L0_UINT32 devID,
																	CAV_L0_UINT32 TxChanNum,
																	CAV_L0_UINT32 PBCBnum,
																	CAV_L0_UINT32 txpNum,
																	CAV_L1_A429_RXP *pTxp);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_Start(CAV_L0_UINT32 devID,
															   CAV_L0_UINT32 TxChanNum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_Stop(CAV_L0_UINT32 devID,
															  CAV_L0_UINT32 TxChanNum);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_PB_Start(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_PB_Stop(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_IsRunning(CAV_L0_UINT32 devID,
																   CAV_L0_UINT32 TxChanNum,
																   CAV_L0_UINT32 *pIsRunning);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_SetConfig(CAV_L0_UINT32 devID,
																   CAV_L0_UINT32 TxChanNum,
																   CAV_L0_UINT32 CSR1,
																   CAV_L0_UINT32 CSR2);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_GetConfig(CAV_L0_UINT32 devID,
																   CAV_L0_UINT32 TxChanNum,
																   CAV_L0_UINT32 *pCSR1,
																   CAV_L0_UINT32 *pCSR2);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_TX_Channel_PB_RXPWrite(CAV_L0_UINT32 devID,
																  CAV_L0_UINT32 txChanNum,
																  CAV_L0_UINT32 numRxps,
																  CAV_L1_A429_RXP *RxpBuffer,
																  CAV_L0_UINT32 options,
																  CAV_L0_UINT32 isFirstMsg);

/* A429 Signal Generator */
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SG_Configure(CAV_L0_UINT32 devID,
														CAV_L0_UINT32 txChannel,
														CAV_L0_UINT32 slewRate);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SG_CreateSGCB(CAV_L0_UINT32 devID,
														 CAV_L0_UINT32 timeHigh,
														 CAV_L0_UINT32 timeLow,
														 CAV_L0_UINT32 *pVectors,
														 CAV_L0_UINT32 numVectors);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SG_Free(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SG_Start(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SG_Stop(CAV_L0_UINT32 devID);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SG_IsRunning(CAV_L0_UINT32 devID,
														CAV_L0_UINT32 *pIsRunning);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SG_WordToVectors(CAV_L0_UINT32 a429word,
															CAV_L0_UINT32 halfBitTime100ns,
															CAV_L0_UINT32 *pVectors,
															CAV_L0_UINT32 sizeInWords,
															CAV_L0_UINT32 *pNumVectors);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_SG_AddVectors(CAV_L0_UINT32 numVec,
														 CAV_L0_UINT32 vector2bit,
														 CAV_L0_UINT32 *pVectors,
														 CAV_L0_UINT32 sizeInWords,
														 CAV_L0_UINT32 *pNumVectors);


EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_Get_Sdisc_In(CAV_L0_UINT32 devID,
														CAV_L0_UINT32 * pSdiscIn);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_Set_Sdisc_Out(CAV_L0_UINT32 devID,
														 CAV_L0_UINT32 * pSdiscOut);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_Sdisc_Out_EnableControl(CAV_L0_UINT32 devID,
																   CAV_L0_UINT32 option);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_Get_Ddisc_In(CAV_L0_UINT32 devID,
														CAV_L0_UINT32 * pDdiscIn);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_Set_Ddisc_Out(CAV_L0_UINT32 devID,
														 CAV_L0_UINT32 * pDdiscOut);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV CAV_L1_A429_Global_Ddisc_Out_EnableControl(CAV_L0_UINT32 devID,
																		  CAV_L0_UINT32 option);

EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV  CAV_L1_ReadDeviceMem32(CAV_L0_UINT32 devID, 
																  CAV_L0_UINT32 offset, 
																  CAV_L0_UINT32 *pData,
																  CAV_L0_UINT32 count);
EXPORT_DLL CAV_L0_UINT32 CAV_L0_CALL_CONV  CAV_L1_WriteDeviceMem32(CAV_L0_UINT32 devID, 
																   CAV_L0_UINT32 offset, 
																   CAV_L0_UINT32 *pData,
																   CAV_L0_UINT32 count);
#ifdef __cplusplus
}
#endif

#endif

