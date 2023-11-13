#include "graphics.c"
#include "stdlib.h"
#include "movement.c"
#include "time.h"

#define WINDOWSIZE 500

void drawBackground(int rowSize, int columnSize){
  background(); // Must draw on the background layer to not be erased by clear().
  setColour(black);
  for (int i = 0; i <rowSize; i++){
    for (int x = 0; x< columnSize; x++){ 
            drawRect((WINDOWSIZE/columnSize)*x, (WINDOWSIZE/rowSize)*i, (WINDOWSIZE/columnSize), (WINDOWSIZE/rowSize));        
        }
    }
}

void drawTarget(int x, int y, int rowSize, int columnSize){
    setColour(blue);
    fillArc(((WINDOWSIZE/rowSize) * x) + 5, ((WINDOWSIZE/columnSize) * y) + 5, (WINDOWSIZE/rowSize) - 10, (WINDOWSIZE/columnSize) - 10, 0 ,360);
}


void drawObstacle(int x, int y, int rowSize, int columnSize){
    background();
    setColour(cyan);
    fillArc(((WINDOWSIZE/rowSize) * x) + 5, ((WINDOWSIZE/columnSize) * y) + 5, (WINDOWSIZE/rowSize) - 10, (WINDOWSIZE/columnSize) - 10, 0 ,360);
}


int atMarker(struct robot *myrobot, struct target *targets, int numoftargets){ //
    for (size_t i = 0; i < numoftargets; i++)
    {
        if ((myrobot->currentX == targets[i].currentX) && (myrobot->currentY == targets[i].currentY) && (targets[i].isHome == 0))
        {
            targets[i].isHome = 1;
            return 1;
        }  
    }
    return 0;
}

//DrawRobot functions (:
void drawRobotBody(int x, int y, int rowSize, int columnSize) {
    setColour(black);
    drawRect(((WINDOWSIZE/rowSize) * x) + 5, ((WINDOWSIZE/columnSize) * y) + 5, (WINDOWSIZE/rowSize) - 10, (WINDOWSIZE/columnSize) - 10);
    fillRect(((WINDOWSIZE/rowSize) * x) + 5, ((WINDOWSIZE/columnSize) * y) + 10, (WINDOWSIZE/rowSize) - 35, (WINDOWSIZE/columnSize) - 30);
    fillRect(((WINDOWSIZE/rowSize) * x) + 25, ((WINDOWSIZE/columnSize) * y) + 10, (WINDOWSIZE/rowSize) - 35, (WINDOWSIZE/columnSize) - 30);
    setColour(cyan);
    fillRect(((WINDOWSIZE/rowSize) * x) + 25, ((WINDOWSIZE/columnSize) * y) + 30, (WINDOWSIZE/rowSize) - 40, (WINDOWSIZE/columnSize) - 40);
}


void drawNorth(int x, int y, int rowSize, int columnSize, int *xs, int *ys) {
    xs[0] = ((WINDOWSIZE/rowSize) * x) + (WINDOWSIZE/rowSize)/2; 
    ys[0] = ((WINDOWSIZE/columnSize) * y);
    xs[1] = ((WINDOWSIZE/rowSize) * x) + (WINDOWSIZE/rowSize)/3;
    ys[1] = ((WINDOWSIZE/columnSize) * y) + (WINDOWSIZE/columnSize)/3;
    xs[2] = ((WINDOWSIZE/rowSize) * x) + 2*(WINDOWSIZE/rowSize)/3;
    ys[2] = ((WINDOWSIZE/columnSize) * y) + (WINDOWSIZE/columnSize)/3;
    fillPolygon(3, xs, ys);
}

void drawEast(int x, int y, int rowSize, int columnSize, int *xs, int *ys) {
    xs[0] = ((WINDOWSIZE/rowSize) * x) + (WINDOWSIZE/rowSize);
    ys[0] = ((WINDOWSIZE/columnSize) * y) + (WINDOWSIZE/columnSize)/2;
    xs[1] = ((WINDOWSIZE/rowSize) * x) + 2*(WINDOWSIZE/rowSize)/3;
    ys[1] = ((WINDOWSIZE/columnSize) * y) + (WINDOWSIZE/columnSize)/3;
    xs[2] = ((WINDOWSIZE/rowSize) * x) + 2*(WINDOWSIZE/rowSize)/3;
    ys[2] = ((WINDOWSIZE/columnSize) * y) + 2*(WINDOWSIZE/columnSize)/3;
    fillPolygon(3, xs, ys);
}

void drawSouth(int x, int y, int rowSize, int columnSize, int *xs, int *ys) {
    xs[0] = ((WINDOWSIZE/rowSize) * x) + (WINDOWSIZE/rowSize)/2;
    ys[0] = ((WINDOWSIZE/columnSize) * y) + (WINDOWSIZE/columnSize);
    xs[1] = ((WINDOWSIZE/rowSize) * x) + (WINDOWSIZE/rowSize)/3;
    ys[1] = ((WINDOWSIZE/columnSize) * y) + 2*(WINDOWSIZE/columnSize)/3;
    xs[2] = ((WINDOWSIZE/rowSize) * x) + 2*(WINDOWSIZE/rowSize)/3;
    ys[2] = ((WINDOWSIZE/columnSize) * y) + 2*(WINDOWSIZE/columnSize)/3;
    fillPolygon(3, xs, ys);
}

void drawWest(int x, int y, int rowSize, int columnSize, int *xs, int *ys) {
    xs[0] = ((WINDOWSIZE/rowSize) * x);
    ys[0] = ((WINDOWSIZE/columnSize) * y) + (WINDOWSIZE/columnSize)/2;
    xs[1] = ((WINDOWSIZE/rowSize) * x) + (WINDOWSIZE/rowSize)/3;
    ys[1] = ((WINDOWSIZE/columnSize) * y) + (WINDOWSIZE/columnSize)/3;
    xs[2] = ((WINDOWSIZE/rowSize) * x) + (WINDOWSIZE/rowSize)/3;
    ys[2] = ((WINDOWSIZE/columnSize) * y) + 2*(WINDOWSIZE/columnSize)/3;
    fillPolygon(3, xs, ys);
}

void drawRobotDirection(struct robot *myrobot, int x, int y, int rowSize, int columnSize) {
    int xs[3], ys[3];
    setColour(red);
    switch(myrobot->direction[0]) {
        case 'n': // North
            drawNorth(x, y, rowSize, columnSize, xs, ys); break;
        case 'e': // East
            drawEast(x, y, rowSize, columnSize, xs, ys); break;
        case 's': // South
            drawSouth(x, y, rowSize, columnSize, xs, ys); break;
        case 'w': // West
            drawWest(x, y, rowSize, columnSize, xs, ys); break;
    }
}

void drawMarker(struct robot *myrobot, int x, int y, int rowSize, int columnSize) {
    if (isCarryingAMarker(myrobot) == 1){
        setColour(blue);
        fillArc(((WINDOWSIZE/rowSize) * x) + 5, ((WINDOWSIZE/columnSize) * y) + 5, (WINDOWSIZE/rowSize) - 10, (WINDOWSIZE/columnSize) - 10, 0 ,360);
    }
}

void drawHome(int homeX, int homeY, int rowSize, int columnSize){
    homeY++; 
    setColour(red);
    drawRect(((WINDOWSIZE/rowSize) * (homeX)) + 5, ((WINDOWSIZE/columnSize) * (homeY - 1)) + 5, (WINDOWSIZE/rowSize) - 10, (WINDOWSIZE/columnSize) - 10);
}

void drawRobot(struct robot *myrobot, int rowSize, int columnSize) {
    int x = myrobot->currentX;
    int y = myrobot->currentY;
    drawRobotBody(x, y, rowSize, columnSize);
    drawRobotDirection(myrobot, x, y, rowSize, columnSize);
    drawMarker(myrobot, x, y, rowSize, columnSize);
    sleep(50);
    clear();
}
// drawRobot section finished

void intiialiseTargets(int numoftargets, struct target *targets, int numofobstacles, struct obstacle *obstacles, int rowSize, int columnSize, int homeX, int homeY){
    for (size_t i = 0; i < numoftargets; i++)
    {   targets[i].currentX = rand() % rowSize; 
        targets[i].currentY = rand() % columnSize;
        for (size_t x = 0; x < numofobstacles; x++)
        {
            while ((obstacles[x].X == targets[i].currentX && obstacles[x].Y == targets[i].currentY) || (targets[i].currentX == homeX && targets[i].currentY == homeY)) 
            //checking if target is on top of an obstacle or on top of the home position
            {
                targets[i].currentX = rand() % rowSize; 
                targets[i].currentY = rand() % columnSize;
            }
        }
        targets[i].isHome = 0;
    }
}

void initialiseObstacles(int numofobstacles, struct obstacle *obstacles, int rowSize, int columnSize, int homeX, int homeY){
    for (size_t i = 0; i < numofobstacles; i++)
    {   
        obstacles[i].X = rand() % rowSize;
        obstacles[i].Y = rand() % columnSize;
        while (obstacles[i].X == homeX && obstacles[i].Y == homeY)
        {
            obstacles[i].X = rand() % rowSize;
            obstacles[i].Y = rand() % columnSize;
        } 
        drawObstacle(obstacles[i].X, obstacles[i].Y, rowSize, columnSize);
    }
}


void drawAllTargets(struct target *targets, int numoftargets, int rowSize, int columnSize){
    for (size_t i = 0; i < numoftargets; i++)
        {
            if (targets[i].isHome == 0) // check if target has not been collected
            {
                drawTarget(targets[i].currentX, targets[i].currentY, rowSize, columnSize);
            }
        }
}
void drawAllObstacles(struct obstacle *obstacles, int numofobstacles, int rowSize, int columnSize){
    for (size_t i = 0; i < numofobstacles; i++)
        {
            drawObstacle(obstacles[i].X, obstacles[i].Y, rowSize, columnSize);
        }
}


void move(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles, char movements[], int *numomoves, int rowSize, int columnSize) {
    int direction = rand() % 10; //Favoring going forward from trial and error
    if (direction < 8 && canMoveForward(myrobot, obstacles, numofobstacles, rowSize, columnSize)) {
        forward(myrobot, movements, *numomoves);
        (*numomoves)++;
    } else if (direction == 8 && canTurnLeft(myrobot, obstacles, numofobstacles, rowSize, columnSize)) {
        left(myrobot);
        if (canMoveForward(myrobot, obstacles, numofobstacles, rowSize, columnSize)) {
            forward(myrobot, movements, *numomoves);
            (*numomoves)++;
        }
    } else if (direction == 9) {
        right(myrobot);
        if (canMoveForward(myrobot, obstacles, numofobstacles, rowSize, columnSize)) {
            forward(myrobot, movements, *numomoves);
            (*numomoves)++;
        }
    }
}

void initialiseRobot(struct robot *myrobot, int initialX, int initialY, char *direction) {
    myrobot->currentX = initialX;
    myrobot->currentY = initialY;
    myrobot->direction = direction;
}

void initialiseGameElements(int numoftargets, struct target *targets, int numofobstacles, struct obstacle *obstacles, int rowSize, int columnSize, int initialX, int initialY) {
    setWindowSize(WINDOWSIZE,WINDOWSIZE);
    initialiseObstacles(numofobstacles, obstacles, rowSize, columnSize, initialX, initialY);
    intiialiseTargets(numoftargets, targets, numofobstacles, obstacles, rowSize, columnSize, initialX, initialY);
}

void drawGame(int rowSize, int columnSize, struct target *targets, int numoftargets, struct obstacle *obstacles, int numofobstacles, struct robot *myrobot, int homeX, int homeY) {
    drawBackground(rowSize, columnSize);
    background();
    drawHome(homeX, homeY, rowSize, columnSize);
    drawAllTargets(targets, numoftargets, rowSize, columnSize);
    drawAllObstacles(obstacles, numofobstacles, rowSize, columnSize);
    foreground();
    drawRobot(myrobot, rowSize, columnSize);
}

void handleMarker(int *targetMarker, struct robot *myrobot, int rowSize, int columnSize, int *numomoves, char *movements, int initialX, int initialY) {
    background();
    setColour(white);
    fillRect(((WINDOWSIZE/rowSize) * myrobot->currentX) + 5, ((WINDOWSIZE/columnSize) * myrobot->currentY) + 5, (WINDOWSIZE/rowSize) - 10, (WINDOWSIZE/columnSize) - 10);
    foreground();
    (*targetMarker)++;
    pickUpMarker(myrobot);
    reverseToHome(*numomoves, movements, myrobot, initialY, initialX, rowSize, columnSize);
    *numomoves = 0; //Reset the number of moves
    background();
    drawTarget(myrobot->currentX, myrobot->currentY, rowSize, columnSize);
    dropMarker(myrobot);
}

void validateArguments(int initialX, int initialY, char *direction, int rowSize, int columnSize, int numoftargets, int numofobstacles){
    if (initialX < 0 || initialX > rowSize - 1) {  //Since my coordinates start from 0, I need to subtract 1 from the rowSize and columnSize.
        printf("Initial X value is out of bounds\n");
        exit(1);
    }
    if (initialY < 0 || initialY > columnSize - 1) {
        printf("Initial Y value is out of bounds\n");
        exit(1);
    }
    if (strcmp(direction, "north") != 0 && strcmp(direction, "east") != 0 && strcmp(direction, "south") != 0 && strcmp(direction, "west") != 0) { 
        printf("Direction is invalid\n");
        exit(1);
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
    char* direction = "north"; //Default values
    int numomoves = 0;
    int rowSize = 10;
    int columnSize = 10;
    int initialX = rand() % 10;
    int initialY = rand() % 10;
    int targetMarker = 0;
    int rowsVisited = 0;
    int blocksVisited = 0;
    int numoftargets = rand() % 10 + 1;
    int numofobstacles = rand() % 10 + 1;
    struct robot myrobot;
    if (argc == 8) // 7 arguments were typed
    {
        initialX = atoi(argv[1]);
        initialY = atoi(argv[2]);
        direction = argv[3]; 
        rowSize = atoi(argv[4]);
        columnSize = atoi(argv[5]);
        numoftargets = atoi(argv[6]);
        numofobstacles = atoi(argv[7]);
        validateArguments(initialX, initialY, direction, rowSize, columnSize, numoftargets, numofobstacles);
    }
    struct target targets[numoftargets];
    struct obstacle obstacles[numofobstacles];
    initialiseRobot(&myrobot, initialX, initialY, direction);
    initialiseGameElements(numoftargets, targets, numofobstacles, obstacles, rowSize, columnSize, initialX, initialY);
    while (targetMarker != numoftargets) 
    {   
        do
        {   
            move(&myrobot, obstacles, numofobstacles, movements, &numomoves, rowSize, columnSize);
            drawGame(rowSize, columnSize, targets, numoftargets, obstacles, numofobstacles, &myrobot, initialX, initialY);
        }
        while (atMarker(&myrobot, targets, numoftargets) == 0);
        handleMarker(&targetMarker, &myrobot, rowSize, columnSize, &numomoves, movements, initialX, initialY);
    }
    free(movements);
    printf("All targets have been found!\n");
}