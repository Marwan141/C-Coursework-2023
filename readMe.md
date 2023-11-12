# C Coursework

Welcome to my coursework! In this version of the coursework with an added twist! You are playing as a child spirit (Robot) recollecting tears (Markers).

## Dependancies

To install this project, you need a C compiler, in this file I explain everything with GCC.

## How to run
First, we need to compile the code to do this we need to make sure we have gcc installed. Once installed, run on your terminal on the same folder as the files the following command:

```c
gcc -o "INSERT_FILE_NAME_HERE" setup.c
```
Beautiful! Now we need to run the actual compiled code. To do this we need to input the following command onto our terminal. (Make sure you're still in the same directory)
```c
./"INSERT_FILE_NAME_HERE" | java -jar  drawapp-3.0.jar
```
This will initialise the random version of the game. If you want to manually enter variables here's a guide on how to utilise command line arguments to do so.
```c
./"INSERT_FILE_NAME_HERE" <InitialX> <InitialY> <InitialDirection> <rowSize> <columnSize> <numberoftargets> <numberofobstacles> | java -jar  drawapp-3.0.jar
```

This might seem a little intimidating but here's an example command.

```c
./test 2 4 north 10 10 4 9 | java -jar  drawapp-3.0.jar
```

## Constraints

Please keep in mind the following constraints when running the commands.

initialX can be any number between 0 and rowSize - 1 

initialY can be any number between 0 and columnSize - 1 

This is due to the fact that the way I number each block is from 0.

Don't try to make the robot's life impossible! Keep the number of obstacles sensible (: Although you can test it however much you want.