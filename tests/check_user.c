#include <check.h>
#include "user.h"
#include <stdio.h>
#include <stdlib.h>

START_TEST(test_user_list){

  User_list* list = NULL;

  User* u = NULL;

  ck_assert_int_eq(add_user(&list,u),-1);

  // popolo la lista
  for (size_t i = 0; i < 20; i++) {
    u = malloc(sizeof(User));
    u -> id = i;
    ck_assert_int_eq(add_user(&list,u),1);
  }

  //rimozione dei nodi centrali
  for (size_t i = 1; i < 19; i++) {
    u = remove_user_by_id(&list,i);
    ck_assert_msg(u != NULL,"Errore in rimozione");
    free(u);
  }

  //rimozione in testa
  u = remove_user_by_id(&list,19);
  ck_assert_msg(u != NULL,"Errore in rimozione");
  free(u);

  //rimozione quando ho un solo nodo
  u = remove_user_by_id(&list,0);
  ck_assert_msg(u != NULL,"Errore in rimozione");
  free(u);

  // ripopolo la lista
  for (size_t i = 0; i < 20; i++) {
    u = malloc(sizeof(User));
    u -> id = i;
    ck_assert_int_eq(add_user(&list,u),1);
  }

  //rimozione in coda
  for (size_t i = 0; i < 20; i++) {
    u = remove_user_by_id(&list,i);
    ck_assert_msg(u != NULL,"Errore in rimozione");
    free(u);
  }

}END_TEST

Suite * user_suite(void)
{
  Suite *s;
  TCase *tc_core;
  s=suite_create("User_List");

  tc_core=tcase_create("Core");

  tcase_add_test(tc_core, test_user_list);
  suite_add_tcase(s, tc_core);
  return s;
}

int main (void)
{
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = user_suite();
  sr = srunner_create(s);

  srunner_run_all(sr,CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return(number_failed == 0) ? EXIT_SUCCESS :EXIT_FAILURE;
}
