// Includes

#include <iostream>
#include <SFML/Graphics.hpp>
#include <random> // Inclure la biblioth�que pour la g�n�ration de nombres al�atoires
#include "input.h"

// Constantes du programme
const int WIN_WIDTH = 1800;
const int WIN_HEIGHT = 900;

// Namespaces
using namespace sf;
using namespace std;

// Prototypes
void SetText(Text& txt, String str);
void CheckBtn();