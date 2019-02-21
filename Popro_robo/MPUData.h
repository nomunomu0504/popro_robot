#ifndef MPUDATA_H
#define MPUDATA_H

class MPUData
{
  public:
    MPUData() : dmpReady(false), mpuInterrupt(false)
    {
    }
    bool dmpReady;
    uint8_t mpuIntStatus;
    uint8_t devStatus;
    uint16_t packetSize;
    uint16_t fifoCount;
    uint8_t fifoBuffer[64];
    volatile bool mpuInterrupt;
    float ypr[3];
};

#endif