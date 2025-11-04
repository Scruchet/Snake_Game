#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constante.hpp"
#include "snake.hpp"
#include "textures.h"


enum EcranFinResultat { QuitterJeu, RedemarrerJeu };


void gestion_fleches(sf::Event event, class snake *personnage, int *changement_dir, bool* pause);
void display_sprites(sf::RenderWindow *window, class snake joueur, class food pomme);
void display_fond(sf::RenderWindow *window);
void collision(class snake *joueur, class food *pomme, int *jeu);
enum EcranFinResultat afficherEcranFin(sf::RenderWindow &window, int score);
void jeu(sf::RenderWindow *window, class snake *personnage, class food *pomme, int *redemarre);
#endif