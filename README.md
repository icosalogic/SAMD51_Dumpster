# SAMD51_Dumpster
Dumps low level attributes of many SAMD51 peripherals.

Sorry folks, yet another library for dumping microprocessor internals.
Until the perfect library exists, I guess we will keep creating more.

# Peripherals
This library does a fairly detailed dump of the register values for a limited number
of peripherals.

- PORTS
- GCLK
- SERCOM (buggy)
- TC
- TCC
- DMAC
- ADC

The PORT dump in particular has a really nice lookup table for mapping [port,mux]
values to the peripheral signals using that port.

# Usage
Here is an example of basic usage:

`
#include <SAMD51_Dumpster.h>
SAMD51_Dumpster ilsd;

void setup() {
  ilsd.begin(false);
  ...
  ilsd.dumpTCC("Before Step X");
  ...
  ilsd.dumpTCC("After Step X");
  ...
  ilsd.dumpADC(null); 
}

void loop() {
...
}
`

By default, the library will operate in terse mode, and will not dump data for
peripherals with an ENABLE flag that is not set.  You can override this behavior
by calling `begin(true)` anytime.  The `begin()` method only sets the verbose
flag, so you can call it repeatedly with no adverse side effects.

If you are interested in a single peripheral instance, say, TC3, instead
of calling

`
  ilsd.dumpTC();
`

which will dump all the enabled TC instances, you can call

`
  ilsd.dumpTCInstance(3);
`

Note that the enabled/verbose check is done in the instance calls, so it will
generate no output if a peripheral is not ENABLED, and verbose is false.

