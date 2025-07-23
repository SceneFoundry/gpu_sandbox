// player_input.cpp
#include "input/player_input.h"
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/compatibility.hpp>
#include <algorithm>

PlayerInput::PlayerInput(IWindowInput* input)
    : m_input(input) {
}

void PlayerInput::update() {
    if (m_input->isKeyPressed(SandboxKey::W)) {
        // TODO: Move player forward
    }

    if (m_input->isKeyPressed(SandboxKey::ESCAPE)) {

       // TODO: Make window escape EXIT the program.
    }
}