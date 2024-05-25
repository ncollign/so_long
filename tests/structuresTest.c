#include <stdio.h>
#include <string.h>
#include "../main-core/so_long.h"

typedef struct
{
    int vie;
    char    prenom[100];
} Personnage;

void    printPlayer(Personnage player)
{
    printf("------------\n");
    printf("Prenom : %s\n", player.prenom);
    printf("Vie : %d\n", player.vie);
    printf("------------\n");

}

int main(void)
{
    Personnage player1;
    player1.vie = 100;
    strcpy(player1.prenom, "Prenom");

    printPlayer(player1);
    return (0);
}