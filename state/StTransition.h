#ifndef ST_TRANSITION_H
#define ST_TRANSITION_H

#include <stdint.h>

namespace state {

struct StTransition {

    enum class State {
        GAME,
        THIS_STATE,
        END
    };

    State target_state;

    union Data {
        int64_t l;
        int32_t i[2];
        int16_t s[4];
        int8_t c[8];
    } data;

    StTransition(State target) :
        target_state { target }
    {
        data.l = 0xDEADC0DEDEADC0DE;
    }

    StTransition(State target, int64_t l) :
        target_state { target }
    {
        data.l = l;
    }

    StTransition(State target, int32_t i0, int32_t i1) :
        target_state { target }
    {
        data.i[0] = i0;
        data.i[1] = i1;
    }

    StTransition(State target, int16_t s0, int16_t s1, int16_t s2, int16_t s3) :
        target_state { target }
    {
        data.s[0] = s0;
        data.s[1] = s1;
        data.s[2] = s2;
        data.s[3] = s3;
    }

    StTransition(State target,
            int8_t c0, int8_t c1, int8_t c2, int8_t c3,
            int8_t c4, int8_t c5, int8_t c6, int8_t c7) :
        target_state { target }
    {
        data.c[0] = c0;
        data.c[1] = c1;
        data.c[2] = c2;
        data.c[3] = c3;
        data.c[4] = c4;
        data.c[5] = c5;
        data.c[6] = c6;
        data.c[7] = c7;
    }
};

}

#endif
