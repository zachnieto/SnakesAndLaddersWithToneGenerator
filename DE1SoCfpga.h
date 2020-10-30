#ifndef DE1SOCFPGA_H
#define DE1SOCFPGA_H

const unsigned int LW_BRIDGE_BASE = 0xFF200000;
const unsigned int LW_BRIDGE_SPAN = 0x00DEC700;
const unsigned int LEDR_BASE = 0x00000000;
const unsigned int SW_BASE = 0x00000040;
const unsigned int KEY_BASE = 0x00000050;
const unsigned int HEX3_HEX0_BASE = 0x00000020; // HEX Reg1 offset
const unsigned int HEX5_HEX4_BASE = 0x00000030; // HEX Reg2 offset

class DE1SoCfpga {

  public:
    char * pBase;
	int fd;

  DE1SoCfpga();
  ~DE1SoCfpga();
  void RegisterWrite(unsigned int reg_offset, int value);
  int RegisterRead(unsigned int reg_offset);

};

#endif
