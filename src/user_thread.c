#include "user_thread.h"

void user_thread(User* u){
  char recvline[MAXLINE + 1];
  char* line = malloc((MAXLINE + 1) * sizeof(char));
  char send_line = malloc((MAXLINE + 1) * sizeof(char));
  ssize_t n;

  pthread_mutex_lock(&(u -> socket_mutex));
  n = read(&u -> socket, recvline, MAXLINE);
  pthread_mutex_unlock(&(u -> socket_mutex));

  while(n > 0){
    recvline[n] = 0;
    line = strcpy(line, recvline);
    command = strtok(line, " \t\r\n/");
    while (command != NULL) {
      printf("L'utente: %i ha inviato il comando: %s\n",u -> id, command);
      /*Qui parte lo switch di comparazaione con i comandi conosciuti*/
    }
  }
}
