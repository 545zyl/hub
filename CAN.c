//****************************************************************************
// @Module        MultiCAN Module (CAN)
// @Filename      CAN.c
// @Project       BMS-BCUv0.4.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC2287M-104F80
//
// @Compiler      Keil
//
// @Codegenerator 2.1
//
// @Description   This file contains functions that use the CAN module.
//
//----------------------------------------------------------------------------
// @Date          2018/7/17 16:33:49
//
//****************************************************************************



// USER CODE BEGIN (CAN_General,1)

// USER CODE END

/*
******************************************************************************
@Note

node0 velicle can;node 1 inbms can;node 2 charge can;

******************************************************************************
*/


//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.h"

// USER CODE BEGIN (CAN_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (CAN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (CAN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (CAN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (CAN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

static ubyte ubFIFOWritePtr[165];
static ubyte ubFIFOReadPtr[165];


// USER CODE BEGIN (CAN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (CAN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (CAN_General,9)

// USER CODE END


//****************************************************************************
// @Function      void CAN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the CAN function 
//                library. It is assumed that the SFRs used by this library 
//                are in reset state. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2018/7/17
//
//****************************************************************************

// USER CODE BEGIN (Init,1)

// USER CODE END

void CAN_vInit(void)
{
ushort i;

  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of Kernel State Configuration Register:
  ///  -----------------------------------------------------------------------
  ///  - Enable the CAN module(MODEN)
  ///  - Enable Bit Protection for MODEN

    MCAN_KSCCFG  =  0x0003;      // load Kernel State Configuration Register

    _nop_();  // one cycle delay 

    _nop_();  // one cycle delay 


  ///  -----------------------------------------------------------------------
  ///  Configuration of the Module Clock:
  ///  -----------------------------------------------------------------------
  ///  - the CAN module clock = 40.00 MHz
  ///  - Normal divider mode selected

    CAN_FDRL     =  0x43FE;      // load Fractional Divider Register

  ///  -----------------------------------------------------------------------
  ///  Panel Control
  ///  -----------------------------------------------------------------------
  ///  - wait until Panel has finished the initialisation

    while(CAN_PANCTRL & CAN_PANCTR_BUSY){ // wait until Panel has finished 
                                          // the initialisation
      }                         

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 0:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 0:
  ///  - set INIT and CCE

    CAN_NCR0     =  0x0041;      // load NODE 0 control register[15-0]

  ///  - load NODE 0 interrupt pointer register

    CAN_NIPR0    =  0x0000;      // load NIPR0_LECINP, ALINP, CFCINP and TRINP

  ///  Configuration of the used CAN Port Pins:
  ///  - Loop-back mode is disabled
  ///  - P2.0 is used for CAN0 Receive input(RXDC0C)
  ///  - P2.1 is used for CAN0 Transmit output(TXDC0C)

  P2_IOCR01 = 0x0090;    //set direction register
    CAN_NPCR0    =  0x0002;      // load node0 port control register


  ///  Configuration of the Node 0 Baud Rate:
  ///  - required baud rate = 250.000 kbaud
  ///  - real baud rate     = 250.000 kbaud
  ///  - sample point       = 60.00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 4 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta

    CAN_NBTR0L   =  0x344F;      // load NBTR0_DIV8, TSEG2, TSEG1, SJW and BRP

  ///  Configuration of the Node 0 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

    CAN_NECNT0H = 0x0060;        // load NECNT0_EWRNLVL register
    CAN_NECNT0L = 0x0000;       

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - the counter is incremented each time a frame was received correctly
  ///  - frame counter: 0x0000

    CAN_NFCR0H = 0x0002;         // load NFCR0_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_NFCR0L = 0x0000;         // load NFCR0_CFC

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 1:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 1:
  ///  - set INIT and CCE

    CAN_NCR1     =  0x0041;      // load NODE 1 control register[15-0]

  ///  - load NODE 1 interrupt pointer register

    CAN_NIPR1    =  0x0000;      // load NIPR1_LECINP, ALINP, CFCINP and TRINP

  ///  Configuration of the used CAN Port Pins:
  ///  - Loop-back mode is disabled
  ///  - P2.7 is used for CAN1 Receive input(RXDC1C)
  ///  - P2.9 is used for CAN1 Transmit output(TXDC1C)

  P2_IOCR09 = 0x00A0;    //set direction register
    CAN_NPCR1    =  0x0002;      // load node1 port control register


  ///  Configuration of the Node 1 Baud Rate:
  ///  - required baud rate = 250.000 kbaud
  ///  - real baud rate     = 250.000 kbaud
  ///  - sample point       = 60.00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 4 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta

    CAN_NBTR1L   =  0x344F;      // load NBTR1_DIV8, TSEG2, TSEG1, SJW and BRP

  ///  Configuration of the Node 1 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

    CAN_NECNT1H = 0x0060;        // load NECNT1_EWRNLVL register
    CAN_NECNT1L = 0x0000;       

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000

    CAN_NFCR1H = 0x0000;         // load NFCR1_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_NFCR1L = 0x0000;         // load NFCR1_CFC

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 2:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 2:
  ///  - set INIT and CCE

    CAN_NCR2     =  0x0041;      // load NODE 2 control register[15-0]

  ///  - load NODE 2 interrupt pointer register

    CAN_NIPR2    =  0x0000;      // load NIPR2_LECINP, ALINP, CFCINP and TRINP

  ///  Configuration of the used CAN Port Pins:
  ///  - Loop-back mode is disabled
  ///  - P4.3 is used for CAN2 Receive inputA(RXDC2A)
  ///  - P4.2 is used for CAN2 Transmit output(TXDC2B)

  P4_IOCR02 = 0x00A0;    //set direction register
    CAN_NPCR2    =  0x0000;      // load node2 port control register


  ///  Configuration of the Node 2 Baud Rate:
  ///  - required baud rate = 250.000 kbaud
  ///  - real baud rate     = 250.000 kbaud
  ///  - sample point       = 60.00 %
  ///  - there are 5 time quanta before sample point
  ///  - there are 4 time quanta after sample point
  ///  - the (re)synchronization jump width is 2 time quanta

    CAN_NBTR2L   =  0x344F;      // load NBTR2_DIV8, TSEG2, TSEG1, SJW and BRP

  ///  Configuration of the Node 2 Error Counter:
  ///  - the error warning threshold value (warning level) is 96

    CAN_NECNT2H = 0x0060;        // load NECNT2_EWRNLVL register
    CAN_NECNT2L = 0x0000;       

  ///  Configuration of the Frame Counter:
  ///  - Frame Counter Mode: the counter is incremented upon the reception 
  ///    and transmission of frames
  ///  - frame counter: 0x0000

    CAN_NFCR2H = 0x0000;         // load NFCR2_CFCOV, CFCIE, CFMOD, CFSEL
    CAN_NFCR2L = 0x0000;         // load NFCR2_CFC

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 3:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 3:
  ///  - set INIT and CCE

    CAN_NCR3     =  0x0041;      // load NODE 3 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 4:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 4:
  ///  - set INIT and CCE

    CAN_NCR4     =  0x0041;      // load NODE 4 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of CAN Node 5:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Node 5:
  ///  - set INIT and CCE

    CAN_NCR5     =  0x0041;      // load NODE 5 control register[15-0]

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Object List Structure:
  ///  -----------------------------------------------------------------------

  ///  Allocate MOs for list 1:

    SetListCommand(0x0100,0x0002);  // MO0 for list 1 (Node 0)

    SetListCommand(0x0120,0x0002);  // MO32 for list 1 (Node 0)

    SetListCommand(0x0121,0x0002);  // MO33 for list 1 (Node 0)

    SetListCommand(0x0122,0x0002);  // MO34 for list 1 (Node 0)

    SetListCommand(0x0123,0x0002);  // MO35 for list 1 (Node 0)

    SetListCommand(0x0124,0x0002);  // MO36 for list 1 (Node 0)

    SetListCommand(0x0125,0x0002);  // MO37 for list 1 (Node 0)

    SetListCommand(0x0126,0x0002);  // MO38 for list 1 (Node 0)

    SetListCommand(0x0127,0x0002);  // MO39 for list 1 (Node 0)

    SetListCommand(0x0128,0x0002);  // MO40 for list 1 (Node 0)

  ///  Allocate MOs for list 2:

    SetListCommand(0x0240,0x0002);  // MO64 for list 2 (Node 1)

    SetListCommand(0x0241,0x0002);  // MO65 for list 2 (Node 1)

    SetListCommand(0x0242,0x0002);  // MO66 for list 2 (Node 1)

    SetListCommand(0x0243,0x0002);  // MO67 for list 2 (Node 1)

    SetListCommand(0x0244,0x0002);  // MO68 for list 2 (Node 1)

    SetListCommand(0x0245,0x0002);  // MO69 for list 2 (Node 1)

    SetListCommand(0x0246,0x0002);  // MO70 for list 2 (Node 1)

    SetListCommand(0x0247,0x0002);  // MO71 for list 2 (Node 1)

    SetListCommand(0x0248,0x0002);  // MO72 for list 2 (Node 1)

    SetListCommand(0x0249,0x0002);  // MO73 for list 2 (Node 1)

    SetListCommand(0x024A,0x0002);  // MO74 for list 2 (Node 1)

    SetListCommand(0x024B,0x0002);  // MO75 for list 2 (Node 1)

    SetListCommand(0x024C,0x0002);  // MO76 for list 2 (Node 1)

    SetListCommand(0x024D,0x0002);  // MO77 for list 2 (Node 1)

    SetListCommand(0x0260,0x0002);  // MO96 for list 2 (Node 1)

    SetListCommand(0x0261,0x0002);  // MO97 for list 2 (Node 1)

    SetListCommand(0x0262,0x0002);  // MO98 for list 2 (Node 1)

    SetListCommand(0x0263,0x0002);  // MO99 for list 2 (Node 1)

    SetListCommand(0x0264,0x0002);  // MO100 for list 2 (Node 1)

    SetListCommand(0x0265,0x0002);  // MO101 for list 2 (Node 1)

    SetListCommand(0x0266,0x0002);  // MO102 for list 2 (Node 1)

    SetListCommand(0x0267,0x0002);  // MO103 for list 2 (Node 1)

    SetListCommand(0x0268,0x0002);  // MO104 for list 2 (Node 1)

    SetListCommand(0x0269,0x0002);  // MO105 for list 2 (Node 1)

    SetListCommand(0x026A,0x0002);  // MO106 for list 2 (Node 1)

    SetListCommand(0x026B,0x0002);  // MO107 for list 2 (Node 1)

    SetListCommand(0x026C,0x0002);  // MO108 for list 2 (Node 1)

    SetListCommand(0x026D,0x0002);  // MO109 for list 2 (Node 1)

    SetListCommand(0x026E,0x0002);  // MO110 for list 2 (Node 1)

    SetListCommand(0x026F,0x0002);  // MO111 for list 2 (Node 1)

    SetListCommand(0x0270,0x0002);  // MO112 for list 2 (Node 1)

    SetListCommand(0x0271,0x0002);  // MO113 for list 2 (Node 1)

    SetListCommand(0x0272,0x0002);  // MO114 for list 2 (Node 1)

    SetListCommand(0x0273,0x0002);  // MO115 for list 2 (Node 1)

    SetListCommand(0x0274,0x0002);  // MO116 for list 2 (Node 1)

    SetListCommand(0x0275,0x0002);  // MO117 for list 2 (Node 1)

  ///  Allocate MOs for list 3:

    SetListCommand(0x0380,0x0002);  // MO128 for list 3 (Node 2)

    SetListCommand(0x0381,0x0002);  // MO129 for list 3 (Node 2)

    SetListCommand(0x0382,0x0002);  // MO130 for list 3 (Node 2)

    SetListCommand(0x0383,0x0002);  // MO131 for list 3 (Node 2)

    SetListCommand(0x0384,0x0002);  // MO132 for list 3 (Node 2)

    SetListCommand(0x03A0,0x0002);  // MO160 for list 3 (Node 2)

    SetListCommand(0x03A1,0x0002);  // MO161 for list 3 (Node 2)

    SetListCommand(0x03A2,0x0002);  // MO162 for list 3 (Node 2)

    SetListCommand(0x03A3,0x0002);  // MO163 for list 3 (Node 2)

    SetListCommand(0x03A4,0x0002);  // MO164 for list 3 (Node 2)

  ///  -----------------------------------------------------------------------
  ///  Configuration of the CAN Message Objects 0 - 254:
  ///  -----------------------------------------------------------------------
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 0:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 0 :
  ///  - message object 0 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR0H = 0x00A0;        // load MO0 control register high
    CAN_MOCTR0L = 0x0000;        // load MO0 control register low

  ///  Configuration of Message Object 0 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x18FF9B00

    CAN_MOAR0H = 0x78FF;         // load MO0 arbitration register high
    CAN_MOAR0L = 0x9B00;         // load MO0 arbitration register low

  ///  Configuration of Message Object 0 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFF00

    CAN_MOAMR0H = 0x3FFF;        // load MO0 acceptance mask register high
    CAN_MOAMR0L = 0xFF00;        // load MO0 acceptance mask register low

  ///  Configuration of Message Object 0 interrupt pointer:
  ///  - use message pending register 0 bit position 0
  ///  - receive interrupt node pointer: MultiCAN SRN 0

    CAN_MOIPR0H = 0x0000;        // load MO0 interrupt pointer register high
    CAN_MOIPR0L = 0x0000;        // load MO0 interrupt pointer register low

  ///  Configuration of Message Object 0 FIFO/Gateway pointer:

    CAN_MOFGPR0H = 0x0000;       // load MO0 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR0L = 0x0000;       // load MO0 FIFO/gateway pointer register low


  ///  Configuration of Message Object 0 Function control:
  ///  - this object is a STANDARD MESSAGE OBJECT
  ///  - 8 valid data bytes
  ///  - enable receive interrupt; bit RXPND is set after successful 
  ///    reception of a frame

    CAN_MOFCR0H = 0x0801;        // load MO0 function control register high
    CAN_MOFCR0L = 0x0000;        // load MO0 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 1:
  ///  -----------------------------------------------------------------------
  ///  - message object 1 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 2:
  ///  -----------------------------------------------------------------------
  ///  - message object 2 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 3:
  ///  -----------------------------------------------------------------------
  ///  - message object 3 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 4:
  ///  -----------------------------------------------------------------------
  ///  - message object 4 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 5:
  ///  -----------------------------------------------------------------------
  ///  - message object 5 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 6:
  ///  -----------------------------------------------------------------------
  ///  - message object 6 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 7:
  ///  -----------------------------------------------------------------------
  ///  - message object 7 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 8:
  ///  -----------------------------------------------------------------------
  ///  - message object 8 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 9:
  ///  -----------------------------------------------------------------------
  ///  - message object 9 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 10:
  ///  -----------------------------------------------------------------------
  ///  - message object 10 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 11:
  ///  -----------------------------------------------------------------------
  ///  - message object 11 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 12:
  ///  -----------------------------------------------------------------------
  ///  - message object 12 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 13:
  ///  -----------------------------------------------------------------------
  ///  - message object 13 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 14:
  ///  -----------------------------------------------------------------------
  ///  - message object 14 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 15:
  ///  -----------------------------------------------------------------------
  ///  - message object 15 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 16:
  ///  -----------------------------------------------------------------------
  ///  - message object 16 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 17:
  ///  -----------------------------------------------------------------------
  ///  - message object 17 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 18:
  ///  -----------------------------------------------------------------------
  ///  - message object 18 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 19:
  ///  -----------------------------------------------------------------------
  ///  - message object 19 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 20:
  ///  -----------------------------------------------------------------------
  ///  - message object 20 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 21:
  ///  -----------------------------------------------------------------------
  ///  - message object 21 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 22:
  ///  -----------------------------------------------------------------------
  ///  - message object 22 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 23:
  ///  -----------------------------------------------------------------------
  ///  - message object 23 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 24:
  ///  -----------------------------------------------------------------------
  ///  - message object 24 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 25:
  ///  -----------------------------------------------------------------------
  ///  - message object 25 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 26:
  ///  -----------------------------------------------------------------------
  ///  - message object 26 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 27:
  ///  -----------------------------------------------------------------------
  ///  - message object 27 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 28:
  ///  -----------------------------------------------------------------------
  ///  - message object 28 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 29:
  ///  -----------------------------------------------------------------------
  ///  - message object 29 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 30:
  ///  -----------------------------------------------------------------------
  ///  - message object 30 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 31:
  ///  -----------------------------------------------------------------------
  ///  - message object 31 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 32:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 32 :
  ///  - message object 32 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR32H = 0x0EA8;       // load MO32 control register high
    CAN_MOCTR32L = 0x0000;       // load MO32 control register low

  ///  Configuration of Message Object 32 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000002

    CAN_MOAR32H = 0x6000;        // load MO32 arbitration register high
    CAN_MOAR32L = 0x0002;        // load MO32 arbitration register low

  ///  Configuration of Message Object 32 Data:

    CAN_MODATA32HH = 0x0000;     // load MO32 Data Bytes(DB7 & DB6)
    CAN_MODATA32HL = 0x0000;     // load MO32 Data Bytes(DB5 & DB4)
    CAN_MODATA32LH = 0x0000;     // load MO32 Data Bytes(DB3 & DB2)
    CAN_MODATA32LL = 0x0022;     // load MO32 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 32 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR32H = 0x3FFF;       // load MO32 acceptance mask register high
    CAN_MOAMR32L = 0xFFFF;       // load MO32 acceptance mask register low

  ///  Configuration of Message Object 32 interrupt pointer:
  ///  - use message pending register 1 bit position 0

    CAN_MOIPR32H = 0x0000;       // load MO32 interrupt pointer register high
    CAN_MOIPR32L = 0x2001;       // load MO32 interrupt pointer register low

  ///  Configuration of Message Object 32 FIFO/Gateway pointer:
  ///  - current select pointer : MO32
  ///  - object select pointer : MO40

    CAN_MOFGPR32H = 0x2820;      // load MO32 FIFO/gateway pointer register 
                                 // high
  ///  - bottom pointer : MO32
  ///  - top pointer : MO40
    CAN_MOFGPR32L = 0x2820;      // load MO32 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 32 Function control:
  ///  - this object is a TRANSMIT FIFO BASE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR32H = 0x0800;       // load MO32 function control register high
    CAN_MOFCR32L = 0x0002;       // load MO32 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 33:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 33 :
  ///  - message object 33 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR33H = 0x0A28;       // load MO33 control register high
    CAN_MOCTR33L = 0x0000;       // load MO33 control register low

  ///  Configuration of Message Object 33 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000002

    CAN_MOAR33H = 0x6000;        // load MO33 arbitration register high
    CAN_MOAR33L = 0x0002;        // load MO33 arbitration register low

  ///  Configuration of Message Object 33 Data:

    CAN_MODATA33HH = 0x0000;     // load MO33 Data Bytes(DB7 & DB6)
    CAN_MODATA33HL = 0x0000;     // load MO33 Data Bytes(DB5 & DB4)
    CAN_MODATA33LH = 0x0000;     // load MO33 Data Bytes(DB3 & DB2)
    CAN_MODATA33LL = 0x0000;     // load MO33 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 33 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR33H = 0x3FFF;       // load MO33 acceptance mask register high
    CAN_MOAMR33L = 0xFFFF;       // load MO33 acceptance mask register low

  ///  Configuration of Message Object 33 interrupt pointer:
  ///  - use message pending register 1 bit position 1

    CAN_MOIPR33H = 0x0000;       // load MO33 interrupt pointer register high
    CAN_MOIPR33L = 0x2130;       // load MO33 interrupt pointer register low

  ///  Configuration of Message Object 33 FIFO/Gateway pointer:
  ///  - current select pointer : MO32

    CAN_MOFGPR33H = 0x0020;      // load MO33 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR33L = 0x0000;      // load MO33 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 33 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 32
  ///  - 0 valid data bytes

    CAN_MOFCR33H = 0x0000;       // load MO33 function control register high
    CAN_MOFCR33L = 0x0003;       // load MO33 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 34:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 34 :
  ///  - message object 34 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR34H = 0x0A28;       // load MO34 control register high
    CAN_MOCTR34L = 0x0000;       // load MO34 control register low

  ///  Configuration of Message Object 34 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000002

    CAN_MOAR34H = 0x6000;        // load MO34 arbitration register high
    CAN_MOAR34L = 0x0002;        // load MO34 arbitration register low

  ///  Configuration of Message Object 34 Data:

    CAN_MODATA34HH = 0x0000;     // load MO34 Data Bytes(DB7 & DB6)
    CAN_MODATA34HL = 0x0000;     // load MO34 Data Bytes(DB5 & DB4)
    CAN_MODATA34LH = 0x0000;     // load MO34 Data Bytes(DB3 & DB2)
    CAN_MODATA34LL = 0x0000;     // load MO34 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 34 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR34H = 0x3FFF;       // load MO34 acceptance mask register high
    CAN_MOAMR34L = 0xFFFF;       // load MO34 acceptance mask register low

  ///  Configuration of Message Object 34 interrupt pointer:
  ///  - use message pending register 1 bit position 2

    CAN_MOIPR34H = 0x0000;       // load MO34 interrupt pointer register high
    CAN_MOIPR34L = 0x2200;       // load MO34 interrupt pointer register low

  ///  Configuration of Message Object 34 FIFO/Gateway pointer:
  ///  - current select pointer : MO32

    CAN_MOFGPR34H = 0x0020;      // load MO34 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR34L = 0x0000;      // load MO34 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 34 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 32
  ///  - 0 valid data bytes

    CAN_MOFCR34H = 0x0000;       // load MO34 function control register high
    CAN_MOFCR34L = 0x0003;       // load MO34 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 35:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 35 :
  ///  - message object 35 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR35H = 0x0A28;       // load MO35 control register high
    CAN_MOCTR35L = 0x0000;       // load MO35 control register low

  ///  Configuration of Message Object 35 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000002

    CAN_MOAR35H = 0x6000;        // load MO35 arbitration register high
    CAN_MOAR35L = 0x0002;        // load MO35 arbitration register low

  ///  Configuration of Message Object 35 Data:

    CAN_MODATA35HH = 0x0000;     // load MO35 Data Bytes(DB7 & DB6)
    CAN_MODATA35HL = 0x0000;     // load MO35 Data Bytes(DB5 & DB4)
    CAN_MODATA35LH = 0x0000;     // load MO35 Data Bytes(DB3 & DB2)
    CAN_MODATA35LL = 0x0000;     // load MO35 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 35 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR35H = 0x3FFF;       // load MO35 acceptance mask register high
    CAN_MOAMR35L = 0xFFFF;       // load MO35 acceptance mask register low

  ///  Configuration of Message Object 35 interrupt pointer:
  ///  - use message pending register 1 bit position 3

    CAN_MOIPR35H = 0x0000;       // load MO35 interrupt pointer register high
    CAN_MOIPR35L = 0x2300;       // load MO35 interrupt pointer register low

  ///  Configuration of Message Object 35 FIFO/Gateway pointer:
  ///  - current select pointer : MO32

    CAN_MOFGPR35H = 0x0020;      // load MO35 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR35L = 0x0000;      // load MO35 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 35 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 32
  ///  - 0 valid data bytes

    CAN_MOFCR35H = 0x0000;       // load MO35 function control register high
    CAN_MOFCR35L = 0x0003;       // load MO35 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 36:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 36 :
  ///  - message object 36 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR36H = 0x0A28;       // load MO36 control register high
    CAN_MOCTR36L = 0x0000;       // load MO36 control register low

  ///  Configuration of Message Object 36 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000002

    CAN_MOAR36H = 0x6000;        // load MO36 arbitration register high
    CAN_MOAR36L = 0x0002;        // load MO36 arbitration register low

  ///  Configuration of Message Object 36 Data:

    CAN_MODATA36HH = 0x0000;     // load MO36 Data Bytes(DB7 & DB6)
    CAN_MODATA36HL = 0x0000;     // load MO36 Data Bytes(DB5 & DB4)
    CAN_MODATA36LH = 0x0000;     // load MO36 Data Bytes(DB3 & DB2)
    CAN_MODATA36LL = 0x0000;     // load MO36 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 36 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR36H = 0x3FFF;       // load MO36 acceptance mask register high
    CAN_MOAMR36L = 0xFFFF;       // load MO36 acceptance mask register low

  ///  Configuration of Message Object 36 interrupt pointer:
  ///  - use message pending register 1 bit position 4

    CAN_MOIPR36H = 0x0000;       // load MO36 interrupt pointer register high
    CAN_MOIPR36L = 0x2400;       // load MO36 interrupt pointer register low

  ///  Configuration of Message Object 36 FIFO/Gateway pointer:
  ///  - current select pointer : MO32

    CAN_MOFGPR36H = 0x0020;      // load MO36 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR36L = 0x0000;      // load MO36 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 36 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 32
  ///  - 0 valid data bytes

    CAN_MOFCR36H = 0x0000;       // load MO36 function control register high
    CAN_MOFCR36L = 0x0003;       // load MO36 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 37:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 37 :
  ///  - message object 37 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR37H = 0x0A28;       // load MO37 control register high
    CAN_MOCTR37L = 0x0000;       // load MO37 control register low

  ///  Configuration of Message Object 37 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000002

    CAN_MOAR37H = 0x6000;        // load MO37 arbitration register high
    CAN_MOAR37L = 0x0002;        // load MO37 arbitration register low

  ///  Configuration of Message Object 37 Data:

    CAN_MODATA37HH = 0x0000;     // load MO37 Data Bytes(DB7 & DB6)
    CAN_MODATA37HL = 0x0000;     // load MO37 Data Bytes(DB5 & DB4)
    CAN_MODATA37LH = 0x0000;     // load MO37 Data Bytes(DB3 & DB2)
    CAN_MODATA37LL = 0x0000;     // load MO37 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 37 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR37H = 0x3FFF;       // load MO37 acceptance mask register high
    CAN_MOAMR37L = 0xFFFF;       // load MO37 acceptance mask register low

  ///  Configuration of Message Object 37 interrupt pointer:
  ///  - use message pending register 1 bit position 5

    CAN_MOIPR37H = 0x0000;       // load MO37 interrupt pointer register high
    CAN_MOIPR37L = 0x2500;       // load MO37 interrupt pointer register low

  ///  Configuration of Message Object 37 FIFO/Gateway pointer:
  ///  - current select pointer : MO32

    CAN_MOFGPR37H = 0x0020;      // load MO37 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR37L = 0x0000;      // load MO37 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 37 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 32
  ///  - 0 valid data bytes

    CAN_MOFCR37H = 0x0000;       // load MO37 function control register high
    CAN_MOFCR37L = 0x0003;       // load MO37 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 38:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 38 :
  ///  - message object 38 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR38H = 0x0A28;       // load MO38 control register high
    CAN_MOCTR38L = 0x0000;       // load MO38 control register low

  ///  Configuration of Message Object 38 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000002

    CAN_MOAR38H = 0x6000;        // load MO38 arbitration register high
    CAN_MOAR38L = 0x0002;        // load MO38 arbitration register low

  ///  Configuration of Message Object 38 Data:

    CAN_MODATA38HH = 0x0000;     // load MO38 Data Bytes(DB7 & DB6)
    CAN_MODATA38HL = 0x0000;     // load MO38 Data Bytes(DB5 & DB4)
    CAN_MODATA38LH = 0x0000;     // load MO38 Data Bytes(DB3 & DB2)
    CAN_MODATA38LL = 0x0000;     // load MO38 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 38 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR38H = 0x3FFF;       // load MO38 acceptance mask register high
    CAN_MOAMR38L = 0xFFFF;       // load MO38 acceptance mask register low

  ///  Configuration of Message Object 38 interrupt pointer:
  ///  - use message pending register 1 bit position 6

    CAN_MOIPR38H = 0x0000;       // load MO38 interrupt pointer register high
    CAN_MOIPR38L = 0x2600;       // load MO38 interrupt pointer register low

  ///  Configuration of Message Object 38 FIFO/Gateway pointer:
  ///  - current select pointer : MO32

    CAN_MOFGPR38H = 0x0020;      // load MO38 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR38L = 0x0000;      // load MO38 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 38 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 32
  ///  - 0 valid data bytes

    CAN_MOFCR38H = 0x0000;       // load MO38 function control register high
    CAN_MOFCR38L = 0x0003;       // load MO38 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 39:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 39 :
  ///  - message object 39 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR39H = 0x0A28;       // load MO39 control register high
    CAN_MOCTR39L = 0x0000;       // load MO39 control register low

  ///  Configuration of Message Object 39 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000002

    CAN_MOAR39H = 0x6000;        // load MO39 arbitration register high
    CAN_MOAR39L = 0x0002;        // load MO39 arbitration register low

  ///  Configuration of Message Object 39 Data:

    CAN_MODATA39HH = 0x0000;     // load MO39 Data Bytes(DB7 & DB6)
    CAN_MODATA39HL = 0x0000;     // load MO39 Data Bytes(DB5 & DB4)
    CAN_MODATA39LH = 0x0000;     // load MO39 Data Bytes(DB3 & DB2)
    CAN_MODATA39LL = 0x0000;     // load MO39 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 39 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR39H = 0x3FFF;       // load MO39 acceptance mask register high
    CAN_MOAMR39L = 0xFFFF;       // load MO39 acceptance mask register low

  ///  Configuration of Message Object 39 interrupt pointer:
  ///  - use message pending register 1 bit position 7

    CAN_MOIPR39H = 0x0000;       // load MO39 interrupt pointer register high
    CAN_MOIPR39L = 0x2700;       // load MO39 interrupt pointer register low

  ///  Configuration of Message Object 39 FIFO/Gateway pointer:
  ///  - current select pointer : MO32

    CAN_MOFGPR39H = 0x0020;      // load MO39 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR39L = 0x0000;      // load MO39 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 39 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 32
  ///  - 0 valid data bytes

    CAN_MOFCR39H = 0x0000;       // load MO39 function control register high
    CAN_MOFCR39L = 0x0003;       // load MO39 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 40:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 40 :
  ///  - message object 40 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 1 (node 0)

    CAN_MOCTR40H = 0x0A28;       // load MO40 control register high
    CAN_MOCTR40L = 0x0000;       // load MO40 control register low

  ///  Configuration of Message Object 40 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000002

    CAN_MOAR40H = 0x6000;        // load MO40 arbitration register high
    CAN_MOAR40L = 0x0002;        // load MO40 arbitration register low

  ///  Configuration of Message Object 40 Data:

    CAN_MODATA40HH = 0x0000;     // load MO40 Data Bytes(DB7 & DB6)
    CAN_MODATA40HL = 0x0000;     // load MO40 Data Bytes(DB5 & DB4)
    CAN_MODATA40LH = 0x0000;     // load MO40 Data Bytes(DB3 & DB2)
    CAN_MODATA40LL = 0x0000;     // load MO40 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 40 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR40H = 0x3FFF;       // load MO40 acceptance mask register high
    CAN_MOAMR40L = 0xFFFF;       // load MO40 acceptance mask register low

  ///  Configuration of Message Object 40 interrupt pointer:
  ///  - use message pending register 1 bit position 8

    CAN_MOIPR40H = 0x0000;       // load MO40 interrupt pointer register high
    CAN_MOIPR40L = 0x2800;       // load MO40 interrupt pointer register low

  ///  Configuration of Message Object 40 FIFO/Gateway pointer:
  ///  - current select pointer : MO32

    CAN_MOFGPR40H = 0x0020;      // load MO40 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR40L = 0x0000;      // load MO40 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 40 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 32
  ///  - 0 valid data bytes

    CAN_MOFCR40H = 0x0000;       // load MO40 function control register high
    CAN_MOFCR40L = 0x0003;       // load MO40 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 41:
  ///  -----------------------------------------------------------------------
  ///  - message object 41 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 42:
  ///  -----------------------------------------------------------------------
  ///  - message object 42 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 43:
  ///  -----------------------------------------------------------------------
  ///  - message object 43 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 44:
  ///  -----------------------------------------------------------------------
  ///  - message object 44 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 45:
  ///  -----------------------------------------------------------------------
  ///  - message object 45 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 46:
  ///  -----------------------------------------------------------------------
  ///  - message object 46 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 47:
  ///  -----------------------------------------------------------------------
  ///  - message object 47 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 48:
  ///  -----------------------------------------------------------------------
  ///  - message object 48 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 49:
  ///  -----------------------------------------------------------------------
  ///  - message object 49 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 50:
  ///  -----------------------------------------------------------------------
  ///  - message object 50 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 51:
  ///  -----------------------------------------------------------------------
  ///  - message object 51 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 52:
  ///  -----------------------------------------------------------------------
  ///  - message object 52 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 53:
  ///  -----------------------------------------------------------------------
  ///  - message object 53 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 54:
  ///  -----------------------------------------------------------------------
  ///  - message object 54 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 55:
  ///  -----------------------------------------------------------------------
  ///  - message object 55 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 56:
  ///  -----------------------------------------------------------------------
  ///  - message object 56 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 57:
  ///  -----------------------------------------------------------------------
  ///  - message object 57 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 58:
  ///  -----------------------------------------------------------------------
  ///  - message object 58 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 59:
  ///  -----------------------------------------------------------------------
  ///  - message object 59 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 60:
  ///  -----------------------------------------------------------------------
  ///  - message object 60 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 61:
  ///  -----------------------------------------------------------------------
  ///  - message object 61 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 62:
  ///  -----------------------------------------------------------------------
  ///  - message object 62 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 63:
  ///  -----------------------------------------------------------------------
  ///  - message object 63 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 64:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 64 :
  ///  - message object 64 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR64H = 0x00A0;       // load MO64 control register high
    CAN_MOCTR64L = 0x0000;       // load MO64 control register low

  ///  Configuration of Message Object 64 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR64H = 0x6100;        // load MO64 arbitration register high
    CAN_MOAR64L = 0x0000;        // load MO64 arbitration register low

  ///  Configuration of Message Object 64 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR64H = 0x3F00;       // load MO64 acceptance mask register high
    CAN_MOAMR64L = 0x0000;       // load MO64 acceptance mask register low

  ///  Configuration of Message Object 64 interrupt pointer:
  ///  - use message pending register 2 bit position 0

    CAN_MOIPR64H = 0x0000;       // load MO64 interrupt pointer register high
    CAN_MOIPR64L = 0x4010;       // load MO64 interrupt pointer register low

  ///  Configuration of Message Object 64 FIFO/Gateway pointer:
  ///  - current select pointer : MO64
  ///  - object select pointer : MO77

    CAN_MOFGPR64H = 0x4D40;      // load MO64 FIFO/gateway pointer register 
                                 // high
  ///  - bottom pointer : MO64
  ///  - top pointer : MO77
    CAN_MOFGPR64L = 0x4D40;      // load MO64 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 64 Function control:
  ///  - this object is a RECEIVE FIFO BASE OBJECT
  ///  - 8 valid data bytes
  ///  - enable FIFO overflow interrupt

    CAN_MOFCR64H = 0x0804;       // load MO64 function control register high
    CAN_MOFCR64L = 0x0001;       // load MO64 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 65:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 65 :
  ///  - message object 65 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR65H = 0x0020;       // load MO65 control register high
    CAN_MOCTR65L = 0x0000;       // load MO65 control register low

  ///  Configuration of Message Object 65 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR65H = 0x6100;        // load MO65 arbitration register high
    CAN_MOAR65L = 0x0000;        // load MO65 arbitration register low

  ///  Configuration of Message Object 65 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR65H = 0x3F00;       // load MO65 acceptance mask register high
    CAN_MOAMR65L = 0x0000;       // load MO65 acceptance mask register low

  ///  Configuration of Message Object 65 interrupt pointer:
  ///  - use message pending register 2 bit position 1

    CAN_MOIPR65H = 0x0000;       // load MO65 interrupt pointer register high
    CAN_MOIPR65L = 0x4100;       // load MO65 interrupt pointer register low

  ///  Configuration of Message Object 65 FIFO/Gateway pointer:

    CAN_MOFGPR65H = 0x0000;      // load MO65 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR65L = 0x0000;      // load MO65 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 65 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR65H = 0x0000;       // load MO65 function control register high
    CAN_MOFCR65L = 0x0000;       // load MO65 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 66:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 66 :
  ///  - message object 66 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR66H = 0x0020;       // load MO66 control register high
    CAN_MOCTR66L = 0x0000;       // load MO66 control register low

  ///  Configuration of Message Object 66 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR66H = 0x6100;        // load MO66 arbitration register high
    CAN_MOAR66L = 0x0000;        // load MO66 arbitration register low

  ///  Configuration of Message Object 66 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR66H = 0x3F00;       // load MO66 acceptance mask register high
    CAN_MOAMR66L = 0x0000;       // load MO66 acceptance mask register low

  ///  Configuration of Message Object 66 interrupt pointer:
  ///  - use message pending register 2 bit position 2

    CAN_MOIPR66H = 0x0000;       // load MO66 interrupt pointer register high
    CAN_MOIPR66L = 0x4200;       // load MO66 interrupt pointer register low

  ///  Configuration of Message Object 66 FIFO/Gateway pointer:

    CAN_MOFGPR66H = 0x0000;      // load MO66 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR66L = 0x0000;      // load MO66 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 66 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR66H = 0x0000;       // load MO66 function control register high
    CAN_MOFCR66L = 0x0000;       // load MO66 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 67:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 67 :
  ///  - message object 67 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR67H = 0x0020;       // load MO67 control register high
    CAN_MOCTR67L = 0x0000;       // load MO67 control register low

  ///  Configuration of Message Object 67 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR67H = 0x6100;        // load MO67 arbitration register high
    CAN_MOAR67L = 0x0000;        // load MO67 arbitration register low

  ///  Configuration of Message Object 67 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR67H = 0x3F00;       // load MO67 acceptance mask register high
    CAN_MOAMR67L = 0x0000;       // load MO67 acceptance mask register low

  ///  Configuration of Message Object 67 interrupt pointer:
  ///  - use message pending register 2 bit position 3

    CAN_MOIPR67H = 0x0000;       // load MO67 interrupt pointer register high
    CAN_MOIPR67L = 0x4300;       // load MO67 interrupt pointer register low

  ///  Configuration of Message Object 67 FIFO/Gateway pointer:

    CAN_MOFGPR67H = 0x0000;      // load MO67 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR67L = 0x0000;      // load MO67 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 67 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR67H = 0x0000;       // load MO67 function control register high
    CAN_MOFCR67L = 0x0000;       // load MO67 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 68:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 68 :
  ///  - message object 68 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR68H = 0x0020;       // load MO68 control register high
    CAN_MOCTR68L = 0x0000;       // load MO68 control register low

  ///  Configuration of Message Object 68 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR68H = 0x6100;        // load MO68 arbitration register high
    CAN_MOAR68L = 0x0000;        // load MO68 arbitration register low

  ///  Configuration of Message Object 68 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR68H = 0x3F00;       // load MO68 acceptance mask register high
    CAN_MOAMR68L = 0x0000;       // load MO68 acceptance mask register low

  ///  Configuration of Message Object 68 interrupt pointer:
  ///  - use message pending register 2 bit position 4

    CAN_MOIPR68H = 0x0000;       // load MO68 interrupt pointer register high
    CAN_MOIPR68L = 0x4400;       // load MO68 interrupt pointer register low

  ///  Configuration of Message Object 68 FIFO/Gateway pointer:

    CAN_MOFGPR68H = 0x0000;      // load MO68 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR68L = 0x0000;      // load MO68 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 68 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR68H = 0x0000;       // load MO68 function control register high
    CAN_MOFCR68L = 0x0000;       // load MO68 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 69:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 69 :
  ///  - message object 69 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR69H = 0x0020;       // load MO69 control register high
    CAN_MOCTR69L = 0x0000;       // load MO69 control register low

  ///  Configuration of Message Object 69 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR69H = 0x6100;        // load MO69 arbitration register high
    CAN_MOAR69L = 0x0000;        // load MO69 arbitration register low

  ///  Configuration of Message Object 69 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR69H = 0x3F00;       // load MO69 acceptance mask register high
    CAN_MOAMR69L = 0x0000;       // load MO69 acceptance mask register low

  ///  Configuration of Message Object 69 interrupt pointer:
  ///  - use message pending register 2 bit position 5

    CAN_MOIPR69H = 0x0000;       // load MO69 interrupt pointer register high
    CAN_MOIPR69L = 0x4500;       // load MO69 interrupt pointer register low

  ///  Configuration of Message Object 69 FIFO/Gateway pointer:

    CAN_MOFGPR69H = 0x0000;      // load MO69 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR69L = 0x0000;      // load MO69 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 69 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR69H = 0x0000;       // load MO69 function control register high
    CAN_MOFCR69L = 0x0000;       // load MO69 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 70:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 70 :
  ///  - message object 70 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR70H = 0x0020;       // load MO70 control register high
    CAN_MOCTR70L = 0x0000;       // load MO70 control register low

  ///  Configuration of Message Object 70 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR70H = 0x6100;        // load MO70 arbitration register high
    CAN_MOAR70L = 0x0000;        // load MO70 arbitration register low

  ///  Configuration of Message Object 70 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR70H = 0x3F00;       // load MO70 acceptance mask register high
    CAN_MOAMR70L = 0x0000;       // load MO70 acceptance mask register low

  ///  Configuration of Message Object 70 interrupt pointer:
  ///  - use message pending register 2 bit position 6

    CAN_MOIPR70H = 0x0000;       // load MO70 interrupt pointer register high
    CAN_MOIPR70L = 0x4600;       // load MO70 interrupt pointer register low

  ///  Configuration of Message Object 70 FIFO/Gateway pointer:

    CAN_MOFGPR70H = 0x0000;      // load MO70 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR70L = 0x0000;      // load MO70 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 70 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR70H = 0x0000;       // load MO70 function control register high
    CAN_MOFCR70L = 0x0000;       // load MO70 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 71:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 71 :
  ///  - message object 71 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR71H = 0x0020;       // load MO71 control register high
    CAN_MOCTR71L = 0x0000;       // load MO71 control register low

  ///  Configuration of Message Object 71 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR71H = 0x6100;        // load MO71 arbitration register high
    CAN_MOAR71L = 0x0000;        // load MO71 arbitration register low

  ///  Configuration of Message Object 71 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR71H = 0x3F00;       // load MO71 acceptance mask register high
    CAN_MOAMR71L = 0x0000;       // load MO71 acceptance mask register low

  ///  Configuration of Message Object 71 interrupt pointer:
  ///  - use message pending register 2 bit position 7

    CAN_MOIPR71H = 0x0000;       // load MO71 interrupt pointer register high
    CAN_MOIPR71L = 0x4700;       // load MO71 interrupt pointer register low

  ///  Configuration of Message Object 71 FIFO/Gateway pointer:

    CAN_MOFGPR71H = 0x0000;      // load MO71 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR71L = 0x0000;      // load MO71 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 71 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR71H = 0x0000;       // load MO71 function control register high
    CAN_MOFCR71L = 0x0000;       // load MO71 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 72:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 72 :
  ///  - message object 72 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR72H = 0x0020;       // load MO72 control register high
    CAN_MOCTR72L = 0x0000;       // load MO72 control register low

  ///  Configuration of Message Object 72 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR72H = 0x6100;        // load MO72 arbitration register high
    CAN_MOAR72L = 0x0000;        // load MO72 arbitration register low

  ///  Configuration of Message Object 72 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR72H = 0x3F00;       // load MO72 acceptance mask register high
    CAN_MOAMR72L = 0x0000;       // load MO72 acceptance mask register low

  ///  Configuration of Message Object 72 interrupt pointer:
  ///  - use message pending register 2 bit position 8

    CAN_MOIPR72H = 0x0000;       // load MO72 interrupt pointer register high
    CAN_MOIPR72L = 0x4800;       // load MO72 interrupt pointer register low

  ///  Configuration of Message Object 72 FIFO/Gateway pointer:

    CAN_MOFGPR72H = 0x0000;      // load MO72 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR72L = 0x0000;      // load MO72 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 72 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR72H = 0x0000;       // load MO72 function control register high
    CAN_MOFCR72L = 0x0000;       // load MO72 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 73:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 73 :
  ///  - message object 73 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR73H = 0x0020;       // load MO73 control register high
    CAN_MOCTR73L = 0x0000;       // load MO73 control register low

  ///  Configuration of Message Object 73 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR73H = 0x6100;        // load MO73 arbitration register high
    CAN_MOAR73L = 0x0000;        // load MO73 arbitration register low

  ///  Configuration of Message Object 73 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR73H = 0x3F00;       // load MO73 acceptance mask register high
    CAN_MOAMR73L = 0x0000;       // load MO73 acceptance mask register low

  ///  Configuration of Message Object 73 interrupt pointer:
  ///  - use message pending register 2 bit position 9

    CAN_MOIPR73H = 0x0000;       // load MO73 interrupt pointer register high
    CAN_MOIPR73L = 0x4900;       // load MO73 interrupt pointer register low

  ///  Configuration of Message Object 73 FIFO/Gateway pointer:

    CAN_MOFGPR73H = 0x0000;      // load MO73 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR73L = 0x0000;      // load MO73 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 73 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR73H = 0x0000;       // load MO73 function control register high
    CAN_MOFCR73L = 0x0000;       // load MO73 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 74:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 74 :
  ///  - message object 74 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR74H = 0x0020;       // load MO74 control register high
    CAN_MOCTR74L = 0x0000;       // load MO74 control register low

  ///  Configuration of Message Object 74 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR74H = 0x6100;        // load MO74 arbitration register high
    CAN_MOAR74L = 0x0000;        // load MO74 arbitration register low

  ///  Configuration of Message Object 74 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR74H = 0x3F00;       // load MO74 acceptance mask register high
    CAN_MOAMR74L = 0x0000;       // load MO74 acceptance mask register low

  ///  Configuration of Message Object 74 interrupt pointer:
  ///  - use message pending register 2 bit position 10

    CAN_MOIPR74H = 0x0000;       // load MO74 interrupt pointer register high
    CAN_MOIPR74L = 0x4A00;       // load MO74 interrupt pointer register low

  ///  Configuration of Message Object 74 FIFO/Gateway pointer:

    CAN_MOFGPR74H = 0x0000;      // load MO74 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR74L = 0x0000;      // load MO74 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 74 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR74H = 0x0000;       // load MO74 function control register high
    CAN_MOFCR74L = 0x0000;       // load MO74 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 75:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 75 :
  ///  - message object 75 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR75H = 0x0020;       // load MO75 control register high
    CAN_MOCTR75L = 0x0000;       // load MO75 control register low

  ///  Configuration of Message Object 75 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR75H = 0x6100;        // load MO75 arbitration register high
    CAN_MOAR75L = 0x0000;        // load MO75 arbitration register low

  ///  Configuration of Message Object 75 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR75H = 0x3F00;       // load MO75 acceptance mask register high
    CAN_MOAMR75L = 0x0000;       // load MO75 acceptance mask register low

  ///  Configuration of Message Object 75 interrupt pointer:
  ///  - use message pending register 2 bit position 11

    CAN_MOIPR75H = 0x0000;       // load MO75 interrupt pointer register high
    CAN_MOIPR75L = 0x4B00;       // load MO75 interrupt pointer register low

  ///  Configuration of Message Object 75 FIFO/Gateway pointer:

    CAN_MOFGPR75H = 0x0000;      // load MO75 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR75L = 0x0000;      // load MO75 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 75 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR75H = 0x0000;       // load MO75 function control register high
    CAN_MOFCR75L = 0x0000;       // load MO75 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 76:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 76 :
  ///  - message object 76 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR76H = 0x0020;       // load MO76 control register high
    CAN_MOCTR76L = 0x0000;       // load MO76 control register low

  ///  Configuration of Message Object 76 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR76H = 0x6100;        // load MO76 arbitration register high
    CAN_MOAR76L = 0x0000;        // load MO76 arbitration register low

  ///  Configuration of Message Object 76 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR76H = 0x3F00;       // load MO76 acceptance mask register high
    CAN_MOAMR76L = 0x0000;       // load MO76 acceptance mask register low

  ///  Configuration of Message Object 76 interrupt pointer:
  ///  - use message pending register 2 bit position 12

    CAN_MOIPR76H = 0x0000;       // load MO76 interrupt pointer register high
    CAN_MOIPR76L = 0x4C00;       // load MO76 interrupt pointer register low

  ///  Configuration of Message Object 76 FIFO/Gateway pointer:

    CAN_MOFGPR76H = 0x0000;      // load MO76 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR76L = 0x0000;      // load MO76 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 76 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR76H = 0x0000;       // load MO76 function control register high
    CAN_MOFCR76L = 0x0000;       // load MO76 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 77:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 77 :
  ///  - message object 77 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR77H = 0x0020;       // load MO77 control register high
    CAN_MOCTR77L = 0x0000;       // load MO77 control register low

  ///  Configuration of Message Object 77 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x01000000

    CAN_MOAR77H = 0x6100;        // load MO77 arbitration register high
    CAN_MOAR77L = 0x0000;        // load MO77 arbitration register low

  ///  Configuration of Message Object 77 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1F000000

    CAN_MOAMR77H = 0x3F00;       // load MO77 acceptance mask register high
    CAN_MOAMR77L = 0x0000;       // load MO77 acceptance mask register low

  ///  Configuration of Message Object 77 interrupt pointer:
  ///  - use message pending register 2 bit position 13

    CAN_MOIPR77H = 0x0000;       // load MO77 interrupt pointer register high
    CAN_MOIPR77L = 0x4D00;       // load MO77 interrupt pointer register low

  ///  Configuration of Message Object 77 FIFO/Gateway pointer:

    CAN_MOFGPR77H = 0x0000;      // load MO77 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR77L = 0x0000;      // load MO77 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 77 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 64
  ///  - 0 valid data bytes

    CAN_MOFCR77H = 0x0000;       // load MO77 function control register high
    CAN_MOFCR77L = 0x0000;       // load MO77 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 78:
  ///  -----------------------------------------------------------------------
  ///  - message object 78 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 79:
  ///  -----------------------------------------------------------------------
  ///  - message object 79 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 80:
  ///  -----------------------------------------------------------------------
  ///  - message object 80 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 81:
  ///  -----------------------------------------------------------------------
  ///  - message object 81 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 82:
  ///  -----------------------------------------------------------------------
  ///  - message object 82 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 83:
  ///  -----------------------------------------------------------------------
  ///  - message object 83 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 84:
  ///  -----------------------------------------------------------------------
  ///  - message object 84 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 85:
  ///  -----------------------------------------------------------------------
  ///  - message object 85 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 86:
  ///  -----------------------------------------------------------------------
  ///  - message object 86 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 87:
  ///  -----------------------------------------------------------------------
  ///  - message object 87 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 88:
  ///  -----------------------------------------------------------------------
  ///  - message object 88 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 89:
  ///  -----------------------------------------------------------------------
  ///  - message object 89 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 90:
  ///  -----------------------------------------------------------------------
  ///  - message object 90 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 91:
  ///  -----------------------------------------------------------------------
  ///  - message object 91 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 92:
  ///  -----------------------------------------------------------------------
  ///  - message object 92 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 93:
  ///  -----------------------------------------------------------------------
  ///  - message object 93 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 94:
  ///  -----------------------------------------------------------------------
  ///  - message object 94 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 95:
  ///  -----------------------------------------------------------------------
  ///  - message object 95 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 96:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 96 :
  ///  - message object 96 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR96H = 0x0EA8;       // load MO96 control register high
    CAN_MOCTR96L = 0x0000;       // load MO96 control register low

  ///  Configuration of Message Object 96 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR96H = 0x6000;        // load MO96 arbitration register high
    CAN_MOAR96L = 0x0000;        // load MO96 arbitration register low

  ///  Configuration of Message Object 96 Data:

    CAN_MODATA96HH = 0x0000;     // load MO96 Data Bytes(DB7 & DB6)
    CAN_MODATA96HL = 0x0000;     // load MO96 Data Bytes(DB5 & DB4)
    CAN_MODATA96LH = 0x0000;     // load MO96 Data Bytes(DB3 & DB2)
    CAN_MODATA96LL = 0x0000;     // load MO96 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 96 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR96H = 0x3FFF;       // load MO96 acceptance mask register high
    CAN_MOAMR96L = 0xFFFF;       // load MO96 acceptance mask register low

  ///  Configuration of Message Object 96 interrupt pointer:
  ///  - use message pending register 3 bit position 0

    CAN_MOIPR96H = 0x0000;       // load MO96 interrupt pointer register high
    CAN_MOIPR96L = 0x6002;       // load MO96 interrupt pointer register low

  ///  Configuration of Message Object 96 FIFO/Gateway pointer:
  ///  - current select pointer : MO96
  ///  - object select pointer : MO117

    CAN_MOFGPR96H = 0x7560;      // load MO96 FIFO/gateway pointer register 
                                 // high
  ///  - bottom pointer : MO96
  ///  - top pointer : MO117
    CAN_MOFGPR96L = 0x7560;      // load MO96 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 96 Function control:
  ///  - this object is a TRANSMIT FIFO BASE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR96H = 0x0800;       // load MO96 function control register high
    CAN_MOFCR96L = 0x0002;       // load MO96 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 97:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 97 :
  ///  - message object 97 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR97H = 0x0A28;       // load MO97 control register high
    CAN_MOCTR97L = 0x0000;       // load MO97 control register low

  ///  Configuration of Message Object 97 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR97H = 0x6000;        // load MO97 arbitration register high
    CAN_MOAR97L = 0x0000;        // load MO97 arbitration register low

  ///  Configuration of Message Object 97 Data:

    CAN_MODATA97HH = 0x0000;     // load MO97 Data Bytes(DB7 & DB6)
    CAN_MODATA97HL = 0x0000;     // load MO97 Data Bytes(DB5 & DB4)
    CAN_MODATA97LH = 0x0000;     // load MO97 Data Bytes(DB3 & DB2)
    CAN_MODATA97LL = 0x0000;     // load MO97 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 97 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR97H = 0x3FFF;       // load MO97 acceptance mask register high
    CAN_MOAMR97L = 0xFFFF;       // load MO97 acceptance mask register low

  ///  Configuration of Message Object 97 interrupt pointer:
  ///  - use message pending register 3 bit position 1

    CAN_MOIPR97H = 0x0000;       // load MO97 interrupt pointer register high
    CAN_MOIPR97L = 0x6100;       // load MO97 interrupt pointer register low

  ///  Configuration of Message Object 97 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR97H = 0x0060;      // load MO97 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR97L = 0x0000;      // load MO97 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 97 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR97H = 0x0000;       // load MO97 function control register high
    CAN_MOFCR97L = 0x0003;       // load MO97 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 98:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 98 :
  ///  - message object 98 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR98H = 0x0A28;       // load MO98 control register high
    CAN_MOCTR98L = 0x0000;       // load MO98 control register low

  ///  Configuration of Message Object 98 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR98H = 0x6000;        // load MO98 arbitration register high
    CAN_MOAR98L = 0x0000;        // load MO98 arbitration register low

  ///  Configuration of Message Object 98 Data:

    CAN_MODATA98HH = 0x0000;     // load MO98 Data Bytes(DB7 & DB6)
    CAN_MODATA98HL = 0x0000;     // load MO98 Data Bytes(DB5 & DB4)
    CAN_MODATA98LH = 0x0000;     // load MO98 Data Bytes(DB3 & DB2)
    CAN_MODATA98LL = 0x0000;     // load MO98 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 98 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR98H = 0x3FFF;       // load MO98 acceptance mask register high
    CAN_MOAMR98L = 0xFFFF;       // load MO98 acceptance mask register low

  ///  Configuration of Message Object 98 interrupt pointer:
  ///  - use message pending register 3 bit position 2

    CAN_MOIPR98H = 0x0000;       // load MO98 interrupt pointer register high
    CAN_MOIPR98L = 0x6200;       // load MO98 interrupt pointer register low

  ///  Configuration of Message Object 98 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR98H = 0x0060;      // load MO98 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR98L = 0x0000;      // load MO98 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 98 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR98H = 0x0000;       // load MO98 function control register high
    CAN_MOFCR98L = 0x0003;       // load MO98 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 99:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 99 :
  ///  - message object 99 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR99H = 0x0A28;       // load MO99 control register high
    CAN_MOCTR99L = 0x0000;       // load MO99 control register low

  ///  Configuration of Message Object 99 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR99H = 0x6000;        // load MO99 arbitration register high
    CAN_MOAR99L = 0x0000;        // load MO99 arbitration register low

  ///  Configuration of Message Object 99 Data:

    CAN_MODATA99HH = 0x0000;     // load MO99 Data Bytes(DB7 & DB6)
    CAN_MODATA99HL = 0x0000;     // load MO99 Data Bytes(DB5 & DB4)
    CAN_MODATA99LH = 0x0000;     // load MO99 Data Bytes(DB3 & DB2)
    CAN_MODATA99LL = 0x0000;     // load MO99 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 99 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR99H = 0x3FFF;       // load MO99 acceptance mask register high
    CAN_MOAMR99L = 0xFFFF;       // load MO99 acceptance mask register low

  ///  Configuration of Message Object 99 interrupt pointer:
  ///  - use message pending register 3 bit position 3

    CAN_MOIPR99H = 0x0000;       // load MO99 interrupt pointer register high
    CAN_MOIPR99L = 0x6300;       // load MO99 interrupt pointer register low

  ///  Configuration of Message Object 99 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR99H = 0x0060;      // load MO99 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR99L = 0x0000;      // load MO99 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 99 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR99H = 0x0000;       // load MO99 function control register high
    CAN_MOFCR99L = 0x0003;       // load MO99 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 100:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 100 :
  ///  - message object 100 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR100H = 0x0A28;      // load MO100 control register high
    CAN_MOCTR100L = 0x0000;      // load MO100 control register low

  ///  Configuration of Message Object 100 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR100H = 0x6000;       // load MO100 arbitration register high
    CAN_MOAR100L = 0x0000;       // load MO100 arbitration register low

  ///  Configuration of Message Object 100 Data:

    CAN_MODATA100HH = 0x0000;    // load MO100 Data Bytes(DB7 & DB6)
    CAN_MODATA100HL = 0x0000;    // load MO100 Data Bytes(DB5 & DB4)
    CAN_MODATA100LH = 0x0000;    // load MO100 Data Bytes(DB3 & DB2)
    CAN_MODATA100LL = 0x0000;    // load MO100 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 100 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR100H = 0x3FFF;      // load MO100 acceptance mask register high
    CAN_MOAMR100L = 0xFFFF;      // load MO100 acceptance mask register low

  ///  Configuration of Message Object 100 interrupt pointer:
  ///  - use message pending register 3 bit position 4

    CAN_MOIPR100H = 0x0000;      // load MO100 interrupt pointer register high
    CAN_MOIPR100L = 0x6400;      // load MO100 interrupt pointer register low

  ///  Configuration of Message Object 100 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR100H = 0x0060;     // load MO100 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR100L = 0x0000;     // load MO100 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 100 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR100H = 0x0000;      // load MO100 function control register high
    CAN_MOFCR100L = 0x0003;      // load MO100 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 101:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 101 :
  ///  - message object 101 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR101H = 0x0A28;      // load MO101 control register high
    CAN_MOCTR101L = 0x0000;      // load MO101 control register low

  ///  Configuration of Message Object 101 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR101H = 0x6000;       // load MO101 arbitration register high
    CAN_MOAR101L = 0x0000;       // load MO101 arbitration register low

  ///  Configuration of Message Object 101 Data:

    CAN_MODATA101HH = 0x0000;    // load MO101 Data Bytes(DB7 & DB6)
    CAN_MODATA101HL = 0x0000;    // load MO101 Data Bytes(DB5 & DB4)
    CAN_MODATA101LH = 0x0000;    // load MO101 Data Bytes(DB3 & DB2)
    CAN_MODATA101LL = 0x0000;    // load MO101 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 101 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR101H = 0x3FFF;      // load MO101 acceptance mask register high
    CAN_MOAMR101L = 0xFFFF;      // load MO101 acceptance mask register low

  ///  Configuration of Message Object 101 interrupt pointer:
  ///  - use message pending register 3 bit position 5

    CAN_MOIPR101H = 0x0000;      // load MO101 interrupt pointer register high
    CAN_MOIPR101L = 0x6500;      // load MO101 interrupt pointer register low

  ///  Configuration of Message Object 101 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR101H = 0x0060;     // load MO101 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR101L = 0x0000;     // load MO101 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 101 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR101H = 0x0000;      // load MO101 function control register high
    CAN_MOFCR101L = 0x0003;      // load MO101 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 102:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 102 :
  ///  - message object 102 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR102H = 0x0A28;      // load MO102 control register high
    CAN_MOCTR102L = 0x0000;      // load MO102 control register low

  ///  Configuration of Message Object 102 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR102H = 0x6000;       // load MO102 arbitration register high
    CAN_MOAR102L = 0x0000;       // load MO102 arbitration register low

  ///  Configuration of Message Object 102 Data:

    CAN_MODATA102HH = 0x0000;    // load MO102 Data Bytes(DB7 & DB6)
    CAN_MODATA102HL = 0x0000;    // load MO102 Data Bytes(DB5 & DB4)
    CAN_MODATA102LH = 0x0000;    // load MO102 Data Bytes(DB3 & DB2)
    CAN_MODATA102LL = 0x0000;    // load MO102 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 102 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR102H = 0x3FFF;      // load MO102 acceptance mask register high
    CAN_MOAMR102L = 0xFFFF;      // load MO102 acceptance mask register low

  ///  Configuration of Message Object 102 interrupt pointer:
  ///  - use message pending register 3 bit position 6

    CAN_MOIPR102H = 0x0000;      // load MO102 interrupt pointer register high
    CAN_MOIPR102L = 0x6600;      // load MO102 interrupt pointer register low

  ///  Configuration of Message Object 102 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR102H = 0x0060;     // load MO102 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR102L = 0x0000;     // load MO102 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 102 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR102H = 0x0000;      // load MO102 function control register high
    CAN_MOFCR102L = 0x0003;      // load MO102 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 103:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 103 :
  ///  - message object 103 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR103H = 0x0A28;      // load MO103 control register high
    CAN_MOCTR103L = 0x0000;      // load MO103 control register low

  ///  Configuration of Message Object 103 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR103H = 0x6000;       // load MO103 arbitration register high
    CAN_MOAR103L = 0x0000;       // load MO103 arbitration register low

  ///  Configuration of Message Object 103 Data:

    CAN_MODATA103HH = 0x0000;    // load MO103 Data Bytes(DB7 & DB6)
    CAN_MODATA103HL = 0x0000;    // load MO103 Data Bytes(DB5 & DB4)
    CAN_MODATA103LH = 0x0000;    // load MO103 Data Bytes(DB3 & DB2)
    CAN_MODATA103LL = 0x0000;    // load MO103 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 103 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR103H = 0x3FFF;      // load MO103 acceptance mask register high
    CAN_MOAMR103L = 0xFFFF;      // load MO103 acceptance mask register low

  ///  Configuration of Message Object 103 interrupt pointer:
  ///  - use message pending register 3 bit position 7

    CAN_MOIPR103H = 0x0000;      // load MO103 interrupt pointer register high
    CAN_MOIPR103L = 0x6700;      // load MO103 interrupt pointer register low

  ///  Configuration of Message Object 103 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR103H = 0x0060;     // load MO103 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR103L = 0x0000;     // load MO103 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 103 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR103H = 0x0000;      // load MO103 function control register high
    CAN_MOFCR103L = 0x0003;      // load MO103 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 104:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 104 :
  ///  - message object 104 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR104H = 0x0A28;      // load MO104 control register high
    CAN_MOCTR104L = 0x0000;      // load MO104 control register low

  ///  Configuration of Message Object 104 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR104H = 0x6000;       // load MO104 arbitration register high
    CAN_MOAR104L = 0x0000;       // load MO104 arbitration register low

  ///  Configuration of Message Object 104 Data:

    CAN_MODATA104HH = 0x0000;    // load MO104 Data Bytes(DB7 & DB6)
    CAN_MODATA104HL = 0x0000;    // load MO104 Data Bytes(DB5 & DB4)
    CAN_MODATA104LH = 0x0000;    // load MO104 Data Bytes(DB3 & DB2)
    CAN_MODATA104LL = 0x0000;    // load MO104 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 104 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR104H = 0x3FFF;      // load MO104 acceptance mask register high
    CAN_MOAMR104L = 0xFFFF;      // load MO104 acceptance mask register low

  ///  Configuration of Message Object 104 interrupt pointer:
  ///  - use message pending register 3 bit position 8

    CAN_MOIPR104H = 0x0000;      // load MO104 interrupt pointer register high
    CAN_MOIPR104L = 0x6800;      // load MO104 interrupt pointer register low

  ///  Configuration of Message Object 104 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR104H = 0x0060;     // load MO104 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR104L = 0x0000;     // load MO104 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 104 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR104H = 0x0000;      // load MO104 function control register high
    CAN_MOFCR104L = 0x0003;      // load MO104 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 105:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 105 :
  ///  - message object 105 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR105H = 0x0A28;      // load MO105 control register high
    CAN_MOCTR105L = 0x0000;      // load MO105 control register low

  ///  Configuration of Message Object 105 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR105H = 0x6000;       // load MO105 arbitration register high
    CAN_MOAR105L = 0x0000;       // load MO105 arbitration register low

  ///  Configuration of Message Object 105 Data:

    CAN_MODATA105HH = 0x0000;    // load MO105 Data Bytes(DB7 & DB6)
    CAN_MODATA105HL = 0x0000;    // load MO105 Data Bytes(DB5 & DB4)
    CAN_MODATA105LH = 0x0000;    // load MO105 Data Bytes(DB3 & DB2)
    CAN_MODATA105LL = 0x0000;    // load MO105 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 105 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR105H = 0x3FFF;      // load MO105 acceptance mask register high
    CAN_MOAMR105L = 0xFFFF;      // load MO105 acceptance mask register low

  ///  Configuration of Message Object 105 interrupt pointer:
  ///  - use message pending register 3 bit position 9

    CAN_MOIPR105H = 0x0000;      // load MO105 interrupt pointer register high
    CAN_MOIPR105L = 0x6900;      // load MO105 interrupt pointer register low

  ///  Configuration of Message Object 105 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR105H = 0x0060;     // load MO105 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR105L = 0x0000;     // load MO105 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 105 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR105H = 0x0000;      // load MO105 function control register high
    CAN_MOFCR105L = 0x0003;      // load MO105 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 106:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 106 :
  ///  - message object 106 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR106H = 0x0A28;      // load MO106 control register high
    CAN_MOCTR106L = 0x0000;      // load MO106 control register low

  ///  Configuration of Message Object 106 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR106H = 0x6000;       // load MO106 arbitration register high
    CAN_MOAR106L = 0x0000;       // load MO106 arbitration register low

  ///  Configuration of Message Object 106 Data:

    CAN_MODATA106HH = 0x0000;    // load MO106 Data Bytes(DB7 & DB6)
    CAN_MODATA106HL = 0x0000;    // load MO106 Data Bytes(DB5 & DB4)
    CAN_MODATA106LH = 0x0000;    // load MO106 Data Bytes(DB3 & DB2)
    CAN_MODATA106LL = 0x0000;    // load MO106 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 106 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR106H = 0x3FFF;      // load MO106 acceptance mask register high
    CAN_MOAMR106L = 0xFFFF;      // load MO106 acceptance mask register low

  ///  Configuration of Message Object 106 interrupt pointer:
  ///  - use message pending register 3 bit position 10

    CAN_MOIPR106H = 0x0000;      // load MO106 interrupt pointer register high
    CAN_MOIPR106L = 0x6A00;      // load MO106 interrupt pointer register low

  ///  Configuration of Message Object 106 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR106H = 0x0060;     // load MO106 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR106L = 0x0000;     // load MO106 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 106 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR106H = 0x0000;      // load MO106 function control register high
    CAN_MOFCR106L = 0x0003;      // load MO106 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 107:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 107 :
  ///  - message object 107 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR107H = 0x0A28;      // load MO107 control register high
    CAN_MOCTR107L = 0x0000;      // load MO107 control register low

  ///  Configuration of Message Object 107 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR107H = 0x6000;       // load MO107 arbitration register high
    CAN_MOAR107L = 0x0000;       // load MO107 arbitration register low

  ///  Configuration of Message Object 107 Data:

    CAN_MODATA107HH = 0x0000;    // load MO107 Data Bytes(DB7 & DB6)
    CAN_MODATA107HL = 0x0000;    // load MO107 Data Bytes(DB5 & DB4)
    CAN_MODATA107LH = 0x0000;    // load MO107 Data Bytes(DB3 & DB2)
    CAN_MODATA107LL = 0x0000;    // load MO107 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 107 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR107H = 0x3FFF;      // load MO107 acceptance mask register high
    CAN_MOAMR107L = 0xFFFF;      // load MO107 acceptance mask register low

  ///  Configuration of Message Object 107 interrupt pointer:
  ///  - use message pending register 3 bit position 11

    CAN_MOIPR107H = 0x0000;      // load MO107 interrupt pointer register high
    CAN_MOIPR107L = 0x6B00;      // load MO107 interrupt pointer register low

  ///  Configuration of Message Object 107 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR107H = 0x0060;     // load MO107 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR107L = 0x0000;     // load MO107 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 107 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR107H = 0x0000;      // load MO107 function control register high
    CAN_MOFCR107L = 0x0003;      // load MO107 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 108:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 108 :
  ///  - message object 108 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR108H = 0x0A28;      // load MO108 control register high
    CAN_MOCTR108L = 0x0000;      // load MO108 control register low

  ///  Configuration of Message Object 108 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR108H = 0x6000;       // load MO108 arbitration register high
    CAN_MOAR108L = 0x0000;       // load MO108 arbitration register low

  ///  Configuration of Message Object 108 Data:

    CAN_MODATA108HH = 0x0000;    // load MO108 Data Bytes(DB7 & DB6)
    CAN_MODATA108HL = 0x0000;    // load MO108 Data Bytes(DB5 & DB4)
    CAN_MODATA108LH = 0x0000;    // load MO108 Data Bytes(DB3 & DB2)
    CAN_MODATA108LL = 0x0000;    // load MO108 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 108 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR108H = 0x3FFF;      // load MO108 acceptance mask register high
    CAN_MOAMR108L = 0xFFFF;      // load MO108 acceptance mask register low

  ///  Configuration of Message Object 108 interrupt pointer:
  ///  - use message pending register 3 bit position 12

    CAN_MOIPR108H = 0x0000;      // load MO108 interrupt pointer register high
    CAN_MOIPR108L = 0x6C00;      // load MO108 interrupt pointer register low

  ///  Configuration of Message Object 108 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR108H = 0x0060;     // load MO108 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR108L = 0x0000;     // load MO108 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 108 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR108H = 0x0000;      // load MO108 function control register high
    CAN_MOFCR108L = 0x0003;      // load MO108 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 109:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 109 :
  ///  - message object 109 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR109H = 0x0A28;      // load MO109 control register high
    CAN_MOCTR109L = 0x0000;      // load MO109 control register low

  ///  Configuration of Message Object 109 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR109H = 0x6000;       // load MO109 arbitration register high
    CAN_MOAR109L = 0x0000;       // load MO109 arbitration register low

  ///  Configuration of Message Object 109 Data:

    CAN_MODATA109HH = 0x0000;    // load MO109 Data Bytes(DB7 & DB6)
    CAN_MODATA109HL = 0x0000;    // load MO109 Data Bytes(DB5 & DB4)
    CAN_MODATA109LH = 0x0000;    // load MO109 Data Bytes(DB3 & DB2)
    CAN_MODATA109LL = 0x0000;    // load MO109 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 109 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR109H = 0x3FFF;      // load MO109 acceptance mask register high
    CAN_MOAMR109L = 0xFFFF;      // load MO109 acceptance mask register low

  ///  Configuration of Message Object 109 interrupt pointer:
  ///  - use message pending register 3 bit position 13

    CAN_MOIPR109H = 0x0000;      // load MO109 interrupt pointer register high
    CAN_MOIPR109L = 0x6D00;      // load MO109 interrupt pointer register low

  ///  Configuration of Message Object 109 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR109H = 0x0060;     // load MO109 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR109L = 0x0000;     // load MO109 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 109 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR109H = 0x0000;      // load MO109 function control register high
    CAN_MOFCR109L = 0x0003;      // load MO109 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 110:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 110 :
  ///  - message object 110 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR110H = 0x0A28;      // load MO110 control register high
    CAN_MOCTR110L = 0x0000;      // load MO110 control register low

  ///  Configuration of Message Object 110 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR110H = 0x6000;       // load MO110 arbitration register high
    CAN_MOAR110L = 0x0000;       // load MO110 arbitration register low

  ///  Configuration of Message Object 110 Data:

    CAN_MODATA110HH = 0x0000;    // load MO110 Data Bytes(DB7 & DB6)
    CAN_MODATA110HL = 0x0000;    // load MO110 Data Bytes(DB5 & DB4)
    CAN_MODATA110LH = 0x0000;    // load MO110 Data Bytes(DB3 & DB2)
    CAN_MODATA110LL = 0x0000;    // load MO110 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 110 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR110H = 0x3FFF;      // load MO110 acceptance mask register high
    CAN_MOAMR110L = 0xFFFF;      // load MO110 acceptance mask register low

  ///  Configuration of Message Object 110 interrupt pointer:
  ///  - use message pending register 3 bit position 14

    CAN_MOIPR110H = 0x0000;      // load MO110 interrupt pointer register high
    CAN_MOIPR110L = 0x6E00;      // load MO110 interrupt pointer register low

  ///  Configuration of Message Object 110 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR110H = 0x0060;     // load MO110 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR110L = 0x0000;     // load MO110 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 110 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR110H = 0x0000;      // load MO110 function control register high
    CAN_MOFCR110L = 0x0003;      // load MO110 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 111:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 111 :
  ///  - message object 111 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR111H = 0x0A28;      // load MO111 control register high
    CAN_MOCTR111L = 0x0000;      // load MO111 control register low

  ///  Configuration of Message Object 111 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR111H = 0x6000;       // load MO111 arbitration register high
    CAN_MOAR111L = 0x0000;       // load MO111 arbitration register low

  ///  Configuration of Message Object 111 Data:

    CAN_MODATA111HH = 0x0000;    // load MO111 Data Bytes(DB7 & DB6)
    CAN_MODATA111HL = 0x0000;    // load MO111 Data Bytes(DB5 & DB4)
    CAN_MODATA111LH = 0x0000;    // load MO111 Data Bytes(DB3 & DB2)
    CAN_MODATA111LL = 0x0000;    // load MO111 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 111 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR111H = 0x3FFF;      // load MO111 acceptance mask register high
    CAN_MOAMR111L = 0xFFFF;      // load MO111 acceptance mask register low

  ///  Configuration of Message Object 111 interrupt pointer:
  ///  - use message pending register 3 bit position 15

    CAN_MOIPR111H = 0x0000;      // load MO111 interrupt pointer register high
    CAN_MOIPR111L = 0x6F00;      // load MO111 interrupt pointer register low

  ///  Configuration of Message Object 111 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR111H = 0x0060;     // load MO111 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR111L = 0x0000;     // load MO111 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 111 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR111H = 0x0000;      // load MO111 function control register high
    CAN_MOFCR111L = 0x0003;      // load MO111 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 112:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 112 :
  ///  - message object 112 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR112H = 0x0A28;      // load MO112 control register high
    CAN_MOCTR112L = 0x0000;      // load MO112 control register low

  ///  Configuration of Message Object 112 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR112H = 0x6000;       // load MO112 arbitration register high
    CAN_MOAR112L = 0x0000;       // load MO112 arbitration register low

  ///  Configuration of Message Object 112 Data:

    CAN_MODATA112HH = 0x0000;    // load MO112 Data Bytes(DB7 & DB6)
    CAN_MODATA112HL = 0x0000;    // load MO112 Data Bytes(DB5 & DB4)
    CAN_MODATA112LH = 0x0000;    // load MO112 Data Bytes(DB3 & DB2)
    CAN_MODATA112LL = 0x0000;    // load MO112 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 112 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR112H = 0x3FFF;      // load MO112 acceptance mask register high
    CAN_MOAMR112L = 0xFFFF;      // load MO112 acceptance mask register low

  ///  Configuration of Message Object 112 interrupt pointer:
  ///  - use message pending register 3 bit position 16

    CAN_MOIPR112H = 0x0000;      // load MO112 interrupt pointer register high
    CAN_MOIPR112L = 0x7000;      // load MO112 interrupt pointer register low

  ///  Configuration of Message Object 112 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR112H = 0x0060;     // load MO112 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR112L = 0x0000;     // load MO112 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 112 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR112H = 0x0000;      // load MO112 function control register high
    CAN_MOFCR112L = 0x0003;      // load MO112 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 113:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 113 :
  ///  - message object 113 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR113H = 0x0A28;      // load MO113 control register high
    CAN_MOCTR113L = 0x0000;      // load MO113 control register low

  ///  Configuration of Message Object 113 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR113H = 0x6000;       // load MO113 arbitration register high
    CAN_MOAR113L = 0x0000;       // load MO113 arbitration register low

  ///  Configuration of Message Object 113 Data:

    CAN_MODATA113HH = 0x0000;    // load MO113 Data Bytes(DB7 & DB6)
    CAN_MODATA113HL = 0x0000;    // load MO113 Data Bytes(DB5 & DB4)
    CAN_MODATA113LH = 0x0000;    // load MO113 Data Bytes(DB3 & DB2)
    CAN_MODATA113LL = 0x0000;    // load MO113 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 113 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR113H = 0x3FFF;      // load MO113 acceptance mask register high
    CAN_MOAMR113L = 0xFFFF;      // load MO113 acceptance mask register low

  ///  Configuration of Message Object 113 interrupt pointer:
  ///  - use message pending register 3 bit position 17

    CAN_MOIPR113H = 0x0000;      // load MO113 interrupt pointer register high
    CAN_MOIPR113L = 0x7100;      // load MO113 interrupt pointer register low

  ///  Configuration of Message Object 113 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR113H = 0x0060;     // load MO113 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR113L = 0x0000;     // load MO113 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 113 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR113H = 0x0000;      // load MO113 function control register high
    CAN_MOFCR113L = 0x0003;      // load MO113 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 114:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 114 :
  ///  - message object 114 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR114H = 0x0A28;      // load MO114 control register high
    CAN_MOCTR114L = 0x0000;      // load MO114 control register low

  ///  Configuration of Message Object 114 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR114H = 0x6000;       // load MO114 arbitration register high
    CAN_MOAR114L = 0x0000;       // load MO114 arbitration register low

  ///  Configuration of Message Object 114 Data:

    CAN_MODATA114HH = 0x0000;    // load MO114 Data Bytes(DB7 & DB6)
    CAN_MODATA114HL = 0x0000;    // load MO114 Data Bytes(DB5 & DB4)
    CAN_MODATA114LH = 0x0000;    // load MO114 Data Bytes(DB3 & DB2)
    CAN_MODATA114LL = 0x0000;    // load MO114 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 114 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR114H = 0x3FFF;      // load MO114 acceptance mask register high
    CAN_MOAMR114L = 0xFFFF;      // load MO114 acceptance mask register low

  ///  Configuration of Message Object 114 interrupt pointer:
  ///  - use message pending register 3 bit position 18

    CAN_MOIPR114H = 0x0000;      // load MO114 interrupt pointer register high
    CAN_MOIPR114L = 0x7200;      // load MO114 interrupt pointer register low

  ///  Configuration of Message Object 114 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR114H = 0x0060;     // load MO114 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR114L = 0x0000;     // load MO114 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 114 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR114H = 0x0000;      // load MO114 function control register high
    CAN_MOFCR114L = 0x0003;      // load MO114 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 115:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 115 :
  ///  - message object 115 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR115H = 0x0A28;      // load MO115 control register high
    CAN_MOCTR115L = 0x0000;      // load MO115 control register low

  ///  Configuration of Message Object 115 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR115H = 0x6000;       // load MO115 arbitration register high
    CAN_MOAR115L = 0x0000;       // load MO115 arbitration register low

  ///  Configuration of Message Object 115 Data:

    CAN_MODATA115HH = 0x0000;    // load MO115 Data Bytes(DB7 & DB6)
    CAN_MODATA115HL = 0x0000;    // load MO115 Data Bytes(DB5 & DB4)
    CAN_MODATA115LH = 0x0000;    // load MO115 Data Bytes(DB3 & DB2)
    CAN_MODATA115LL = 0x0000;    // load MO115 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 115 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR115H = 0x3FFF;      // load MO115 acceptance mask register high
    CAN_MOAMR115L = 0xFFFF;      // load MO115 acceptance mask register low

  ///  Configuration of Message Object 115 interrupt pointer:
  ///  - use message pending register 3 bit position 19

    CAN_MOIPR115H = 0x0000;      // load MO115 interrupt pointer register high
    CAN_MOIPR115L = 0x7300;      // load MO115 interrupt pointer register low

  ///  Configuration of Message Object 115 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR115H = 0x0060;     // load MO115 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR115L = 0x0000;     // load MO115 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 115 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR115H = 0x0000;      // load MO115 function control register high
    CAN_MOFCR115L = 0x0003;      // load MO115 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 116:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 116 :
  ///  - message object 116 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR116H = 0x0A28;      // load MO116 control register high
    CAN_MOCTR116L = 0x0000;      // load MO116 control register low

  ///  Configuration of Message Object 116 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR116H = 0x6000;       // load MO116 arbitration register high
    CAN_MOAR116L = 0x0000;       // load MO116 arbitration register low

  ///  Configuration of Message Object 116 Data:

    CAN_MODATA116HH = 0x0000;    // load MO116 Data Bytes(DB7 & DB6)
    CAN_MODATA116HL = 0x0000;    // load MO116 Data Bytes(DB5 & DB4)
    CAN_MODATA116LH = 0x0000;    // load MO116 Data Bytes(DB3 & DB2)
    CAN_MODATA116LL = 0x0000;    // load MO116 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 116 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR116H = 0x3FFF;      // load MO116 acceptance mask register high
    CAN_MOAMR116L = 0xFFFF;      // load MO116 acceptance mask register low

  ///  Configuration of Message Object 116 interrupt pointer:
  ///  - use message pending register 3 bit position 20

    CAN_MOIPR116H = 0x0000;      // load MO116 interrupt pointer register high
    CAN_MOIPR116L = 0x7400;      // load MO116 interrupt pointer register low

  ///  Configuration of Message Object 116 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR116H = 0x0060;     // load MO116 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR116L = 0x0000;     // load MO116 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 116 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR116H = 0x0000;      // load MO116 function control register high
    CAN_MOFCR116L = 0x0003;      // load MO116 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 117:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 117 :
  ///  - message object 117 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 2 (node 1)

    CAN_MOCTR117H = 0x0A28;      // load MO117 control register high
    CAN_MOCTR117L = 0x0000;      // load MO117 control register low

  ///  Configuration of Message Object 117 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR117H = 0x6000;       // load MO117 arbitration register high
    CAN_MOAR117L = 0x0000;       // load MO117 arbitration register low

  ///  Configuration of Message Object 117 Data:

    CAN_MODATA117HH = 0x0000;    // load MO117 Data Bytes(DB7 & DB6)
    CAN_MODATA117HL = 0x0000;    // load MO117 Data Bytes(DB5 & DB4)
    CAN_MODATA117LH = 0x0000;    // load MO117 Data Bytes(DB3 & DB2)
    CAN_MODATA117LL = 0x0000;    // load MO117 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 117 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR117H = 0x3FFF;      // load MO117 acceptance mask register high
    CAN_MOAMR117L = 0xFFFF;      // load MO117 acceptance mask register low

  ///  Configuration of Message Object 117 interrupt pointer:
  ///  - use message pending register 3 bit position 21

    CAN_MOIPR117H = 0x0000;      // load MO117 interrupt pointer register high
    CAN_MOIPR117L = 0x7500;      // load MO117 interrupt pointer register low

  ///  Configuration of Message Object 117 FIFO/Gateway pointer:
  ///  - current select pointer : MO96

    CAN_MOFGPR117H = 0x0060;     // load MO117 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR117L = 0x0000;     // load MO117 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 117 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 96
  ///  - 0 valid data bytes

    CAN_MOFCR117H = 0x0000;      // load MO117 function control register high
    CAN_MOFCR117L = 0x0003;      // load MO117 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 118:
  ///  -----------------------------------------------------------------------
  ///  - message object 118 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 119:
  ///  -----------------------------------------------------------------------
  ///  - message object 119 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 120:
  ///  -----------------------------------------------------------------------
  ///  - message object 120 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 121:
  ///  -----------------------------------------------------------------------
  ///  - message object 121 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 122:
  ///  -----------------------------------------------------------------------
  ///  - message object 122 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 123:
  ///  -----------------------------------------------------------------------
  ///  - message object 123 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 124:
  ///  -----------------------------------------------------------------------
  ///  - message object 124 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 125:
  ///  -----------------------------------------------------------------------
  ///  - message object 125 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 126:
  ///  -----------------------------------------------------------------------
  ///  - message object 126 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 127:
  ///  -----------------------------------------------------------------------
  ///  - message object 127 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 128:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 128 :
  ///  - message object 128 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR128H = 0x00A0;      // load MO128 control register high
    CAN_MOCTR128L = 0x0000;      // load MO128 control register low

  ///  Configuration of Message Object 128 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x0000F456

    CAN_MOAR128H = 0x6000;       // load MO128 arbitration register high
    CAN_MOAR128L = 0xF456;       // load MO128 arbitration register low

  ///  Configuration of Message Object 128 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x000000FF

    CAN_MOAMR128H = 0x2000;      // load MO128 acceptance mask register high
    CAN_MOAMR128L = 0x00FF;      // load MO128 acceptance mask register low

  ///  Configuration of Message Object 128 interrupt pointer:
  ///  - use message pending register 4 bit position 0

    CAN_MOIPR128H = 0x0000;      // load MO128 interrupt pointer register high
    CAN_MOIPR128L = 0x8022;      // load MO128 interrupt pointer register low

  ///  Configuration of Message Object 128 FIFO/Gateway pointer:
  ///  - current select pointer : MO128
  ///  - object select pointer : MO132

    CAN_MOFGPR128H = 0x8480;     // load MO128 FIFO/gateway pointer register 
                                 // high
  ///  - bottom pointer : MO128
  ///  - top pointer : MO132
    CAN_MOFGPR128L = 0x8480;     // load MO128 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 128 Function control:
  ///  - this object is a RECEIVE FIFO BASE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR128H = 0x0800;      // load MO128 function control register high
    CAN_MOFCR128L = 0x0001;      // load MO128 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 129:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 129 :
  ///  - message object 129 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR129H = 0x0020;      // load MO129 control register high
    CAN_MOCTR129L = 0x0000;      // load MO129 control register low

  ///  Configuration of Message Object 129 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x0000F456

    CAN_MOAR129H = 0x6000;       // load MO129 arbitration register high
    CAN_MOAR129L = 0xF456;       // load MO129 arbitration register low

  ///  Configuration of Message Object 129 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x000000FF

    CAN_MOAMR129H = 0x2000;      // load MO129 acceptance mask register high
    CAN_MOAMR129L = 0x00FF;      // load MO129 acceptance mask register low

  ///  Configuration of Message Object 129 interrupt pointer:
  ///  - use message pending register 4 bit position 1

    CAN_MOIPR129H = 0x0000;      // load MO129 interrupt pointer register high
    CAN_MOIPR129L = 0x8100;      // load MO129 interrupt pointer register low

  ///  Configuration of Message Object 129 FIFO/Gateway pointer:

    CAN_MOFGPR129H = 0x0000;     // load MO129 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR129L = 0x0000;     // load MO129 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 129 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 128
  ///  - 0 valid data bytes

    CAN_MOFCR129H = 0x0000;      // load MO129 function control register high
    CAN_MOFCR129L = 0x0000;      // load MO129 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 130:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 130 :
  ///  - message object 130 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR130H = 0x0020;      // load MO130 control register high
    CAN_MOCTR130L = 0x0000;      // load MO130 control register low

  ///  Configuration of Message Object 130 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x0000F456

    CAN_MOAR130H = 0x6000;       // load MO130 arbitration register high
    CAN_MOAR130L = 0xF456;       // load MO130 arbitration register low

  ///  Configuration of Message Object 130 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x000000FF

    CAN_MOAMR130H = 0x2000;      // load MO130 acceptance mask register high
    CAN_MOAMR130L = 0x00FF;      // load MO130 acceptance mask register low

  ///  Configuration of Message Object 130 interrupt pointer:
  ///  - use message pending register 4 bit position 2

    CAN_MOIPR130H = 0x0000;      // load MO130 interrupt pointer register high
    CAN_MOIPR130L = 0x8200;      // load MO130 interrupt pointer register low

  ///  Configuration of Message Object 130 FIFO/Gateway pointer:

    CAN_MOFGPR130H = 0x0000;     // load MO130 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR130L = 0x0000;     // load MO130 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 130 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 128
  ///  - 0 valid data bytes

    CAN_MOFCR130H = 0x0000;      // load MO130 function control register high
    CAN_MOFCR130L = 0x0000;      // load MO130 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 131:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 131 :
  ///  - message object 131 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR131H = 0x0020;      // load MO131 control register high
    CAN_MOCTR131L = 0x0000;      // load MO131 control register low

  ///  Configuration of Message Object 131 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x0000F456

    CAN_MOAR131H = 0x6000;       // load MO131 arbitration register high
    CAN_MOAR131L = 0xF456;       // load MO131 arbitration register low

  ///  Configuration of Message Object 131 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x000000FF

    CAN_MOAMR131H = 0x2000;      // load MO131 acceptance mask register high
    CAN_MOAMR131L = 0x00FF;      // load MO131 acceptance mask register low

  ///  Configuration of Message Object 131 interrupt pointer:
  ///  - use message pending register 4 bit position 3

    CAN_MOIPR131H = 0x0000;      // load MO131 interrupt pointer register high
    CAN_MOIPR131L = 0x8300;      // load MO131 interrupt pointer register low

  ///  Configuration of Message Object 131 FIFO/Gateway pointer:

    CAN_MOFGPR131H = 0x0000;     // load MO131 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR131L = 0x0000;     // load MO131 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 131 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 128
  ///  - 0 valid data bytes

    CAN_MOFCR131H = 0x0000;      // load MO131 function control register high
    CAN_MOFCR131L = 0x0000;      // load MO131 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 132:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 132 :
  ///  - message object 132 is valid
  ///  - message object is used as receive object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR132H = 0x0020;      // load MO132 control register high
    CAN_MOCTR132L = 0x0000;      // load MO132 control register low

  ///  Configuration of Message Object 132 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x0000F456

    CAN_MOAR132H = 0x6000;       // load MO132 arbitration register high
    CAN_MOAR132L = 0xF456;       // load MO132 arbitration register low

  ///  Configuration of Message Object 132 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x000000FF

    CAN_MOAMR132H = 0x2000;      // load MO132 acceptance mask register high
    CAN_MOAMR132L = 0x00FF;      // load MO132 acceptance mask register low

  ///  Configuration of Message Object 132 interrupt pointer:
  ///  - use message pending register 4 bit position 4

    CAN_MOIPR132H = 0x0000;      // load MO132 interrupt pointer register high
    CAN_MOIPR132L = 0x8400;      // load MO132 interrupt pointer register low

  ///  Configuration of Message Object 132 FIFO/Gateway pointer:

    CAN_MOFGPR132H = 0x0000;     // load MO132 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR132L = 0x0000;     // load MO132 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 132 Function control:
  ///  - this object is a RECEIVE FIFO SLAVE OBJECT connected to the base 
  ///    object 128
  ///  - 0 valid data bytes

    CAN_MOFCR132H = 0x0000;      // load MO132 function control register high
    CAN_MOFCR132L = 0x0000;      // load MO132 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 133:
  ///  -----------------------------------------------------------------------
  ///  - message object 133 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 134:
  ///  -----------------------------------------------------------------------
  ///  - message object 134 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 135:
  ///  -----------------------------------------------------------------------
  ///  - message object 135 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 136:
  ///  -----------------------------------------------------------------------
  ///  - message object 136 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 137:
  ///  -----------------------------------------------------------------------
  ///  - message object 137 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 138:
  ///  -----------------------------------------------------------------------
  ///  - message object 138 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 139:
  ///  -----------------------------------------------------------------------
  ///  - message object 139 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 140:
  ///  -----------------------------------------------------------------------
  ///  - message object 140 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 141:
  ///  -----------------------------------------------------------------------
  ///  - message object 141 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 142:
  ///  -----------------------------------------------------------------------
  ///  - message object 142 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 143:
  ///  -----------------------------------------------------------------------
  ///  - message object 143 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 144:
  ///  -----------------------------------------------------------------------
  ///  - message object 144 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 145:
  ///  -----------------------------------------------------------------------
  ///  - message object 145 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 146:
  ///  -----------------------------------------------------------------------
  ///  - message object 146 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 147:
  ///  -----------------------------------------------------------------------
  ///  - message object 147 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 148:
  ///  -----------------------------------------------------------------------
  ///  - message object 148 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 149:
  ///  -----------------------------------------------------------------------
  ///  - message object 149 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 150:
  ///  -----------------------------------------------------------------------
  ///  - message object 150 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 151:
  ///  -----------------------------------------------------------------------
  ///  - message object 151 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 152:
  ///  -----------------------------------------------------------------------
  ///  - message object 152 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 153:
  ///  -----------------------------------------------------------------------
  ///  - message object 153 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 154:
  ///  -----------------------------------------------------------------------
  ///  - message object 154 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 155:
  ///  -----------------------------------------------------------------------
  ///  - message object 155 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 156:
  ///  -----------------------------------------------------------------------
  ///  - message object 156 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 157:
  ///  -----------------------------------------------------------------------
  ///  - message object 157 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 158:
  ///  -----------------------------------------------------------------------
  ///  - message object 158 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 159:
  ///  -----------------------------------------------------------------------
  ///  - message object 159 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 160:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 160 :
  ///  - message object 160 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR160H = 0x0EA8;      // load MO160 control register high
    CAN_MOCTR160L = 0x0000;      // load MO160 control register low

  ///  Configuration of Message Object 160 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR160H = 0x6000;       // load MO160 arbitration register high
    CAN_MOAR160L = 0x0000;       // load MO160 arbitration register low

  ///  Configuration of Message Object 160 Data:

    CAN_MODATA160HH = 0x0000;    // load MO160 Data Bytes(DB7 & DB6)
    CAN_MODATA160HL = 0x0000;    // load MO160 Data Bytes(DB5 & DB4)
    CAN_MODATA160LH = 0x0000;    // load MO160 Data Bytes(DB3 & DB2)
    CAN_MODATA160LL = 0x0000;    // load MO160 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 160 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR160H = 0x3FFF;      // load MO160 acceptance mask register high
    CAN_MOAMR160L = 0xFFFF;      // load MO160 acceptance mask register low

  ///  Configuration of Message Object 160 interrupt pointer:
  ///  - use message pending register 5 bit position 0

    CAN_MOIPR160H = 0x0000;      // load MO160 interrupt pointer register high
    CAN_MOIPR160L = 0xA000;      // load MO160 interrupt pointer register low

  ///  Configuration of Message Object 160 FIFO/Gateway pointer:
  ///  - current select pointer : MO160
  ///  - object select pointer : MO164

    CAN_MOFGPR160H = 0xA4A0;     // load MO160 FIFO/gateway pointer register 
                                 // high
  ///  - bottom pointer : MO160
  ///  - top pointer : MO164
    CAN_MOFGPR160L = 0xA4A0;     // load MO160 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 160 Function control:
  ///  - this object is a TRANSMIT FIFO BASE OBJECT
  ///  - 8 valid data bytes

    CAN_MOFCR160H = 0x0800;      // load MO160 function control register high
    CAN_MOFCR160L = 0x0002;      // load MO160 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 161:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 161 :
  ///  - message object 161 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR161H = 0x0A28;      // load MO161 control register high
    CAN_MOCTR161L = 0x0000;      // load MO161 control register low

  ///  Configuration of Message Object 161 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR161H = 0x6000;       // load MO161 arbitration register high
    CAN_MOAR161L = 0x0000;       // load MO161 arbitration register low

  ///  Configuration of Message Object 161 Data:

    CAN_MODATA161HH = 0x0000;    // load MO161 Data Bytes(DB7 & DB6)
    CAN_MODATA161HL = 0x0000;    // load MO161 Data Bytes(DB5 & DB4)
    CAN_MODATA161LH = 0x0000;    // load MO161 Data Bytes(DB3 & DB2)
    CAN_MODATA161LL = 0x0000;    // load MO161 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 161 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR161H = 0x3FFF;      // load MO161 acceptance mask register high
    CAN_MOAMR161L = 0xFFFF;      // load MO161 acceptance mask register low

  ///  Configuration of Message Object 161 interrupt pointer:
  ///  - use message pending register 5 bit position 1

    CAN_MOIPR161H = 0x0000;      // load MO161 interrupt pointer register high
    CAN_MOIPR161L = 0xA100;      // load MO161 interrupt pointer register low

  ///  Configuration of Message Object 161 FIFO/Gateway pointer:
  ///  - current select pointer : MO160

    CAN_MOFGPR161H = 0x00A0;     // load MO161 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR161L = 0x0000;     // load MO161 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 161 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 160
  ///  - 0 valid data bytes

    CAN_MOFCR161H = 0x0000;      // load MO161 function control register high
    CAN_MOFCR161L = 0x0003;      // load MO161 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 162:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 162 :
  ///  - message object 162 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR162H = 0x0A28;      // load MO162 control register high
    CAN_MOCTR162L = 0x0000;      // load MO162 control register low

  ///  Configuration of Message Object 162 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR162H = 0x6000;       // load MO162 arbitration register high
    CAN_MOAR162L = 0x0000;       // load MO162 arbitration register low

  ///  Configuration of Message Object 162 Data:

    CAN_MODATA162HH = 0x0000;    // load MO162 Data Bytes(DB7 & DB6)
    CAN_MODATA162HL = 0x0000;    // load MO162 Data Bytes(DB5 & DB4)
    CAN_MODATA162LH = 0x0000;    // load MO162 Data Bytes(DB3 & DB2)
    CAN_MODATA162LL = 0x0000;    // load MO162 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 162 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR162H = 0x3FFF;      // load MO162 acceptance mask register high
    CAN_MOAMR162L = 0xFFFF;      // load MO162 acceptance mask register low

  ///  Configuration of Message Object 162 interrupt pointer:
  ///  - use message pending register 5 bit position 2

    CAN_MOIPR162H = 0x0000;      // load MO162 interrupt pointer register high
    CAN_MOIPR162L = 0xA200;      // load MO162 interrupt pointer register low

  ///  Configuration of Message Object 162 FIFO/Gateway pointer:
  ///  - current select pointer : MO160

    CAN_MOFGPR162H = 0x00A0;     // load MO162 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR162L = 0x0000;     // load MO162 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 162 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 160
  ///  - 0 valid data bytes

    CAN_MOFCR162H = 0x0000;      // load MO162 function control register high
    CAN_MOFCR162L = 0x0003;      // load MO162 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 163:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 163 :
  ///  - message object 163 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR163H = 0x0A28;      // load MO163 control register high
    CAN_MOCTR163L = 0x0000;      // load MO163 control register low

  ///  Configuration of Message Object 163 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR163H = 0x6000;       // load MO163 arbitration register high
    CAN_MOAR163L = 0x0000;       // load MO163 arbitration register low

  ///  Configuration of Message Object 163 Data:

    CAN_MODATA163HH = 0x0000;    // load MO163 Data Bytes(DB7 & DB6)
    CAN_MODATA163HL = 0x0000;    // load MO163 Data Bytes(DB5 & DB4)
    CAN_MODATA163LH = 0x0000;    // load MO163 Data Bytes(DB3 & DB2)
    CAN_MODATA163LL = 0x0000;    // load MO163 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 163 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR163H = 0x3FFF;      // load MO163 acceptance mask register high
    CAN_MOAMR163L = 0xFFFF;      // load MO163 acceptance mask register low

  ///  Configuration of Message Object 163 interrupt pointer:
  ///  - use message pending register 5 bit position 3

    CAN_MOIPR163H = 0x0000;      // load MO163 interrupt pointer register high
    CAN_MOIPR163L = 0xA300;      // load MO163 interrupt pointer register low

  ///  Configuration of Message Object 163 FIFO/Gateway pointer:
  ///  - current select pointer : MO160

    CAN_MOFGPR163H = 0x00A0;     // load MO163 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR163L = 0x0000;     // load MO163 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 163 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 160
  ///  - 0 valid data bytes

    CAN_MOFCR163H = 0x0000;      // load MO163 function control register high
    CAN_MOFCR163L = 0x0003;      // load MO163 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 164:
  ///  -----------------------------------------------------------------------

  ///  General Configuration of the Message Object 164 :
  ///  - message object 164 is valid
  ///  - message object is used as transmit object
  ///  - this message object is assigned to list 3 (node 2)

    CAN_MOCTR164H = 0x0A28;      // load MO164 control register high
    CAN_MOCTR164L = 0x0000;      // load MO164 control register low

  ///  Configuration of Message Object 164 Arbitration:
  ///  - priority class 1; transmit acceptance filtering is based on the list 
  ///    order
  ///  - extended 29-bit identifier
  ///  - identifier 29-bit:      0x00000000

    CAN_MOAR164H = 0x6000;       // load MO164 arbitration register high
    CAN_MOAR164L = 0x0000;       // load MO164 arbitration register low

  ///  Configuration of Message Object 164 Data:

    CAN_MODATA164HH = 0x0000;    // load MO164 Data Bytes(DB7 & DB6)
    CAN_MODATA164HL = 0x0000;    // load MO164 Data Bytes(DB5 & DB4)
    CAN_MODATA164LH = 0x0000;    // load MO164 Data Bytes(DB3 & DB2)
    CAN_MODATA164LL = 0x0000;    // load MO164 Data Bytes(DB1 & DB0)

  ///  Configuration of Message Object 164 acceptance mask:
  ///  - only accept receive frames with matching IDE bit
  ///  - acceptance mask 29-bit: 0x1FFFFFFF

    CAN_MOAMR164H = 0x3FFF;      // load MO164 acceptance mask register high
    CAN_MOAMR164L = 0xFFFF;      // load MO164 acceptance mask register low

  ///  Configuration of Message Object 164 interrupt pointer:
  ///  - use message pending register 5 bit position 4

    CAN_MOIPR164H = 0x0000;      // load MO164 interrupt pointer register high
    CAN_MOIPR164L = 0xA400;      // load MO164 interrupt pointer register low

  ///  Configuration of Message Object 164 FIFO/Gateway pointer:
  ///  - current select pointer : MO160

    CAN_MOFGPR164H = 0x00A0;     // load MO164 FIFO/gateway pointer register 
                                 // high
    CAN_MOFGPR164L = 0x0000;     // load MO164 FIFO/gateway pointer register 
                                 // low


  ///  Configuration of Message Object 164 Function control:
  ///  - this object is a TRANSMIT FIFO SLAVE OBJECT connected to the base 
  ///    object 160
  ///  - 0 valid data bytes

    CAN_MOFCR164H = 0x0000;      // load MO164 function control register high
    CAN_MOFCR164L = 0x0003;      // load MO164 function control register low

  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 165:
  ///  -----------------------------------------------------------------------
  ///  - message object 165 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 166:
  ///  -----------------------------------------------------------------------
  ///  - message object 166 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 167:
  ///  -----------------------------------------------------------------------
  ///  - message object 167 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 168:
  ///  -----------------------------------------------------------------------
  ///  - message object 168 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 169:
  ///  -----------------------------------------------------------------------
  ///  - message object 169 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 170:
  ///  -----------------------------------------------------------------------
  ///  - message object 170 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 171:
  ///  -----------------------------------------------------------------------
  ///  - message object 171 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 172:
  ///  -----------------------------------------------------------------------
  ///  - message object 172 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 173:
  ///  -----------------------------------------------------------------------
  ///  - message object 173 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 174:
  ///  -----------------------------------------------------------------------
  ///  - message object 174 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 175:
  ///  -----------------------------------------------------------------------
  ///  - message object 175 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 176:
  ///  -----------------------------------------------------------------------
  ///  - message object 176 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 177:
  ///  -----------------------------------------------------------------------
  ///  - message object 177 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 178:
  ///  -----------------------------------------------------------------------
  ///  - message object 178 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 179:
  ///  -----------------------------------------------------------------------
  ///  - message object 179 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 180:
  ///  -----------------------------------------------------------------------
  ///  - message object 180 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 181:
  ///  -----------------------------------------------------------------------
  ///  - message object 181 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 182:
  ///  -----------------------------------------------------------------------
  ///  - message object 182 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 183:
  ///  -----------------------------------------------------------------------
  ///  - message object 183 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 184:
  ///  -----------------------------------------------------------------------
  ///  - message object 184 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 185:
  ///  -----------------------------------------------------------------------
  ///  - message object 185 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 186:
  ///  -----------------------------------------------------------------------
  ///  - message object 186 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 187:
  ///  -----------------------------------------------------------------------
  ///  - message object 187 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 188:
  ///  -----------------------------------------------------------------------
  ///  - message object 188 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 189:
  ///  -----------------------------------------------------------------------
  ///  - message object 189 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 190:
  ///  -----------------------------------------------------------------------
  ///  - message object 190 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 191:
  ///  -----------------------------------------------------------------------
  ///  - message object 191 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 192:
  ///  -----------------------------------------------------------------------
  ///  - message object 192 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 193:
  ///  -----------------------------------------------------------------------
  ///  - message object 193 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 194:
  ///  -----------------------------------------------------------------------
  ///  - message object 194 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 195:
  ///  -----------------------------------------------------------------------
  ///  - message object 195 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 196:
  ///  -----------------------------------------------------------------------
  ///  - message object 196 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 197:
  ///  -----------------------------------------------------------------------
  ///  - message object 197 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 198:
  ///  -----------------------------------------------------------------------
  ///  - message object 198 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 199:
  ///  -----------------------------------------------------------------------
  ///  - message object 199 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 200:
  ///  -----------------------------------------------------------------------
  ///  - message object 200 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 201:
  ///  -----------------------------------------------------------------------
  ///  - message object 201 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 202:
  ///  -----------------------------------------------------------------------
  ///  - message object 202 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 203:
  ///  -----------------------------------------------------------------------
  ///  - message object 203 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 204:
  ///  -----------------------------------------------------------------------
  ///  - message object 204 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 205:
  ///  -----------------------------------------------------------------------
  ///  - message object 205 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 206:
  ///  -----------------------------------------------------------------------
  ///  - message object 206 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 207:
  ///  -----------------------------------------------------------------------
  ///  - message object 207 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 208:
  ///  -----------------------------------------------------------------------
  ///  - message object 208 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 209:
  ///  -----------------------------------------------------------------------
  ///  - message object 209 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 210:
  ///  -----------------------------------------------------------------------
  ///  - message object 210 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 211:
  ///  -----------------------------------------------------------------------
  ///  - message object 211 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 212:
  ///  -----------------------------------------------------------------------
  ///  - message object 212 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 213:
  ///  -----------------------------------------------------------------------
  ///  - message object 213 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 214:
  ///  -----------------------------------------------------------------------
  ///  - message object 214 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 215:
  ///  -----------------------------------------------------------------------
  ///  - message object 215 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 216:
  ///  -----------------------------------------------------------------------
  ///  - message object 216 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 217:
  ///  -----------------------------------------------------------------------
  ///  - message object 217 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 218:
  ///  -----------------------------------------------------------------------
  ///  - message object 218 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 219:
  ///  -----------------------------------------------------------------------
  ///  - message object 219 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 220:
  ///  -----------------------------------------------------------------------
  ///  - message object 220 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 221:
  ///  -----------------------------------------------------------------------
  ///  - message object 221 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 222:
  ///  -----------------------------------------------------------------------
  ///  - message object 222 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 223:
  ///  -----------------------------------------------------------------------
  ///  - message object 223 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 224:
  ///  -----------------------------------------------------------------------
  ///  - message object 224 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 225:
  ///  -----------------------------------------------------------------------
  ///  - message object 225 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 226:
  ///  -----------------------------------------------------------------------
  ///  - message object 226 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 227:
  ///  -----------------------------------------------------------------------
  ///  - message object 227 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 228:
  ///  -----------------------------------------------------------------------
  ///  - message object 228 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 229:
  ///  -----------------------------------------------------------------------
  ///  - message object 229 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 230:
  ///  -----------------------------------------------------------------------
  ///  - message object 230 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 231:
  ///  -----------------------------------------------------------------------
  ///  - message object 231 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 232:
  ///  -----------------------------------------------------------------------
  ///  - message object 232 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 233:
  ///  -----------------------------------------------------------------------
  ///  - message object 233 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 234:
  ///  -----------------------------------------------------------------------
  ///  - message object 234 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 235:
  ///  -----------------------------------------------------------------------
  ///  - message object 235 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 236:
  ///  -----------------------------------------------------------------------
  ///  - message object 236 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 237:
  ///  -----------------------------------------------------------------------
  ///  - message object 237 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 238:
  ///  -----------------------------------------------------------------------
  ///  - message object 238 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 239:
  ///  -----------------------------------------------------------------------
  ///  - message object 239 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 240:
  ///  -----------------------------------------------------------------------
  ///  - message object 240 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 241:
  ///  -----------------------------------------------------------------------
  ///  - message object 241 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 242:
  ///  -----------------------------------------------------------------------
  ///  - message object 242 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 243:
  ///  -----------------------------------------------------------------------
  ///  - message object 243 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 244:
  ///  -----------------------------------------------------------------------
  ///  - message object 244 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 245:
  ///  -----------------------------------------------------------------------
  ///  - message object 245 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 246:
  ///  -----------------------------------------------------------------------
  ///  - message object 246 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 247:
  ///  -----------------------------------------------------------------------
  ///  - message object 247 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 248:
  ///  -----------------------------------------------------------------------
  ///  - message object 248 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 249:
  ///  -----------------------------------------------------------------------
  ///  - message object 249 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 250:
  ///  -----------------------------------------------------------------------
  ///  - message object 250 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 251:
  ///  -----------------------------------------------------------------------
  ///  - message object 251 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 252:
  ///  -----------------------------------------------------------------------
  ///  - message object 252 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 253:
  ///  -----------------------------------------------------------------------
  ///  - message object 253 is not valid
  ///  -----------------------------------------------------------------------
  ///  Configuration of Message Object 254:
  ///  -----------------------------------------------------------------------
  ///  - message object 254 is not valid

  ///  -----------------------------------------------------------------------
  ///  Configuration of Service Request Nodes 0 - 15:
  ///  -----------------------------------------------------------------------
  ///  SRN0 service request node configuration:
  ///  - SRN0 interrupt priority level (ILVL) = 11
  ///  - SRN0 interrupt group level (GLVL) = 2
  ///  - SRN0 group priority extension (GPX) = 0

  CAN_0IC        =  0x006E;     

  ///  SRN1 service request node configuration:
  ///  - SRN1 interrupt priority level (ILVL) = 10
  ///  - SRN1 interrupt group level (GLVL) = 2
  ///  - SRN1 group priority extension (GPX) = 0

  CAN_1IC        =  0x006A;     


  ///  -----------------------------------------------------------------------
  ///  Initialization of the FIFO Pointer:
  ///  -----------------------------------------------------------------------

  for (i = 0; i < 165; i++)
  {
    ubFIFOWritePtr[i] = (ubyte)(CAN_HWOBJ[i].uwMOFGPRL & 0x00FF);
    ubFIFOReadPtr[i]  = (ubyte)(CAN_HWOBJ[i].uwMOFGPRL & 0x00FF);
  }

  //   -----------------------------------------------------------------------
  //   Start the CAN Nodes:
  //   -----------------------------------------------------------------------

  ///  - ------------- CAN_NCR0 ----------------------------------------------

    CAN_NCR0 &= ~ (uword) 0x0041; // reset INIT and CCE
  ///  - ------------- CAN_NCR1 ----------------------------------------------

    CAN_NCR1 &= ~ (uword) 0x0041; // reset INIT and CCE
  ///  - ------------- CAN_NCR2 ----------------------------------------------

    CAN_NCR2 &= ~ (uword) 0x0041; // reset INIT and CCE



  // USER CODE BEGIN (Init,3)

  // USER CODE END

} //  End of function CAN_vInit

//****************************************************************************
// @Function      void CAN_vGetMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function fills the forwarded SW message object with 
//                the content of the chosen HW message object.
//                
//                For Receive Message object use function CAN_vReleaseObj, to 
//                release the message object. 
//                
//                The structure of the SW message object is defined in the 
//                header file CAN.h (see stCAN_SWObj).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be read (0-254)
// @Parameters    *pstObj: 
//                Pointer on a message object to be filled by this function
//
//----------------------------------------------------------------------------
// @Date          2018/7/17
//
//****************************************************************************

// USER CODE BEGIN (GetMsgObj,1)

// USER CODE END

void CAN_vGetMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj)
{
  ubyte i;

  //----- get DLC -------------------------------------------------------
  pstObj->ubMOCfg = (ubyte)((CAN_HWOBJ[ubObjNr].uwMOFCRH & 0x0F00) >> 8); //MOFCRnH[11-8] DLC

  //----- get MODATA ----------------------------------------------------
  for(i = 0; i < pstObj->ubMOCfg; i++)
  {
    pstObj->ubData[i] = CAN_HWOBJ[ubObjNr].ubData[i];
  }

  //----- get DIR -------------------------------------------------------
    pstObj->ubMOCfg |= (ubyte)((CAN_HWOBJ[ubObjNr].uwMOCTRL & 0x0800) >> 7);  // set DIR if transmit object

  //----- get Identifier ------------------------------------------------
  if(CAN_HWOBJ[ubObjNr].uwMOARH & 0x2000)    // if extended identifier
  {
    //----- get Extended Identifier -------------------------------------
    pstObj->ulID = (((ulong)(CAN_HWOBJ[ubObjNr].uwMOARH & 0x1FFF))<<16) + CAN_HWOBJ[ubObjNr].uwMOARL;

    pstObj->ubMOCfg = pstObj->ubMOCfg | 0x20;  // set IDE
  }
  else                                       // standard identifier
  {
    //----- get Standard Identifier -------------------------------------
    pstObj->ulID = (CAN_HWOBJ[ubObjNr].uwMOARH & 0x1FFF) >> 2;
  }

  //----- get Acceptance Mask -----------------------------------------
  if(((CAN_HWOBJ[ubObjNr].uwMOARH & 0x2000) == 0) && (CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x2000))    // if IDE = 0 & MIDE = 1
  {
    pstObj->ulMask = (CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x1FFF) >> 2;
  }
  else
  {
    pstObj->ulMask = (((ulong)(CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x1FFF))<<16) + CAN_HWOBJ[ubObjNr].uwMOAMRL;
  }

  //----- get Acceptance Mask bit ---------------------------------------
  pstObj->ubMOCfg |= (ubyte)((CAN_HWOBJ[ubObjNr].uwMOAMRH & 0x2000) >> 7); // set MIDE

  //----- get Frame Counter Value ---------------------------------------
  pstObj->uwCounter = CAN_HWOBJ[ubObjNr].uwMOIPRH;

} //  End of function CAN_vGetMsgObj

//****************************************************************************
// @Function      void CAN_vTransmit(ubyte ubObjNr) 
//
//----------------------------------------------------------------------------
// @Description   This function triggers the CAN controller to send the 
//                selected message.
//                If the selected message object is a TRANSMIT OBJECT then 
//                this function triggers the sending of a data frame. If 
//                however the selected message object is a RECEIVE OBJECT 
//                this function triggers the sending of a remote frame.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object (0-254)
//
//----------------------------------------------------------------------------
// @Date          2018/7/17
//
//****************************************************************************

// USER CODE BEGIN (Transmit,1)

// USER CODE END

void CAN_vTransmit(ubyte ubObjNr)
{

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0720;  // set TXRQ,TXEN0,TXEN1,MSGVAL

} //  End of function CAN_vTransmit

//****************************************************************************
// @Function      void CAN_vConfigMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function sets up the message objects. This includes 
//                the 8 data bytes, the identifier (11- or 29-bit), the 
//                acceptance mask (11- or 29-bit), the data number (0-8 
//                bytes), the DIR-bit (transmit or receive object), the 
//                IDE-bit (standard or extended  identifier), the MIDE-bit 
//                (accepts reception of both frames or matching IDE-bit 
//                frame) and  the frame counter value. 
//                The message is not sent; for this the function 
//                CAN_vTransmit must be called.
//                
//                The structure of the SW message object is defined in the 
//                header file CAN.h (see stCAN_SWObj).
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be configured (0-254)
// @Parameters    *pstObj: 
//                Pointer on a message object
//
//----------------------------------------------------------------------------
// @Date          2018/7/17
//
//****************************************************************************

// USER CODE BEGIN (ConfigMsgObj,1)

// USER CODE END

void CAN_vConfigMsgObj(ubyte ubObjNr, stCAN_SWObj *pstObj)
{

  ubyte i;

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0000;
  CAN_HWOBJ[ubObjNr].uwMOCTRL = 0x0020;        // reset MSGVAL

  //----- Configure identifier ---------------------------------------
  CAN_HWOBJ[ubObjNr].uwMOARH  &= ~(uword)0x3FFF;

  if(pstObj->ubMOCfg & 0x20)                   // if extended identifier
  {
    //----- Configure extended identifier(29bit) ----------------------
    CAN_HWOBJ[ubObjNr].uwMOARH  |= (uword)(0x2000 | ((pstObj->ulID >> 16) & 0x1FFF));
    CAN_HWOBJ[ubObjNr].uwMOARL   = (uword)(pstObj->ulID & 0xFFFF);
  }
  else                                         // standard identifier
  {
    //----- Configure standard identifier(11bit) ----------------------
    CAN_HWOBJ[ubObjNr].uwMOARH |= (uword)((pstObj->ulID & 0x07FF) << 2);
    CAN_HWOBJ[ubObjNr].uwMOARL = 0x0000;
  }

  //----- Configure acceptance mask -----------------------------------
  if((pstObj->ubMOCfg & 0x60) == 0x40) // if (IDE = 0 & MIDE = 1)
  {

    CAN_HWOBJ[ubObjNr].uwMOAMRH = (uword)((pstObj->ulMask & 0x07FF) << 2);
    CAN_HWOBJ[ubObjNr].uwMOAMRL = 0x0000;
  }
  else
  {

    CAN_HWOBJ[ubObjNr].uwMOAMRH = (uword)((pstObj->ulMask >> 16) & 0x1FFF);
    CAN_HWOBJ[ubObjNr].uwMOAMRL = (uword)(pstObj->ulMask & 0xFFFF);
  }

  //----- Configure Acceptance Mask -----------------------------------
  CAN_HWOBJ[ubObjNr].uwMOAMRH |= (((uword)(pstObj->ubMOCfg & 0x40)) << 7);

  //----- Configure Frame Counter -------------------------------------
  CAN_HWOBJ[ubObjNr].uwMOIPRH = pstObj->uwCounter;

  //----- Configure DLC & Data Bytes ----------------------------------
  CAN_HWOBJ[ubObjNr].uwMOFCRH &= (~(uword)0x0F00);
  CAN_HWOBJ[ubObjNr].uwMOFCRH |= (((uword)(pstObj->ubMOCfg & 0x0F)) << 8);

  if(pstObj->ubMOCfg & 0x10)                 // if transmit direction
  {
    //----- Configure message object data bytes -----------------------
    for(i = 0; i < (pstObj->ubMOCfg & 0x0F); i++)
    {
      CAN_HWOBJ[ubObjNr].ubData[i] = pstObj->ubData[i];
    }

    CAN_HWOBJ[ubObjNr].uwMOCTRH  = 0x0E28;  // set DIR, TXEN1, TXEN0, MSGVAL
                                            // and NEWDAT
  }
  else                                      // receive direction
  {
    CAN_HWOBJ[ubObjNr].uwMOCTRH  = 0x0020;  // set MSGVAL
    CAN_HWOBJ[ubObjNr].uwMOCTRL  = 0x0800;  // reset DIR
  }

  CAN_HWOBJ[ubObjNr].uwMOCTRL  = 0x0040;  // reset RTSEL

} //  End of function CAN_vConfigMsgObj

//****************************************************************************
// @Function      void CAN_vLoadData(ubyte ubObjNr, ubyte *ubpubData) 
//
//----------------------------------------------------------------------------
// @Description   If a hardware TRANSMIT OBJECT has to be loaded with data 
//                but not with a new identifier, this function may be used 
//                instead of the function CAN_vConfigMsgObj. The message 
//                object should be accessed by calling the function 
//                CAN_ubRequestMsgObj before calling this function. This 
//                prevents the CAN controller from working with invalid data.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the message object to be configured (0-254)
// @Parameters    *ubpubData: 
//                Pointer on a data buffer
//
//----------------------------------------------------------------------------
// @Date          2018/7/17
//
//****************************************************************************

// USER CODE BEGIN (LoadData,1)

// USER CODE END

void CAN_vLoadData(ubyte ubObjNr, ubyte *ubpubData)
{
  ubyte i;

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0008;       // set NEWDAT

  for(i = 0; i < (CAN_HWOBJ[ubObjNr].uwMOFCRH & 0x0F00) >> 8; i++)
  {
    CAN_HWOBJ[ubObjNr].ubData[i] = *(ubpubData++); //load MODATA
  }

  CAN_HWOBJ[ubObjNr].uwMOCTRH = 0x0020;       // set MSGVAL
  CAN_HWOBJ[ubObjNr].uwMOCTRL = 0x0040;       // reset RTSEL

} //  End of function CAN_vLoadData

//****************************************************************************
// @Function      ubyte CAN_ubWriteFIFO(ubyte ubObjNr, stCAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function sets up the next free TRANSMIT message object 
//                which is part of a FIFO. This includes the 8 data bytes, 
//                the identifier (11- or 29-bit) and the data number (0-8 
//                bytes). The direction bit (DIR) and the EDE-bit can not be 
//                changed. The acceptance mask register and the Frame Counter 
//                remains unchanged. This function checks whether the choosen 
//                message object is still executing a transmit request, or if 
//                the object can be accessed exclusively. 
//                The structure of the SW message object is defined in the 
//                header file CAN.h (see CAN_SWObj).
//                Note: 
//                This function can only used for TRANSMIT objects which are 
//                configured for FIFO base functionality. 
//
//----------------------------------------------------------------------------
// @Returnvalue   0: message object is busy (a transfer is active); 1: the 
//                message object was configured and the transmite is 
//                requested; 2: this is not a FIFO base object
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the FIFO base object
// @Parameters    *pstObj: 
//                Pointer on a message object
//
//----------------------------------------------------------------------------
// @Date          2018/7/17
//
//****************************************************************************

// USER CODE BEGIN (WriteFIFO,1)

// USER CODE END

ubyte CAN_ubWriteFIFO(ubyte ubObjNr, stCAN_SWObj *pstObj)
{
  ubyte i,j;
  ubyte ubReturn;

  ubReturn = 2;

  if((CAN_HWOBJ[ubObjNr].uwMOFCRL & 0x000F) == 0x0002)    // if transmit FIFO base object 
  {
    j = ubFIFOWritePtr[ubObjNr];

    ubReturn = 0;
    if((CAN_HWOBJ[j].uwMOCTRL & 0x0100) == 0x0000)        // if reset TXRQ 
    {
      if(j == ((CAN_HWOBJ[ubObjNr].uwMOFGPRL & 0xFF00) >> 8))      // last MO in a list
      {
        // WritePtr = BOT of the base object
        ubFIFOWritePtr[ubObjNr] = (ubyte)(CAN_HWOBJ[ubObjNr].uwMOFGPRL & 0x00FF);
      }
      else
      {
        // WritePtr = PNEXT of the current selected slave
        ubFIFOWritePtr[ubObjNr] = (ubyte)((CAN_HWOBJ[j].uwMOCTRH & 0xFF00) >> 8);
      }

      CAN_HWOBJ[j].uwMOCTRL = 0x0008;                     // reset NEWDAT 

      CAN_HWOBJ[j].uwMOARH  &= ~(uword)0x1FFF;

      if(CAN_HWOBJ[j].uwMOARH & 0x2000)                   // extended identifier
      {
        CAN_HWOBJ[j].uwMOARH |= (uword)((pstObj->ulID >> 16) & 0x1FFF);
        CAN_HWOBJ[j].uwMOARL = (uword)(pstObj->ulID & 0xFFFF);
      }
      else                                                // if standard identifier
      {
        CAN_HWOBJ[j].uwMOARH |= (uword)((pstObj->ulID & 0x07FF) << 2);
        CAN_HWOBJ[j].uwMOARL = 0x0000;
      }

      CAN_HWOBJ[j].uwMOFCRH &= ~(uword)0x0F00;
      CAN_HWOBJ[j].uwMOFCRH |= (((uword)(pstObj->ubMOCfg & 0x0F)) << 8);

      for(i = 0; i < (pstObj->ubMOCfg & 0x0F); i++)
      {
        CAN_HWOBJ[j].ubData[i] = pstObj->ubData[i];
      }

      CAN_HWOBJ[j].uwMOCTRH  = 0x0128;              // set TXRQ, NEWDAT, MSGVAL 

      ubReturn = 1;
    }
  }
  return(ubReturn);

} //  End of function CAN_ubWriteFIFO


//****************************************************************************
// @Function      ubyte CAN_ubReadFIFO(ubyte ubObjNr, stCAN_SWObj *pstObj) 
//
//----------------------------------------------------------------------------
// @Description   This function reads the next RECEIVE message object which 
//                is part of a FIFO. It checks whether the selected RECEIVE 
//                OBJECT has received a new message. If so the forwarded SW 
//                message object is filled with the content of the HW message 
//                object and the functions returns the value "1". The 
//                structure of the SW message object is defined in the header 
//                file CAN.h (see CAN_SWObj).
//                Note: 
//                This function can only used for RECEIVE objects which are 
//                configured for FIFO base functionality. 
//                Be sure that no interrupt is enabled for the FIFO objects. 
//
//----------------------------------------------------------------------------
// @Returnvalue   0: the message object has not received a new message; 1: 
//                the message object has received a new message; 2: this is 
//                not a FIFO base object; 3: a previous message was lost; 4: 
//                the received message is corrupted
//
//----------------------------------------------------------------------------
// @Parameters    ubObjNr: 
//                Number of the FIFO base object
// @Parameters    *pstObj: 
//                Pointer on a message object to be filled by this function
//
//----------------------------------------------------------------------------
// @Date          2018/7/17
//
//****************************************************************************

// USER CODE BEGIN (ReadFIFO,1)

// USER CODE END

ubyte CAN_ubReadFIFO(ubyte ubObjNr, stCAN_SWObj *pstObj)
{
  ubyte i,j;
  ubyte ubReturn;

  ubReturn = 2;

  if((CAN_HWOBJ[ubObjNr].uwMOFCRL & 0x000F) == 0x0001)    // if receive FIFO base object 
  {
    j = ubFIFOReadPtr[ubObjNr];

    ubReturn = 0;
    if(CAN_HWOBJ[j].uwMOCTRL & 0x0008)                    // if NEWDAT 
    {
      CAN_HWOBJ[j].uwMOCTRL = 0x0008;                     // clear NEWDAT

      if(j == ((CAN_HWOBJ[ubObjNr].uwMOFGPRL & 0xFF00) >> 8))      // last MO in a list
      {
        // ReadPtr = BOT of the base object
        ubFIFOReadPtr[ubObjNr] = (ubyte)(CAN_HWOBJ[ubObjNr].uwMOFGPRL & 0x00FF);
      }
      else
      {
        // ReadPtr = PNEXT of the current selected slave
        ubFIFOReadPtr[ubObjNr] = (ubyte)((CAN_HWOBJ[j].uwMOCTRH & 0xFF00) >> 8);
      }

      // check if the previous message was lost 
      if(CAN_HWOBJ[j].uwMOCTRL & 0x0010)                  // if set MSGLST 
      {
        CAN_HWOBJ[j].uwMOCTRL = 0x0010;                   // reset MSGLST 
        return(3);
      }

      pstObj->ubMOCfg = (ubyte)((CAN_HWOBJ[j].uwMOFCRH & 0x0F00) >> 8); //MOFCRnH[11-8] DLC

      for(i = 0; i < pstObj->ubMOCfg; i++)
      {
        pstObj->ubData[i] = CAN_HWOBJ[j].ubData[i];
      }

      pstObj->ubMOCfg |= (ubyte)((CAN_HWOBJ[j].uwMOCTRL & 0x0800) >> 7);// set DIR if transmit object

      if(CAN_HWOBJ[j].uwMOARH & 0x2000)             // if extended identifier
      {
        pstObj->ulID = (((ulong)(CAN_HWOBJ[j].uwMOARH & 0x1FFF))<<16) + CAN_HWOBJ[j].uwMOARL;

        pstObj->ubMOCfg = pstObj->ubMOCfg | 0x20;         // set IDE
      }
      else                                                // standard identifier
      {
        pstObj->ulID = (CAN_HWOBJ[j].uwMOARH & 0x1FFF) >> 2;
      }

      pstObj->uwCounter = CAN_HWOBJ[j].uwMOIPRH;

      // check if the message was corrupted 
      if(CAN_HWOBJ[j].uwMOCTRL & 0x0008)                  // if NEWDAT 
      {
        CAN_HWOBJ[j].uwMOCTRL = 0x0008;                   // clear NEWDAT
        return(4);
      }
      ubReturn = 1;
    }
  }
  return(ubReturn);

} //  End of function CAN_ubReadFIFO




//****************************************************************************
// @Macro         CAN_viSRN0() 
//
//----------------------------------------------------------------------------
// @Description   
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2018/7/17
//
//****************************************************************************

// USER CODE BEGIN (SRN0,1)

// USER CODE END

void CAN_viSRN0(void) interrupt CAN_SRN0INT
{

  uword uwSRN0ObjHandler;

  // USER CODE BEGIN (SRN0,2)

  // USER CODE END

  CAN_MSIMASKH = 0x0000;          // set message index mask register
  CAN_MSIMASKL = 0x0001;

  while (CAN_MSID0 != 0x0020)
  {
    switch(CAN_MSID0){

    case 0: // message object 0 interrupt 
    
      uwSRN0ObjHandler = CAN_HWOBJ[0].uwMOCTRL;

      if(uwSRN0ObjHandler & MOSTAT_RXPND)          // if message object 0 receive interrupt
      {
            // USER CODE BEGIN (SRN0_OBJ0,1)

            // USER CODE END

        if(uwSRN0ObjHandler & MOSTAT_NEWDAT)       // if NEWDAT is set
        {
            // USER CODE BEGIN (SRN0_OBJ0,2)
            refreshBMSinfFromVCU();
            // USER CODE END

          if (uwSRN0ObjHandler & MOSTAT_MSGLST)    // if MSGLST is set
          {
            // Indicates that the CAN controller has stored a new 
            // message into this object, while NEWDAT was still set,
            // ie. the previously stored message is lost.

            // USER CODE BEGIN (SRN0_OBJ0,3)
						refreshBMSinfFromVCU();
            // USER CODE END

          }
          else
          {
            // The CAN controller has stored a new message into this object.

            // USER CODE BEGIN (SRN0_OBJ0,4)

            // USER CODE END
          }

        }

        CAN_HWOBJ[0].uwMOCTRL = MOSTAT_RST_MNR;            // reset MSGLST + NEWDAT + RXPND

      }  // End of RXPND0


      CAN_MSPND0H = ~(uword) 0x0000; // reset PND bit
      CAN_MSPND0L = ~(uword) 0x0001;

      // USER CODE BEGIN (SRN0_OBJ0,7)

      // USER CODE END

      break;

    default:

      // USER CODE BEGIN (SRN0,3)

      // USER CODE END

      break;

    }  // end switch 

    // USER CODE BEGIN (SRN0,7)

    // USER CODE END

  }  // end of while CAN_MSID


  // USER CODE BEGIN (SRN0,15)

  // USER CODE END

} //  End of function CAN_viSRN0


//****************************************************************************
// @Macro         CAN_viSRN1() 
//
//----------------------------------------------------------------------------
// @Description   
//
//----------------------------------------------------------------------------
// @Returnvalue   
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2018/7/17
//
//****************************************************************************

// USER CODE BEGIN (SRN1,1)

// USER CODE END

void CAN_viSRN1(void) interrupt CAN_SRN1INT
{


  // USER CODE BEGIN (SRN1,2)

  // USER CODE END


  // USER CODE BEGIN (SRN1,15)
  RefreshCellInformationWithCANFrameData();
  // USER CODE END

} //  End of function CAN_viSRN1



// USER CODE BEGIN (CAN_General,10)

// USER CODE END

