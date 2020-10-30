#ifndef SPEAKER_H
#define SPEAKER_H

#include "DE1SoCfpga.h"


class Speaker: public DE1SoCfpga {
  public:

  Speaker();
  ~Speaker();

  void Sound(float hz, float sec);

};

#endif
