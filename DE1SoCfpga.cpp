#include "DE1SoCfpga.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

using namespace std;

	DE1SoCfpga::DE1SoCfpga() {
		
      // Open /dev/mem to give access to physical addresses
      fd = open("/dev/mem", (O_RDWR | O_SYNC));
      if (fd == -1) //  check for errors in openning /dev/m$
      {
        cout << "ERROR: could not open /dev/mem..." << endl;
        exit(1);
      }
      // Get a mapping from physical addresses to virtual addresses
      char * virtual_base = (char * ) mmap(NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
      if (virtual_base == MAP_FAILED) // check for errors
      {
        cout << "ERROR: mmap() failed..." << endl;
        close(fd); // close memory before exiting
        exit(1); // Returns 1 to the operating system;
      }
      pBase = virtual_base;
	}
	
	DE1SoCfpga::~DE1SoCfpga() {
		if (munmap(pBase, LW_BRIDGE_SPAN) != 0) {
        cout << "ERROR: munmap() failed..." << endl;
        exit(1);
      }
      close(fd); // close memory
	}

  /**
   * Write a 4-byte value at the specified general-purpose I/O location.
   *
   * @parem offset        Offset where device is mapped.
   * @param value Value to be written.
   */
  void DE1SoCfpga::RegisterWrite(unsigned int reg_offset, int value) {

    *(volatile unsigned int * )(pBase + reg_offset) = value;
  }

  /**
   * Read a 4-byte value from the specified general-purpose I/O location.
   *
   * @param offset        Offset where device is mapped.
   * @return              Value read.
   */
  int DE1SoCfpga::RegisterRead(unsigned int reg_offset) {
    return *(volatile unsigned int * )(pBase + reg_offset);
  }
