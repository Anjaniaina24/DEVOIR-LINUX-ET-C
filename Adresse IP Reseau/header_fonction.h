#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void test(char *tab, char *ip, char* resultat, int *nbr1, int *bitereseau);
char* adresseMasque(int bitereseau, int *nbr2);
char* adresseReseau(int *nbr1, int* nbr2, int *nbr3);
char *adresseBroadcast(int bitereseau, int *nbr1, int* nbr3, int* nbr4);
int nombreMachine(int bitereseau);
void principale();