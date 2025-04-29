/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */

extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);
    Button_Init();
    gyroInit();

	#if RUN_TESTS
	runTests();
	#endif

    initConnect4();

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#endif // COMPILE_TOUCH_FUNCTIONS

	displayConnect4();
}

void initConnect4(){
	connect4Init();
}

void displayConnect4(){
	displayFromGameState();
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}

void LCD_Touch_Polling_Connect4(){

	while (1){

		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			processGameTouchInput(StaticTouchData);
		}
		if (Button_Is_Pressed()){
			processGameButtonInput();
		}

		uint8_t gyroMove = getGyroConnect4Move();
		STMPE811_t movement;
		switch (gyroMove){
		case GYRO_SIGNAL_MOVE_RIGHT:

			movement.x = LCD_PIXEL_WIDTH - 1;
			processGameTouchInput(movement);

			break;
		case GYRO_SIGNAL_MOVE_LEFT:

			movement.x = 1;
			processGameTouchInput(movement);

			break;
		case GYRO_SIGNAL_NO_MOVE:
			break;
		}



	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
	incrementStoredTime();
}

void TIM2_IRQHandler(){
	callTIM2IRQHandler();
}

#endif // COMPILE_TOUCH_FUNCTIONS

void runTests(){

	GameInfo testGame;
	GameInfo returnedGame;
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);


	// TEST 1: CHECK FOR WINNER WITH NO PIECES ON BOARD
	uint8_t board[DEFAULT_ROWS][DEFAULT_COLUMNS] = {
	    {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
	    {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
	    {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
	    {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
	    {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
	    {EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE}
	};

	for (int i = 0; i < DEFAULT_ROWS; i++){
		for (int k = 0; k < DEFAULT_COLUMNS; k++){

			testGame.board[i][k] = board[i][k];

		}
	}

	testGame.turnNumber = 1;
	testGame.currentPlayer = PLAYER_ONE;
	testGame.playerOneWins = 0;
	testGame.playerTwoWins = 0;
	testGame.playerOneColor = LCD_COLOR_RED;
	testGame.playerTwoColor = LCD_COLOR_YELLOW;
	testGame.gameState = GAME_STATE_TURN_LOOP;
	testGame.selectedCol = DEFAULT_COL_SELECTION;
	testGame.winner = EMPTY_SPACE;
	testGame.secondsPlayed = 0;
	testGame.playerMode = TWO_PLAYER_MODE;

	connect4InitFromGameInfo(testGame);
	checkForAndHandleWinner();

	returnedGame = getGameInfo();

	assert(returnedGame.winner == EMPTY_SPACE);
	assert(returnedGame.gameState == GAME_STATE_TURN_LOOP);

	// TEST 2: CHECK FOR HORIZONTAL WINNER
	uint8_t board1[DEFAULT_ROWS][DEFAULT_COLUMNS] = {
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, PLAYER_ONE, PLAYER_ONE, PLAYER_ONE, PLAYER_ONE}
	};

	for (int i = 0; i < DEFAULT_ROWS; i++){
		for (int k = 0; k < DEFAULT_COLUMNS; k++){

			testGame.board[i][k] = board1[i][k];

		}
	}

	testGame.turnNumber = 1;
	testGame.currentPlayer = PLAYER_ONE;
	testGame.playerOneWins = 0;
	testGame.playerTwoWins = 0;
	testGame.playerOneColor = LCD_COLOR_RED;
	testGame.playerTwoColor = LCD_COLOR_YELLOW;
	testGame.gameState = GAME_STATE_TURN_LOOP;
	testGame.selectedCol = DEFAULT_COL_SELECTION;
	testGame.winner = EMPTY_SPACE;
	testGame.secondsPlayed = 0;
	testGame.playerMode = TWO_PLAYER_MODE;

	connect4InitFromGameInfo(testGame);
	checkForAndHandleWinner();

	returnedGame = getGameInfo();

	assert(returnedGame.winner == PLAYER_ONE);
	assert(returnedGame.gameState == GAME_STATE_END);

	// TEST 3: CHECK FOR VERTICAL WINNER
	uint8_t board2[DEFAULT_ROWS][DEFAULT_COLUMNS] = {
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, PLAYER_ONE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, PLAYER_ONE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, PLAYER_ONE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, PLAYER_ONE}
	};

	for (int i = 0; i < DEFAULT_ROWS; i++){
		for (int k = 0; k < DEFAULT_COLUMNS; k++){

			testGame.board[i][k] = board2[i][k];

		}
	}

	testGame.turnNumber = 1;
	testGame.currentPlayer = PLAYER_ONE;
	testGame.playerOneWins = 0;
	testGame.playerTwoWins = 0;
	testGame.playerOneColor = LCD_COLOR_RED;
	testGame.playerTwoColor = LCD_COLOR_YELLOW;
	testGame.gameState = GAME_STATE_TURN_LOOP;
	testGame.selectedCol = DEFAULT_COL_SELECTION;
	testGame.winner = EMPTY_SPACE;
	testGame.secondsPlayed = 0;
	testGame.playerMode = TWO_PLAYER_MODE;

	connect4InitFromGameInfo(testGame);
	checkForAndHandleWinner();

	returnedGame = getGameInfo();

	assert(returnedGame.winner == PLAYER_ONE);
	assert(returnedGame.gameState == GAME_STATE_END);

	// TEST 4: CHECK FOR DIAGONAL WINNER
	uint8_t board3[DEFAULT_ROWS][DEFAULT_COLUMNS] = {
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, PLAYER_ONE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, PLAYER_ONE, EMPTY_SPACE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, PLAYER_ONE, EMPTY_SPACE},
		{EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE, PLAYER_ONE}
	};

	for (int i = 0; i < DEFAULT_ROWS; i++){
		for (int k = 0; k < DEFAULT_COLUMNS; k++){

			testGame.board[i][k] = board3[i][k];

		}
	}

	testGame.turnNumber = 1;
	testGame.currentPlayer = PLAYER_ONE;
	testGame.playerOneWins = 0;
	testGame.playerTwoWins = 0;
	testGame.playerOneColor = LCD_COLOR_RED;
	testGame.playerTwoColor = LCD_COLOR_YELLOW;
	testGame.gameState = GAME_STATE_TURN_LOOP;
	testGame.selectedCol = DEFAULT_COL_SELECTION;
	testGame.winner = EMPTY_SPACE;
	testGame.secondsPlayed = 0;
	testGame.playerMode = TWO_PLAYER_MODE;

	connect4InitFromGameInfo(testGame);
	checkForAndHandleWinner();

	returnedGame = getGameInfo();

	assert(returnedGame.winner == PLAYER_ONE);
	assert(returnedGame.gameState == GAME_STATE_END);


}

