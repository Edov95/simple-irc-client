/**
  * @file user_commands.h
  * @author Edoardo Vanin
  * @date 23 Giugno 2017
  * @brief File contenente le funzioni da svolgere ogni volta che ricevo un comando
  */
#ifndef __USER_COMMANDS_H__
#define __USER_COMMANDS_H__

#include "user.h"
#include "channel.h"

/**
  * @brief Cambia il nickname
  */
void recieve_nick(User* u, char* name);

/**
  * @brief Risponde con un messaggio di benvenuto
  */
void recieve_user(User* u);

/**
  * @brief Entra in un canale
  */
void recieve_join(User* u, char* name);

#endif