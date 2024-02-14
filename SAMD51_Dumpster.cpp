/*
 * Dump routines for some low level SAMD51 hardware components.
 */

#include "SAMD51_Dumpster.h"
#include "portmux.h"


SAMD51_Dumpster::SAMD51_Dumpster() {
}


/*
 * Sets the flag that controls printing of disabled entries.  By default,
 * only enabled entries are printed.  Passing in a value > 0 will cause
 * disabled entries to be printed, too.
 */
void SAMD51_Dumpster::begin(int verbose) {
  this->verbose = verbose;
}

/*
 * Dump all the port groups configured for this microprocessor instance.
 */
void SAMD51_Dumpster::dumpPort(const char* msg) {
  Serial.printf("\nPORT:");
  if (msg != NULL) {
    Serial.printf(" %s", msg);
  }
  Serial.printf("\n");
  
  for (int i = 0; i < PORT_GROUPS; i++) {
    dumpPortGroup(i);
  }
}

/*
 * Dump a port group of 32 ports.
 */
void SAMD51_Dumpster::dumpPortGroup(int groupNum) {
  const char* groupName[4] = {"A", "B", "C", "D"};
  const char* evAct[4] = {"OUT", "SET", "CLR", "TGL"};
  PortGroup* pg = &(PORT->Group[groupNum]);
  uint32_t dir    = pg->DIR.reg;
  uint32_t out    = pg->OUT.reg;
  uint32_t in     = pg->IN.reg;
  uint32_t sample = pg->CTRL.reg;
  const char* gName = groupName[groupNum];
  Serial.printf("PORT GROUP %d %s\n", groupNum, gName);
  PORT_EVCTRL_Type evctrl;
  evctrl.reg = pg->EVCTRL.reg;
  Serial.printf("    EVCTRL 0: portei=%d evact=%d [%s] %d\n",
                evctrl.bit.PORTEI0, evctrl.bit.EVACT0, evAct[evctrl.bit.EVACT0], evctrl.bit.PID0);
  Serial.printf("           1: portei=%d evact=%d [%s] %d\n",
                evctrl.bit.PORTEI1, evctrl.bit.EVACT1, evAct[evctrl.bit.EVACT1], evctrl.bit.PID1);
  Serial.printf("           2: portei=%d evact=%d [%s] %d\n",
                evctrl.bit.PORTEI2, evctrl.bit.EVACT2, evAct[evctrl.bit.EVACT2], evctrl.bit.PID2);
  Serial.printf("           3: portei=%d evact=%d [%s] %d\n",
                evctrl.bit.PORTEI3, evctrl.bit.EVACT3, evAct[evctrl.bit.EVACT3], evctrl.bit.PID3);
  
  // display 2 ports per iteration, so we can increment the mux index once
  int muxNum = 0;
  for (int portNum = 0; portNum < 32; portNum++) {
    PORT_PMUX_Type mux;
    mux.reg = pg->PMUX[muxNum].reg;
    PORT_PINCFG_Type cfg;
    cfg.reg = pg->PINCFG[portNum].reg;
    Serial.printf("    P%s%02d: dir=%d out=%d in=%d sample=%d mux=%d ",
                  gName, portNum, dir & 1, out & 1, in & 1, sample & 1, mux.bit.PMUXE);
    Serial.printf("pmuxen=%d inen=%d pullen=%d drvstr=%d",
                  cfg.bit.PMUXEN, cfg.bit.INEN, cfg.bit.PULLEN, cfg.bit.DRVSTR);
    if (cfg.bit.PMUXEN) {
      Serial.printf(" mux_user=%s", getPortMuxUserName(portNum, mux.bit.PMUXE));
    }
    Serial.printf("\n");
    dir    >>= 1;
    out    >>= 1;
    in     >>= 1;
    sample >>= 1;
    
    portNum += 1;
    muxNum += 1;
    
    cfg.reg = pg->PINCFG[portNum].reg;
    Serial.printf("    P%s%02d: dir=%d out=%d in=%d sample=%d mux=%d ",
                  gName, portNum, dir & 1, out & 1, in & 1, sample & 1, mux.bit.PMUXO);
    Serial.printf("pmuxen=%d inen=%d pullen=%d drvstr=%d",
                  cfg.bit.PMUXEN, cfg.bit.INEN, cfg.bit.PULLEN, cfg.bit.DRVSTR);
    if (cfg.bit.PMUXEN) {
      Serial.printf(" mux_user=%s", getPortMuxUserName(portNum, mux.bit.PMUXO));
    }
    Serial.printf("\n");
    dir    >>= 1;
    out    >>= 1;
    in     >>= 1;
    sample >>= 1;
  }
  Serial.printf("\n");
}


/*
 * Dumps the GCLK entries.
 */
void SAMD51_Dumpster::dumpGCLK(const char* msg) {
  Serial.printf("\nGCLK:");
  if (msg != NULL) {
    Serial.printf(" %s", msg);
  }
  Serial.printf("\n");
  
  // check SYNCBUSY?
  uint8_t tmp8 = REG_GCLK_CTRLA;
  Serial.printf("  CTRLA=0X%02x (SWRST=%d)\n", tmp8, tmp8 & 0x1);
  uint16_t tmp16 = REG_GCLK_SYNCBUSY;
  Serial.printf("  SYNCBUSY=0x%x\n", tmp16);
  
  dumpGCLKGenerators();
  
  Serial.println(" ");
  
  dumpGCLKUsers();
  
  Serial.printf("\n");
}

/*
 * Dumps all the GCLK generator entries.
 */
void SAMD51_Dumpster::dumpGCLKGenerators() {
  for (int i = 0; i < GCLK_GEN_NUM; i++) {
    dumpGclkGenctrl(i);
  }
}

/*
 * Dumps all the GCLK user entries.
 */
void SAMD51_Dumpster::dumpGCLKUsers() {
  for (int i = 0; i < GCLK_NUM; i++) {
    dumpGclkPchctrl(i);
  }
}

/*
 * Dumps a single GCLK generator entry.
 * 
 * N.B.: Max div is 512, except for GCLK1, where it is 131072.
 */
void SAMD51_Dumpster::dumpGclkGenctrl(int n) {
  GCLK_GENCTRL_Type genctrl;
  genctrl.reg = GCLK->GENCTRL[n].reg;
  
  if (genctrl.bit.GENEN || verbose) {
    Serial.printf("  GENCTRL%d=0x%x (src=%d [%s] genen=%d idc=%d ",
                  n, genctrl.reg, genctrl.bit.SRC, gclkSrcName[genctrl.bit.SRC], genctrl.bit.GENEN,
                  genctrl.bit.IDC);
    Serial.printf("oov=%d oe=%d divsel=%d runstdby=%d div=%d)\n",
                  genctrl.bit.OOV, genctrl.bit.OE, genctrl.bit.DIVSEL,
                  genctrl.bit.RUNSTDBY, genctrl.bit.DIV);
  }
}

/*
 * Dumps a single GCLK peripheral channel entry (aka user entry).
 */
void SAMD51_Dumpster::dumpGclkPchctrl(int n) {
  GCLK_PCHCTRL_Type pchctrl;
  pchctrl.reg = GCLK->PCHCTRL[n].reg;
  if (pchctrl.bit.CHEN || verbose) {
    Serial.printf("  PCHCTRL%d=0x%02x (gen=%d chen=%d wrtlock=%d) [%s]\n",
                  n, pchctrl.reg, pchctrl.bit.GEN, pchctrl.bit.CHEN, pchctrl.bit.WRTLOCK,
                  gclkUserName[n]);
  }
}


/*
 * Dump the MCLK flags.
 * 
 * TODO: Finish this implementation.  Not turning on the MCLK for a
 *       peripheral is a common problem.
 */
void SAMD51_Dumpster::dumpMCLK(const char* msg) {
  Serial.printf("\nMCLK:");
  if (msg != NULL) {
    Serial.printf(" %s", msg);
  }
  Serial.printf("\n");
  
  uint8_t hsdiv = REG_MCLK_HSDIV;
  uint8_t cpudiv = REG_MCLK_CPUDIV;
  Serial.printf("  hsdiv=0X%02x cpudiv=0X%02x\n", hsdiv, cpudiv);
  
  dumpMclkAHB();
  dumpMclkAPBA();
  dumpMclkAPBB();
  dumpMclkAPBC();
  dumpMclkAPBD();
}

void SAMD51_Dumpster::dumpMclkAHB() {
  MCLK_AHBMASK_Type ahb;
  ahb.reg = REG_MCLK_AHBMASK;
  
  Serial.printf("  AHB: HPB0/APBA=%d  HPB1/APBB=%d  HPB2/APBC=%d  HPB3/APBD=%d\n",
                ahb.bit.HPB0_, ahb.bit.HPB1_, ahb.bit.HPB2_, ahb.bit.HPB3_);
  // To be continued....
  // To be continued....
}

void SAMD51_Dumpster::dumpMclkAPBA() {
  
  Serial.printf("  APBA: \n");
}

void SAMD51_Dumpster::dumpMclkAPBB() {
  
  Serial.printf("  APBB: \n");
}

void SAMD51_Dumpster::dumpMclkAPBC() {
  
  Serial.printf("  APBC: \n");
}


void SAMD51_Dumpster::dumpMclkAPBD() {
  
  Serial.printf("  APBD: \n");
}

/*
 * Dumps all the SERCOM instances.
 * 
 * Documentation page numbers for SERCOM register descriptions:
 * UART: 851
 * SPI:  889
 * I2C:  928
 */
void SAMD51_Dumpster::dumpSERCOM(const char* msg) {
  Serial.printf("\nSERCOM:");
  if (msg != NULL) {
    Serial.printf(" %s", msg);
  }
  Serial.printf("\n");
  
  for (int i = 0; i < SERCOM_INST_NUM; i++) {
    dumpSercomInstance(i);
  }
}

/*
 * Dumps the given SERCOM instance number.
 */
void SAMD51_Dumpster::dumpSercomInstance(int n) {
  if (n < 0 || n >= SERCOM_INST_NUM) {
    return;
  }
  Sercom* instances[] = SERCOM_INSTS;
  Sercom* sc = instances[n];
  SercomUsart* scu = &sc->USART;
  
  // Serial.printf("  Sercom  sc=0x%x  scu=0x%x\n", sc, scu);
  
  bool myVerbose = verbose;
  
  if (scu->CTRLA.bit.ENABLE || myVerbose) {
    switch (scu->CTRLA.bit.MODE) {
      case 0:  // USART with external clock
      case 1:  // USART with internal clock
        Serial.printf("SERCOM%d: USART\n", n);
        dumpSercomUsart(scu);
        break;
      case 2:  // SPI peripheral
      case 3:  // SPI controller
        Serial.printf("SERCOM%d: SPI\n", n);
        dumpSercomSpi(&sc->SPI);
        break;
      case 4:  // I2C peripheral
        Serial.printf("SERCOM%d: I2CS\n", n);
        dumpSercomI2cs(&sc->I2CS);
        break;
      case 5:  // I2C controller
        Serial.printf("SERCOM%d: I2CM\n", n);
        dumpSercomI2cm(&sc->I2CM);
        break;
      default:
        Serial.printf("SERCOM%d: invalid mode=0x%x (%d)\n",
                     n, scu->CTRLA.bit.MODE, scu->CTRLA.bit.MODE);
        break;
    }
  Serial.printf("\n");
  }
}

/*
 * Dump a SERCOM/USART object.
 */
void SAMD51_Dumpster::dumpSercomUsart(SercomUsart* scu) {
  SERCOM_USART_CTRLA_Type ctrla;
  ctrla.reg = scu->CTRLA.reg;
  Serial.printf("  CTRLA: 0x%x swrst %d enable %d mode %d runstdby %d ",
                ctrla.reg, ctrla.bit.SWRST, ctrla.bit.ENABLE, ctrla.bit.MODE, ctrla.bit.RUNSTDBY);
  Serial.printf("ibon=%d txinv=%d rxinv=%d sampr=%d\n",
                ctrla.bit.IBON, ctrla.bit.TXINV, ctrla.bit.RXINV, ctrla.bit.SAMPR);
  Serial.printf("         txpo=%d rxpo=%d sampa=%d form=%d cmode=%d cpol=%d dord=%d\n",
                ctrla.bit.TXPO, ctrla.bit.RXPO, ctrla.bit.SAMPA, ctrla.bit.FORM,
                ctrla.bit.CMODE, ctrla.bit.CPOL, ctrla.bit.DORD);
                
  SERCOM_USART_CTRLB_Type ctrlb;
  ctrlb.reg = scu->CTRLB.reg;
  Serial.printf("  CTRLB: 0x%x chsize=%d [%s] sbmode=%d [%dbit] colden=%d ",
                ctrlb.reg, ctrlb.bit.CHSIZE, usartChsize[ctrlb.bit.CHSIZE], ctrlb.bit.SBMODE,
                ctrlb.bit.SBMODE + 1, ctrlb.bit.COLDEN);
  Serial.printf("sfde=%d enc=%d pmode=%d [%s] txen=%d rxen=%d lincmd=%d\n",
                ctrlb.bit.SFDE, ctrlb.bit.ENC, ctrlb.bit.PMODE, usartPmode[ctrlb.bit.PMODE],
                ctrlb.bit.TXEN, ctrlb.bit.RXEN, ctrlb.bit.LINCMD);
  
  SERCOM_USART_CTRLC_Type ctrlc;
  ctrlc.reg = scu->CTRLC.reg;
  Serial.printf("  CTRLC: 0x%x gtime=%d brklen=%d hdrdly=%d ",
                ctrlc.reg, ctrlc.bit.GTIME, ctrlc.bit.BRKLEN, ctrlc.bit.HDRDLY);
  Serial.printf("inack=%d dsnack=%d maxiter=%d data32b=%d\n", 
                ctrlc.bit.INACK, ctrlc.bit.DSNACK, ctrlc.bit.MAXITER, ctrlc.bit.DATA32B);
  
  SERCOM_USART_BAUD_Type baud;
  baud.reg = scu->BAUD.reg;
  Serial.printf("  BAUD: 0x%x (%d) (%d.%d)\n", baud.reg, baud.reg, baud.FRAC.BAUD, baud.FRAC.FP);
  
  Serial.printf("  RXPL: 0x%x (%d)\n", scu->RXPL.reg, scu->RXPL.reg);
  
  SERCOM_USART_INTENSET_Type intenset;
  intenset.reg = scu->INTENSET.reg;
  Serial.printf("  INTENSET: 0x%x dre=%d txc=%d rxc=%d rxs=%d ctsic=%d rxbrk=%d error=%d\n",
                intenset.reg, intenset.bit.DRE, intenset.bit.TXC, intenset.bit.RXC,
                intenset.bit.RXS, intenset.bit.CTSIC, intenset.bit.RXBRK, intenset.bit.ERROR);
  
  SERCOM_USART_INTFLAG_Type intflag;
  intflag.reg = scu->INTFLAG.reg;
  Serial.printf("  INTFLAG: 0x%x dre=%d txc=%d rxc=%d rxs=%d ctsic=%d rxbrk=%d error=%d\n",
                intflag.reg, intflag.bit.DRE, intflag.bit.TXC, intflag.bit.RXC,
                intflag.bit.RXS, intflag.bit.CTSIC, intflag.bit.RXBRK, intflag.bit.ERROR);
  
  SERCOM_USART_STATUS_Type status;
  status.reg = scu->STATUS.reg;
  Serial.printf("  STATUS: 0x%x perr=%d ferr=%d bufovf=%d cts=%d isf=%d coll=%d txe=%d iter=%d\n",
                status.reg, status.bit.PERR, status.bit.FERR, status.bit.BUFOVF, status.bit.CTS,
                status.bit.ISF, status.bit.COLL, status.bit.TXE, status.bit.ITER);
  
  SERCOM_USART_SYNCBUSY_Type sb;
  sb.reg = scu->SYNCBUSY.reg;
  Serial.printf("  SYNCBUSY: 0x%x swrst=%d enable=%d ctrlb=%d rxerrcnt=%d length=%d\n",
                sb.reg, sb.bit.SWRST, sb.bit.ENABLE, sb.bit.CTRLB, sb.bit.RXERRCNT, sb.bit.LENGTH);
  
  Serial.printf("  RXERRCNT: 0x%x (%d)\n", scu->RXERRCNT.reg, scu->RXERRCNT.reg);
  
  SERCOM_USART_LENGTH_Type len;
  len.reg = scu->LENGTH.reg;
  Serial.printf("  LENGTH: 0x%x length=%d lenen=%d\n", len.reg, len.bit.LEN, len.bit.LENEN);
  
  SERCOM_USART_DATA_Type data;
  data.reg = scu->DATA.reg;
  Serial.printf("  DATA: 0x%x (%d)\n", data.reg, data.reg);
  
  Serial.printf("  DBGCTRL: 0x%x dbgstop=%d\n", scu->DBGCTRL.reg, scu->DBGCTRL.bit.DBGSTOP);
}

/*
 * Dump a SERCOM/SPI object.
 */
void SAMD51_Dumpster::dumpSercomSpi(SercomSpi* scs) {
  SERCOM_SPI_CTRLA_Type ctrla;
  ctrla.reg = scs->CTRLA.reg;
  Serial.printf("  CTRLA: 0x%x swrst %d enable %d mode %d runstdby %d ",
                ctrla.reg, ctrla.bit.SWRST, ctrla.bit.ENABLE, ctrla.bit.MODE, ctrla.bit.RUNSTDBY);
  Serial.printf("ibon=%d dopo=%d dipo=%d\n",
                ctrla.bit.IBON, ctrla.bit.DOPO, ctrla.bit.DIPO);
  Serial.printf("         form=%d cpha=%d cpol=%d dord=%d\n",
                ctrla.bit.FORM, ctrla.bit.CPHA, ctrla.bit.CPOL, ctrla.bit.DORD);
                
  SERCOM_SPI_CTRLB_Type ctrlb;
  ctrlb.reg = scs->CTRLB.reg;
  Serial.printf("  CTRLB: 0x%x chsize=%d [%s] ploaden=%d ssde=%d mssen=%d amode=%d rxen=%d\n",
                ctrlb.reg, ctrlb.bit.CHSIZE, usartChsize[ctrlb.bit.CHSIZE], ctrlb.bit.PLOADEN,
                ctrlb.bit.SSDE, ctrlb.bit.MSSEN, ctrlb.bit.AMODE, ctrlb.bit.RXEN);
  
  SERCOM_SPI_CTRLC_Type ctrlc;
  ctrlc.reg = scs->CTRLC.reg;
  Serial.printf("  CTRLC: 0x%x icspace=%d data32b=%d\n", 
                ctrlc.reg, ctrlc.bit.ICSPACE, ctrlc.bit.DATA32B);
  
  SERCOM_SPI_BAUD_Type baud;
  baud.reg = scs->BAUD.reg;
  Serial.printf("  BAUD: 0x%x (%d)\n", baud.reg, baud.reg);
  
  SERCOM_SPI_INTENSET_Type intenset;
  intenset.reg = scs->INTENSET.reg;
  Serial.printf("  INTENSET: 0x%x dre=%d txc=%d rxc=%d ssl=%d error=%d\n",
                intenset.reg, intenset.bit.DRE, intenset.bit.TXC, intenset.bit.RXC,
                intenset.bit.SSL, intenset.bit.ERROR);
  
  SERCOM_SPI_INTFLAG_Type intflag;
  intflag.reg = scs->INTFLAG.reg;
  Serial.printf("  INTFLAG: 0x%x dre=%d txc=%d rxc=%d ssl=%d error=%d\n",
                intflag.reg, intflag.bit.DRE, intflag.bit.TXC, intflag.bit.RXC,
                intflag.bit.SSL, intflag.bit.ERROR);
  
  SERCOM_SPI_STATUS_Type status;
  status.reg = scs->STATUS.reg;
  Serial.printf("  STATUS: 0x%x bufovf=%d lenerr=%d\n",
                status.reg, status.bit.BUFOVF, status.bit.LENERR);
  
  SERCOM_SPI_SYNCBUSY_Type sb;
  sb.reg = scs->SYNCBUSY.reg;
  Serial.printf("  SYNCBUSY: 0x%x swrst=%d enable=%d ctrlb=%d length=%d\n",
                sb.reg, sb.bit.SWRST, sb.bit.ENABLE, sb.bit.CTRLB, sb.bit.LENGTH);
  
  SERCOM_SPI_LENGTH_Type len;
  len.reg = scs->LENGTH.reg;
  Serial.printf("  LENGTH: 0x%x length=%d lenen=%d\n", len.reg, len.bit.LEN, len.bit.LENEN);
  
  SERCOM_SPI_ADDR_Type addr;
  addr.reg = scs->ADDR.reg;
  Serial.printf("  ADDR: 0x%x addr 0x%x (%d) addrmask 0x%x (%d)\n",
                addr.reg, addr.bit.ADDR, addr.bit.ADDR, addr.bit.ADDRMASK, addr.bit.ADDRMASK);
  
  SERCOM_SPI_DATA_Type data;
  data.reg = scs->DATA.reg;
  Serial.printf("  DATA: 0x%x (%d)\n", data.reg, data.reg);
  
  Serial.printf("  DBGCTRL: 0x%x dbgstop=%d\n", scs->DBGCTRL.reg, scs->DBGCTRL.bit.DBGSTOP);
}

/*
 * Dump a SERCOM/I2C peripheral instance.
 */
void SAMD51_Dumpster::dumpSercomI2cs(SercomI2cs* sci) {
  SERCOM_I2CS_CTRLA_Type ctrla;
  ctrla.reg = sci->CTRLA.reg;
  Serial.printf("  CTRLA: 0x%x swrst %d enable %d mode %d runstdby %d ",
                ctrla.reg, ctrla.bit.SWRST, ctrla.bit.ENABLE, ctrla.bit.MODE, ctrla.bit.RUNSTDBY);
  Serial.printf("pinout=%d sdahold=%d \n", ctrla.bit.PINOUT, ctrla.bit.SDAHOLD);
  Serial.printf("         sexttoen=%d speed=%d sclsm=%d lowtouten=%d\n",
                ctrla.bit.SEXTTOEN, ctrla.bit.SPEED, ctrla.bit.SCLSM, ctrla.bit.LOWTOUTEN);
                
  SERCOM_I2CS_CTRLB_Type ctrlb;
  ctrlb.reg = sci->CTRLB.reg;
  Serial.printf("  CTRLB: 0x%x smen=%d gcmd=%d aacken=%d amode=%d cmd=%d ackact=%d\n",
                ctrlb.reg, ctrlb.bit.SMEN, ctrlb.bit.GCMD,
                ctrlb.bit.AACKEN, ctrlb.bit.AMODE, ctrlb.bit.CMD, ctrlb.bit.ACKACT);
  
  SERCOM_I2CS_CTRLC_Type ctrlc;
  ctrlc.reg = sci->CTRLC.reg;
  Serial.printf("  CTRLC: 0x%x sdasetup=%d data32b=%d\n", 
                ctrlc.reg, ctrlc.bit.SDASETUP, ctrlc.bit.DATA32B);
  
  SERCOM_I2CS_INTENSET_Type intenset;
  intenset.reg = sci->INTENSET.reg;
  Serial.printf("  INTENSET: 0x%x prec=%d amatch=%d drdy=%d error=%d\n",
                intenset.reg, intenset.bit.PREC, intenset.bit.AMATCH, intenset.bit.DRDY,
                intenset.bit.ERROR);
  
  SERCOM_I2CS_INTFLAG_Type intflag;
  intflag.reg = sci->INTFLAG.reg;
  Serial.printf("  INTFLAG: 0x%x prec=%d amatch=%d drdy=%d error=%d\n",
                intflag.reg, intflag.bit.PREC, intflag.bit.AMATCH, intflag.bit.DRDY,
                intflag.bit.ERROR);
  
  SERCOM_I2CS_STATUS_Type status;
  status.reg = sci->STATUS.reg;
  Serial.printf("  STATUS: 0x%x buserr=%d coll=%d rxnack=%d dir=%d sr=%d ",
                status.reg, status.bit.BUSERR, status.bit.COLL, status.bit.RXNACK,
                status.bit.DIR, status.bit.SR);
  Serial.printf("lowtout=%d clkhold=%d sexttout=%d hs=%d lenerr=%d\n",
                status.bit.LOWTOUT, status.bit.CLKHOLD, status.bit.SEXTTOUT,
                status.bit.HS, status.bit.LENERR);
  
  SERCOM_I2CS_SYNCBUSY_Type sb;
  sb.reg = sci->SYNCBUSY.reg;
  Serial.printf("  SYNCBUSY: 0x%x swrst=%d enable=%d length=%d\n",
                sb.reg, sb.bit.SWRST, sb.bit.ENABLE, sb.bit.LENGTH);
  
  SERCOM_I2CS_LENGTH_Type len;
  len.reg = sci->LENGTH.reg;
  Serial.printf("  LENGTH: 0x%x length=%d lenen=%d\n", len.reg, len.bit.LEN, len.bit.LENEN);
  
  SERCOM_I2CS_ADDR_Type addr;
  addr.reg = sci->ADDR.reg;
  Serial.printf("  ADDR: 0x%x gencen=%d addr 0x%x (%d) tenbiten=%d addrmask 0x%x (%d)\n",
                addr.reg, addr.bit.GENCEN, addr.bit.ADDR, addr.bit.ADDR, addr.bit.TENBITEN,
                addr.bit.ADDRMASK, addr.bit.ADDRMASK);
  
  SERCOM_I2CS_DATA_Type data;
  data.reg = sci->DATA.reg;
  Serial.printf("  DATA: 0x%x (%d)\n", data.reg, data.reg);
}

/*
 * Dump a SERCOM/I2C controller instance.
 */
void SAMD51_Dumpster::dumpSercomI2cm(SercomI2cm* sci) {
  SERCOM_I2CM_CTRLA_Type ctrla;
  ctrla.reg = sci->CTRLA.reg;
  Serial.printf("  CTRLA: 0x%x swrst %d enable %d mode %d runstdby %d ",
                ctrla.reg, ctrla.bit.SWRST, ctrla.bit.ENABLE, ctrla.bit.MODE, ctrla.bit.RUNSTDBY);
  Serial.printf("pinout=%d sdahold=%d \n", ctrla.bit.PINOUT, ctrla.bit.SDAHOLD);
  Serial.printf("         mexttoen=%d sexttoen=%d speed=%d sclsm=%d inactout=%d lowtouten=%d\n",
                ctrla.bit.MEXTTOEN, ctrla.bit.SEXTTOEN, ctrla.bit.SPEED, ctrla.bit.SCLSM,
                ctrla.bit.INACTOUT, ctrla.bit.LOWTOUTEN);
                
  SERCOM_I2CM_CTRLB_Type ctrlb;
  ctrlb.reg = sci->CTRLB.reg;
  Serial.printf("  CTRLB: 0x%x smen=%d qcen=%d cmd=%d ackact=%d\n",
                ctrlb.reg, ctrlb.bit.SMEN, ctrlb.bit.QCEN, ctrlb.bit.CMD, ctrlb.bit.ACKACT);
  
  SERCOM_I2CM_CTRLC_Type ctrlc;
  ctrlc.reg = sci->CTRLC.reg;
  Serial.printf("  CTRLC: 0x%x  data32b=%d\n", ctrlc.reg, ctrlc.bit.DATA32B);
  
  SERCOM_I2CM_BAUD_Type baud;
  baud.reg = sci->BAUD.reg;
  Serial.printf("  BAUD: 0x%x baud=%d baudlow=%d hsbaud=%d hsbaudlow=%d\n",
                baud.reg, baud.bit.BAUD, baud.bit.BAUDLOW, baud.bit.HSBAUD, baud.bit.HSBAUDLOW);
  
  SERCOM_I2CM_INTENSET_Type intenset;
  intenset.reg = sci->INTENSET.reg;
  Serial.printf("  INTENSET: 0x%x mb=%d sb=%d error=%d\n",
                intenset.reg, intenset.bit.MB, intenset.bit.SB, intenset.bit.ERROR);
  
  SERCOM_I2CM_INTFLAG_Type intflag;
  intflag.reg = sci->INTFLAG.reg;
  Serial.printf("  INTFLAG: 0x%x mb=%d sb=%d error=%d\n",
                intflag.reg, intflag.bit.MB, intflag.bit.SB, intflag.bit.ERROR);
  
  SERCOM_I2CM_STATUS_Type status;
  status.reg = sci->STATUS.reg;
  Serial.printf("  STATUS: 0x%x buserr=%d arblost=%d rxnack=%d busstate=%d [%s] ",
                status.reg, status.bit.BUSERR, status.bit.ARBLOST, status.bit.RXNACK,
                status.bit.BUSSTATE, i2cmBusState[status.bit.BUSSTATE]);
  Serial.printf("lowtout=%d clkhold=%d mexttout=%d sexttout=%d lenerr=%d\n",
                status.bit.LOWTOUT, status.bit.CLKHOLD, status.bit.MEXTTOUT,
                status.bit.SEXTTOUT, status.bit.LENERR);
  
  SERCOM_I2CM_SYNCBUSY_Type sb;
  sb.reg = sci->SYNCBUSY.reg;
  Serial.printf("  SYNCBUSY: 0x%x swrst=%d enable=%d sysop=%d\n",
                sb.reg, sb.bit.SWRST, sb.bit.ENABLE, sb.bit.SYSOP);
  
  SERCOM_I2CM_ADDR_Type addr;
  addr.reg = sci->ADDR.reg;
  Serial.printf("  ADDR: 0x%x addr 0x%x (%d) lenen=%d hs=%d tenbiten=%d len=%d\n",
                addr.reg, addr.bit.ADDR, addr.bit.ADDR, addr.bit.LENEN,
                addr.bit.HS, addr.bit.TENBITEN, addr.bit.LEN);
  
  SERCOM_I2CM_DATA_Type data;
  data.reg = sci->DATA.reg;
  Serial.printf("  DATA: 0x%x (%d)\n", data.reg, data.reg);
  
  Serial.printf("  DBGCTRL: 0x%x dbgstop=%d\n", sci->DBGCTRL.reg, sci->DBGCTRL.bit.DBGSTOP);
}

/*
 * Dumps all the TCC instances.
 */
void SAMD51_Dumpster::dumpTCC(const char* msg) {
  Serial.printf("\nTCC:");
  if (msg != NULL) {
    Serial.printf(" %s", msg);
  }
  Serial.printf("\n");
  
  for (int i = 0; i < TCC_INST_NUM; i++) {
    dumpTccInstance(i);
  }
}

/*
 * Gets a pointer to the given TCC instance number, and calls the method for dumping
 * that revision of TCC instance.  This allows handling the various flavors of TCC
 * instances that have existed over the evolution of SAM processors.
 */
void SAMD51_Dumpster::dumpTccInstance(int n) {
  Tcc* instances[] = TCC_INSTS;
  Tcc* tcc = instances[n];
  int ccNum = tccCcNum[n];
  
  if (tcc->CTRLA.bit.ENABLE || verbose) {

    Serial.printf("TCC%d: ", n);
    
#if REV_TCC == 0x310
    dumpTccInstance310(tcc, ccNum);
#else
    Serial.printf("TCC version 0x%x not supported\n", REV_TCC);
#endif

  }
}

#if REV_TCC == 0x310
void SAMD51_Dumpster::dumpTccInstance310(Tcc* tcc, int ccNum) {
  int prescalerVal[] = {1, 2, 4, 8, 16, 64, 256, 1024};
  TCC_CTRLA_Type ctrla;
  ctrla.reg = tcc->CTRLA.reg;

  Serial.printf("CTRLA=0x%x swrst=%d en=%d eres=%d ",
                ctrla.reg, ctrla.bit.SWRST, ctrla.bit.ENABLE, ctrla.bit.RESOLUTION);
  Serial.printf("prescaler=%d [div %d] runstdby=%d prescsync=%d ",
                ctrla.bit.PRESCALER, prescalerVal[ctrla.bit.PRESCALER], ctrla.bit.RUNSTDBY,
                ctrla.bit.PRESCSYNC);
  Serial.printf("alock=%d msync=%d dmaos=%d cpten=[%d,%d,%d,%d,%d,%d]\n",
                ctrla.bit.ALOCK, ctrla.bit.MSYNC, ctrla.bit.DMAOS, ctrla.bit.CPTEN0,
                ctrla.bit.CPTEN1, ctrla.bit.CPTEN2, ctrla.bit.CPTEN3, ctrla.bit.CPTEN4,
                ctrla.bit.CPTEN5);
                
  TCC_CTRLBSET_Type ctrlb;
  ctrlb.reg = tcc->CTRLBSET.reg;
  Serial.printf("      CTRLB=0x%x dir=%d [%s] lupd=%d oneshot=%d idxcmd=%d cmd=%d\n",
                ctrlb.reg, ctrlb.bit.DIR, ctrlb.bit.DIR == 0 ? "+" : "-", ctrlb.bit.LUPD,
                ctrlb.bit.ONESHOT, ctrlb.bit.IDXCMD, ctrlb.bit.CMD);
                
  TCC_FCTRLA_Type fctrl;
  fctrl.reg = tcc->FCTRLA.reg;
  Serial.printf("      FCTRLA=0x%x src=%d keep=%d qual=%d blank=%d restart=%d ",
                fctrl.reg, fctrl.bit.SRC, fctrl.bit.KEEP, fctrl.bit.QUAL, fctrl.bit.BLANK,
                fctrl.bit.RESTART);
  Serial.printf("halt=%d chsel=%d capture=%d blankpresc=%d ",
                fctrl.bit.HALT, fctrl.bit.CHSEL, fctrl.bit.CAPTURE, fctrl.bit.BLANKPRESC);
  Serial.printf("blankval=%d filterval=%d\n",
                fctrl.bit.BLANKVAL, fctrl.bit.FILTERVAL);
                
  fctrl.reg = tcc->FCTRLB.reg;
  Serial.printf("      FCTRLB=0x%x src=%d keep=%d qual=%d blank=%d restart=%d ",
                fctrl.reg, fctrl.bit.SRC, fctrl.bit.KEEP, fctrl.bit.QUAL, fctrl.bit.BLANK,
                fctrl.bit.RESTART);
  Serial.printf("halt=%d chsel=%d capture=%d blankpresc=%d ",
                fctrl.bit.HALT, fctrl.bit.CHSEL, fctrl.bit.CAPTURE, fctrl.bit.BLANKPRESC);
  Serial.printf("blankval=%d filterval=%d\n",
                fctrl.bit.BLANKVAL, fctrl.bit.FILTERVAL);
  
  TCC_WEXCTRL_Type wexctrl;
  wexctrl.reg = tcc->WEXCTRL.reg;
  Serial.printf("      WEXCTRL=0x%x otmx=%d dtie=[%d,%d,%d,%d], dtls=%d dths=%d\n",
                wexctrl.reg, wexctrl.bit.OTMX, wexctrl.bit.DTIEN0, wexctrl.bit.DTIEN1,
                wexctrl.bit.DTIEN2, wexctrl.bit.DTIEN3, wexctrl.bit.DTLS, wexctrl.bit.DTHS);
  
  TCC_DRVCTRL_Type drvctrl;
  drvctrl.reg = tcc->DRVCTRL.reg;
  Serial.printf("      DRVCTRL=0x%x nre=[%d,%d,%d,%d,%d,%d,%d,%d] ",
                drvctrl.reg, drvctrl.bit.NRE0, drvctrl.bit.NRE1, drvctrl.bit.NRE2, drvctrl.bit.NRE3,
                drvctrl.bit.NRE4, drvctrl.bit.NRE5, drvctrl.bit.NRE6, drvctrl.bit.NRE7);
  Serial.printf("nrv=[%d,%d,%d,%d,%d,%d,%d,%d] ",
                drvctrl.bit.NRV0, drvctrl.bit.NRV1, drvctrl.bit.NRV2, drvctrl.bit.NRV3,
                drvctrl.bit.NRV4, drvctrl.bit.NRV5, drvctrl.bit.NRV6, drvctrl.bit.NRV7);
  Serial.printf("inven=[%d,%d,%d,%d,%d,%d,%d,%d] filterval0=%d filterval1=%d\n",
                drvctrl.bit.INVEN0, drvctrl.bit.INVEN1, drvctrl.bit.INVEN2, drvctrl.bit.INVEN3,
                drvctrl.bit.INVEN4, drvctrl.bit.INVEN5, drvctrl.bit.INVEN6, drvctrl.bit.INVEN7,
                drvctrl.bit.FILTERVAL0, drvctrl.bit.FILTERVAL1);

  TCC_DBGCTRL_Type dbgctrl;
  dbgctrl.reg = tcc->DBGCTRL.reg;
  Serial.printf("      DBGCTRL=0x%x dbgrun=%d fddbg=%d\n",
                dbgctrl.reg, dbgctrl.bit.DBGRUN, dbgctrl.bit.FDDBD);
  
  TCC_EVCTRL_Type evctrl;
  evctrl.reg = tcc->EVCTRL.reg;
  Serial.printf("      EVCTRL=0x%x evact0=%d evact1=%d cntsel=%d ovfeo=%d trgeo=%d cnteo=%d ",
                evctrl.reg, evctrl.bit.EVACT0, evctrl.bit.EVACT1, evctrl.bit.CNTSEL,
                evctrl.bit.OVFEO, evctrl.bit.TRGEO, evctrl.bit.CNTEO);
  Serial.printf("tcinv0=%d tcinv1=%d tcei0=%d tcei1=%d ",
                evctrl.bit.TCINV0, evctrl.bit.TCINV1, evctrl.bit.TCEI0, evctrl.bit.TCEI1);
  Serial.printf("mcei=[%d,%d,%d,%d,%d,%d] mceo=[%d,%d,%d,%d,%d,%d]\n",
                evctrl.bit.MCEI0, evctrl.bit.MCEI1, evctrl.bit.MCEI2, evctrl.bit.MCEI3,
                evctrl.bit.MCEI4, evctrl.bit.MCEI5, evctrl.bit.MCEO0, evctrl.bit.MCEO1,
                evctrl.bit.MCEO2, evctrl.bit.MCEO3, evctrl.bit.MCEO4, evctrl.bit.MCEO5);

  TCC_INTENSET_Type intenset;
  intenset.reg = tcc->INTENSET.reg;
  Serial.printf("      INTENSET=0x%x  ovf=%d trg=%d cnt=%d err=%d ufs=%d dfs=%d ",
                intenset.reg, intenset.bit.OVF, intenset.bit.TRG, intenset.bit.CNT,
                intenset.bit.ERR, intenset.bit.UFS, intenset.bit.DFS);
  Serial.printf("faulta=%d faultb=%d fault0=%d fault1=%d, mc=[%d,%d,%d,%d,%d,%d]\n",
                intenset.bit.FAULTA, intenset.bit.FAULTB, intenset.bit.FAULT0, intenset.bit.FAULT1,
                intenset.bit.MC0, intenset.bit.MC1, intenset.bit.MC2, intenset.bit.MC3,
                intenset.bit.MC4, intenset.bit.MC5);

  TCC_INTFLAG_Type intflag;
  intflag.reg = tcc->INTFLAG.reg;
  Serial.printf("      INTFLAG=0x%x  ovf=%d trg=%d cnt=%d err=%d ufs=%d dfs=%d ",
                intflag.reg, intflag.bit.OVF, intflag.bit.TRG, intflag.bit.CNT,
                intflag.bit.ERR, intflag.bit.UFS, intflag.bit.DFS);
  Serial.printf("faulta=%d faultb=%d fault0=%d fault1=%d, mc=[%d,%d,%d,%d,%d,%d]\n",
                intflag.bit.FAULTA, intflag.bit.FAULTB, intflag.bit.FAULT0, intflag.bit.FAULT1,
                intflag.bit.MC0, intflag.bit.MC1, intflag.bit.MC2, intflag.bit.MC3,
                intflag.bit.MC4, intflag.bit.MC5);

  TCC_STATUS_Type status;
  status.reg = tcc->STATUS.reg;
  Serial.printf("      STATUS=0x%x  stop=%d idx=%d ufs=%d dfs=%d slave=%d pattbufv=%d perbufv=%d ",
                status.reg, status.bit.STOP, status.bit.IDX, status.bit.UFS, status.bit.DFS,
                status.bit.SLAVE, status.bit.PATTBUFV, status.bit.PERBUFV);
  Serial.printf("faultin[AB01]=[%d,%d,%d,%d] fault[AB01]=[%d,%d,%d,%d] ",
                status.bit.FAULTAIN, status.bit.FAULTBIN, status.bit.FAULT0IN, status.bit.FAULT1IN,
                status.bit.FAULTA, status.bit.FAULTB, status.bit.FAULT0, status.bit.FAULT1);
  Serial.printf("ccbufv=[%d,%d,%d,%d,%d,%d] cmp=[%d,%d,%d,%d,%d,%d]\n",
                status.bit.CCBUFV0, status.bit.CCBUFV1, status.bit.CCBUFV2, status.bit.CCBUFV3,
                status.bit.CCBUFV4, status.bit.CCBUFV5, status.bit.CMP0, status.bit.CMP1,
                status.bit.CMP2, status.bit.CMP3, status.bit.CMP4, status.bit.CMP5);

  TCC_PATT_Type patt;
  patt.reg = tcc->PATT.reg;
  Serial.printf("      PATT=0x%x     pge=[%d,%d,%d,%d,%d,%d,%d,%d] pgv=[%d,%d,%d,%d,%d,%d,%d,%d]\n",
                patt.reg, patt.bit.PGE0, patt.bit.PGE1, patt.bit.PGE2, patt.bit.PGE3,
                patt.bit.PGE4, patt.bit.PGE5, patt.bit.PGE6, patt.bit.PGE7,
                patt.bit.PGE0, patt.bit.PGE1, patt.bit.PGE2, patt.bit.PGE3,
                patt.bit.PGE4, patt.bit.PGE5, patt.bit.PGE6, patt.bit.PGE7);

  patt.reg = tcc->PATTBUF.reg;
  Serial.printf("      PATTBUF=0x%x  pge=[%d,%d,%d,%d,%d,%d,%d,%d] pgv=[%d,%d,%d,%d,%d,%d,%d,%d]\n",
                patt.reg, patt.bit.PGE0, patt.bit.PGE1, patt.bit.PGE2, patt.bit.PGE3,
                patt.bit.PGE4, patt.bit.PGE5, patt.bit.PGE6, patt.bit.PGE7,
                patt.bit.PGE0, patt.bit.PGE1, patt.bit.PGE2, patt.bit.PGE3,
                patt.bit.PGE4, patt.bit.PGE5, patt.bit.PGE6, patt.bit.PGE7);

  TCC_WAVE_Type wave;
  wave.reg = tcc->WAVE.reg;
  Serial.printf("      WAVE=0x%x  wavegen=%d [%s] ramp=%d ciperen=%d ciccen=[%d,%d,%d,%d] ",
                wave.reg, wave.bit.WAVEGEN, tccWaveGenNames[wave.bit.WAVEGEN], wave.bit.RAMP,
                wave.bit.CIPEREN, wave.bit.CICCEN0, wave.bit.CICCEN1, wave.bit.CICCEN2,
                wave.bit.CICCEN3);
  Serial.printf("pol=[%d,%d,%d,%d,%d,%d] swap=[%d,%d,%d,%d]\n",
                wave.bit.POL0, wave.bit.POL1, wave.bit.POL2, wave.bit.POL3, wave.bit.POL4,
                wave.bit.POL5, wave.bit.SWAP0, wave.bit.SWAP1, wave.bit.SWAP2, wave.bit.SWAP3);
                
  TCC_COUNT_Type count;
  count.reg = tcc->COUNT.reg;
  Serial.printf("      COUNT=0x%x  count=%d\n", count.reg, count.reg);

  TCC_CC_Type xx;
  TCC_CCBUF_Type xxbuf;
  
  // TODO: Fix the following formatting to handle dithering
  
  xx.reg = tcc->PER.reg;
  xxbuf.reg = tcc->PERBUF.reg;
  Serial.printf("      PER=0x%x  val=%d BUF val=%d\n", xx.reg, xx.bit.CC, xxbuf.bit.CCBUF);
  
  for (int i = 0; i < ccNum; i++) {
    xx.reg = tcc->CC[i].reg;
    xxbuf.reg = tcc->CCBUF[i].reg;
    Serial.printf("      CC%d=0x%x  val=%d BUF val=%d\n", i, xx.reg, xx.bit.CC, xxbuf.bit.CCBUF);
  }
  
}
#endif

/*
 * Dumps all the TC instances.
 */
void SAMD51_Dumpster::dumpTC(const char* msg) {
  Serial.printf("\nTC:");
  if (msg != NULL) {
    Serial.printf(" %s", msg);
  }
  Serial.printf("\n");

  for (int i = 0; i < TC_INST_NUM; i++) {
    dumpTcInstance(i);
  }
}

/*
 * Dump most registers of a TC instance.
 */
void SAMD51_Dumpster::dumpTcInstance(int n) {
  if (n < 0 || n >= TC_INST_NUM) {
    Serial.printf("TC instance num out of range: n=%d\n", n);
    return;
  }
  Tc* tcInstances[] = TC_INSTS;
  Tc* tc = tcInstances[n];
  uint8_t en = tc->COUNT16.CTRLA.bit.ENABLE;
  if (en || verbose) {
    Serial.printf("\nTC%d:\n", n);
    Serial.printf("  CTRLA 0x%x (swrst=%d en=%d mode=%d presync=%d runstdby=%d ondemand=%d\n",
                  tc->COUNT16.CTRLA.reg, tc->COUNT16.CTRLA.bit.SWRST, en, tc->COUNT16.CTRLA.bit.MODE,
                  tc->COUNT16.CTRLA.bit.PRESCSYNC, tc->COUNT16.CTRLA.bit.RUNSTDBY, tc->COUNT16.CTRLA.bit.ONDEMAND);
    uint8_t tmp8 = tc->COUNT16.CTRLA.bit.PRESCALER;
    Serial.printf("              prescalar=%d [%d] alock=%d capten=%d,%d copen=%d,%d captmode=%d,%d\n",
                  tmp8, tcPrescalars[tmp8], tc->COUNT16.CTRLA.bit.ALOCK,
                  tc->COUNT16.CTRLA.bit.CAPTEN0, tc->COUNT16.CTRLA.bit.CAPTEN1,
                  tc->COUNT16.CTRLA.bit.COPEN0, tc->COUNT16.CTRLA.bit.COPEN1,
                  tc->COUNT16.CTRLA.bit.CAPTMODE0, tc->COUNT16.CTRLA.bit.CAPTMODE1);
    Serial.printf("  CTRLB 0x%x (dir=%d lupd=%d oneshot=%d cmd=%d)\n",
                  tc->COUNT16.CTRLBSET.reg, tc->COUNT16.CTRLBSET.bit.DIR, tc->COUNT16.CTRLBSET.bit.LUPD,
                  tc->COUNT16.CTRLBSET.bit.ONESHOT, tc->COUNT16.CTRLBSET.bit.CMD);
    Serial.printf("  EVCTRL 0x%x (evact=%d tcinv=%d tcei=%d ovfeo=%d mceo0=%d mceo1=%d)\n",
                  tc->COUNT16.EVCTRL.reg, tc->COUNT16.EVCTRL.bit.EVACT, tc->COUNT16.EVCTRL.bit.TCINV,
                  tc->COUNT16.EVCTRL.bit.TCEI, tc->COUNT16.EVCTRL.bit.OVFEO,
                  tc->COUNT16.EVCTRL.bit.MCEO0, tc->COUNT16.EVCTRL.bit.MCEO1);
    Serial.printf("  INTENSET 0x%x (ovf=%d err=%d mc0=%d mc1=%d)\n",
                  tc->COUNT16.INTENSET.reg, tc->COUNT16.INTENSET.bit.OVF, tc->COUNT16.INTENSET.bit.ERR,
                  tc->COUNT16.INTENSET.bit.MC0, tc->COUNT16.INTENSET.bit.MC1);
    Serial.printf("  INTFLAG 0x%x (ovf=%d err=%d mc0=%d mc1=%d)\n",
                  tc->COUNT16.INTFLAG.reg, tc->COUNT16.INTFLAG.bit.OVF, tc->COUNT16.INTFLAG.bit.ERR,
                  tc->COUNT16.INTFLAG.bit.MC0, tc->COUNT16.INTFLAG.bit.MC1);
    Serial.printf("  STATUS 0x%x (stop=%d slave=%d perbufv=%d ccbufv0=%d ccbufv1=%d)\n",
                  tc->COUNT16.STATUS.reg, tc->COUNT16.STATUS.bit.STOP, tc->COUNT16.STATUS.bit.SLAVE,
                  tc->COUNT16.STATUS.bit.PERBUFV, tc->COUNT16.STATUS.bit.CCBUFV0, tc->COUNT16.STATUS.bit.CCBUFV1);
    Serial.printf("  WAVE 0x%x (%s)\n", tc->COUNT16.WAVE.reg, tcWaves[tc->COUNT16.WAVE.bit.WAVEGEN]);
    Serial.printf("  DRVCTRL 0x%x (inven0=%d inven1=%d)\n",
                  tc->COUNT16.DRVCTRL.reg, tc->COUNT16.DRVCTRL.bit.INVEN0, tc->COUNT16.DRVCTRL.bit.INVEN1);
    Serial.printf("  DBGCTRL 0x%x (dbgrun=%d)\n",
                  tc->COUNT16.DBGCTRL.reg, tc->COUNT16.DBGCTRL.bit.DBGRUN);
    Serial.printf("  COUNT 0x%x (%d)  CC0 0x%x (%d) CC1 0x%x (%d)  CCBUF0 0x%x (%d) CCBUF1 0x%x (%d)\n\n",
                  tc->COUNT16.COUNT.reg, tc->COUNT16.COUNT.reg,
                  tc->COUNT16.CC[0].reg, tc->COUNT16.CC[0].reg,
                  tc->COUNT16.CC[1].reg, tc->COUNT16.CC[1].reg,
                  tc->COUNT16.CCBUF[0].reg, tc->COUNT16.CCBUF[0].reg,
                  tc->COUNT16.CCBUF[1].reg, tc->COUNT16.CCBUF[1].reg);
  }
}
  
/*
 * Dumps the EVSYS entries.
 */
void SAMD51_Dumpster::dumpEVSYS(const char* msg) {
  Serial.printf("\nEVSYS: ");
  if (msg != NULL) {
    Serial.printf(" %s", msg);
  }
  Serial.printf("\n");

  EVSYS_CTRLA_Type ctrla;
  ctrla.reg = EVSYS->CTRLA.reg;
  EVSYS_PRICTRL_Type prictrl;
  prictrl.reg = EVSYS->PRICTRL.reg;
  Serial.printf("EVSYS: CNTRLA=0x%x swrst=%d PRICTRL=0x%x pri=%d rren=%d\n",
                 ctrla.reg, ctrla.bit.SWRST, prictrl.reg, prictrl.bit.PRI, prictrl.bit.RREN);

  EVSYS_INTPEND_Type intpend;
  intpend.reg = EVSYS->INTPEND.reg;
  Serial.printf("       INTPEND=0x%x id=%d ovr=%d evd=%d ready=%d busy=%d\n",
                intpend.reg, intpend.bit.ID, intpend.bit.OVR, intpend.bit.EVD, intpend.bit.READY,
                intpend.bit.BUSY);
  
  EVSYS_INTSTATUS_Type intstatus;
  intstatus.reg = EVSYS->INTSTATUS.reg;
  Serial.printf("       INTSTATUS=0x%03x ch=[%d,%d,%d,%d, %d,%d,%d,%d, %d,%d,%d,%d]\n",
                intstatus.reg,
                intstatus.bit.CHINT0, intstatus.bit.CHINT1, intstatus.bit.CHINT2, 
                intstatus.bit.CHINT3, intstatus.bit.CHINT4, intstatus.bit.CHINT5,
                intstatus.bit.CHINT6, intstatus.bit.CHINT7, intstatus.bit.CHINT8, 
                intstatus.bit.CHINT9, intstatus.bit.CHINT10, intstatus.bit.CHINT11);
  
  EVSYS_BUSYCH_Type busych;
  busych.reg = EVSYS->BUSYCH.reg;
  Serial.printf("       BUSYCH=0x%03x    ch=[%d,%d,%d,%d, %d,%d,%d,%d, %d,%d,%d,%d]\n",
                busych.reg,
                busych.bit.BUSYCH0, busych.bit.BUSYCH1, busych.bit.BUSYCH2, 
                busych.bit.BUSYCH3, busych.bit.BUSYCH4, busych.bit.BUSYCH5, 
                busych.bit.BUSYCH6, busych.bit.BUSYCH7, busych.bit.BUSYCH8, 
                busych.bit.BUSYCH9, busych.bit.BUSYCH10, busych.bit.BUSYCH11);

  EVSYS_READYUSR_Type readyusr;
  readyusr.reg = EVSYS->READYUSR.reg;
  Serial.printf("       READYUSR=0x%03x  ch=[%d,%d,%d,%d, %d,%d,%d,%d, %d,%d,%d,%d]\n",
                readyusr.reg,
                readyusr.bit.READYUSR0, readyusr.bit.READYUSR1, readyusr.bit.READYUSR2, 
                readyusr.bit.READYUSR3, readyusr.bit.READYUSR4, readyusr.bit.READYUSR5, 
                readyusr.bit.READYUSR6, readyusr.bit.READYUSR7, readyusr.bit.READYUSR8, 
                readyusr.bit.READYUSR9, readyusr.bit.READYUSR10, readyusr.bit.READYUSR11);
                
  for (int i = 0; i < EVSYS_CHANNELS; i++) {
    dumpEvChannel(i);
  }
  
  for (int i = 0; i < EVSYS_USERS; i++) {
    dumpEvUser(i);
  }
}

/*
 * Dumps a single event channel.
 */
void SAMD51_Dumpster::dumpEvChannel(int chNum) {
  EvsysChannel *ch = &(EVSYS->Channel[chNum]);
  
  EVSYS_CHANNEL_Type channel;
  channel.reg = ch->CHANNEL.reg;
  
  if (channel.bit.EVGEN > 0 || verbose) {
    Serial.printf("       CH[%2d] evgen=%d [%s] path=%d [%d] edgsel=%d runstdby=%d ondemand=%d ",
                  chNum, channel.bit.EVGEN, evGenNames[channel.bit.EVGEN], channel.bit.PATH,
                  evPathNames[channel.bit.PATH], channel.bit.EDGSEL, channel.bit.RUNSTDBY,
                  channel.bit.ONDEMAND);
                
    if (chNum < 12) {
      EVSYS_CHINTENSET_Type chintset;
      chintset.reg = ch->CHINTENSET.reg;
      EVSYS_CHINTFLAG_Type chintflag;
      chintflag.reg = ch->CHINTFLAG.reg;
      EVSYS_CHSTATUS_Type chstatus;
      chstatus.reg = ch->CHSTATUS.reg;
      Serial.printf("intset[ovr=%d evd=%d] intflag[ovr=%d evd=%d] status[rdyusr=%d busych=%d]",
                    chintset.bit.OVR, chintset.bit.EVD, chintflag.bit.OVR, chintflag.bit.EVD,
                    chstatus.bit.RDYUSR, chstatus.bit.BUSYCH);
    }
    Serial.printf("\n");
    int foundUser = 0;
    for (int i = 0; i < EVSYS_USERS; i++) {
      EVSYS_USER_Type user;
      user.reg = EVSYS->USER[i].reg;
      if (user.bit.CHANNEL == chNum) {
        char prefix[32] = ", ";
        if (!foundUser) {
          foundUser = 1;
          strcpy(prefix, "           USERS: ");
        }
        Serial.printf("%s%s", prefix, evUserNames[i]);
      }
      if (foundUser) {
        Serial.printf("\n");
      }
    }
  }
}

/*
 * Dumps a single event user.
 */
void SAMD51_Dumpster::dumpEvUser(int userNum) {
  EVSYS_USER_Type user;
  user.reg = EVSYS->USER[userNum].reg;
  if (user.bit.CHANNEL > 0 || verbose) {
    Serial.printf("       USER %d [%s] channel %d\n",
                  userNum, evUserNames[userNum], user.bit.CHANNEL);
  }
}

/*
 * Dumps the DMAC (Direct Memory Access Controller).
 */
void SAMD51_Dumpster::dumpDMAC(const char* msg) {
  Serial.printf("\nDMAC:");
  if (msg != NULL) {
    Serial.printf(" %s", msg);
  }
  Serial.printf("\n");

  DMAC_CTRL_Type ctrl;
  ctrl.reg = DMAC->CTRL.reg;
  Serial.printf("DMAC: CNTRL=0x%x swrst=%d en=%d lvlen=[%d,%d,%d,%d]\n",
                 ctrl.reg, ctrl.bit.SWRST, ctrl.bit.DMAENABLE, ctrl.bit.LVLEN0, ctrl.bit.LVLEN1,
                 ctrl.bit.LVLEN2, ctrl.bit.LVLEN3);

  DMAC_CRCCTRL_Type crcctrl;
  crcctrl.reg = DMAC->CRCCTRL.reg;
  Serial.printf("      CRCCTRL=0x%x beatsize=%d [%d bytes] poly=%d [%s] ",
                 crcctrl.reg, crcctrl.bit.CRCBEATSIZE, beatSizes[crcctrl.bit.CRCBEATSIZE],
                 crcctrl.bit.CRCPOLY, crcPolyNames[crcctrl.bit.CRCPOLY]);
  Serial.printf("src=%d [%s] mode=%d [%s]\n",
                 crcctrl.bit.CRCSRC, crcSrcNames[crcctrl.bit.CRCSRC], crcctrl.bit.CRCMODE,
                 crcModeNames[crcctrl.bit.CRCMODE]);

  DMAC_CRCDATAIN_Type datain;
  DMAC_CRCCHKSUM_Type chksum;
  DMAC_CRCSTATUS_Type status;
  datain.reg = DMAC->CRCDATAIN.reg;
  chksum.reg = DMAC->CRCCHKSUM.reg;
  status.reg = DMAC->CRCSTATUS.reg;
  Serial.printf("      CRCSTATUS=0x%x busy=%d zero=%d err=%d CRCDATAIN=0x%x CRCCHKSUM=0x%x\n",
                 status.reg, status.bit.CRCBUSY, status.bit.CRCZERO, status.bit.CRCERR,
                 datain.bit.CRCDATAIN, chksum.bit.CRCCHKSUM);

  DMAC_DBGCTRL_Type dbgctrl;
  dbgctrl.reg = DMAC->DBGCTRL.reg;
  Serial.printf("      DBGCTRL=0x%x dbgrun=%d\n", dbgctrl.reg, dbgctrl.bit.DBGRUN);
  
  DMAC_SWTRIGCTRL_Type swtrig;
  swtrig.reg = DMAC->SWTRIGCTRL.reg;
  Serial.printf("      SWTRIGCTRL=0x%x ch=[", swtrig.reg);
  dumpArray(swtrig.reg, 32);
  Serial.printf("]\n");

  DMAC_PRICTRL0_Type prictrl;
  prictrl.reg = DMAC->PRICTRL0.reg;
  Serial.printf("      PRICTRL=0x%x ", prictrl.reg);
  Serial.printf("lvlpri0=%d qos0=%d [%s] rren0=%d ",
                prictrl.bit.LVLPRI0, prictrl.bit.QOS0, priQosNames[prictrl.bit.QOS0],
                prictrl.bit.RRLVLEN0);
  Serial.printf("lvlpri1=%d qos1=%d [%s] rren1=%d\n",
                prictrl.bit.LVLPRI1, prictrl.bit.QOS1, priQosNames[prictrl.bit.QOS1],
                prictrl.bit.RRLVLEN1);
  Serial.printf("             lvlpri2=%d qos2=%d [%s] rren2=%d ",
                prictrl.bit.LVLPRI2, prictrl.bit.QOS2, priQosNames[prictrl.bit.QOS2],
                prictrl.bit.RRLVLEN2);
  Serial.printf("lvlpri3=%d qos3=%d [%s] rren3=%d\n",
                prictrl.bit.LVLPRI3, prictrl.bit.QOS3, priQosNames[prictrl.bit.QOS3],
                prictrl.bit.RRLVLEN3);

  DMAC_INTPEND_Type intpend;
  intpend.reg = DMAC->INTPEND.reg;
  Serial.printf("      INTPEND=0x%x id=%d terr=%d tcmpl=%d susp=%d crcerr=%d ferr=%d busy=%d pend=%d\n",
                intpend.reg, intpend.bit.ID, intpend.bit.TERR, intpend.bit.TCMPL, intpend.bit.SUSP,
                intpend.bit.CRCERR, intpend.bit.FERR, intpend.bit.BUSY, intpend.bit.PEND);
  
  DMAC_INTSTATUS_Type intstatus;
  intstatus.reg = DMAC->INTSTATUS.reg;
  Serial.printf("      INTSTATUS=0x%x ch=[", intstatus.reg);
  dumpArray(intstatus.reg, 32);
  Serial.printf("]\n");

  DMAC_BUSYCH_Type busych;
  busych.reg = DMAC->BUSYCH.reg;
  Serial.printf("      BUSYCH=0x%x ch=[", busych.reg);
  dumpArray(busych.reg, 32);
  Serial.printf("]\n");

  DMAC_PENDCH_Type pendch;
  pendch.reg = DMAC->PENDCH.reg;
  Serial.printf("      PENDCH=0x%x ch=[", pendch.reg);
  dumpArray(pendch.reg, 32);
  Serial.printf("]\n");

  DMAC_ACTIVE_Type active;
  active.reg = DMAC->ACTIVE.reg;
  Serial.printf("      ACTIVE=0x%x lvlex=[%d,%d,%d,%d] id=%d abusy=%d btcnt=%d\n",
                active.reg, active.bit.LVLEX0, active.bit.LVLEX1, active.bit.LVLEX2,
                active.bit.LVLEX3, active.bit.ID, active.bit.ABUSY, active.bit.BTCNT);
  
  DMAC_BASEADDR_Type baseaddr;
  DMAC_WRBADDR_Type wrbaddr;
  baseaddr.reg = DMAC->BASEADDR.reg;
  wrbaddr.reg = DMAC->WRBADDR.reg;
  Serial.printf("      BASEADDR=0x%x WRBADDR=0x%x\n", baseaddr.reg, wrbaddr.reg);

  for (int i = 0; i < DMAC_CH_NUM; i++) {
    dumpDmacChannel(i);
  }
}

/*
 * Dumps a single DMAC channel.
 */
void SAMD51_Dumpster::dumpDmacChannel(int chNum) {
  DmacChannel *ch = &(DMAC->Channel[chNum]);
  
  DMAC_CHCTRLA_Type ctrla;
  ctrla.reg = ch->CHCTRLA.reg;
  
  if (ctrla.bit.ENABLE || verbose) {
    Serial.printf("        CH[%2d] CTRLA=0x%x swrst=%d en=%d runstdby=%d trigsrc=%d [%s] ",
                  chNum, ctrla.reg, ctrla.bit.SWRST, ctrla.bit.ENABLE, ctrla.bit.RUNSTDBY,
                  ctrla.bit.TRIGSRC, trigSrcNames[ctrla.bit.TRIGSRC]);
    Serial.printf("trigact=%d [%s] burstlen=%d [%d] threshold=%d [%d]\n",
                  ctrla.bit.TRIGACT, trigActNames[ctrla.bit.TRIGACT], ctrla.bit.BURSTLEN,
                  ctrla.bit.BURSTLEN + 1, ctrla.bit.THRESHOLD, thresholdSizes[ctrla.bit.THRESHOLD]);

    DMAC_CHCTRLB_Type ctrlb;
    ctrlb.reg = ch->CHCTRLB.reg;
    Serial.printf("              CTRLB=0x%x cmd=%d [%s]\n",
                  ctrlb.reg, ctrlb.bit.CMD, dmacCmdNames[ctrlb.bit.CMD]);

    DMAC_CHPRILVL_Type prilvl;
    DMAC_CHEVCTRL_Type evctrl;
    prilvl.reg = ch->CHPRILVL.reg;
    evctrl.reg = ch->CHEVCTRL.reg;
    Serial.printf("              CHPRILVL=0x%x EVCTRL=0x%x evact=%d [%s] evomode=%d [%s] ",
                  prilvl.reg, evctrl.reg, evctrl.bit.EVACT, dmacChEvActNames[evctrl.bit.EVACT],
                  evctrl.bit.EVOMODE, dmacChEvOutModeNames[evctrl.bit.EVOMODE]);
    Serial.printf("evie=%d evoe=%d\n", evctrl.bit.EVIE, evctrl.bit.EVOE);

    DMAC_CHINTENSET_Type inten;
    DMAC_CHINTFLAG_Type intflag;
    inten.reg = ch->CHINTENSET.reg;
    intflag.reg = ch->CHINTFLAG.reg;
    Serial.printf("              CHINTEN=0x%x terr=%d tcmpl=%d susp=%d ",
                  inten.reg, inten.bit.TERR, inten.bit.TCMPL, inten.bit.SUSP);
    Serial.printf("CHINTFLAG=0x%x terr=%d tcmpl=%d susp=%d\n",
                  intflag.reg, intflag.bit.TERR, intflag.bit.TCMPL, intflag.bit.SUSP);

    DMAC_CHSTATUS_Type status;
    status.reg = ch->CHSTATUS.reg;
    Serial.printf("              CHSTATUS=0x%x pend=%d busy=%d ferr=%d crcerr=%d\n",
                  status.reg, status.bit.PEND, status.bit.BUSY, status.bit.FERR, status.bit.CRCERR);
  }
  
}
  
/*
 * Dumps a single DMAC descriptor.
 */
void SAMD51_Dumpster::dumpDmacDesc(DmacDescriptor* desc) {
  if (desc == NULL) {
    return;
  }
  
  DMAC_BTCTRL_Type btctrl;
  btctrl.reg = desc->BTCTRL.reg;
  Serial.printf("        DESC[0x%x] BTCTRL=0x%x valid=%d evosel=%d [%s] blockact=%d [%s] ",
                desc, btctrl.reg, btctrl.bit.VALID,
                btctrl.bit.EVOSEL, dmacDescEvoSelNames[btctrl.bit.EVOSEL],
                btctrl.bit.BLOCKACT, dmacDescBlkActNames[btctrl.bit.BLOCKACT]);
  Serial.printf("beatsize=%d [%s bytes] srcinc=%d dstinc=%d stepsel=%d stepsize=%d [%d]\n",
                btctrl.bit.BEATSIZE, beatSizes[btctrl.bit.BEATSIZE], btctrl.bit.SRCINC,
                btctrl.bit.DSTINC, btctrl.bit.STEPSEL, dmacStepSelNames[btctrl.bit.STEPSEL],
                btctrl.bit.STEPSIZE, powersOf2[btctrl.bit.STEPSIZE]);
                
  DMAC_BTCNT_Type btcnt;
  DMAC_SRCADDR_Type srcaddr;
  DMAC_DSTADDR_Type dstaddr;
  DMAC_DESCADDR_Type descaddr;
  btcnt.reg = desc->BTCNT.reg;
  srcaddr.reg = desc->SRCADDR.reg;
  dstaddr.reg = desc->DSTADDR.reg;
  descaddr.reg = desc->DESCADDR.reg;
  Serial.printf("            BTCNT=0x%x [%d] SRCADDR=0x%x DSTADDR=0x%x DESCADDR=0x%x\n",
                btcnt.reg, btcnt.bit.BTCNT, srcaddr.reg, dstaddr.reg, descaddr.reg);
  
}

/*
 * Dumps a comma-separated list of bit values in array format.
 * Leaves an extra space after every 8th value, for better readability.
 */
void SAMD51_Dumpster::dumpArray(uint32_t val, int cnt) {
  for (int i = 1; i <= cnt; i++) {
    Serial.printf("%d", val & 0x1);
    val >>= 1;
    if (i < cnt) {
      Serial.printf(i % 8 == 0 ? ", " : ",");
    }
  }
}

/*
 * Dump the ADC instances.
 */
void SAMD51_Dumpster::dumpADC(const char* msg) {
  Serial.printf("\nADC:");
  if (msg != NULL) {
    Serial.printf(" %s", msg);
  }
  Serial.printf("\n");

  for (int i = 0; i < ADC_INST_NUM; i++) {
    dumpAdcInstance(i);
  }
}

/*
 * Dump the ADC instance with the given index.
 */
void SAMD51_Dumpster::dumpAdcInstance(int n) {
  Adc* adcs[ADC_INST_NUM] = ADC_INSTS;
  Adc* adc = adcs[n];
  
  ADC_CTRLA_Type ctrla;
  ctrla.reg = adc->CTRLA.reg;
  
  if (ctrla.bit.ENABLE || verbose) {
    Serial.printf("ADC%d: CNTRLA=0x%x swrst=%d en=%d dualsel=%d [%s] slaveen=%d ",
                  n, ctrla.reg, ctrla.bit.SWRST, ctrla.bit.ENABLE, ctrla.bit.DUALSEL,
                  adcDualSelNames[ctrla.bit.DUALSEL], ctrla.bit.SLAVEEN);
    Serial.printf("runstdby=%d ondemand=%d prescaler=%d [/%d] r2r=%d\n",
                  ctrla.bit.RUNSTDBY, ctrla.bit.ONDEMAND, ctrla.bit.PRESCALER,
                  adcPrescalerSizes[ctrla.bit.PRESCALER], ctrla.bit.R2R);
                  
    ADC_EVCTRL_Type evctrl;
    evctrl.reg = adc->EVCTRL.reg;
    Serial.printf("      EVCTRL=0x%x flushei=%d startei=%d flushinv=%d startinv=%d ",
                  evctrl.reg, evctrl.bit.FLUSHEI, evctrl.bit.STARTEI, evctrl.bit.FLUSHINV,
                  evctrl.bit.STARTINV);
    Serial.printf("resrdyeo=%d winmoneo=%d\n", evctrl.bit.RESRDYEO, evctrl.bit.WINMONEO);
    
    ADC_DBGCTRL_Type dbgctrl;
    dbgctrl.reg = adc->DBGCTRL.reg;
    Serial.printf("      DBGCTRL=0x%x dbgrun=%d\n", dbgctrl.reg, dbgctrl.bit.DBGRUN);
    
    ADC_INPUTCTRL_Type inputctrl;
    inputctrl.reg = adc->INPUTCTRL.reg;
    Serial.printf("      INPUTCTRL=0x%x muxpos=%d [%s] diffmode=%d muxneg=%d [%s] dseqstop=%d\n",
                  inputctrl.reg, inputctrl.bit.MUXPOS, adcMuxPosNames[inputctrl.bit.MUXPOS],
                  inputctrl.bit.DIFFMODE, inputctrl.bit.MUXNEG,
                  adcMuxNegNames[inputctrl.bit.MUXNEG], inputctrl.bit.DSEQSTOP);
    
    ADC_CTRLB_Type ctrlb;
    ctrlb.reg = adc->CTRLB.reg;
    Serial.printf("      CTRLB=0x%x leftadj=%d freerun=%d corren=%d ressel=%d [%d] ",
                  ctrlb.reg, ctrlb.bit.LEFTADJ, ctrlb.bit.FREERUN, ctrlb.bit.CORREN,
                  ctrlb.bit.RESSEL, adcResSelSizes[ctrlb.bit.RESSEL]);
    Serial.printf("winmode=%d [%s] winss=%d\n",
                  ctrlb.bit.WINMODE, adcWinModeNames[ctrlb.bit.WINMODE], ctrlb.bit.WINSS);

    ADC_REFCTRL_Type refctrl;
    refctrl.reg = adc->REFCTRL.reg;
    Serial.printf("      REFCTRL=0x%x refsel=%d [%s] refcomp=%d\n",
                  refctrl.reg, refctrl.bit.REFSEL, adcRefSelNames[refctrl.bit.REFSEL],
                  refctrl.bit.REFCOMP);

    ADC_AVGCTRL_Type avgctrl;
    avgctrl.reg = adc->AVGCTRL.reg;
    Serial.printf("      AVGCTRL=0x%x samplenum=%d [%d samples] adjres=%d [%d]\n",
                  avgctrl.reg, avgctrl.bit.SAMPLENUM, powersOf2[avgctrl.bit.SAMPLENUM],
                  avgctrl.bit.ADJRES, powersOf2[avgctrl.bit.ADJRES]);

    ADC_SAMPCTRL_Type sampctrl;
    sampctrl.reg = adc->SAMPCTRL.reg;
    Serial.printf("      SAMPCTRL=0x%x samplen=%d offcomp=%d\n",
                  sampctrl.reg, sampctrl.bit.SAMPLEN, sampctrl.bit.OFFCOMP);

    ADC_WINLT_Type winlt;
    ADC_WINUT_Type winut;
    winlt.reg = adc->WINLT.reg;
    winut.reg = adc->WINUT.reg;
    Serial.printf("      WINLT=0x%x (%d) WINUT=0x%x (%d)\n",
                  winlt.reg, winlt.bit.WINLT, winut.reg, winut.bit.WINUT);

    ADC_GAINCORR_Type gaincorr;
    ADC_OFFSETCORR_Type offsetcorr;
    gaincorr.reg = adc->GAINCORR.reg;
    offsetcorr.reg = adc->OFFSETCORR.reg;
    Serial.printf("      GAINCORR=0x%x (%d) OFFSETCORR=0x%x (%d)\n",
                  gaincorr.reg, gaincorr.bit.GAINCORR, offsetcorr.reg, offsetcorr.bit.OFFSETCORR);

    ADC_SWTRIG_Type swtrig;
    swtrig.reg = adc->SWTRIG.reg;
    Serial.printf("      SWTRIG=0x%x flush=%d start=%d\n",
                  swtrig.reg, swtrig.bit.FLUSH, swtrig.bit.START);

    ADC_INTENSET_Type intenset;
    ADC_INTFLAG_Type intflag;
    intenset.reg = adc->INTENSET.reg;
    intflag.reg = adc->INTFLAG.reg;
    Serial.printf("      INTENSET=0x%x resrdy=%d overrun=%d winmon=%d\n",
                  intenset.reg, intenset.bit.RESRDY, intenset.bit.OVERRUN, intenset.bit.WINMON);
    Serial.printf("      INTFLAG=0x%x resrdy=%d overrun=%d winmon=%d\n",
                  intflag.reg, intflag.bit.RESRDY, intflag.bit.OVERRUN, intflag.bit.WINMON);

    ADC_STATUS_Type status;
    status.reg = adc->STATUS.reg;
    Serial.printf("      STATUS=0x%x adcbusy=%d wcc=%d\n",
                  status.reg, status.bit.ADCBUSY, status.bit.WCC);

    ADC_SYNCBUSY_Type syncbusy;
    syncbusy.reg = adc->SYNCBUSY.reg;
    Serial.printf("      SYNCBUSY=0x%x swrst=%d enable=%d inputctrl=%d ctrlb=%d refctrl=%d ",
                  syncbusy.reg, syncbusy.bit.SWRST, syncbusy.bit.ENABLE, syncbusy.bit.INPUTCTRL,
                  syncbusy.bit.CTRLB, syncbusy.bit.REFCTRL);
    Serial.printf("avgctrl=%d sampctrl=%d winlt=%d winut=%d gaincorr=%d offsetcorr=%d swtrig=%d\n",
                  syncbusy.bit.AVGCTRL, syncbusy.bit.SAMPCTRL, syncbusy.bit.WINLT,
                  syncbusy.bit.WINUT, syncbusy.bit.GAINCORR, syncbusy.bit.OFFSETCORR,
                  syncbusy.bit.SWTRIG);

    ADC_DSEQDATA_Type dseqdata;
    dseqdata.reg = adc->DSEQDATA.reg;
    Serial.printf("      DSEQDATA=0x%x (%d)\n", dseqdata.reg, dseqdata.bit.DATA);

    ADC_DSEQCTRL_Type dseqctrl;
    ADC_DSEQSTAT_Type dseqstat;
    dseqctrl.reg = adc->DSEQCTRL.reg;
    dseqstat.reg = adc->DSEQSTAT.reg;
    Serial.printf("      DSEQCTRL=0x%x inputctrl=%d ctrlb=%d refctrl=%d avgctrl=%d sampctrl=%d ",
                  dseqctrl.reg, dseqctrl.bit.INPUTCTRL, dseqctrl.bit.CTRLB, dseqctrl.bit.REFCTRL,
                  dseqctrl.bit.AVGCTRL, dseqctrl.bit.SAMPCTRL);
    Serial.printf("winlt=%d winut=%d gaincorr=%d offsetcorr=%d autostart=%d\n",
                  dseqctrl.bit.WINLT, dseqctrl.bit.WINUT, dseqctrl.bit.GAINCORR,
                  dseqctrl.bit.OFFSETCORR, dseqctrl.bit.AUTOSTART);
    Serial.printf("      DSEQSTAT=0x%x inputctrl=%d ctrlb=%d refctrl=%d avgctrl=%d sampctrl=%d ",
                  dseqstat.reg, dseqstat.bit.INPUTCTRL, dseqstat.bit.CTRLB, dseqstat.bit.REFCTRL,
                  dseqstat.bit.AVGCTRL, dseqstat.bit.SAMPCTRL);
    Serial.printf("winlt=%d winut=%d gaincorr=%d offsetcorr=%d busy=%d\n",
                  dseqstat.bit.WINLT, dseqstat.bit.WINUT, dseqstat.bit.GAINCORR,
                  dseqstat.bit.OFFSETCORR, dseqstat.bit.BUSY);

    // TODO: If DSEQ is configured, dump the contents of the registers at DSEQDATA.
    
    ADC_RESULT_Type result;
    ADC_RESS_Type ress;
    result.reg = adc->RESULT.reg;
    ress.reg = adc->RESS.reg;
    Serial.printf("      RESULT=0x%x (%d) RESS=0x%x (%d)\n",
                  result.reg, result.bit.RESULT, ress.reg, ress.bit.RESS);

    ADC_CALIB_Type calib;
    calib.reg = adc->CALIB.reg;
    Serial.printf("      CALIB=0x%x biascomp=%d biasr2r=%d biasrefbuf=%d\n",
                  calib.reg, calib.bit.BIASCOMP, calib.bit.BIASR2R, calib.bit.BIASREFBUF);
  }
}
