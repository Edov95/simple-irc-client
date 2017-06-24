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
#include "util.h"
#include "text.h"
#include "errors.h"

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

#endif
