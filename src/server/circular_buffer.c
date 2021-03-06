/*
** circular_buffer.c for myirc in /home/brout_m/rendu/system/PSU_2016_myirc
**
** Made by brout_m
** Login   <marc.brout@epitech.eu>
**
** Started on  Wed May 31 11:22:18 2017 brout_m
** Last update Wed Jun  7 10:30:12 2017 brout_m
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "types.h"

#ifdef __plusplus
extern "C" {
#endif

bool			is_full(t_circular *c)
{
  return (c->len == BUFFER_MAX_SIZE - 1);
}

void			strncircular(t_circular *c, const char *str, int n)
{
  int			i;
  int			cpos;

  i = 0;
  cpos = c->pos + c->len;
  while (i < n && c->len < BUFFER_MAX_SIZE - 1)
    {
      c->buffer[cpos] = str[i];
      INCR(cpos);
      ++i;
      ++c->len;
    }
  c->buffer[INCR(cpos)] = 0;
}

static bool		end(t_circular *c, int pos)
{
  if (c->remains)
    {
      c->remains = false;
      return (false);
    }
  return (c->buffer[pos] == '\r' && c->buffer[INCR(pos)] == '\n');
}

bool			find_command(t_circular *c)
{
  bool			state;
  int			pos;
  int			i;

  i = 0;
  pos = c->pos;
  state = c->remains;
  while (i < c->len)
    {
      if (end(c, pos))
	{
	  c->remains = state;
	  return (true);
	}
      ++i;
      INCR(pos);
    }
  c->remains = state;
  return (false);
}

bool			strfromcircular(t_circular *c,
					char out[MESSAGE_MAX_SIZE])
{
  int			i;

  i = 0;
  memset(out, 0, MESSAGE_MAX_SIZE);
  while (!end(c, c->pos) && i < MESSAGE_MAX_SIZE - 1)
    {
      out[i] = c->buffer[c->pos];
      INCR(c->pos);
      ++i;
      --c->len;
    }
  out[i] = 0;
  if (!end(c, c->pos))
    return (true);
  INCR(c->pos);
  INCR(c->pos);
  c->len -= 2;
  return (false);
}

#ifdef __plusplus
}
#endif
