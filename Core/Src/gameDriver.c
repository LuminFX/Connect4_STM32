/*
 * gameDriver.c
 *
 *  Created on: Apr 17, 2025
 *      Author: tylerschmitz
 */

#include "gameDriver.h"

static GameInfo connect4Game;

void connect4Init(){

	for (int i = 0; i < DEFAULT_ROWS; i++){
		for (int k = 0; k < DEFAULT_COLUMNS; k++){

			connect4Game.board[i][k] = EMPTY_SPACE;

		}
	}

	connect4Game.turnNumber = 1;
	connect4Game.currentPlayer = PLAYER_ONE;
	connect4Game.playerOneWins = 0;
	connect4Game.playerTwoWins = 0;
	connect4Game.playerOneColor = LCD_COLOR_RED;
	connect4Game.playerTwoColor = LCD_COLOR_YELLOW;
	connect4Game.gameState = GAME_STATE_MODE_SEL;
	connect4Game.selectedCol = DEFAULT_COL_SELECTION;
	connect4Game.winner = EMPTY_SPACE;
	connect4Game.secondsPlayed = 0;
	connect4Game.minutesPlayed = 0;


}

void displayFromGameState(){

	switch (connect4Game.gameState) {

		case (GAME_STATE_MODE_SEL):
				connect4DisplayModeSelect();
				break;
		case (GAME_STATE_TURN_LOOP):
				connect4DisplayBoard();
				break;
		case (GAME_STATE_END):
				connect4DisplayEndScreen();
				break;
		default:
			LCD_Clear(0, LCD_COLOR_WHITE);
			break;

	}

}

void connect4DisplayBoard(){

	LCD_Clear(0, LCD_COLOR_WHITE);

	uint16_t currColor;

	// display main board

	uint16_t spaceValue = floor(LCD_PIXEL_WIDTH / DEFAULT_COLUMNS);
	uint16_t offset = spaceValue / 2;
	uint16_t circleRadiusValue = floor((offset * 3) / 4);

	uint16_t vertOffset = LCD_PIXEL_HEIGHT - (spaceValue * DEFAULT_ROWS) - 2;

	LCD_Draw_Square_Fill(LCD_PIXEL_WIDTH/2,  ((spaceValue * DEFAULT_ROWS) / 2) + vertOffset, LCD_PIXEL_WIDTH, (spaceValue * DEFAULT_ROWS), LCD_COLOR_BLUE);

	for (int row = 0; row < DEFAULT_ROWS; row++){
		for (int col = 0; col < DEFAULT_COLUMNS; col++){
			switch (connect4Game.board[row][col]){

				case (EMPTY_SPACE):
						currColor = LCD_COLOR_WHITE;
						break;
				case (PLAYER_ONE):
						currColor = connect4Game.playerOneColor;
						break;
				case (PLAYER_TWO):
						currColor = connect4Game.playerTwoColor;
						break;
				default:
						currColor = LCD_COLOR_BLUE;
			}

			LCD_Draw_Circle_Fill((col * spaceValue) + offset, (row * spaceValue) + offset + vertOffset, circleRadiusValue, currColor);

		}

	}

	// display piece to be placed
	if (connect4Game.currentPlayer == PLAYER_ONE){
		currColor = connect4Game.playerOneColor;
	}
	else{
		currColor = connect4Game.playerTwoColor;
	}

	LCD_Draw_Circle_Fill((connect4Game.selectedCol * spaceValue) + offset, vertOffset - offset , circleRadiusValue, currColor);

	// display top banner
	uint8_t player1BaseX = 10;
	uint8_t player1BaseY = 10;

	LCD_DisplayChar(player1BaseX,player1BaseY,'P');
	LCD_DisplayChar(player1BaseX + 15,player1BaseY,'1');

	uint8_t player2BaseX = 195;
	uint8_t player2BaseY = 10;

	LCD_DisplayChar(player2BaseX,player2BaseY,'P');
	LCD_DisplayChar(player2BaseX + 15,player2BaseY,'2');


}

void connect4DisplayModeSelect(){

	LCD_Clear(0, LCD_COLOR_WHITE);

	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);

	uint8_t player1BaseX = 20;
	uint8_t player1BaseY = 140;

	LCD_DisplayChar(player1BaseX,player1BaseY,'1');
	LCD_DisplayChar(player1BaseX + 15,player1BaseY,'P');
	LCD_DisplayChar(player1BaseX + 25,player1BaseY,'l');
	LCD_DisplayChar(player1BaseX + 35,player1BaseY,'a');
	LCD_DisplayChar(player1BaseX + 45,player1BaseY,'y');
	LCD_DisplayChar(player1BaseX + 55,player1BaseY,'e');
	LCD_DisplayChar(player1BaseX + 65,player1BaseY,'r');

	uint8_t player2BaseX = 140;
	uint8_t player2BaseY = 140;

	LCD_DisplayChar(player2BaseX,player2BaseY,'2');
	LCD_DisplayChar(player2BaseX + 15,player2BaseY,'P');
	LCD_DisplayChar(player2BaseX + 25,player2BaseY,'l');
	LCD_DisplayChar(player2BaseX + 35,player2BaseY,'a');
	LCD_DisplayChar(player2BaseX + 45,player2BaseY,'y');
	LCD_DisplayChar(player2BaseX + 55,player2BaseY,'e');
	LCD_DisplayChar(player2BaseX + 65,player2BaseY,'r');

}

void connect4DisplayWinMessage(){

	char winnerChar = 'x';
	uint16_t winnerColor = LCD_COLOR_WHITE;
	switch (connect4Game.winner){
		case (PLAYER_ONE):
			winnerChar = '1';
			winnerColor = connect4Game.playerOneColor;
			break;
		case (PLAYER_TWO):
			winnerChar = '2';
			winnerColor = connect4Game.playerTwoColor;
			break;
	}

	// print background box

	LCD_Draw_Square_Fill(LCD_PIXEL_WIDTH/2,  55, LCD_PIXEL_WIDTH, 110, winnerColor);

	// print winner text

	uint8_t player1BaseX = 20;
	uint8_t player1BaseY = 55;

	LCD_DisplayChar(player1BaseX,player1BaseY,'P');
	LCD_DisplayChar(player1BaseX + 10,player1BaseY,'l');
	LCD_DisplayChar(player1BaseX + 20,player1BaseY,'a');
	LCD_DisplayChar(player1BaseX + 30,player1BaseY,'y');
	LCD_DisplayChar(player1BaseX + 40,player1BaseY,'e');
	LCD_DisplayChar(player1BaseX + 50,player1BaseY,'r');
	LCD_DisplayChar(player1BaseX + 65,player1BaseY, winnerChar);
	LCD_DisplayChar(player1BaseX + 80,player1BaseY,'W');
	LCD_DisplayChar(player1BaseX + 90,player1BaseY,'i');
	LCD_DisplayChar(player1BaseX + 100,player1BaseY,'n');
	LCD_DisplayChar(player1BaseX + 110,player1BaseY,'s');
	LCD_DisplayChar(player1BaseX + 120,player1BaseY,'!');

}

void connect4DisplayEndScreen(){

	// TODO print end screen
	LCD_Clear(0, LCD_COLOR_WHITE);

	uint8_t gameTimeBaseX = 20;
	uint8_t gameTimeBaseY = 55;

	LCD_DisplayChar(gameTimeBaseX,gameTimeBaseY,'G');
	LCD_DisplayChar(gameTimeBaseX + 15,gameTimeBaseY,'a');
	LCD_DisplayChar(gameTimeBaseX + 30,gameTimeBaseY,'m');
	LCD_DisplayChar(gameTimeBaseX + 45,gameTimeBaseY,'e');
	LCD_DisplayChar(gameTimeBaseX + 65,gameTimeBaseY,'T');
	LCD_DisplayChar(gameTimeBaseX + 75,gameTimeBaseY,'i');
	LCD_DisplayChar(gameTimeBaseX + 85,gameTimeBaseY, 'm');
	LCD_DisplayChar(gameTimeBaseX + 100,gameTimeBaseY,'e');
	LCD_DisplayChar(gameTimeBaseX + 110,gameTimeBaseY,':');

	char tbuffer2[4];
	sprintf(tbuffer2, "%03d", connect4Game.secondsPlayed);

	LCD_DisplayChar(gameTimeBaseX + 120,gameTimeBaseY,tbuffer2[0]);
	LCD_DisplayChar(gameTimeBaseX + 135,gameTimeBaseY,tbuffer2[1]);
	LCD_DisplayChar(gameTimeBaseX + 150,gameTimeBaseY,tbuffer2[2]);
	LCD_DisplayChar(gameTimeBaseX + 165,gameTimeBaseY,'s');

	uint8_t scoreBaseX = 20;
	uint8_t scoreBaseY = 80;

	LCD_DisplayChar(scoreBaseX,scoreBaseY,'S');
	LCD_DisplayChar(scoreBaseX + 10,scoreBaseY,'c');
	LCD_DisplayChar(scoreBaseX + 20,scoreBaseY,'o');
	LCD_DisplayChar(scoreBaseX + 30,scoreBaseY,'r');
	LCD_DisplayChar(scoreBaseX + 40,scoreBaseY,'e');
	LCD_DisplayChar(scoreBaseX + 50,scoreBaseY,':');

	uint8_t scoreValsBaseX = 20;
	uint8_t scoreValsBaseY = 115;

	char buffer1[4];
	sprintf(buffer1, "%d", connect4Game.playerOneWins);

	char buffer2[4];
	sprintf(buffer2, "%d", connect4Game.playerTwoWins);

	LCD_DisplayChar(scoreValsBaseX,scoreValsBaseY,'P');
	LCD_DisplayChar(scoreValsBaseX + 10,scoreValsBaseY,'1');
	LCD_DisplayChar(scoreValsBaseX + 20,scoreValsBaseY,':');
	LCD_DisplayChar(scoreValsBaseX + 30,scoreValsBaseY, buffer1[0]);
	LCD_DisplayChar(scoreValsBaseX,scoreValsBaseY + 35,'P');
	LCD_DisplayChar(scoreValsBaseX + 10,scoreValsBaseY + 35,'2');
	LCD_DisplayChar(scoreValsBaseX + 20,scoreValsBaseY + 35,':');
	LCD_DisplayChar(scoreValsBaseX + 30,scoreValsBaseY + 35, buffer2[0]);


	LCD_Draw_Square_Fill(LCD_PIXEL_WIDTH/2, LCD_PIXEL_HEIGHT - 40 , LCD_PIXEL_WIDTH, 70, LCD_COLOR_BLUE);

	uint16_t resetBaseX = LCD_PIXEL_WIDTH/2 - 23;
	uint16_t resetBaseY = LCD_PIXEL_HEIGHT - 50;

	LCD_DisplayChar(resetBaseX,resetBaseY,'R');
	LCD_DisplayChar(resetBaseX + 15,resetBaseY,'e');
	LCD_DisplayChar(resetBaseX + 25,resetBaseY,'s');
	LCD_DisplayChar(resetBaseX + 35,resetBaseY,'e');
	LCD_DisplayChar(resetBaseX + 45,resetBaseY,'t');

}

void processGameTouchInput(STMPE811_TouchData StaticTouchData){

	switch (connect4Game.gameState){

		case (GAME_STATE_MODE_SEL):

			uint8_t OnePlayerButtonXBounds[2] = {2, LCD_PIXEL_WIDTH/2};
			uint8_t TwoPlayerButtonXBounds[2] = {LCD_PIXEL_WIDTH/2, LCD_PIXEL_WIDTH-2};

			if (StaticTouchData.x < OnePlayerButtonXBounds[1] && StaticTouchData.x > OnePlayerButtonXBounds[0]){
				connect4Game.playerMode = SINGLE_PLAYER_MODE;
				connect4Game.gameState = GAME_STATE_TURN_LOOP;
				srand(HAL_GetTick());
			}
			if (StaticTouchData.x < TwoPlayerButtonXBounds[1] && StaticTouchData.x > TwoPlayerButtonXBounds[0]){
				connect4Game.playerMode = TWO_PLAYER_MODE;
				connect4Game.gameState = GAME_STATE_TURN_LOOP;
			}

			startGameTimer();

			displayFromGameState();
			HAL_Delay(200);
			break;

		case (GAME_STATE_TURN_LOOP):

			uint8_t moveLeftXBounds[2] = {0, LCD_PIXEL_WIDTH/2};
			uint8_t moveRightXBounds[2] = {LCD_PIXEL_WIDTH/2, LCD_PIXEL_WIDTH};

			if (StaticTouchData.x < moveLeftXBounds[1] && StaticTouchData.x > moveLeftXBounds[0]){
				if (connect4Game.selectedCol > 0){
					connect4Game.selectedCol -= 1;
					displayFromGameState();
					HAL_Delay(200);
				}
			}
			if (StaticTouchData.x < moveRightXBounds[1] && StaticTouchData.x > moveRightXBounds[0]){
				if (connect4Game.selectedCol < 6){
					connect4Game.selectedCol += 1;
					displayFromGameState();
					HAL_Delay(200);
				}
			}
			break;

		case (GAME_STATE_END):

			uint16_t resetYBounds[2] = {160, 0};
			if (StaticTouchData.y < resetYBounds[0] && StaticTouchData.y > resetYBounds[1]){

				for (int i = 0; i < DEFAULT_ROWS; i++){
					for (int k = 0; k < DEFAULT_COLUMNS; k++){

						connect4Game.board[i][k] = EMPTY_SPACE;

					}
				}

				connect4Game.turnNumber = 1;
				connect4Game.currentPlayer = PLAYER_ONE;
				connect4Game.gameState = GAME_STATE_TURN_LOOP;
				connect4Game.selectedCol = DEFAULT_COL_SELECTION;
				connect4Game.winner = EMPTY_SPACE;
				connect4Game.secondsPlayed = 0;

				startGameTimer();

				displayFromGameState();
				HAL_Delay(200);

			}

			break;

		default:
			break;

	}

}

void processGameButtonInput(){

	if (connect4Game.gameState != GAME_STATE_TURN_LOOP){
		return;
	}

	if (placePieceInCurrCol()){

		changePlayer();
		connect4Game.selectedCol = DEFAULT_COL_SELECTION;
		displayFromGameState();

		if (checkForAndHandleWinner()){
			return;
		}

		connect4Game.turnNumber += 1;

		HAL_Delay(300);

		if (connect4Game.playerMode == SINGLE_PLAYER_MODE){
			AIPlayerStep();
			checkForAndHandleWinner();
		}

	}

}

bool checkForAndHandleWinner(){

	uint8_t winner = getWinner();
	if (winner != EMPTY_SPACE){
		connect4Game.winner = winner;
		connect4Game.gameState = GAME_STATE_END;

		stopGameTimer();

		connect4DisplayWinMessage();

		switch (winner){
		case (PLAYER_ONE):
			connect4Game.playerOneWins++;
			break;
		case (PLAYER_TWO):
			connect4Game.playerTwoWins++;
			break;
		}

		HAL_Delay(5000);
		displayFromGameState();
		return true;
	}
	return false;

}

bool placePieceInCurrCol(){

	if (connect4Game.board[0][connect4Game.selectedCol] == EMPTY_SPACE){

		for (int i = DEFAULT_ROWS-1; i >= 0; i--){
			if (connect4Game.board[i][connect4Game.selectedCol] == EMPTY_SPACE){
				connect4Game.board[i][connect4Game.selectedCol] = connect4Game.currentPlayer;
				return true;
			}
		}

	}
	return false;

}

void changePlayer(){

	switch (connect4Game.currentPlayer){

		case (PLAYER_ONE):
			connect4Game.currentPlayer = PLAYER_TWO;
			break;
		case (PLAYER_TWO):
			connect4Game.currentPlayer = PLAYER_ONE;
			break;
		default:
			break;
	}

}

void AIPlayerStep(){

	// TODO make a real AI thing here
	connect4Game.selectedCol = rand() % 6;
	while (!placePieceInCurrCol()){
		connect4Game.selectedCol = rand() % 6;
	}

	displayFromGameState();
	HAL_Delay(400);

	changePlayer();
	connect4Game.selectedCol = DEFAULT_COL_SELECTION;
	connect4Game.turnNumber += 1;
	displayFromGameState();
	HAL_Delay(400);

}

uint8_t getWinner(){

	// check rows for win
	for (int row = 0; row < DEFAULT_ROWS; row++){
		for (int col = 0; col < DEFAULT_COLUMNS-3; col++){

			if ((connect4Game.board[row][col] == connect4Game.board[row][col + 1]) &&
				(connect4Game.board[row][col] == connect4Game.board[row][col + 2]) &&
				(connect4Game.board[row][col] == connect4Game.board[row][col + 3]) &&
				(connect4Game.board[row][col] != EMPTY_SPACE)){
				return connect4Game.board[row][col];
			}

		}
	}

	// check cols for win
	for (int row = 0; row < DEFAULT_ROWS-3; row++){
		for (int col = 0; col < DEFAULT_COLUMNS; col++){

			if ((connect4Game.board[row][col] == connect4Game.board[row+1][col]) &&
				(connect4Game.board[row][col] == connect4Game.board[row+2][col]) &&
				(connect4Game.board[row][col] == connect4Game.board[row+3][col]) &&
				(connect4Game.board[row][col] != EMPTY_SPACE)){
				return connect4Game.board[row][col];
			}

		}
	}

	// check diagonals for win
	for (int row = 0; row < DEFAULT_ROWS-3; row++){
		for (int col = 0; col < DEFAULT_COLUMNS-3; col++){

			if ((connect4Game.board[row][col] == connect4Game.board[row+1][col + 1]) &&
				(connect4Game.board[row][col] == connect4Game.board[row+2][col + 2]) &&
				(connect4Game.board[row][col] == connect4Game.board[row+3][col + 3]) &&
				(connect4Game.board[row][col] != EMPTY_SPACE)){
				return connect4Game.board[row][col];
			}

		}
	}

	for (int row = 3; row < DEFAULT_ROWS; row++) {
	    for (int col = 0; col < DEFAULT_COLUMNS - 3; col++) {
	        if ((connect4Game.board[row][col] == connect4Game.board[row - 1][col + 1]) &&
	            (connect4Game.board[row][col] == connect4Game.board[row - 2][col + 2]) &&
	            (connect4Game.board[row][col] == connect4Game.board[row - 3][col + 3]) &&
	            (connect4Game.board[row][col] != EMPTY_SPACE)) {
	            return connect4Game.board[row][col];
	        }
	    }
	}


	return EMPTY_SPACE;

}

void incrementStoredTime(){

	connect4Game.secondsPlayed++;

}

