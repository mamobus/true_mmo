#include "texture_manager.h"

GLuint load_texture(game_t* game, textures_e texture_enum)
{   
    char* temp_file_names[TEXTURES_E_SIZE];

    temp_file_names[HUD_TEXTURE    ] = "../assets/hud/hud.png";
    temp_file_names[TILESET        ] = "../assets/tileset/spritesheet.png"; 
    temp_file_names[MOB_STOLEN_GIRL] = "../assets/mob_sprites/stolen_girl.png"; 

    assert(texture_enum < TEXTURES_E_SIZE);

    GLuint loaded_texture_GL_id;
    //if so, then not loaded
    if(game->texture_manager.textures[texture_enum].GL_id == 0)
    {
        loaded_texture_GL_id = loadTexture(temp_file_names[texture_enum]);
    }
    else
    {
        loaded_texture_GL_id = game->texture_manager.textures[texture_enum].GL_id;
    }

    return loaded_texture_GL_id;
}

GLuint unload_texture(game_t* game, textures_e texture_enum)
{   
    //if so, then not loaded AND WE CANNOT UNLOAD
    assert(game->texture_manager.textures[texture_enum].GL_id != 0);

    glDeleteTextures(1, &texture_enum);

    return 0;
}