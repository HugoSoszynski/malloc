/*
** main.c for test in /home/soszyn_h/rendu/PSU/PSU_2016_malloc/tests
**
** Made by Hugo SOSZYNSKI
** Login   <hugo.soszynski@epitech.eu>
**
** Started on  Mon Jan 23 10:41:40 2017 Hugo SOSZYNSKI
** Last update Mon Jan 23 11:21:49 2017 Hugo SOSZYNSKI
*/

#include	<unistd.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/time.h>
#include	<sys/resource.h>

int                             my_put_ulnbr_base(unsigned long int nb, const char *base)
{
  int                           count;
  unsigned long int             base_length;

  count = 0;
  base_length = strlen(base);
  if (nb >= base_length)
    count = my_put_ulnbr_base(nb / base_length, base);
  write(1, &base[nb % base_length], 1);
  count += 1;
  return (count);
}

void testing()
{

}

int		main()
{
//  char		*newmem;
//  char		*lel;
//  int		b;
//  int		i;
//
//  i = 0;
//  b = 0;
//
//  write(1, "End of exec (sbrk(0)) : ", 24);
//  my_put_ulnbr_base(sbrk(0), "0123456789ABCDEF");
//  write(1, "\n", 1);
//
//  newmem = realloc(NULL, 27);
//
//  write(1, "PTR : ", 6);
//  my_put_ulnbr_base(newmem, "0123456789ABCDEF");
//  write(1, "\n", 1);
//
//  while (i < 26)
//  {
//    newmem[i] = 'A' + i;
//    i++;
//  }
//  newmem[26] = '\0';
//  write(1, newmem, strlen(newmem));
//  write(1, "\n", 1);
//
//  newmem = realloc(newmem, 37);
//
//  for (i = 26; i < 36; i++)
//    newmem[i] = (i - 26) + '0';
//  newmem[36] = '\0';
//  write(1, newmem, strlen(newmem));
//  write(1, "\n", 1);
//
//  free(newmem);
//
//  write(1, "End of exec (sbrk(0)) : ", 24);
//  my_put_ulnbr_base(sbrk(0), "0123456789ABCDEF");
//  write(1, "\n", 1);



//  char *ptr;
//  char *ptra;
//  char *ptrb;
//  char *v3;
//  char *v5;
//  char *v6;
//  char *v7;
//  int score = 0;
//
//  write(1, "End of exec (sbrk(0)) : ", 24);
//  my_put_ulnbr_base(sbrk(0), "0123456789ABCDEF");
//  write(1, "\n", 1);
//
//  write(2, "1", 1);
//  ptr = realloc(NULL, 2);
//  if (ptr)
//  {
//    write(2, "2", 1);
//
//    ptra = realloc(ptr, 42 * getpagesize());
//    if (ptra)
//    {
//      write(2, "3", 1);
//
//      v3 = memset(ptra, 0, 42 * getpagesize());
//      write(2, "4", 1);
//
//      realloc(v3, 0);
//      write(2, "5", 1);
//
//      score = 1;
//      v5 = realloc(0, 43 * getpagesize());
//      write(2, "6", 1);
//
//      v7 = v5;
//      v6 = sbrk(0);
//      ptrb = realloc(v5, 0x1F4);
//      write(2, "7", 1);
//
//      if (ptrb)
//      {
//	write(2, "8", 1);
//
//	if (v7 == ptrb)
//	  score = 2;
//	if (sbrk(0) == v6)
//	  score++;
//	realloc(ptrb, 0);
//	write(2, "9", 1);
//
//      }
//    }
//  }
//
//  write(1, "SCORE : ", 8);
//  my_put_ulnbr_base(score, "0123456789");
//  write(1, "\n", 1);
//
//  write(1, "End of exec (sbrk(0)) : ", 24);
//  my_put_ulnbr_base(sbrk(0), "0123456789ABCDEF");
//  write(1, "\n", 1);
//
//  return (0);



  int result; // rax@2
  void *v3; // rax@5
  int v4; // eax@5
  void *v5; // ST28_8@5
  void *v6; // [sp+18h] [bp-28h]@5
  void *v7; // [sp+20h] [bp-20h]@5
  void *ptr; // [sp+28h] [bp-18h]@1
  void *ptra; // [sp+28h] [bp-18h]@3
  void *ptrb; // [sp+28h] [bp-18h]@5
  size_t size; // [sp+30h] [bp-10h]@1
  signed int v12; // [sp+3Ch] [bp-4h]@5

  size = 42 * getpagesize();
  write(1, "Test 7 : Testing realloc's : ", 29);
  ptr = realloc(0LL, 2);
  if ( ptr )
  {
    ptra = realloc(ptr, size);
    if ( ptra )
    {
      v3 = memset(ptra, 0, size);
      realloc(v3, 0LL);
      v12 = 1;
      v4 = getpagesize();
      v5 = realloc(0LL, v4 + size);
      v7 = v5;
      v6 = sbrk(0LL);
      ptrb = realloc(v5, 0x1F4);
      if ( ptrb )
      {
	if ( v7 == ptrb )
	  v12 = 2;
	if ( sbrk(0LL) == v6 )
	  ++v12;
	realloc(ptrb, 0LL);
	result = (unsigned int)v12;
      }
      else
      {
	result = 0LL;
      }
    }
    else
    {
      result = 0LL;
    }
  }
  else
  {
    result = 0LL;
  }
  my_put_ulnbr_base(result, "0123456789");
  write(1, "\n", 1);
  return result;

}
