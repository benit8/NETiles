/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Signal.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	template <typename... Args>
	class Signal;
}

////////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <forward_list>

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

template <typename... Args>
class Signal
{
	typedef std::function<void(Args...)> Connection;

public:
	Signal() = default;
	~Signal() = default;

public:
	template <typename T>
	void connect(T *classPtr, void (T::*classMember)(Args...)) {
		m_connections.push_back(std::bind(classMember, classPtr));
	}

	void emit(Args... args) {
		for (auto it = m_connections.begin(); it != m_connections.end(); ++it)
			(*it)(args...);
	}

	void operator()(Args... args) {
		emit(args...);
	}

private:
	std::forward_list<Connection> m_connections;
};

}