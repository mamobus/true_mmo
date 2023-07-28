workspace_folder := C:/prog/true_mmo
precompiled_folder := $(workspace_folder)/client/precompiled
client_folder := $(workspace_folder)/client

include_flags := -L$(workspace_folder)/libs -I$(workspace_folder)/includes
flags := -o $(workspace_folder)/builds/client.exe $(include_flags) -fdiagnostics-color=always
special_flags := -pipe #-Wall -O2
libs := -lglfw3 -lglew32s -lopengl32 -lgdi32
CC = C:\msys64\mingw64\bin\gcc.exe

precompiled_libs := \
	$(precompiled_folder)/client.o \
	$(precompiled_folder)/common/game.o \
	$(precompiled_folder)/common/window.o \
	$(precompiled_folder)/draw/draw.o \
	$(precompiled_folder)/draw/load_texture.o \
	$(precompiled_folder)/draw/lodepng.o \
	$(precompiled_folder)/map/load.o \
	$(precompiled_folder)/map/cute_tiled.o \
	$(precompiled_folder)/draw/load_shaders.o

all: $(precompiled_libs)
	$(CC) $(flags) $(precompiled_libs) $(libs) $(special_flags)

$(precompiled_folder)/client.o: $(client_folder)/client.c
	$(CC) -c $(client_folder)/client.c -o $(precompiled_folder)/client.o $(include_flags) $(libs)

$(precompiled_folder)/map/cute_tiled.o: $(client_folder)/map/cute_tiled.c $(client_folder)/map/cute_tiled.h
	$(CC) -c $(client_folder)/map/cute_tiled.c -o $(precompiled_folder)/map/cute_tiled.o $(include_flags) $(libs)

$(precompiled_folder)/common/game.o: $(client_folder)/common/game.c $(client_folder)/common/game.h
	$(CC) -c $(client_folder)/common/game.c -o $(precompiled_folder)/common/game.o $(include_flags) $(libs)

$(precompiled_folder)/common/window.o: $(client_folder)/common/window.c $(client_folder)/common/window.h
	$(CC) -c $(client_folder)/common/window.c -o $(precompiled_folder)/common/window.o $(include_flags) $(libs)

$(precompiled_folder)/draw/draw.o: $(client_folder)/draw/draw.c $(client_folder)/draw/draw.h
	$(CC) -c $(client_folder)/draw/draw.c -o $(precompiled_folder)/draw/draw.o $(include_flags) $(libs)

$(precompiled_folder)/draw/load_texture.o: $(client_folder)/draw/load_texture.c $(client_folder)/draw/load_texture.h
	$(CC) -c $(client_folder)/draw/load_texture.c -o $(precompiled_folder)/draw/load_texture.o $(include_flags) $(libs)

$(precompiled_folder)/draw/lodepng.o: $(client_folder)/draw/lodepng.c $(client_folder)/draw/lodepng.h
	$(CC) -c $(client_folder)/draw/lodepng.c -o $(precompiled_folder)/draw/lodepng.o $(include_flags) $(libs)

$(precompiled_folder)/map/load.o: $(client_folder)/map/load.c $(client_folder)/map/load.h
	$(CC) -c $(client_folder)/map/load.c -o $(precompiled_folder)/map/load.o $(include_flags) $(libs)

$(precompiled_folder)/draw/load_shaders.o: $(client_folder)/draw/load_shaders.c $(client_folder)/draw/load_shaders.h
	$(CC) -c $(client_folder)/draw/load_shaders.c -o $(precompiled_folder)/draw/load_shaders.o $(include_flags) $(libs)

run:
	$(workspace_folder)/builds/client.exe