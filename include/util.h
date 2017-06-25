/**
  * @file user.h
  * @author Edoardo Vanin
  * @date 20 Giugno 2017
  * @brief File contenente funzioni e/o variabili globali
  */
#include "user.h"
#include "channel.h"
#include <pthread.h>

///@brief impone un numero massimo di utenti che si possono collegare al server
#define MAXUSER 15
#define MAXLINE 4096

///@brief contatore per la lista utenti
int count;
///@brief lista globale per contenente tutti gli utenti del presenti nel server
User_list* main_user_list;
///@brief semaforo per la lista utenti, evita malfunzionamenti dalla programmazione concorrente
pthread_mutex_t main_user_list_mutex;

///@brief lista globale per la gestione di tutti i canali
Channel_list* main_channel_list;
///@brief semaforo per la lista cananli, evita malfunzionamenti dalla programmazione concorrente
pthread_mutex_t main_channel_list_mutex;
