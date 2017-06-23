/**
  * @file user.h
  * @author Edoardo Vanin
  * @date 20 Giugno 2017
  * @brief File per gestire i comandi utente
  */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include "user.h"
#include "channel.h"
#include "util.h"
#include "commands.h"
#include "user_commands.h"

#define MAXLINE 4096


/**
  * @brief Gestice i comandi arrivati dagli utenti connessi
  * @param L'utente da gestire
  * @details la funzione principe del programma (in realtà si tratta di uno
      switch sul comanda arrivato) ma deve essere gestito ad hoc
  */
void user_thread(User* u);
