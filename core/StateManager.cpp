/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** StateManager.cpp
*/

#include "StateManager.hpp"

StateManager::StateManager()
: m_flags(0)
{
}

StateManager::~StateManager()
{
	m_states.clear();
}


void StateManager::push(std::unique_ptr<State> state)
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

State &StateManager::getCurrentState() const
{
	if (m_states.empty())
		throw std::logic_error("StateManager is empty");

	return *m_states.back();
}