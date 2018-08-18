#include "GameStates.h"


GameStates::GameStates()
{
}


GameStates::~GameStates()
{
}

GameStates::GameStates(State startState)
{
	m_state = startState;
}

void GameStates::ChangeState(State state)
{
	m_state = state;
}

State GameStates::GetState()
{
	return m_state;
}