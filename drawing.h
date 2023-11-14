#ifndef DRAWING_H
#define DRAWING_H
//declaring structs and functions used in both files 
struct robot
    {
        int currentX;
        int currentY;
        char *direction;
        int hasmarker;
    };

struct target
    {
        int currentY;
        int currentX;
        int ishome;
    };
struct obstacle
    {
        int Y;
        int X;
    };

void drawRobot(struct robot *myrobot, int rowSize, int columnSize);
void drawGame(int rowSize, int columnSize, struct target *targets, int numoftargets, struct obstacle *obstacles, int numofobstacles, struct robot *myrobot, int initialX, int initialY);

#endif