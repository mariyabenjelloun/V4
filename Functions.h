#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

// Fonction servant � charger l'image qui est � l'adresse donn�e par filename. Elle renvoit un pointeur vers une SDL Surface qui a �t� cr��.
SDL_Surface* load_image(std::string filename) ;

#endif //FUNCTIONS_H_INCLUDED
