
//
// iterator.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include "dict.h"

/*
 * Allocate a new dict_iterator_t. NULL on failure.
 */

dict_iterator_t *
dict_iterator_new(dict_t *dict) {
  dict_pair_t *pair = dict->head;

  dict_iterator_t *self;
  if (!(self = DICT_MALLOC(sizeof(dict_iterator_t))))
    return NULL;
  self->next = pair;

  return self;
}

/*
 * Return the next dict_pair_t or NULL when no more
 * nodes remain in the dict.
 */

dict_pair_t *
dict_iterator_next(dict_iterator_t *self) {
  dict_pair_t *curr = self->next;
  if (curr)
    self->next = curr->next;
  return curr;
}

/*
 * Free the dict iterator.
 */

void
dict_iterator_destroy(dict_iterator_t *self) {
  DICT_FREE(self);
  self = NULL;
}
