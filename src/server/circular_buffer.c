#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"

void strncircular(t_circular *c, char *str, int n)
{
  int i;
  int cpos;

  i = 0;
  cpos = c->pos + c->len;
  while (i < n)
  {
    c->buffer[cpos] = str[i];
    INCR(cpos);
    ++i;
    ++c->len;
  }
}

static bool end(t_circular *c, int pos)
{
  return (c->buffer[pos] == '\r' &&
          c->buffer[INCR(pos)] == '\n');
}

bool find_command(t_circular *c)
{
  int pos;
  int i;

  i = 0;
  pos = c->pos;
  while (i < c->len)
  {
    if (end(c, pos))
      return (true);
    ++i;
    INCR(pos);
  }
  return (false);
}

bool strfromcircular(t_circular *c, char out[MESSAGE_MAX_SIZE])
{
  int i;

  i = 0;
  memset(out, 0, MESSAGE_MAX_SIZE);
  printf("socket buffer = !%s!\n", c->buffer);
  while (!end(c, c->pos) && i < MESSAGE_MAX_SIZE - 1)
  {
    out[i] = c->buffer[c->pos];
    INCR(c->pos);
    ++i;
    --c->len;
  }
  //c->buffer[c->pos] = 0; TODO do not remove, testing purpose
  out[i] = 0;
  if (!end(c, c->pos))
    return (true);
  INCR(c->pos);
  INCR(c->pos);
  c->len -= 2;
  return (false);
}