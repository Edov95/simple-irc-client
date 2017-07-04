/**
  * @file recieve_commands.h
  * @author Edoardo Vanin
  * @date 23 Giugno 2017
  * @brief File contenente le funzioni da svolgere ogni volta che ricevo un comando
  */
#ifndef __USER_COMMANDS_H__
#define __USER_COMMANDS_H__

#include <unistd.h>
#include "commands.h"
#include "user.h"
#include "channel.h"
#include "utils.h"
#include "text.h"
#include "errors.h"
#include "response.h"

/**
  * @brief Cambia il nickname
  * @param u l'utente che ha chiamato il comando
  * @param list la lista utenti da cui andare a cercare u
  * @param name il nuovo nickname
  */
void recieve_nick(User* u, User_list* list, char* name);

/**
  * @brief Risponde con un messaggio di benvenuto
  * @param u l'utente che ha chiamato il comando
  */
void recieve_user(User* u);

/**
  * @brief Entra in un canale
  * @param u l'utente che ha chiamato il comando
  * @param name il nome del canale in cui entrare
  * @details la funzione entra sempre in un canale, se non esiste lo crea, se esiste aggiunge l'utente alla lista utenti del canale
  */
void recieve_join(User* u, char* name);

/**
  * @brief Mode
  * @param u l'utente che ha chiamato il comando
  */
void recieve_mode(User* u, char* umode);

/**
  * @brief Who
  * @param u l'utente che ha chiamato il comando
  * @param query la sintassi per il comando WHO
  * @details si possono distinguere tre casi in cui agisce il comando WHO
  * il primo senza query ed invia al chiamante tutte le informazioni di tutti gli utenti che non
  sono negli stessi canali di u
  * il secondo con parametro un canale ed invia ad u le informazioni di tutt gli utenti del canale (u escluso)
  * infine il terzo caso in cui la funzione WHO viene chiamata su un utente e invia ad u nickname e hostname dell'utente cercato
  */
void recieve_who(User* u, char* query);

/**
  * @brief Whois
  * @param u l'utente che ha chiamato il comando
  * @param query l'utente su vui si vuole chiamare il WHOIS
  * @details invia le stesse informazioni di WHO username solo con la formattazione di una chiamata WHOIS
  */
void recieve_whois(User* u, char* query);
/**
  * @brief Ping
  * @param u l'utente che ha chiamato il comando
  * @param ping_message l'identificativo del cliente che ha chiamato il comando Ping
  * @details a differenza della specifica nel RFC1459 non supporta la gestione di server multipli o chiamata di ping verso utenti del sistema
  */
void recieve_ping(User* u, char* ping_message);

/**
  * @brief Privmsg
  * @param u l'utente che ha chiamato il comando
  * @param message il messaggio da inviare al canale
  * @details la funzione non gestisce lo scambio di messaggi tra utenti ma sono nei canali
  */
void recieve_privmsg(User* u, char* message);

/**
  * @brief Part
  * @param u l'utente che ha chiamato il comando
  * @param parameter la stringa che contiene il canale da abbandonare e il messaggio di leave
  * @details la funzione non gestisce, a differenza di quanto indicato dalla RFC1459 l'abbandono multiplo
  */
void recieve_part(User* u, char* parameter);

/**
  * @brief Quit
  * @param u l'utente che ha chiamato il comando
  * @param parameter il leave message
  * @details comando quit, disconnnette l'utente dal server e rimuove la sua presenza dalle liste utente e canale
  */
void recieve_quit(User* u, char* parameter);

/**
  * @brief List
  * @param u l'utente che ha chiamato il comando
  * @details ritorna la lista di canali presenti nel server
  */
void recieve_list(User* u);

/**
  * @brief Topic
  * @param u l'utente che ha chiamato il comando
  */
/*void recieve_topic(User* u, char* parameter);*/

#endif
