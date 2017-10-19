/* 
 * File:   Checkers.h
 * Author: Logan Reich
 *
 * Created on April 9, 2017, 6:22 PM
 */

#ifndef CHECKERS_H
#define	CHECKERS_H
#include "game.h"
#include "Space.h"
#include <string>

namespace main_savitch_14 {

    class Checkers : public game {
    public:
        Checkers();
        void restart();
        void display_status()const;
        bool is_legal(const std::string& move)const;
        void make_move(const std::string& move);
        bool is_game_over()const;
        bool must_jump()const;
        game* clone()const;
        void compute_moves(std::queue<string>& moves)const;
        int evaluate()const;
    private:
        Space board[8][8];
    };
}
#include "Checkers.cc"
#endif	/* CHECKERS_H */

