/*
** my_free.c for PSU_2016_malloc in /home/soszyn_h/rendu/PSU/PSU_2016_malloc/my_free.c.cpp
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Tue Jan 24 13:49:33 2017 Hugo SOSZYNSKI
** Last update Thu Jan 26 14:46:51 2017 Hugo SOSZYNSKI
*/

#include	<unistd.h>
#include	<stdio.h>
#include	<string.h>
#include	"my_malloc.h"

void		free_block_concat(void **space, t_header *header)
{
  t_header	tmp;

  if (header->prev != NULL)
  {
    memcpy(&tmp, header->prev, sizeof(t_header));
    if (tmp.is_allocated == 0)
    {
      tmp.next = header->next;
      memcpy(header->prev, &tmp, sizeof(t_header));
      *space = header->prev;
      memcpy(header, *space, sizeof(t_header));
    }
  }
  if (header->next != NULL)
  {
    memcpy(&tmp, header->next, sizeof(t_header));
    if (tmp.is_allocated == 0)
    {
      header->next = tmp.next;
      memcpy(*space, header, sizeof(t_header));
    }
  }
}

void		free(void *space)
{
  t_header	header;
  t_header	tmp;
  void		*prev;

  space -= sizeof(t_header);
  memcpy(&header, space, sizeof(t_header));
  if (header.magic_number != space + 1)
  {
    write(2, "Wrong magic number\n", 19);
    return ;
  }
  header.is_allocated = 0;
  memcpy(space, &header, sizeof(t_header));
  free_block_concat(&space, &header);
  if (header.next == NULL)
  {
    prev = header.prev;
    if (prev != NULL)
    {
      memcpy(&tmp, prev, sizeof(t_header));
      tmp.next = NULL;
      memcpy(prev, &tmp, sizeof(t_header));
    }
    brk(space);
  }
}