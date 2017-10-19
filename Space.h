/* 
 * File:   Space.h
 * Author: Logan Reich
 *
 * Created on April 9, 2017, 6:02 PM
 */

#ifndef SPACE_H
#define	SPACE_H

namespace main_savitch_14 {

    class Space {
    public:
        Space(bool playable = false, char state = 'E', bool king = false);
        void set_playable(bool p);
        void set_status(char s);
        void king_me(bool k);
        bool get_playable()const;
        char get_status()const;
        bool get_king()const;
    private:
        //Is the space playable?
        bool is_playable;
        //Empty(E), Red(R), or Black(B)
        char status;
        //Is there a king present?
        bool is_king;
    };
}
#include "Space.cc"
#endif	/* SPACE_H */

