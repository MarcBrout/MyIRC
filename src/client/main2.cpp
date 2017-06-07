#include "client.h"
#include "circular_tools.h"

int main()
{
  char buff[10];
  t_circular p;
  t_client_data data;
  strfromcircular(&p, buff);
  return get_select(&data);
}
