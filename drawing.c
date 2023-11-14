#include "graphics.c"
#include "stdlib.h"
#include "movement.c"
#include "time.h"

#define WINDOWSIZE 500

void drawBackground(int rowsize, int columnsize){
  background(); // Must draw on the background layer to not be erased by clear().
  setColour(black);
  for (int i = 0; i <rowsize; i++){
    for (int x = 0; x< columnsize; x++){ 
            drawRect((WINDOWSIZE/rowsize)*x, (WINDOWSIZE/columnsize)*i, (WINDOWSIZE/rowsize), (WINDOWSIZE/columnsize));        
        
        }
    }
}

void drawTarget(int x, int y, int rowsize, int columnsize){
    setColour(blue);
    fillArc(((WINDOWSIZE/rowsize) * x) + 5, ((WINDOWSIZE/columnsize) * y) + 5, (WINDOWSIZE/rowsize) - 10, (WINDOWSIZE/columnsize) - 10, 0 ,360);
}


void drawObstacle(int x, int y, int rowsize, int columnsize){
    setColour(cyan);
    fillRect(((WINDOWSIZE/rowsize) * x) + 5, ((WINDOWSIZE/columnsize) * y) + 5, (WINDOWSIZE/rowsize) - 10, (WINDOWSIZE/columnsize) - 10);
}


int atMarker(struct robot *myrobot, struct target *targets, int numoftargets){ //
    for (size_t i = 0; i < numoftargets; i++)
    {
        if ((myrobot->currentX == targets[i].currentX) && (myrobot->currentY == targets[i].currentY) && (targets[i].ishome == 0))
        {
            targets[i].ishome = 1;
            return 1;
        }  
    }
    return 0;
}

//DrawRobot functions (:
void drawRobotBody(int x, int y, int rowsize, int columnsize) {
    setColour(black);
    drawRect(((WINDOWSIZE/rowsize) * x) + 5, ((WINDOWSIZE/columnsize) * y) + 5, (WINDOWSIZE/rowsize) - 10, (WINDOWSIZE/columnsize) - 10);
    fillRect(((WINDOWSIZE/rowsize) * x) + 5, ((WINDOWSIZE/columnsize) * y) + 10, (WINDOWSIZE/rowsize) - 35, (WINDOWSIZE/columnsize) - 30);
    fillRect(((WINDOWSIZE/rowsize) * x) + 25, ((WINDOWSIZE/columnsize) * y) + 10, (WINDOWSIZE/rowsize) - 35, (WINDOWSIZE/columnsize) - 30);
    setColour(cyan);
    fillRect(((WINDOWSIZE/rowsize) * x) + 25, ((WINDOWSIZE/columnsize) * y) + 30, (WINDOWSIZE/rowsize) - 40, (WINDOWSIZE/columnsize) - 40);
}

//same calculations for a triangle but rotated for each!
void drawNorthTriangle(int x, int y, int rowsize, int columnsize, int *xs, int *ys) {
    xs[0] = ((WINDOWSIZE/rowsize) * x) + (WINDOWSIZE/rowsize)/2; 
    ys[0] = ((WINDOWSIZE/columnsize) * y);
    xs[1] = ((WINDOWSIZE/rowsize) * x) + (WINDOWSIZE/rowsize)/3;
    ys[1] = ((WINDOWSIZE/columnsize) * y) + (WINDOWSIZE/columnsize)/3;
    xs[2] = ((WINDOWSIZE/rowsize) * x) + 2*(WINDOWSIZE/rowsize)/3;
    ys[2] = ((WINDOWSIZE/columnsize) * y) + (WINDOWSIZE/columnsize)/3;
    fillPolygon(3, xs, ys);
}

void drawEastTriangle(int x, int y, int rowsize, int columnsize, int *xs, int *ys) {
    xs[0] = ((WINDOWSIZE/rowsize) * x) + (WINDOWSIZE/rowsize);
    ys[0] = ((WINDOWSIZE/columnsize) * y) + (WINDOWSIZE/columnsize)/2;
    xs[1] = ((WINDOWSIZE/rowsize) * x) + 2*(WINDOWSIZE/rowsize)/3;
    ys[1] = ((WINDOWSIZE/columnsize) * y) + (WINDOWSIZE/columnsize)/3;
    xs[2] = ((WINDOWSIZE/rowsize) * x) + 2*(WINDOWSIZE/rowsize)/3;
    ys[2] = ((WINDOWSIZE/columnsize) * y) + 2*(WINDOWSIZE/columnsize)/3;
    fillPolygon(3, xs, ys);
}

void drawSouthTriangle(int x, int y, int rowsize, int columnsize, int *xs, int *ys) {
    xs[0] = ((WINDOWSIZE/rowsize) * x) + (WINDOWSIZE/rowsize)/2;
    ys[0] = ((WINDOWSIZE/columnsize) * y) + (WINDOWSIZE/columnsize);
    xs[1] = ((WINDOWSIZE/rowsize) * x) + (WINDOWSIZE/rowsize)/3;
    ys[1] = ((WINDOWSIZE/columnsize) * y) + 2*(WINDOWSIZE/columnsize)/3;
    xs[2] = ((WINDOWSIZE/rowsize) * x) + 2*(WINDOWSIZE/rowsize)/3;
    ys[2] = ((WINDOWSIZE/columnsize) * y) + 2*(WINDOWSIZE/columnsize)/3;
    fillPolygon(3, xs, ys);
}

void drawWestTriangle(int x, int y, int rowsize, int columnsize, int *xs, int *ys) {
    xs[0] = ((WINDOWSIZE/rowsize) * x);
    ys[0] = ((WINDOWSIZE/columnsize) * y) + (WINDOWSIZE/columnsize)/2;
    xs[1] = ((WINDOWSIZE/rowsize) * x) + (WINDOWSIZE/rowsize)/3;
    ys[1] = ((WINDOWSIZE/columnsize) * y) + (WINDOWSIZE/columnsize)/3;
    xs[2] = ((WINDOWSIZE/rowsize) * x) + (WINDOWSIZE/rowsize)/3;
    ys[2] = ((WINDOWSIZE/columnsize) * y) + 2*(WINDOWSIZE/columnsize)/3;
    fillPolygon(3, xs, ys);
}

void drawRobotDirection(struct robot *myrobot, int x, int y, int rowsize, int columnsize) {
    int xs[3], ys[3]; //Arrays to store the x and y coordinates of the triangle
    setColour(red);
    switch(myrobot->direction[0]) {
        case 'n': 
            drawNorthTriangle(x, y, rowsize, columnsize, xs, ys); break;
        case 'e': 
            drawEastTriangle(x, y, rowsize, columnsize, xs, ys); break;
        case 's': 
            drawSouthTriangle(x, y, rowsize, columnsize, xs, ys); break;
        case 'w': 
            drawWestTriangle(x, y, rowsize, columnsize, xs, ys); break;
    }
}

void drawMarker(struct robot *myrobot, int x, int y, int rowsize, int columnsize) {
    if (isCarryingAMarker(myrobot) == 1){
        setColour(blue);
        fillArc(((WINDOWSIZE/rowsize) * x) + 5, ((WINDOWSIZE/columnsize) * y) + 5, (WINDOWSIZE/rowsize) - 10, (WINDOWSIZE/columnsize) - 10, 0 ,360);
    }
}

void drawHome(int homeX, int homeY, int rowsize, int columnsize){
    setColour(red);
    drawRect(((WINDOWSIZE/rowsize) * (homeX)) + 5, ((WINDOWSIZE/columnsize) * (homeY)) + 5, (WINDOWSIZE/rowsize) - 10, (WINDOWSIZE/columnsize) - 10);
}

void drawRobot(struct robot *myrobot, int rowsize, int columnsize) {
    int x = myrobot->currentX;
    int y = myrobot->currentY;
    drawRobotBody(x, y, rowsize, columnsize);
    drawRobotDirection(myrobot, x, y, rowsize, columnsize);
    drawMarker(myrobot, x, y, rowsize, columnsize);
}
// drawRobot section finished


int isPositionOccupied(int x, int y, struct target *targets, int numoftargets, struct obstacle *obstacles, int numofobstacles, int homeX, int homeY) {
    //cheking if the position is occupied by a target obstacle or home
    if (x == homeX && y == homeY) {
        return 1;
    }
    for (size_t i = 0; i < numofobstacles; i++) {
        if (obstacles[i].X == x && obstacles[i].Y == y) {
            return 1;
        }
    }
    for (size_t i = 0; i < numoftargets; i++) {
        if (targets[i].currentX == x && targets[i].currentY == y) {
            return 1;
        }
    }
    return 0;
}

void initialiseTargets(int numoftargets, struct target *targets, int numofobstacles, struct obstacle *obstacles, int rowsize, int columnsize, int homeX, int homeY){
    for (size_t i = 0; i < numoftargets; i++)
    {  
        do {
            targets[i].currentX = rand() % rowsize; 
            targets[i].currentY = rand() % columnsize;
        } while (isPositionOccupied(targets[i].currentX,targets[i].currentY, targets, i, obstacles, numofobstacles, homeX, homeY));
        targets[i].ishome = 0;
    }
}


void initialiseObstacles(int numofobstacles, struct obstacle *obstacles, int rowsize, int columnsize, int homeX, int homeY){
    for (size_t i = 0; i < numofobstacles; i++)
    {   do {
            obstacles[i].X = rand() % rowsize;
            obstacles[i].Y = rand() % columnsize;
        } while (isPositionOccupied(obstacles[i].X, obstacles[i].Y, NULL, 0, obstacles, i, homeX, homeY)); //no need to check for targets as they deal with obstacles
        drawObstacle(obstacles[i].X, obstacles[i].Y, rowsize, columnsize);
    }
}


void drawAllTargets(struct target *targets, int numoftargets, int rowsize, int columnsize){
    for (size_t i = 0; i < numoftargets; i++)
        {
            if (targets[i].ishome == 0)
            {
                drawTarget(targets[i].currentX, targets[i].currentY, rowsize, columnsize);
            }
        }
}
void drawAllObstacles(struct obstacle *obstacles, int numofobstacles, int rowsize, int columnsize){
    for (size_t i = 0; i < numofobstacles; i++)
        {
            drawObstacle(obstacles[i].X, obstacles[i].Y, rowsize, columnsize);
        }
}


void move(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles, char movements[], int *movecounter, int rowsize, int columnsize) {
    int direction = rand() % 10; //Favoring going forward from trial and error found 80% forward to be the best
    if (direction < 8 && canMoveForward(myrobot, obstacles, numofobstacles, rowsize, columnsize)) {
        forward(myrobot, movements, *movecounter);
        (*movecounter)++;
    } else if (direction == 8 && canTurnLeft(myrobot, obstacles, numofobstacles, rowsize, columnsize)) {
        left(myrobot);
        if (canMoveForward(myrobot, obstacles, numofobstacles, rowsize, columnsize)) {
            forward(myrobot, movements, *movecounter);
            (*movecounter)++;
        }
    } else if (direction == 9) {
        right(myrobot);
        if (canMoveForward(myrobot, obstacles, numofobstacles, rowsize, columnsize)) {
            forward(myrobot, movements, *movecounter);
            (*movecounter)++;
        }
    }
}

void initialiseRobot(struct robot *myrobot, int initialX, int initialY, char *direction) {
    myrobot->currentX = initialX;
    myrobot->currentY = initialY;
    myrobot->direction = direction;
}

void initialiseGameElements(int numoftargets, struct target *targets, int numofobstacles, struct obstacle *obstacles, int rowsize, int columnsize, int initialX, int initialY) {
    setWindowSize(WINDOWSIZE,WINDOWSIZE);
    initialiseObstacles(numofobstacles, obstacles, rowsize, columnsize, initialX, initialY);
    initialiseTargets(numoftargets, targets, numofobstacles, obstacles, rowsize, columnsize, initialX, initialY);
}

void drawGame(int rowsize, int columnsize, struct target *targets, int numoftargets, struct obstacle *obstacles, int numofobstacles, struct robot *myrobot, int homeX, int homeY) {
    foreground();
    drawHome(homeX, homeY, rowsize, columnsize);
    drawAllTargets(targets, numoftargets, rowsize, columnsize);
    drawAllObstacles(obstacles, numofobstacles, rowsize, columnsize);
    drawRobot(myrobot, rowsize, columnsize);
}

void handleMarker(int *targetmarker, struct robot *myrobot, struct target *targets, int rowsize, int columnsize, int *movecounter, char *movements, int initialX, int initialY, int numoftargets, struct obstacle *obstacles, int numofobstacles) {
    foreground();
    setColour(white);
    fillRect(((WINDOWSIZE/rowsize) * myrobot->currentX) + 5, ((WINDOWSIZE/columnsize) * myrobot->currentY) + 5, (WINDOWSIZE/rowsize) - 10, (WINDOWSIZE/columnsize) - 10);
    (*targetmarker)++;
    pickUpMarker(myrobot);
    reverseToHome(*movecounter, movements, myrobot, initialY, initialX, rowsize, columnsize, targets, numoftargets, obstacles, numofobstacles);
    *movecounter = 0; //Reset the number of moves
    drawTarget(myrobot->currentX, myrobot->currentY, rowsize, columnsize);
    dropMarker(myrobot);
}

void validateArguments(int initialX, int initialY, char *direction, int rowsize, int columnsize, int numoftargets, int numofobstacles){
    if (initialX < 0 || initialX > rowsize - 1) {  //My coordinate system is 0 indexed in the code but abstracted from the user (:
        printf("Initial X value is out of bounds\n");
        exit(1);
    }
    if (initialY < 0 || initialY > columnsize - 1) {
        printf("Initial Y value is out of bounds\n");
        exit(1);
    }
    if (strcmp(direction, "north") != 0 && strcmp(direction, "east") != 0 && strcmp(direction, "south") != 0 && strcmp(direction, "west") != 0) { 
        printf("Direction is invalid\n");
        exit(1);
    }
}

void initialise(char **argv, int *initialX, int *initialY, char **direction, int *rowsize, int *columnsize, int *numoftargets, int *numofobstacles) {
    *initialX = atoi(argv[1]) - 1;
    *initialY = atoi(argv[2]) - 1;
    *direction = argv[3]; 
    *rowsize = atoi(argv[4]);
    *columnsize = atoi(argv[5]);
    *numoftargets = atoi(argv[6]);
    *numofobstacles = atoi(argv[7]);
    validateArguments(*initialX, *initialY, *direction, *rowsize, *columnsize, *numoftargets, *numofobstacles);
}

void gameLoop(struct robot *myrobot, struct target *targets, struct obstacle *obstacles, int numoftargets, int numofobstacles, int rowsize, int columnsize, int initialX, int initialY, char *movements, int *movecounter, int *targetmarker) {
    drawBackground(rowsize, columnsize);
    while (*targetmarker != numoftargets) 
    {   
        do
        {   
            move(myrobot, obstacles, numofobstacles, movements, movecounter, rowsize, columnsize);
            drawGame(rowsize, columnsize, targets, numoftargets, obstacles, numofobstacles, myrobot, initialX, initialY);
            sleep(100);
            clear();
            
        }
        while (atMarker(myrobot, targets, numoftargets) == 0);
        handleMarker(targetmarker, myrobot, targets, rowsize, columnsize, movecounter, movements, initialX, initialY, numoftargets, obstacles, numofobstacles);
    }
}

int main(int argc, char **argv){
    time_t t;
    srand((unsigned int) time(&t)); 
    char* movements = malloc(1000 * sizeof(char));
    if (movements == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }
    char* direction = "north"; //Default values if no arguments are given
    int movecounter = 0;
    int rowsize = 10;
    int columnsize = 10;
    int initialX = rand() % 10;
    int initialY = rand() % 10;
    int targetmarker = 0;
    int numoftargets = rand() % 10 + 1;
    int numofobstacles = rand() % 10 + 1;
    struct robot myrobot;
    if (argc == 8) 
    {
        initialise(argv, &initialX, &initialY, &direction, &rowsize, &columnsize, &numoftargets, &numofobstacles);
    }
    struct target targets[numoftargets];
    struct obstacle obstacles[numofobstacles];
    initialiseRobot(&myrobot, initialX, initialY, direction);
    initialiseGameElements(numoftargets, targets, numofobstacles, obstacles, rowsize, columnsize, initialX, initialY);
    gameLoop(&myrobot, targets, obstacles, numoftargets, numofobstacles, rowsize, columnsize, initialX, initialY, movements, &movecounter, &targetmarker);
    free(movements);
    drawGame(rowsize, columnsize, targets, numoftargets, obstacles, numofobstacles, &myrobot, initialX, initialY);
    printf("All targets have been found!\n");
}