#include "../include/user.h"

/*ADD USER*/
int add_user(User_list** list, User* user){
  if( find_by_id(_list,user->id) != NULL ) // L'utente è già presente nella lista
    return -1;

  User_list* temp = malloc(sizeof(User_list)); // allocazione memoria
  temp -> payload = user; // inserisco l'utene nel nodo di lista

  //gestisco il caso critico: il primo inserimento
  if(list == NULL){
    temp -> prev = NULL;
    temp -> next = NULL;
  } else {
    //inserimento in testa
    temp -> prev = NULL;
    temp -> next = list;
    (*list) -> prev = temp;
  }

  *list = temp; // riassegnazione della testa della lista

  return 1; // ritorno di successo
}

/*FIND BY ID*/
User* find_by_id(User_list* list, int id){
  if (list == NULL) return NULL;

  User_list* temp = list;

  //scorro la lista
  while (temp -> payload -> id != id) {
    if(temp -> next == NULL) {
      return NULL;
    } else {
      temp = temp -> next;
    }
  }
  return temp -> payload;
}

/*FIND BY USERNAME*/
User* find_by_username(User_list* list, string username){
  if (list == NULL || username == NULL ) return NULL;

  User_list* temp = list;

  //scorro la lista
  while (strcmp(temp -> payload -> username, username) != 0) {
    if(temp -> next == NULL) {
      return NULL;
    } else {
      temp = temp -> next;
    }
  }
  return temp -> payload;
}

/*REMOVE BY ID*/
User* remove_user_by_id(User_list* list, int id){
  if(list == NULL) return NULL;

  User_list* temp = list;

  //scorro la lista
  while (temp -> payload -> id != id) {
    if(temp -> next == NULL) {
      return NULL;
    } else {
      temp = temp -> next;
    }
  }

  //rimozione del nodo dalla lista
  temp -> prev -> next = temp -> next;
  temp -> next -> prev = temp -> prev;

  User* user = temp -> payload; //salvo l'utente

  free(temp); // libero la cella di memoria puntata

  return user; //ritoro l'utente
}

/*REMOVE BY USERNAME*/
User* remove_user_by_username(User_list* list, string username){
  if(list == NULL || username == NULL) return NULL;

  /*Al posto di iterare la lista sfrutto la funzione find_by_username
  per trovare l'utende da eliminare e poi, grazie alla finzione
  remove_user_by_id lo rimuovo */

  User* temp = find_by_username(list,username);
  if(temp == NULL) return NULL;

  return remove_user_by_id(list, temp->id);
}
