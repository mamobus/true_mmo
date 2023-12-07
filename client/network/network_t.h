#pragma once

#include <vec.h>
#include <enet/enet.h>

typedef struct network_manager_t
{
    ENetAddress serever_adress;
    ENetEvent  event;
    ENetHost* client_host;
    ENetPeer  *server_peer;
    ENetPacket  *packet;
} network_manager_t;

typedef struct entity2send_t
{
    vec3d pos;    
    vec3d vel;
    
    int id; //unique id for virtual memory in clients and ability to realloc
    int type_id; //collider, AI, drop,

    int state;

    entity_data_t data;
} entity2send_t;