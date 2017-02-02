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
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
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
  int fd;
  struct stat stats1;

  fd = open("my_malloc.c", O_RDONLY);

  if (fd < 0)
    return (1);

  fstat(fd, &stats1);
  close(fd);
  return 0;
}
