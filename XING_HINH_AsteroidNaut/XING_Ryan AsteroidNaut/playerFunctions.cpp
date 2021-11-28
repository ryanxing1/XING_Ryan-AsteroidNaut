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

//Declares all character attributes
void createCharArr(Player p[], Scoreboard z[]){
    for(int i = 0; i < 2; i++){
        p[i].up = false;
        p[i].left = false;
        p[i].right = false;
        p[i].jumps = 0;
        p[i].health = 6;
        p[i].curr = 0;
        p[i].direction = false;

        p[i].location.dx = 0;
        p[i].location.dy = 0;
        z[i].score = 0;
    }
    p[0].location.posx = 400;
    p[0].location.posy = 440;
    p[1].location.posx = 480;
    p[1].location.posy = 440;

}

//Physics engine for player movement
void playerMovement(ALLEGRO_EVENT &ev, ALLEGRO_BITMAP *arr[], bool &gameStop, Player p[], int z){

    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        	gameStop = true;
    }

    //Controls for player 1
    if(z == 0){
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    if(p[z].jumps < 2){
                        p[z].location.dy = -12;
                        p[z].jumps += 1;
                    }
                    break;

                case ALLEGRO_KEY_LEFT:
                    p[z].left = true;
                    p[z].direction = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    p[z].right = true;
                    p[z].direction = true;
                    break;

            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT:
                    p[z].left = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    p[z].right = false;
                    break;
            }
        }
    }

    //Controls for player two
    if(z == 1){
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_W:
                    if(p[z].jumps < 2){
                        p[z].location.dy = -12;
                        p[z].jumps += 1;
                    }
                    break;

                case ALLEGRO_KEY_A:
                    p[z].left = true;
                    p[z].direction = false;
                    break;
                case ALLEGRO_KEY_D:
                    p[z].right = true;
                    p[z].direction = true;
                    break;

            }
        }
        else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_A:
                    p[z].left = false;
                    break;
                case ALLEGRO_KEY_D:
                    p[z].right = false;
                    break;
            }
        }
    }


    if (ev.type == ALLEGRO_EVENT_TIMER){

        p[0].curr++;
        p[0].curr %= 30;

        p[z].location.posx += p[z].location.dx; //Draws the location of the player
        p[z].location.posy += p[z].location.dy;


        if (p[z].left && p[z].location.dy < 0.3 && p[z].location.dy >= 0){

            //printf("animatin walking left\n");

            if (p[0].curr >= ANIMATIONSPEED/4){
                al_draw_scaled_bitmap(arr[2], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

            else if (p[0].curr <= ANIMATIONSPEED/4){
                al_draw_scaled_bitmap(arr[3], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }
        }

        else if (p[z].right && p[z].location.dy < 0.3 && p[z].location.dy >= 0){

            //printf("Animating Walking Right\n");

            if (p[0].curr >= ANIMATIONSPEED/4){
                al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

            else if (p[0].curr <= ANIMATIONSPEED/4){
                al_draw_scaled_bitmap(arr[1], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

        }

        else if (p[z].location.dy < 0){

            //printf("Jumping Animation\n");

            if (p[z].location.dy <= -7 && p[z].direction == true){
                al_draw_scaled_bitmap(arr[4], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

            else if (p[z].location.dy >= -7 && p[z].direction == true){
                al_draw_scaled_bitmap(arr[5], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

            else if (p[z].location.dy <= -7 && p[z].direction == false){
                al_draw_scaled_bitmap(arr[9], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

            else if (p[z].location.dy >= -7 && p[z].direction == false){
                al_draw_scaled_bitmap(arr[10], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }
        }

        if (p[z].jumps < 2 && p[z].location.dy > 0.3){

            //printf("Normal Fall\n");

            if (p[z].direction){
                al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }
            if (!p[z].direction){
                al_draw_scaled_bitmap(arr[2], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }
        }


        if (p[z].jumps == 2 && p[z].location.dy > 0){

            //printf("Falling animation\n");

            if (p[z].location.dy < 1 && p[z].direction == true){
                al_draw_scaled_bitmap(arr[6], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

            else if (p[z].location.dy < 3 && p[z].direction == true){
                al_draw_scaled_bitmap(arr[7], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

            else if (p[z].location.dy > 3 && p[z].direction == true){
                al_draw_scaled_bitmap(arr[8], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

            if (p[z].location.dy < 1 && p[z].direction == false){
                al_draw_scaled_bitmap(arr[11], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

            else if (p[z].location.dy < 3 && p[z].direction == false){
                al_draw_scaled_bitmap(arr[12], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }

            else if (p[z].location.dy > 3 && p[z].direction == false){
                al_draw_scaled_bitmap(arr[13], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            }
        }

        else if(p[z].direction == true && p[z].left == false && p[z].right == false && p[z].location.dy < 0.3 && p[z].location.dy >= 0){
            al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            //printf("stopped animation\n");

        }

        else if(p[z].direction == false && p[z].left == false && p[z].right == false && p[z].location.dy < 0.3 && p[z].location.dy >= 0){
            al_draw_scaled_bitmap(arr[2], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), p[z].location.posx - 75, p[z].location.posy - 75, 150, 150, 0);
            //printf("stopped animation\n");

        }


        //Checks if keyse are pressed and adds velocity accordingly
        if(p[z].left && p[z].location.dx > -5){
            p[z].location.dx -= 0.5;
        }
        if(p[z].right && p[z].location.dx < 5){
            p[z].location.dx += 0.5;
        }
        if(!p[z].left && p[z].location.dx < 0){
            p[z].location.dx += 0.5;
        }
        if(!p[z].right && p[z].location.dx > 0){
            p[z].location.dx -= 0.5;
        }

        //Checks if player is airborne (gravity physics)
        if(p[z].location.posy < SCREEN_H - 20 && p[z].location.dy < 5){

            if (p[z].location.dy < 0){
                p[z].location.dy += 0.5;
            }
            else{
                 p[z].location.dy += 0.2;
            }
        }

        //Out of bounds regions (Kills player)
        if(p[z].location.posy > SCREEN_H - 20){
            p[z].health = 0;
        }
        if(p[z].location.posx > SCREEN_W + 50){
            p[z].health = 0;
        }
        if(p[z].location.posx < 1){
            p[z].health = 0;
        }


    }
}

//Calculates which player the asteroids should shoot towards
int calcClosest(Player p[], Asteroids q[], int i, int gameMode){
    int dist1 = sqrt(((p[0].location.posx - q[i].astPosx) * (p[0].location.posx - q[i].astPosx)) + ((p[0].location.posy - q[i].astPosy) * ((p[0].location.posy - q[i].astPosy))));
    int dist2 = sqrt(((p[1].location.posx - q[i].astPosx) * (p[1].location.posx - q[i].astPosx)) + ((p[1].location.posy - q[i].astPosy) * ((p[1].location.posy - q[i].astPosy))));

    if(gameMode == 1){
        if(dist1 < dist2 && p[0].health > 0){
        return 0;
        }
        else if(p[1].health <= 0){
            return 0;
        }
        if(dist2 < dist1 && p[1].health > 0){
            return 1;
        }
        else if(p[0].health <= 0){
            return 1;
        }
    }
    else{
        return 0;
    }

}

