#include "graphics.c"
#include "stdlib.h"
#include "movement.c"
#include "time.h"

void drawBackground(int rowSize, int columnSize){
  background(); // Must draw on the background layer.
  setColour(black);
  for (int i = 0; i <rowSize; i++){
    for (int x = 0; x<columnSize; x++){ 
            drawRect((500/columnSize)*x, (500/rowSize)*i, (500/columnSize), (500/rowSize));        
        }
    }
}

void drawTarget(int x, int y, int rowSize, int columnSize){
    setColour(blue);
    fillArc(((500/rowSize) * x) + 5, ((500/columnSize) * y) + 5, (500/rowSize) - 10, (500/columnSize) - 10, 0 ,360);
}


void drawObstacle(int x, int y, int rowSize, int columnSize){
    background();
    setColour(cyan);
    fillArc(((500/rowSize) * x) + 5, ((500/columnSize) * y) + 5, (500/rowSize) - 10, (500/columnSize) - 10, 0 ,360);
}


int atMarker(int RX, int RY, struct target *targets, int numoftargets){ // Robot X, Robot Y, Marker X, Marker Y 
    for (size_t i = 0; i < numoftargets; i++)
    {
               if ((RX == targets[i].currentX) && (RY == targets[i].currentY) && (targets[i].isHome == 0)){
                targets[i].isHome = 1;
                return 1;}  
    }
    return 0;
}

//DrawRobot functions (:
void drawRobotBody(int x, int y, int rowSize, int columnSize) {
    setColour(black);
    drawRect(((500/rowSize) * x) + 5, ((500/columnSize) * y) + 5, (500/rowSize) - 10, (500/columnSize) - 10);
    fillRect(((500/rowSize) * x) + 5, ((500/columnSize) * y) + 10, (500/rowSize) - 35, (500/columnSize) - 30);
    fillRect(((500/rowSize) * x) + 25, ((500/columnSize) * y) + 10, (500/rowSize) - 35, (500/columnSize) - 30);
}

void drawRobotHead(int x, int y, int rowSize, int columnSize) {
    setColour(cyan);
    fillRect(((500/rowSize) * x) + 25, ((500/columnSize) * y) + 30, (500/rowSize) - 40, (500/columnSize) - 40);
}

void drawNorth(int x, int y, int rowSize, int columnSize, int *xs, int *ys) {
    xs[0] = ((500/rowSize) * x) + (500/rowSize)/2;
    ys[0] = ((500/columnSize) * y);
    xs[1] = ((500/rowSize) * x) + (500/rowSize)/3;
    ys[1] = ((500/columnSize) * y) + (500/columnSize)/3;
    xs[2] = ((500/rowSize) * x) + 2*(500/rowSize)/3;
    ys[2] = ((500/columnSize) * y) + (500/columnSize)/3;
    fillPolygon(3, xs, ys);
}

void drawEast(int x, int y, int rowSize, int columnSize, int *xs, int *ys) {
    xs[0] = ((500/rowSize) * x) + (500/rowSize);
    ys[0] = ((500/columnSize) * y) + (500/columnSize)/2;
    xs[1] = ((500/rowSize) * x) + 2*(500/rowSize)/3;
    ys[1] = ((500/columnSize) * y) + (500/columnSize)/3;
    xs[2] = ((500/rowSize) * x) + 2*(500/rowSize)/3;
    ys[2] = ((500/columnSize) * y) + 2*(500/columnSize)/3;
    fillPolygon(3, xs, ys);
}

void drawSouth(int x, int y, int rowSize, int columnSize, int *xs, int *ys) {
    xs[0] = ((500/rowSize) * x) + (500/rowSize)/2;
    ys[0] = ((500/columnSize) * y) + (500/columnSize);
    xs[1] = ((500/rowSize) * x) + (500/rowSize)/3;
    ys[1] = ((500/columnSize) * y) + 2*(500/columnSize)/3;
    xs[2] = ((500/rowSize) * x) + 2*(500/rowSize)/3;
    ys[2] = ((500/columnSize) * y) + 2*(500/columnSize)/3;
    fillPolygon(3, xs, ys);
}

void drawWest(int x, int y, int rowSize, int columnSize, int *xs, int *ys) {
    xs[0] = ((500/rowSize) * x);
    ys[0] = ((500/columnSize) * y) + (500/columnSize)/2;
    xs[1] = ((500/rowSize) * x) + (500/rowSize)/3;
    ys[1] = ((500/columnSize) * y) + (500/columnSize)/3;
    xs[2] = ((500/rowSize) * x) + (500/rowSize)/3;
    ys[2] = ((500/columnSize) * y) + 2*(500/columnSize)/3;
    fillPolygon(3, xs, ys);
}

void drawRobotDirection(struct robot *myrobot, int x, int y, int rowSize, int columnSize) {
    int xs[3], ys[3];
    setColour(red);
    switch(myrobot->direction[0]) {
        case 'n': // North
            drawNorth(x, y, rowSize, columnSize, xs, ys);
            break;
        case 'e': // East
            drawEast(x, y, rowSize, columnSize, xs, ys);
            break;
        case 's': // South
            drawSouth(x, y, rowSize, columnSize, xs, ys);
            break;
        case 'w': // West
            drawSouth(x, y, rowSize, columnSize, xs, ys);
            break;
    }
}

void drawMarker(struct robot *myrobot, int x, int y, int rowSize, int columnSize) {
    if (isCarryingAMarker(myrobot) == 1){
        setColour(blue);
        fillArc(((500/rowSize) * x) + 5, ((500/columnSize) * y) + 5, (500/rowSize) - 10, (500/columnSize) - 10, 0 ,360);
    }
}

void drawRobot(struct robot *myrobot, int rowSize, int columnSize) {
    int x = myrobot->currentX;
    int y = myrobot->currentY;
    drawRobotBody(x, y, rowSize, columnSize);
    drawRobotHead(x, y, rowSize, columnSize);
    drawRobotDirection(myrobot, x, y, rowSize, columnSize);
    drawMarker(myrobot, x, y, rowSize, columnSize);
    sleep(50);
    clear();
}
// drawRobot section finished

void reverseToHome(int numomoves, char movements[], struct robot *myrobot, int homeY, int homeX, int rowSize, int columnSize){
   
    for (size_t i = (numomoves - 1); i > 0; i--) {
    switch (movements[i]) { //decode the movements! Capital letters mean reverse in either the x or y direction.
        case 'Y':
            myrobot->direction = "south";
            myrobot->currentY += 1;
            break;
        case 'y':
            myrobot->direction = "north";
            myrobot->currentY -= 1;
            break;
        case 'X':
            myrobot->direction = "east";
            myrobot->currentX += 1;
            break;
        case 'x':
            myrobot->direction = "west";
            myrobot->currentX -= 1;
            break;
        default:
            break;
    }
    drawRobot(myrobot, rowSize, columnSize);
}
}


void intiialiseTargets(int numoftargets, struct target *targets, int numofobstacles, struct obstacle *obstacles, int rowSize, int columnSize, int homeX, int homeY){
    for (size_t i = 0; i < numoftargets; i++)
{       targets[i].currentX = rand() % rowSize; 
        targets[i].currentY = rand() % columnSize;
        for (size_t x = 0; x < numofobstacles; x++)
        {
            while ((obstacles[x].X == targets[i].currentX && obstacles[x].Y == targets[i].currentY) || targets[i].currentX == homeX && targets[i].currentY == homeY)
            {targets[i].currentX = rand() % rowSize;
            targets[i].currentY = rand() % columnSize;}
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
   int direction = rand() % 3; // Choose a random direction: 0 = forward, 1 = left, 2 = right
    if (direction == 0 && canMoveForward(myrobot, obstacles, numofobstacles, rowSize, columnSize)) {
        forward(myrobot, movements, *numomoves);
        (*numomoves)++;
    } else if (direction == 1 && canTurnLeft(myrobot, obstacles, numofobstacles, rowSize, columnSize)) {
        left(myrobot);
        if (canMoveForward(myrobot, obstacles, numofobstacles, rowSize, columnSize)) {
            forward(myrobot, movements, *numomoves);
            (*numomoves)++;
        }
    } else {
        right(myrobot);
        if (canMoveForward(myrobot, obstacles, numofobstacles, rowSize, columnSize)) {
            forward(myrobot, movements, *numomoves);
            (*numomoves)++;
        }
    }
}
//Comments for tomorrow
//Counter of blocks if at edge and counter == rowSize
//Go around obstacle


void initialiseRobot(struct robot *myrobot, int initialX, int initialY, char *direction) {
    myrobot->currentX = initialX;
    myrobot->currentY = initialY;
    myrobot->direction = direction;
}

void initialiseGameElements(int numoftargets, struct target *targets, int numofobstacles, struct obstacle *obstacles, int rowSize, int columnSize, int initialX, int initialY) {
    initialiseObstacles(numofobstacles, obstacles, rowSize, columnSize, initialX, initialY);
    intiialiseTargets(numoftargets, targets, numofobstacles, obstacles, rowSize, columnSize, initialX, initialY);
}

void drawGame(int rowSize, int columnSize, struct target *targets, int numoftargets, struct obstacle *obstacles, int numofobstacles, struct robot *myrobot) {
    drawBackground(rowSize, columnSize);
    background();
    drawAllTargets(targets, numoftargets, rowSize, columnSize);
    drawAllObstacles(obstacles, numofobstacles, rowSize, columnSize);
    foreground();
    drawRobot(myrobot, rowSize, columnSize);
}

void handleMarker(int *targetMarker, struct robot *myrobot, int rowSize, int columnSize, int *numomoves, char *movements, int initialX, int initialY) {
    background();
    setColour(white);
    fillRect(((500/rowSize) * myrobot->currentX) + 5, ((500/columnSize) * myrobot->currentY) + 5, (500/rowSize) - 10, (500/columnSize) - 10);
    foreground();
    (*targetMarker)++;
    pickUpMarker(myrobot);
    reverseToHome(*numomoves, movements, myrobot, initialX, initialY, rowSize, columnSize);
    background();
    drawTarget(myrobot->currentX, myrobot->currentY, rowSize, columnSize);
    *numomoves = 1; //reinitialise the number of moves we start from 1 so the first move gets saved.
    dropMarker(myrobot);
}

void validateArguments(int initialX, int initialY, char *direction, int rowSize, int columnSize, int numoftargets, int numofobstacles){
    if (initialX < 0 || initialX > rowSize - 1) {
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
    int maxMovements = 1000; // or any other size you want
    char *movements = malloc(maxMovements * sizeof(char));
    char* direction = "north";
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
        initialX = atoi(argv[1]); // Get x value
        initialY = atoi(argv[2]); // Get y value
        direction = argv[3]; // Get direction
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
    setWindowSize(500,500);
    while (targetMarker != numoftargets)
    {   
    do
    {   
        move(&myrobot, obstacles, numofobstacles, movements, &numomoves, rowSize, columnSize);
        drawGame(rowSize, columnSize, targets, numoftargets, obstacles, numofobstacles, &myrobot);
    } while (atMarker(myrobot.currentX, myrobot.currentY, targets, numoftargets) == 0);
    handleMarker(&targetMarker, &myrobot, rowSize, columnSize, &numomoves, movements, initialX, initialY);
    }
}