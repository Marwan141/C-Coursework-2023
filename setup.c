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

void drawTarget(int x, int y){
    setColour(blue);
    fillArc(((500/10) * x) + 5, ((500/10) * y) + 5, (500/10) - 10, (500/10) - 10, 0 ,360);
}


void drawObstacle(int x, int y){
    background();
    setColour(cyan);
    fillArc(((500/10) * x) + 5, ((500/10) * y) + 5, (500/10) - 10, (500/10) - 10, 0 ,360);
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


void drawRobot(struct robot *myrobot){  
    int x = myrobot->currentX;
    int y = myrobot->currentY;
    setColour(black);
    drawRect(((500/10) * x) + 5, ((500/10) * y) + 5, (500/10) - 10, (500/10) - 10);
    fillRect(((500/10) * x) + 5, ((500/10) * y) + 10, (500/10) - 35, (500/10) - 30);
    fillRect(((500/10) * x) + 25, ((500/10) * y) + 10, (500/10) - 35, (500/10) - 30);
    setColour(cyan);
    fillRect(((500/10) * x) + 25, ((500/10) * y) + 30, (500/10) - 40, (500/10) - 40);
    if (isCarryingAMarker(myrobot) == 1){
        setColour(blue);
        fillArc(((500/10) * x) + 5, ((500/10) * y) + 5, (500/10) - 10, (500/10) - 10, 0 ,360);
    }
    sleep(50);
    clear();
}

void reverseToHome(int numomoves, char *movements[], struct robot *myrobot){
    for (size_t i = (numomoves - 1); i > 0; i--) //reverse the array and follow opposite steps
    {
        if (strcmp(movements[i], "Y") == 0)
        {myrobot->currentY += 1;}
        else if (strcmp(movements[i], "y") == 0)
        {myrobot->currentY -= 1;}
        else if (strcmp(movements[i], "X") == 0)
        {myrobot->currentX += 1;}
        else if (strcmp(movements[i], "x") == 0)
        {myrobot->currentX -= 1;}
        drawRobot(myrobot);
    }
}


int main(int argc, char **argv){
    time_t t;
    srand((unsigned int) time(&t));
    char* movements[1000];
    int numomoves = 0;
    int rowSize = 10;
    int columnSize = 10;
    int initialX = 4;
    int initialY = 3;
    int targetMarker = 0;
    int numoftargets = 4;
    int numofobstacles = 10;
    struct robot myrobot;

    myrobot.currentX = initialX;
    myrobot.currentY = initialY;
    myrobot.direction = "north";

    if (argc == 5) // Four arguments were typed
    {
        initialX = atoi(argv[1]); // Get x value
        initialY = atoi(argv[2]); // Get y value
        myrobot.direction = argv[3]; // Get direction
        numoftargets = atoi(argv[6]);
    }
    struct target targets[numoftargets];
    struct obstacle obstacles[numofobstacles];

    for (size_t i = 0; i < numofobstacles; i++)
    {
        obstacles[i].X = rand() % 10;
        obstacles[i].Y = rand() % 10;
        while (obstacles[i].X == 0 || obstacles[i].X == 9)
        {
            obstacles[i].X = rand() % 10;
        }
        while (obstacles[i].Y == 0 || obstacles[i].Y == 9)
        {
            obstacles[i].Y = rand() % 10;
        }
        
        
       
       drawObstacle(obstacles[i].X, obstacles[i].Y);
    
    }


    for (size_t i = 0; i < numoftargets; i++)
{
        for (size_t i = 0; i < numofobstacles; i++)
        {
            targets[i].currentX = rand() % 10;
            targets[i].currentY = rand() % 10;
        }
               
    targets[i].isHome = 0;
}
    
    setWindowSize(500,500);

    while (targetMarker != numoftargets)
    {  
        
    do
    {   

    
        //make it visit the whole grid.
    int direction = rand() % 3; // Choose a random direction: 0 = forward, 1 = left, 2 = right

    if (direction == 0 && canMoveForward(&myrobot, obstacles, numofobstacles)) {
        forward(&myrobot, movements, numomoves);
        numomoves++;
    } else if (direction == 1 && canTurnLeft(&myrobot, obstacles, numofobstacles)) {
        left(&myrobot);
        if (canMoveForward(&myrobot, obstacles, numofobstacles)) {
            forward(&myrobot, movements, numomoves);
            numomoves++;
        }
    } else {
        right(&myrobot);
        if (canMoveForward(&myrobot, obstacles, numofobstacles)) {
            forward(&myrobot, movements, numomoves);
            numomoves++;
        }
    }
    
        
        
        drawBackground(rowSize, columnSize);
        background();
    
        for (size_t i = 0; i < numoftargets; i++)
        {
            if (targets[i].isHome == 0) // check if target has not been collected
            {
                drawTarget(targets[i].currentX, targets[i].currentY);
            }

        }
        for (size_t i = 0; i < numofobstacles; i++)
        {
            drawObstacle(obstacles[i].X, obstacles[i].Y);
        }

        foreground();
        drawRobot(&myrobot);

    } while (atMarker(myrobot.currentX, myrobot.currentY, targets, numoftargets) == 0);
    background();
    setColour(white);
    fillRect(((500/10) * myrobot.currentX) + 5, ((500/10) * myrobot.currentY) + 5, (500/10) - 10, (500/10) - 10);
    foreground();
    targetMarker++;
    pickUpMarker(&myrobot);
    reverseToHome(numomoves, movements, &myrobot);
    background();
    drawTarget(myrobot.currentX, myrobot.currentY);
    numomoves = 1; //reinitialise the number of moves we start from 1 so the first move gets saved.
    dropMarker(&myrobot);
    }
}

