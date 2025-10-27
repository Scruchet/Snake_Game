#include <SFML/Graphics.hpp>
#include <iostream>
#include "main.hpp"

int main()
{
    int redemarrer = 1;
    while (redemarrer)
    {
        sf::RenderWindow window(sf::VideoMode(TAILLE_ECRAN, TAILLE_ECRAN), "Snake");
        window.setFramerateLimit(60);
        snake personnage(TAILLE_ECRAN / 2, TAILLE_ECRAN / 2);
        food pomme(0);
        pomme.restawn();
        redemarrer = 0;
        jeu(&window, &personnage, &pomme, &redemarrer);
    }
    return 0;
}
