/**
  * @file main.c
  * @author Edoardo Vanin <edoardo.vanin.1@studenti.unipd.it>
  * @date 17 Giugno 2017
  * @mainpage IRC server
  * IRC Server è un progetto sviluppato per l'esame di laboratorio
  * di ingegneria informatica dell'università di Padova.
  *
  * @section implementazione Cosa implmenta e cosa non implementa il server
  * Il server è un'implementazione molto semplificata del protocollo definitio
  * dalla RFC1459 (<https://tools.ietf.org/html/rfc1459>) in particolare implementa
  * i comandi
  *   - NICK
  *   - JOIN
  *   - MODE
  *   - WHO
  *   - WHOIS
  *   - PING
  *   - PRIVMSG
  *   - PART
  *   - QUIT
  *   - LIST
  *
  * Il server non gestisce a differenza di quanto dichiarato nel RFC1459 (<https://tools.ietf.org/html/rfc1459>)
  * le proprietà dei canali e degli utenti, non gestisce gli operatori dei canali quindi un utente non si può
  * chiamare il comando KICK su nessun utente e non è stato implementato l'invio di file tra utenti
  *
  * @section installazione Come installare il server
  * Una volta scaricati i sorgenti del progetto eseguire i seguenti comandi
  *   - cmake .
  *   - make
  *
  * Il primo serve a creare i file make per la compilazione, il secondo comando compila il progetto
  * creando gli eseguibili nella cartella bin/ il progetto include anche due programmi di test per
  * le due liste, Channel_list e User_list i sorgenti sono disponibili in test/
  *
  * I test file sono stati creati con il framework Check (<https://libcheck.github.io/check/>)
  *
  */

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include "user.h"
#include "channel.h"
#include "utils.h"
#include "user_thread.h"

int main(int argc, char const *argv[]) {

  int server_socket, user_socket;
  struct sockaddr_in server_address;
  struct sockaddr_in client_address;
  socklen_t client_address_size = sizeof(client_address);
  int u_id = 1000;
  char* username = malloc(8*sizeof(char));
  char temp[5];

  User* new_user;

  count = 0;// inizializzo a zero il contator di utenti

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
    //accept non è all'interno dell'if di decisione perché è una funzione bloccante
    if ((user_socket = accept(server_socket,
                            (struct sockaddr *) &client_address,
                            &client_address_size)) == -1 ) {
      fprintf(stderr, "[Errore chiamando accept: %s]\n", strerror(errno));
      exit(5);
    }

    // aggiunge l'utente alla lista se permesso
    if(count < MAXUSER){
      strcpy(username, "user"); //pulisco la stringa dal nome precendente
      sprintf(temp,"%d", u_id);
      strcat(username, temp);
      new_user = create_user( username,
                              inet_ntoa(client_address.sin_addr),
                              u_id,
                              user_socket);

      u_id = u_id + 1; //incrementa il contatore degli id
      pthread_mutex_lock(&main_user_list_mutex);
      add_user(&main_user_list,new_user);
      count = count + 1; //va a braccetto con la lista, deve andare qui
      pthread_mutex_unlock(&main_user_list_mutex);
      pthread_create(&(new_user -> thread), NULL, (void* (*)(void*))user_thread, new_user);
    } else { //troppi utenti glielo dico
      close(user_socket); // così rifiuto la connessione, chiudendo il socket
    }
  }

  return 0;
}
