#include "user_thread.h"

void user_thread(User* u){
  char recvline[MAXLINE + 1];
  char* line = malloc((MAXLINE + 1) * sizeof(char));
  char* send_line = malloc((MAXLINE + 1) * sizeof(char));
  char* command;
  ssize_t n;

  pthread_mutex_lock(&(u -> socket_mutex));
  n = read(u -> socket, recvline, MAXLINE);
  pthread_mutex_unlock(&(u -> socket_mutex));

  while(n > 0){
    recvline[n] = 0;
    line = strcpy(line, recvline);
    command = strtok(line, " \t\r\n/");
    while (command != NULL) {
      printf("L'utente: %i ha inviato il comando: %s\n",u -> id, command);
      /*Qui parte lo switch di comparazaione con i comandi conosciuti*/
      if(strcmp(command,NICK) == 0){
        recieve_nick(u, main_user_list, strtok(NULL, " \t\r\n/"));
      } else if(strcmp(command,USER) == 0){
        recieve_user(u);
      } else if(strcmp(command,JOIN) == 0){
        recieve_join(u, strtok(NULL, " \t\r\n/"));
      } else if(strcmp(command, MODE) == 0){
        strtok(NULL, " \t\r\n/");
        recieve_mode(u, strtok(NULL, " \t\r\n/"));
      } else if(strcmp(command, WHO) == 0){
        recieve_who(u, strtok(NULL, " \t\r\n/"));
      } else if(strcmp(command, WHOIS) == 0){
        recieve_whois(u, strtok(NULL, " \t\r\n/"));
      } else if(strcmp(command, PING) == 0){
        recieve_ping(u, strtok(NULL, " \t\r\n/"));
      } else if(strcmp(command, PRIVMSG) == 0){
        recieve_privmsg(u, strtok(NULL, "\n"));
      } else if(strcmp(command, PART) == 0){
        recieve_part(u, strtok(NULL, "\n"));
      }

      command = strtok(NULL, " \t\r\n/");
    }

    pthread_mutex_lock(&u->socket_mutex);
    n = read(u->socket, recvline, MAXLINE);
    pthread_mutex_unlock(&u->socket_mutex);
  }
}
