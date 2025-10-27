#include "game.hpp"

void gestion_fleches(sf::Event event, class snake *personnage, int *changement_dir)
{
    if (*changement_dir)
        return;
    // Détection d’appui d’une touche
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case sf::Keyboard::Left:
            if (personnage->get_direction() != DIR_DROITE)
            {
                personnage->set_direction(DIR_GAUCHE);
                // std::cout << "Bouton Gauche pressé !" << std::endl;
            }
            break;
        case sf::Keyboard::Right:
            if (personnage->get_direction() != DIR_GAUCHE)
            {
                personnage->set_direction(DIR_DROITE);
                // std::cout << "Bouton Droite pressé !" << std::endl;
            }
            break;
        case sf::Keyboard::Up:
            if (personnage->get_direction() != DIR_BAS)
            {
                personnage->set_direction(DIR_HAUT);
                // std::cout << "Bouton Haut pressé !" << std::endl;
            }
            break;
        case sf::Keyboard::Down:
            if (personnage->get_direction() != DIR_HAUT)
            {
                personnage->set_direction(DIR_BAS);
                // std::cout << "Bouton Bas pressé !" << std::endl;
            }
            break;
        case sf::Keyboard::Space:
            personnage->manger();
            break;
        }
        *changement_dir = 1;
    }
}

void generer_arriere_plan(sf::RenderWindow *window)
{
    window->clear();
    int taille_carre = TAILLE_ECRAN / TAILLE;
    sf::RectangleShape carre(sf::Vector2f(taille_carre, taille_carre));
    for (int i = 0; i < TAILLE; i++)
    {
        int couleur = i % 2;
        for (int j = 0; j < TAILLE; j++)
        {
            couleur++;

            if (couleur % 2)
            {
                carre.setFillColor(sf::Color(173, 214, 68, 255));
            }
            else
            {
                carre.setFillColor(sf::Color(166, 209, 60, 255));
            }
            carre.setPosition(j * taille_carre, i * taille_carre);
            window->draw(carre);
        }
    }
}

void generer_arriere_plan_jpeg(const std::string &nom_fichier)
{
    int taille_carre = TAILLE_ECRAN / TAILLE;
    sf::RenderTexture renderTexture;
    if (!renderTexture.create(TAILLE_ECRAN, TAILLE_ECRAN))
    {
        std::cerr << "Erreur : impossible de créer la RenderTexture !" << std::endl;
        return;
    }

    sf::RectangleShape carre(sf::Vector2f(taille_carre, taille_carre));

    for (int i = 0; i < TAILLE; i++)
    {
        int couleur = i % 2;
        for (int j = 0; j < TAILLE; j++)
        {
            couleur++;
            if (couleur % 2)
                carre.setFillColor(sf::Color(173, 214, 68, 255));
            else
                carre.setFillColor(sf::Color(143, 180, 50, 255));

            carre.setPosition(j * taille_carre, i * taille_carre);
            renderTexture.draw(carre);
        }
    }

    renderTexture.display();

    sf::Image image = renderTexture.getTexture().copyToImage();

    if (!image.saveToFile(nom_fichier))
    {
        std::cerr << "Erreur : impossible d’enregistrer le fichier " << nom_fichier << std::endl;
        return;
    }

    std::cout << "✅ Image enregistrée avec succès : " << nom_fichier << std::endl;
}

void display_sprites(sf::RenderWindow *window, class snake joueur, class food pomme)
{
    std::vector<sf::Sprite> cp = joueur.get_sprite();
    for (int i = 0; i < joueur.get_taille(); i++)
    {
        window->draw(cp[i]);
    }
    sf::Sprite sprite = pomme.get_Sprite();
    window->draw(sprite);
}

void display_fond(sf::RenderWindow *window)
{
    sf::Texture texture;
    if (!texture.loadFromMemory(snake_png, snake_png_len))
    {
        // error...
        std::cout << "Erreur lors de l'application de l'arrière plan." << std::endl;
    }
    else
    {
        sf::Sprite sprite(texture);
        window->draw(sprite);
    }
}

void collision(class snake *joueur, class food *pomme, int *jeu)
{
    // Verifier si le joueur et la pomme sont sur la même case
    int taille = joueur->get_taille();
    std::vector<struct struct_corps> tmp = joueur->get_corps();
    for (int i = 0; i < taille; i++)
    {
        if (tmp[0].x == TAILLE_ECRAN || tmp[0].y == TAILLE_ECRAN || tmp[0].x < 0 || tmp[0].y < 0)
            *jeu = 0;
        if (tmp[i].x == pomme->getPosX() && tmp[i].y == pomme->getPosY())
        {
            joueur->manger();
            pomme->restawn();
            for (int j = 0; j < TAILLE - 1; j++)
            {
                if (tmp[j].x == pomme->getPosX() && tmp[j].y == pomme->getPosY()) // La pomme sur une partie du serpent
                {
                    pomme->restawn();
                    j = 0; // Recommencer la verification sur tout le corps
                }
            }
            return;
        }
        if (i != 0 && tmp[0].x == tmp[i].x && tmp[0].y == tmp[i].y)
        {
            *jeu = 0;
            return;
        }
    }
}

void jeu(sf::RenderWindow *window, class snake *personnage, class food *pomme, int *redemarrer)
{
    sf::Clock clock;
    float delai = 10;
    int resfresh = (int)delai;
    int jeu = 1;
    int changement_dir = 0;
    *redemarrer = 0;

    // generer_arriere_plan_jpeg("../textures/snake.png");
    while (window->isOpen() && jeu)
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            // Fermer la fenêtre
            if (event.type == sf::Event::Closed)
                window->close();
        }
        display_fond(window);
        display_sprites(window, *personnage, *pomme);
        if (clock.getElapsedTime().asMilliseconds() >= delai)
        {
            clock.restart();
            if (resfresh >= 10)
            {
                changement_dir = 0;
                resfresh = 0;
                personnage->avancer(); // <-- fonction à créer ou à appeler
                collision(personnage, pomme, &jeu);
                personnage->put_texture(*pomme); // met à jour les textures et positions
            }
            gestion_fleches(event, personnage, &changement_dir);
            resfresh++;
        }
        // generer_arriere_plan(&window);

        window->display();
    }
    *redemarrer = afficherEcranFin(*window, personnage->get_taille() - 1);
}

EcranFinResultat afficherEcranFin(sf::RenderWindow &window, int score)
{
    sf::Font font;
    if (!font.loadFromMemory(arial_ttf, arial_ttf_len))
    {
        std::cerr << "Erreur : impossible de charger la police !" << std::endl;
        return QuitterJeu;
    }
    sf::Text message("Fin du jeu !", font, 50);
    message.setFillColor(sf::Color::White);
    message.setPosition(150, 100);

    sf::Text texteScore("Score : " + std::to_string(score), font, 30);
    texteScore.setFillColor(sf::Color::Yellow);
    texteScore.setPosition(200, 200);

    sf::RectangleShape redemarrer({150, 60});
    redemarrer.setFillColor(sf::Color(100, 100, 255));
    redemarrer.setPosition(200, 300);

    sf::Text texteredemarrer("Redemarrer", font, 25);
    sf::FloatRect rBounds = texteredemarrer.getLocalBounds();
    texteredemarrer.setOrigin(rBounds.width / 2, rBounds.height / 2);
    texteredemarrer.setPosition(redemarrer.getPosition().x + 75, redemarrer.getPosition().y + 30);

    sf::RectangleShape quitter({150, 60});
    quitter.setFillColor(sf::Color(100, 100, 255));
    quitter.setPosition(500, 300);

    sf::Text textequitter("Quitter", font, 25);
    sf::FloatRect qBounds = textequitter.getLocalBounds();
    textequitter.setOrigin(qBounds.width / 2, qBounds.height / 2);
    textequitter.setPosition(quitter.getPosition().x + 75, quitter.getPosition().y + 30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                return QuitterJeu;

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                redemarrer.setFillColor(redemarrer.getGlobalBounds().contains(mousePos.x, mousePos.y) ? sf::Color(150, 150, 255) : sf::Color(100, 100, 255));
                quitter.setFillColor(quitter.getGlobalBounds().contains(mousePos.x, mousePos.y) ? sf::Color(150, 150, 255) : sf::Color(100, 100, 255));
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (redemarrer.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    return RedemarrerJeu;
                if (quitter.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    return QuitterJeu;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(message);
        window.draw(texteScore);
        window.draw(redemarrer);
        window.draw(texteredemarrer);
        window.draw(quitter);
        window.draw(textequitter);
        window.display();
    }

    return QuitterJeu;
}
