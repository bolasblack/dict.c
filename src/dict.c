//
// dict.c
//
// Copyright (c) 2015 c4605 <bolasblack@gmail.com>
//

#include "dict.h"

/*
 * Allocate a new dict_t. NULL on failure.
 */

dict_t *
dict_new() {
  dict_t *self;
  if (!(self = DICT_MALLOC(sizeof(dict_t))))
    return NULL;
  self->head = NULL;
  self->tail = NULL;
  self->free = NULL;
  return self;
}

/*
 * Free the dict.
 */

void
dict_destroy(dict_t *self) {
  dict_pair_t *next;
  dict_pair_t *curr = self->head;

  while (curr) {
    next = curr->next;
    if (self->free) self->free(curr->key, curr->val);
    DICT_FREE(curr);
    curr = next;
  }

  DICT_FREE(self);
}

/*
 * Add a key-value pair to dict.
 */

dict_pair_t *
dict_set(dict_t *self, char *key, void *val) {
  dict_pair_t *pair = dict_get(self, key);

  if (pair) {
    if (self->free) self->free(pair->key, pair->val);
    pair->val = val;
  } else {
    pair = dict_pair_new(key, val);
    if (self->head) {
      pair->prev = self->tail;
      pair->next = NULL;
      self->tail->next = pair;
      self->tail = pair;
    } else {
      self->head = self->tail = pair;
      pair->prev = pair->next = NULL;
    }
  }

  return pair;
}

/*
 * Return the node associated to val or NULL.
 */

dict_pair_t *
dict_get(dict_t *self, char *key) {
  dict_iterator_t *it = dict_iterator_new(self);
  dict_pair_t *pair;

  while ((pair = dict_iterator_next(it))) {
    if (strcmp(key, pair->key) == 0) {
      dict_iterator_destroy(it);
      return pair;
    }
  }

  dict_iterator_destroy(it);
  return NULL;
}

/*
 * Remove the given node from the dict, freeing it and it's value.
 */

void
dict_remove(dict_t *self, char *key) {
  dict_pair_t *pair = dict_get(self, key);

  if (!pair) return;

  pair->prev
    ? (pair->prev->next = pair->next)
    : (self->head = pair->next);

  pair->next
    ? (pair->next->prev = pair->prev)
    : (self->tail = pair->prev);

  if (self->free) self->free(pair->key, pair->val);

  DICT_FREE(pair);
}
