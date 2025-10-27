#include "snake.hpp"

void snake::avancer()
{
    int taille_corps = corps.size();
    last_position = corps[taille_corps - 1];

    if (taille_corps > 1)
    {
        for (int i = taille_corps - 1; i > 0; i--)
        {
            corps[i] = corps[i - 1];
        }
    }

    // En fonction de la direction, faire avancer la tete
    switch (direction)
    {
    case DIR_BAS:
        corps[0].y += SAUT;
        break;
    case DIR_HAUT:
        corps[0].y -= SAUT;
        break;
    case DIR_GAUCHE:
        corps[0].x -= SAUT;
        break;
    case DIR_DROITE:
        corps[0].x += SAUT;
        break;
    }
}

int snake::get_direction()
{
    return direction;
}

std::vector<struct_corps> snake::get_corps()
{
    return corps;
}

void snake::set_direction(int direction)
{
    this->direction = direction;
}

void snake::manger()
{
    corps.push_back(last_position);
    sprite.push_back(sf::Sprite());
}

void snake::print_info()
{
    switch (direction)
    {
    case DIR_BAS:
        std::cout << "Direction : BAS" << std::endl;
        break;
    case DIR_HAUT:
        std::cout << "Direction : HAUT" << std::endl;
        break;
    case DIR_GAUCHE:
        std::cout << "Direction : GAUCHE" << std::endl;
        break;
    case DIR_DROITE:
        std::cout << "Direction : DROITE" << std::endl;
        break;
    default:
        std::cout << "Erreur, direction " << std::endl;
        break;
    }
    std::cout << "Corps :" << std::endl;
    for (int i = 0; i < corps.size(); i++)
    {
        std::cout << "[ " << corps[i].x << " " << corps[i].y << " ] " << std::endl;
    }
    std::cout << "Derniere position : [ " << last_position.x << " " << last_position.y << " ]" << std::endl;
}

void snake::put_texture(food pomme)
{
    sf::Color couleur_pomme = pomme.get_Couleur();
    int taille = corps.size();
    if (taille == 0)
        return;
    if (sprite.size() < taille)
        sprite.resize(taille);

    // --- TÊTE ---
    sprite[0].setPosition(corps[0].x, corps[0].y);
    switch (direction)
    {
    case DIR_BAS:
        sprite[0].setTexture(textures["head_down"]);
        break;
    case DIR_HAUT:
        sprite[0].setTexture(textures["head_up"]);
        break;
    case DIR_GAUCHE:
        sprite[0].setTexture(textures["head_left"]);
        break;
    case DIR_DROITE:
        sprite[0].setTexture(textures["head_right"]);
        break;
    }
    if (COLORFUL_SNAKE)
    {
        sprite[0].setColor(couleur_pomme);
    }
    // --- CORPS ---
    if (taille > 2)
    {
        for (int i = 1; i < taille - 1; ++i)
        {
            struct_corps avant = corps[i - 1];
            struct_corps actuel = corps[i];
            struct_corps apres = corps[i + 1];

            if (avant.x == actuel.x && apres.x == actuel.x)
                sprite[i].setTexture(textures["body_vertical"]);
            else if (avant.y == actuel.y && apres.y == actuel.y)
                sprite[i].setTexture(textures["body_horizontal"]);
            else if ((avant.x < actuel.x && apres.y < actuel.y) || (apres.x < actuel.x && avant.y < actuel.y))
                sprite[i].setTexture(textures["body_topleft"]);
            else if ((avant.x > actuel.x && apres.y < actuel.y) || (apres.x > actuel.x && avant.y < actuel.y))
                sprite[i].setTexture(textures["body_topright"]);
            else if ((avant.x < actuel.x && apres.y > actuel.y) || (apres.x < actuel.x && avant.y > actuel.y))
                sprite[i].setTexture(textures["body_bottomleft"]);
            else if ((avant.x > actuel.x && apres.y > actuel.y) || (apres.x > actuel.x && avant.y > actuel.y))
                sprite[i].setTexture(textures["body_bottomright"]);
            sprite[i].setPosition(corps[i].x, corps[i].y);
            if (COLORFUL_SNAKE)
            {
                sprite[i].setColor(couleur_pomme);
            }
        }
    }
    // --- QUEUE ---
    if (taille > 1)
    {
        struct_corps last = corps[taille - 1];
        struct_corps prev = corps[taille - 2];

        if (last.x > prev.x)
            sprite[taille - 1].setTexture(textures["tail_right"]);
        else if (last.x < prev.x)
            sprite[taille - 1].setTexture(textures["tail_left"]);
        else if (last.y > prev.y)
            sprite[taille - 1].setTexture(textures["tail_down"]);
        else
            sprite[taille - 1].setTexture(textures["tail_up"]);
        sprite[taille - 1].setPosition(corps[taille - 1].x, corps[taille - 1].y);
        if (COLORFUL_SNAKE)
        {
            sprite[taille - 1].setColor(couleur_pomme);
        }
    }
}

int snake::get_taille()
{
    return sprite.size();
}

std::vector<sf::Sprite> snake::get_sprite()
{
    return sprite;
}
