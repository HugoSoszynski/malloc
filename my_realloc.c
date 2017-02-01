/*
** my_realloc.c for PSU_2016_malloc in /home/soszyn_h/rendu/PSU/PSU_2016_malloc/my_realloc.c
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Mon Jan 30 09:35:04 2017 Hugo SOSZYNSKI
** Last update Mon Jan 30 09:35:04 2017 Hugo SOSZYNSKI
*/

#include	<stddef.h>
#include	<unistd.h>
#include	<string.h>
#include	"my_malloc.h"

void		*realloc(void *ptr, size_t size)
{
  t_header	header;
  void		*space;
  int		page_size;

  if (ptr == NULL)
    return (malloc(size));
  if (size == 0)
  {
    free(ptr);
    return (NULL);
  }
  page_size = getpagesize();
  memcpy(&header, ptr - sizeof(t_header), sizeof(t_header));
  if (header.magic_number != ptr - sizeof(t_header) + 1)
    return (ptr);
  if (size + sizeof(t_header) < (header.nb_page * page_size))
    return (ptr);
  space = malloc(size);
  if (space == NULL)
    return (ptr);
  memcpy(space, ptr, header.nb_page * page_size);
  free(ptr);
  return (space);
}