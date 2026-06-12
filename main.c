#include "xc.h"

// CONFIG1
#pragma config WDTPS = PS32768   // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128     // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON       // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF      // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx2        // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
#pragma config GWRP = OFF        // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF         // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF      // JTAG Port Enable (JTAG port is disabled)      
// CONFIG2
#pragma config POSCMOD = HS      // Primary Oscillator Select (Primary oscillator disabled)
#pragma config OSCIOFNC = ON     // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSECMD    // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are enable)
#pragma config FNOSC = FRCDIV    // Oscillator Select (Fast RC Oscillator with Postscaler (FRCDIV))
#pragma config IESO = OFF        // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

#include "lib_turing.h"

int main(void) {
    Turing_Init();
    
    while(1) {
        Turing_Task();
    }
    
    return 0;
}