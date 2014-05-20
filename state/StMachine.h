#ifndef ST_MACHINE_H
#define ST_MACHINE_H

#include <memory>
#include <map>
#include <functional>

#include "State.h"
#include "StTransition.h"

namespace state {

using StMaker = std::function<std::unique_ptr<State> (StTransition::Data)>;
using StTransitionMap = std::map<StTransition::State, StMaker>;

class StMachine {
    StTransitionMap m_transition_map;
    std::unique_ptr<State> m_current_state;

public:
    StMachine(StTransitionMap transitionMap);
    void ChangeState(StTransition transition);
    State& CurrentState() const { return *m_current_state; }
    bool HasState() const { return static_cast<bool>(m_current_state); }
};

}

#endif
