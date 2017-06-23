#include "receive_commands.h"

void recieve_nick(User* u, char* name){
  char* send_line = malloc(MAXLINE + 1);
  strcpy(send_line, ":");
  strcat(send_line, u -> name);
  strcat(send_line, "!");
  strcat(send_line, user->hostname);
  strcat(send_line, " ");
}
