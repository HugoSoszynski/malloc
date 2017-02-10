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
#include	<limits.h>
#include	"my_malloc.h"

void		*g_heap_start = NULL;

/*
** This function is in charge of the allocation at the
** beginning of the heap. This append for the first allocation
** or if all the allocated memory was freed.
*/
static void	*heap_start_alloc(size_t nb_page, int page_size)
{
  void		*space;
  t_header	header;

  header.nb_page = nb_page;
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
static void	*search_free_space(size_t nb_page)
{
  void		*space;
  t_header	header;

  space = g_heap_start;
  while (space != NULL)
  {
    memcpy(&header, space, sizeof(t_header));
    if (header.is_allocated == 0 && header.nb_page > nb_page)
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
void		*alloc_heap_end(size_t nb_page, int page_size)
{
  void		*space;
  t_header	header;
  t_header	tmp;

  header.nb_page = nb_page;
  space = g_heap_start;
  memcpy(&tmp, space, sizeof(t_header));
  while (tmp.next != NULL)
  {
    space = tmp.next;
    memcpy(&tmp, space, sizeof(t_header));
  }
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

/*
** Main malloc function
*/
void		*malloc(size_t size)
{
  void		*space;
  size_t	nb_page;
  int		page_size;

  if (ULONG_MAX - sizeof(t_header) < size)
    return (NULL);
  page_size = getpagesize();
  nb_page = (size + sizeof(t_header)) / page_size;
  if ((size + sizeof(t_header)) % page_size)
    nb_page += 1;
  if (LONG_MAX / (unsigned)(page_size) < nb_page)
    return (NULL);
  if (g_heap_start == NULL || g_heap_start == sbrk(0))
  {
    g_heap_start = sbrk(0);
    space = heap_start_alloc(nb_page, page_size);
  }
  else
  {
    space = search_free_space(nb_page);
    if (space == NULL)
      space = alloc_heap_end(nb_page, page_size);
  }
  return (space + sizeof(t_header));
}