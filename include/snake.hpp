#ifndef SNAKE_H
#define SNAKE_H
#include <string>
#include <vector>

#include "textures.h"
#include "food.hpp"
#include "constante.hpp"

struct struct_corps
{
    int x;
    int y;
};

class snake
{
private:
    int direction = DIR_DROITE;
    std::vector<struct_corps> corps;
    struct_corps last_position;
    std::vector<sf::Sprite> sprite;
    std::map<std::string, sf::Texture> textures;

public:
    void avancer();
    int get_direction();
    void set_direction(int direction);
    void manger();
    void print_info();
    void put_texture(class food pomme);
    int get_taille();
    std::vector<struct_corps> get_corps();
    std::vector<sf::Sprite> get_sprite();
    snake(int x, int y)
    {
        struct_corps tmp;
        tmp.x = x;
        tmp.y = y;
        corps.push_back(tmp);
        last_position.x = 0;
        last_position.y = 0;
        textures["head_up"].loadFromMemory(head_up_png, head_up_png_len);
        textures["head_down"].loadFromMemory(head_down_png, head_down_png_len);
        textures["head_left"].loadFromMemory(head_left_png, head_left_png_len);
        textures["head_right"].loadFromMemory(head_right_png, head_right_png_len);

        textures["body_vertical"].loadFromMemory(body_vertical_png, body_vertical_png_len);
        textures["body_horizontal"].loadFromMemory(body_horizontal_png, body_horizontal_png_len);
        textures["body_topleft"].loadFromMemory(body_topleft_png, body_topleft_png_len);
        textures["body_topright"].loadFromMemory(body_topright_png, body_topright_png_len);
        textures["body_bottomleft"].loadFromMemory(body_bottomleft_png, body_bottomleft_png_len);
        textures["body_bottomright"].loadFromMemory(body_bottomright_png, body_bottomright_png_len);

        textures["tail_up"].loadFromMemory(tail_up_png, tail_up_png_len);
        textures["tail_down"].loadFromMemory(tail_down_png, tail_down_png_len);
        textures["tail_left"].loadFromMemory(tail_left_png, tail_left_png_len);
        textures["tail_right"].loadFromMemory(tail_right_png, tail_right_png_len);
    }
};

#endif