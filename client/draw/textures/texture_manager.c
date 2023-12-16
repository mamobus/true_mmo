#include "texture_manager.h"

// int get_mob_texture_id(int mob_type_id)
// {
//     return (mob_type_id - 999);
// }

// int get_static_cosmetic_texture_id(int static_cosmetic_type_id)
// {
//     return static_cosmetic_type_id - 999;
// }

// char* file_names[TEXTURES_E_SIZE];

// void tm_init()
// {
//     file_names[TEXTURE_HUD    ] = "../assets/hud/hud.png";
//     file_names[TEXTURE_TILESET] = "../assets/tileset/spritesheet.png"; 

//     file_names[TEXTURE_PLAYER_HEADS] = "../assets/tileset/headsets.png";


//     #define mob(type_id, name, texture, pixel_H, pixel_W, texture_H, texture_W, stand_frames, move_frames, attack_frames, cast_frames, death_frames, ...) \
//     file_names[TEXTURE_MOB_##name] = texture;
//     #include <moblist.h>
// }

GLuint load_texture(int type)
{   
    // assert(texture_enum < TEXTURES_E_SIZE);

    // GLuint loaded_texture_GL_id;
    // //if so, then not loaded
    // if(game->texture_manager.textures[texture_enum].times_loaded == 0)
    // {
    //     loaded_texture_GL_id = loadTexture(file_names[texture_enum]);
    // }
    // else
    // {
    //     loaded_texture_GL_id = game->texture_manager.textures[texture_enum].GL_id;
    // }

    // game->texture_manager.textures[texture_enum].times_loaded++;
    char* file_name;

    switch (type)
    {
    case TEXTURE_HUD: //HUD
        file_name = "../assets/hud/hud.png"; 
        break;

    case TEXTURE_TILESET: //MAP
        // file_name = "../assets/tileset/spritesheet.png";
        file_name = "../assets/tileset/rtset.png";
        break;

    case TEXTURE_PLAYER: //heads 
        file_name = "../assets/mob_sprites/player.png";
        break;
    case TEXTURE_PLAYER_HEADS: //heads 
        file_name = "../assets/mob_sprites/headsets.png";
        break;

    #define mob(mobtype_id, name, texture, pixel_H, pixel_W, texture_H, texture_W, stand_frames, move_frames, attack_frames, cast_frames, death_frames, ...) \
    case mobtype_id: \
        file_name = texture; \
        break;
    #include <_lists/moblist.h>
    
    default:
        file_name = NULL;
        break;
    }    
    
    GLuint loaded_texture_GL_id = loadTexture(file_name);

    return loaded_texture_GL_id;
}

// GLuint unload_texture(game_t* game, int type_id)
GLuint unload_texture(GLuint texture)
{   
    //if so, then not loaded AND WE CANNOT UNLOAD
    // printf("unloaded texture %d\n", texture_enum);
    // TEXTURE_MOB_Alice
    // assert(game->texture_manager.textures[texture_enum].times_loaded > 0);
    // game->texture_manager.textures[texture_enum].times_loaded -= 1;

    // if(game->texture_manager.textures[texture_enum].times_loaded = 0)
    // {
    //     assert(game->texture_manager.textures[texture_enum].GL_id != 0);
    // }
    glDeleteTextures(1, &texture);
    return 0;
}