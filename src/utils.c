#include "utils.h"

void send_user_info(User* u, User* target, char* channel) {
  char* send_line = malloc(MAXLINE + 1);
  strcpy(send_line, ":");
  strcat(send_line, SERVER_NAME);
  strcat(send_line, " ");
  strcat(send_line, RPL_WHOREPLY);
  strcat(send_line, " ");
  strcat(send_line, u -> name);
  strcat(send_line, " ");
  if(channel != NULL){
    strcat(send_line, channel);
    strcat(send_line, " ");
  }
  /*
  for (size_t i = 0; i < 15; i++) {
    if(target -> channels[i] != NULL){
      strcat(send_line, " ");
      strcat(send_line, target -> channels[i]);
    }
  }
  strcat(send_line, " ");
  */
  strcat(send_line, target->name);
  strcat(send_line, " ");
  strcat(send_line, target->hostname);
  strcat(send_line, " ");
  strcat(send_line, SERVER_NAME);
  strcat(send_line, " ");
  strcat(send_line, target->name);
  strcat(send_line, " H :0 ");
  strcat(send_line, target->name);
  strcat(send_line, "\n");

  write(u -> socket, send_line, strlen(send_line));
  free(send_line);
}

void send_all_user_info(User* u){
  char* send_line = malloc(MAXLINE + 1);
  pthread_mutex_lock(&main_user_list_mutex);
  int is_in_the_same_channel;
  User_list* list = main_user_list;
  User* target = NULL;
  while (list != NULL) {
    is_in_the_same_channel = 0;
    target = list -> payload;
    for (size_t i = 0; i < 15; i++) {
      for (size_t j = 0; j < 15; j++) {
        if(target -> channels[i] != NULL &&
           u -> channels[j] != NULL &&
           u -> id != target -> id &&
           strcmp(target -> channels[i], u -> channels[j]) == 0){
             i = j = 15;
             is_in_the_same_channel = 1;
           }
      }
    }
    if(!is_in_the_same_channel){
      send_user_info(u, target, NULL);
    }
    list = list -> next;
  }
  pthread_mutex_unlock(&main_user_list_mutex);

  strcpy(send_line, ":");
  strcat(send_line, SERVER_NAME);
  strcat(send_line, " ");
  strcat(send_line, RPL_ENDOFWHO);
  strcat(send_line, " ");
  strcat(send_line, u -> name);
  strcat(send_line, " * ");
  strcat(send_line, ENDOFWHO);
  write(u -> socket, send_line, strlen(send_line));

  printf("Qui\n");
  free(send_line);
  printf("Qui2\n");
}

void send_channel_info(User* u, Channel* c) {
  User_list* list = c -> users;
  User* target;
  char* send_line = malloc(MAXLINE + 1);
  while (list != NULL) {
    target = list -> payload;
    send_user_info(u, target, c -> name);
    list = list -> next;
  }

  strcpy(send_line, ":");
  strcat(send_line, SERVER_NAME);
  strcat(send_line, " ");
  strcat(send_line, RPL_ENDOFWHO);
  strcat(send_line, " ");
  strcat(send_line, u -> name);
  strcat(send_line, " * ");
  strcat(send_line, ENDOFWHO);
  write(u -> socket, send_line, strlen(send_line));

  free(send_line);
}
