#include "menu.h"

#include "Functions.h"


Menu::Menu() // constructeur par d�faut
{
    //Conditions initiales de la taille de l'�cran
    int SCREEN_WIDTH = 816 ;
    int SCREEN_LENGTH = 816 ;
    //Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO);
    //Initialisation de la fenetre du menu
    SDL_Surface *menu = 0 ;
    //Pr�paration d'un �v�nement
    SDL_Event event;
    //Initialisation des positions initiales
    _positionMenu.x = 0;
    _positionMenu.y = 0;
    //Cr�ation de l'�cran
    _screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_LENGTH, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //Met le titre de la fenetre
    SDL_WM_SetCaption("Bomby", NULL);
    //Charge l'image du menu
    menu = load_image("pack_images_sdz/Menu_Bomby.bmp");
    //Affiche l'image menu sur l'�cran
    SDL_BlitSurface(menu, NULL, _screen, &_positionMenu);
    //Actualisation de l'�cran
    SDL_Flip(_screen);
    //Initialement, le son est allum�
    _isSound = true ;

    //et le jeu est en marche
    bool game_on = true;
    //Tant que le jeu est en marche
    while (game_on)
    {
        //On regarde les �v�nements suivants
        SDL_WaitEvent(&event);
        //Selon le type de l'�v�nement
        switch(event.type)
        {
            //Evenement de type quitter
            case SDL_QUIT:
                game_on = 0;
                break;
           //Evenement de type on appuie sur une touche
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: //  arr�t du jeu
                        game_on = 0;
                        break;
                    case SDLK_a: //  arr�t du jeu
                        game_on = 0;
                        break;
                    //Gestions des autres cas
                    //D�marre un jeu
                    case SDLK_p:
                    {
                        //Cr�ation d'une nouvelle carte
                        SDL_FillRect(_screen, NULL, SDL_MapRGB(_screen->format, 255, 255, 255));
                        Map* mappi = new Map(_screen, _isSound) ;
                        //On lance le jeu
                        mappi->game_on() ;
                        //Actualisation de l'�cran
                        SDL_Flip(_screen);
                        break;
                    }
                    //On affiche les r�gles
                    case SDLK_r:
                        menuRules();
                        break;
                    //On affiche les options
                    case SDLK_o:
                        menuOptions();
                        break;
                    default:
                        break;
                }
            }
            default:
            {
                break ;
            }

        }

        //Affichage du menu
       SDL_FillRect(_screen, NULL, SDL_MapRGB(_screen->format, 0, 0, 0));
       SDL_BlitSurface(menu, NULL, _screen, &_positionMenu);
       SDL_Flip(_screen);
    }

    //Lib�ration de la m�moire
    SDL_FreeSurface(menu);
    SDL_FreeSurface(_screen);

    SDL_Quit();
}

//Menu o� il y'a les r�gles. Idem que pr�c�demment pour l'affichage et la gestion des �venements
void Menu::menuRules()
{
    bool rulesOn = true ;
    SDL_Event event ;
    while (rulesOn)
    {
        SDL_Surface* imageRules = SDL_LoadBMP("pack_images_sdz/Menu_Rules.bmp");
        SDL_BlitSurface(imageRules, NULL, _screen, &_positionMenu);
        SDL_Flip(_screen);
        SDL_WaitEvent(&event);

        switch(event.type)
        {
        case SDL_QUIT:
        {
            rulesOn = 0;
            break;
        }
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            {
                rulesOn = 0;
                break;
            }
            default:
                break;
            }
        }
        default:
            break;
        }
    }
}

//Menu o� il y'a les options. Idem que pr�c�demment pour l'affichage et la gestion des �venements
void Menu::menuOptions()
{
    bool optionsOn = true ;
    SDL_Event event ;
    while (optionsOn)
    {
        SDL_Surface* imageRules = SDL_LoadBMP("pack_images_sdz/Menu_options.bmp");
        SDL_BlitSurface(imageRules, NULL, _screen, &_positionMenu);
        SDL_Flip(_screen);
        SDL_WaitEvent(&event);

        switch(event.type)
        {
        case SDL_QUIT:
        {
            optionsOn = 0;
            break;
        }
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            {
                optionsOn = 0;
                break;
            }
            case SDLK_o:
            {
                _isSound = true ;
                break;
            }
            case SDLK_f:
            {
                _isSound = false ;
                break;
            }
            default:
                break;
            }
        }
        default:
            break;
        }
    }
}
