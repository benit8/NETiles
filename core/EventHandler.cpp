/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** EventHandler.cpp
*/

#include "EventHandler.hpp"

EventHandler::EventHandler()
{
	m_eventListeners[sf::Event::Closed]              = std::make_unique<CloseEventListener>();
	m_eventListeners[sf::Event::Resized]             = std::make_unique<ResizeEventListener>();
	m_eventListeners[sf::Event::LostFocus]           = std::make_unique<FocusEventListener>();
	m_eventListeners[sf::Event::GainedFocus]         = std::make_unique<FocusEventListener>();
	m_eventListeners[sf::Event::TextEntered]         = std::make_unique<TextEventListener>();
	m_eventListeners[sf::Event::KeyPressed]          = std::make_unique<KeyEventListener>();
	m_eventListeners[sf::Event::KeyReleased]         = std::make_unique<KeyEventListener>();
	m_eventListeners[sf::Event::MouseWheelScrolled]  = std::make_unique<MouseWheelEventListener>();
	m_eventListeners[sf::Event::MouseButtonPressed]  = std::make_unique<MouseButtonEventListener>();
	m_eventListeners[sf::Event::MouseButtonReleased] = std::make_unique<MouseButtonEventListener>();
	m_eventListeners[sf::Event::MouseMoved]          = std::make_unique<MouseMoveEventListener>();
	m_eventListeners[sf::Event::MouseEntered]        = std::make_unique<MouseFocusEventListener>();
	m_eventListeners[sf::Event::MouseLeft]           = std::make_unique<MouseFocusEventListener>();
}


void EventHandler::dispatchEvent(sf::Event &e)
{
	auto it = m_eventListeners.find(e.type);
	if (it != m_eventListeners.end())
		it->second->handleEvent(e);
}


void EventHandler::onClose(CloseCallback callback)
{
	auto it = m_eventListeners.find(sf::Event::Closed);
	if (it != m_eventListeners.end())
		dynamic_cast<CloseEventListener*>(it->second.get())->registerCallback(callback);
}

void EventHandler::onResize(ResizeCallback callback)
{
	auto it = m_eventListeners.find(sf::Event::Resized);
	if (it != m_eventListeners.end())
		dynamic_cast<ResizeEventListener*>(it->second.get())->registerCallback(callback);
}

void EventHandler::onFocusIn(FocusCallback callback)
{
	auto it = m_eventListeners.find(sf::Event::GainedFocus);
	if (it != m_eventListeners.end())
		dynamic_cast<FocusEventListener*>(it->second.get())->registerCallback(callback);
}

void EventHandler::onFocusOut(FocusCallback callback)
{
	auto it = m_eventListeners.find(sf::Event::LostFocus);
	if (it != m_eventListeners.end())
		dynamic_cast<FocusEventListener*>(it->second.get())->registerCallback(callback);
}

void EventHandler::onText(TextCallback callback)
{
	auto it = m_eventListeners.find(sf::Event::TextEntered);
	if (it != m_eventListeners.end())
		dynamic_cast<TextEventListener*>(it->second.get())->registerCallback(callback);
}

void EventHandler::onKeyDown(KeyCallback callback, sf::Keyboard::Key key, int ctrlKeys)
{
	auto it = m_eventListeners.find(sf::Event::KeyPressed);
	if (it != m_eventListeners.end())
		dynamic_cast<KeyEventListener*>(it->second.get())->registerCallback(callback, key, ctrlKeys);
}

void EventHandler::onKeyUp(KeyCallback callback, sf::Keyboard::Key key, int ctrlKeys)
{
	auto it = m_eventListeners.find(sf::Event::KeyReleased);
	if (it != m_eventListeners.end())
		dynamic_cast<KeyEventListener*>(it->second.get())->registerCallback(callback, key, ctrlKeys);
}

void EventHandler::onMouseWheel(MouseWheelCallback callback, sf::Mouse::Wheel wheel)
{
	auto it = m_eventListeners.find(sf::Event::MouseWheelScrolled);
	if (it != m_eventListeners.end())
		dynamic_cast<MouseWheelEventListener*>(it->second.get())->registerCallback(callback, wheel);
}

void EventHandler::onMouseDown(MouseButtonCallback callback, sf::Mouse::Button button)
{
	auto it = m_eventListeners.find(sf::Event::MouseButtonPressed);
	if (it != m_eventListeners.end())
		dynamic_cast<MouseButtonEventListener*>(it->second.get())->registerCallback(callback, button);
}

void EventHandler::onMouseUp(MouseButtonCallback callback, sf::Mouse::Button button)
{
	auto it = m_eventListeners.find(sf::Event::MouseButtonReleased);
	if (it != m_eventListeners.end())
		dynamic_cast<MouseButtonEventListener*>(it->second.get())->registerCallback(callback, button);
}

void EventHandler::onMouseMove(MouseMoveCallback callback)
{
	auto it = m_eventListeners.find(sf::Event::MouseMoved);
	if (it != m_eventListeners.end())
		dynamic_cast<MouseMoveEventListener*>(it->second.get())->registerCallback(callback);
}

void EventHandler::onMouseIn(MouseFocusCallback callback)
{
	auto it = m_eventListeners.find(sf::Event::MouseEntered);
	if (it != m_eventListeners.end())
		dynamic_cast<MouseFocusEventListener*>(it->second.get())->registerCallback(callback);
}

void EventHandler::onMouseOut(MouseFocusCallback callback)
{
	auto it = m_eventListeners.find(sf::Event::MouseLeft);
	if (it != m_eventListeners.end())
		dynamic_cast<MouseFocusEventListener*>(it->second.get())->registerCallback(callback);
}