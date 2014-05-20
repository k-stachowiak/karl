#include "StateMachine.h"

StateMachine::StateMachine(TransitionMap transitionMap) :
    m_transition_map(transitionMap)
{}

void StateMachine::ChangeState(StateTransition transition)
{
    if (transition.target_state == StateTransition::State::END) {
        m_current_state.reset();
        return;
    }

    if (transition.target_state == StateTransition::State::THIS_STATE) {
        return;
    }

    m_current_state = m_transition_map[transition.target_state](transition.data);
}
