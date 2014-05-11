#include "platform.h"
#include "resources.h"
#include "state_game.h"
#include "machine.h"

int main(void)
{
	Platform platform;
	Resources resources;
	Machine machine {{
		{
			Transition::State::GAME,
			[&resources](Transition::Data) mutable {
				return std::unique_ptr<State> { new StateGame { resources } };
			}
		}
	}};

	machine.ChangeState({ Transition::State::GAME });

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
