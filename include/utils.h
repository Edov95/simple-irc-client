/**
  * @file user.h
  * @author Edoardo Vanin
  * @date 20 Giugno 2017
  * @brief File contenente funzioni e/o variabili globali
  */
#ifndef __UTILS_H__
#define __UTILS_H__


#include "user.h"
#include "channel.h"
#include "errors.h"
#include "response.h"
#include "text.h"
#include <pthread.h>
#include <unistd.h>

///@brief impone un numero massimo di utenti che si possono collegare al server
#define MAXUSER 150
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

/**
  * @brief Funzione per gestire il caso "utente" del comando WHO
  */
void send_user_info(User* u, User* target, char* channel);

/**
  * @brief Funzione per gestire il caso "tutti gli utenti" del comando WHO
  */
void send_all_user_info(User* u);

/**
  * @brief Fuzione per gestire il caso "cananle" del comando WHO
  */
void send_channel_info(User* u, Channel* c);

#endif
