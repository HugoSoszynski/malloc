/*
** show_alloc_mem.c for PSU_2016_malloc in /home/soszyn_h/rendu/PSU/PSU_2016_malloc/show_alloc_mem.c
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Thu Feb 09 08:22:47 2017 Hugo SOSZYNSKI
** Last update Thu Feb 09 08:22:47 2017 Hugo SOSZYNSKI
*/

#include	<stddef.h>
#include	<unistd.h>
#include	<stdio.h>
#include	<string.h>
#include	"my_malloc.h"

void		show_alloc_mem()
{
  void		*space;
  t_header	header;
  size_t	size;
  int		page_size;

  page_size = getpagesize();
  space = g_heap_start;
  printf("break : %p\n", sbrk(0));
  while (space != NULL)
  {
    memcpy(&header, space, sizeof(t_header));
    if (header.is_allocated)
    {
      size = header.nb_page * page_size;
      printf("%p - %p : %lu bytes\n", space, header.next - 1, size);
      space = header.next;
    }
  }
}