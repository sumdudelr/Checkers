/* 
 * File:   Space.cc
 * Author: Logan Reich
 * 
 * Created on April 9, 2017, 6:02 PM
 */

#include "Space.h"
namespace main_savitch_14 {

    Space::Space(bool playable, char state, bool king) {
        is_playable = playable;
        if (state == 'E' || state == 'R' || state == 'B')
            status = state;
        else
            status = 'E';
        is_king == king;
    }

    void Space::set_status(char s) {
        if (s == 'E' || s == 'R' || s == 'B')
            status = s;
        else
            status = 'E';
    }

    void Space::king_me(bool k) {
        is_king = k;
    }

    bool Space::get_playable()const {
        return is_playable;
    }

    char Space::get_status()const {
        return status;
    }

    bool Space::get_king()const {
        return is_king;
    }

    void Space::set_playable(bool p) {
        is_playable = p;
    }
}
