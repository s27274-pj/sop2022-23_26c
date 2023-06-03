#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/*funkcja do symetrycznego wyświetlania kolejnych wierszy choinki*/
void isInRadius(int parameter, int point, int radius){
    printf((abs(parameter-point) <= radius) ? "x" : " ");
}

int main(int argc, char** argv){
    int wysokoscChoinki = atoi(argv[1]);
    int rozmiarPienka, dlugoscWiersza;
    if (wysokoscChoinki <= 0){
        printf("Tree's height should be a positive number.");
        return 0;
    }
    /*Rozszerzam wysokość choinki, aby uzyskać choinkę o wymiarach 1 na 2*/
    dlugoscWiersza = wysokoscChoinki*2;
    for (int wiersz = 0; wiersz < wysokoscChoinki; ++wiersz){
        /*przechodzę przez kolejne pola wiersza i sprawdzam, czy trzeba w nich wyświetlić znak*/
        for (int poleNaZnak = 1; poleNaZnak <= dlugoscWiersza; ++poleNaZnak) {
            isInRadius(poleNaZnak, wysokoscChoinki, wiersz);
        }
        printf("\n");
    }
    /*ze względów estetycznych dodałem do drzewa pieniek*/
    rozmiarPienka = wysokoscChoinki/3;
    if (rozmiarPienka == 0) {
        rozmiarPienka = 1;
    }
    for (int wiersz = 0; wiersz < rozmiarPienka; wiersz++) {
        for (int poleNaZnak = 1; poleNaZnak <= dlugoscWiersza; ++poleNaZnak) {
            isInRadius(poleNaZnak, wysokoscChoinki, wysokoscChoinki > 3);
        }
        printf("\n");
    }
    return 0;
}
