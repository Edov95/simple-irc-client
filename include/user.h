/**
  * @file user.h
  * @author Edoardo Vanin
  * @date 12 Giugno 2017
  * @brief File per gestire gli utenti collegati al server
  * @todo Creare un test per la lista
  * @todo Creare la documentazione
  */
#ifndef __USER_H__
#define __USER_H__

#include <string.h>


#ifndef __STRING__
typedef char* string
#endif



/**
  * @brief Struttura per gestire gli utenti
  * @details L'utente è un'entità con nome e identificativo univoci, un
      indicatore per il canale corrente (curr_channel) e
      il socket da cui l'utente si connette
  */
typedef struct {
  string name;
  int id;
  string curr_channel;
  int socket;
} User;

/**
  * @brief Lista concatenata per gestire gli utenti
  * @details Implementazione di una lista doppiamente concatenata per gestire
      gli utenti connessi al server
  */
typedef struct {
  User_list* next;
  User_list* prev;
  User* payload;
} User_list;

/**
  * @brief Aggiunge un utente alla lista
  * @param list puntatore doppio alla lista di utenti, la lista viene modificata
  * @return -1 se l'utente NON è stato inserito correttamente nella lista
  * @return diverso da -1 se l'utente è stato inserito correttamente
  */
int add_user(User_list** list, User* u);

/**
  * @brief Rimuove un utente dalla lista dato l'identificatore
  * @param list puntatore doppio alla lista di utenti, la lista viene modificata
  * @param id identificatore univoco dell'utente
  * @return il puntatore all'utente se trovato, altrimenti puntatore nullo
  * @details La funzione cerca l'utente con id passato come parametro e se
      lo trova restituire un puntatore alla zona di memora contenente i
      l'oggetto e contemporaneamente lo rimuove dalla lista ma NON libera
      l'area di memoria occupata
  */
User* remove_user_by_id(User_list** list, int id);

/**
  * @brief Rimuove un utente dalla lista dato lo username
  * @param list puntatore doppio alla lista di utenti, la lista viene modificata
  * @param username identificatore univoco dell'utente
  * @return il puntatore all'utente se trovato, altrimenti puntatore nullo
  * @details La funzione cerca l'utente con username passato come parametro e se
      lo trova restituire un puntatore alla zona di memora contenente i
      l'oggetto e contemporaneamente lo rimuove dalla lista ma NON libera
      l'area di memoria occupata
  */
User* remove_user_by_username(User_list** list, string username);

/**
  * @brief Trova un utende usando il suo identificativo
  * @param list puntatore alla lista utenti
  * @param id l'identificatore dell'utente da trovare
  * @return il puntatore all'utene se trovato altrimenti ritorna puntatore nullo
  * @details a differenza delle funzioni remove_user_* non elimina la referenza
      nella lista di utenti
  */
User* find_by_id(User_list* list, int id);

/**
  * @brief Trova un utende usando il suo identificativo
  * @param list puntatore alla lista utenti
  * @param usrname l'identificatore dell'utente da trovare
  * @return il puntatore all'utene se trovato altrimenti ritorna puntatore nullo
  * @details a differenza delle funzioni remove_user_* non elimina la referenza
      nella lista di utenti
  */
User* find_by_username(User_list* list, string username);

/**
  * @brief Stampa la lista utenti
  */
int print_list(User_list* list);

#endif
