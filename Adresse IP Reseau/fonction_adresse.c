#include "header_fonction.h"

void principale()
{

    char *tab = malloc(255*sizeof(char));
    char *resultat = malloc(255*sizeof(char));
    char *ip = malloc(30*sizeof(char));
    int *nbr1 = malloc(5*sizeof(int));
    int *nbr2 = malloc(5*sizeof(int));
    int *nbr3 = malloc(5*sizeof(int));
    int *nbr4 = malloc(5*sizeof(int));
    int bitereseau = 0;
    int decoupe = 0;
    int i = 0;
    int j = 0;
    
    for(i = 0; i < 4; i++)
    {
		nbr1[i] = 0;
		nbr2[i] = 0;
		nbr3[i] = 0;
		nbr4[i] = 0;
	}
    
    printf("Entrez un adresse IP : ");
    scanf("%s", tab);
    
	test(tab, ip, resultat, nbr1, &bitereseau);
	
		printf("IP : %d.%d.%d.%d/%d\n", nbr1[0], nbr1[1], nbr1[2], nbr1[3], bitereseau);
		printf("ClasSe : %s\n", resultat);
		printf("Nombre de machine : %d\n", nombreMachine(bitereseau));
		printf("Netmask : %s\n", adresseMasque(bitereseau, nbr2));
		printf("Adresse Reseau : %s\n", adresseReseau(nbr1, nbr2, nbr3));
		printf("Adresse Broadcast : %s\n\n", adresseBroadcast(bitereseau, nbr1, nbr3, nbr4));
	
    printf("Entrez le nombre de decoupe : ");
    scanf("%d", &decoupe);
	
		for(i = 0; i < pow(2, decoupe); i++)
		{
            printf("Sous reseau : %d \n", i);
			int nbrmachine = nombreMachine(bitereseau) / pow(2, decoupe);
			printf("Adresse Reseau : %d.%d.%d.%d\n", nbr3[0], nbr3[1], nbr3[2], nbr3[3]);
			nbrmachine += nbr3[3];
			nbr3[3] = nbrmachine % 256;
			nbr3[2] += nbrmachine / 256;
			nbr3[1] += nbr3[2] / 256;
			nbr3[0] += nbr3[1] / 256; 
			nbr3[2] %= 256;
			nbr3[1] %= 256;
			nbr3[0] %= 256;
			
			printf("Adresse Broadcast : %d.%d.%d.%d\n\n", nbr3[0], nbr3[1], nbr3[2], nbr3[3]);
			nbr3[3]++;
			for(j = 3; j > 0; j--)
			{
				if(nbr3[j] > 255)
				{
					nbr3[j] = nbr3[j] % 256;
					nbr3[j-1]++;
				}
			}
			
	}

    free(nbr1);
    free(nbr2);
    free(nbr3);
    free(nbr4);
    free(ip);
    free(tab);
    free(resultat);

}

void test(char *tab, char *ip, char* resultat, int *nbr1, int *bitereseau)
{
	
	if (strlen(tab) > 0) 
    {
        if (sscanf(tab, "%20[0-9./]s", ip) == 1) 
        {
            if (sscanf(ip, "%d.%d.%d.%d/%d", &nbr1[0], &nbr1[1], &nbr1[2], &nbr1[3], bitereseau) == 5) 
            {
                if (nbr1[0] >= 0 && nbr1[0] <= 255 && nbr1[1] >= 0 && nbr1[1] <= 255 && nbr1[2] >= 0 && nbr1[2] <= 255 && nbr1[3] >= 0 && nbr1[3] <= 255 && *bitereseau <= 32 && *bitereseau >= 0) 
                {
                    if (nbr1[0] >= 0 && nbr1[0] <= 127) 
                    {
                        strcpy(resultat, "Ceci est un adresse IP de classe A");
                    } 
                    else if (nbr1[0] >= 128 && nbr1[0] <= 191) 
                    {
                        strcpy(resultat, "Ceci est un adresse IP de classe B");
                    } 
                    else if (nbr1[0] >= 192 && nbr1[0] <= 223) 
                    {
                        strcpy(resultat, "Ceci est un adresse IP de classe C");
                    }
                    else if (nbr1[0] >= 224 && nbr1[0] <= 239) 
                    {
                        strcpy(resultat, "Ceci est un adresse IP de classe D");
                    }
                    else if (nbr1[0] >= 240 && nbr1[0] <= 255) 
                    {
                        strcpy(resultat, "Ceci est un adresse IP de classe E");
                    } 
                    else 
                    {
                        strcpy(resultat, "Ceci n'est pas un adresse IP");
                    }
                } 
                else 
                {
                strcpy(resultat, "Ceci n'est pas une forme valide d'adresse IP");
                }
            } 
            else 
            {
                strcpy(resultat, "Ceci n'est pas une forme valide d'adresse IP");
            }
        } 
        else 
        {
            strcpy(resultat, "Ceci n'est pas un adresse IP");
        }
    }
	
}

char* adresseMasque(int bitereseau, int *nbr2)
{

    char *masquereseau = malloc(30*sizeof(char));
    int i = 0;
    int j = 0;
	
	for(i = 0; bitereseau > 0; i++)
    {
		bitereseau -= 8;
		if(bitereseau > 0)
		{
			nbr2[i] = pow(2, 8) - 1;
		}
		else
		{
			bitereseau += 8;
			for(j = 7; j >= 8-bitereseau; j--)
			{
				nbr2[i] += pow(2, j);
			}
			bitereseau -= 8;
		}
	}
	sprintf(masquereseau, "%d.%d.%d.%d", nbr2[0], nbr2[1], nbr2[2], nbr2[3]);
	
    return masquereseau;
    
    free(masquereseau);
	
}

char *adresseReseau(int *nbr1, int* nbr2, int *nbr3)
{

    char *adressereseau = malloc(30*sizeof(char));	
    int i = 0;
    
    for(i = 0; i < 4; i++)
    {
		nbr3[i] = nbr2[i] & nbr1[i];
	}
	
	sprintf(adressereseau, "%d.%d.%d.%d", nbr3[0], nbr3[1], nbr3[2], nbr3[3]);
    
    return adressereseau;
    
    free(adressereseau);
	
}

char *adresseBroadcast(int bitereseau, int *nbr1, int *nbr3, int* nbr4)
{

    char *adressebroadcast = malloc(30*sizeof(char));	
    int i = 0;
    int j = 0;
    int bitehote = 32 - bitereseau;
    
    for(i = 0; i < 4; i++)
    {
		if(bitehote != 0)
		{
			bitehote -= 8;
			if(bitehote >= 0)
			{
				nbr4[3-i] = 255;
			}
			else
			{
				bitehote += 8;
				nbr4[3-i] += nbr3[3-i];
				for(j = 0; j < bitehote; j++)
				{
					nbr4[3-i] += pow(2, j);
				}
				bitehote = 0;
			}
		}
		else
		{
			nbr4[3-i] = nbr1[3-i];
		}
	}
    
	sprintf(adressebroadcast, "%d.%d.%d.%d", nbr4[0], nbr4[1], nbr4[2], nbr4[3]);
    
    return adressebroadcast;
    
    free(adressebroadcast);
	
}

int nombreMachine(int bitereseau)
{

	return  pow(2, 32-bitereseau) - 2;
	
}
