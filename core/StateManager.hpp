/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** StateManager.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class StateManager;

////////////////////////////////////////////////////////////////////////////////

#include <exception>
#include <memory>
#include <vector>

#include "State.hpp"

////////////////////////////////////////////////////////////////////////////////

class StateManager
{
public:
	enum Flags
	{
		Pop	= (1 << 0),
		Swap	= (1 << 1),
	};

public:
	StateManager();
	~StateManager();

public:
	template <typename T, typename... Args>
	void pushState(Args&&... args);
	template <typename T, typename... Args>
	void swapState(Args&&... args);

	void pushState(std::unique_ptr<State> state);
	void swapState(std::unique_ptr<State> state);
	void popState();

	State &getCurrentState() const;

protected:
	void updateStates();

private:
	std::vector<std::unique_ptr<State>> m_states;
	std::unique_ptr<State> m_swap;
	int m_flags;
};

////////////////////////////////////////////////////////////////////////////////

template <typename T, typename... Args>
inline void StateManager::pushState(Args&&... args)
{
	pushState(std::make_unique<T>(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
inline void StateManager::swapState(Args&&... args)
{
	swapState(std::make_unique<T>(std::forward<Args>(args)...));
}