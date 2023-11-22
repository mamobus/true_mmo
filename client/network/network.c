#include "network.h"

void net_create_manager(game_t* game)
{
    assert(enet_initialize() == 0);

    game->net_mngr.client_host = enet_host_create(NULL, 1, 2, 0, 0);
    assert(game->net_mngr.client_host != NULL);
    
    enet_address_set_host(&game->net_mngr.serever_adress, "localhost");
    game->net_mngr.serever_adress.port = 8800; //5553 5355

    game->net_mngr.server_peer = enet_host_connect(game->net_mngr.client_host, &game->net_mngr.serever_adress, 2, 0);

    /* Wait up to 5 seconds for the connection attempt to succeed. */
    if (enet_host_service (game->net_mngr.client_host, &game->net_mngr.event, 2000) > 0 &&
        game->net_mngr.event.type == ENET_EVENT_TYPE_CONNECT)
    {
        printf("Connection to server succeeded\n");
    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the server_peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset (game->net_mngr.server_peer);
        printf("Connection to server failed\n");
    }
}

void net_destroy_manager(game_t* game)
{
    enet_deinitialize();
}

void net_update(game_t* game)
{
    while(enet_host_service(game->net_mngr.client_host, &game->net_mngr.event, 0) > 0)
    {
        switch (game->net_mngr.event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            printf("recieved\n");
            printf("recieved string \'%s\'\n", game->net_mngr.event.packet->data);
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
            printf("You have been disconnected.\n");
            break;
        default:
            // printf("Tick tock\n");
            break;
        }
        // ENetPacket* packet = enet_packet_create("packetlol", 11, ENET_PACKET_FLAG_RELIABLE);
        // enet_host_broadcast(server_host, 0, packet);
        // enet_peer_send(&game->net_mngr.server_peer, 0, packet);
        // enet_host_flush (game->net_mngr.client_host);
    }
}