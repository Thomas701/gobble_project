#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 1280 // hauteur fenetre
#define WIDTH  800 // largeur fenetre


SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = IMG_Load(path);

    if(!tmp) // probleme chargement image
    {
        fprintf(stderr, "Erreur SDL_Load : %s\n", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    if(!texture) // probleme transfo image en texture
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
        return NULL;
    }
    return texture;
}


void intro_authors(SDL_Window * window)
{
    // texture
    SDL_Texture * texture_authors  = NULL; // contient la texture qui va acceuilir l'image authors

    // renderer
    SDL_Renderer * renderer = NULL ;

    // musique
    Mix_Music * music_intro = NULL;


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if(!renderer)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
    }
    else
    {
        texture_authors = loadImage("authors.png", renderer);
    
        if(!texture_authors)
        {
            fprintf(stderr, "Erreur loadImage : %s\n", SDL_GetError());
            perror("Impossible d'afficher la texture = NULL");
        }
        else
        {
            //boucle pour rendre l'image d'intro transparente
            for (int i = 0 ; i < 130 ; ++i )
            {
                SDL_RenderClear(renderer);
                if(0 != SDL_SetTextureAlphaMod(texture_authors, i))
                {
                    fprintf(stderr, "Erreur SDL_SetTextureAlphaMod: %s\n", SDL_GetError());
                }
                else
                {
                    SDL_RenderCopy(renderer, texture_authors, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(15);
                }
             }
            // alloue la musique de demarrage
            music_intro = Mix_LoadMUS("intro2.wav");
            if (!music_intro)
            {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s\n", Mix_GetError());
            }
            else 
            {
                Mix_VolumeMusic(MIX_MAX_VOLUME/6); // baisse volume musique
                Mix_PlayMusic(music_intro, 0);      // joue une seule fois
            }

            for (int i = 130 ; i < 255 ; ++i )
            {
                SDL_RenderClear(renderer);
                if(0 != SDL_SetTextureAlphaMod(texture_authors, i))
                {
                    fprintf(stderr, "Erreur SDL_SetTextureAlphaMod : %s\n", SDL_GetError());
                }
                else
                {
                    SDL_RenderCopy(renderer, texture_authors, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(15);
                }
            }
            for (int i = 255 ; i >= 0 ; --i )
            {
                SDL_RenderClear(renderer);  // effacer image précédente
                if(0 != SDL_SetTextureAlphaMod(texture_authors, i))
                {
                    fprintf(stderr, "Erreur SDL_SetTextureAlphaMod : %s\n", SDL_GetError());
                }
                else
                {
                    SDL_RenderCopy(renderer, texture_authors, NULL, NULL);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(15);
                }
            }
        }
    }
    if(renderer) SDL_DestroyRenderer(renderer); // liberation rendu
    if(texture_authors) SDL_DestroyTexture(texture_authors); // liberation texture
    if (music_intro) Mix_FreeMusic(music_intro); // libération de la musique, plus besoin
}


SDL_bool isInRect(SDL_Point point, SDL_Point rectangleHautGauche, SDL_Point rectangleBasDroit) // pour favoir si le point est à l'interieur d'un rectangle
{
   if (   point.x >= rectangleHautGauche.x  && point.x <= rectangleBasDroit.x && point.y >= rectangleHautGauche.y  && point.y <= rectangleBasDroit.y ) // si le point est dans le rectangle
    return SDL_TRUE ;
  return SDL_FALSE;
}

SDL_bool lancementMenu(SDL_Renderer * renderer, SDL_Texture * textureBackground, SDL_Texture * textureMenu)
{
    SDL_RenderClear(renderer);

    // lancement image background
    textureBackground = loadImage("background.jpg", renderer);
    if(!textureBackground)
    {
        fprintf(stderr, "Error loadImage for textureBackground : %s\n", SDL_GetError());
        return SDL_FALSE;
    }

    if (0 != SDL_RenderCopy(renderer, textureBackground, NULL, NULL))
    {
        fprintf(stderr, "Error SDL_RenderCopy for textureBackground : %s\n", SDL_GetError());
        return SDL_FALSE;
    }


    // lancement image menu (transparente pour afficher background) blendMod car blanc
    textureMenu = loadImage("menuBis.jpg", renderer);
    if (0 != SDL_SetTextureBlendMode(textureMenu, SDL_BLENDMODE_MOD))
    {
        fprintf(stderr, "transparence textureMenu impossible : %s\n", SDL_GetError());
        return SDL_FALSE;
    }
    if(!textureMenu)
    {
        fprintf(stderr, "Error loadImage for textureMenu : %s\n", SDL_GetError());
        return SDL_FALSE;
    }

    if (0 != SDL_RenderCopy(renderer, textureMenu, NULL, NULL))
    {
        fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
        return SDL_FALSE;
    }

    SDL_RenderPresent(renderer);
    return SDL_TRUE;
}

int main(int argc, char ** argv) 
{ 
    // fenetre principale
    SDL_Window *window = NULL ;

    // textures
    SDL_Texture * textureMenu = NULL;
    SDL_Texture * textureBackground = NULL;

    // renderer
    SDL_Renderer * renderer = NULL;

    // point
        // dans l'image menu
        SDL_Point pointChoice1VS1_HG = {160,240};
        SDL_Point pointChoice1VS1_BD = {990, 355};

        SDL_Point pointChoiceIA_HG = {170,430};
        SDL_Point pointChoiceIA_BD = {975, 550};

        SDL_Point pointQuitter_HG  = {170, 650};
        SDL_Point pointQuitter_BD  = {1000, 780};

        SDL_Point pointSound_HG = {1120,0};
        SDL_Point pointSound_BD = {1280, 185};

        // souris pour evenement
        SDL_Point pointMouse = {0 , 0};
  
    // boolean
    int programOn = 1 ;   // 0 si quitter 
    int menu = 0 ;        // 1 si on est dans le menu, 0 sinon
    int boolPlayMusic = 1 ;   // si on joue de la musique ?

    // musiques
    Mix_Music * mainMusic = NULL; 

    int statut = EXIT_FAILURE ;

    // initialise le systeme gestion de rendu, d'évenements , audio et temps + test
    if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }

    // alloue la fenetre
    window = SDL_CreateWindow("GOOBLE PROJECT - PREP'ISIMA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, SDL_WINDOW_SHOWN) ;

    if(!window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit ;
    }

    // chargement carte son
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) // création de la configuration de la carte son
    {
        SDL_Log("Erreur initialisation SDL_mixer : %s", Mix_GetError());
        goto Quit ;
    }
  
    // intro image authors + son
    intro_authors(window);

    // initialisation renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        fprintf(stderr, "Error SDL_CreateRenderer for renderer: %s\n", SDL_GetError());
        goto Quit;
    }

    // initialisation de la musique
    mainMusic = Mix_LoadMUS("mainMusic.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME/12);
    if(!mainMusic)
    {
        fprintf(stderr, "Error for load mainMusic : %s \n",SDL_GetError());
    }

    if(0 != Mix_PlayMusic(mainMusic, -1)) 
    {
        fprintf(stderr, "Error in Mix_PlayMusic %s\n", SDL_GetError());
        boolPlayMusic = 0;
    }
    

    menu = 1 ;

    if (!lancementMenu(renderer, textureBackground, textureMenu))
    {
        fprintf(stderr, "Error un lancementMenu : %s \n", SDL_GetError());
        goto Quit ;
    }



    while(programOn) // boucle principale
    {
        SDL_Event event;

        while(programOn && SDL_PollEvent(&event)) // programme continue et un nouveau evenement dans la file
        {
            switch(event.type)
            {
                case SDL_QUIT :                       // utilisateur veut quitter
                    goto Quit ;
                break ;

                case SDL_KEYDOWN :                   // utilisateur a taper une touche
                    if(event.type == SDL_KEYDOWN)
                    {
                        if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) // echape pour afficher menu
                        {
                            menu = 1 ;
                            lancementMenu(renderer, textureBackground, textureMenu);
                        }
                    }
                break;
    
                case SDL_MOUSEBUTTONDOWN :           // bouton souris enfonce
                    if(menu)                         // on se trouve dans le menu
                    {
                        if (event.button.button == SDL_BUTTON_LEFT) // bouton souris gauche
                        {
                            SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
                            if (isInRect(pointMouse , pointChoice1VS1_HG, pointChoice1VS1_BD)) // choix 2 joueurs en local
                            {
                                menu = 0 ;
                                SDL_RenderClear(renderer);
                                SDL_RenderPresent(renderer);
                                printf("Lancement jeu 1VS1 \n");
                            }
                            else if(isInRect(pointMouse , pointChoiceIA_HG, pointChoiceIA_BD)) // choix 2 joueurs en local
                            {
                                menu = 0;
                                SDL_RenderClear(renderer);
                                SDL_RenderPresent(renderer);
                                printf("Lancement jeu contre IA \n");
                            }
                            else if(isInRect(pointMouse , pointSound_HG, pointSound_BD)) // choix 2 joueurs en local
                            {
                                if(boolPlayMusic == 0) // cas ou on a pas de musique
                                {
                                    boolPlayMusic = 1;// on met de bool a 1
                                    Mix_ResumeMusic();
                                }
                                else                  // cas ou on a de la musique et on veut l'arreter
                                {
                                    boolPlayMusic = 0; // on met le bool a 0 pour stopper
                                    Mix_PauseMusic();

                                }
                            }
                            else if(isInRect(pointMouse , pointQuitter_HG, pointQuitter_BD)) // choix 2 joueurs en local
                            {
                                goto Quit;
                            }
                        }
                    }
                break ;
      
                default :
                break ;
            }  
        }
    }

    statut = EXIT_SUCCESS;
  



/*goto*/
Quit :
    
    if(mainMusic) Mix_FreeMusic(mainMusic);

    if(textureMenu) SDL_DestroyTexture(textureMenu);
    if(textureBackground) SDL_DestroyTexture(textureBackground);


    if (renderer) SDL_DestroyRenderer(renderer);

    if(window) SDL_DestroyWindow(window); // libere la fenetre

    Mix_CloseAudio(); // liberation de la gestion musqie
    SDL_Quit(); // libere SDL_INIT uniquement pas les images / polices...
    return statut;
}