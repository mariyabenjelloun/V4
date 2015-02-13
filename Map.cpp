#include "Map.h"

#include "Bonus.h"
#include "Bomby.h"
#include "Bomb.h"
#include "Fire.h"
#include "Case.h"
#include "Functions.h"

#include <time.h>

//Constructeur
Map::Map(SDL_Surface* screen, bool isSound)
{
//Cr�ation du premier joueur et de toutes ses images
     _player1 = new Bomby(screen,1,1) ;
    SDL_Surface* imagePlayer1D = load_image("pack_images_sdz/Mario_D.bmp");
    SDL_Surface* imagePlayer1R = load_image("pack_images_sdz/Mario_R.bmp");
    SDL_Surface* imagePlayer1U = load_image("pack_images_sdz/Mario_U.bmp");
    SDL_Surface* imagePlayer1L = load_image("pack_images_sdz/Mario_L.bmp");
    _player1->setImageD(imagePlayer1D) ;
    _player1->setImageR(imagePlayer1R) ;
    _player1->setImageU(imagePlayer1U) ;
    _player1->setImageL(imagePlayer1L) ;
//Cr�ation du deuxi�me joueur et de toutes ses images
    _player2 = new Bomby(screen,13,13) ;
    SDL_Surface* imagePlayer2D = load_image("pack_images_sdz/Luigi_D.bmp");
    SDL_Surface* imagePlayer2R = load_image("pack_images_sdz/Luigi_R.bmp");
    SDL_Surface* imagePlayer2U = load_image("pack_images_sdz/Luigi_U.bmp");
    SDL_Surface* imagePlayer2L = load_image("pack_images_sdz/Luigi_L.bmp");
    _player2->setImageD(imagePlayer2D) ;
    _player2->setImageR(imagePlayer2R) ;
    _player2->setImageU(imagePlayer2U) ;
    _player2->setImageL(imagePlayer2L) ;

//Initialisation de la cr�ation de nombre al�atoire
    srand(time(NULL));
//Possibilit� de laisser la touche enfonc�e et d'avoir des �v�nements comme si on appuyait sur la touche
    SDL_EnableKeyRepeat(200,200);
//Reserve les canaux de son
    Mix_AllocateChannels(32);
//Renvoie un message d'erreur s'il n'arrive pas � ouvrir le son
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
        printf("%s", Mix_GetError());
    }
    isSound = true ;
//Si on a mis l'option son, le son va �tre charg�
    if (isSound)
    {
        _sound = Mix_LoadWAV("pack_images_sdz/explosion.wav");
        //Cr�ation du pointeur de type Mix_Music
        _music = Mix_LoadMUS("pack_images_sdz/SuperMarioBros.mp3"); //Chargement de la musique
        Mix_PlayMusic(_music, -1); //Jouer infiniment la musique
    }
    else
    {
        _sound = 0 ;
        _music = 0 ;
    }



//Chargeons les diff�rents sprites
    _imageEmpty = load_image("pack_images_sdz/empty.bmp");
    SDL_Surface* buisson = load_image("pack_images_sdz/buisson.bmp");
    SDL_Surface* arbre = load_image("pack_images_sdz/Arbre.bmp");
    _imageBonusBomb = load_image("pack_images_sdz/bomb_bonus.bmp");
    _imageBonusSpeed = load_image("pack_images_sdz/Bonus_speed.bmp");
    _imageBonusPower = load_image("pack_images_sdz/Bonus_power.bmp");
    _imageBonusIll = load_image("pack_images_sdz/Bonus_sick.bmp");
//Initialisation de l'�cran
    _screen = screen ;
//Initialisation des diff�rentes listes
    _vectCase = vector<Case*>() ;
    _vectBomb = vector<Bomb*>() ;
    _vectFire = vector<Fire*>() ;
//Cr�ation de la liste des cases
    for (int i=0 ; i<15 ; i++)
    {
        for (int j=0 ; j<15 ; j++)
        {
            Case* case0 = new Case(_imageEmpty,i,j,screen) ;
            _vectCase.push_back(case0) ;
        }
    }
//Cr�ation d'un tableau stockant 0 si la case est vide et 1 si elle est pleine
    int carte[15*15] = {0};
    int taille_bloc = 54 ;

//Int�ressons nous � la position des arbres
//On cr�e un cadre compos� d'arbres qui d�limitent la map
    for(int i(0);i<=14;i+=14)
    {
        for (int j(0);j<=14;j++)
        {
            _vectCase[15*i+j]->setType(TREE) ;
            _vectCase[15*i+j]->setAppearance(arbre) ;
            _vectCase[15*i+j]->render() ;
            carte[15*i + j] = 1;
        }
    }
    for(int i(0);i<=14;i++)
    {
        for (int j(0);j<=14;j+=14)
        {
            _vectCase[15*i+j]->setType(TREE) ;
            _vectCase[15*i+j]->setAppearance(arbre) ;
            _vectCase[15*i+j]->render() ;
            carte[15*i + j] = 1;
        }
    }

//On place les arbres � des endroits fixes, une ligne et une colonne sur deux
    for(int i(2);i<=14;i+=2)
    {
        for (int j(2);j<=14;j+=2)
        {
            _vectCase[15*i+j]->setType(TREE) ;
            _vectCase[15*i+j]->setAppearance(arbre) ;
            _vectCase[15*i+j]->render() ;
            carte[15*i + j] = 1;
        }
    }

    //Intéressons nous aux cases qui ne sont pas des arbres, et qui sont donc des buissons simples ou des buissons avec bonus. La repartition sera faite al�atoirement
    for (int i(0);i<=14;i++)
    {
        for (int j(0);j<=14;j++)
        {
            //Notons num le numero de la case
            int num=15*i+j;

            //Fixons ses coordonnées
            SDL_Rect position ;
            position.x= i * taille_bloc;
            position.y= j * taille_bloc;

            //Pour que les personnages puissent se déplacer au début, il faut leur laisser des cases vides. Il faut également ne pas changer la nature des cases qui sont définies comme étant des arbres.

            //rajouter pour ne pas superposer arbres et buissons
            if((num!=16)&&(num!=17)&&(num!=31)&&(num!=27)&&(num!=28)&&(num!=43)&&(num!=181)&&(num!=196)&&(num!=197)&&(num!=193)&&(num!=207)&&(num!=208)&&(carte[15*i+j]!=1))
            {
                double test=(double)rand()/((double)RAND_MAX+1);
                //Dans le cas où ce nombre est inférieur à la probabilité d'avoir un buisson, on place un buisson
                if(test<=0.7)
                {
                    Case* case0 = _vectCase[15*i+j] ;
                    case0->setAppearance(buisson) ;
                    case0->setType(BUSH) ;
                    case0->render() ;
                    double test2=(double)rand()/((double)RAND_MAX+1) ;
                    //Dans le cas o� ce nombre est inf�rieur � la probabilit� d'avoir un bonus, on place un bonus
                    if (test2 <= 0.1) // proba de bonus de type bombe
                    {
                        Bonus* bonus = new Bonus(BONUS_BOMB,i,j) ;
                        case0->setBonus(bonus) ;
                    }
                    else if (test2 <= 0.2) // proba de bonus de type speed
                    {
                        Bonus* bonus = new Bonus(BONUS_SPEED,i,j) ;
                        case0->setBonus(bonus) ;
                    }
                    else if (test2 <= 0.5) // proba de bonus de type power
                    {
                        Bonus* bonus = new Bonus(BONUS_POWER,i,j) ;
                        case0->setBonus(bonus) ;
                    }
                    else if (test2 <= 0.8) // proba de bonus de type maladie
                    {
                        Bonus* bonus = new Bonus(BONUS_ILL,i,j) ;
                        case0->setBonus(bonus) ;
                    }
                }
            }
        }
    }
    //Actualisation de l'�cran
    SDL_Flip(_screen) ;
}

//Fonction principale qui g�re tout le jeu
void Map::game_on()
{
    //Initialisation d'un �v�nement
    SDL_Event event ;
    //Pointeur vers un bool�en initialis� � vrai qui dit s'il faut continuer la partie ou pas
    bool* go_on = new bool(true) ;
    //Boucle principale du jeu, qui fonctionne tant qu'on joue
    while(*go_on)
    {
        //Tant qu'une commande de la SDL_event est actionn�e
        while( SDL_PollEvent( &event ) )
        {
            // Si on appuie sur une touche du clavier
			if( event.type == SDL_KEYDOWN )
			{
			    //On regarde si cela correspond � une touche d'interaction des joueurs
			    handleEventPlayer1(event) ;
			    handleEventPlayer2(event) ;
			}
            //Si on appuye sur la croix
			else if ( event.type == SDL_QUIT )
			{
				//On ferme le jeu
				*go_on = false;
			}
        }
        //Disparition des feux p�rim�s
        disappearFire() ;
        //Explosion des bombes
        bombExplod() ;
        //Affichage de l'�cran
        render() ;
        //Teste si les joueurs sont morts et si c'est le cas, il arr�te la boucle
        testDead(go_on) ;
    }
    //Affiche les �crans de fin de jeu
    SDL_Rect offset;
    offset.x = 0;
    offset.y = 0;
    //Bool�en qui est vrai si le joeur est mort
    bool p1Dead = !(_player1->getAlive()) ;
    bool p2Dead = !(_player2->getAlive()) ;
    //Si tous les deux sont morts, il y'a match nul et on affiche l'�cran relatif
    if (p1Dead && p2Dead)
    {
        SDL_Surface* imageDraw = load_image("pack_images_sdz/Draw.bmp");;
        SDL_BlitSurface(imageDraw, 0, _screen, &offset );
        SDL_Flip(_screen) ;
    }
   //Si c'est le joueur 1 qui est mort, on affiche l'�cran de victoire qui correspond
   // et on joue le son
    else if (p1Dead)
    {
        SDL_Surface* imageP1win = load_image("pack_images_sdz/Victory_Luigi.bmp");;
        SDL_BlitSurface(imageP1win, 0, _screen, &offset );
        Mix_Chunk* soundP1Win = Mix_LoadWAV("pack_images_sdz/Luigi.wav");
        SDL_Flip(_screen) ;
        Mix_PlayChannel(1, soundP1Win, 0);
    }
    //De m�me pour le deuxi�me joueur
    else if (p2Dead)
    {
        SDL_Surface* imageP2win = load_image("pack_images_sdz/Victory_Mario.bmp");;
        SDL_BlitSurface(imageP2win, 0, _screen, &offset );
        Mix_Chunk* soundP2Win = Mix_LoadWAV("pack_images_sdz/Mario.wav");
        SDL_Flip(_screen) ;
        Mix_PlayChannel(1, soundP2Win, 0);
    }
    //Temps depuis le d�but du jeu
    int startTicks = SDL_GetTicks() ;
    //On laisse afficher l'�cran de victoire pendant 1 seconde
    while ((SDL_GetTicks()-startTicks) < 1000)
    {

    }
    //Lib�re la m�moire relative au son et �teint le son
    Mix_FreeMusic(_music);
    Mix_FreeChunk(_sound);
    Mix_CloseAudio();
}

//Fonction d'affichage g�n�rale
void Map::render()
{
   //Affichage de chacune des cases
    for (int i =0 ; i<15 ; i++)
    {
        for (int j=0 ; j<15 ; j++)
        {
            _vectCase[15*i+j]->render() ;
        }
    }
    //Affichage des deux joueurs
    _player2->render() ;
    _player1->render() ;
    //Mise � jour de l'�cran
    SDL_Flip(_screen) ;
}


//Fonction correspondant � la tentative du joueur de faire un pas � gauche
void Map::walkLeft(Bomby* player)
{
    //Si on ne peut pas le d�placer parce que le temps minimumn n'est pas encore �coul�, on arr�te tout
    if (!player->movePlayer())
    {
        return ;
    }
    //On suppose qu'il a l'autorisation de se d�placer
    //On le met en direction de la gauche
    player->setDirection(DIRECTION_LEFT) ;
    //Recuperation des coordonn�es
    int x = player->get_x() ;
    int y = player->get_y() ;
    //Recuperation du pointeur vers la case en question
    Case* case0 = _vectCase[15*(x-1)+y] ;
    //Selon le type de la case, action diff�rente
    switch (case0->getType())
    {
    //Si la case est vide, on ne fait rien
    case EMPTY:
    {
        break ;
    }
    //S'il y'a un buisson, on ne peut pas y aller donc on quitte la fonction
    case BUSH:
    {
        return ;
    }
    //De m�me s'il y'a un arbre
    case TREE:
    {
        return ;
    }
    //On tue le joueur s'il va dans le feu
    case WITH_FIRE:
    {
        player->kill();
        break ;
    }
    //On n'autorise pas le joueur � aller sur la case avec une bombe dessus
    case WITH_BOMB:
    {
        return ;
    }
    //S'il y'a un bonus de type bombe, il prend le bonus
    case WITH_BONUS_BOMB:
    {
        //Recuperation du pointeur vers le bonus
        Bonus* bonus = case0->getBonus() ;
        //On enl�ve le bonus de la case
        case0->setBonus(0) ;
        //On supprime le bonus
        delete bonus ;
        //On d�clare que la case est vide et on fait les changements n�cessaires
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        //On ajoute une bombe au joueur
        player->setNbBomb(player->getNbBomb()+1) ;
        break ;
    }
    //S'il y'a le bonus vitesse, m�me changement que pr�c�demment
    case WITH_BONUS_SPEED:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        //Augmentation de la vitesse du joueur
        player->increaseSpeed() ;
        break ;
    }
    //Idem avec le bonus power
    case WITH_BONUS_POWER:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        //Augmentation de la puissance des bombes pos�es
        player->increasePower() ;
        break ;
    }
    //Idem avec le sortil�ge maladie
    case WITH_BONUS_ILL:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        //On change l'�tat de vie du joueur, s'il �tait malade il devient normal et inversement
        player->setIll(!player->getIll()) ;
        break ;
    }
    }
    //D�placement du joueur
    player->set_x(x-1) ;
}

//Idem que pr�c�demment pour la droite
void Map::walkRight(Bomby* player)
{
    if (!player->movePlayer())
    {
        return ;
    }
    player->setDirection(DIRECTION_RIGHT) ;
    int x = player->get_x() ;
    int y = player->get_y() ;
    Case* case0 = _vectCase[15*(x+1)+y] ;
    switch (case0->getType())
    {
    case EMPTY:
    {
        break ;
    }
    case BUSH:
    {
        return ;
    }
    case TREE:
    {
        return ;
    }
    case WITH_FIRE:
    {
        player->kill();
        break ;
    }
    case WITH_BOMB:
    {
        return ;
    }
    case WITH_BONUS_BOMB:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->setNbBomb(player->getNbBomb()+1) ;
        break ;
    }
    case WITH_BONUS_SPEED:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->increaseSpeed() ;
        break ;
    }
    case WITH_BONUS_POWER:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->increasePower() ;
        break ;
    }
    case WITH_BONUS_ILL:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->setIll(!player->getIll()) ;
        break ;
    }
    }
    player->set_x(x+1) ;
}

//Idem que pr�c�demment pour le d�placement vers le haut
void Map::walkUp(Bomby* player)
{
    if (!player->movePlayer())
    {
        return ;
    }
    player->setDirection(DIRECTION_UP) ;
    int x = player->get_x() ;
    int y = player->get_y() ;
    Case* case0 = _vectCase[15*x+(y-1)] ;
    switch (case0->getType())
    {
    case EMPTY:
    {
        break ;
    }
    case BUSH:
    {
        return ;
    }
    case TREE:
    {
        return ;
    }
    case WITH_FIRE:
    {
        player->kill();
        break ;
    }
    case WITH_BOMB:
    {
        return ;
    }
    case WITH_BONUS_BOMB:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->setNbBomb(player->getNbBomb()+1) ;
        break ;
    }
    case WITH_BONUS_SPEED:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->increaseSpeed() ;
        break ;
    }
    case WITH_BONUS_POWER:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->increasePower() ;
        break ;
    }
    case WITH_BONUS_ILL:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->setIll(!player->getIll()) ;
        break ;
    }
    }
    player->set_y(y-1) ;
}

//Idem que pr�c�demment pour le d�placement vers le bas
void Map::walkDown(Bomby* player)
{
    if (!player->movePlayer())
    {
        return ;
    }
    player->setDirection(DIRECTION_DOWN) ;
    int x = player->get_x() ;
    int y = player->get_y() ;
    Case* case0 = _vectCase[15*x+(y+1)] ;
    switch (case0->getType())
    {
    case EMPTY:
    {
        break ;
    }
    case BUSH:
    {
        return ;
    }
    case TREE:
    {
        return ;
    }
    case WITH_FIRE:
    {
        player->kill();
        break ;
    }
    case WITH_BOMB:
    {
        return ;
    }
    case WITH_BONUS_BOMB:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->setNbBomb(player->getNbBomb()+1) ;
        break ;
    }
    case WITH_BONUS_SPEED:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->increaseSpeed() ;
        break ;
    }
    case WITH_BONUS_POWER:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->increasePower() ;
        break ;
    }
    case WITH_BONUS_ILL:
    {
        Bonus* bonus = case0->getBonus() ;
        case0->setBonus(0) ;
        delete bonus ;
        case0->setType(EMPTY) ;
        case0->setAppearance(_imageEmpty) ;
        player->setIll(!player->getIll()) ;
        break ;
    }
    }
    player->set_y(y+1) ;
}

//Gestion de l'explosion des bombes
void Map::bombExplod()
{
    //Vecteur des pointeurs vers les bombes qui n'ont pas encore explos�
    vector<Bomb*> existingBombs = vector<Bomb*>() ;
    //Nombre de bombes totales sur la map
    int nbBomb = _vectBomb.size() ;
    //Passage de chaque bombe en revue
    for (int n=0 ; n<nbBomb ; n++)
    {
        //Recup�ration de la bombe en question
        Bomb* bomb = _vectBomb[n] ;
        //Vrai si la bombe doit exploser et faux ou sinon
        bool explod = bomb->explode() ;
        //Si elle doit exploser
        if (explod)
        {
           //on joue le son de la bombe
            Mix_PlayChannel(1, _sound, 0);
            //On r�cup�re le joueur qui a pos� la bombe
            Bomby* bomby = bomb->getBomby() ;
            //On lui dit qu'il peut de nouveau d�poser une bombe
            bomby->setNbBomb(1) ;
            //Recup�ration des coordon�es de la bombes
            int i = bomb->get_x() ;
            int j = bomb->get_y() ;
            //R�cup�ration de la puissance de la bombe
            int power = bomby->getPower() ;
            //Compteur pour savoir combien de cases la bombe a touch�
            int p = 1 ;
            bool ok = true ;
            //Tentative d'explosion vers la gauche de la case et on bloque la propagation s'il y'a un buisson
            while(ok)
            {
                if ((_vectCase[15*(i-p)+j]->getType()==TREE) || (_vectCase[15*(i-p)+j]->getType()==BUSH))
                {
                    ok = false ;
                }
                explodeCase(i-p,j) ;
                p ++ ;
                ok &= (p<=power) ;
            }
            //Idem vers la droite
            ok = true ;
            p = 1 ;
            while(ok)
            {
                if ((_vectCase[15*(i+p)+j]->getType()==TREE) || (_vectCase[15*(i+p)+j]->getType()==BUSH))
                {
                    ok = false ;
                }
                explodeCase(i+p,j) ;
                p ++ ;
                ok &= (p<=power) ;
            }
            //Idem vers le haut
            ok = true ;
            p = 1 ;
            while(ok)
            {
                if ((_vectCase[15*i+j-p]->getType()==TREE) || (_vectCase[15*i+j-p]->getType()==BUSH))
                {
                    ok = false ;
                }
                explodeCase(i,j-p) ;
                p ++ ;
                ok &= (p<=power) ;
            }
            //Idem vers le bas
            ok = true ;
            p = 1 ;
            while(ok)
            {
                if ((_vectCase[15*i+j+p]->getType()==TREE) || (_vectCase[15*i+j+p]->getType()==BUSH))
                {
                    ok = false ;
                }
                explodeCase(i,j+p) ;
                p ++ ;
                ok &= (p<=power) ;
            }
           //Suppression de la bombe
            delete bomb ;
            //On fait exploser la case du centre de l'explosion
            explodeCase(i,j) ;
        }
        else
        {
            //Si elle n'a pas explos�, on la rajoute dans la liste des bombes qui n'ont pas explos�
            existingBombs.push_back(bomb) ;
        }
    }
    //Il ne reste plus que celles qui n'ont pas explos� dans le vecteur bombe
    _vectBomb = existingBombs ;
}


//Explosion de la case (i,j) et ajout du feu
void Map::explodeCase(int i, int j)
{
    //Verification si on peut faire exploser la case
    if ((_vectCase[15*i+j]->getType() == BUSH) || (_vectCase[15*i+j]->getType() == WITH_BOMB)
        || (_vectCase[15*i+j]->getType() == EMPTY) || (_vectCase[15*i+j]->getType() == WITH_BONUS_BOMB)
        || (_vectCase[15*i+j]->getType() == WITH_BONUS_SPEED))
    {
        SDL_Surface* imageFire = load_image("pack_images_sdz/fire.bmp");
        _vectCase[15*i+j]->setType(WITH_FIRE) ;
        _vectCase[15*i+j]->setAppearance(imageFire) ;
        Fire* fire = new Fire(i,j) ;
        _vectFire.push_back(fire) ;
    }
    //On tue le joueur s'il est sur la case qui s'explose
    if ((_player1->get_x() == i) && (_player1->get_y() == j))
    {
        _player1->kill() ;
    }
    if ((_player2->get_x() == i) && (_player2->get_y() == j))
    {
        _player2->kill() ;
    }
}

//Test si les joueurs sont encore en vie pour voir si on doit continuer le jeu ou non
void Map::testDead(bool* goOn)
{
    if (!_player1->getAlive())
    {
        *goOn = false ;
    }
    if (!_player2->getAlive())
    {
        *goOn = false ;
    }
}

//On fait disparaitre le feu
void Map::disappearFire()
{
    //Cr�ation de la feu qui ne sont pas encore �teints
    vector<Fire*> existingFires = vector<Fire*> () ;
    //Recup�ration de nombre de feu sur la map
    int nbFire = _vectFire.size() ;
    //On parcourt chaque feu pour voir s'il doit disparaitre ou non
    for (int n=0 ; n<nbFire ; n++)
    {
        Fire* fire = _vectFire[n] ;
        //Si on doit faire disparaitre le feu
        if (fire->disappear())
        {
            int i = fire->get_x() ;
            int j = fire->get_y() ;
            //On regarde s'il y'a un bonus
            Case* case0 = _vectCase[15*i+j] ;
            Bonus* bonus = case0->getBonus() ;
            //S'il n'y a pas de bonus, la case est vide
            if (bonus == 0)
            {
                case0->setType(EMPTY) ;
                case0->setAppearance(_imageEmpty) ;
            }
            //Sinon, on r�cup�re le bonus et on l'affiche
            else
            {
                switch (bonus->getType())
                {
                case BONUS_SPEED:
                {
                    case0->setType(WITH_BONUS_SPEED) ;
                    case0->setAppearance(_imageBonusSpeed) ;
                    break ;
                }
                case BONUS_BOMB:
                {
                    case0->setType(WITH_BONUS_BOMB) ;
                    case0->setAppearance(_imageBonusBomb) ;
                    break ;
                }
                case BONUS_POWER:
                {
                    case0->setType(WITH_BONUS_POWER) ;
                    case0->setAppearance(_imageBonusPower) ;
                    break ;
                }
                case BONUS_ILL:
                {
                    case0->setType(WITH_BONUS_ILL) ;
                    case0->setAppearance(_imageBonusIll) ;
                    break ;
                }
                }

            }
            //On supprime le feu
            delete fire ;
        }
        else
            //Si le feu n'a pas disparu, on le rajoute dans la liste des feux � conserver
        {
            existingFires.push_back(fire) ;
        }
    }
    //liste finale des feux encore vifs
    _vectFire = existingFires ;
}



//Commandes joueur 2
void Map::handleEventPlayer2(SDL_Event event)
{
    switch( event.key.keysym.sym )
    {
    case SDLK_UP:  //Mouvement vers le haut
        if (!_player2->getIll()) //Cas de bonne sant�
        {
            walkUp(_player2) ;
        }
        else //Cas de maladie
        {
            walkDown(_player2) ;
        }
        break;
    case SDLK_DOWN: //Mouvement vers le bas
        if (!_player2->getIll())
        {
            walkDown(_player2) ;
        }
        else
        {
            walkUp(_player2) ;
        }
        break;
    case SDLK_LEFT: //Mouvement vers la gauche
        if (!_player2->getIll())
        {
            walkLeft(_player2) ;
        }
        else
        {
            walkRight(_player2) ;
        }
        break;
    case SDLK_RIGHT: //Mouvement vers la droite
        if (!_player2->getIll())
        {
            walkRight(_player2) ;
        }
        else
        {
            walkLeft(_player2) ;
        }
        break;
    //Pose de bombe
    case SDLK_KP_ENTER :
    {
        if (_player2->ableToPutBomb()) //s'il lui reste une bombe
        {
            //On change l'apparence de la case
            SDL_Surface* imageBomb = load_image("pack_images_sdz/bomb.bmp");
            int i = _player2->get_x() ;
            int j = _player2->get_y() ;
            _vectCase[15*i+j]->setType(WITH_BOMB) ;
            _vectCase[15*i+j]->setAppearance(imageBomb) ;
            //Diminution du nombre de bombes posables
            _player2->setNbBomb(_player2->getNbBomb()-1) ;
           // Cr�ation de la bombe
            Bomb* bomb = new Bomb(_player2,i,j) ;
            //Rajout dans la liste de toutes les bombes
            _vectBomb.push_back(bomb) ;
        }
        break;
    }
    default:
        break ;
    }
}

//Idem que pr�c�demment pour le joueur 1
void Map::handleEventPlayer1(SDL_Event event)
{
    switch( event.key.keysym.sym )
    {
    case SDLK_w:  //Mouvement vers le haut
        if (!_player1->getIll())
        {
            walkUp(_player1) ;
        }
        else
        {
            walkDown(_player1) ;
        }
        break;
    case SDLK_s:
        if (!_player1->getIll())
        {
            walkDown(_player1) ;
        }
        else
        {
            walkUp(_player1) ;
        }
        break;
    case SDLK_a:
        if (!_player1->getIll())
        {
            walkLeft(_player1) ;
        }
        else
        {
            walkRight(_player1) ;
        }
        break;
    case SDLK_d:
        if (!_player1->getIll())
        {
            walkRight(_player1) ;
        }
        else
        {
            walkLeft(_player1) ;
        }
        break;
    case SDLK_SPACE :
    {
        if (_player1->ableToPutBomb())
        {
            SDL_Surface* imageBomb = load_image("pack_images_sdz/bomb.bmp");
            int i = _player1->get_x() ;
            int j = _player1->get_y() ;
            _vectCase[15*i+j]->setType(WITH_BOMB) ;
            _vectCase[15*i+j]->setAppearance(imageBomb) ;
            _player1->setNbBomb(_player1->getNbBomb()-1) ;
            Bomb* bomb = new Bomb(_player1,i,j) ;
            _vectBomb.push_back(bomb) ;
        }
        break;
    }
    default:
        break ;
    }
}
