/*
 * DO NOT EDIT!  This file was automatically generated by mkPortMux.sh
 * 2024-02-08 19:24:07 PST
 *
 * SAMD51 specific file to map from a port and mux number
 * to the peripheral function configured to use that port.
 */

#ifdef _SAMD51J20A_
#ifndef _SAMD51J20A_PORTMUX_
#define _SAMD51J20A_PORTMUX_

const uint16_t numPortUserNames = 243;
const char* portUserNames[numPortUserNames] = {
    "undefined", "AC_AIN0", "AC_AIN1", "AC_AIN2", "AC_AIN3", "AC_CMP0", "AC_CMP1", "ADC0_AIN0", "ADC0_AIN1", "ADC0_AIN10", 
    "ADC0_AIN11", "ADC0_AIN12", "ADC0_AIN13", "ADC0_AIN14", "ADC0_AIN15", "ADC0_AIN2", "ADC0_AIN3", "ADC0_AIN4", "ADC0_AIN5", "ADC0_AIN6", 
    "ADC0_AIN7", "ADC0_AIN8", "ADC0_AIN9", "ADC0_DRV0", "ADC0_DRV1", "ADC0_DRV10", "ADC0_DRV11", "ADC0_DRV12", "ADC0_DRV13", "ADC0_DRV14", 
    "ADC0_DRV15", "ADC0_DRV16", "ADC0_DRV17", "ADC0_DRV18", "ADC0_DRV19", "ADC0_DRV2", "ADC0_DRV20", "ADC0_DRV21", "ADC0_DRV22", "ADC0_DRV23", 
    "ADC0_DRV24", "ADC0_DRV25", "ADC0_DRV26", "ADC0_DRV27", "ADC0_DRV28", "ADC0_DRV29", "ADC0_DRV3", "ADC0_DRV30", "ADC0_DRV31", "ADC0_DRV4", 
    "ADC0_DRV5", "ADC0_DRV6", "ADC0_DRV7", "ADC0_DRV8", "ADC0_DRV9", "ADC0_PTCXY0", "ADC0_PTCXY1", "ADC0_PTCXY10", "ADC0_PTCXY11", "ADC0_PTCXY13", 
    "ADC0_PTCXY14", "ADC0_PTCXY15", "ADC0_PTCXY16", "ADC0_PTCXY17", "ADC0_PTCXY18", "ADC0_PTCXY19", "ADC0_PTCXY2", "ADC0_PTCXY20", "ADC0_PTCXY21", "ADC0_PTCXY22", 
    "ADC0_PTCXY23", "ADC0_PTCXY24", "ADC0_PTCXY25", "ADC0_PTCXY26", "ADC0_PTCXY27", "ADC0_PTCXY28", "ADC0_PTCXY29", "ADC0_PTCXY3", "ADC0_PTCXY30", "ADC0_PTCXY31", 
    "ADC0_PTCXY4", "ADC0_PTCXY5", "ADC0_PTCXY6", "ADC0_PTCXY7", "ADC0_PTCXY8", "ADC0_PTCXY9", "ADC1_AIN0", "ADC1_AIN1", "ADC1_AIN2", "ADC1_AIN3", 
    "ADC1_AIN6", "ADC1_AIN7", "ADC1_AIN8", "ADC1_AIN9", "ANAREF_VREF0", "ANAREF_VREF1", "ANAREF_VREF2", "CCL_IN0", "CCL_IN1", "CCL_IN10", 
    "CCL_IN11", "CCL_IN2", "CCL_IN3", "CCL_IN4", "CCL_IN5", "CCL_IN6", "CCL_IN7", "CCL_IN8", "CCL_IN9", "CCL_OUT0", 
    "CCL_OUT1", "CCL_OUT2", "CCL_OUT3", "CM4_SWCLK", "CM4_SWO", "DAC_VOUT0", "DAC_VOUT1", "EIC_EXTINT0", "EIC_EXTINT1", "EIC_EXTINT10", 
    "EIC_EXTINT11", "EIC_EXTINT12", "EIC_EXTINT13", "EIC_EXTINT14", "EIC_EXTINT15", "EIC_EXTINT2", "EIC_EXTINT3", "EIC_EXTINT4", "EIC_EXTINT5", "EIC_EXTINT6", 
    "EIC_EXTINT7", "EIC_EXTINT8", "EIC_EXTINT9", "EIC_NMI", "GCLK_IO0", "GCLK_IO1", "GCLK_IO2", "GCLK_IO3", "GCLK_IO4", "GCLK_IO5", 
    "GCLK_IO6", "GCLK_IO7", "I2S_FS0", "I2S_FS1", "I2S_MCK0", "I2S_MCK1", "I2S_SCK0", "I2S_SCK1", "I2S_SDI", "I2S_SDO", 
    "PCC_CLK", "PCC_DATA0", "PCC_DATA1", "PCC_DATA2", "PCC_DATA3", "PCC_DATA4", "PCC_DATA5", "PCC_DATA6", "PCC_DATA7", "PCC_DATA8", 
    "PCC_DATA9", "PCC_DEN1", "PCC_DEN2", "PDEC_QDI0", "PDEC_QDI1", "PDEC_QDI2", "QSPI_CS", "QSPI_DATA0", "QSPI_DATA1", "QSPI_DATA2", 
    "QSPI_DATA3", "QSPI_SCK", "SDHC0_SDCD", "SDHC0_SDCK", "SDHC0_SDCMD", "SDHC0_SDDAT0", "SDHC0_SDDAT1", "SDHC0_SDDAT2", "SDHC0_SDDAT3", "SDHC0_SDWP", 
    "SERCOM0_PAD0", "SERCOM0_PAD1", "SERCOM0_PAD2", "SERCOM0_PAD3", "SERCOM1_PAD0", "SERCOM1_PAD1", "SERCOM1_PAD2", "SERCOM1_PAD3", "SERCOM2_PAD0", "SERCOM2_PAD1", 
    "SERCOM2_PAD2", "SERCOM2_PAD3", "SERCOM3_PAD0", "SERCOM3_PAD1", "SERCOM3_PAD2", "SERCOM3_PAD3", "SERCOM4_PAD0", "SERCOM4_PAD1", "SERCOM4_PAD2", "SERCOM4_PAD3", 
    "SERCOM5_PAD0", "SERCOM5_PAD1", "SERCOM5_PAD2", "SERCOM5_PAD3", "TAL_BRK", "TC0_WO0", "TC0_WO1", "TC1_WO0", "TC1_WO1", "TC2_WO0", 
    "TC2_WO1", "TC3_WO0", "TC3_WO1", "TC4_WO0", "TC4_WO1", "TC5_WO0", "TC5_WO1", "TCC0_WO0", "TCC0_WO1", "TCC0_WO2", 
    "TCC0_WO3", "TCC0_WO4", "TCC0_WO5", "TCC0_WO6", "TCC0_WO7", "TCC1_WO0", "TCC1_WO1", "TCC1_WO2", "TCC1_WO3", "TCC1_WO4", 
    "TCC1_WO5", "TCC1_WO6", "TCC1_WO7", "TCC2_WO0", "TCC2_WO1", "TCC2_WO2", "TCC3_WO0", "TCC3_WO1", "TCC4_WO0", "TCC4_WO1", 
    "USB_DM", "USB_DP", "USB_SOF_1KHZ", 
};

const uint16_t numPorts = PORT_GROUPS * 32;
const uint16_t numMux   = 16;
const uint16_t numPortMuxUserMap = numPorts * numMux;

const uint16_t portMuxUserMap[numPortMuxUserMap] = {
    117,    0,    0,  184,  209,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    118,    0,    0,  185,  210,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    125,  115,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    126,   55,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   23,    0,
    127,   77,    0,  180,  205,    0,    0,    0,    0,    0,    0,    0,    0,   97,   46,    0,
    128,  116,    0,  181,  206,    0,    0,    0,    0,    0,    0,    0,    0,   98,    0,    0,
    129,   80,    0,  182,  207,    0,    0,    0,  172,    0,    0,    0,    0,  101,   49,    0,
    130,   81,    0,  183,  208,    0,    0,    0,  179,    0,    0,    0,    0,  109,   50,    0,
    133,   88,  180,  189,  205,  217,  229,  167,  174,  144,    0,    0,    0,  102,   51,    0,
    132,   89,  181,  188,  206,  218,  230,  168,  175,  142,    0,    0,    0,  103,   52,    0,
    119,   84,  182,  190,  207,  219,  231,  169,  176,  146,    0,    0,  138,  104,   53,    0,
    120,   85,  183,  191,  208,  220,  232,  170,  177,  149,    0,    0,  139,  110,   54,    0,
    121,    0,  188,  197,  209,  223,  227,    0,  172,    0,  161,    0,    5,    0,    0,    0,
    122,    0,  189,  196,  210,  224,  228,    0,  179,    0,  162,    0,    6,    0,    0,    0,
    123,    0,  190,  198,  211,  233,  227,    0,    0,    0,  150,    0,  134,    0,    0,    0,
    124,    0,  191,  199,  212,  234,  228,    0,    0,    0,    0,    0,  135,    0,    0,    0,
    117,   57,  184,  193,  209,  225,  221,    0,    0,    0,  151,    0,  136,   97,   25,    0,
    118,   58,  185,  192,  210,  226,  222,    0,    0,    0,  152,    0,  137,   98,   26,    0,
    125,    0,  186,  194,  211,  227,  223,    0,    0,    0,  153,    0,    5,  101,   27,    0,
    126,   59,  187,  195,  212,  228,  224,    0,    0,    0,  154,    0,    6,  109,   28,    0,
    127,   60,  202,  194,    0,  229,  217,    0,    0,  142,  155,    0,    0,    0,   29,    0,
    128,   61,  203,  195,    0,  230,  218,    0,    0,  149,  156,    0,    0,    0,   30,    0,
    129,   62,  192,  201,  213,  231,  219,    0,    0,  148,  157,    0,    0,  105,   31,    0,
    130,   63,  193,  200,  214,  232,  220,  242,    0,  143,  158,    0,    0,  106,   32,    0,
    131,    0,  194,  202,  215,  235,  163,  240,    0,    0,    0,    0,    0,  107,    0,    0,
    132,    0,  195,  203,  216,    0,  164,  241,    0,    0,    0,    0,    0,  111,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    120,   64,    0,    0,    0,    0,    0,  204,    0,    0,    0,    0,  135,    0,   33,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    123,   65,    0,  186,    0,  233,    0,  113,    0,    0,    0,    0,  134,  102,   34,    0,
    124,    0,    0,  187,    0,  234,    0,    0,    0,    0,    0,    0,    0,  110,    0,    0,
    117,   78,    0,  202,    0,    0,    0,    0,    0,    0,    0,    0,    0,   98,   47,    0,
    118,   79,    0,  203,    0,    0,    0,    0,    0,    0,    0,    0,    0,  101,   48,    0,
    125,   67,    0,  200,    0,  235,    0,    0,    0,    0,    0,    0,    0,  109,   36,    0,
    126,   68,    0,  201,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   37,    0,
    127,   90,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   38,    0,
    128,   91,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,   39,    0,
    129,   92,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  105,   40,    0,
    130,   93,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,  106,   41,    0,
    131,   86,    0,  196,  213,    0,    0,    0,    0,    0,    0,    0,    0,  107,   24,    0,
    132,   87,    0,  197,  214,    0,    0,    0,    0,    0,    0,    0,    0,  111,   35,    0,
    119,    0,    0,  198,  215,  221,  225,  171,  178,  148,    0,    0,  138,  100,    0,    0,
    120,    0,    0,  199,  216,  222,  226,  166,  173,  143,    0,    0,  139,  110,    0,    0,
    121,   73,  196,    0,  213,  236,  217,    0,  172,  147,    0,    0,  140,    0,   42,    0,
    122,   74,  197,    0,  214,  237,  218,    0,  179,  145,    0,    0,  141,    0,   43,    0,
    123,   75,  198,    0,  215,  238,  219,    0,    0,    0,  159,    0,  134,  108,   44,    0,
    124,   76,  199,    0,  216,  239,  220,    0,    0,    0,  160,    0,  135,   99,   45,    0,
    117,    0,  200,    0,    0,  236,  221,    0,    0,  146,    0,    0,  136,  100,    0,    0,
    118,    0,  201,    0,    0,  237,  222,    0,    0,  144,    0,    0,  137,  112,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    129,    0,  186,  202,    0,    0,  165,  242,    0,    0,    0,    0,  134,   97,    0,    0,
    130,    0,  187,  203,    0,    0,  163,    0,    0,    0,    0,    0,  135,  109,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
      0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    123,    0,    0,  201,  205,  238,  223,  114,    0,    0,    0,    0,    0,    0,    0,    0,
    124,    0,    0,  200,  206,  239,  224,  204,    0,    0,    0,    0,    0,    0,    0,    0,
};

const char* getPortMuxUserName(uint16_t portNum, uint16_t muxNum) {
  return portUserNames[portMuxUserMap[portNum * 16 + muxNum]];
}

#endif // _SAMD51J20A_PORTMUX_
#endif // _SAMD51J20A_
