/*
** main.c for test in /home/soszyn_h/rendu/PSU/PSU_2016_malloc/tests
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Mon Jan 23 10:41:40 2017 Hugo SOSZYNSKI
** Last update Mon Jan 23 11:21:49 2017 Hugo SOSZYNSKI
*/

#include	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/time.h>
#include	<sys/resource.h>

int                             my_put_ulnbr_base(unsigned long int nb, const char *base)
{
  int                           count;
  unsigned long int             base_length;

  count = 0;
  base_length = strlen(base);
  if (nb >= base_length)
    count = my_put_ulnbr_base(nb / base_length, base);
  write(1, &base[nb % base_length], 1);
  count += 1;
  return (count);
}


int		main()
{
  char		*newmem;
  char		*lel;
  int		b;
  int		i;

  i = 0;
  b = 0;

  write(1, "End of exec (sbrk(0)) : ", 24);
  my_put_ulnbr_base(sbrk(0), "0123456789ABCDEF");
  write(1, "\n", 1);

  newmem = malloc(27);

  write(1, "PTR : ", 6);
  my_put_ulnbr_base(newmem, "0123456789ABCDEF");
  write(1, "\n", 1);

  while (i < 26)
  {
    newmem[i] = 'A' + i;
    i++;
  }
  newmem[26] = '\0';
  write(1, newmem, strlen(newmem));
  write(1, "\n", 1);

  lel = malloc (11);
  write(1, "LEL : ", 6);
  my_put_ulnbr_base(lel, "0123456789ABCDEF");
  write(1, "\n", 1);
  for (int a = 0; a < 10; a++)
    lel[a] = '0' + a;
  lel[10] = '\0';
  write(1, lel, strlen(lel));
  write(1, "\n", 1);

  write(1, "End of exec (sbrk(0)) : ", 24);
  my_put_ulnbr_base(sbrk(0), "0123456789ABCDEF");
  write(1, "\n", 1);

  free(lel);

  write(1, "End of exec (sbrk(0)) : ", 24);
  my_put_ulnbr_base(sbrk(0), "0123456789ABCDEF");
  write(1, "\n", 1);

  free(newmem);

  write(1, "End of exec (sbrk(0)) : ", 24);
  my_put_ulnbr_base(sbrk(0), "0123456789ABCDEF");
  write(1, "\n", 1);


  return (0);
}
