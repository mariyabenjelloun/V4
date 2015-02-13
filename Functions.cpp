#include "Functions.h"



//Implémentation de la méthode retournant la surface de l'image utilisée avec en argument le nom du fichier
SDL_Surface* load_image(std::string filename)
{
    //Initailisation de la surfae de base
    SDL_Surface* loadedImage = NULL;

    //Initialisation de la surface optimisé à retourner
    SDL_Surface* optimizedImage = NULL;

    //Chargement de l'image à utiliser
    loadedImage = SDL_LoadBMP( filename.c_str() );

    //Test du chargement de l'image
    if( loadedImage != NULL )
    {
        //Optimisation de la surface chargée
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Libération de la surface de base
        SDL_FreeSurface( loadedImage );

        //Test de chargement de la surface optimisée
        if( optimizedImage != NULL )
        {
            //On fixe les couleurs des images chargées
			//Le triplet ()  199, 207, 0  correspond à la couleur des images qui ne sera pas affichée
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 255,242,0 ) );
        }
    }

    //La méthode retourne l'image optimisée
    return optimizedImage;
}



