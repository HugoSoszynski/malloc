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
** Here are the cases we can encounter :
** 1. We are at the first alloc or we have nothing allocated
** 2. Already alloc, no free space, need to allocate at the end
** 3. Already alloc, free spaces, try to allocate in the free spaces.
** 	If the size can't fit free spaces, allocate at the end.
*/

/*
** This function is in charge of the allocation at the
** beginning of the heap. This append for the first allocation
** or if all the allocated memory was freed.
*/
static void	*heap_start_alloc(size_t size)
{
  void		*space;
  int		page_size;
  t_header	header;

  page_size = getpagesize();
  header.nb_page = (size + sizeof(t_header)) / page_size;
  if ((size + sizeof(t_header)) % page_size)
    header.nb_page += 1;
  space = sbrk(header.nb_page * page_size);
  if (space == (void*)(-1))
    return (NULL);
  header.is_allocated = 1;
  header.next = NULL;
  header.prev = NULL;
  header.magic_number = space + 1;
  memcpy(space, &header, sizeof(t_header));
  return (space);
}

/*
** This function search for freed space between allocated memory
** and return the space find if the space can contain the wanted size.
*/
static void	*search_free_space(size_t size)
{
  void		*space;
  t_header	header;
  size_t	nb_page;
  int		page_size;

  page_size = getpagesize();
  nb_page = (size + sizeof(t_header)) / page_size;
  if ((size + sizeof(t_header)) % page_size)
    nb_page += 1;
  space = g_heap_start;
  while (space != NULL)
  {
    memcpy(&header, space, sizeof(t_header));
    if (header.is_allocated == 0 && header.nb_page >= nb_page)
    {
      header.is_allocated = 1;
      memcpy(space, &header, sizeof(t_header));
      return (space);
    }
    space = header.next;
  }
  return (NULL);
}

/*
** This function allocate more memory at the end of the
** already allocated memory.
*/
void		*alloc_heap_end(size_t size)
{
  void		*space;
  t_header	header;
  t_header	tmp;
  int		page_size;

  page_size = getpagesize();
  header.nb_page = (size + sizeof(t_header)) / page_size;
  if ((size + sizeof(t_header)) % page_size)
    header.nb_page += 1;
  space = g_heap_start;
  memcpy(&tmp, space, sizeof(t_header));
  while (tmp.next != NULL)
    memcpy(&tmp, tmp.next, sizeof(t_header));
  tmp.next = sbrk(header.nb_page * page_size);
  if (tmp.next == (void*)(-1))
    return (NULL);
  memcpy(space, &tmp, sizeof(t_header));
  header.is_allocated = 1;
  header.next = NULL;
  header.prev = space;
  header.magic_number = tmp.next + 1;
  memcpy(tmp.next, &header, sizeof(t_header));
  return (tmp.next);
}

void		*malloc(size_t size)
{
  void		*space;

  if (g_heap_start == NULL || g_heap_start == sbrk(0))
  {
    g_heap_start = sbrk(0);
    space = heap_start_alloc(size);
  }
  else
  {
    space = search_free_space(size);
    if (space == NULL)
      space = alloc_heap_end(size);
  }
  return (space + sizeof(t_header));
}

