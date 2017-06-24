#include "recieve_commands.h"

void recieve_nick(User* u, User_list* list, char* name){

  char* send_line = malloc(MAXLINE + 1);
  strcpy(send_line, ":");
  strcat(send_line, u -> name);
  strcat(send_line, "!");
  strcat(send_line, u->hostname);
  strcat(send_line, " ");

  if(name == NULL){
    strcat(send_line, ERR_NONICKNAMEGIVEN);
    strcat(send_line, NONICKNAMEGIVEN);
    strcat(send_line, "\n");
  } else if (find_by_username(list, name) != NULL) {
    strcat(send_line, ERR_NICKNAMEINUSE);
    strcat(send_line, " ");
    strcat(send_line, name);
    strcat(send_line, " ");
    strcat(send_line, name);
    strcat(send_line, "\n");
  } else {
    strcat(send_line, NICK);
    strcat(send_line, " :");
    strcat(send_line, name);
    strcat(send_line, "\n");
    write(u->socket, send_line, strlen(send_line));
    //notificare che ho cambiato nome
    change_name(&u,name);
    free(send_line);
    return;
  }

  write(u->socket, send_line, strlen(send_line));

  free(send_line);
  return;
}

void recieve_user(User* u){
  char* send_line = malloc(MAXLINE + 1);
  strcat(send_line, WELCOME_02);
  strcat(send_line, WELCOME_03);
  strcat(send_line, WELCOME_USER_01);
  strcat(send_line, u->name);
  strcat(send_line, WELCOME_USER_02);
  strcat(send_line, u->hostname);
  strcat(send_line, "\n");
  write(u->socket, send_line, strlen(send_line));
  free(send_line);
}
