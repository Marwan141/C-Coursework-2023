#ifndef SETUP_H
#define SETUP_H
//declaring structs and functions used in both files 
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

void drawRobot(struct robot *myrobot, int rowSize, int columnSize);

#endif