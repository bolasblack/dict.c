
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "src/dict.h"

// Helpers

#define test(fn) \
  puts("... \x1b[33m" # fn "\x1b[0m"); \
  test_##fn();

static int freeProxyCalls = 0;

void
freeProxy(char *key, void *val) {
  ++freeProxyCalls;
  free(val);
}

typedef struct {
  char *name;
} User;

static int
User_equal(User *a, User *b) {
  return 0 == strcmp(a->name, b->name);
}

// Tests

static void
test_dict_pair_new() {
  char *key = "some key";
  char *val = "some value";
  dict_pair_t *pair = dict_pair_new(key, val);
  assert(pair->key == key);
  assert(pair->val == val);
  free(pair);
}

static void
test_dict_destroy() {
  // Setup
  dict_t *a = dict_new();
  dict_destroy(a);

  // a b c
  dict_t *b = dict_new();
  int *val_a = 1;
  int *val_b = 2;
  int *val_c = 3;
  dict_set(b, "a", val_a);
  dict_set(b, "b", val_b);
  dict_set(b, "c", val_c);
  dict_destroy(b);

  // Assertions
  dict_t *c = dict_new();
  c->free = freeProxy;
  dict_set(c, "a", dict_pair_new("a", val_a));
  dict_set(c, "b", dict_pair_new("b", val_b));
  dict_set(c, "c", dict_pair_new("c", val_c));
  dict_destroy(c);
  assert(3 == freeProxyCalls);
}

static void
test_dict_set() {
  // Setup
  dict_t *dict = dict_new();
  dict_pair_t *a = dict_set(dict, "a", "a");
  dict_pair_t *b = dict_set(dict, "b", "b");
  dict_pair_t *c = dict_set(dict, "c", "c");
  b = dict_set(dict, "b", "d");

  // Assertions
  assert(a == dict->head);
  assert(c == dict->tail);
  assert(b == a->next);
  assert(NULL == a->prev);
  assert(c == b->next);
  assert(a == b->prev);
  assert(NULL == c->next);
  assert(b == c->prev);
  assert(strcmp(a->key, "a") == 0);
  assert(strcmp(a->val, "a") == 0);
  assert(strcmp(b->key, "b") == 0);
  assert(strcmp(b->val, "d") == 0);
  assert(strcmp(c->key, "c") == 0);
  assert(strcmp(c->val, "c") == 0);

  dict_destroy(dict);
}

static void
test_dict_get() {
  dict_t *langs = dict_new();
  dict_pair_t *js = dict_set(langs, "js", "js");
  dict_pair_t *ruby = dict_set(langs, "ruby", "ruby");

  dict_pair_t *a = dict_get(langs, "js");
  dict_pair_t *b = dict_get(langs, "ruby");
  dict_pair_t *c = dict_get(langs, "foo");
  assert(js == a);
  assert(ruby == b);
  assert(NULL == c);

  dict_destroy(langs);

  dict_t *users = dict_new();
  User userTJ = { "tj" };
  User userSimon = { "simon" };
  User userTaylor = { "taylor" };
  dict_pair_t *tj = dict_set(users, "tj", &userTJ);
  dict_pair_t *simon = dict_set(users, "sinon", &userSimon);

  a = dict_get(users, "tj");
  b = dict_get(users, "sinon");
  c = dict_get(users, "taylor");
  assert(tj == a);
  assert(simon == b);
  assert(NULL == c);

  dict_destroy(users);
}

static void
test_dict_remove() {
  // Setup
  dict_t *dict = dict_new();
  dict_pair_t *a = dict_set(dict, "a", "a");
  dict_pair_t *b = dict_set(dict, "b", "b");
  dict_pair_t *c = dict_set(dict, "c", "c");

  dict_remove(dict, "b");
  assert(a == dict->head);
  assert(c == dict->tail);
  assert(c == a->next);
  assert(NULL == a->prev);
  assert(NULL == c->next);
  assert(a == c->prev);

  dict_remove(dict, "a");
  assert(c == dict->head);
  assert(c == dict->tail);
  assert(NULL == c->next);
  assert(NULL == c->prev);

  dict_remove(dict, "c");
  assert(NULL == dict->head);
  assert(NULL == dict->tail);

  dict_destroy(dict);
}

static void
test_dict_iterator_t() {
  // Setup
  dict_t *dict = dict_new();
  dict_pair_t *tj = dict_set(dict, "tj", "tj");
  dict_pair_t *taylor = dict_set(dict, "taylor", "taylor");
  dict_pair_t *simon = dict_set(dict, "simon", "simon");

  // Assertions

  // From head
  dict_iterator_t *it = dict_iterator_new(dict);
  dict_pair_t *a = dict_iterator_next(it);
  dict_pair_t *b = dict_iterator_next(it);
  dict_pair_t *c = dict_iterator_next(it);
  dict_pair_t *d = dict_iterator_next(it);

  assert(a == tj);
  assert(b == taylor);
  assert(c == simon);
  assert(NULL == d);

  dict_iterator_destroy(it);
  dict_destroy(dict);
}

int
main(void){
  printf("\ndict_t: %ld\n", sizeof(dict_t));
  printf("dict_pair_t: %ld\n", sizeof(dict_pair_t));
  printf("dict_iterator_t: %ld\n\n", sizeof(dict_iterator_t));
  test(dict_pair_new);
  test(dict_set);
  test(dict_get);
  test(dict_remove);
  test(dict_destroy);
  test(dict_iterator_t);
  puts("... \x1b[32m100%\x1b[0m\n");
  return 0;
}
