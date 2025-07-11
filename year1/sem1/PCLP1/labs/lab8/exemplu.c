# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main ()
{
   char c = 'a', *p, s[100];
   //p primeste adresa lui c, deci p=&c si *p=c
   p = &c;
   //afiseaza *p=c='a', *p=c+1='b', *p=c+2='c'
   printf ("%c %c %c", *p, *p+1, *p+2);
   s[0] = 'A'; s[1] = 'B'; s[2] = 'C'; s[3] = '\0';
   p = s;
   //pointer catre s, pointer cu val s[1], pointer catre s+1
   printf ("\n%s %s %c %s", s, p, *(p+1), p+1);
   strcpy (s, "\nacesta este un exemplu de lucru cu pointeri");
   printf ("%s", s);
   //trece peste primele 17 caractere din
   p += 17;
   //inlocuieste e cu E si ' ' cu \n
   for (; *p != '\0'; ++p) {
      if (*p == 'e')
         *p = 'E';
      if (*p == ' ')
         *p = '\n';
   }
   printf ("%s\n", s);
   return 0;
}