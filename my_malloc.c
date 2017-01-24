/*
** my_malloc.c for PSU_2016_malloc in /home/loens_g/rendu/TEK2/SystemUnix/PSU_2016_malloc/my_malloc.c
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Mon Jan 23 09:34:22 2017 Gregoire LOENS
** Last update Mon Jan 23 14:45:53 2017 Hugo SOSZYNSKI
*/

#include	<unistd.h>
#include	<stdio.h>
#include	<string.h>
#include	"my_malloc.h"

void		*g_heap_start = NULL;

/*
 * Here are the cases we can encounter :
 * 1. We are at the first alloc or we have nothing allocated
 * 2. Already alloc, no free space, need to allocate at the end
 * 3. Already alloc, free spaces, try to allocate in the free spaces.
 * 	If the size can't fit free spaces, allocate at the end.
 */

static void	*heap_start_alloc(size_t size, t_header *header)
{
  void		*space;
  int		page_size;

  page_size = getpagesize();
  header->nb_page = (size + sizeof(t_header)) / page_size;
  if ((size + sizeof(t_header)) % page_size)
    header->nb_page += 1;
  space = sbrk(header->nb_page * page_size);
  if (space == (void*)(-1))
    return (NULL);
  header->is_allocated = 1;
  header->next = sbrk(0);
  header->prev = g_heap_start;
  header->magic_number = space + 1;
  memcpy(space, header, sizeof(t_header));
  return (space);
}

void		*malloc(size_t size)
{
  void		*space = NULL;
  t_header	header;

  if (g_heap_start == NULL || g_heap_start == sbrk(0))
  {
    g_heap_start = sbrk(0);
    space = heap_start_alloc(size, &header);
  }
  return (space + sizeof(t_header));
}

