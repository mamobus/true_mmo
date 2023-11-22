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
