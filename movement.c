#include <string.h>

struct robot
    {
        int currentX;
        int currentY;
        char *direction;
        int hasMarker;
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
            movements[numomoves] = 'Y'; //lowercase Y means
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

int checkObstacle(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles){
    for (size_t i = 0; i < numofobstacles; i++)
    {
        if ((myrobot->currentX == obstacles[i].X) && (myrobot->currentY == obstacles[i].Y))
        {
            int it = (rand() % 5) + 1;

            for (size_t i = 0; i < it; i++)
            {
                left(myrobot);
            }
            return 1;
        }     
    }
    return 0;
}



int canMoveForward(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles){
    switch (myrobot->direction[0])
    {
        case 'n':
            myrobot->currentY -= 1;
            if ((myrobot->currentY) < 0 || (checkObstacle(myrobot, obstacles, numofobstacles))){ 
                myrobot->currentY += 1;
              
                return 0;
            }
            myrobot->currentY += 1;
            return 1;
        case 's':
            myrobot->currentY += 1;
            if ((myrobot->currentY) > 9 || (checkObstacle(myrobot, obstacles, numofobstacles))){
                myrobot->currentY -= 1;
            
                return 0;
            }
            myrobot->currentY -= 1;
            return 1;
        case 'e':
            myrobot->currentX += 1;
            if ((myrobot->currentX) > 9 || (checkObstacle(myrobot, obstacles, numofobstacles))){
                myrobot->currentX -= 1;
       
                return 0;
            }
            myrobot->currentX -= 1;
            return 1;
        case 'w':
            myrobot->currentX -= 1;
            if ((myrobot->currentX) < 0 || (checkObstacle(myrobot, obstacles, numofobstacles))){
                myrobot->currentX += 1;
                return 0;
            }
            myrobot->currentX += 1;
            return 1;
        
    }
}


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

int canTurnLeft(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles) {
    char* currentDirection = myrobot->direction;
    left(myrobot);
    int canMove = canMoveForward(myrobot, obstacles, numofobstacles);
    myrobot->direction = currentDirection;
    return canMove;
}
int canTurnRight(struct robot *myrobot, struct obstacle *obstacles, int numofobstacles) {
    char* currentDirection = myrobot->direction;
    right(myrobot);
    int canMove = canMoveForward(myrobot, obstacles, numofobstacles);
    myrobot->direction = currentDirection;
    return canMove;
}