#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include "game.h"

//Determines the size of the scoreboard file
int sizeOfFile(FILE *fptr){
   int counter = 0;
   char line[100] = "";
   fptr = fopen("Scoreboard.txt", "r");
   if(fptr){
        while(1){
            if(fgets(line, 100, fptr)){
                counter++;
            }
            else{
                break;
            }
        }
    }
   return counter;
}

//Sorts the scoreboard file in an intialized structure
void sortFile(Scoreboard p[], FILE *fptr, int a){

    fptr = fopen("Scoreboard.txt", "r");

    if (fptr){
        for(int i=0; i<a; i++){
            fscanf(fptr, "%s %d", p[i].name, &p[i].score);
        }
    }

    for (int i = 0; i < a; i++){
        for (int j = 0; j < a; j++){
            if (p[j].score < p[i].score){

                int temp = p[i].score;
                p[i].score = p[j].score;
                p[j].score = temp;

                char nameTemp[4];
                strcpy(nameTemp, p[i].name);
                strcpy(p[i].name, p[j].name);
                strcpy(p[j].name, nameTemp);
            }
        }
    }

    fclose(fptr);
}

//Rewrites the new sorted information back to the text file
void writeFile(Scoreboard p[], FILE *fptr, int a){

    fptr = fopen("Scoreboard.txt", "w");

    if(fptr){
        for (int i = 0; i < a; i++){
            fprintf(fptr, "%s %d\n", p[i].name, p[i].score);
        }
    }

    fclose(fptr);
}


