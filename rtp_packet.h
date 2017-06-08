#ifndef __RTP_UTILS_H__
#define __RTP_UTILS_H__

#include <sys/types.h>
#include <netinet/in.h>

/*
 * @brief enumerazione di supporto per indicare il tipo di flusso
 */
typedef enum{
  _h264 = 1,
  _mp3
} RTP_Payload;


// la inserico nel file c in modo da renderla "privata"?
//definizione del cast OOP-like
#define RTP_FixedHeader(OBJ) ((RTP_FixedHeader*)(OBJ))

/**
  * @brief Struttura che descrive l'header di un pacchetto RTP
  */
typedef struct {
  unsigned char V:2;    // versione
  unsigned char P:1;    // padding
  unsigned char X:1;    // extension
  unsigned char CC:4;   // CSRC count
  unsigned char M:1;    // marker
  unsigned char PT:7;   // payload
  uint16_t seqNum;      //sequence number
  uint32_t timeStamp;   //timestamp
  uint32_t SSRC;        //SSRC
} RTP_FixedHeader;


//definizione del cast OOP-like
#define RTP_Handler(OBJ) ((RTP_Handler*)(OBJ))

/**
  * @brief Struttura per gestre il pacchetto RTP
  */
typedef struct {
  int sock;
  struct sockaddr_in servAdd;
  uint16_t seqNum;
  uint32_t timestamp;
  uint32_t SSRC;
  RTP_FixedHeader* header;
  RTP_Payload payload;

}RTP_Handler;

/**
  * @brief Crea il gestore del pacchetto RTP
  * @param IP: L'indirizzo ip del client
  * @param port: il numero di porta del servizio
  * @param payload: il payload del pacchetto
  */
RTP_Handler* RTPCreate(unsigned int IP, int port, RTP_Payload payload);

/**
  * @brief distruttore per la struttura RTP_Handler
  * Distruttore per la struttura RTP_Handler,
  * chiude il socket e libera la memoria
  * @param pHandler: puntatore alla struttura da distruggere
  */
void RTPDelete(RTP_Handler* hand);

/**
  * @brief invia i dati a destinazione
  */
int RTPSend(RTP_Handler* hand, void* data, int size, unsigned int timeStamp);

#endif
