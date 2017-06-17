#include <check.h>
#include "channel.h"
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_channel_list){

  Channel_list* list = NULL;
  Channel* c = NULL;
  char* str;

  ck_assert(add_channel(&list,c) == -1);
  // popolo la lista
  for (int i = 0; i < 20; i++) {
    c = malloc(sizeof(Channel));
    c -> name = malloc(1024*sizeof(char));
    sprintf(c -> name,"%c%i",'#', i);
    ck_assert_int_eq(add_channel(&list,c),1);
  }

  //rimozione dei nodi centrali
  for (int i = 1; i < 19; i++) {
    sprintf(str,"%c%i",'#',i);
    c = remove_channel(&list, str);
    ck_assert_msg(c != NULL,"Errore in rimozione");
    free(c);
  }

  sprintf(str,"%c%i",'#',19);
  //rimozione in testa
  c = remove_channel(&list,str);
  ck_assert_msg(c != NULL,"Errore in rimozione");
  free(c);

  sprintf(str,"%c%i",'#',0);
  //rimozione quando ho un solo nodo
  c = remove_channel(&list,str);
  ck_assert_msg(c != NULL,"Errore in rimozione");
  free(c);

  // ripopolo la lista
  for (int i = 0; i < 20; i++) {
    c = malloc(sizeof(Channel));
    c -> name = malloc(1024*sizeof(char));
    sprintf(c -> name,"%c%i",'#', i);
    ck_assert_int_eq(add_channel(&list,c),1);
  }

  //rimozione in coda
  for (int i = 0; i < 20; i++) {
    sprintf(str,"%c%i",'#', i);
    c = remove_channel(&list,str);
    ck_assert_msg(c != NULL,"Errore in rimozione");
    free(c);
  }

}END_TEST

Suite * channel_suite(void)
{
  Suite *s;
  TCase *tc_core;
  s=suite_create("Channel_List");

  tc_core=tcase_create("Core");

  tcase_add_test(tc_core, test_channel_list);
  suite_add_tcase(s, tc_core);
  return s;
}

int main (void)
{
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = channel_suite();
  sr = srunner_create(s);

  srunner_run_all(sr,CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return(number_failed == 0) ? EXIT_SUCCESS :EXIT_FAILURE;
}
