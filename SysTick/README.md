1. Understanding SysTick
   - SysTick (System tick) is a 24-bit down counter intergral to all Arm Cortex-M processors. It is designed to offer a configurable time base that can be used for various purposes, such as task scheduling, system monitoring, and time tracking. This timer provides a simple and efficient means of generating periodic interrupts and serves as a cornerstone for implementing system timing functions, including operating system (OS) tick generation for real-time operating systems (RTOSs). Usinng SysTick makes code more portable since it is part of the core and not a vendor-specific peripheral.
   - Key features:
     - 24-bit reloadable counter: Counter decrements from a specified value to zero, automatically reload once hit zero
     - Core integration: Being part of the core, it's required minimal configuration and offers low-latency interrupt       handling
     - Clock source: SysTick can operate either from the core clock or an external reference clock
     - Inteript generation: Once counter hit zero, it can trigger an interrupt.
2. SysTick timer registers
   - SysTick COntrol and Status Register (SYST_CSR)
     - This register controls the SysTick timer's operation and provides status information. It has the following bits:
         - ENABLE (Bit 0) -> Enable or disables the SysTick counter
         - TICKINT (BIT 1) -> Enable or disables the SysTick interrupt
         - CLKSOURCE (Bit 2) -> Select the clock source (0 = external reference clock, 1 = processor clock)
         - COUNTFLAG (Bit 16) -> Indicates whether the counter has reach zero since the last read ( 1 = yes, 0 = no)
   - SysTick Reload Value Register (SYST_RVR)
         - This specified the start value to load into the SysTick current value register. It is crucial for setting         the timer's period and understanding its bit assignments and calculations is essential for effective SysTick           configuration
         - Following fields: Bit[31:24] Reservd anmd Bits[23:0] RELOAD -> this field specifies the value that the            SysTick timer will load into SYST_CVR register when the counter is enabled and when it reachse 0
         - Calculate RELOAD value by: CLock cycles = clock frequency * 1ms
       *NOTE: 1mHz = 1000000Hz and 1ms = 0.001s
         - After we got Clock cycles, subtract that for 1
       Example: STM32F4 has board frequency is 16000000 -> RELOAD = (16000000 * 0.001) - 1 = 15,999
         - In computer, developers always counting from 0, so if not subtract by 1 it will stop at 1 before reach 0           and automatically reload new value
   - SysTick Current Value Register (SYST_CVR)
         - This holds the current value of the SysTick counter. Developer can use this register to monitor the                countdown process and to reset the counter when necessary
   - SysTick Calibration Value Register (SYST_CALIB)
         - Provides with the calibration properties of the SysTick timer


*CODE EXAMPLE

```
#include "SysTick.h"

#define CRTL_ENABLE (1U << 0)
#define CTRL_CLOCKSOURCE (1U << 2)
#define CTRL_COUNTERFLAG (1U << 16)

#define BOARD_FREQUENTCY 8000

void systick_delay(uint32_t delay)
{
	SysTick -> LOAD = BOARD_FREQUENTCY -1; //load number of clock per ms
	SysTick -> VAL = 0; //current value is 0
	SysTick -> CTRL = CTRL_CLOCKSOURCE; // clock source (1 is external, 0 is from baord) define above
	SysTick -> CTRL |= CRTL_ENABLE; // enable system tick

	for ( uint32_t i = 0; i < delay; i++)
	{
		while ((SysTick -> CTRL & CTRL_COUNTERFLAG) == 0){}
	}
	SysTick -> CTRL = 0; //disable systick
}
```


