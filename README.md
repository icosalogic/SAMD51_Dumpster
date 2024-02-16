# SAMD51_Dumpster
Dumps low level attributes of many SAMD51 peripherals.

Sorry folks, yet another library for dumping SAMD51 microprocessor internals.
Until the perfect library exists, I guess we will keep creating more.

Much of this code will probably work verbatim on a SAMD21, but no work has been done in that direction.

# Peripherals
This library does a fairly detailed dump of the register values for a limited number
of peripherals.

- PORTS
- GCLK
- MCLK
- SERCOM
- TC
- TCC
- DMAC
- ADC

The PORT dump in particular has a really nice lookup table for mapping [port,mux]
values to the names of the peripheral signals using that port.

# Usage
Here is an example of basic usage.

```C++
#include <SAMD51_Dumpster.h>
SAMD51_Dumpster ilsd;

void setup() {
  ilsd.begin(false);
  // other code here...
  ilsd.dumpTCC("Before Step X");
  // other code here...
  ilsd.dumpTCC("After Step X");
  // other code here...
  ilsd.dumpADC(NULL); 
}

void loop() {
  // other code here...
}
```

For a complete list of methods you can call, see `SAMD51_Dumpster.h`.

By default, the library will operate in terse mode, and will not dump data for
peripherals with an ENABLE flag that is not set.  You can override this behavior
by calling `begin(true)` to set the verbose flag to true.  The `begin()` method only sets the verbose
flag, so you can call it repeatedly with no unexpected side effects.

If you are interested in a single peripheral instance, say, TC3, instead of calling

```
  ilsd.dumpTC(NULL);
```

which will dump all the enabled TC instances, you can call

```
  ilsd.dumpTCInstance(3);
```

Note that the enabled/verbose check is done in the instance calls, so `dumpTCInstance(3)` will
generate no output if TC3 is not ENABLED and the verbose flag is false.

