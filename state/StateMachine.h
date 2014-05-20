#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <memory>
#include <map>
#include <functional>

#include "State.h"
#include "StateTransition.h"

using StateMaker = std::function<std::unique_ptr<State> (StateTransition::Data)>;
using TransitionMap = std::map<StateTransition::State, StateMaker>;

class StateMachine {
    TransitionMap m_transition_map;
    std::unique_ptr<State> m_current_state;

public:
    StateMachine(TransitionMap transitionMap);
    void ChangeState(StateTransition transition);
    State& CurrentState() const { return *m_current_state; }
    bool HasState() const { return static_cast<bool>(m_current_state); }
};

#endif
