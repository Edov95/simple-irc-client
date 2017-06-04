#ifndef __RTP_PACKET_H__
#define __RTP_PACKET_H__

#include <sys/types.h> //ora dovrebbe essere giusta :)

// Header di un pacchetto RTP
typedef struct {
  unsigned char V:2;
  unsigned char P:1;
  unsigned char X:1;
  unsigned char CC:4;
  unsigned char M:1;

  //qui forse convine usare una struttura oppure un'enumerazione controllare cosa dicono le specifiche
  unsigned char PT:7;
  //==============
  
  unsigned int seqNum:16;
  unsigned long long timeStamp:32;
  unsigned long long SSRC:32;
} RTP_FixedHeader;

#endif
