#include <string.h>
#include "drawing.h"

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
    myrobot->hasmarker = 1;
}

void dropMarker(struct robot *myrobot){
    myrobot->hasmarker = 0;
}

int isCarryingAMarker(struct robot *myrobot){
    return myrobot->hasmarker;
}

void left(struct robot *myrobot){
    switch (myrobot->direction[0])
    {
        case 'n':
            myrobot->direction = "west"; break;
        case 's':
            myrobot->direction = "east"; break;
        case 'e':
            myrobot->direction = "north"; break;
        case 'w':
            myrobot->direction = "south"; break;
    }
}

void right(struct robot *myrobot){
    switch (myrobot->direction[0])
    {
        case 'n':
            myrobot->direction = "east"; break;
        case 's':
            myrobot->direction = "west"; break;
        case 'e':
            myrobot->direction = "south"; break;
        case 'w':
            myrobot->direction = "north"; break;
    }
}

void forward(struct robot *myrobot, char movements[], int movecounter){
    switch (myrobot->direction[0])
    { //Encode movements! Capital letters mean reverse in either the x or y direction.
        case 'n':
            myrobot->currentY--;
            movements[movecounter] = 'Y'; break;
        case 's':
            myrobot->currentY++;
            movements[movecounter] = 'y'; break;
        case 'e':
            myrobot->currentX++;
            movements[movecounter] = 'x'; break;
        case 'w':
            myrobot->currentX--;
            movements[movecounter] = 'X'; break;
    }
}

void reverseToHome(int movecounter, char movements[], struct robot *myrobot, int homeY, int homeX, int rowSize, int columnSize){
    for (size_t i = (movecounter - 1); i >= 0; i--) {
        if (atHome(myrobot, homeX, homeY)) {
            break;
        }
        switch (movements[i]) { //decode the movements! Capital letters mean reverse in either the x or y direction.
            case 'Y':
                myrobot->direction = "south";
                myrobot->currentY += 1; break;
            case 'y':
                myrobot->direction = "north";
                myrobot->currentY -= 1; break;
            case 'X':
                myrobot->direction = "east";
                myrobot->currentX += 1; break;
            case 'x':
                myrobot->direction = "west";
                myrobot->currentX -= 1; break;
        }
        drawRobot(myrobot, rowSize, columnSize);
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
    }
    return 0;
}
//CanMove section end

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