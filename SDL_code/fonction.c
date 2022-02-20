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
        texture_authors = loadImage("Frames/authors.png", renderer);
    
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
            music_intro = Mix_LoadMUS("Music/intro2.wav");
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
    textureBackground = loadImage("Frames/background.jpg", renderer);
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
    textureMenu = loadImage("Frames/menuBis.jpg", renderer);
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