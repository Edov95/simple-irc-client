/**
  * @file user_commands.h
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
  */
void recieve_nick(User* u, User_list* list, char* name);

/**
  * @brief Risponde con un messaggio di benvenuto
  */
void recieve_user(User* u);

/**
  * @brief Entra in un canale
  */
void recieve_join(User* u, char* name);

/**
  * @brief Mode
  */
void recieve_mode(User* u, char* umode);

/**
  * @brief Who
  */
void recieve_who(User* u, char* query);

/**
  * @brief Whois
  */
void recieve_whois(User* u, char* query);
/**
  * @brief Ping
  */
void recieve_ping(User* u, char* ping_message);

/**
  * @brief Privmsg
  */
void recieve_privmsg(User* u, char* message);

/**
  * @brief Part
  */
void recieve_part(User* u, char* parameter);

/**
  * @brief Quit
  */
void recieve_quit(User* u, char* parameter);

/**
  * @brief List
  */
void recieve_list(User* u);

/**
  * @brief Topic
  *
void recieve_topic(User* u, char* parameter);*/

#endif
