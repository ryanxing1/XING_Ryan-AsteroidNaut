#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_native_dialog.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/mouse.h>
#include "game.h"

//Creates bitmap arrays and checks if they are valid
int createSprites(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *arr[], ALLEGRO_BITMAP *arr1[], ALLEGRO_BITMAP *arr2[], ALLEGRO_BITMAP *arr3[], ALLEGRO_BITMAP *arr4[], ALLEGRO_BITMAP *arr5[], ALLEGRO_BITMAP *arr6[], ALLEGRO_BITMAP *arr7[], ALLEGRO_BITMAP *arr8[], ALLEGRO_BITMAP *arr9[]){

    ALLEGRO_BITMAP *spriteSheet;
    spriteSheet = al_load_bitmap("Astronaut Sprite Sheet.png");

    if (!spriteSheet) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize spritesheet!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    ALLEGRO_BITMAP *spriteSheet1;
    spriteSheet1 = al_load_bitmap("Astronaut Sprite Sheet 2.png");

    if (!spriteSheet1) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize spritesheet!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    ALLEGRO_BITMAP *spriteSheet2;
    spriteSheet2 = al_load_bitmap("Galaxy Background.png");

    if (!spriteSheet2) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize spritesheet!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    ALLEGRO_BITMAP *spriteSheet3;
    spriteSheet3 = al_load_bitmap("Platform Sprite Sheet.png");

    if (!spriteSheet3) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize spritesheet!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    ALLEGRO_BITMAP *spriteSheet4;
    spriteSheet4 = al_load_bitmap("Asteroid Sprite Sheet.png");

    if (!spriteSheet4) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize spritesheet!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    ALLEGRO_BITMAP *spriteSheet5;
    spriteSheet5 = al_load_bitmap("Explosion Sprite Sheet.png");

    if (!spriteSheet5) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize spritesheet!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    ALLEGRO_BITMAP *spriteSheet6;
    spriteSheet6 = al_load_bitmap("Menu Sprite Sheet.png");

    if (!spriteSheet6) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize spritesheet!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    ALLEGRO_BITMAP *spriteSheet7;
    spriteSheet7 = al_load_bitmap("onePlayerExit Sprite Sheet.png");

    if (!spriteSheet7) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize spritesheet!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    ALLEGRO_BITMAP *spriteSheet8;
    spriteSheet8 = al_load_bitmap("Title Screen Sprite Sheet.png");

    if (!spriteSheet8) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize spritesheet!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    ALLEGRO_BITMAP *spriteSheet9;
    spriteSheet9 = al_load_bitmap("Hearts Sprite Sheet.png");

    if (!spriteSheet9) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize spritesheet!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            arr[i*4+j] = al_create_sub_bitmap(spriteSheet, j*512 , i*512, 512, 512);
        }
    }

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            arr1[i*4+j] = al_create_sub_bitmap(spriteSheet1, j*512 , i*512, 512, 512);
        }
    }

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            arr2[i*2+j] = al_create_sub_bitmap(spriteSheet2, j*100 , i*100, 100, 100);
        }
    }

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            arr3[i*2+j] = al_create_sub_bitmap(spriteSheet3, j*64 , i*45, 64, 45);
        }
    }

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            arr4[i*2+j] = al_create_sub_bitmap(spriteSheet4, j*64 , i*64, 64, 64);
        }
    }

    for (int i=0; i<3; i++) {
        for (int j=0; j<2; j++) {
            arr5[i*2+j] = al_create_sub_bitmap(spriteSheet5, j*128 , i*128, 128, 128);
        }
    }

    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            arr6[i*5+j] = al_create_sub_bitmap(spriteSheet6, j*150 , i*150, 150, 150);
        }
    }

    for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
            arr7[i*3+j] = al_create_sub_bitmap(spriteSheet7, j*144 , i*144, 144, 144);
        }
    }

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            arr8[i*2+j] = al_create_sub_bitmap(spriteSheet8, j*128 , i*128, 128, 128);
        }
    }

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            arr9[i*4+j] = al_create_sub_bitmap(spriteSheet9, j*32 , i*32, 32, 32);
        }
    }
}

