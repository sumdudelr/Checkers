/* 
 * File:   Checkers.cc
 * Author: Logan Reich
 * 
 * Created on April 9, 2017, 6:22 PM
 */

#include "Checkers.h"
#include "colors.h"
#include "game.h"
#include <iostream>
#include <iomanip>
using namespace std;
namespace main_savitch_14 {

    Checkers::Checkers() {
    }

    //Start the game from the beginning

    void Checkers::restart() {
        //Start by clearing all spaces
        for (int y = 0; y < 8; ++y) {
            for (int x = 0; x < 8; ++x) {
                board[x][y].set_playable(false);
                board[x][y].set_status('E');
                board[x][y].king_me(false);
            }
        }

        //Set each space individually

        board[0][0].set_playable(true);
        board[0][0].set_status('B');

        board[2][0].set_playable(true);
        board[2][0].set_status('B');

        board[4][0].set_playable(true);
        board[4][0].set_status('B');

        board[6][0].set_playable(true);
        board[6][0].set_status('B');

        board[1][1].set_playable(true);
        board[1][1].set_status('B');

        board[3][1].set_playable(true);
        board[3][1].set_status('B');

        board[5][1].set_playable(true);
        board[5][1].set_status('B');

        board[7][1].set_playable(true);
        board[7][1].set_status('B');

        board[0][2].set_playable(true);
        board[0][2].set_status('B');

        board[2][2].set_playable(true);
        board[2][2].set_status('B');

        board[4][2].set_playable(true);
        board[4][2].set_status('B');

        board[6][2].set_playable(true);
        board[6][2].set_status('B');

        board[1][5].set_playable(true);
        board[1][5].set_status('R');

        board[3][5].set_playable(true);
        board[3][5].set_status('R');

        board[5][5].set_playable(true);
        board[5][5].set_status('R');

        board[7][5].set_playable(true);
        board[7][5].set_status('R');

        board[1][7].set_playable(true);
        board[1][7].set_status('R');

        board[3][7].set_playable(true);
        board[3][7].set_status('R');

        board[5][7].set_playable(true);
        board[5][7].set_status('R');

        board[7][7].set_playable(true);
        board[7][7].set_status('R');

        board[0][6].set_playable(true);
        board[0][6].set_status('R');

        board[2][6].set_playable(true);
        board[2][6].set_status('R');

        board[4][6].set_playable(true);
        board[4][6].set_status('R');

        board[6][6].set_playable(true);
        board[6][6].set_status('R');

        //Playable empty spaces
        board[1][3].set_playable(true);

        board[3][3].set_playable(true);

        board[5][3].set_playable(true);

        board[7][3].set_playable(true);

        board[0][4].set_playable(true);

        board[2][4].set_playable(true);

        board[4][4].set_playable(true);

        board[6][4].set_playable(true);
    }

    //Draw the board to screen

    void Checkers::display_status()const {
        cout << "    A  B  C  D  E  F  G  H \n";
        for (int y = 0; y < 8; ++y) {
            char tmp;
            cout << RESET << ' ' << (tmp = y + '1') << ' ';
            for (int x = 0; x < 8; ++x) {
                if (board[x][y].get_playable()) {
                    if (board[x][y].get_status() == 'E')
                        cout << B_BLACK << "   ";
                    else if (board[x][y].get_status() == 'B') {
                        if(board[x][y].get_king() == true)
                            cout << BOLD;   
                        cout << B_BLACK << WHITE << " B " << RESET;
                    }
                    else if (board[x][y].get_status() == 'R') {
                        if(board[x][y].get_king() == true)
                            cout << BOLD;
                        cout << B_BLACK << RED << " R " << RESET;
                    }
                }
                    else
                    cout << B_WHITE << "   ";
            }
            cout << RESET << endl;
        }
    }

    //Check if a move is legal

    bool Checkers::is_legal(const std::string& move)const {

        int x1 = move[0] - 'A';
        int y1 = move[1] - '1';
        int x2 = move[2] - 'A';
        int y2 = move[3] - '1';

        //Checks for moving off the board
        if (x1 > 8 || x1 < 0 || y1 > 8 || y1 < 0)
            return false;
        else if (x2 > 8 || x2 < 0 || y2 > 8 || y2 < 0)
            return false;
        
        //Check the current player
        if(next_mover() == HUMAN && board[x1][y1].get_status() != 'B') {
            return false;
        }
        else if(next_mover() != HUMAN && board[x1][y1].get_status() != 'R') {
            return false;
        }

        //Need to check if there must be a jump first
        int diff;
        if (must_jump()) {
            //Must jump!
            diff = 2;
            if(board[(x1 + x2) / 2][(y1 + y2) / 2].get_status() == 'E') {
                return false;
            }
            else if(next_mover() == HUMAN &&
                    board[(x1 + x2) / 2][(y1 + y2) / 2].get_status() == 'B')
                return false;
            else if(next_mover() != HUMAN &&
                    board[(x1 + x2) / 2][(y1 + y2) / 2].get_status() == 'R')
                return false;
        } else
            diff = 1;

        if (board[x2][y2].get_status() == 'E') {
            if (board[x1][y1].get_king() == false &&
                    board[x1][y1].get_status() == 'B') {
                //Can only move down
                if ((x1 == x2 + diff || x1 == x2 - diff) && (y1 == y2 - diff)) {
                    return true;
                }
            } else if (board[x1][y1].get_king() == false
                    && board[x1][y1].get_status() == 'R') {
                //Can only move up
                if ((x1 == x2 + diff || x1 == x2 - diff) && (y1 == y2 + diff)) {
                    return true;
                }
            } else {
                //Can move forward and backward
                if ((x1 == x2 + diff || x1 == x2 - diff)
                        && (y1 == y2 + diff || y1 == y2 - diff)) {
                    return true;
                }
            }
        }

        return false;
    }

    //Make a move

    void Checkers::make_move(const std::string& move) {
        int x1 = move[0] - 'A';
        int y1 = move[1] - '1';
        int x2 = move[2] - 'A';
        int y2 = move[3] - '1';
        bool did_jump = false;
        if (must_jump()) {
            board[(x1 + x2) / 2][(y1 + y2) / 2].set_status('E');
            did_jump = true;
        }

        board[x2][y2].set_status(board[x1][y1].get_status());
        board[x2][y2].king_me(board[x1][y1].get_king());
        if(board[x2][y2].get_status() == 'R' && y2 == 0)
            board[x2][y2].king_me(true);
        if(board[x2][y2].get_status() == 'B' && y2 == 7)
            board[x2][y2].king_me(true);

        board[x1][y1].set_status('E');
        
        if(!(did_jump && must_jump()))
            game::make_move(move);
    }

    bool Checkers::is_game_over()const {
        bool thing1 = true;
        bool thing2 = true;
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                if (board[x][y].get_status() == 'R'){
                    thing1 = false;
                }
                else if(board[x][y].get_status() == 'B') {
                    thing2 = false;
                }
            }
        }
            if(thing1 == true || thing2 == true)
                return true;
            else return false;
    }

    bool Checkers::must_jump() const {
        for (int x = 0; x < 6; ++x) {
            for (int y = 0; y < 8; ++y) {
                if (board[x][y].get_status() == 'B' &&
                        next_mover() == HUMAN && y < 6) {
                    if (board[x + 1][y + 1].get_status() == 'R' &&
                            board[x + 2][y + 2].get_status() == 'E') {
                        //There Must Be A Jump
                        return true;
                    }
                    else if(board[x][y].get_king() == true &&
                            board[x + 1][y - 1].get_status() == 'R' &&
                            board[x + 2][y - 2].get_status() == 'E') {
                        return true;
                    }
                } else if (board[x][y].get_status() == 'R' &&
                        next_mover() != HUMAN && y > 1) {
                    if (board[x + 1][y - 1].get_status() == 'B' &&
                            board[x + 2][y - 2].get_status() == 'E') {
                        //There Must Be A Jump
                        return true;
                    }
                    else if(board[x][y].get_king() == true &&
                            board[x + 1][y + 1].get_status() == 'B' &&
                            board[x + 2][y + 2].get_status() == 'E') {
                        return true;
                    }
                }
            }
        }
        for (int x = 2; x < 8; ++x) {
            for (int y = 0; y < 8; ++y) {
                if (board[x][y].get_status() == 'B' &&
                        next_mover() == HUMAN && y < 6) {
                    if (board[x - 1][y + 1].get_status() == 'R' &&
                            board[x - 2][y + 2].get_status() == 'E') {
                        //There Must Be A Jump
                        return true;
                    }
                    else if(board[x][y].get_king() == true &&
                            board[x - 1][y - 1].get_status() == 'R' &&
                            board[x - 2][y - 2].get_status() == 'E') {
                        return true;
                    }
                } else if (board[x][y].get_status() == 'R' &&
                        next_mover() != HUMAN && y > 1) {
                    if (board[x - 1][y - 1].get_status() == 'B' &&
                            board[x - 2][y - 2].get_status() == 'E') {
                        //There Must Be A Jump
                        return true;
                    }
                    else if(board[x][y].get_king() == true &&
                            board[x - 1][y + 1].get_status() == 'B' &&
                            board[x - 2][y + 2].get_status() == 'E') {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    void Checkers::compute_moves(std::queue<string>& moves)const {
        //Compute All Moves
        for(int x1 = 0; x1 < 8; ++x1) {
            for(int y1 = 0; y1 < 8; ++y1) {
                for(int x2 = 0; x2 < 8; ++x2) {
                    for(int y2 = 0; y2 < 8; ++y2) {
                        string move = "NULL";
                        move[0] = x1 + 'A';
                        move[1] = y1 + '1';
                        move[2] = x2 + 'A';
                        move[3] = y2 + '1';
                        if(is_legal(move)) {
                            moves.push(move);
                        }
                    }
                }
            }
        }
    }
    
    int Checkers::evaluate()const {
        //Returns a numeric appraisal of the board.
        //Positive is good for the computer, negative is good for the human.
        int red = 0, black = 0;
        for(int x = 0; x < 8; ++x) {
            for(int y = 0; y < 8; ++y) {
                if(board[x][y].get_status() == 'R') {
                    ++red;
                }
                else if(board[x][y].get_status() == 'B') {
                    ++black;
                }
            }
        }
        return red - black;
    }
    
    game* Checkers::clone()const {
        return new Checkers(*this);
    }
}
