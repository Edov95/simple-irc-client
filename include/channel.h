/**
  * @file user.h
  * @author Edoardo Vanin
  * @date 17 Giugno 2017
  * @brief File per gestire i cananli del server
  */
#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#ifndef __STRING__
#define __STRING__
typedef char* string;
#endif


#define CHANNEL(OBJ) ((Channel*)(OGJ))
#define CHANNEL_LIST(OBJ) ((Channel_list*)(OBJ))

#include "user.h"
#include <stdlib.h>


/**
  * @brief Struttura per gestire i cananli
  */
typedef struct {
  string name;
  User_list* users;
}Channel;

/**
  * @brief Crea un canale date un nome del canale
  */
Channel* create_channel(string name);

/**
  * @brief Aggiunge un utente al canale
  */
int add_user(Channel* c, User* c);

/**
  * @brief Struttura per collezionare i canali nel server
  */
typedef struct _Channel_list{
  struct _Channel_list *prev;
  struct _Channel_list *next;
  Channel* payload;
}Channel_list;


/**
  * @brief Aggiunge un canale alla lista
  * @param il puntatore alla lista di canali da aggiornare
  * @param il canale da aggiungere
  * @return -1 se il canale NON è stato inserito correttamente nella lista
  * @return diverso da -1 se il canale è stato inserito correttamente
  */
int add_channel(Channel_list** list, Channel* c);

/**
  * @brief Rimuove un canale dalla lista
  * @param list puntatore doppio alla lista di canali, la lista viene modificata
  * @param name il nome del canale
  * @return il puntatore al canale se trovato, altrimenti puntatore nullo
  * @details La funzione cerca il canale e se lo trova restituire un puntatore
      alla zona di memora contenente l'oggetto e contemporaneamente
      lo rimuove dalla lista ma NON libera l'area di memoria occupata
  */
Channel* remove_channel(Channel_list** list, string name);

/**
  * @brief Trova un canale nella lista canali
  * @param list puntatore alla lista di canali
  * @param name il nome del canale
  * @return il puntatore al canale se trovato altrimenti ritorna puntatore nullo
  * @details a differenza della funzione remove_channel non elimina la referenza
      nella lista di canali
  */
Channel* find_channel(Channel_list* list, string name);

/**
  * @brief Stampa la lista dei canali
  */
void print_list_channel(Channel_list* list);

/**
  * @brief Stampa la lista utenti per il canale selezionato
  */
void print_users_in_channel(Channel* c);

/**
  * @brief Stampa la lista degli utenti in ogni canale
  */
void print_list_channel_and_users(Channel_list* list);

#endif
