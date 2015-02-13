#include "Functions.h"



//Impl�mentation de la m�thode retournant la surface de l'image utilis�e avec en argument le nom du fichier
SDL_Surface* load_image(std::string filename)
{
    //Initailisation de la surfae de base
    SDL_Surface* loadedImage = NULL;

    //Initialisation de la surface optimis� � retourner
    SDL_Surface* optimizedImage = NULL;

    //Chargement de l'image � utiliser
    loadedImage = SDL_LoadBMP( filename.c_str() );

    //Test du chargement de l'image
    if( loadedImage != NULL )
    {
        //Optimisation de la surface charg�e
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Lib�ration de la surface de base
        SDL_FreeSurface( loadedImage );

        //Test de chargement de la surface optimis�e
        if( optimizedImage != NULL )
        {
            //On fixe les couleurs des images charg�es
			//Le triplet ()  199, 207, 0  correspond � la couleur des images qui ne sera pas affich�e
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 255,242,0 ) );
        }
    }

    //La m�thode retourne l'image optimis�e
    return optimizedImage;
}



