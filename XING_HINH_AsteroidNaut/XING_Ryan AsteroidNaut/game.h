#define PINK        al_map_rgb(255, 0, 255)
#define BLACK       al_map_rgb(0, 0, 0)
#define SLATEGREY   al_map_rgb(112,128,144)
#define WHITE       al_map_rgb(255, 255, 255)
#define GREEN       al_map_rgb(66, 178, 1)
#define ANIMATIONSPEED 60

const float FPS = 60;			// set frame rate per second
const int SCREEN_W = 1000;       // screen width
const int SCREEN_H = 750;       // screen height

struct Coordinates {
    float dx;
    float dy;
    float posx;
    float posy;

    int x;
    int y;
};

struct Player {
    bool up;
    bool left;
    bool right;

    int jumps;
    bool direction;
    int health;
    int curr;

    Coordinates location;

};

struct Asteroids{

    bool astDirection;
    bool isCollision;

    float astPosx;
    float astPosy;
    float angle;
    float distance1;
    float distance2;

    int curr2;
    int astCurr;
    int explosionCurr;
    int tempX;
    int tempY;

    int side;

    int astRad;
    int astSpeed;

    int c;
    bool startDisplay;

};

struct Scoreboard{

    char name[10];
    int score;

};

//Basic game functions, intializing allegro, creating sprites, and closing the game
int checkSetup(ALLEGRO_DISPLAY *display, ALLEGRO_TIMER *timer, ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_FONT *font);
void closeGame(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *arr[], ALLEGRO_BITMAP *arr1[], ALLEGRO_BITMAP *arr2[], ALLEGRO_BITMAP *arr3[], ALLEGRO_BITMAP *arr4[], ALLEGRO_BITMAP *arr5[], ALLEGRO_BITMAP *arr6[], ALLEGRO_BITMAP *arr7[], ALLEGRO_BITMAP *arr8[], ALLEGRO_BITMAP *arr9[]);
int createSprites(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *arr[], ALLEGRO_BITMAP *arr1[], ALLEGRO_BITMAP *arr2[], ALLEGRO_BITMAP *arr3[], ALLEGRO_BITMAP *arr4[], ALLEGRO_BITMAP *arr5[], ALLEGRO_BITMAP *arr6[], ALLEGRO_BITMAP *arr7[], ALLEGRO_BITMAP *arr8[], ALLEGRO_BITMAP *arr9[]);

//Character functions
void createCharArr(Player p[], Scoreboard z[]);
void playerMovement(ALLEGRO_EVENT &ev, ALLEGRO_BITMAP *arr[], bool &gameStop, Player p[], int z);
int calcClosest(Player p[], Asteroids q[], int i, int gameMode);

//Platform functions
void platformPhysics(ALLEGRO_EVENT &ev, int x1, int y1, Player p[]);
void platformLocations(ALLEGRO_EVENT ev, Coordinates f[], Player p[], bool &intializePlatforms);
void drawPlatforms(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], Player p[], Coordinates f[]);

//Background functions
void background(ALLEGRO_EVENT &ev, ALLEGRO_BITMAP *arr[], int &curr1);


//Asteroid Functions
void declareAsteroidArr(Asteroids q[]);
void drawAsteroids(ALLEGRO_EVENT &ev, ALLEGRO_BITMAP *arr[], ALLEGRO_BITMAP *arr1[], Player p[], Asteroids q[], bool &gameStop, int gameMode);
void drawHearts(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], Player p[], int gameMode);

//User interface functions
int clicked(ALLEGRO_EVENT ev, int mouseX1, int mouseY1, int mouseX2, int mouseY2);
void interface(ALLEGRO_EVENT ev);
void playButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int &curr4);
void hiscoreButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int &curr4);
void helpButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int &curr4);
void drawTitle(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int &curr3);
void mainMenu(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], ALLEGRO_BITMAP *arr1[], int &curr4);
void instructions(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *png, ALLEGRO_FONT *font);
void oneplayerButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int curr4);
void twoplayerButton(ALLEGRO_EVENT ev, ALLEGRO_BITMAP *arr[], int &curr4);
void hiScores(ALLEGRO_EVENT ev, ALLEGRO_FONT *font, Scoreboard p[]);
void printScore(ALLEGRO_EVENT ev, ALLEGRO_FONT *font, Scoreboard p[], Player z[], int gameMode);

// File Functions
int sizeOfFile(FILE *fptr);
void sortFile(Scoreboard p[], FILE *fptr, int a);
void writeFile(Scoreboard p[], FILE *fptr, int a);
