#include "Config.h"
#include "Platform.h"
#include "Resources.h"
#include "StateGame.h"
#include "StateMachine.h"

#include "Moon.h"

int main()
{
    CfgInit();

    Platform platform;
    Resources resources;
    StateMachine machine {{
        {
            StateTransition::State::GAME,
            [&resources](StateTransition::Data) mutable {
                return std::unique_ptr<State> { new StateGame { resources } };
            }
        }
    }};

    machine.ChangeState({ StateTransition::State::GAME });

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
