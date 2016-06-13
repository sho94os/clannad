// Vector is a dynamic list of void pointers

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "clannad.h"

Vector*
create_vector()
{
  Vector *ret = malloc(sizeof(Vector));
  ret->length = 0;
  return ret;
}

void
realloc_vector(Vector *vec, int length)
{
  void **ptr = (void **)realloc(vec->data, length * sizeof(void *));
  memset(ptr + (length - 1) * sizeof(void *), 0, sizeof(void *));
  vec->data = ptr;
}

void*
vector_get(Vector *vec, int index)
{
  assert(index < vec->length);
  return vec->data[index];
}

void
vector_push(Vector *vec, void *ptr)
{
  vec->length++;
  realloc_vector(vec, vec->length);
  vec->data[vec->length - 1] = ptr;
}
