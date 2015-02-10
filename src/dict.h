//
// dict.h
//
// Copyright (c) 2015 c4605 <bolasblack@gmail.com>
//

#ifndef DICT_H
#define DICT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>

// Library version

#define DICT_VERSION "0.0.1"

// Memory management macros

#ifndef DICT_MALLOC
#define DICT_MALLOC malloc
#endif

#ifndef DICT_FREE
#define DICT_FREE free
#endif

/*
 * dict_t pair struct.
 */

typedef struct dict_pair {
  struct dict_pair *prev;
  struct dict_pair *next;
  char *key;
  void *val;
} dict_pair_t;

/*
 * dict_t struct.
 */

typedef struct {
  dict_pair_t *head;
  dict_pair_t *tail;
  void (*free)(char *key, void *val);
} dict_t;

/*
 * dict_t iterator struct.
 */

typedef struct {
  dict_pair_t *next;
} dict_iterator_t;

// Node prototypes.

dict_pair_t *
dict_pair_new(char *key, void *val);

// list_t prototypes.

dict_t *
dict_new();

dict_pair_t *
dict_set(dict_t *self, char *key, void *val);

dict_pair_t *
dict_get(dict_t *self, char *key);

void
dict_remove(dict_t *self, char *key);

void
dict_destroy(dict_t *self);

// dict_t iterator prototypes.

dict_iterator_t *
dict_iterator_new(dict_t *dict);

dict_pair_t *
dict_iterator_next();

void
dict_iterator_destroy(dict_iterator_t *self);

#ifdef __cplusplus
}
#endif

#endif /* DICT_H */
