#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
    fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
  }
  else
  {
    texture_authors = loadImage("authors.png", renderer);

    if(!texture_authors)
    {
      fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
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
            fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
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
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s", Mix_GetError());
      }
      else Mix_PlayMusic(music_intro, 0);

      for (int i = 130 ; i < 255 ; ++i )
      {
        SDL_RenderClear(renderer);
        if(0 != SDL_SetTextureAlphaMod(texture_authors, i))
        {
          fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
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
          fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
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
   if (   point.x >= rectangleHautGauche.x  && point.x <= rectangleBasDroit.x
       && point.y >= rectangleHautGauche.y  && point.y <= rectangleBasDroit.y ) // si le point est dans le rectangle
  {
    return SDL_TRUE ;
  }
  return SDL_FALSE;
}

int main(int argc, char ** argv) 
{ 
  // fenetre principale
  SDL_Window *window = NULL ;

  // textures
  SDL_Texture * textureMenu = NULL;
  SDL_Texture * textureBackground = NULL;

  // renderer
  SDL_Renderer * rendererMenu = NULL;
  SDL_Renderer * rendererBackground = NULL;

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
  int programOn = 1 ; // =0 si quitter 
  int menu = 0 ;        // 1 si on est dans le menu, 0 sinon
  int playMusic = 1 ;

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

  // lancement image background pendant tout le jeu image de Thomas
  rendererBackground = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(!rendererBackground)
  {
    fprintf(stderr, "Error SDL_CreateRenderer for rendereBackground: %s\n", SDL_GetError());
    goto Quit;
  }
  
  textureBackground = loadImage("background.jpg", rendererBackground);
  if(!textureBackground)
  {
    fprintf(stderr, "Error loadImage for textureBackground : %s\n", SDL_GetError());
    goto Quit;
  }
  
  SDL_RenderClear(rendererBackground);
  SDL_RenderCopy(rendererBackground, textureBackground, NULL, NULL);
  SDL_RenderPresent(rendererBackground); 
  
  // lancement image menu la rendre transparente pour afficher image de Thomas
  
  menu = 1;
  rendererMenu = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(!rendererMenu)
  {
    fprintf(stderr, "Error SDL_CreateRenderer for rendererMenu: %s", SDL_GetError());
    goto Quit;
  }
  
  textureMenu = loadImage("menu.jpg", rendererMenu);
  if(!textureMenu)
  {
    fprintf(stderr, "Error loadImage for textureMenu : %s\n", SDL_GetError());
    goto Quit;
  }
  
  SDL_RenderClear(rendererMenu);
  SDL_RenderCopy(rendererMenu, textureMenu, NULL, NULL);
  SDL_RenderPresent(rendererMenu);
  


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
	    //SDL_RenderClear(); effacer l'image du jeu ici menu
	    SDL_RenderCopy(rendererMenu, textureMenu, NULL, NULL);
	    SDL_RenderPresent(rendererMenu);
	    SDL_RenderPresent(rendererMenu);
	  }
	}
	break;
      case SDL_MOUSEBUTTONDOWN :           // bouton souris enfonce

	if(menu)                          // on se trouve dans le menu
	{
	  if (event.button.button == SDL_BUTTON_LEFT) // bouton souris gauche
	  {
	    SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
	    if (isInRect(pointMouse , pointChoice1VS1_HG, pointChoice1VS1_BD)) // choix 2 joueurs en local
	    {
	      menu = 0 ;
	      SDL_RenderClear(rendererMenu);
	      printf("Lancement jeu 1VS1 \n ");
	    }
	    else if(isInRect(pointMouse , pointChoiceIA_HG, pointChoiceIA_BD)) // choix 2 joueurs en local
	    {
	      menu = 0;
	      SDL_RenderClear(rendererMenu);
	      printf("Lancement jeu contre IA \n ");
	    }
	    else if(isInRect(pointMouse , pointSound_HG, pointSound_BD)) // choix 2 joueurs en local
	    {
	      playMusic = (1 == playMusic) ? 0 : 1 ;
	      printf("state sound : %d \n ", playMusic);
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
  
  //menu = 0;



  
  statut = EXIT_SUCCESS;
  
Quit :
  if(textureMenu) SDL_DestroyTexture(textureMenu);
  if (rendererMenu) SDL_DestroyRenderer(rendererMenu);
  if(window) SDL_DestroyWindow(window); // libere la fenetre
  Mix_CloseAudio(); // liberation de la gestion musqie
  SDL_Quit(); // libere SDL_INIT uniquement pas les images / polices...
  return statut;
}
























































/*
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 1280 // hauteur fenetre
#define WIDTH  800 // largeur fenetre
 


// fonction pour changer de couleur
int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
  if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0) // prepare la peinture sur la surface
    return -1;
  if(SDL_RenderClear(renderer) < 0) // nettoie l'ancien renderer
    return -1;
  return 0;
}

int main(int argc, char ** argv) 
{ 
  // fenetre principale
  SDL_Window *window = NULL ;

  // renderer
  SDL_Renderer * renderer = NULL;

  int statut = EXIT_FAILURE ;

  // creation couleurs RGBA
  SDL_Color orange = {255, 127, 40, 255}; // struct acces r orange.r etc.

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

  
  // alloue renderer
  renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);

  if(!renderer)
  {
    fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
    goto Quit;
  }

  
  


  SDL_Delay(500);

  if (0 != setWindowColor(renderer, orange))
  {
    fprintf(stderr,"Erreur SDL_RenderClear : %s", SDL_GetError());
    goto Quit;
  }

  SDL_RenderPresent(renderer); // MAJ de renderer

  SDL_Delay(5000);
  
  statut = EXIT_SUCCESS;

  
			      
Quit :

  if(renderer)
  {
    SDL_DestroyRenderer(renderer);
  }
    
  if(window)
  {
    SDL_DestroyWindow(window); // libere la fenetre
  }

  SDL_Quit(); // libere SDL_INIT uniquement pas les images / polices
  return statut;
}
*/

/*
  // fonction pour mettre ne pleine écran, ne marche pas LINUX
   if (0 != SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN))
   {
     perror("Probleme de passage pleine écran");
   }


   // possible de créer un renderer en même temps que la fenêtre grace a SDL_CreateWindowAndRenderer() p28


   // fonction de colision pour tester si un point appartient à un rectangle
   SDL_bool test(SDL_Point point, SDL_Rect rect)
   {
       if(point.x >= rect.x && point.x <= (rect.x + rect.w) && point.y >= rect.y && point.y <= (rect.y + rect.h))
           return SDL_TRUE;
       else
           return SDL_FALSE;
   }
   // ou sinon
   // savoir si un point est dans un rectangle ? SDL_PointInRect p 31
   


   // savoir si deux rectangles se touchent ? SDL_HasIntersection p 31 obtenir le rectangle d'intersection ? SDL_IntersectRect p 31

   // dessiner point par point p 38 & 39 (tableau de point)
 */
