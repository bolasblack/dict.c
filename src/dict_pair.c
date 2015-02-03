
//
// node.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include "dict.h"

/*
 * Allocates a new dict_pair_t. NULL on failure.
 */

dict_pair_t *
dict_pair_new(char *key, void *val) {
  dict_pair_t *self;
  if (!(self = DICT_MALLOC(sizeof(dict_pair_t))))
    return NULL;
  self->prev = NULL;
  self->next = NULL;
  self->key = key;
  self->val = val;
  return self;
}
