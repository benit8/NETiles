/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / Widget.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class Widget;
}

////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../EventHandler.hpp"
#include "../Window.hpp"
#include "GUI.hpp"
#include "Signal.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class Widget
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
	Widget();
	virtual ~Widget() = default;

public: // Methods
	virtual void handleEvent(sf::Event &e);
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
	bool isMouseHover(sf::Vector2i mouse);
	bool isMouseHover(sf::Vector2f mouse);

private: // Callbacks
	void callback_mouseMove(sf::Vector2i pos, sf::Vector2i offset);
	void callback_mouseDown(sf::Mouse::Button btn, sf::Vector2i pos);
	void callback_mouseUp(sf::Mouse::Button btn, sf::Vector2i pos);
	void callback_text(unsigned unicode);

public: // Getters & Setters
	const Widget *getParent() const;
	const std::vector<Widget *> &getChildren() const;
	void setParent(Widget *parent);
	void addChild(Widget *child);

	bool isHovered() const;
	bool isClicked() const;
	bool isDragged() const;
	bool isHoverable() const;
	bool isClickable() const;
	bool isDraggable() const;
	void setMode(Mode mode);

	sf::FloatRect getZone() const;
	void setZone(const sf::FloatRect &zone);

	sf::Vector2f getPosition() const;
	void setPosition(float offsetX, float offsetY);
	void setPosition(const sf::Vector2f &position);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f &offset);

	sf::Vector2f getSize() const;
	void setSize(float width, float height);
	void setSize(const sf::Vector2f &size);
	void setWidth(float width);
	void setHeight(float height);

protected:
	Widget *m_parent;
	std::vector<Widget *> m_children;

	State m_state;
	Mode m_mode;
	sf::FloatRect m_zone;

	EventHandler m_eventDispatcher;
};

}