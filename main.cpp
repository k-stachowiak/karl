#include "platform.h"
#include "resources.h"
#include "game.h"

int main(void)
{
	Platform platform;
	Resources resources;
	std::unique_ptr<State> initial_state { new StateGame { resources } };
	platform.Loop(std::move(initial_state));

	return 0;
}
