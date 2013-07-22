#include <string.h>
#include <stdlib.h>
#include "stack-c.h"
#include "overstack.h"
//#define __USE_DEPRECATED_STACK_FUNCTIONS__ 1
typedef long long *pint64;
// un nom de variable est code sur 24 octets soit 6 int (d'ou nsiz=6), j'utilise le type long long car il est code
// sur 8 octets (soit 2 int), ainsi la comparaison se fait sur trois long long plutot que sur 6 int ou 24 char
// Par contre, je ne sais pas ce que cela donne sur un processeur 64 bits, a voir donc.
#define caseid(x,n) ((pint64)(x))[n]
#define cmpids(x,y) ((caseid(x,0)!=caseid(y,0))?(caseid(x,0)-caseid(y,0)):(caseid(x,1)!=caseid(y,1))?(caseid(x,1)-caseid(y,1)):(caseid(x,2)-caseid(y,2)))
#define cpyids(x,y,m,n) (caseid (x,3*(m))=caseid (y,3*(n)),caseid (x,3*(m)+1)=caseid (y,3*(n)+1),caseid (x,3*(m)+2)=caseid (y,3*(n)+2))

#define OVERTABLESIZE 512

static int zero = 0, un = 1, deux = 2;
static struct overTable
{
  int nom[OVERTABLESIZE * nsiz];
  int assoc[OVERTABLESIZE * nsiz];
  int top;
  int last;
} OT = {{0}, {0}, -1, 0};


extern int C2F(cvnamel)(int *id,char *str,int *jobptr,int *str_len);

/* insOT insert un nom en respectant l'ordre alphabetique
   dans la table avec le nom (assoc) de la fonction associee */

void insOT (int *nom, int *assoc)
{
  int a = 0, b = OT.top;
  int m = 0, c, i;

  while (a <= b)
    {
      m = (int)((a + b) / 2);
      c = (int)cmpids (OT.nom + nsiz * m, nom);
      if (c == 0)
        return;
      else if (c > 0)
        b = m - 1;
      else
        a = m + 1;
    }

  if (a <= OT.top)
    for (i = OT.top + 1 ;i > a; i--)
      {
	cpyids (OT.nom, OT.nom, i, i - 1);
	cpyids (OT.assoc, OT.assoc, i, i - 1);
      }
      
  cpyids (OT.nom, nom, a, 0);
  cpyids (OT.assoc, assoc, a, 0);

  ++OT.top;

  return;
}

/* getassoc permet, etant donne un nom, 
   de recuperer le nom de la fonction associee.
   La recherche utilise un algo de recherche 
   dichotomique, et compare le nom avec le dernier
   nom trouve (en cas de boucle sur la macro, cela
   permet de recuperer l'association plus rapidement) */

int *getassoc (int *id)
{
  int a = 0, b = OT.top;
  int m = 0, c;

  if (cmpids (OT.nom + OT.last, id) == 0)
    return OT.assoc + OT.last;

  while (a <= b)
    {
      m = (a + b) / 2;
      c = (int)cmpids (OT.nom + nsiz * m, id);
      if (c == 0)
	{
	  OT.last = nsiz * m;
	  return OT.assoc + OT.last;
	}
      else if (c > 0)
        b = m - 1;
      else
        a = m + 1;
    }
  return NULL;
}  

/* getSciTab met en position pos, un tableau
   de strings contenant nom et association */

void getSciTab (int pos)
{
  int t = OT.top + 1;
  int i, len;
  char *ch;
  char **tab = malloc (2 * t * sizeof(char*));
  
  for (i = 0; i < t; i++)
    {
      ch = malloc (nsiz * sizeof(int) + 1);
      C2F(cvnamel) (OT.nom + nsiz * i, ch, &un, &len);
      ch[len] = '\0';
      tab[i] = ch;
      ch = malloc (nsiz * sizeof(int) + 1);
      C2F(cvnamel) (OT.assoc + nsiz * i, ch, &un,&len);
      ch[len] = '\0';
      tab[t + i] = ch;
    }

  C2F(createvarfromptr) (&pos, "S", &t, &deux, tab, nlgh);
  
  for (i = 0; i < t; i++)
    {
      free (tab[i]);
      free (tab[t + i]);
    }
  
  free (tab);
  
  return; 
}
 
/* setSciTab permet de modifier la table en recuperant 
   une matrice n x 2 de strings en position pos */

int setSciTab (char **tab, int m)
{
  int i;
  int id[nsiz], id1[nsiz], idnul[nsiz] = {673720360, 673720360, 673720360, 673720360, 673720360, 673720360};
  
  for (i = 0; i <= OT.top; i++)
    cpyids (OT.nom, idnul, i, 0);
      
  OT.top = -1;
  OT.last = 0;
  for (i = 0; i < m; i++)
    {
      C2F(cvname) (id, tab[i], &zero, strlen (tab[i]));
      C2F(cvname) (id1, tab[m + i], &zero, strlen (tab[m + i]));
      insOT (id, id1);
    }
  return 0;
}
  
