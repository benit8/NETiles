/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** StateManager.cpp
*/

#include "StateManager.hpp"

StateManager::StateManager()
: m_swap(nullptr)
, m_flags(0)
{
}

StateManager::~StateManager()
{
	m_states.clear();
}


void StateManager::pushState(std::unique_ptr<State> state)
{
	m_states.push_back(std::move(state));
}

void StateManager::swapState(std::unique_ptr<State> state)
{
	m_swap = std::move(state);
	m_flags |= Pop | Swap;
}

void StateManager::popState()
{
	m_flags |= Pop;
}

void StateManager::updateStates()
{
	if (m_flags & Pop) {
		m_flags &= ~Pop;
		m_states.pop_back();

		if (m_flags & Swap) {
			m_flags &= ~Swap;
			m_states.push_back(std::move(m_swap));
		}
	}
}

State &StateManager::getCurrentState() const
{
	if (m_states.empty())
		throw std::logic_error("StateManager is empty");

	return *m_states.back();
}