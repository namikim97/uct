#include "utils.h"

#include <iostream>
#include "boardc4.h"
#include "boardc5.h"
#include "boardothello.h"

Game parse_game(const char *arg) {
    std::string string(arg);
    if (string=="connect4") return BOARDC4;
    else if (string=="connect5") return BOARDC5;
    else if (string=="othello") return OTHELLO;
    else return OTHELLO;
}

Board *choose_game(Game game) {
	std::cout<<"let's play ";
	switch (game) {
	case BOARDC4:
		std::cout<<"connect 4"<<std::endl;
		return new BoardC4();
	case BOARDC5:
		std::cout<<"connect 5"<<std::endl;
		return new BoardC5();
	case OTHELLO:
		std::cout<<"othello"<<std::endl;
		return new BoardOthello();
	}
}

Player *play_game(Player *player_a,Player *player_b,Board *board) {
	//FIXME check if there is a player one and a player two
	Player *player_current=player_a;
	Player *winner=NULL;
	Move * last_move=NULL;

	while (true) {
		board->print();

		//get the move
		Move *move=player_current->get_move(board,last_move);
		if (not move) break;
		last_move=move;

		//actually play the move
		board->play_move(*move);
		delete move;

		//check for win
		Token winner_token=board->check_for_win();
		if (winner_token!=NOT_PLAYED) {
			if (winner_token==player_a->get_player()) winner=player_a;
			else winner=player_b;
			break;
		}

		//switch player
		if (player_current==player_a) player_current=player_b;
		else player_current=player_a;
	}

    board->print();
	if (winner) {
		std::cout<<"winner: ";
		winner->print();
	} else {
		std::cout<<"draw";
	}
	std::cout<<std::endl;

	return winner;
}

