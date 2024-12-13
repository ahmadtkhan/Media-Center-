#include "LPC17xx.h" 
#include "GLCD.h"
//#include "cmsis_os.h"
#include <stdio.h>
#include "game_logic.h"
#include "KBD.h"

#define DELAY_1MS_COUNT 25000

#define GAME_STATE_RUNNING 0
#define GAME_STATE_EXIT 1
#define GAME_STATE_RETRY 2

uint32_t current_joystick_val = 0;
int gameState = GAME_STATE_RETRY;

typedef enum {
    OBSTACLE_PLATFORM,
    OBSTACLE_SPIKE
} ObstacleType;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    ObstacleType type;
} Obstacle;

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int velocityY;
    int isJumping;
} Character;

Character player;
Obstacle obstacles[MAX_OBSTACLES];
int numObstacles;
int levelNumber = 1;
int score = 100;
unsigned int endTime = 100;

void resetGameVariables() {
    score = 0;
    levelNumber = 1;
    initCharacter();
   
}

void game_main() {
    GLCD_Init();

    while (gameState != GAME_STATE_EXIT) { 
        if (gameState == GAME_STATE_RETRY) {
            
            resetGameVariables();
            gameState = GAME_STATE_RUNNING; 
        }

        GLCD_Clear(Black);
        GLCD_SetBackColor(White);
        GLCD_SetTextColor(Black);
        GLCD_DisplayString(0, 0, __FI, "COE718 Obstacle game");
        GLCD_DisplayString(1, 0, __FI, "Finish 5 levels of obstacle course");

        GLCD_SetBackColor(Black);
        GLCD_SetTextColor(Green);

        unsigned int startTime = 0;

        for (levelNumber = 1; levelNumber <= MAX_LEVELS; levelNumber++) {
            level(levelNumber);
            if (gameState != GAME_STATE_RUNNING) {
                break; 
            }
        }

        if (gameState == GAME_STATE_RUNNING) {
       
            score = (endTime - startTime) / 2;
            gameCompleted();
        }
    }
}

void draw_ground_lvl(){
    GLCD_SetTextColor(Yellow);
    GLCD_Bargraph_Modified(0, SCREEN_HEIGHT - 10,  SCREEN_WIDTH, 10, 100);
}

void initCharacter() {
    player.x = 10;
    player.y = GROUND_LEVEL;
    player.width = CHAR_SIZE;
    player.height = CHAR_SIZE;
    player.velocityY = 0;
    player.isJumping = 0;
}

void drawCharacter() {
    GLCD_SetTextColor(White);
    GLCD_Bargraph_Modified(player.x, player.y,  player.width, player.height, 100);
}

void eraseCharacter() {
    GLCD_SetTextColor(Black);
    GLCD_Bargraph_Modified(player.x, player.y, player.width, player.height, 100);
}

void moveCharacterRight() {
    eraseCharacter();
    player.x += 5;
    if (player.x > SCREEN_WIDTH) {
        player.x = 0;
    }
    drawCharacter();
}

void moveCharacterLeft() {
    eraseCharacter();
    player.x -= 20;
    if (player.x <= 10) {
        player.x = 10;
    }
    drawCharacter();
}

void jumpCharacter() {
    if (!player.isJumping) {
        player.isJumping = 1;
        player.velocityY = -10; 
    }
}

void gravityEffect() {
    if (player.isJumping) {
        eraseCharacter();
        player.y += player.velocityY;
        player.velocityY += 1;
        if (player.y >= GROUND_LEVEL) {
            player.y = GROUND_LEVEL;
            player.isJumping = 0;
            player.velocityY = 0;
        }
    } else if(player.y < GROUND_LEVEL){
        eraseCharacter();
        player.y += player.velocityY;
        player.velocityY += 1;
    }
    drawCharacter();
}

void checkCollisions() {
    if (checkCollisionWithObstacles()) {

    }
}

void drawObstacles() {
    int i;
    for (i = 0; i < numObstacles; i++) {
        Obstacle obs = obstacles[i];
        if (obs.type == OBSTACLE_PLATFORM) {
            GLCD_SetTextColor(Green);
        } else if (obs.type == OBSTACLE_SPIKE) {
            GLCD_SetTextColor(Red);
        }
        GLCD_Bargraph_Modified(obs.x, obs.y, obs.width, obs.height, 100);
    }
}

void eraseObstacles() {
    int i;
    for (i = 0; i < numObstacles; i++) {
        Obstacle obs = obstacles[i];
        GLCD_SetTextColor(Black);
        GLCD_Bargraph_Modified(obs.x, obs.y, obs.width, obs.height, 100);
    }
}

void delay(int milliseconds) {
    volatile unsigned long i;
    while (milliseconds > 0) {
        for (i = 0; i < DELAY_1MS_COUNT; i++) {
        }
        milliseconds--;
    }
}

void initObstaclesLevel(int level) {
    switch (level) {
        case 1:
            numObstacles = 4;
            obstacles[0] = (Obstacle){50, GROUND_LEVEL - 30, 75, 10, OBSTACLE_PLATFORM};
            obstacles[1] = (Obstacle){100, GROUND_LEVEL, 10, 40, OBSTACLE_SPIKE};
						obstacles[2] = (Obstacle){275, GROUND_LEVEL, 10, 20, OBSTACLE_SPIKE};
						obstacles[3] = (Obstacle){150, GROUND_LEVEL - 70, 75, 10, OBSTACLE_PLATFORM};
						obstacles[4] = (Obstacle){300, GROUND_LEVEL - 30, 75, 10, OBSTACLE_PLATFORM};
            break;
        case 2:
					numObstacles = 3;
          obstacles[0] = (Obstacle){50, GROUND_LEVEL - 20, 70, 30, OBSTACLE_PLATFORM};
          obstacles[1] = (Obstacle){150, GROUND_LEVEL, 20, 20, OBSTACLE_SPIKE};
					obstacles[2] = (Obstacle){220, GROUND_LEVEL, 20, 20, OBSTACLE_SPIKE};
					break;
				case 3:
					numObstacles = 3;
          obstacles[0] = (Obstacle){50, GROUND_LEVEL - 30, 50, 10, OBSTACLE_PLATFORM};
          obstacles[1] = (Obstacle){150, GROUND_LEVEL, 20, 20, OBSTACLE_SPIKE};
					obstacles[2] = (Obstacle){220, GROUND_LEVEL, 20, 20, OBSTACLE_SPIKE};
					break;
				case 4:
					numObstacles = 4;
          obstacles[0] = (Obstacle){25, GROUND_LEVEL - 30, 50, 10, OBSTACLE_PLATFORM};
					obstacles[1] = (Obstacle){25, GROUND_LEVEL - 30, 50, 10, OBSTACLE_PLATFORM};
          obstacles[2] = (Obstacle){150, GROUND_LEVEL, 20, 20, OBSTACLE_SPIKE};
					obstacles[3] = (Obstacle){220, GROUND_LEVEL, 20, 20, OBSTACLE_SPIKE};
					break;
				case 5:
					obstacles[0] = (Obstacle){25, GROUND_LEVEL, 50, 10, OBSTACLE_SPIKE};
					obstacles[1] = (Obstacle){25, GROUND_LEVEL - 30, 50, 10, OBSTACLE_PLATFORM};
          obstacles[2] = (Obstacle){150, GROUND_LEVEL, 20, 20, OBSTACLE_SPIKE};
					obstacles[3] = (Obstacle){220, GROUND_LEVEL, 20, 20, OBSTACLE_SPIKE};
					break;
        default:
            numObstacles = 0;
            break;
    }
}

void level(int levelNum) {
    if (gameState != GAME_STATE_RUNNING) {
        return; // Exit if game is not running
    } 
		endTime = endTime + 100;

    GLCD_Clear(Black);
    initCharacter();
    initObstaclesLevel(levelNum);
    drawObstacles();

    displayScoreAndLevel();

    while (player.x < SCREEN_WIDTH && gameState == GAME_STATE_RUNNING) {
        draw_ground_lvl();
        gravityEffect();
        checkCollisions();

        if (gameState != GAME_STATE_RUNNING) {
            break; // Exit if game is over
        }

        current_joystick_val = get_button();
        delay(20);

        if(current_joystick_val == KBD_UP){
            jumpCharacter();
        } else if(current_joystick_val == KBD_LEFT){
            moveCharacterLeft();
        } else if(current_joystick_val == KBD_RIGHT){
            moveCharacterRight();
        }
    }
}

void gameOver() {
    GLCD_Clear(Black);
    GLCD_SetTextColor(Red);
    GLCD_DisplayString(5, 5, 1, "Game Over");
    char scoreStr[20];
    sprintf(scoreStr, "Final Score: %d", score);
    GLCD_DisplayString(7, 5, 1, (unsigned char *)scoreStr);

    int selectedOption = 0; // 0: Retry, 1: Exit
    uint32_t joystickVal;

    while (1) {
        if (selectedOption == 0) {
            // Retry is selected
            GLCD_SetBackColor(White);
            GLCD_SetTextColor(Black);
            GLCD_DisplayString(9, 5, 1, "Retry");

            GLCD_SetBackColor(Black);
            GLCD_SetTextColor(White);
            GLCD_DisplayString(11, 5, 1, "Exit");
        } else {
            // Exit is selected
            GLCD_SetBackColor(Black);
            GLCD_SetTextColor(White);
            GLCD_DisplayString(9, 5, 1, "Retry");

            GLCD_SetBackColor(White);
            GLCD_SetTextColor(Black);
            GLCD_DisplayString(11, 5, 1, "Exit");
        }

        joystickVal = get_button();

        if (joystickVal == KBD_DOWN) {
            selectedOption = (selectedOption + 1) % 2;
            delay(200);
        } else if (joystickVal == KBD_SELECT) {
            if (selectedOption == 0) {
                gameState = GAME_STATE_RETRY;
                break;
            } else {
                gameState = GAME_STATE_EXIT;
                break;
            }
        }
        delay(100);
    }
}

void gameCompleted() {
    GLCD_Clear(Black);
    GLCD_SetBackColor(Black);
    GLCD_SetTextColor(Green);
    GLCD_DisplayString(5, 5, __FI, "Game completed !! Congrats");
    char scoreStr[20];
    sprintf(scoreStr, "Score: %d", score);
    GLCD_DisplayString(7, 5, __FI, (unsigned char *)scoreStr);

    int selectedOption = 0; // 0: Play Again, 1: Exit
    uint32_t joystickVal;

    while (1) {
        if (selectedOption == 0) {
            GLCD_SetBackColor(White);
            GLCD_SetTextColor(Black);
            GLCD_DisplayString(9, 5, 1, "Play Again");

            GLCD_SetBackColor(Black);
            GLCD_SetTextColor(White);
            GLCD_DisplayString(11, 5, 1, "Exit");
        } else {
            GLCD_SetBackColor(Black);
            GLCD_SetTextColor(White);
            GLCD_DisplayString(9, 5, 1, "Play Again");

            GLCD_SetBackColor(White);
            GLCD_SetTextColor(Black);
            GLCD_DisplayString(11, 5, 1, "Exit");
        }

        joystickVal = get_button();

        if (joystickVal == KBD_DOWN) {
            selectedOption = (selectedOption + 1) % 2; 
            delay(200);
        } else if (joystickVal == KBD_SELECT) {
            if (selectedOption == 0) {
                gameState = GAME_STATE_RETRY;
                break;
            } else {
                gameState = GAME_STATE_EXIT;
                break;
            }
        }
        delay(100);
    }
}

void displayScoreAndLevel() {
    GLCD_SetTextColor(Green);
    char levelStr[20];
    sprintf(levelStr, "Level: %d", levelNumber);
    GLCD_DisplayString(0, 0, __FI, (unsigned char *)levelStr);

    char scoreStr[20];
    sprintf(scoreStr, "Score: %d", score);
    GLCD_DisplayString(1, 5, __FI, (unsigned char *)scoreStr);
}

int checkCollisionWithObstacles() {
    int i;
    for (i = 0; i < numObstacles; i++) {
        Obstacle obs = obstacles[i];
        if (checkCollision(player.x, player.y, player.width, player.height,
                           obs.x, obs.y, obs.width, obs.height)) {
            if (obs.type == OBSTACLE_SPIKE) {
                gameOver();
                return 1; // Collision occurred
            } else if (obs.type == OBSTACLE_PLATFORM) {
                if (player.velocityY > 0 && player.y + player.height <= obs.y + obs.height) {
                    player.y = obs.y - player.height;
                    player.isJumping = 0;
                    player.velocityY = 0;
                }
            }
        }
    }
    return 0;
}

int checkCollision(int x1, int y1, int w1, int h1,
                   int x2, int y2, int w2, int h2) {
    if (x1 + w1 < x2 || x1 > x2 + w2) return 0;
    if (y1 + h1 < y2 || y1 > y2 + h2) return 0;
    return 1;
}


