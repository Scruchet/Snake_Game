#include "food.hpp"

using namespace std;

void food::restawn()
{
    pos_x = SAUT * randomInt(0, TAILLE - 1);
    pos_y = SAUT * randomInt(0, TAILLE - 1);
    sprite.setTexture(texture);
    sprite.setPosition(pos_x, pos_y);
    this->set_couleur();
}

void food::print_loc()
{
    cout << "Position X : " << pos_x << endl;
    cout << "Position Y : " << pos_y << endl;
}

int food::getPosX()
{
    return pos_x;
}

int food::getPosY()
{
    return pos_y;
}

void food::set_couleur()
{
    sf::Color couleur_tmp(randomInt(0, 255),randomInt(0, 255),randomInt(0, 255),255);
    couleur = sprite.getColor();
    sprite.setColor(couleur_tmp);
}

sf::Color food::get_Couleur()
{
    return couleur;
}

sf::Sprite food::get_Sprite()
{
    return sprite;
}



int randomInt(int min, int max)
{
    static random_device rd;  // Graine aléatoire (unique)
    static mt19937 gen(rd()); // Générateur Mersenne Twister
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}
