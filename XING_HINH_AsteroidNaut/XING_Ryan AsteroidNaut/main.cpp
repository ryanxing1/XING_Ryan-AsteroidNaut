 /*****************************************************************************
 *	Name:     Ryan Xing, Brenden Hinh, Nico Wada                             *
 *	Date:     2/14/2021                                                      *
 *                                                                           *
 *	                                                                         *
 *	Usage: Use help screen to learn how the game works. Press buttons to     *
    navigate the UI                                                          *
 *	                                                                         *
 *	                                                                         *
 *	Known Issues:                                                            *
 *	                                                                         *
 *****************************************************************************/

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


int main(int argc, char *argv[]) {

    //Initializes Allegro and necessary add ons
    al_init();

    ALLEGRO_DISPLAY *display = nullptr;
    display = al_create_display(SCREEN_W, SCREEN_H);

	ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
	event_queue = al_create_event_queue();

	ALLEGRO_TIMER *timer = nullptr;
	timer = al_create_timer(1.0 / FPS);

	al_init_font_addon();
    al_init_ttf_addon();

    ALLEGRO_FONT *font = al_load_ttf_font("8-BIT WONDER.TTF", 14, 0);
    ALLEGRO_FONT *font2 = al_load_ttf_font("Stencil 8bit.ttf", 40, 0);

    FILE *fptr;

    //Checks if Allegro was set up correctly
    checkSetup(display, timer, event_queue, font);

    //Registers events for event queue
    al_register_event_source(event_queue, al_get_display_event_source(display));
 	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_mouse_event_source());

    //Initializes all Bitmap arrays
    ALLEGRO_BITMAP *charFrame[16];
    ALLEGRO_BITMAP *charFrame1[16];
    ALLEGRO_BITMAP *backFrame[4];
    ALLEGRO_BITMAP *platFrame[4];
    ALLEGRO_BITMAP *astFrame[4];
    ALLEGRO_BITMAP *explosionFrame[6];
    ALLEGRO_BITMAP *menuFrame[24];
    ALLEGRO_BITMAP *playerExitFrame[16];
    ALLEGRO_BITMAP *helpScreen;
    ALLEGRO_BITMAP *titleFrame[4];
    ALLEGRO_BITMAP *heartFrame[16];
    ALLEGRO_BITMAP *gameOver;
    helpScreen = al_load_bitmap("Help Screen.png");
    gameOver = al_load_bitmap("Game Over.png");

    createSprites(display, charFrame, charFrame1, backFrame, platFrame, astFrame, explosionFrame, menuFrame, playerExitFrame, titleFrame, heartFrame);

    //Initialization of Structures
    Coordinates platGen[5];
    Player characters[2];
    Asteroids asteroidsArr[3];
    Scoreboard players[2];

    //Assortment of currs used for animating main menu
    int curr1 = 0;
    int curr2 = 0;
    int curr3 = 0;

    srand(time(0));

    //Boolean values used to direct the series of events in the game
    bool gameStop;
    bool playerOneStop;
    bool playerTwoStop;
    bool stopMain = false;

    //Bool used to create randomized platforms just once
    bool intializePlatforms = false;

    al_start_timer(timer);

    while (!stopMain){

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        gameStop = false;
        playerOneStop = false;
        playerTwoStop = false;
        int gameMode;

        //Declares Character and Asteroid structures
        createCharArr(characters, players);
        declareAsteroidArr(asteroidsArr);

        //Draws main menu
        background(ev, backFrame, curr1);
        mainMenu(ev, menuFrame, playerExitFrame, curr2);
        drawTitle(ev, titleFrame, curr3);
        al_flip_display();

        if (clicked(ev, 410,350,610,420)== 1){
            //Code for player one and player two options
            while(!gameStop){
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev);
                background(ev, backFrame, curr1);

                oneplayerButton(ev, playerExitFrame, curr3);
                twoplayerButton(ev, menuFrame, curr3);

                al_draw_text(font2, WHITE, 0, 710, 0, "BACK");
                if (clicked(ev, 0,720,75,750) == 1){
                    gameStop = true;
                }
                al_flip_display();

                if (clicked(ev, 180,325,460,400) == 1){
                    //Code for single player game mode
                    gameMode = 0;
                    while (!playerOneStop){
                        ALLEGRO_EVENT ev;
                        al_wait_for_event(event_queue, &ev);

                        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                            playerOneStop = true;
                            gameStop = true;

                        }

                        background(ev, backFrame, curr1);
                        drawPlatforms(ev, platFrame, characters, platGen);
                        drawHearts(ev, heartFrame, characters, gameMode);

                        if(characters[0].health > 0){
                                playerMovement(ev, charFrame, gameStop, characters, 0);
                        }
                        if(characters[0].health <= 0){
                            //Game over screen with option to save scores
                            al_clear_to_color(BLACK);
                            al_draw_scaled_bitmap(gameOver, 0, 0, al_get_bitmap_width(gameOver), al_get_bitmap_height(gameOver), 250, 100, 500, 500, 0);
                            al_draw_textf(font, WHITE, 500, 470, ALLEGRO_ALIGN_CENTER, "Enter 4 Letter Usernames in the console to save score");
                            al_draw_textf(font, WHITE, 500, 500, ALLEGRO_ALIGN_CENTER, "Player 1 Score %d", players[0].score);
                            al_flip_display();

                            fptr = fopen("Scoreboard.txt", "a");
                            printf("Enter Username for Player 1:\n");
                            scanf("%s", players[0].name);
                            if(fptr){
                                fprintf(fptr, "%s %d\n", players[0].name, players[0].score);
                            }
                            fclose(fptr);
                            playerOneStop = true;
                            gameStop = true;

                        }

                        platformLocations(ev, platGen, characters, intializePlatforms);
                        drawAsteroids(ev, astFrame, explosionFrame, characters, asteroidsArr, gameStop, gameMode);
                        printScore(ev, font, players, characters, gameMode);
                        al_flip_display();

                    }
                }

                if (clicked(ev, 570,325,845,400) == 1){
                    //Code for two player game mode
                    gameMode = 1;
                    while (!playerTwoStop) {

                        ALLEGRO_EVENT ev;
                        al_wait_for_event(event_queue, &ev);

                        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                            playerTwoStop = true;
                            gameStop = true;

                        }

                        background(ev, backFrame, curr1);
                        drawPlatforms(ev, platFrame, characters, platGen);
                        drawHearts(ev, heartFrame, characters, gameMode);

                        if(characters[0].health > 0){
                            playerMovement(ev, charFrame, gameStop, characters, 0);
                        }
                        if(characters[1].health > 0){
                            playerMovement(ev, charFrame1, gameStop, characters, 1);

                        }

                        if (characters[0].health <= 0 && characters[1].health <= 0){
                            //Game over screen with option to save scores
                            al_clear_to_color(BLACK);
                            al_draw_scaled_bitmap(gameOver, 0, 0, al_get_bitmap_width(gameOver), al_get_bitmap_height(gameOver), 250, 100, 500, 500, 0);
                            al_draw_textf(font, WHITE, 500, 470, ALLEGRO_ALIGN_CENTER, "Enter 4 Letter Usernames in the console to save score");

                            al_draw_textf(font, WHITE, 300, 500, ALLEGRO_ALIGN_CENTER, "Player 1 Score %d", players[0].score);
                            al_draw_textf(font, WHITE, 700, 500, ALLEGRO_ALIGN_CENTER, "Player 2 Score %d", players[1].score);


                            al_flip_display();

                            fptr = fopen("Scoreboard.txt", "a");
                            printf("Enter Username for Player 1:\n");
                            scanf("%s", players[0].name);
                            if(fptr){
                                fprintf(fptr, "%s %d\n", players[0].name, players[0].score);
                            }
                            printf("Enter Username for Player 2:\n");
                            scanf("%s", players[1].name);
                            if(fptr){
                                fprintf(fptr, "%s %d\n", players[1].name, players[1].score);
                            }

                            fclose(fptr);
                            playerTwoStop = true;
                            gameStop = true;

                        }

                        platformLocations(ev, platGen, characters, intializePlatforms);
                        drawAsteroids(ev, astFrame, explosionFrame, characters, asteroidsArr, gameStop, gameMode);
                        printScore(ev, font, players, characters, gameMode);
                        al_flip_display();

                    }

                }

            }

        }

        //Exit button
        else if (clicked(ev, 400, 590, 620, 650) == 1){
            break;
        }

        //Code that sorts text file and outputs highscore table
        else if (clicked(ev, 370,430,650,495) == 1){
            int fileSize = sizeOfFile(fptr);
            printf("%d", fileSize);
            Scoreboard users[fileSize];

            sortFile(users, fptr, fileSize);
            writeFile(users, fptr, fileSize);

            ALLEGRO_FONT *font = al_load_ttf_font("8-BIT WONDER.TTF", 30, 0);

            while(1){
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev);

                background(ev, backFrame, curr1);
                hiScores(ev, font, users);
                al_draw_text(font2, WHITE, 0, 710, 0, "BACK");

                al_flip_display();
                if (clicked(ev, 0,720,75,750) == 1){
                    break;
                }
            }


        }

        //Displays help screen
        else if (clicked(ev, 410,505,610,570) == 1){
            while(1){
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev);

                background(ev, backFrame, curr1);
                instructions(ev, helpScreen, font);

                al_draw_text(font2, WHITE, 0, 710, 0, "BACK");

                al_flip_display();
                if (clicked(ev, 0,720,75,750) == 1){
                    break;
                }
            }
        }

    }

    //Destroys screen and all bitmaps used to close the game
    closeGame(display, charFrame, charFrame1, backFrame, platFrame, astFrame, explosionFrame, menuFrame, playerExitFrame, titleFrame, heartFrame);

	return 0;
}
