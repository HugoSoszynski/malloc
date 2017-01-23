/*
** my_malloc.h for PSU_2016_malloc in /home/loens_g/rendu/TEK2/SystemUnix/PSU_2016_malloc/my_malloc.h
**
** Made by Gregoire LOENS
** Login   <gregoire.loens@epitech.eu>
**
** Started on  Mon Jan 23 09:35:04 2017 Gregoire LOENS
** Last update Mon Jan 23 14:46:08 2017 Hugo SOSZYNSKI
*/

#ifndef MY_MALLOC_H
# define MY_MALLOC_H

# ifndef MAGIC_NUMBER
#  define MAGIC_NUMBER (0xACDCB00B)
# endif /* !MAGICNUMBER */

typedef struct		s_page
{
  int			magic_number;
  size_t		nb_page;
}			t_page;

#endif /* !PSU_2016_MALLOC_MY_MALLOC_H */
