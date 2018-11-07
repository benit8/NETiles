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
#include <list>

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

template <typename... Args>
class Signal
{
	class IConnection
	{
	public:
		virtual ~IConnection() = default;
		virtual void emit(Args...) = 0;
	};

	////////////////////////////////////////

	template <typename T>
	class Connection : public IConnection
	{
	public:
		Connection(T *classPtr, void (T::*classMember)(Args...))
		: m_classPtr(classPtr)
		, m_classMember(classMember)
		{}

		~Connection() override = default;

		void emit(Args... args) override {
			(m_classPtr->*m_classMember)(args...);
		}

	private:
		T *m_classPtr;
		void (T::*m_classMember)(Args...);
	};

public:
	Signal() = default;
	~Signal() {
		for (auto it = m_connections.begin(); it != m_connections.end(); ++it)
			delete *it;
	}

public:
	template <typename T>
	void connect(T *classPtr, void (T::*classMember)(Args...)) {
		auto c = new Connection<T>(classPtr, classMember);
		m_connections.push_back(c);
	}

	void emit(Args... args) {
		for (auto it = m_connections.begin(); it != m_connections.end(); ++it)
			(*it)->emit(args...);
	}

private:
	std::list<IConnection *> m_connections;
};

}