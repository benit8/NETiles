/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** StateManager.cpp
*/

#include "StateManager.hpp"

StateManager::StateManager()
{
}

StateManager::~StateManager()
{
	m_states.clear();
}


void StateManager::push(std::unique_ptr<IState> state)
{
	m_states.push_back(std::move(state));
}

void StateManager::pop()
{
	m_flags |= Pop;
}

void StateManager::tryPop()
{
	if (m_flags & Pop) {
		m_flags &= ~Pop;
		m_states.pop_back();
	}
}

IState &StateManager::getCurrentState() const
{
	if (m_states.empty())
		throw std::logic_error("StateManager is empty");

	return *m_states.back();
}