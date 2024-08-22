#include "header_adresse.h"

void principale()
{

    char *tab = malloc(255*sizeof(char));
    char *resultat = malloc(255*sizeof(char));
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;

    strcpy(tab, getenv("QUERY_STRING"));
     if (tab == NULL) {
        tab = "";
    }

    if (strlen(tab) > 0) {
        char ip[16];
        if (sscanf(tab, "adresse=%15[0-9.]s", ip) == 1) 
        {
            if (sscanf(ip, "%d.%d.%d.%d", &a, &b, &c, &d) == 4) 
            {
                if (a >= 0 && a <= 255 && b >= 0 && b <= 255 && c >= 0 && c <= 255 && d >= 0 && d <= 255) 
                {
                    if (a >= 0 && a <= 127) 
                    {
                        strcpy(resultat, "Ceci est un adresse IP de classe A");
                    } 
                    else if (a >= 128 && a <= 191) 
                    {
                        strcpy(resultat, "Ceci est un adresse IP de classe B");
                    } 
                    else if (a >= 192 && a <= 223) 
                    {
                        strcpy(resultat, "Ceci est un adresse IP de classe C");
                    }
                    else if (a >= 224 && a <= 239) 
                    {
                        strcpy(resultat, "Ceci est un adresse IP de classe D");
                    }
                    else if (a >= 240 && a <= 255) 
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

    sprintf(tab, "%d.%d.%d.%d", a, b, c, d);

    printHtml(resultat, tab);

    free(tab);
    free(resultat);

}

void printHtml(char *resultat, char *tab)
{

    printf("Content-Type: text/html\n\n");
    printf(

        "        <!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <title>Adresse</title>\n"
        "    <style>\n"
        "        form\n"
        "        {\n"
        "            background-color: #BCF076;\n"
        "            border-radius: 40px;\n"
        "            width: 50vw;\n"
        "            height: 90vh;\n"
        "            margin: auto;\n"
        "            margin-top: 5vh;\n"
        "            padding-top: 20px;\n"
        "        }\n"
        "        input\n"
        "        {\n"
        "            background-color: #C4BDA0;\n"
        "            border-radius: 20px;\n"
        "            width: 80%%;\n"
        "            height: 20%%;\n"
        "            margin: 10%%;\n"
        "            font-size: 400%%;\n"
        "            text-align: center;\n"
        "            margin-bottom: 20px;\n"
        "            margin-top: 0px;\n"
        "        }\n"
        "        input.valid\n"
        "        {\n"
        "            border-radius: 20px;\n"
        "            background-color: #38C8D1;\n"
        "            width: 50%%;\n"
        "            height: 10%%;\n"
        "            margin-left: 25%%;\n"
        "            font-size: 200%%;\n"
        "            font-weight: bold;\n"
        "            padding: 10px;\n"
        "        }\n"
        "        p\n"
        "        {\n"
        "           text-align: center;\n"
        "           font-size: 50px;\n"
        "           margin: 20px;\n"
        "        }\n"
        "    </style>\n"
        "</head>\n"
        "<body>\n"
        "    \n"
        "    <form action=\"adresse.cgi\" method=\"get\">\n"
        "       <p>\n"
        "           Entrez un adresse IP\n"
        "       </p>\n"
        "        <input type=\"text\" name=\"adresse\" placeholder=\"%s\">\n"
        "        <input class=\"valid\" type=\"submit\" value=\"Son classe ?\">\n"
        "       <p>\n"
        "           %s\n"
        "       </p>\n"
        "    </form>\n"
        "\n"
        "</body>\n"
        "</html>\n",tab , resultat

    );

}
