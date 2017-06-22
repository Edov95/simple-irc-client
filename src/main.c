#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include "user.h"
#include "channel.h"
#include "util.h"

/*
  - inizializzare il socket
  - ascoltare la porta
  - accettare le richieste fino ad un max utenti
  - associare un thread ad ogni utente che si connette
  */

int main(int argc, char const *argv[]) {

  int server_socket, user_socket;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  socklen_t client_address_size = sizeof(client_address);
  int count = 0, u_id = 1000;

  User* new_user;


  printf("Hello, Word\n");

  if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "[Errore chiamando socket: %s\n", strerror(errno));
    exit(2);
  }

  bzero(&server_address,sizeof(server_address));
  server_address.sin_family       = AF_INET;
  server_address.sin_addr.s_addr  = htonl(INADDR_ANY);
  server_address.sin_port         = htons(6667);

  if(bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1) {
    fprintf(stderr, "[Errore in bind di: %s]\n", strerror(errno));
    exit(3);
  }

  if(listen(server_socket, 1) == -1) {
    fprintf(stderr, "[Errore chiamando listen: %s]\n", strerror(errno));
    exit(4);
  }

  printf("[Server inizializzato nella porta: %i.]\n", 6667);
  printf("[Premi Ctrl+C per uscire.]\n");

  while(1){
    if ((user_socket = accept(server_socket,
                            (struct sockaddr *) &client_address,
                            &client_address_size)) == -1 ) {
      fprintf(stderr, "[Errore chiamando accept: %s]\n", strerror(errno));
      exit(5);
    }

    // aggiunge l'utente alla lista se permesso
    if(count < MAXUSER){
      new_user = create_user( NOME_FAKE,
                              inet_ntoa(client_address.sin_addr),
                              u_id,
                              user_socket);

      u_id = u_id + 1; //incrementa il contatore degli id
      pthread_mutex_lock(&main_user_list_mutex);
      add_user(main_user_list,new_user);
      pthread_mutex_unlock(&main_user_list_mutex);
      count = count + 1;
    } else { //troppi utenti, libero l'utente
      send_connection_refuse(user_socket);      
    }

    pthread_create(&(new_user -> thread), NULL, (void* (*) (void*)) user_thread, new_user);

  }

  return 0;
}
