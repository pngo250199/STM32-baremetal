# STM32-baremetal
Documenting all projects
Bare metal of STM32. In this file, there are two types of MCU has used were STM32f4 nucleo and STM32f1 blue pill



1. Introducing tools
   - the F4 nucleo has its debugger chip while F1 blue pill need an external debugger, both of them are called STlink
   - Developer could debug straight from stm32cubeIDE tool and with the help of stm32cubeProgrammer to check on memory address used and mass erase memory used to get more storage when upload new codes
   - In this document focuesses on getting familiar with OpenOCD and GDB for embedded debugging.
       - The benefits of using OpenOCD + GDB instead of a typical IDE debugger provides greater control, flexibility, and visibility, especially for embedded systems.
       - Direct access to CPU registers, Memory-mapped peripherals and breakpoints/watchpoints at hardware breakpoints/watchpoints
       - Useful for DIAGNOSING COMPLEX HARDWARE ISSUES, DEBUGGING STARTUP CODE AND BOOTLOADERS, and INSPECTING RTOS BEHAVIOR AND LOW-LEVEL EXECUTION
       - Work across different PLATFORMS and ENVIRONMENTS (including macOS or linux) and is not tied to a specific IDE or vendor
       - Support scriptable and automated debugging workflows, making it suitable for advanced development and testing setups

2. Setting up debugging tools
   - Download xpack for openOCD packages (depends on developer OS to get the correct files)
   - Navigate the bin file from the packages just downloads and add it into Enviroment variables
    <img width="1492" height="781" alt="image" src="https://github.com/user-attachments/assets/22c3e6ed-6471-4215-95a5-66fcce203650" />
