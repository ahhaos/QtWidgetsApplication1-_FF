#include "cav_l1.h"

/* The DEVICE ID is a 32-bit value that identifies the following:
*		bits 28-31 = Backplane Type (0 = Simulated, 1 = PCI)
*		bits 20-27 = Board Type (0x10 = SIM-A429, 0x11 = TEST-A429, 0x12 = PMC-A4293, 0x13 = PC104P-A429, 0x14 = PCI-A429)
*		bits 16-19 = Board Number (0 to 15)
*      bits 8-15 = Channel Type (0x10 = 1553, 0x20 = A429)
*		bits 0-7 = Reserved,Default Value 0x00
*
*/
#include "shiZhu429.h"
#include <QDebug>


cav429::cav429()
{

}
cav429::~cav429()
{
}

void cav429::init()
{

}
