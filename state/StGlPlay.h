#ifndef ST_GLPLAY_H
#define ST_GLPLAY_H

#include <allegro5/allegro.h>

#include "Common.h"
#include "Resources.h"
#include "State.h"
#include "ResTexture.h"

namespace state {

class StGlPlay : public State {
    bool m_done;
    res::Resources& m_resources;
    res::ResTexture m_texture;
public:
    StGlPlay(res::Resources& resources);
    StTransition Tick(double dt) override;
    void Draw(double weight) override;
    void KeyUp(int key) override;
    bool MouseMove(int dx, int dy) override;
};

}

#endif
