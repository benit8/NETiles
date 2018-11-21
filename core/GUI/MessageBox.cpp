/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / MessageBox.cpp
*/

#include "MessageBox.hpp"
#include "../Window.hpp"
#include "GUI.hpp"
#include <algorithm>
#include <cctype>

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

////////////////////////////////////////////////////////////////////////////////

MessageBox::MessageBox()
: MessageBox("", {})
{
}

MessageBox::MessageBox(const std::string &text, const std::vector<ButtonType> &buttons)
: Modal()
, m_font(GUI::getDefaultFont())
, m_rawText(text)
, m_text("", m_font, 18)
{
	m_eventDispatcher.onResize(BIND1(MessageBox::updatePositions));
	m_eventDispatcher.onKeyDown(BIND(Modal::close), sf::Keyboard::Escape);

	m_back.setBackgroundColor(sf::Color(0, 0, 0, 150));

	m_zone.setFillColor(sf::Color::Black);
	m_zone.setOutlineThickness(1);

	constructGeometry(buttons);
}

MessageBox::~MessageBox()
{
	for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it)
		delete *it;
}

////////////////////////////////////////////////////////////////////////////////

void MessageBox::draw(sf::RenderTarget &rt)
{
	m_back.draw(rt);
	rt.draw(m_zone);

	m_text.move(getPosition());
	rt.draw(m_text);
	m_text.move(-getPosition());
}

////////////////////////////////////////////////////////////////////////////////

void MessageBox::updatePositions(sf::Vector2u size)
{
	m_back.setSize({size.x, size.y});

	setPosition({
		(size.x - width()) / 2.f,
		(size.y - height()) / 2.f
	});
}

void MessageBox::constructGeometry(const std::vector<ButtonType> &buttons)
{
	unsigned maxWidth = Window::getMainWindow() ? Window::getMainWindow()->width() : sf::VideoMode::getDesktopMode().width;
	maxWidth *= 0.75f;

	float w = 0;
	for (size_t i = 0; i < m_rawText.length(); ++i) {
		w += m_font.getGlyph(m_rawText[i], 18, false).advance;
		if (w > maxWidth - 60) {
			for (; !isspace(m_rawText[i]); --i);
			m_rawText[i] = '\n';
			w = 0;
		}
	}

	m_text.setString(m_rawText);
	m_text.setPosition(30, 20);

	sf::FloatRect textBounds = m_text.getLocalBounds();
	setSize(
		std::max(400.f, std::max(textBounds.width + 60, constructButtons(buttons))),
		std::max(200.f, textBounds.height + 102)
	);

	updatePositions(Window::getMainWindow()->getSize());

	w = 0;
	for (auto it = m_buttons.begin(); it != m_buttons.end(); ++it) {
		Button *b = *it;
		w += b->width() + 20;
		b->setPosition(width() - w, height() - b->height() - 20);
	}
}

float MessageBox::constructButtons(const std::vector<ButtonType> &buttons)
{
	if (buttons.empty())
		return 0;

	float w = 0;
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		Button *b = createButton(*it);
		w += b->width() + 20;
		m_buttons.push_front(b);
	}

	return w + 20;
}

Button *MessageBox::createButton(ButtonType type)
{
	Button *button = new Button;
	addChild(button);

	switch (type) {
		case Ok:
			button->setLabel("Ok", true);
			button->onClick.connect(this, &MessageBox::emitAccept);
			break;
		case Save:
			button->setLabel("Save", true);
			button->onClick.connect(this, &MessageBox::emitAccept);
			break;
		case SaveAll:
			button->setLabel("SaveAll", true);
			button->onClick.connect(this, &MessageBox::emitAccept);
			break;
		case Open:
			button->setLabel("Open", true);
			button->onClick.connect(this, &MessageBox::emitAccept);
			break;
		case Yes:
			button->setLabel("Yes", true);
			button->onClick.connect(this, &MessageBox::emitAccept);
			break;
		case YesToAll:
			button->setLabel("YesToAll", true);
			button->onClick.connect(this, &MessageBox::emitAccept);
			break;
		case No:
			button->setLabel("No", true);
			button->onClick.connect(this, &MessageBox::emitReject);
			break;
		case NoToAll:
			button->setLabel("NoToAll", true);
			button->onClick.connect(this, &MessageBox::emitReject);
			break;
		case Abort:
			button->setLabel("Abort", true);
			button->onClick.connect(this, &MessageBox::emitReject);
			break;
		case Retry:
			button->setLabel("Retry", true);
			button->onClick.connect(this, &MessageBox::emitAccept);
			break;
		case Ignore:
			button->setLabel("Ignore", true);
			button->onClick.connect(this, &MessageBox::emitAccept);
			break;
		case Close:
			button->setLabel("Close", true);
			button->onClick.connect(this, &MessageBox::emitReject);
			break;
		case Cancel:
			button->setLabel("Cancel", true);
			button->onClick.connect(this, &MessageBox::emitReject);
			break;
		case Discard:
			button->setLabel("Discard", true);
			button->onClick.connect(this, &MessageBox::emitClose);
			break;
		case Help:
			button->setLabel("Help", true);
			button->onClick.connect(this, &MessageBox::emitHelp);
			break;
		case Apply:
			button->setLabel("Apply", true);
			button->onClick.connect(this, &MessageBox::emitAccept);
			break;
		case Reset:
			button->setLabel("Reset", true);
			button->onClick.connect(this, &MessageBox::emitReset);
			break;
		case RestoreDefaults:
			button->setLabel("RestoreDefaults", true);
			button->onClick.connect(this, &MessageBox::emitReset);
			break;
	}

	return button;
}

////////////////////////////////////////////////////////////////////////////////

void MessageBox::emitAccept(sf::Vector2i)
{
	onAccept.emit();
	Modal::close();
}

void MessageBox::emitReject(sf::Vector2i)
{
	onReject.emit();
	Modal::close();
}

void MessageBox::emitClose(sf::Vector2i)
{
	onClose.emit();
	Modal::close();
}

void MessageBox::emitHelp(sf::Vector2i)
{
	onHelp.emit();
}

void MessageBox::emitReset(sf::Vector2i)
{
	onReset.emit();
}

////////////////////////////////////////////////////////////////////////////////

}