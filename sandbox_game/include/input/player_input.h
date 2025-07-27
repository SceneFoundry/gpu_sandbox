// player_input.h

#pragma once
#include "interfaces/window_input_i.h"




class PlayerInput {
public:
    PlayerInput(IWindowInput* input);

    void update();

private:
    IWindowInput* m_input;
};
