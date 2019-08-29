/**
    Section: Includes
*/
#include <xc.h>

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    //    INT1I: External Interrupt 1
    //    Priority: 3
        IPC5bits.INT1IP = 3;
    //    INT2I: External Interrupt 2
    //    Priority: 2
        IPC7bits.INT2IP = 2;
}
