/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** EventHandler.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

class EventHandler;

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <functional>
#include <map>
#include <vector>

#include <SFML/Window/Event.hpp>

#include "EventListeners/Close.hpp"
#include "EventListeners/Resize.hpp"
#include "EventListeners/Focus.hpp"
#include "EventListeners/Text.hpp"
#include "EventListeners/Key.hpp"
#include "EventListeners/MouseWheel.hpp"
#include "EventListeners/MouseButton.hpp"
#include "EventListeners/MouseMove.hpp"
#include "EventListeners/MouseFocus.hpp"

// Only for callbacks binding
using namespace std::placeholders;

////////////////////////////////////////////////////////////////////////////////

#define BIND(C) std::bind(&C, this)
#define BIND1(C) std::bind(&C, this, _1)
#define BIND2(C) std::bind(&C, this, _1, _2)
#define BIND3(C) std::bind(&C, this, _1, _2, _3)

////////////////////////////////////////////////////////////////////////////////

class EventHandler
{
	typedef std::map<sf::Event::EventType, std::unique_ptr<IEventListener>> EventListeners;

public:
	EventHandler();
	~EventHandler() = default;

public:
	void dispatchEvent(sf::Event &e);

	void onClose(CloseCallback callback);
	void onResize(ResizeCallback callback);
	void onFocusIn(FocusCallback callback);
	void onFocusOut(FocusCallback callback);
	void onText(TextCallback callback);
	void onKeyDown(KeyCallback callback, sf::Keyboard::Key key, int ctrlKeys = 0);
	void onKeyUp(KeyCallback callback, sf::Keyboard::Key key, int ctrlKeys = 0);
	void onMouseWheel(MouseWheelCallback callback, sf::Mouse::Wheel wheel = sf::Mouse::VerticalWheel);
	void onMouseDown(MouseButtonCallback callback, sf::Mouse::Button button);
	void onMouseUp(MouseButtonCallback callback, sf::Mouse::Button button);
	void onMouseMove(MouseMoveCallback callback);
	void onMouseIn(MouseFocusCallback callback);
	void onMouseOut(MouseFocusCallback callback);

private:
	EventListeners m_eventListeners;
};