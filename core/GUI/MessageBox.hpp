/*
** EPITECH PROJECT, 2018
** NETiles
** File description:
** GUI / MessageBox.hpp
*/

#pragma once

////////////////////////////////////////////////////////////////////////////////

namespace GUI {
	class MessageBox;
}

////////////////////////////////////////////////////////////////////////////////

#include "Modal.hpp"
#include "Button.hpp"

#include <map>
#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace GUI
{

class MessageBox : public Modal
{
public:
	enum ButtonType
	{
		Invalid,
		Ok,
		Save,
		SaveAll,
		Open,
		Yes,
		YesToAll,
		No,
		NoToAll,
		Abort,
		Retry,
		Ignore,
		Close,
		Cancel,
		Discard,
		Help,
		Apply,
		Reset,
		RestoreDefaults,

		Count
	};

public:
	MessageBox();
	MessageBox(const std::string &text, const std::vector<ButtonType> &buttons);
	~MessageBox() override;

	void draw(sf::RenderTarget &target) override;

private:
	void constructGeometry(const std::vector<ButtonType> &buttons);
	float constructButtons(const std::vector<ButtonType> &buttons);
	Button *createButton(ButtonType type);

	void emitAccept(sf::Vector2i);
	void emitReject(sf::Vector2i);
	void emitClose(sf::Vector2i);
	void emitHelp(sf::Vector2i);
	void emitReset(sf::Vector2i);

public:
	Signal<> onAccept;
	Signal<> onReject;
	Signal<> onClose;
	Signal<> onHelp;
	Signal<> onReset;

private:
	sf::Font m_font;
	std::string m_rawText;
	sf::Text m_text;
	std::list<Button *> m_buttons;
};

}