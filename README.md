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
   - Navigate the bin file from the packages just downloads and add it into Enviroment variables path
    <img width="1492" height="781" alt="image" src="https://github.com/user-attachments/assets/22c3e6ed-6471-4215-95a5-66fcce203650" />

   - For GNU, download arm-gnu then add bin path into enviroment variables
   - Connect the board with STlink debug
   - After created project, open cmd for setting up
         - Access the folder through the command prompt by using cd (change directory). Example: cd F:\Work_Station_Only_USB_Windows\STM32\example\Debug
         <img width="602" height="46" alt="image" src="https://github.com/user-attachments/assets/e2f7253d-cdcf-44a5-a1cc-43b2b6f1d088" />
         - Next is copy lines from the STM32Cube IDE console pane, to do this in current project, right click on whole file -> build configurations -> clean all, then build the project, we will see these line from console
           <img width="1479" height="307" alt="image" src="https://github.com/user-attachments/assets/e3501083-31a9-4fe5-a042-b1a8cb6fb82f" />
         - Look for the line "startup" to consider it first line need to copy and paste into cmd promt, for next line 2 3 and 4, copy into a note to remove **-fcyclomatic-complexity** flags then paste them into cmd prompt
         - copy the last line has .elf, at this point, there should not have any issues or errors
            <img width="1098" height="356" alt="image" src="https://github.com/user-attachments/assets/3b81650a-dcc4-4f7d-9ebf-53278cc3fe32" />
         - To observing the results, developer can use the command arm-none-eabi-size (name of the project).elf -> you will see the size of the file, if match it means you already in
         - Last step will be convert the original .elf into binary by using objcopy tool. Type "arm-none-eabi-objcopy -o binary (name of the project).elf (name of the project).bin
     
3. Connecting Microcontroller
   - Connect the board (this time will try with STM32F4 nucleo)
   - After connect the board, type "openocd -f interface/stlink.cfg -f target/stm32f4x.cfg". If it  show no errors, mean developer already access into the board and ready to communicate with the board (*NOTE: If             want to use for f1 blue pill, change stm32f4x.cfg into stm32f1x.cfg)
       <img width="1052" height="406" alt="image" src="https://github.com/user-attachments/assets/5d36e62a-019c-454b-b3a1-3736b7cd9f12" />
   - At this point, the cmd prompt will be lock in and running. Next is turn on another cmd and type "arm-none-eabi-gdb"
     <img width="736" height="340" alt="image" src="https://github.com/user-attachments/assets/ea50ca42-3688-41a7-8ea3-c91441fd2e7b" />
   - After gdb is open,establish a connection to the microcontroller by port number, in this case is 3333 (to check the port through the openocd cmd at the last line). Type "target remote localhost:3333"
   - link into the exactly .elf file that would want to debug, to do this we use command "file" to navigate it. For example "file F:/Work_Station_Only_USB_Windows/STM32/example/Debug/example.elf". Once see reading symbol From \... Developer already to debug
     <img width="844" height="204" alt="image" src="https://github.com/user-attachments/assets/0e1cb9a6-a04c-4f00-bf64-6a41477e8b97" />


*CHECKLIST: - First cmd, open ocd by  cmd: "openocd -f interface/stlink.cfg -f target/stm32f4x.cfg"
            - Turn another cmd, open gdb by cmd: "arm-none-eabi-gdb"
            - access into MCU port number by cmd: "target remote locahost:3333"
            - link into the exactly .elf file by cmd: "file F:/Work_Station_Only_USB_Windows/STM32/example/Debug/example.elf" 

4. Start debugging
   - Once everything is setting up, use cmd monitor to control the code
   - to upload code, we build from IDE to create new .elf file then type "load" from cmd
   - type monitor reset init to reset board
   - monitor resume to continue code
   - monitor reset halt to access into debug mode
     <img width="609" height="138" alt="image" src="https://github.com/user-attachments/assets/e86f8fe2-c30e-4688-b8a5-b10641a08136" />

*EXAMPLE: - Developer want to test out if the LED is blinking or not and delay is very fast that normal eyes could not see it, after command "monitor reset halt" to access into debug mode, type break main to direct into main() function.
          - type continue or next to go step by step in the code til reach the delay line
          - From this point, developer could see the led still blinking normally since it break right after the delay, developer find out that the delay time was too fast to modify it longer.

