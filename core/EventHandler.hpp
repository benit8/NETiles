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

#include "eventListeners/Close.hpp"
#include "eventListeners/Resize.hpp"
#include "eventListeners/Focus.hpp"
#include "eventListeners/Text.hpp"
#include "eventListeners/Key.hpp"
#include "eventListeners/MouseWheel.hpp"
#include "eventListeners/MouseButton.hpp"
#include "eventListeners/MouseMove.hpp"
#include "eventListeners/MouseFocus.hpp"

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