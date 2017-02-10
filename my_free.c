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
#include	<pthread.h>
#include	"my_malloc.h"

/*
** This function concat freed blocks
*/
void		free_block_concat(void **space, t_header *header)
{
  t_header	tmp;

  if (header->prev != NULL)
  {
    memcpy(&tmp, header->prev, sizeof(t_header));
    if (tmp.is_allocated == 0)
    {
      tmp.next = header->next;
      tmp.nb_page += header->nb_page;
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
      header->nb_page += tmp.nb_page;
      memcpy(*space, header, sizeof(t_header));
    }
  }
}

/*
** This function reduces the unused heap
*/
void		reduce_heap(void *space, t_header *header)
{
  t_header	tmp;

  if (header->next == NULL)
  {
    if (header->prev != NULL)
    {
      memcpy(&tmp, header->prev, sizeof(t_header));
      tmp.next = NULL;
      memcpy(header->prev, &tmp, sizeof(t_header));
    }
    brk(space);
  }
}

void		free(void *space)
{
  t_header	header;

  pthread_mutex_lock(&g_mutex);
  if (space == NULL)
  {
    pthread_mutex_unlock(&g_mutex);
    return ;
  }
  space -= sizeof(t_header);
  memcpy(&header, space, sizeof(t_header));
  if (header.magic_number != space + 1)
  {
    pthread_mutex_unlock(&g_mutex);
    return ;
  }
  header.is_allocated = 0;
  memcpy(space, &header, sizeof(t_header));
  free_block_concat(&space, &header);
  reduce_heap(space, &header);
  pthread_mutex_unlock(&g_mutex);
}