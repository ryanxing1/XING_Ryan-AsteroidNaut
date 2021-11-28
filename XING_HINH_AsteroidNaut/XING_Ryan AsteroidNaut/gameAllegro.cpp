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


//Checks if all allegro addons are correctly initialized
int checkSetup(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font){

	if (!display) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}

	if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize primatives addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the keyboard!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	return -1;
   	}

 	if (!al_install_mouse()) {
	    al_show_native_message_box(display, "Error", "Error", "failed to initialize the mouse!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      	return -1;
   	}

 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error", "Failed to initialize image addon!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}

	if (!font){
      al_show_native_message_box(display, "Error", "Error", "Could not load comic.ttf",
                                    nullptr, ALLEGRO_MESSAGEBOX_ERROR);
      return -1;
    }

    if (!timer) {
   		al_show_native_message_box(display, "Error", "Error", "Failed to create timer!",
                                nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create event_queue!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}

   return 0;
}

//Closes the game and destroys display and bitmaps
void closeGame(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *arr[], ALLEGRO_BITMAP *arr1[], ALLEGRO_BITMAP *arr2[], ALLEGRO_BITMAP *arr3[], ALLEGRO_BITMAP *arr4[], ALLEGRO_BITMAP *arr5[], ALLEGRO_BITMAP *arr6[], ALLEGRO_BITMAP *arr7[], ALLEGRO_BITMAP *arr8[], ALLEGRO_BITMAP *arr9[]){
    al_destroy_display(display);
    for(int i=0; i<16; i++){
        al_destroy_bitmap(arr[i]);
    }
    for(int i=0; i<16; i++){
        al_destroy_bitmap(arr1[i]);
    }
    for(int i=0; i<4; i++){
        al_destroy_bitmap(arr2[i]);
    }
    for(int i=0; i<4; i++){
        al_destroy_bitmap(arr3[i]);
    }
    for(int i=0; i<4; i++){
        al_destroy_bitmap(arr4[i]);
    }
    for(int i=0; i<6; i++){
        al_destroy_bitmap(arr5[i]);
    }
    for(int i=0; i<24; i++){
        al_destroy_bitmap(arr6[i]);
    }
    for(int i=0; i<12; i++){
        al_destroy_bitmap(arr7[i]);
    }
    for(int i=0; i<4; i++){
        al_destroy_bitmap(arr8[i]);
    }
    for(int i=0; i<16; i++){
        al_destroy_bitmap(arr9[i]);
    }
    printf("destroyed");
}
