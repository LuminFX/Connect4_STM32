/*
 * gameDriver.h
 *
 *  Created on: Apr 17, 2025
 *      Author: tylerschmitz
 */

#ifndef INC_GAMEDRIVER_H_
#define INC_GAMEDRIVER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "LCD_Driver.h"
#include "Timer_Driver.h"
#include <math.h>
#include "RNG_Driver.h"
#include "assert.h"

#define DEFAULT_COLUMNS 7
#define DEFAULT_ROWS 6
#define DEFAULT_WIN_LENGTH 4
#define MAXIMUM_POSSIBLE_TURNS (DEFAULT_COLUMNS * DEFAULT_ROWS)

#define EMPTY_SPACE 0
#define PLAYER_ONE 1
#define PLAYER_TWO 2
#define TIE 3

#define SINGLE_PLAYER_MODE 1
#define TWO_PLAYER_MODE 2

#define GAME_STATE_MODE_SEL 0
#define GAME_STATE_TURN_LOOP 1
#define GAME_STATE_END 2

#define DEFAULT_COL_SELECTION 3

typedef struct {

	uint8_t board[DEFAULT_ROWS][DEFAULT_COLUMNS];
	uint8_t turnNumber;
	uint8_t currentPlayer;
	uint8_t playerOneWins;
	uint8_t playerTwoWins;
	uint16_t playerOneColor;
	uint16_t playerTwoColor;
	uint8_t playerMode;
	uint8_t gameState;
	uint8_t selectedCol;
	uint8_t winner;
	uint8_t secondsPlayed;

} GameInfo;

void connect4Init();
void connect4InitFromGameInfo(GameInfo game);
void displayFromGameState();
void connect4DisplayBoard();
void connect4DisplayModeSelect();
void processGameTouchInput(STMPE811_TouchData StaticTouchData);
void processGameButtonInput();
void changePlayer();
bool placePieceInCurrCol();
void AIPlayerStep();
uint8_t getWinner();
bool checkForAndHandleWinner();
void connect4DisplayWinMessage();
void connect4DisplayEndScreen();
void incrementStoredTime();
bool gameHasTie();
GameInfo getGameInfo();

#endif /* INC_GAMEDRIVER_H_ */
