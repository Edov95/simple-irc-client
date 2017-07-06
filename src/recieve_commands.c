#include "recieve_commands.h"

void recieve_nick(User* u, User_list* list, char* name){

  char* send_line = malloc(MAXLINE + 1);
  strcpy(send_line, ":");
  strcat(send_line, u -> name);
  strcat(send_line, "!");
  strcat(send_line, u -> hostname);
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
    change_name(&u,name);
    strcat(send_line, NICK);
    strcat(send_line, " :");
    strcat(send_line, name);
    strcat(send_line, "\n");
    write(u->socket, send_line, strlen(send_line));
    User_list* list_tmp;
    User* user_tmp;
    Channel* c;
    // cazzo mene lo invio a tutti
    for(int i = 0; i < 15; i++){
      if(u -> channels[i] != NULL){
        pthread_mutex_lock(&main_channel_list_mutex);
        c = find_channel(main_channel_list, u -> channels[i]);
        pthread_mutex_unlock(&main_channel_list_mutex);
        list_tmp = c -> users;
        while (list_tmp != NULL) {
          user_tmp = list_tmp -> payload;
          write(user_tmp -> socket, send_line, strlen(send_line));
          list_tmp = list_tmp -> next;
        }
      }
    }
    free(send_line);
    return;
  }

  write(u -> socket, send_line, strlen(send_line));

  free(send_line);
  return;
}

void recieve_user(User* u){
  char* send_line = malloc(MAXLINE + 1);
  strcpy(send_line, WELCOME_02);
  strcat(send_line, WELCOME_03);
  strcat(send_line, WELCOME_USER_01);
  strcat(send_line, u -> name);
  strcat(send_line, WELCOME_USER_02);
  strcat(send_line, u -> hostname);
  strcat(send_line, "\n");
  write(u -> socket, send_line, strlen(send_line));
  free(send_line);
}

/* JOIN */
void recieve_join(User* u, char* channel){
  // qua sarà divertente XD
  char* send_line = malloc(MAXLINE + 1);

  if(channel[0] != '#' && channel[0] != '&'){ //ERR_NOSUCHCHANNEL
    printf("%s\n",channel);
    printf("%c\n",channel[0]);
    strcat(send_line, ":");
    strcat(send_line, SERVER_NAME);
    strcat(send_line, " ");
    strcat(send_line, ERR_NOSUCHCHANNEL);
    strcat(send_line, " ");
    strcat(send_line, u -> name);
    strcat(send_line, channel);
    strcat(send_line, " :No such channel");

    write(u -> socket, send_line, strlen(send_line));
    free(send_line);
    return;
  }

  //eseguo operazioni per aggiungere il canale oppure entrarci
  int max_chan = 1;
  pthread_mutex_lock(&main_channel_list_mutex);
  Channel* c = find_channel(main_channel_list, channel);

  for (size_t i = 0; i < 15; i++) {
    //se almeno una stringa del vettore punta a NULL vuol dire che non ho raggiunto il numero massimo di canali
    if(u -> channels[i] == NULL){
      if(c == NULL){
        //aggiungo il canale alla lista canali
        c = create_channel(channel, NULL);
        add_channel(&main_channel_list,c);
      }
      //se riesce ad aggiungere l'utente, vuol dire che non era già presente nel canale
      // il caso "l'utente è già nel canale" viene gestito da client
      if(add_user(&(c -> users), u) != -1){
        c -> number_users = c -> number_users + 1;
        (u -> channels[i]) = malloc(30);
        strcpy(u -> channels[i], channel); //aggiorno la lista canali
        //add_user(&(c -> users), u);//aggiungo l'utente alla lista utenti
      }

      max_chan = 0; //l'utente non ha raggiunto il numero massimo di canali
      i = 15;
    }
  }
  pthread_mutex_unlock(&main_channel_list_mutex);

  if(max_chan){
    //compongo errore "troppi canali"
    strcpy(send_line, ":");
    strcat(send_line, SERVER_NAME);
    strcat(send_line, " ");
    strcat(send_line, ERR_TOOMANYCHANNELS);
    strcat(send_line, " ");
    strcat(send_line, u -> name);
    strcat(send_line, " :Too many channels");
  } else {
    //compongo la stringa di avvenuta JOIN
    strcpy(send_line, ":");
    strcat(send_line, u -> name);
    strcat(send_line, "!");
    strcat(send_line, u -> hostname);
    strcat(send_line, " ");
    strcat(send_line, JOIN);
    strcat(send_line, " :");
    strcat(send_line, channel);
    strcat(send_line, "\n");
  }

  // invio la notifica di join all'utente sia essa too many channels oppure join
  write(u -> socket, send_line, strlen(send_line));

  if(!max_chan){
    strcpy(send_line, "");
    //invio la lista utenti a tutti
    User_list* list = c -> users;
    User* temp;

    while (list != NULL) {
      temp = list -> payload;
      strcat(send_line, ":");
      strcat(send_line, SERVER_NAME);
      strcat(send_line, " ");
      strcat(send_line, RPL_NAMREPLY);
      strcat(send_line, " ");
      strcat(send_line, u -> name);
      strcat(send_line, " @ ");
      strcat(send_line, channel);
      strcat(send_line, " :");
      strcat(send_line, temp -> name);
      strcat(send_line, "\n");
      list = list -> next;
    }

    strcat(send_line, "\n");
    strcat(send_line, ":");
    strcat(send_line, SERVER_NAME);
    strcat(send_line, " ");
    strcat(send_line, RPL_ENDOFNAMES);
    strcat(send_line, " ");
    strcat(send_line, u -> name);
    strcat(send_line, " ");
    strcat(send_line, channel);
    strcat(send_line, ENDOFNAMES);
    strcat(send_line, "\n");

    list = c -> users;
    while (list != NULL) {
      temp = list -> payload;
      write(temp -> socket, send_line, strlen(send_line)); // invio la notifica names agli utenti
      list = list -> next;
    }
  }

  // invio a tutti gli utenti di chan che sono entrato :)

  free(send_line);
}

/*MODE*/
void recieve_mode(User* u, char* umode){
  char* send_line = malloc(MAXLINE + 1);
  if(umode != NULL) {
    strcpy(send_line, ":");
    strcat(send_line, u -> name);
    strcat(send_line, " ");
    strcat(send_line, MODE);
    strcat(send_line, " ");
    strcat(send_line, u -> name);
    strcat(send_line, " ");
    strcat(send_line, umode);
    strcat(send_line, "\n");

    write(u -> socket, send_line, strlen(send_line));
  }
  free(send_line);
}

/*WHO BESTEMMIE*/
void recieve_who(User* u, char* query){

  char* send_line = malloc(MAXLINE + 1);
  bzero(send_line, MAXLINE + 1);
  User* temp;
  Channel *c;

  if (query == NULL) { //se chiede info su tutti gli utenti
    send_all_user_info(u);
  } else {
    pthread_mutex_lock(&main_user_list_mutex);
    temp = find_by_username(main_user_list, query);
    pthread_mutex_unlock(&main_user_list_mutex);

    pthread_mutex_lock(&main_channel_list_mutex);
    c = find_channel(main_channel_list, query);
    pthread_mutex_unlock(&main_channel_list_mutex);

    if(temp == NULL && c == NULL){
      strcpy(send_line, ":");
      strcat(send_line, SERVER_NAME);
      strcat(send_line, " ");
      strcat(send_line, ERR_NOSUCHCHANNEL);
      strcat(send_line, " ");
      strcat(send_line, u -> name);
      strcat(send_line, " ");
      strcat(send_line, query);
      strcat(send_line, " :No such user/channel\n");
      strcat(send_line, ":");
      strcat(send_line, SERVER_NAME);
      strcat(send_line, " ");
      strcat(send_line, RPL_ENDOFWHO);
      strcat(send_line, " ");
      strcat(send_line, u -> name);
      //strcat(send_line, " * ");
      strcat(send_line, ENDOFWHO);
      write(u -> socket, send_line, strlen(send_line));
    } else if(temp != NULL){
      send_user_info(u, temp, NULL);
      strcpy(send_line, ":");
      strcat(send_line, SERVER_NAME);
      strcat(send_line, " ");
      strcat(send_line, RPL_ENDOFWHO);
      strcat(send_line, " ");
      strcat(send_line, u -> name);
      //strcat(send_line, " * ");
      strcat(send_line, ENDOFWHO);
      write(u -> socket, send_line, strlen(send_line));
    } else if(c != NULL){
      send_channel_info(u,c);
    }
  }

  free(send_line);
}

/*WHOIS*/
void recieve_whois(User* u, char* query){

  char* send_line = malloc(MAXLINE + 1);

  pthread_mutex_lock(&main_user_list_mutex);
  User* user = find_by_username(main_user_list, query);
  pthread_mutex_unlock(&main_user_list_mutex);

  if(user != NULL){
    strcpy(send_line, ":");
    strcat(send_line, SERVER_NAME);
    strcat(send_line, " ");
    strcat(send_line, RPL_WHOISUSER);
    strcat(send_line, " ");
    strcat(send_line, user->name);
    strcat(send_line, " ");
    strcat(send_line, user->name);
    strcat(send_line, " ~");
    strcat(send_line, user->name);
    strcat(send_line, " ");
    strcat(send_line, user->hostname);
    strcat(send_line, " :");
    strcat(send_line, user->name);
    strcat(send_line, "\n");

    strcat(send_line, ":");
    strcat(send_line, SERVER_NAME);
    strcat(send_line, " ");
    strcat(send_line, RPL_WHOISSERVER);
    strcat(send_line, " ");
    strcat(send_line, user->name);
    strcat(send_line, " ");
    strcat(send_line, user->name);
    strcat(send_line, " ");
    strcat(send_line, SERVER_NAME);
    strcat(send_line, " ");
    strcat(send_line, SERVER_INFO);
    strcat(send_line, "\n");

    strcat(send_line, ":");
    strcat(send_line, SERVER_NAME);
    strcat(send_line, " ");
    strcat(send_line, RPL_ENDOFWHOIS);
    strcat(send_line, " ");
    strcat(send_line, u -> name);
    strcat(send_line, " ");
    strcat(send_line, user->name);
    strcat(send_line, ENDOFWHOIS);

  } else {
    strcpy(send_line, ":");
    strcat(send_line, SERVER_NAME);
    strcat(send_line, " ");
    strcat(send_line, RPL_ENDOFWHOIS);
    strcat(send_line, " ");
    strcat(send_line, u -> name);
    strcat(send_line, " ");
    strcat(send_line, query);
    strcat(send_line, ENDOFWHOIS);
  }

  write(u -> socket, send_line, strlen(send_line));
  free(send_line);
}

/*PING*/
void recieve_ping(User* u, char* ping_message){
  char* send_line = malloc(MAXLINE + 1);
  strcpy(send_line, DEFAULT_PONG);
  strcat(send_line, ping_message);
  strcat(send_line, "\n");
  write(u -> socket, send_line, strlen(send_line));
  free(send_line);
}

/*PRIVMSG*/
void recieve_privmsg(User* u, char* message){
  char* send_line = malloc(MAXLINE + 1);
  char* target = strtok(message, " \t\r\n/");
  char* send_message = strtok(NULL, "\n");
  Channel* c;

  pthread_mutex_lock(&main_channel_list_mutex);
  c = find_channel(main_channel_list, target);
  pthread_mutex_unlock(&main_channel_list_mutex);

  //non faccio controlli sull'esistenza dell canale perché
  //effettivamente il comando parte solo se l'utente è nel canale
  strcpy(send_line, ":");
  strcat(send_line, u -> name);
  strcat(send_line, "!");
  strcat(send_line, u -> hostname);
  strcat(send_line, " ");
  strcat(send_line, PRIVMSG);
  strcat(send_line, " ");
  strcat(send_line, target);
  strcat(send_line, " ");
  strcat(send_line, send_message);
  strcat(send_line, "\n");

  User_list* list = c -> users;
  User* temp;
  while (list != NULL) {
    temp = list -> payload;
    if(temp -> id != u -> id){
      write(temp -> socket, send_line, strlen(send_line));
    }
    list = list -> next;
  }
  free(send_line);
}

/*PART*/
void  recieve_part(User* u, char* parameter) {
  int len = strlen(parameter);
  char* send_line = malloc(MAXLINE + 1);
  char* channel = strtok(parameter, " \t\r\n/");
  char* leave_msg;

  //se hanno la stessa lunghezza non c'è il leave message
  if(len != strlen(channel)){
    leave_msg = strtok(NULL, "\n");
  }

  Channel* c;

  pthread_mutex_lock(&main_channel_list_mutex);
  c = find_channel(main_channel_list, channel);
  pthread_mutex_unlock(&main_channel_list_mutex);

  //prima di rimuovere il canale e l'utente devo inviare il comando di risposta
  strcpy(send_line, ":");
  strcat(send_line, u -> name);
  strcat(send_line, "!");
  strcat(send_line, u -> hostname);
  strcat(send_line, " ");
  strcat(send_line, PART);

  strcat(send_line, " ");
  strcat(send_line, channel);
  strcat(send_line, " ");
  strcat(send_line, leave_msg);
  strcat(send_line, "\n");


  User_list* list = c -> users;
  User* temp;
  while (list != NULL) {
    temp = list -> payload;
    write(temp -> socket, send_line, strlen(send_line));
    list = list -> next;
  }

  remove_user_by_id(&(c -> users), u -> id);

  for (size_t i = 0; i < 15; i++) {
    if(u -> channels[i] != NULL &&
       strcmp(u -> channels[i], channel) == 0) {
      free((u -> channels[i]));
      u -> channels[i] = NULL;
      //i = 15;
    }
  }
  //se u è l'unico utente elimino il canale dalla lista canali
  if(c -> users == NULL){
    pthread_mutex_lock(&main_channel_list_mutex);
    remove_channel(&main_channel_list, c -> name);
    pthread_mutex_unlock(&main_channel_list_mutex);
    free((c -> name));
    free((c -> topic));
    free(c); //ho eliminato il canale :)
  } else {
    c -> number_users = c -> number_users - 1;
  }
  free(send_line);
}

/*QUIT*/
void recieve_quit(User* u, char* parameter){

  User* temp;
  char* str_temp = malloc(MAXLINE + 1);

  //esco da tutti i canali in cui sono collegato
  for (size_t i = 0; i < 15; i++) {
    if(u -> channels[i] != NULL){
      strcpy(str_temp, u -> channels[i]);
      recieve_part(u, str_temp);
    }
  }

  // chiudo la connessione
  pthread_mutex_lock(&u -> socket_mutex);
  close(u -> socket);
  pthread_mutex_unlock(&u -> socket_mutex);

  //rimuovo l'utente dalla lista utenti
  pthread_mutex_lock(&main_user_list_mutex);
  remove_user_by_id(&main_user_list, u -> id);
  count = count - 1;
  pthread_mutex_unlock(&main_user_list_mutex);

  //libero le zone di memoria occupate dall'utente
  for (size_t i = 0; i < 15; i++) {
    if(u -> channels[i] != NULL){
      free(u -> channels[i]);
    }
  }

  free(u -> name);
  free(u -> hostname);

  free(u);

  free(str_temp);

}

/*LIST*/
void recieve_list(User* u){
  char* send_line = malloc(MAXLINE + 1);

  strcpy(send_line, ":");
  strcat(send_line, SERVER_NAME);
  strcat(send_line, " ");
  strcat(send_line, RPL_LISTSTART);
  strcat(send_line, " ");
  strcat(send_line, u -> name);
  strcat(send_line, LIST_HEADER);

  pthread_mutex_lock(&main_channel_list_mutex);
  Channel_list* list = main_channel_list;
  while (list != NULL) {
    strcat(send_line, ":");
    strcat(send_line, SERVER_NAME);
    strcat(send_line, " ");
    strcat(send_line, RPL_LIST);
    strcat(send_line, " ");
    strcat(send_line, u -> name);
    strcat(send_line, " ");
    strcat(send_line, list -> payload -> name);
    strcat(send_line, " %i");
    sprintf(send_line, send_line, list -> payload -> number_users);
    strcat(send_line, " ");
    if(list -> payload -> topic != NULL)
      strcat(send_line, list -> payload -> topic);
    strcat(send_line, "\n");
    list = list -> next;
  }
  pthread_mutex_unlock(&main_channel_list_mutex);

  strcat(send_line, ":");
  strcat(send_line, SERVER_NAME);
  strcat(send_line, " ");
  strcat(send_line, RPL_LISTEND);
  strcat(send_line, " ");
  strcat(send_line, u -> name);
  //strcat(send_line, " ");
  strcat(send_line, LIST_END);

  write(u -> socket, send_line, strlen(send_line));
  free(send_line);
}
/*
void recieve_topic(User* u, char* parameter){
  int len = strlen(parameter);
  char* send_line = malloc(MAXLINE + 1);
  char* channel = strtok(parameter, " \t\r\n/");
  char* topic;

  //se hanno la stessa lunghezza non c'è il leave message
  if(len != strlen(channel)){
    topic = strtok(NULL, "\n");
  }

  pthread_mutex_lock(&main_channel_list_mutex);
  Channel* c = find_channel(main_channel_list, channel);
  pthread_mutex_unlock(&main_channel_list_mutex);

  change_topic(c,topic);
}
*/
