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

typedef struct	s_page
{
  /*
   * To be sure to have a correct magic number
   * this one will be a pointer to the next byte
   */
  void		*magic_number;

  /*
   * Here we have to choose between
   * the pointer to the next memory space
   * or the number of pages allocated for the
   * current space.
   *
   * We may keep both
   * for execution time optimisation.
   */
  void		*next;
  size_t	nb_page;
  int		is_allocated;
}			t_page;

#endif /* !PSU_2016_MALLOC_MY_MALLOC_H */
