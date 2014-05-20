#include "Config.h"
#include "Platform.h"
#include "Resources.h"
#include "StGame.h"
#include "StMachine.h"

#include "Moon.h"

int main()
{
    CfgInit();

    Platform platform;
    Resources resources;
    state::StMachine machine {{
        {
            state::StTransition::State::GAME,
            [&resources](state::StTransition::Data) mutable {
                return std::unique_ptr<state::State> {
                    new state::StGame { resources }
                };
            }
        }
    }};

    machine.ChangeState({ state::StTransition::State::GAME });

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
