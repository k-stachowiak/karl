#include "machine.h"

Machine::Machine(TransitionMap transitionMap) :
	m_transition_map(transitionMap)
{}

void Machine::ChangeState(Transition transition)
{
	if (transition.target_state == Transition::State::END) {
		m_current_state.reset();
		return;
	}

	if (transition.target_state == Transition::State::THIS_STATE) {
		return;
	}

	m_current_state = m_transition_map[transition.target_state](transition.data);
}
