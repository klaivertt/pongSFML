#ifndef INPUT_H
#define INPUT_H
#include <SFML/Graphics.hpp>
using namespace sf;

class Input
{
	struct Button { bool left, right, up, down, espcape; };

public:
	// Proto du constructeur
	Input();

	// Proto
	Button GetButton(void) const;
	void InputHandler(Event event, RenderWindow& window);

private:
	Button button;
};
#endif