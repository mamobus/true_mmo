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
    enet_peer_disconnect_now(game->net_mngr.server_peer, 0);

    enet_deinitialize();
}

static void parse_mobs(game_t* game, ENetEvent* event)
{
    //so we have ents to parse
    //lets do it 1 by 1
    //if not listed then create it
    //ill have to add timer to entities so they expire if not updated for long time

    int* data = event->packet->data;
    entity2send_t* entities = &data[2];
    int type = data[0];
    int size = data[1];



    for(int i=0; i<size; i++)
    {
        entity2send_t packetmob = entities[i]; 
        // printf("mob id %d\n", packetmob.id);
        // entity_add()
        entity_t* mob = entity_find(packetmob.id, packetmob.type_id, game);
        if(mob != NULL) //if exist then update
        {
            assert(mob->id == packetmob.id);
            mob->pos = packetmob.pos;
            mob->vel = packetmob.vel;
            mob->state = packetmob.state;
        }
        else //not exist, should be added
        {
            entity_t newmob = {0};
            newmob.id = packetmob.id;
            newmob.pos = packetmob.pos;
            newmob.vel = packetmob.vel;
            newmob.state = packetmob.state;
            //everything else set to 0 by {0}
            printf("mob adding\n");
            entity_add(newmob, packetmob.type_id, game);
            printf("mob added\n");
        }
    }

}

void net_update(game_t* game)
{
    ENetEvent event;
    while(enet_host_service(game->net_mngr.client_host, &event, 0) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            int type = ((int*)event.packet->data)[0];
            int size = ((int*)event.packet->data)[1];
            // printf("recieved type %d size %d\n", type, size);
            
            parse_mobs(game, &event);
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