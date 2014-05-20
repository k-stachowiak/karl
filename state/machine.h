#ifndef MACHINE_H
#define MACHINE_H

#include <memory>
#include <map>
#include <functional>

#include "state.h"
#include "transition.h"

using StateMaker = std::function<std::unique_ptr<State> (Transition::Data)>;
using TransitionMap = std::map<Transition::State, StateMaker>;

class Machine {
    TransitionMap m_transition_map;
    std::unique_ptr<State> m_current_state;

public:
    Machine(TransitionMap transitionMap);
    void ChangeState(Transition transition);
    State& CurrentState() const { return *m_current_state; }
    bool HasState() const { return static_cast<bool>(m_current_state); }
};

#endif
