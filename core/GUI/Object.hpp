/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Object.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Object;
}

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "GUI.hpp"
#include "Signal.hpp"
#include "../EventHandler.hpp"
#include "../Window.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Object
{
public: // Typedefs & Enums
	enum State {
		Normal,
		Hovered,
		Clicked,
		Dragged
	};

	enum Mode {
		Visible,
		Hoverable,
		Clickable,
		Draggable
	};

public: // Con/Destructor
	Object();
	virtual ~Object() = default;

public: // Methods
	void handleEvent(sf::Event &e);
	void render(sf::RenderTarget &rt);
	virtual void draw(sf::RenderTarget &rt) {}

public: // Signals
	Signal<sf::Vector2i> onHoverIn;
	Signal<sf::Vector2i> onHoverOut;
	Signal<sf::Mouse::Button, sf::Vector2i> onClick;
	Signal<sf::Mouse::Button, sf::Vector2i> onRelease;
	Signal<sf::Vector2i, sf::Vector2i> onDrag;
	Signal<sf::Vector2i> onDragBegin;
	Signal<sf::Vector2i> onDragEnd;

private:
	bool doesMouseHover(sf::Vector2i mousePos = sf::Mouse::getPosition(*Window::getMainWindow()));

private: // Callbacks
	void callback_mouseMove(sf::Vector2i pos, sf::Vector2i offset);
	void callback_mouseDown(sf::Mouse::Button btn, sf::Vector2i pos);
	void callback_mouseUp(sf::Mouse::Button btn, sf::Vector2i pos);
	void callback_text(unsigned unicode);

public: // Getters & Setters
	const Object *getParent() const;
	const std::vector<Object *> &getChildren() const;
	void setParent(Object *parent);
	void addChild(Object *child);

	bool isHovered() const;
	bool isClicked() const;
	bool isDragged() const;
	bool isHoverable() const;
	bool isClickable() const;
	bool isDraggable() const;
	void setMode(Mode mode);

	sf::Vector2i getPosition() const;
	int getLeft() const;
	int getTop() const;
	void setPosition(int offsetX, int offsetY);
	void setPosition(const sf::Vector2i &position);
	void move(int offsetX, int offsetY);
	void move(const sf::Vector2i &offset);

	sf::Vector2u getSize() const;
	unsigned getWidth() const;
	unsigned getHeight() const;
	void setSize(unsigned width, unsigned height);
	void setSize(const sf::Vector2u &size);
	void setWidth(unsigned width);
	void setHeight(unsigned height);

protected:
	Object *m_parent;
	std::vector<Object *> m_children;

	State m_state;
	Mode m_mode;
	sf::Vector2i m_position;
	sf::Vector2u m_size;

	EventHandler m_eventDispatcher;
};

}