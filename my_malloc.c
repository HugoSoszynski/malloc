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

void		*malloc(size_t size)
{
  void		*space;
  size_t	page_size;
  t_page	header;

  page_size = (size_t)(getpagesize());
  header.magic_number = MAGIC_NUMBER;
  header.nb_page = (size + sizeof(t_page)) / page_size;
  if ((size + sizeof(t_page)) % page_size)
    header.nb_page += 1;
  space = sbrk(0);
  if (space == (void*)(-1))
    return (NULL);
  sbrk(header.nb_page * page_size);
  memcpy(space, &header, sizeof(t_page));
  return (space + sizeof(t_page));
}

void		*realloc(void *space, size_t size)
{
  void		*next;
  size_t	npages;
  size_t	page_size;
  t_page	header;

  page_size = (size_t)(getpagesize());
  space -= sizeof(t_page);
  memcpy(&header, space, sizeof(t_page));
  if ((unsigned)(header.magic_number) != MAGIC_NUMBER)
    return (NULL);
  next = space + (page_size * header.nb_page);
  npages = (size + sizeof(t_page)) / page_size;
  if (npages < header.nb_page)
  {
    sbrk(npages * page_size);
    memcpy(space + npages * page_size, next,
	   (sbrk(0) - (space + npages * page_size)));
  }
  else
  {
    memcpy((space + npages * page_size), next, (sbrk(0) - next));
    sbrk(-(header.nb_page - page_size) * page_size);
  }
  memcpy(space, &header, sizeof(t_page));
  return (space + sizeof(t_page));
}

void		free(void *space)
{
  void		*end;
  size_t	living_size;
  size_t	page_size;
  t_page	header;

  page_size = (size_t)(getpagesize());
  space -= sizeof(t_page);
  memcpy(&header, space, sizeof(t_page));
  if ((unsigned)(header.magic_number) != MAGIC_NUMBER)
    return ;
  end = space + (page_size * header.nb_page);
  living_size = sbrk(0) - end;
  if (living_size)
    memcpy(space, end, living_size);
  sbrk(-(page_size * header.nb_page));
}
