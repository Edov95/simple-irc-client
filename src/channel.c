#include "channel.h"
#include "user.h"

/*CREATE CHANNEL*/
Channel* create_channel(string name){
  Channel* c = malloc(sizeof(Channel));
  c -> name = malloc(strlen(name) + 1);
  strcpy(c -> name, name);
  c -> users = NULL;
}

/*ADD USER*/
int add_user_to_channel(Channel** c,User* u){
  if(*c == NULL) return -1;
  return add_user(&((*c) -> users),u);
}

/*ADD Channel*/
int add_channel(Channel_list** list, Channel* c){
  // Canale nullo o già presente
  if(c == NULL || find_channel(*list,c->name) != NULL){
    return -1;
  }

  Channel_list* temp = malloc(sizeof(Channel_list)); // allocazione memoria
  temp -> payload = c; // inserisco il canale nel nodo di lista

  //gestisco il caso critico: il primo inserimento
  if(*list == NULL){
    temp -> prev = NULL;
    temp -> next = NULL;
  } else {
    //inserimento in testa
    temp -> prev = NULL;
    temp -> next = *list;
    (*list) -> prev = temp;
  }

  *list = temp; // riassegnazione della testa della lista

  return 1; // ritorno di successo
}

/*FIND CHANNEL*/
Channel* find_channel(Channel_list* list, string name){
  if (list == NULL || name == NULL ) return NULL;

  Channel_list* temp = list;

  //scorro la lista
  while (temp != NULL) {
    if(strcmp(temp -> payload -> name, name) == 0) {
      return temp -> payload;
    }
    temp = temp -> next;
  }

  return NULL;
}

/*REMOVE *CHANNEL*/
Channel* remove_channel(Channel_list** list, string name){
  if(*list == NULL) return NULL;

  Channel_list* temp = *list;

  //scorro la lista per portarmi al canale scelto
  while (strcmp(temp -> payload -> name, name) != 0) {
    if(temp -> next == NULL) {
      return NULL;
    } else {
      temp = temp -> next;
    }
  }

  if(temp -> next == NULL && temp -> prev == NULL){ //c'è un solo nodo
    (*list) = NULL;
  } else if(temp -> prev == NULL){ //caso in cui il nodo da rimuovere è il primo
    temp -> next -> prev = NULL;
    *list = (*list) -> next;
  } else if(temp -> next == NULL) { //devo rimuovere l'ultimo
    temp -> prev -> next = NULL;
  } else {
    temp -> prev -> next = temp -> next;
    temp -> next -> prev = temp -> prev;
  }

  Channel* chan = temp -> payload; //salvo il canale

  free(temp); // libero la cella di memoria puntata

  return chan; //ritoro il canale
}

/*PRITN LIST IN CHANNEL*/
void print_list_channel(Channel_list* list) {
  if(list == NULL) return;
  while(list != NULL){
    printf("Channel name's: %s\n", list -> payload -> name );
    list = list -> next;
  }
}

/*PRINT USERS IN CHANNEL*/
void print_users_in_channel(Channel* c){
  if(c == NULL) return;
  printf("Channel name's: %s\n", c -> name );
  printf("User in channel: \n");
  print_list(c -> users);
}

/*PRINT LIST CHANNEL AND USERS*/
void print_list_channel_and_users(Channel_list* list){
  if(list == NULL) return;

  if(list == NULL) return;
  while(list != NULL){
    printf("Channel name's: %s\n", list -> payload -> name );
    printf("User in channel: \n");
    print_list(list -> payload -> users);
    list = list -> next;
  }
}
