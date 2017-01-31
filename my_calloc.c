/*
** calloc.c for malloc in /home/loens_g/rendu/TEK2/malloc/calloc.c
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Tue Jan 31 09:45:03 2017 Gregoire LOENS
** Last update Tue Jan 31 09:45:03 2017 Gregoire LOENS
*/

#include 	<string.h>
#include	"my_malloc.h"

void		*calloc(size_t nmemb, size_t size)
{
  void		*space;

  if (nmemb == 0)
    return (NULL);
  space = malloc(size);
  if (space == NULL)
    return (NULL);
  space  = memset(space, 0, nmemb);
  return (space);
}