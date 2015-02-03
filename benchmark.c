
#include <stdio.h>
#include "bench/bench.h"
#include "src/dict.h"

static void
bm(char *label, void (*fn)()) {
  printf(" %18s", label);
  fflush(stdout);
  fn();
}

static int nnodes = 10000;
static float startTime;
static dict_t *s_dict;


static void
to_string(int num, char *str) {
  sprintf(str, "%d", num);
}

static dict_t *
create_dict() {
  int n = nnodes;
  if (!s_dict) {
    s_dict = dict_new();
    while (n--) {
      char *str = malloc(6);
      to_string(n, str);
      dict_set(s_dict, str, str);
    }
  }
  return s_dict;
}


static void
start() {
  startTime = cpu();
}

static void
stop() {
  float duration = cpu() - startTime;
  printf(": \x1b[32m%.4f\x1b[0ms\n", duration);
}

static void
bm_set() {
  int n = nnodes;
  dict_t *dict = dict_new();
  start();
  while (n--) {
    char *str = malloc(6);
    to_string(n, str);
    dict_set(dict, str, str);
  }
  stop();
  dict_destroy(dict);
}

static void
bm_get() {
  start();
  dict_get(s_dict, "1");
  stop();
}

static void
bm_iterate() {
  dict_iterator_t *it = dict_iterator_new(s_dict);
  dict_pair_t *pair;
  start();
  while ((pair = dict_iterator_next(it)))
    ;
  stop();
}

int
main(void){
  create_dict();
  puts("\n 10,000 piars\n");
  bm("set", bm_set);
  bm("get", bm_get);
  bm("iterate", bm_iterate);
  puts("");
  dict_destroy(s_dict);
  return 0;
}
