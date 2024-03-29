/*
 * DO NOT EDIT!  This file was automatically generated by mkPortMux.sh
 * 2024-02-08 19:24:06 PST
 *
 * SAMD51 specific file to map from a port and mux number
 * to the peripheral function configured to use that port.
 */

#ifdef _SAMD51G18A_
#ifndef _SAMD51G18A_PORTMUX_
#define _SAMD51G18A_PORTMUX_

const uint16_t numPortUserNames = 193;
const char* portUserNames[numPortUserNames] = {
    "undefined", "AC_AIN0", "AC_AIN1", "AC_AIN2", "AC_AIN3", "AC_CMP0", "AC_CMP1", "ADC0_AIN0", "ADC0_AIN1", "ADC0_AIN10", 
    "ADC0_AIN11", "ADC0_AIN14", "ADC0_AIN15", "ADC0_AIN2", "ADC0_AIN3", "ADC0_AIN4", "ADC0_AIN5", "ADC0_AIN6", "ADC0_AIN7", "ADC0_AIN8", 
    "ADC0_AIN9", "ADC0_DRV0", "ADC0_DRV1", "ADC0_DRV10", "ADC0_DRV11", "ADC0_DRV12", "ADC0_DRV13", "ADC0_DRV14", "ADC0_DRV15", "ADC0_DRV16", 
    "ADC0_DRV17", "ADC0_DRV18", "ADC0_DRV19", "ADC0_DRV2", "ADC0_DRV20", "ADC0_DRV21", "ADC0_DRV3", "ADC0_DRV4", "ADC0_DRV5", "ADC0_DRV6", 
    "ADC0_DRV7", "ADC0_DRV8", "ADC0_DRV9", "ADC0_PTCXY0", "ADC0_PTCXY1", "ADC0_PTCXY10", "ADC0_PTCXY11", "ADC0_PTCXY13", "ADC0_PTCXY14", "ADC0_PTCXY15", 
    "ADC0_PTCXY16", "ADC0_PTCXY17", "ADC0_PTCXY18", "ADC0_PTCXY19", "ADC0_PTCXY2", "ADC0_PTCXY20", "ADC0_PTCXY21", "ADC0_PTCXY3", "ADC0_PTCXY4", "ADC0_PTCXY5", 
    "ADC0_PTCXY6", "ADC0_PTCXY7", "ADC0_PTCXY8", "ADC0_PTCXY9", "ADC1_AIN0", "ADC1_AIN1", "ADC1_AIN2", "ADC1_AIN3", "ANAREF_VREF0", "ANAREF_VREF1", 
    "ANAREF_VREF2", "CCL_IN0", "CCL_IN1", "CCL_IN11", "CCL_IN2", "CCL_IN3", "CCL_IN4", "CCL_IN5", "CCL_IN6", "CCL_IN7", 
    "CCL_IN8", "CCL_OUT0", "CCL_OUT1", "CCL_OUT2", "CM4_SWCLK", "DAC_VOUT0", "DAC_VOUT1", "EIC_EXTINT0", "EIC_EXTINT1", "EIC_EXTINT10", 
    "EIC_EXTINT11", "EIC_EXTINT12", "EIC_EXTINT13", "EIC_EXTINT14", "EIC_EXTINT15", "EIC_EXTINT2", "EIC_EXTINT3", "EIC_EXTINT4", "EIC_EXTINT5", "EIC_EXTINT6", 
    "EIC_EXTINT7", "EIC_EXTINT8", "EIC_EXTINT9", "EIC_NMI", "GCLK_IO0", "GCLK_IO1", "GCLK_IO2", "GCLK_IO3", "GCLK_IO4", "GCLK_IO5", 
    "PCC_CLK", "PCC_DATA0", "PCC_DATA1", "PCC_DATA2", "PCC_DATA3", "PCC_DATA4", "PCC_DATA5", "PCC_DATA6", "PCC_DATA7", "PCC_DEN1", 
    "PCC_DEN2", "PDEC_QDI0", "PDEC_QDI1", "PDEC_QDI2", "QSPI_CS", "QSPI_DATA0", "QSPI_DATA1", "QSPI_DATA2", "QSPI_DATA3", "QSPI_SCK", 
    "SDHC0_SDCD", "SDHC0_SDCK", "SDHC0_SDCMD", "SDHC0_SDDAT0", "SDHC0_SDDAT1", "SDHC0_SDDAT2", "SDHC0_SDDAT3", "SDHC0_SDWP", "SERCOM0_PAD0", "SERCOM0_PAD1", 
    "SERCOM0_PAD2", "SERCOM0_PAD3", "SERCOM1_PAD0", "SERCOM1_PAD1", "SERCOM1_PAD2", "SERCOM1_PAD3", "SERCOM2_PAD0", "SERCOM2_PAD1", "SERCOM2_PAD2", "SERCOM2_PAD3", 
    "SERCOM3_PAD0", "SERCOM3_PAD1", "SERCOM3_PAD2", "SERCOM3_PAD3", "SERCOM4_PAD0", "SERCOM4_PAD1", "SERCOM4_PAD2", "SERCOM4_PAD3", "SERCOM5_PAD0", "SERCOM5_PAD1", 
    "SERCOM5_PAD2", "SERCOM5_PAD3", "TAL_BRK", "TC0_WO0", "TC0_WO1", "TC1_WO0", "TC1_WO1", "TC2_WO0", "TC2_WO1", "TC3_WO0", 
    "TC3_WO1", "TCC0_WO0", "TCC0_WO1", "TCC0_WO2", "TCC0_WO3", "TCC0_WO4", "TCC0_WO5", "TCC0_WO6", "TCC0_WO7", "TCC1_WO0", 
    "TCC1_WO1", "TCC1_WO2", "TCC1_WO3", "TCC1_WO4", "TCC1_WO5", "TCC1_WO6", "TCC1_WO7", "TCC2_WO0", "TCC2_WO1", "TCC2_WO2", 
    "USB_DM", "USB_DP", "USB_SOF_1KHZ", 
};

const uint16_t numPorts = PORT_GROUPS * 32;
const uint16_t numMux   = 16;
const uint16_t numPortMuxUserMap = numPorts * numMux;

const uint16_t portMuxUserMap[numPortMuxUserMap] = {
     87,    0,    0,  142,  167,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     88,    0,    0,  143,  168,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     95,   85,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     96,   43,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   21,    0,
     97,   57,    0,  138,  163,    0,    0,    0,    0,    0,    0,    0,    0,   71,   36,    0,
     98,   86,    0,  139,  164,    0,    0,    0,    0,    0,    0,    0,    0,   72,    0,    0,
     99,   58,    0,  140,  165,    0,    0,    0,  130,    0,    0,    0,    0,   74,   37,    0,
    100,   59,    0,  141,  166,    0,    0,    0,  137,    0,    0,    0,    0,   81,   38,    0,
    103,   66,  138,  147,  163,  171,  183,  125,  132,    0,    0,    0,    0,   75,   39,    0,
    102,   67,  139,  146,  164,  172,  184,  126,  133,    0,    0,    0,    0,   76,   40,    0,
     89,   62,  140,  148,  165,  173,  185,  127,  134,    0,    0,    0,  108,   77,   41,    0,
     90,   63,  141,  149,  166,  174,  186,  128,  135,    0,    0,    0,  109,   82,   42,    0,
     91,    0,  146,  155,  167,  177,  181,    0,  130,    0,  119,    0,    5,    0,    0,    0,
     92,    0,  147,  154,  168,  178,  182,    0,  137,    0,  120,    0,    6,    0,    0,    0,
     93,    0,  148,  156,  169,  187,  181,    0,    0,    0,  110,    0,  104,    0,    0,    0,
     94,    0,  149,  157,  170,  188,  182,    0,    0,    0,    0,    0,  105,    0,    0,    0,
     87,   45,  142,  151,  167,  179,  175,    0,    0,    0,  111,    0,  106,   71,   23,    0,
     88,   46,  143,  150,  168,  180,  176,    0,    0,    0,  112,    0,  107,   72,   24,    0,
     95,    0,  144,  152,  169,  181,  177,    0,    0,    0,  113,    0,    5,   74,   25,    0,
     96,   47,  145,  153,  170,  182,  178,    0,    0,    0,  114,    0,    6,   81,   26,    0,
     97,   48,  160,  152,    0,  183,  171,    0,    0,    0,  115,    0,    0,    0,   27,    0,
     98,   49,  161,  153,    0,  184,  172,    0,    0,    0,  116,    0,    0,    0,   28,    0,
     99,   50,  150,  159,    0,  185,  173,    0,    0,    0,  117,    0,    0,   78,   29,    0,
    100,   51,  151,  158,    0,  186,  174,  192,    0,    0,  118,    0,    0,   79,   30,    0,
    101,    0,  152,  160,    0,  189,  121,  190,    0,    0,    0,    0,    0,   80,    0,    0,
    102,    0,  153,  161,    0,    0,  122,  191,    0,    0,    0,    0,    0,   83,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     90,   52,    0,    0,    0,    0,    0,  162,    0,    0,    0,    0,  105,    0,   31,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     93,   53,    0,  144,    0,  187,    0,   84,    0,    0,    0,    0,  104,   75,   32,    0,
     94,    0,    0,  145,    0,  188,    0,    0,    0,    0,    0,    0,    0,   82,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     95,   55,    0,  158,    0,  189,    0,    0,    0,    0,    0,    0,    0,   81,   34,    0,
     96,   56,    0,  159,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   35,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    101,   64,    0,  154,    0,    0,    0,    0,    0,    0,    0,    0,    0,   80,   22,    0,
    102,   65,    0,  155,    0,    0,    0,    0,    0,    0,    0,    0,    0,   83,   33,    0,
     89,    0,    0,  156,    0,  175,  179,  129,  136,    0,    0,    0,  108,   73,    0,    0,
     90,    0,    0,  157,    0,  176,  180,  124,  131,    0,    0,    0,  109,   82,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
     99,    0,  144,  160,    0,    0,  123,  192,    0,    0,    0,    0,  104,   71,    0,    0,
    100,    0,  145,  161,    0,    0,  121,    0,    0,    0,    0,    0,  105,   81,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};

const char* getPortMuxUserName(uint16_t portNum, uint16_t muxNum) {
  return portUserNames[portMuxUserMap[portNum * 16 + muxNum]];
}

#endif // _SAMD51G18A_PORTMUX_
#endif // _SAMD51G18A_
