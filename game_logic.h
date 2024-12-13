#ifndef __GAME_LOGIC_H
#define __GAME_LOGIC_H

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   1										/* Uncomment to use the LCD */

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define CHAR_SIZE 15  
#define GROUND_LEVEL (SCREEN_HEIGHT - CHAR_SIZE - 10)
//#define GROUND_LEVEL 230

#define MAX_OBSTACLES 5
#define MAX_LEVELS 5

extern void game_main();
extern void initCharacter();
extern void drawCharacter();
extern void eraseCharacter();
extern void moveCharacterRight();
extern void moveCharacterLeft();
extern void jumpCharacter();
extern void gravityEffect();
extern void checkCollisions();
extern void drawObstacles();
//extern void eraseObstacles();
extern void initObstaclesLevel(int level);
extern void level(int levelNum);
extern void gameOver();
extern void gameCompleted();
extern void displayScoreAndLevel();
extern void delay();
extern int checkCollisionWithObstacles();
extern int checkCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

#endif