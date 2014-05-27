#include "Config.h"
#include "Platform.h"
#include "Resources.h"
#include "StGame.h"
#include "StGlPlay.h"
#include "StMachine.h"

#include "Moon.h"

/* TODO:
 * - Move to indexed vertexes in the OpenGL.
 * - Move to interleaved vertex attributes.
 */

int main()
{
    CfgInit();

    Platform platform;
    res::Resources resources;

    state::StMachine machine {{
        {
            state::StTransition::State::GAME,
            [&resources](state::StTransition::Data) mutable {
                return std::unique_ptr<state::State> {
                    new state::StGame { resources }
                };
            }
        },
        {
            state::StTransition::State::GL_PLAY,
            [&resources](state::StTransition::Data) mutable {
                return std::unique_ptr<state::State> {
                    new state::StGlPlay { resources }
                };
            }
        }
    }};

    machine.ChangeState({ state::StTransition::State::GAME });
    // machine.ChangeState({ state::StTransition::State::GL_PLAY });

    while (true) {
        auto transition = platform.ProcessEvents(machine.CurrentState());
        machine.ChangeState(transition);
        if (!machine.HasState()) {
            break;
        }

        transition = platform.LoopStep(machine.CurrentState());
        machine.ChangeState(transition);
        if (!machine.HasState()) {
            break;
        }
    }

    return 0;
}
