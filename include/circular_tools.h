#ifndef CIRCULAR_TOOLS_H_
# define CIRCULAR_TOOLS_H_

# define MESSAGE_MAX_SIZE 512
# define BUFFER_MAX_SIZE 4096
# define INCR(x) ((x) = ((x) + 1) % BUFFER_MAX_SIZE)

typedef struct s_circular t_circular;

struct s_circular
{
  int pos;
  int len;
  char buffer[BUFFER_MAX_SIZE];
};

void strncircular(t_circular *c, char *str, int n);
bool find_command(t_circular *c);
bool strfromcircular(t_circular *c, char out[MESSAGE_MAX_SIZE]);

#endif /* !MYIRC_CIRCULAR_TOOLS_H_ */
