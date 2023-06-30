#include "input.h"

// Constructeur

Input::Input()
{
	button.left = button.right = button.up = button.down = button.espcape = false;
}

// Fonction qui acc�de � button (struc) et donne l'info de private
Input::Button Input::GetButton(void) const
{
	return button;
}

// Foction de gestion des inputs

void Input::InputHandler(Event event, RenderWindow& window)
{
	// Fermer La fen�tre si on clique sur la croix
	if (event.type == Event::Closed)
	{
		// On ferme la fen�tre
		window.close();
	}

	// Gestion des inputs (appuy�s)
	if (event.type == Event::KeyPressed)
	{
		switch (event.key.code) // Code de la touche utilis�e
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

	// Touche relach�e
	if (event.type == Event::KeyReleased)
	{
		// Touche relach�e
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