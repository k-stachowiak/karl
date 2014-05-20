#include "StMachine.h"

namespace state {

StMachine::StMachine(StTransitionMap transitionMap) :
    m_transition_map(transitionMap)
{}

void StMachine::ChangeState(StTransition transition)
{
    if (transition.target_state == StTransition::State::END) {
        m_current_state.reset();
        return;
    }

    if (transition.target_state == StTransition::State::THIS_STATE) {
        return;
    }

    m_current_state = m_transition_map[transition.target_state](transition.data);
}

}
