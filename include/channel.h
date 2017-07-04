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
#define MAXLINE 4096
#include <stdlib.h>


/**
  * @brief Struttura per gestire i cananli
  */
typedef struct {
  string name;      //!< il nome del canale
  string topic;     //!< il topic del canale, non ancora utilizzato, per sviluppi futuri
  int number_users; //!< conta il numero di utenti presenti nel canale
  User_list* users; //!< la lista degli utenti presenti nel canale
}Channel;

/**
  * @brief Crea un canale dato un nome ed un argomento
  * @param name il nome del canale
  * @param topic l'argomento del canale, può eventualmente essere nullo non influisce sulla creazione effettiva del canale
  * @return il puntatore all'area occupata dal canale appena creato
  */
Channel* create_channel(string name, string topic);

/**
  * @brief Cambia il topic
  * @param topic l'argomento da cambiare
  */
void change_topic(Channel* c, string topic);

/**
  * @brief Aggiunge un utente al canale
  * @param c il canale a cui aggiungere l'utente
  * @param u l'utente da aggiungere al canale
  * @return -1 se l'utente NON è stato inserito correttamente nella lista
  * @return diverso da -1 se l'utente è stato inserito correttamente
  */
int add_user_to_channel(Channel** c, User* u);

/**
  * @brief Struttura per collezionare i canali nel server
  */
typedef struct _Channel_list{
  struct _Channel_list *prev; //!< puntatore alla cella precedente della lista
  struct _Channel_list *next; //!< puntatore alla cella successiva della lista
  Channel* payload;           //!< il canale da memorizzare nella lista
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
  * @param list la lista da stampare
  */
void print_list_channel(Channel_list* list);

/**
  * @brief Stampa la lista utenti per il canale selezionato
  * @param c il canale per di cui si vuole stampare la lista utenti
  */
void print_users_in_channel(Channel* c);

/**
  * @brief Stampa la lista degli utenti in ogni canale
  * @param lista la lista che si vuole stampare
  */
void print_list_channel_and_users(Channel_list* list);

#endif
