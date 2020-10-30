#include "Speaker.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>

using namespace std;


const unsigned int MPCORE_PRIV_TIMER_LOAD_OFFSET = 0xDEC600; //  Points  to  LOAD Register
const unsigned int MPCORE_PRIV_TIMER_COUNTER_OFFSET = 0xDEC604; //  Points  to COUNTER Register
const unsigned int MPCORE_PRIV_TIMER_CONTROL_OFFSET = 0xDEC608; //  Points  to CONTROL Register
const unsigned int MPCORE_PRIV_TIMER_INTERRUPT_OFFSET = 0xDEC60C; //  Points  to INTERRUPT Register
const unsigned int PARR_BASE = 0x70;


  Speaker::Speaker() {
  }

  Speaker::~Speaker() {
  }

  void Speaker::Sound(float hz, float sec) {
  
    int loadDefault = RegisterRead(MPCORE_PRIV_TIMER_LOAD_OFFSET);
    int controlDefault = RegisterRead(MPCORE_PRIV_TIMER_CONTROL_OFFSET);
    int interruptDefault = RegisterRead(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET);


  	int count = (200000000 / hz) / 2;
    RegisterWrite(MPCORE_PRIV_TIMER_LOAD_OFFSET, count);
    RegisterWrite(MPCORE_PRIV_TIMER_CONTROL_OFFSET, 3);
    RegisterWrite(PARR_BASE + 4, 1); // set register for output
    bool toggle = false;
    int runtime = (200000000 / (count * 2)) * sec;
    while (runtime > 0) {
    
      if (RegisterRead(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET) != 0) {
        RegisterWrite(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET, 1);
        if (toggle) {
          RegisterWrite(PARR_BASE, 1);
	  runtime--;
        }
        else {
          RegisterWrite(PARR_BASE, 0);
        } 
        toggle = !toggle;
      }
    }
	RegisterWrite(MPCORE_PRIV_TIMER_LOAD_OFFSET, loadDefault);
	RegisterWrite(MPCORE_PRIV_TIMER_CONTROL_OFFSET, controlDefault);
	RegisterWrite(MPCORE_PRIV_TIMER_INTERRUPT_OFFSET, interruptDefault);
  }
  
