#ifndef FOOD_H
#define FOOD_H
#include <random>
#include <iostream>
#include "main.hpp"
#include "constante.hpp"
#include "textures.h"

class food
{
private:
    int pos_x;
    int pos_y;

    sf::Texture texture;
    sf::Sprite sprite;

    sf::Color couleur;

public:
    void restawn();
    void print_loc();
    void set_couleur();
    int getPosX();
    int getPosY();
    sf::Color get_Couleur();
    sf::Sprite get_Sprite();
    food(int x)
    {

        texture.loadFromMemory(apple_png, apple_png_len);
    };
};

int randomInt(int min, int max);

#endif