/*
 * Function definitions for routines that dump low-level SAMD51 hardware components.
 */

#ifndef SAMD51_DUMPSTER_H
#define SAMD51_DUMPSTER_H

#ifndef __SAMD51__
// #pragma GCC error "This library only works for Atmel SAMD51 processors"
#endif

#include <Arduino.h>

class SAMD51_Dumpster {
public:
  SAMD51_Dumpster();

  void begin(int verbose);
  void dumpArray(uint32_t val, int cnt);
  
  void dumpPort(const char* msg);
  void dumpPortGroup(int n);
  
  void dumpGCLK(const char* msg);
  void dumpGCLKGenerators();
  void dumpGCLKUsers();
  void dumpGclkGenctrl(int n);
  void dumpGclkPchctrl(int n);
  
  void dumpMCLK(const char* msg);
  void dumpMclkAHB();
  void dumpMclkAPBA();  // 0..3???
  void dumpMclkAPBB();
  void dumpMclkAPBC();
  void dumpMclkAPBD();
  
  void dumpSERCOM(const char* msg);
  void dumpSercomInstance(int n);
  void dumpSercomUsart(SercomUsart* scu);
  void dumpSercomSpi(SercomSpi* scs);
  void dumpSercomI2cs(SercomI2cs* sci);
  void dumpSercomI2cm(SercomI2cm* sci);
  
  void dumpTC(const char* msg);
  void dumpTcInstance(int n);

  void dumpTCC(const char* msg);
  void dumpTccInstance(int n);
#if REV_TCC == 0x310
  void dumpTccInstance310(Tcc* tcc, int ccNum);
#endif

  void dumpEVSYS(const char* msg);
  void dumpEvChannel(int chNum);
  void dumpEvUser(int userNum);
  
  void dumpDMAC(const char* msg);
  void dumpDmacChannel(int chNum);
  void dumpDmacDesc(DmacDescriptor* desc);
  
  void dumpADC(const char* msg);
  void dumpAdcInstance(int n);

protected:
  int verbose;

  const char* gclkSrcName[9] = {"XOSC0", "XOSC1", "IN", "GCLK1", "OSC_32K_UL",
                                "OSC_32K", "DFLL_48M", "DPLL0", "DPLL1"};
  const char* gclkUserName[48] = {"DFLL48_in", "FDPLL0_ref", "FDPLL1_ref", "32kHz",
                                  "EIC",       "FREQM_msr",  "FREQM_ref",  "SERCOM0",
				  "SERCOM1",   "TC0/1",      "USB",        "EVSYS0",
				  "EVSYS1",    "EVSYS2",     "EVSYS3",     "EVSYS4",
				  "EVSYS5",    "EVSYS6",     "EVSYS7",     "EVSYS8",
				  "EVSYS9",    "EVSYS10",    "EVSYS11",    "SERCOM2",
				  "SERCOM3",   "TCC0/1",     "TC2/3",      "CAN0",
				  "CAN1",      "TCC2/3",     "TC4/5",      "PDEC",
				  "AC",        "CCL",        "SERCOM4",    "SERCOM5",
				  "SERCOM6",   "SERCOM7",    "TCC4",       "TC6/7",
				  "ADC0",      "ADC1",       "DAC",        "I2S_a",
				  "I2S_b",     "SDHC0",      "SDHC1",      "CM4_trace"
				};
  const int tccCcNum[5] = {TCC0_CC_NUM, TCC1_CC_NUM, TCC2_CC_NUM, TCC3_CC_NUM, TCC4_CC_NUM};
  const char* tccWaveGenNames[8] = {"NFRQ", "MFRQ", "NPWM", "Reserved",
                                   "DSCRITICAL", "DSBOTTOM", "DSBOTH", "DSTOP"};
  const int tcPrescalars[8] = {1, 2, 4, 8, 16, 64, 256, 1024};
  const char* tcWaves[4] = {"NFRQ", "MFRQ", "NPWM", "MPWM"};

  const char* evGenNames[EVSYS_GENERATORS] = {
    "NONE", "OSCCTRL_XOSC_FAIL_0", "OSCCTRL_XOSC_FAIL_1", "OSC32KCTRL_XOSC32K_FAIL", 
    "RTC_PER_0", "RTC_PER_1", "RTC_PER_2", "RTC_PER_3", "RTC_PER_4", "RTC_PER_5", "RTC_PER_6", 
    "RTC_PER_7", "RTC_CMP_0", "RTC_CMP_1", "RTC_CMP_2", "RTC_CMP_3", "RTC_TAMPER", "RTC_OVF", 
    "EIC_EXTINT_0", "EIC_EXTINT_1", "EIC_EXTINT_2", "EIC_EXTINT_3", "EIC_EXTINT_4", "EIC_EXTINT_5", 
    "EIC_EXTINT_6", "EIC_EXTINT_7", "EIC_EXTINT_8", "EIC_EXTINT_9", "EIC_EXTINT_10", 
    "EIC_EXTINT_11", "EIC_EXTINT_12", "EIC_EXTINT_13", "EIC_EXTINT_14", "EIC_EXTINT_15", 
    "DMAC_CH_0", "DMAC_CH_1", "DMAC_CH_2", "DMAC_CH_3", "PAC_ACCERR", "TAL_BRK", "TAL_IRQMON_0", 
    "TCC0_OVF", "TCC0_TRG", "TCC0_CNT", "TCC0_MCX_0", "TCC0_MCX_1", "TCC0_MCX_2", "TCC0_MCX_3", 
    "TCC0_MCX_4", "TCC0_MCX_5", 
    "TCC1_OVF", "TCC1_TRG", "TCC1_CNT", "TCC1_MCX_0", "TCC1_MCX_1", "TCC1_MCX_2", "TCC1_MCX_3", 
    "TCC2_OVF", "TCC2_TRG", "TCC2_CNT", "TCC2_MCX_0", "TCC2_MCX_1", "TCC2_MCX_2", 
    "TCC3_OVF", "TCC3_TRG", "TCC3_CNT", "TCC3_MCX_0", "TCC3_MCX_1", 
    "TCC4_OVF", "TCC4_TRG", "TCC4_CNT", "TCC4_MCX_0", "TCC4_MCX_1", 
    "TC0_OVF", "TC0_MCX_0", "TC0_MCX_1", "TC1_OVF", "TC1_MCX_0", "TC1_MCX_1", 
    "TC2_OVF", "TC2_MCX_0", "TC2_MCX_1", "TC3_OVF", "TC3_MCX_0", "TC3_MCX_1", 
    "TC4_OVF", "TC4_MCX_0", "TC4_MCX_1", "TC5_OVF", "TC5_MCX_0", "TC5_MCX_1", 
    "TC6_OVF", "TC6_MCX_0", "TC6_MCX_1", "TC7_OVF", "TC7_MCX_0", "TC7_MCX_1", 
    "PDEC_OVF", "PDEC_ERR", "PDEC_DIR", "PDEC_VLC", "PDEC_MCX_0", "PDEC_MCX_1", 
    "ADC0_RESRDY", "ADC0_WINMON", "ADC1_RESRDY", "ADC1_WINMON", 
    "AC_COMP_0", "AC_COMP_1", "AC_WIN_0",
    "DAC_EMPTY_0", "DAC_EMPTY_1", "DAC_RESRDY_0", "DAC_RESRDY_1", 
    "TRNG_READY", "CCL_LUTOUT_0", "CCL_LUTOUT_1", "CCL_LUTOUT_2", "CCL_LUTOUT_3"
  };
  const char* evUserNames[EVSYS_USERS] = {
    "RTC_TAMPER", "PORT_EV_0", "PORT_EV_1", "PORT_EV_2", "PORT_EV_3",
    "DMAC_CH_0", "DMAC_CH_1", "DMAC_CH_2", "DMAC_CH_3", "DMAC_CH_4",
    "DMAC_CH_5", "DMAC_CH_6", "DMAC_CH_7", 
    "TAL_BRK", "CM4_TRACE_START", "CM4_TRACE_STOP", "CM4_TRACE_TRIG", 
    "TCC0_EV_0", "TCC0_EV_1", "TCC0_MC_0", "TCC0_MC_1", "TCC0_MC_2", "TCC0_MC_3", "TCC0_MC_4",
    "TCC0_MC_5", 
    "TCC1_EV_0", "TCC1_EV_1", "TCC1_MC_0", "TCC1_MC_1", "TCC1_MC_2", "TCC1_MC_3", 
    "TCC2_EV_0", "TCC2_EV_1", "TCC2_MC_0", "TCC2_MC_1", "TCC2_MC_2", 
    "TCC3_EV_0", "TCC3_EV_1", "TCC3_MC_0", "TCC3_MC_1", 
    "TCC4_EV_0", "TCC4_EV_1", "TCC4_MC_0", "TCC4_MC_1", 
    "TC0_EVU", "TC1_EVU", "TC2_EVU", "TC3_EVU", "TC4_EVU", "TC5_EVU", "TC6_EVU", "TC7_EVU", 
    "PDEC_EVU_0", "PDEC_EVU_1", "PDEC_EVU_2", "ADC0_START", "ADC0_SYNC", "ADC1_START", "ADC1_SYNC", 
    "AC_SOC_0", "AC_SOC_1", "DAC_START_0", "DAC_START_1", 
    "CCL_LUTIN_0", "CCL_LUTIN_1", "CCL_LUTIN_2", "CCL_LUTIN_3", 
  };
  const char* evPathNames[4] = {"sync", "resync", "async", "invalid"};
  const int beatSizes[4] = {1, 2, 4, 0};
  const char* crcPolyNames[4] = {"CRC-16 (CRC-CCITT)", "CRC32 (IEEE 802.3)", "n/a", "n/a"};
  const char* crcSrcNames[64] = {"NOACT", "IO", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                 "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
				 "CH0",  "CH1",  "CH2",  "CH3",  "CH4",  "CH5",  "CH6",  "CH7",
				 "CH8",  "CH9",  "CH10", "CH11", "CH12", "CH13", "CH14", "CH15",
				 "CH16", "CH17", "CH18", "CH19", "CH20", "CH21", "CH22", "CH23",
				 "CH24", "CH25", "CH26", "CH27", "CH28", "CH29", "CH30", "CH31"};
  const char* crcModeNames[4] = {"DEFAULT", "reserved", "CRCMON", "CRCGEN"};
  const char* priQosNames[4] = {"REGULAR", "LOW", "MEDIUM", "CRITICAL"};
  const char* trigSrcNames[85] = {"DISABLE", "RTC_TIMESTAMP", "DSU_DCC0", "DSU_DCC1",          // 0
                                  "SERCOM0_RX", "SERCOM0_TX", "SERCOM1_RX", "SERCOM1_TX",      // 4
                                  "SERCOM2_RX", "SERCOM2_TX", "SERCOM3_RX", "SERCOM3_TX",      // 8
                                  "SERCOM4_RX", "SERCOM4_TX", "SERCOM5_RX", "SERCOM5_TX",      // 12
                                  "SERCOM6_RX", "SERCOM6_TX", "SERCOM7_RX", "SERCOM7_TX",      // 16
				  "CAN0_DBG", "CAN1_DBG",                                      // 20
				  "TCC0_OVF", "TCC0_MC0", "TCC0_MC1", "TCC0_MC2", "TCC0_MC3",  // 22
				  "TCC0_MC4", "TCC0_MC5",                                      // 27
				  "TCC1_OVF", "TCC1_MC0", "TCC1_MC1", "TCC1_MC2", "TCC1_MC3",  // 29
				  "TCC2_OVF", "TCC2_MC0", "TCC2_MC1", "TCC2_MC2",              // 34
				  "TCC3_OVF", "TCC3_MC0", "TCC3_MC1",                          // 38
				  "TCC4_OVF", "TCC4_MC0", "TCC4_MC1",                          // 41
				  "TC0_OVF", "TC0_MC0", "TC0_MC1",                             // 44
				  "TC1_OVF", "TC1_MC0", "TC1_MC1",                             // 47
				  "TC2_OVF", "TC2_MC0", "TC2_MC1",                             // 50
				  "TC3_OVF", "TC3_MC0", "TC3_MC1",                             // 53
				  "TC4_OVF", "TC4_MC0", "TC4_MC1",                             // 56
				  "TC5_OVF", "TC5_MC0", "TC5_MC1",                             // 59
				  "TC6_OVF", "TC6_MC0", "TC6_MC1",                             // 62
				  "TC7_OVF", "TC7_MC0", "TC7_MC1",                             // 65
				  "ADC0_RESRDY", "ADC0_SEQ", "ADC1_RESRDY", "ADC1_SEQ",        // 68
				  "DAC0_EMPTY", "DAC1_EMPTY", "DAC0_RESRDY", "DAC1_RESRDY",    // 72
				  "I2S0_RX", "I2S1_RX", "I2S0_TX", "I2S1_TX",                  // 76
				  "PCC_RX", "AES_WR", "AES_RD", "QSPI_RX", "QSPI_TX"};         // 80
  const char* trigActNames[4] = {"BLOCK", "reserved", "BURST", "TRANSACTION"};
  const int thresholdSizes[4] = {1, 2, 4, 8};
  const char* dmacCmdNames[4] = {"NOACT", "SUSPEND", "RESUME", "n/a"};
  const char* dmacChEvActNames[8] = {"NOACT", "TRIG", "CTRIG", "CBLOCK",
                                     "SUSPEND", "RESUME", "SSKIP", "INCPRI"};
  const char* dmacChEvOutModeNames[4] = {"DEFAULT", "TRIGACT", "n/a_2", "n/a_3"};
  const char* dmacDescEvoSelNames[4] = {"DISABLE", "BLOCK", "reserved", "BEAT"};
  const char* dmacDescBlkActNames[4] = {"NOACT", "INT", "SUSPEND", "BOTH"};
  const char* dmacStepSelNames[2] = {"DST", "SRC"};
  const int powersOf2[16] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192,
			     16384, 32768};
  
  const int adcPrescalerSizes[8] = {2, 4, 8, 16, 32, 64, 128, 256};
  const char* adcDualSelNames[4] = {"BOTH", "INTERLEAVE", "reserved2", "reserved3"};
  const char* adcMuxPosNames[32] = {"AIN0", "AIN1", "AIN2", "AIN3", "AIN4", "AIN5", "AIN6", "AIN7",
                                    "AIN8", "AIN9", "AIN10", "AIN11", "AIN12", "AIN13", "AIN14",
				    "AIN15", "resv16", "resv17", "resv18", "resv19", "resv20",
				    "resv21", "resv22", "resv23", "SCALEDCOREVCC", "SCALEDVBAT",
				    "SCALEDIOVCC", "BANDGAP", "PTAT", "CTAT", "DAC", "resv31"};
  const char* adcMuxNegNames[32] = {"AIN0", "AIN1", "AIN2", "AIN3", "AIN4", "AIN5", "AIN6", "AIN7",
                                    "resv8", "resv9", "resv10", "resv11", "resv12", "resv13",
				    "resv14", "resv15", "resv16", "resv17", "resv18", "resv19",
				    "resv20", "resv21", "resv22", "resv23", "GND", "resv25",
				    "resv26", "resv27", "resv28", "resv29", "resv30", "resv31"};
  const int adcResSelSizes[4] = {12, 16, 10, 8};
  const char* adcWinModeNames[8] = {"DISABLE", "MODE1", "MODE2", "MODE3", "MODE4",
                                    "resv5", "resv6", "resv7"};
  const char* adcRefSelNames[16] = {"INTREF", "resv1", "INTVCC0", "INTVCC1", "AREFA", "AREFB",
                                    "AREFC", "resv7", "resv8", "resv9", "resv10", "resv11",
				    "resv12", "resv13", "resv14", "resv15"};

  const char* usartChsize[8] = {"8bit", "9bit", "n/a", "n/a", "n/a", "5bit", "6bit", "7bit"};
  const char* usartPmode[2] = {"even", "odd"};

  const char* i2cmBusState[4] = {"unknown", "idle", "owner", "busy"};

};

#endif // SAMD51_DUMPSTER_H
