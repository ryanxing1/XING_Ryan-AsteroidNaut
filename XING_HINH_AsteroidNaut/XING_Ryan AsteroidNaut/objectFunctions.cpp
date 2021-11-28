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

#define M_PI acos(-1.0)

//Function that creates hitboxes for platforms; changes player dx and dy accordingly
void platformPhysics(ALLEGRO_EVENT &ev, int x1, int y1, Player p[]){

    if(ev.type == ALLEGRO_EVENT_TIMER){
        if(p[0].location.posy > y1 && p[0].location.posy < y1 + 70){
            if(p[0].location.posx < x1 + 210 && p[0].location.posx > x1 + 200){
                p[0].location.dx = 0;
                p[0].location.posx = x1 + 210;
            }
            else if (p[0].location.posx > x1 && p[0].location.posx < x1 + 10){
                p[0].location.dx = 0;
                p[0].location.posx = x1;
            }
        }

        if (p[0].location.posx > x1 && p[0].location.posx < x1 + 210){
            if(p[0].location.posy < y1 + 70 && p[0].location.posy > y1 + 50){
                p[0].location.dy = 0;
                p[0].location.posy = y1 + 70;
            }
            else if (p[0].location.posy > y1 - 5 && p[0].location.posy < y1 + 15){
                p[0].location.posy = y1 - 5;
                p[0].location.dy = 0;
                p[0].jumps = 0;
            }
        }

        if(p[1].location.posy > y1 && p[1].location.posy < y1 + 70){
            if(p[1].location.posx < x1 + 210 && p[1].location.posx > x1 + 200){
                p[1].location.dx = 0;
                p[1].location.posx = x1 + 210;
            }
            else if (p[1].location.posx > x1 && p[1].location.posx < x1 + 10){
                p[1].location.dx = 0;
                p[1].location.posx = x1;
            }
        }

        if (p[1].location.posx > x1 && p[1].location.posx < x1 + 210){
            if(p[1].location.posy < y1 + 70 && p[1].location.posy > y1 + 50){
                p[1].location.dy = 0;
                p[1].location.posy = y1 + 70;
            }
            else if (p[1].location.posy > y1 - 5 && p[1].location.posy < y1 + 15){
                p[1].location.posy = y1 - 5;
                p[1].location.dy = 0;
                p[1].jumps = 0;
            }
        }

    }
}

//Code that randomly generates platforms in given regions to ensure that jumps are possible
void platformLocations(ALLEGRO_EVENT ev, Coordinates f[], Player p[], bool &intializePlatforms){

    if(!intializePlatforms){

        f[0].x = rand() % (150 - 50 + 1) + 100;
        f[1].x = rand() % (150 - 50 + 1) + 100;
        f[2].x = 350;
        f[3].x = rand() % (650 - 550 + 1) + 550;
        f[4].x = rand() % (650 - 550 + 1) + 550;

        f[0].y = rand() % (630 - 600 + 1) + 600;
        f[1].y = rand() % (300 - 200 + 1) + 200;
        f[2].y = 430;
        f[3].y = rand() % (630 - 600 + 1) + 600;
        f[4].y = rand() % (300 - 200 + 1) + 200;

        intializePlatforms = true;
    }

    if (ev.type == ALLEGRO_EVENT_TIMER){
        platformPhysics(ev, f[0].x, f[0].y, p); // bot left
        platformPhysics(ev, f[1].x, f[1].y, p); // top left
        platformPhysics(ev, f[2].x, f[2].y, p); // middle
        platformPhysics(ev, f[3].x, f[3].y, p); // bot right
        platformPhysics(ev, f[4].x, f[4].y, p); // top right
    }
}

//Animates platform sprites
void drawPlatforms(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], Player p[], Coordinates f[]){
    if(ev.type == ALLEGRO_EVENT_TIMER){
        for (int i = 0; i < 5; i++){

            if(p[0].curr >= 0 && p[0].curr <= 15){
                al_draw_scaled_bitmap(arr[0], 0, 0, 64, 45, f[i].x-15, f[i].y-25, 220, 110, 0);
            }
            if(p[0].curr >= 15 && p[0].curr <= 30){
                al_draw_scaled_bitmap(arr[1], 0, 0, 64, 45, f[i].x-15, f[i].y-25, 220, 110, 0);
            }
            if(p[0].curr >= 30 && p[0].curr <= 45){
                al_draw_scaled_bitmap(arr[2], 0, 0, 64, 45, f[i].x-15, f[i].y-25, 220, 110, 0);
            }
            if(p[0].curr >= 45 && p[0].curr <= 60){
                al_draw_scaled_bitmap(arr[3], 0, 0, 64, 45, f[i].x-15, f[i].y-25, 220, 110, 0);
            }
        }
    }
}

//Animation for a space background
void background(ALLEGRO_EVENT &ev, ALLEGRO_BITMAP *arr[], int &curr1){
    if (ev.type == ALLEGRO_EVENT_TIMER){
        curr1++;
        curr1 %= ANIMATIONSPEED*4;

        if(curr1 <= 80){
            al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 0, 0, 500, 500, 0);
            al_draw_scaled_bitmap(arr[2], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 500, 0, 500, 500, 0);
            al_draw_scaled_bitmap(arr[1], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 0, 500, 500, 500, 0);
            al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 500, 500, 500, 500, 0);

        }
        else if (curr1 <= 160){
            al_draw_scaled_bitmap(arr[1], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 0, 0, 500, 500, 0);
            al_draw_scaled_bitmap(arr[1], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 500, 0, 500, 500, 0);
            al_draw_scaled_bitmap(arr[2], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 0, 500, 500, 500, 0);
            al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 500, 500, 500, 500, 0);

        }
        else{
            al_draw_scaled_bitmap(arr[2], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 0, 0, 500, 500, 0);
            al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 500, 0, 500, 500, 0);
            al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 0, 500, 500, 500, 0);
            al_draw_scaled_bitmap(arr[1], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 500, 500, 500, 500, 0);

        }
    }
}

//Declares/resets asteroid functionality; values can be changed to dictate hitboxes and speeds.
void declareAsteroidArr(Asteroids q[]){
    for(int i=0; i<3; i++){
        q[i].astRad = 40;
        q[i].astSpeed = 7;
        q[i].isCollision = false;
        q[i].startDisplay = false;
        q[i].astCurr = 0;
    }
}

//Draws 3 separate asteroids that have hitboxes; asteroids will always aim at the closest player
void drawAsteroids(ALLEGRO_EVENT &ev, ALLEGRO_BITMAP *arr[], ALLEGRO_BITMAP *arr1[], Player p[], Asteroids q[], bool &gameStop, int gameMode){

    if(q[0].curr2 == 60){

        q[0].isCollision = false;
        q[0].startDisplay = true;

        q[0].side = rand() % 4 + 1;

        if(q[0].side == 1){
            q[0].astPosx = 0;
            q[0].astPosy = rand() % SCREEN_H + 1;
        }
        else if (q[0].side == 2){
            q[0].astPosx = rand() % SCREEN_W + 1;
            q[0].astPosy = 0;
        }
        else if (q[0].side == 3){
            q[0].astPosx = SCREEN_W;
            q[0].astPosy = rand() % SCREEN_H + 1;
        }
        else if (q[0].side == 4){
            q[0].astPosx = rand() % SCREEN_W + 1;
            q[0].astPosy = SCREEN_H;
        }

        q[0].c = calcClosest(p, q, 0, gameMode);
        q[0].angle = atan((p[q[0].c].location.posy - q[0].astPosy) / (p[q[0].c].location.posx - q[0].astPosx));

        if(p[q[0].c].location.posx >= q[0].astPosx){
            q[0].astDirection = true;
        }
        else if (p[q[0].c].location.posx <= q[0].astPosx){
            q[0].astDirection = false;
        }
    }

    if(q[0].curr2 == 120){

        q[1].isCollision = false;
        q[1].startDisplay = true;

        q[1].side = rand() % 4 + 1;

        if(q[1].side == 1){
            q[1].astPosx = 0;
            q[1].astPosy = rand() % SCREEN_H + 1;
        }
        else if (q[1].side == 2){
            q[1].astPosx = rand() % SCREEN_W + 1;
            q[1].astPosy = 0;
        }
        else if (q[1].side == 3){
            q[1].astPosx = SCREEN_W;
            q[1].astPosy = rand() % SCREEN_H + 1;
        }
        else if (q[1].side == 4){
            q[1].astPosx = rand() % SCREEN_W + 1;
            q[1].astPosy = SCREEN_H;
        }

        q[1].c = calcClosest(p, q, 1, gameMode);
        q[1].angle = atan((p[q[1].c].location.posy - q[1].astPosy) / (p[q[1].c].location.posx - q[1].astPosx));

        if(p[q[1].c].location.posx >= q[1].astPosx){
            q[1].astDirection = true;
        }
        else if (p[q[1].c].location.posx <= q[1].astPosx){
            q[1].astDirection = false;
        }
    }

    if(q[0].curr2 == 0){

        q[2].isCollision = false;
        q[2].startDisplay = true;

        q[2].side = rand() % 4 + 1;

        if(q[2].side == 1){
            q[2].astPosx = 0;
            q[2].astPosy = rand() % SCREEN_H + 1;
        }
        else if (q[2].side == 2){
            q[2].astPosx = rand() % SCREEN_W + 1;
            q[2].astPosy = 0;
        }
        else if (q[2].side == 3){
            q[2].astPosx = SCREEN_W;
            q[2].astPosy = rand() % SCREEN_H + 1;
        }
        else if (q[2].side == 4){
            q[2].astPosx = rand() % SCREEN_W + 1;
            q[2].astPosy = SCREEN_H;
        }

        q[2].c = calcClosest(p, q, 2, gameMode);
        q[2].angle = atan((p[q[2].c].location.posy - q[2].astPosy) / (p[q[2].c].location.posx - q[2].astPosx));

        if(p[q[2].c].location.posx >= q[2].astPosx){
            q[2].astDirection = true;
        }
        else if (p[q[2].c].location.posx <= q[2].astPosx){
            q[2].astDirection = false;
        }
    }

    if(q[0].curr2 > 0){

        if(!q[0].isCollision && q[0].startDisplay){
            q[0].distance1 = sqrt(((p[0].location.posx - q[0].astPosx) * (p[0].location.posx - q[0].astPosx)) + ((p[0].location.posy - q[0].astPosy) * ((p[0].location.posy - q[0].astPosy))));
            q[0].distance2 = sqrt(((p[1].location.posx - q[0].astPosx) * (p[1].location.posx - q[0].astPosx)) + ((p[1].location.posy - q[0].astPosy) * ((p[1].location.posy - q[0].astPosy))));

            if(q[0].astDirection){
                if(q[0].astCurr >= 0 && q[0].astCurr <= 5) al_draw_scaled_rotated_bitmap(arr[0], 30, 30, q[0].astPosx, q[0].astPosy, 4,4, q[0].angle - M_PI/1.5, 0);
                else if(q[0].astCurr >= 5 && q[0].astCurr <= 10) al_draw_scaled_rotated_bitmap(arr[1], 30, 30, q[0].astPosx, q[0].astPosy, 4,4, q[0].angle - M_PI/1.5, 0);
                else if(q[0].astCurr >= 10 && q[0].astCurr <= 15) al_draw_scaled_rotated_bitmap(arr[2], 30, 30, q[0].astPosx, q[0].astPosy, 4,4, q[0].angle - M_PI/1.5, 0);
                else if(q[0].astCurr >= 15 && q[0].astCurr <= 20) al_draw_scaled_rotated_bitmap(arr[3], 30, 30, q[0].astPosx, q[0].astPosy, 4,4, q[0].angle - M_PI/1.5, 0);
            }
            else{
                if(q[0].astCurr >= 0 && q[0].astCurr <= 5) al_draw_scaled_rotated_bitmap(arr[0], 30, 30, q[0].astPosx, q[0].astPosy, 4,4, q[0].angle + M_PI/2.75, 0);
                else if(q[0].astCurr >= 5 && q[0].astCurr <= 10) al_draw_scaled_rotated_bitmap(arr[1], 30, 30, q[0].astPosx, q[0].astPosy, 4,4, q[0].angle + M_PI/2.75, 0);
                else if(q[0].astCurr >= 10 && q[0].astCurr <= 15) al_draw_scaled_rotated_bitmap(arr[2], 30, 30, q[0].astPosx, q[0].astPosy, 4,4, q[0].angle + M_PI/2.75, 0);
                else if(q[0].astCurr >= 15 && q[0].astCurr <= 20) al_draw_scaled_rotated_bitmap(arr[3], 30, 30, q[0].astPosx, q[0].astPosy, 4,4, q[0].angle + M_PI/2.75, 0);
            }

            if(q[0].side == 1){
                q[0].astPosx += cos(q[0].angle) * q[0].astSpeed;
                q[0].astPosy += sin(q[0].angle) * q[0].astSpeed;
            }
            else if (q[0].side == 3){
                q[0].astPosx -= cos(q[0].angle) * q[0].astSpeed;
                q[0].astPosy -= sin(q[0].angle) * q[0].astSpeed;

            }
            else if (q[0].side == 2 || q[0].side == 4){
                if(q[0].astDirection){
                    q[0].astPosx += cos(q[0].angle) * q[0].astSpeed;
                    q[0].astPosy += sin(q[0].angle) * q[0].astSpeed;
                }
                else{
                    q[0].astPosx -= cos(q[0].angle) * q[0].astSpeed;
                    q[0].astPosy -= sin(q[0].angle) * q[0].astSpeed;
                }
            }

            if(q[0].distance1 <= (q[0].astRad + 20) && p[0].health > 0){
                q[0].isCollision = true;
                p[q[0].c].health--;

                q[0].explosionCurr = 0;
                q[0].tempX = p[0].location.posx;
                q[0].tempY = p[0].location.posy;
            }
            else if(q[0].distance2 <= (q[0].astRad + 20) && p[1].health > 0 && gameMode == 1){
                q[0].isCollision = true;
                p[1].health--;

                q[0].explosionCurr = 0;
                q[0].tempX = p[1].location.posx;
                q[0].tempY = p[1].location.posy;

            }
        }

        if(q[0].isCollision){

            q[0].explosionCurr++;

            if(q[0].explosionCurr >= 0 && q[0].explosionCurr <= 10){
                al_draw_scaled_bitmap(arr1[0], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[0].tempX - 100, q[0].tempY - 100, 200, 200, 0);
            }
            else if(q[0].explosionCurr >= 10 && q[0].explosionCurr <= 20){
                al_draw_scaled_bitmap(arr1[1], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[0].tempX - 100, q[0].tempY - 100, 200, 200, 0);
            }
            else if(q[0].explosionCurr >= 20 && q[0].explosionCurr <= 30){
                al_draw_scaled_bitmap(arr1[2], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[0].tempX - 100, q[0].tempY - 100, 200, 200, 0);
            }
            else if(q[0].explosionCurr >= 30 && q[0].explosionCurr <= 40){
                al_draw_scaled_bitmap(arr1[3], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[0].tempX - 100, q[0].tempY - 100, 200, 200, 0);
            }
            else if(q[0].explosionCurr >= 40 && q[0].explosionCurr <= 50){
                al_draw_scaled_bitmap(arr1[4], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[0].tempX - 100, q[0].tempY - 100, 200, 200, 0);
            }
            else if(q[0].explosionCurr >= 50 && q[0].explosionCurr <= 60){
                al_draw_scaled_bitmap(arr1[5], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[0].tempX - 100, q[0].tempY - 100, 200, 200, 0);
            }
        }


        if(!q[1].isCollision && q[1].startDisplay){
            q[1].distance1 = sqrt(((p[0].location.posx - q[1].astPosx) * (p[0].location.posx - q[1].astPosx)) + ((p[0].location.posy - q[1].astPosy) * ((p[0].location.posy - q[1].astPosy))));
            q[1].distance2 = sqrt(((p[1].location.posx - q[1].astPosx) * (p[1].location.posx - q[1].astPosx)) + ((p[1].location.posy - q[1].astPosy) * ((p[1].location.posy - q[1].astPosy))));

            if(q[1].astDirection){
                if(q[0].astCurr >= 0 && q[0].astCurr <= 5) al_draw_scaled_rotated_bitmap(arr[0], 30, 30, q[1].astPosx, q[1].astPosy, 4,4, q[1].angle - M_PI/1.5, 0);
                else if(q[0].astCurr >= 5 && q[0].astCurr <= 10) al_draw_scaled_rotated_bitmap(arr[1], 30, 30, q[1].astPosx, q[1].astPosy, 4,4, q[1].angle - M_PI/1.5, 0);
                else if(q[0].astCurr >= 10 && q[0].astCurr <= 15) al_draw_scaled_rotated_bitmap(arr[2], 30, 30, q[1].astPosx, q[1].astPosy, 4,4, q[1].angle - M_PI/1.5, 0);
                else if(q[0].astCurr >= 15 && q[0].astCurr <= 20) al_draw_scaled_rotated_bitmap(arr[3], 30, 30, q[1].astPosx, q[1].astPosy, 4,4, q[1].angle - M_PI/1.5, 0);

            }
            else{
                if(q[0].astCurr >= 0 && q[0].astCurr <= 5) al_draw_scaled_rotated_bitmap(arr[0], 30, 30, q[1].astPosx, q[1].astPosy, 4,4, q[1].angle + M_PI/2.75, 0);
                else if(q[0].astCurr >= 5 && q[0].astCurr <= 10) al_draw_scaled_rotated_bitmap(arr[1], 30, 30, q[1].astPosx, q[1].astPosy, 4,4, q[1].angle + M_PI/2.75, 0);
                else if(q[0].astCurr >= 10 && q[0].astCurr <= 15) al_draw_scaled_rotated_bitmap(arr[2], 30, 30, q[1].astPosx, q[1].astPosy, 4,4, q[1].angle + M_PI/2.75, 0);
                else if(q[0].astCurr >= 15 && q[0].astCurr <= 20) al_draw_scaled_rotated_bitmap(arr[3], 30, 30, q[1].astPosx, q[1].astPosy, 4,4, q[1].angle + M_PI/2.75, 0);
            }
            if(q[1].side == 1){
                q[1].astPosx += cos(q[1].angle) * q[1].astSpeed;
                q[1].astPosy += sin(q[1].angle) * q[1].astSpeed;
            }
            else if (q[1].side == 3){
                q[1].astPosx -= cos(q[1].angle) * q[1].astSpeed;
                q[1].astPosy -= sin(q[1].angle) * q[1].astSpeed;

            }
            else if (q[1].side == 2 || q[1].side == 4){
                if(q[1].astDirection){
                    q[1].astPosx += cos(q[1].angle) * q[1].astSpeed;
                    q[1].astPosy += sin(q[1].angle) * q[1].astSpeed;
                }
                else{
                    q[1].astPosx -= cos(q[1].angle) * q[1].astSpeed;
                    q[1].astPosy -= sin(q[1].angle) * q[1].astSpeed;
                }
            }

            if(q[1].distance1 <= (q[1].astRad + 20) && p[0].health > 0){
                q[1].isCollision = true;
                p[0].health--;

                q[1].explosionCurr = 0;
                q[1].tempX = p[0].location.posx;
                q[1].tempY = p[0].location.posy;
            }
            else if(q[1].distance2 <= (q[1].astRad + 20) && p[1].health > 0 && gameMode == 1){
                q[1].isCollision = true;
                p[1].health--;

                q[1].explosionCurr = 0;
                q[1].tempX = p[1].location.posx;
                q[1].tempY = p[1].location.posy;

            }

        }

        if(q[1].isCollision){
            q[1].explosionCurr++;

            if(q[1].explosionCurr >= 0 && q[1].explosionCurr <= 10){
                al_draw_scaled_bitmap(arr1[0], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[1].tempX - 100, q[1].tempY - 100, 200, 200, 0);
            }
            else if(q[1].explosionCurr >= 10 && q[1].explosionCurr <= 20){
                al_draw_scaled_bitmap(arr1[1], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[1].tempX - 100, q[1].tempY - 100, 200, 200, 0);
            }
            else if(q[1].explosionCurr >= 20 && q[1].explosionCurr <= 30){
                al_draw_scaled_bitmap(arr1[2], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[1].tempX - 100, q[1].tempY - 100, 200, 200, 0);
            }
            else if(q[1].explosionCurr >= 30 && q[1].explosionCurr <= 40){
                al_draw_scaled_bitmap(arr1[3], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[1].tempX - 100, q[1].tempY - 100, 200, 200, 0);
            }
            else if(q[1].explosionCurr >= 40 && q[1].explosionCurr <= 50){
                al_draw_scaled_bitmap(arr1[4], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[1].tempX - 100, q[1].tempY - 100, 200, 200, 0);
            }
            else if(q[1].explosionCurr >= 50 && q[1].explosionCurr <= 60){
                al_draw_scaled_bitmap(arr1[5], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[1].tempX - 100, q[1].tempY - 100, 200, 200, 0);
            }
        }

        if(!q[2].isCollision && q[2].startDisplay){
            q[2].distance1 = sqrt(((p[0].location.posx - q[2].astPosx) * (p[0].location.posx - q[2].astPosx)) + ((p[0].location.posy - q[2].astPosy) * ((p[0].location.posy - q[2].astPosy))));
            q[2].distance2 = sqrt(((p[1].location.posx - q[2].astPosx) * (p[1].location.posx - q[2].astPosx)) + ((p[1].location.posy - q[2].astPosy) * ((p[1].location.posy - q[2].astPosy))));

            if(q[2].astDirection){
                if(q[0].astCurr >= 0 && q[0].astCurr <= 5) al_draw_scaled_rotated_bitmap(arr[0], 30, 30, q[2].astPosx, q[2].astPosy, 4,4, q[2].angle - M_PI/1.5, 0);
                else if(q[0].astCurr >= 5 && q[0].astCurr <= 10) al_draw_scaled_rotated_bitmap(arr[1], 30, 30, q[2].astPosx, q[2].astPosy, 4,4, q[2].angle - M_PI/1.5, 0);
                else if(q[0].astCurr >= 10 && q[0].astCurr <= 15) al_draw_scaled_rotated_bitmap(arr[2], 30, 30, q[2].astPosx, q[2].astPosy, 4,4, q[2].angle - M_PI/1.5, 0);
                else if(q[0].astCurr >= 15 && q[0].astCurr <= 20) al_draw_scaled_rotated_bitmap(arr[3], 30, 30, q[2].astPosx, q[2].astPosy, 4,4, q[2].angle - M_PI/1.5, 0);

            }
            else{
                if(q[0].astCurr >= 0 && q[0].astCurr <= 5) al_draw_scaled_rotated_bitmap(arr[0], 30, 30, q[2].astPosx, q[2].astPosy, 4,4, q[2].angle + M_PI/2.75, 0);
                else if(q[0].astCurr >= 5 && q[0].astCurr <= 10) al_draw_scaled_rotated_bitmap(arr[1], 30, 30, q[2].astPosx, q[2].astPosy, 4,4, q[2].angle + M_PI/2.75, 0);
                else if(q[0].astCurr >= 10 && q[0].astCurr <= 15) al_draw_scaled_rotated_bitmap(arr[2], 30, 30, q[2].astPosx, q[2].astPosy, 4,4, q[2].angle + M_PI/2.75, 0);
                else if(q[0].astCurr >= 15 && q[0].astCurr <= 20) al_draw_scaled_rotated_bitmap(arr[3], 30, 30, q[2].astPosx, q[2].astPosy, 4,4, q[2].angle + M_PI/2.75, 0);
            }

            if(q[2].side == 1){
                q[2].astPosx += cos(q[2].angle) * q[2].astSpeed;
                q[2].astPosy += sin(q[2].angle) * q[2].astSpeed;
            }
            else if (q[2].side == 3){
                q[2].astPosx -= cos(q[2].angle) * q[2].astSpeed;
                q[2].astPosy -= sin(q[2].angle) * q[2].astSpeed;

            }
            else if (q[2].side == 2 || q[2].side == 4){
                if(q[2].astDirection){
                    q[2].astPosx += cos(q[2].angle) * q[2].astSpeed;
                    q[2].astPosy += sin(q[2].angle) * q[2].astSpeed;
                }
                else{
                    q[2].astPosx -= cos(q[2].angle) * q[2].astSpeed;
                    q[2].astPosy -= sin(q[2].angle) * q[2].astSpeed;
                }
            }

            if(q[2].distance1 <= (q[2].astRad + 20) && p[0].health > 0){
                q[2].isCollision = true;
                p[0].health--;

                q[2].explosionCurr = 0;
                q[2].tempX = p[0].location.posx;
                q[2].tempY = p[0].location.posy;
            }
            else if(q[2].distance2 <= (q[2].astRad + 20) && p[1].health > 0 && gameMode == 1){
                q[2].isCollision = true;
                p[1].health--;

                q[2].explosionCurr = 0;
                q[2].tempX = p[1].location.posx;
                q[2].tempY = p[1].location.posy;

            }
        }

        if(q[2].isCollision){

            q[2].explosionCurr++;

            if(q[2].explosionCurr >= 0 && q[2].explosionCurr <= 10){
                al_draw_scaled_bitmap(arr1[0], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[2].tempX - 100, q[2].tempY - 100, 200, 200, 0);
            }
            else if(q[2].explosionCurr >= 10 && q[2].explosionCurr <= 20){
                al_draw_scaled_bitmap(arr1[1], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[2].tempX - 100, q[2].tempY - 100, 200, 200, 0);
            }
            else if(q[2].explosionCurr >= 20 && q[2].explosionCurr <= 30){
                al_draw_scaled_bitmap(arr1[2], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[2].tempX - 100, q[2].tempY - 100, 200, 200, 0);
            }
            else if(q[2].explosionCurr >= 30 && q[2].explosionCurr <= 40){
                al_draw_scaled_bitmap(arr1[3], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[2].tempX - 100, q[2].tempY - 100, 200, 200, 0);
            }
            else if(q[2].explosionCurr >= 40 && q[2].explosionCurr <= 50){
                al_draw_scaled_bitmap(arr1[4], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[2].tempX - 100, q[2].tempY - 100, 200, 200, 0);
            }
            else if(q[2].explosionCurr >= 50 && q[2].explosionCurr <= 60){
                al_draw_scaled_bitmap(arr1[5], 0, 0, al_get_bitmap_width(arr1[0]), al_get_bitmap_height(arr1[0]), q[2].tempX - 100, q[2].tempY - 100, 200, 200, 0);
            }
        }
    }

    if(ev.type == ALLEGRO_EVENT_TIMER){
        q[0].curr2++;
        q[0].curr2 %= 180;
        q[0].astCurr ++;
        q[0].astCurr %= 20;

    }
}

//Draws hearts that correlate to the players' health
void drawHearts(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], Player p[], int gameMode){
    if(gameMode == 1){
        al_draw_scaled_bitmap(arr[p[0].health], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 0, -50, 150, 150, 0);
        al_draw_scaled_bitmap(arr[p[1].health+7], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 850, -50, 150, 150, 0);
    }
    else{
        al_draw_scaled_bitmap(arr[p[0].health], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 0, -50, 150, 150, 0);
    }

}

//Animates playbutton
void playButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int &curr4){

    if (ev.type == ALLEGRO_EVENT_TIMER){
        curr4++;
        curr4 %= 200;
    }
    if (curr4 < 40){
        al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 220, 100, 600, 600, 0);
    }
    else if (curr4 < 80){
        al_draw_scaled_bitmap(arr[1], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 244, 100, 600, 600, 0);
    }
    else if (curr4 < 120){
        al_draw_scaled_bitmap(arr[2], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 268, 100, 600, 600, 0);
    }
    else if (curr4 < 160){
        al_draw_scaled_bitmap(arr[3], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 292, 100, 600, 600, 0);
    }
    else if (curr4 < 200){
        al_draw_scaled_bitmap(arr[4], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 316, 100, 600, 600, 0);
    }
}

//Animates hiscore button
void hiscoreButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int &curr4){
    if (ev.type == ALLEGRO_EVENT_TIMER){
        curr4++;
        curr4 %= 200;
    }
    if (curr4 < 25){
        al_draw_scaled_bitmap(arr[5], 0, 0, al_get_bitmap_width(arr[5]), al_get_bitmap_height(arr[5]), 210, 200, 600, 600, 0);
    }
    else if (curr4 < 50){
        al_draw_scaled_bitmap(arr[6], 0, 0, al_get_bitmap_width(arr[5]), al_get_bitmap_height(arr[5]), 234, 200, 600, 600, 0);
    }
    else if (curr4 < 75){
        al_draw_scaled_bitmap(arr[7], 0, 0, al_get_bitmap_width(arr[5]), al_get_bitmap_height(arr[5]), 258, 200, 600, 600, 0);
    }
    else if (curr4 < 100){
        al_draw_scaled_bitmap(arr[8], 0, 0, al_get_bitmap_width(arr[5]), al_get_bitmap_height(arr[5]), 282, 200, 600, 600, 0);
    }
    else if (curr4 < 125){
        al_draw_scaled_bitmap(arr[9], 0, 0, al_get_bitmap_width(arr[5]), al_get_bitmap_height(arr[5]), 306, 200, 600, 600, 0);
    }
    else if (curr4 < 150){
        al_draw_scaled_bitmap(arr[10], 0, 0, al_get_bitmap_width(arr[10]), al_get_bitmap_height(arr[10]), 210, 224, 600, 600, 0);
    }
    else if (curr4 < 175){
        al_draw_scaled_bitmap(arr[11], 0, 0, al_get_bitmap_width(arr[11]), al_get_bitmap_height(arr[11]), 234, 224, 600, 600, 0);
    }
    else if (curr4 < 200){
        al_draw_scaled_bitmap(arr[12], 0, 0, al_get_bitmap_width(arr[11]), al_get_bitmap_height(arr[11]), 258, 224, 600, 600, 0);
    }
}

//Animates help button
void helpButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int &curr4){
    if (ev.type == ALLEGRO_EVENT_TIMER){
        curr4++;
        curr4 %= 200;
    }
    if (curr4 < 40){
        al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 220, 250, 600, 600, 0);
    }
    else if (curr4 < 80){
        al_draw_scaled_bitmap(arr[13], 0, 0, al_get_bitmap_width(arr[13]), al_get_bitmap_height(arr[13]), 292, 298, 600, 600, 0);
    }

    else if (curr4 < 120){
        al_draw_scaled_bitmap(arr[14], 0, 0, al_get_bitmap_width(arr[13]), al_get_bitmap_height(arr[13]), 316, 298, 600, 600, 0);
    }
    else if (curr4 < 160){
        al_draw_scaled_bitmap(arr[15], 0, 0, al_get_bitmap_width(arr[13]), al_get_bitmap_height(arr[13]), 220, 322, 600, 600, 0);
    }
    else if (curr4 < 200){
        al_draw_scaled_bitmap(arr[16], 0, 0, al_get_bitmap_width(arr[13]), al_get_bitmap_height(arr[13]), 244, 322, 600, 600, 0);
    }
}

//Animates exitbutton
void exitButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int curr4){
    if (ev.type == ALLEGRO_EVENT_TIMER){
        curr4++;
        curr4 %= 200;

    }

    if (curr4 < 40){
        al_draw_scaled_bitmap(arr[7], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 210, 320, 600, 600, 0);
    }
    else if (curr4 < 80){
        al_draw_scaled_bitmap(arr[8], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 210, 320, 600, 600, 0);
    }
    else if (curr4 < 120){
        al_draw_scaled_bitmap(arr[9], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 210, 320, 600, 600, 0);
    }
    else if (curr4 < 160){
        al_draw_scaled_bitmap(arr[10], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 210, 320, 600, 600, 0);
    }
    else if (curr4 < 200){
        al_draw_scaled_bitmap(arr[11], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 210, 320, 600, 600, 0);
    }
}

//Animates oneplayer button
void oneplayerButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int curr4){

    if (ev.type == ALLEGRO_EVENT_TIMER){
        curr4++;
        curr4 %= 200;
    }
    if (curr4 < 28){
        al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 10, 65, 600, 600, 0);
    }
    else if (curr4 < 56){
        al_draw_scaled_bitmap(arr[1], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 10, 65, 600, 600, 0);
    }
    else if (curr4 < 84){
        al_draw_scaled_bitmap(arr[2], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 10, 65, 600, 600, 0);
    }
    else if (curr4 < 112){
        al_draw_scaled_bitmap(arr[3], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 10, 65, 600, 600, 0);
    }
    else if (curr4 < 140){
        al_draw_scaled_bitmap(arr[4], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 10, 65, 600, 600, 0);
    }
    else if (curr4 < 168){
        al_draw_scaled_bitmap(arr[5], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 10, 65, 600, 600, 0);
    }
    else if (curr4 <= 200){
        al_draw_scaled_bitmap(arr[6], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 10, 65, 600, 600, 0);
    }

}

//Animates two player button
void twoplayerButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int &curr4){

    if (ev.type == ALLEGRO_EVENT_TIMER){
        curr4++;
        curr4 %= 200;
    }
    if (curr4 < 28){
        al_draw_scaled_bitmap(arr[17], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 458, 148, 600, 600, 0);
    }
    else if (curr4 < 56){
        al_draw_scaled_bitmap(arr[18], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 482, 148, 600, 600, 0);
    }
    else if (curr4 < 84){
        al_draw_scaled_bitmap(arr[19], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 506, 148, 600, 600, 0);
    }
    else if (curr4 < 112){
        al_draw_scaled_bitmap(arr[20], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 410, 172, 600, 600, 0);
    }
    else if (curr4 < 140){
        al_draw_scaled_bitmap(arr[21], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 434, 172, 600, 600, 0);
    }
    else if (curr4 < 168){
        al_draw_scaled_bitmap(arr[22], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 458, 172, 600, 600, 0);
    }
    else if (curr4 <= 200){
        al_draw_scaled_bitmap(arr[23], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 482, 172, 600, 600, 0);
    }
}

//Displays instructions in help screen
void instructions(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *png, ALLEGRO_FONT *font){
    if (ev.type == ALLEGRO_EVENT_TIMER){
        al_draw_scaled_bitmap(png, 0, 0, al_get_bitmap_width(png), al_get_bitmap_height(png), 50, 0, 750, 750, 0);
        al_draw_text(font, WHITE, 450, 500, 0, "1 Use the Arrow Keys to move");
        al_draw_text(font, WHITE, 450, 520, 0, "2 Do not get hit by the asteroids");
        al_draw_text(font, WHITE, 450, 540, 0, "3 Use the platforms to jump over asteroids");
        al_draw_text(font, WHITE, 450, 580, 0, "Tips");
        al_draw_text(font, WHITE, 450, 600, 0, "Make use of all five platforms");
        al_draw_text(font, WHITE, 450, 620, 0, "Remember about the double jump");
        al_draw_text(font, WHITE, 450, 640, 0, "Do not fall into the void");
        al_draw_text(font, WHITE, 450, 660, 0, "Just survive");
    }
}

//Animates the title
void drawTitle(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int &curr3){
    if (ev.type == ALLEGRO_EVENT_TIMER){
        curr3++;
        curr3 %= 30;

        if(curr3 >= 0 && curr3 <= 10){
            al_draw_scaled_bitmap(arr[0], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 250, -75, 500, 500, 0);
        }
        else if(curr3 >= 10 && curr3 <= 20){
            al_draw_scaled_bitmap(arr[1], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 250, -75, 500, 500, 0);
        }
        else if(curr3 >= 20 && curr3 <= 30){
            al_draw_scaled_bitmap(arr[2], 0, 0, al_get_bitmap_width(arr[0]), al_get_bitmap_height(arr[0]), 250, -75, 500, 500, 0);
        }

    }
}

//Displays mainmenu
void mainMenu(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], ALLEGRO_BITMAP *arr1[], int &curr4){

    playButton(ev, arr, curr4);
    hiscoreButton(ev, arr, curr4);
    helpButton(ev, arr, curr4);
    exitButton(ev, arr1, curr4);

}


//Displays top ten high scores
void hiScores(ALLEGRO_EVENT ev, ALLEGRO_FONT *font, Scoreboard p[]){
    if (ev.type == ALLEGRO_EVENT_TIMER){
        al_draw_text(font, WHITE, 500, 150, ALLEGRO_ALIGN_CENTER, "HIGH SCORES");
        al_draw_textf(font, WHITE, 500, 200, ALLEGRO_ALIGN_CENTER, "%s %d", p[0].name, p[0].score);
        al_draw_textf(font, WHITE, 500, 230, ALLEGRO_ALIGN_CENTER, "%s %d", p[1].name, p[1].score);
        al_draw_textf(font, WHITE, 500, 260, ALLEGRO_ALIGN_CENTER, "%s %d", p[2].name, p[2].score);
        al_draw_textf(font, WHITE, 500, 290, ALLEGRO_ALIGN_CENTER, "%s %d", p[3].name, p[3].score);
        al_draw_textf(font, WHITE, 500, 320, ALLEGRO_ALIGN_CENTER, "%s %d", p[4].name, p[4].score);
        al_draw_textf(font, WHITE, 500, 350, ALLEGRO_ALIGN_CENTER, "%s %d", p[5].name, p[5].score);
        al_draw_textf(font, WHITE, 500, 380, ALLEGRO_ALIGN_CENTER, "%s %d", p[6].name, p[6].score);
        al_draw_textf(font, WHITE, 500, 410, ALLEGRO_ALIGN_CENTER, "%s %d", p[7].name, p[7].score);
        al_draw_textf(font, WHITE, 500, 440, ALLEGRO_ALIGN_CENTER, "%s %d", p[8].name, p[8].score);
        al_draw_textf(font, WHITE, 500, 470, ALLEGRO_ALIGN_CENTER, "%s %d", p[9].name, p[9].score);
    }
}

//Adds score to ongoing game and displays it
void printScore(ALLEGRO_EVENT ev, ALLEGRO_FONT *font, Scoreboard p[], Player z[], int gameMode){
    if(ev.type == ALLEGRO_EVENT_TIMER){
        if(z[0].health > 0){
            p[0].score += 1;
        }
        if(z[1].health > 0){
            p[1].score += 1;
        }
        if(gameMode == 1){
            al_draw_textf(font, WHITE, 500, 0, ALLEGRO_ALIGN_CENTER, "Red %d                                     Blue %d", p[0].score, p[1].score);
        }
        else{
            al_draw_textf(font, WHITE, 500, 0, ALLEGRO_ALIGN_CENTER, "Red %d", p[0].score);

        }
    }
}

//Click functionality for buttons
int clicked(ALLEGRO_EVENT ev, int mouseX1, int mouseY1, int mouseX2, int mouseY2){

    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if (ev.mouse.x > mouseX1 && ev.mouse.x < mouseX2){
            if (ev.mouse.y > mouseY1 && ev.mouse.y < mouseY2){
                return 1;
            }
        }
    }
    else{
        return 0;
    }
}
