.ONESHELL:

compiled := client/precompiled
client := client

client_include_flags := -Llibs -Iincludes -Iclient
server_include_flags := -Llibs -Iincludes -Iserver
client_flags := -o builds/client.exe $(client_include_flags) -fdiagnostics-color=always -g3 
server_flags := -o builds/server.exe $(server_include_flags) -fdiagnostics-color=always
special_flags := -pipe#-O2 -Wall 
special_flags_optimized := -pipe -O0 #-march=native# -Wall 
client_libs := -lglfw3 -lglew32s -lopengl32 -lgdi32 -lccd -lenet64 -lws2_32 -lwinmm
server_libs := -lccd -lenet64 -lws2_32 -lwinmm
# GCC = C:\msys64\mingw64\bin\gcc.exe

client_obj := \
	$(compiled)/client.o \
	$(compiled)/input.o \
	$(compiled)/chunk.o \
	$(compiled)/window.o \
	$(compiled)/camera.o \
	$(compiled)/draw.o \
	$(compiled)/lodepng.o \
	$(compiled)/load_texture.o \
	$(compiled)/load_shaders.o \
	$(compiled)/texture_manager.o \
	$(compiled)/mob.o \
	$(compiled)/update.o \
	$(compiled)/hud.o \
	$(compiled)/vec.o \
	$(compiled)/network.o \
	$(compiled)/vector.o

client_src := \
	client/client.c \
	client/common/input.c \
	client/map/chunk.c \
	client/draw/window/window.c \
	client/draw/camera/camera.c \
	client/draw/draw.c \
	client/HUD/hud.c \
	client/draw/load/lodepng.c \
	client/draw/load/load_texture.c \
	client/draw/textures/texture_manager.c \
	client/draw/load/load_shaders.c \
	client/logic/mob/mob.c \
	client/physics/update/update.c \
	client/network/network.c \
	includes/vec.c \
	includes/vector.c

client_headers := \
	client/common/player.h \
	client/common/game_t.h \
	client/common/input.h \
	client/map/chunk.h \
	client/map/chunk_t.h \
	client/draw/window/window.h \
	client/draw/window/window_t.h \
	client/draw/camera/camera.h \
	client/draw/camera/camera_t.h \
	client/draw/textures/texture_manager_t.h \
	client/draw/textures/texture_manager.h \
	client/HUD/hud_t.h \
	client/HUD/hud.h \
	client/draw/draw.h \
	client/draw/load/lodepng.h \
	client/draw/load/load_texture.h \
	client/draw/load/load_shaders.h \
	client/logic/mob/mob.h \
	client/logic/mob/mob_t.h \
	client/physics/update/update.h \
	client/network/network_t.h \
	client/network/network.h \
	includes/debug_defines.h \
	includes/vec.h \
	includes/vector.h


client_: $(client_obj) 
	gcc $(client_flags) $(client_obj) $(client_libs) $(special_flags)

server_:
	gcc server/server.c $(server_flags) $(server_libs) $(special_flags)

$(compiled)/vec.o: includes/vec.c $(client_headers)
	gcc -c includes/vec.c -o $(compiled)/vec.o $(client_include_flags) $(client_libs)

$(compiled)/client.o: client/client.c $(client_headers)
	gcc -c client/client.c -o $(compiled)/client.o $(client_include_flags) $(client_libs)

$(compiled)/input.o: client/common/input.c $(client_headers)
	gcc -c client/common/input.c -o $(compiled)/input.o $(client_include_flags) $(client_libs)

$(compiled)/camera.o: client/draw/camera/camera.c $(client_headers)
	gcc -c client/draw/camera/camera.c -o $(compiled)/camera.o $(client_include_flags) $(client_libs)

$(compiled)/window.o: client/draw/window/window.c $(client_headers)
	gcc -c client/draw/window/window.c -o $(compiled)/window.o $(client_include_flags) $(client_libs)

$(compiled)/hud.o: client/HUD/hud.c $(client_headers)
	gcc -c client/HUD/hud.c -o $(compiled)/hud.o $(client_include_flags) $(client_libs)

$(compiled)/draw.o: client/draw/draw.c $(client_headers)
	gcc -c client/draw/draw.c -o $(compiled)/draw.o $(client_include_flags) $(client_libs)

$(compiled)/load_texture.o: client/draw/load/load_texture.c $(client_headers)
	gcc -c client/draw/load/load_texture.c -o $(compiled)/load_texture.o $(client_include_flags) $(client_libs)

$(compiled)/lodepng.o: client/draw/load/lodepng.c $(client_headers)
	gcc -c client/draw/load/lodepng.c -o $(compiled)/lodepng.o $(client_include_flags) $(client_libs)

$(compiled)/load_shaders.o: client/draw/load/load_shaders.c $(client_headers)
	gcc -c client/draw/load/load_shaders.c -o $(compiled)/load_shaders.o $(client_include_flags) $(client_libs)

$(compiled)/texture_manager.o: client/draw/textures/texture_manager.c $(client_headers)
	gcc -c client/draw/textures/texture_manager.c -o $(compiled)/texture_manager.o $(client_include_flags) $(client_libs)

$(compiled)/chunk.o: client/map/chunk.c $(client_headers)
	gcc -c client/map/chunk.c -o $(compiled)/chunk.o $(client_include_flags) $(client_libs)

$(compiled)/mob.o: client/logic/mob/mob.c $(client_headers)
	gcc -c client/logic/mob/mob.c -o $(compiled)/mob.o $(client_include_flags) $(client_libs)

$(compiled)/network.o: client/network/network.c $(client_headers)
	gcc -c client/network/network.c -o $(compiled)/network.o $(client_include_flags) $(client_libs)

$(compiled)/update.o: client/physics/update/update.c $(client_headers)
	gcc -c client/physics/update/update.c -o $(compiled)/update.o $(client_include_flags) $(client_libs)

$(compiled)/vector.o: includes/vector.c $(client_headers)
	gcc -c includes/vector.c -o $(compiled)/vector.o $(client_include_flags) $(client_libs)

builds/imorter.exe: 
	gcc importer/import.c $(special_flags_optimized) -o builds/imorter.exe
# full:
import_: importer/import.c
	gcc importer/import.c $(special_flags) -o builds/imorter.exe
	builds/imorter.exe

# uptodate: $(client_)

run: client_ server_ $(client_obj) 
	cd ./builds && \
	server.exe && client.exe

run_client: client_
	cd ./builds && \
	client.exe

client_opt:
	gcc $(client_flags) $(client_src) $(client_libs) $(special_flags_optimized)
	cd ./builds && \
	builds/client.exe