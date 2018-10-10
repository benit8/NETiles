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

#include "IState.hpp"

////////////////////////////////////////////////////////////////////////////////

class StateManager
{
public:
	enum Flags
	{
		Pop	= (1 << 0),
	};

public:
	StateManager();
	~StateManager();

public:
	template <typename T, typename... Args>
	void push(Args&&... args);
	void push(std::unique_ptr<IState> state);
	template <typename T, typename... Args>
	void swap(Args&&... args);
	void pop();

	void tryPop();
	IState &getCurrentState() const;

private:
	std::vector<std::unique_ptr<IState>> m_states;
	int m_flags;
};

////////////////////////////////////////////////////////////////////////////////

template <typename T, typename... Args>
inline void StateManager::push(Args&&... args)
{
	push(std::make_unique<T>(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
inline void StateManager::swap(Args&&... args)
{
	push(std::make_unique<T>(std::forward<Args>(args)...));
	m_flags |= Pop;
}