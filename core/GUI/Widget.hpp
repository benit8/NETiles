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

#include <list>

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
		Normal	= (1 << 0),
		Hovered	= (1 << 1),
		Clicked	= (1 << 2),
		Dragged	= (1 << 3)
	};

	enum Mode {
		Visible,
		Hoverable,
		Clickable,
		Draggable
	};

public: // Con/Destructor
	Widget();
	virtual ~Widget();

public: // Methods
	virtual void handleEvent(sf::Event &e);
	virtual void render(sf::RenderTarget &rt);
	virtual void draw(sf::RenderTarget &rt) {}

public: // Signals
	Signal<sf::Vector2i> onHoverIn;
	Signal<sf::Vector2i> onHoverOut;
	Signal<sf::Mouse::Button, sf::Vector2i> onClick;
	Signal<sf::Mouse::Button, sf::Vector2i> onRelease;
	Signal<sf::Vector2i, sf::Vector2i> onDrag;
	Signal<sf::Vector2i> onDragBegin;
	Signal<sf::Vector2i> onDragEnd;
	Signal<unsigned> onTextInput;

private:
	bool isMouseHover(sf::Vector2i mouse);
	bool isMouseHover(sf::Vector2f mouse);
	sf::Vector2f getParentOffset();

private: // Callbacks
	void callback_mouseMove(sf::Vector2i pos, sf::Vector2i offset);
	void callback_mouseDown(sf::Mouse::Button btn, sf::Vector2i pos);
	void callback_mouseUp(sf::Mouse::Button btn, sf::Vector2i pos);
	void callback_text(unsigned unicode);

public: // Getters & Setters
	const Widget *getParent() const;
	const std::list<Widget *> &getChildren() const;
	void setParent(Widget *parent);
	void addChild(Widget *child);
	void removeChild(Widget *child);

	virtual bool isHovered() const;
	virtual bool isClicked() const;
	virtual bool isDragged() const;
	virtual bool isHoverable() const;
	virtual bool isClickable() const;
	virtual bool isDraggable() const;
	virtual void setMode(Mode mode);

	virtual sf::FloatRect getZone() const;
	virtual void setZone(const sf::FloatRect &zone);

	virtual sf::Vector2f getPosition() const;
	virtual float getLeft() const;
	virtual float getTop() const;
	virtual void setPosition(const sf::Vector2f &position);
	virtual void move(const sf::Vector2f &offset);
	virtual void setPosition(float offsetX, float offsetY);
	virtual void move(float offsetX, float offsetY);

	virtual sf::Vector2f getSize() const;
	virtual float getWidth() const;
	virtual float getHeight() const;
	virtual void setSize(const sf::Vector2f &size);
	virtual void setSize(float width, float height);
	virtual void setWidth(float width);
	virtual void setHeight(float height);

protected:
	Widget *m_parent;
	std::list<Widget *> m_children;

	int m_state;
	int m_mode;
	sf::FloatRect m_zone;

	EventHandler m_eventDispatcher;
};

}