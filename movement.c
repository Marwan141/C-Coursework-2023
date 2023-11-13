#include <string.h>

struct robot
    {
        int currentX;
        int currentY;
        char *direction;
        int hasMarker;
        int blocksVisited;
        int rowsVisited;
    };

struct target
    {
        int currentY;
        int currentX;
        int isHome;
    };
struct obstacle
    {
        int Y;
        int X;
    };

void left(struct robot *myrobot){
    switch (myrobot->direction[0])
    {
        case 'n':
            myrobot->direction = "west";
            break;
        case 's':
            myrobot->direction = "east";
            break;
        case 'e':
            myrobot->direction = "north";
            break;
        case 'w':
            myrobot->direction = "south";
            break;
    }
}

void right(struct robot *myrobot){
    switch (myrobot->direction[0])
    {
        case 'n':
            myrobot->direction = "east";
            break;
        case 's':
            myrobot->direction = "west";
            break;
        case 'e':
            myrobot->direction = "south";
            break;
        case 'w':
            myrobot->direction = "north";
            break;
    }
}

void forward(struct robot *myrobot, char movements[], int numomoves){
    switch (myrobot->direction[0])
    {
        case 'n':
            myrobot->currentY -= 1;
            movements[numomoves] = 'Y'; //Encode movement
            break;
        case 's':
            myrobot->currentY += 1;
            movements[numomoves] = 'y';
            break;
        case 'e':
            myrobot->currentX += 1;
            movements[numomoves] = 'x';
            break;
        case 'w':
            myrobot->currentX -= 1;
            movements[numomoves] = 'X';
            break;
    }
}
//CanMove section
int checkObstacle(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles){
    for (size_t i = 0; i < numofobstacles; i++)
    {
        if ((myrobot->currentX == obstacles[i].X) && (myrobot->currentY == obstacles[i].Y))
        {
            return 1;
        }     
    }
    return 0;
}

int canMoveNorth(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles) {
    myrobot->currentY -= 1;
    if ((myrobot->currentY) < 0 || (checkObstacle(myrobot, obstacles, numofobstacles))){ 
        myrobot->currentY += 1;
        myrobot->direction = "south"; //stop robot from moving forward and change direction
        return 0;
    }
    myrobot->currentY += 1;
    return 1;
}

int canMoveSouth(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles, int rowSize) {
    myrobot->currentY += 1;
    if ((myrobot->currentY) > (rowSize - 1) || (checkObstacle(myrobot, obstacles, numofobstacles))){
        myrobot->currentY -= 1;
        myrobot->direction = "north";
        return 0;
    }
    myrobot->currentY -= 1;
    return 1;
}

int canMoveEast(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles, int columnSize) {
    myrobot->currentX += 1;
    if ((myrobot->currentX) > (columnSize - 1) || (checkObstacle(myrobot, obstacles, numofobstacles))){
        myrobot->currentX -= 1;
        myrobot->direction = "west";
        return 0;
    }
    myrobot->currentX -= 1;
    return 1;
}

int canMoveWest(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles) {
    myrobot->currentX -= 1;
    if ((myrobot->currentX) < 0 || (checkObstacle(myrobot, obstacles, numofobstacles))){
        myrobot->currentX += 1;
        myrobot->direction = "east";
        return 0;
    }
    myrobot->currentX += 1;
    return 1;
}

int canMoveForward(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles, int rowSize, int columnSize){
    switch (myrobot->direction[0])
    {
        case 'n':
            return canMoveNorth(myrobot, obstacles, numofobstacles);
        case 's':
            return canMoveSouth(myrobot, obstacles, numofobstacles, rowSize);
        case 'e':
            return canMoveEast(myrobot, obstacles, numofobstacles, columnSize);
        case 'w':
            return canMoveWest(myrobot, obstacles, numofobstacles);
        default:
            return 0;
    }
}
//CanMove section end

int atHome(struct robot *myrobot, int x, int y){
    if ((myrobot->currentX == x) && (myrobot->currentY == y)){
        return 1;
    }
    return 0;
}

int targetAtHome(struct target *mytarget, int x, int y){
    if ((mytarget->currentX == x) && (mytarget->currentY == y)){
        return 1;
    }
    return 0;
}

void pickUpMarker(struct robot *myrobot){
    myrobot->hasMarker = 1;
}

void dropMarker(struct robot *myrobot){
    myrobot->hasMarker = 0;
}

int isCarryingAMarker(struct robot *myrobot){
    return myrobot->hasMarker;
}

int canTurnLeft(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles, int rowSize, int columnSize) {
    char* currentDirection = myrobot->direction;
    left(myrobot);
    int canMove = canMoveForward(myrobot, obstacles, numofobstacles, rowSize, columnSize);
    myrobot->direction = currentDirection;
    return canMove;
}
int canTurnRight(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles, int rowSize, int columnSize) {
    char* currentDirection = myrobot->direction;
    right(myrobot);
    int canMove = canMoveForward(myrobot, obstacles, numofobstacles, rowSize, columnSize);
    myrobot->direction = currentDirection;
    return canMove;
}