#include "input.h"

// Constructeur

Input::Input()
{
	button.left = button.right = button.up = button.down = button.espcape = false;
}

// Fonction qui accède à button (struc) et donne l'info de private
Input::Button Input::GetButton(void) const
{
	return button;
}

// Foction de gestion des inputs

void Input::InputHandler(Event event, RenderWindow& window)
{
	// Fermer La fenêtre si on clique sur la croix
	if (event.type == Event::Closed)
	{
		// On ferme la fenêtre
		window.close();
	}

	// Gestion des inputs (appuyés)
	if (event.type == Event::KeyPressed)
	{
		switch (event.key.code) // Code de la touche utilisée
		{
		case Keyboard::Escape:
			button.espcape = true;
			break;

		case Keyboard::Down:
			button.down = true;
			break;

		case Keyboard::Up:
			button.up = true;
			break;
		default :
			break;
		}
	}

	// Touche relachée
	if (event.type == Event::KeyReleased)
	{
		// Touche relachée
		switch (event.key.code) 
		{
		case Keyboard::Escape:
			button.espcape = false;
			break;



		case Keyboard::Down:
			button.down = false;
			break;

		case Keyboard::Up:
			button.up = false;
			break;
		default:
			break;
		}
	}

}