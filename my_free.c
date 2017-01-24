/*
** my_free.c.cpp for PSU_2016_malloc in /home/soszyn_h/rendu/PSU/PSU_2016_malloc/my_free.c.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Jan 24 13:49:33 2017 Hugo SOSZYNSKI
** Last update Tue Jan 24 13:49:33 2017 Hugo SOSZYNSKI
*/

#include	<unistd.h>
#include	<stdio.h>
#include	<string.h>
#include	"my_malloc.h"

void		free(void *space)
{
  t_header	header;

  space -= sizeof(t_header);
  memcpy(&header, space, sizeof(t_header));
  if (header.magic_number != space + 1)
  {
    write(2, "Wrong magic number\n", 19);
    return ;
  }
  header.is_allocated = 0;
  if (header.next == NULL)
    brk(space);
}