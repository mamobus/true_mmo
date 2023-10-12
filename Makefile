.ONESHELL:

precompiled_folder := $(CURDIR)/client/precompiled
client_folder := $(CURDIR)/client

include_flags := -L$(CURDIR)/libs -I$(CURDIR)/includes
flags := -o $(CURDIR)/builds/client.exe $(include_flags) -fdiagnostics-color=always
special_flags := -pipe #-Wall -O2
libs := -lglfw3 -lglew32s -lopengl32 -lgdi32
CC = C:\msys64\mingw64\bin\gcc.exe

precompiled_client_libs := \
	$(precompiled_folder)/client.o \
	$(precompiled_folder)/common/game.o \
	$(precompiled_folder)/common/window.o \
	$(precompiled_folder)/load/chunk.o \
	$(precompiled_folder)/load/cute_tiled.o \
	$(precompiled_folder)/draw/draw.o \
	$(precompiled_folder)/draw/lodepng.o \
	$(precompiled_folder)/draw/load_texture.o \
	$(precompiled_folder)/draw/load_shaders.o

client_libs := \
	$(precompiled_folder)/client.c \
	$(precompiled_folder)/common/game.c \
	$(precompiled_folder)/common/window.c \
	$(precompiled_folder)/load/chunk.c \
	$(precompiled_folder)/load/cute_tiled.c \
	$(precompiled_folder)/draw/draw.c \
	$(precompiled_folder)/draw/lodepng.c \
	$(precompiled_folder)/draw/load_texture.c \
	$(precompiled_folder)/draw/load_shaders.c

client_: $(precompiled_client_libs) 
	$(CC) $(flags) $(precompiled_client_libs) $(libs) $(special_flags)

$(precompiled_folder)/client.o: $(client_folder)/client.c
	$(CC) -c $(client_folder)/client.c -o $(precompiled_folder)/client.o $(include_flags) $(libs)

$(precompiled_folder)/load/cute_tiled.o: $(client_folder)/load/cute_tiled.c $(client_folder)/load/cute_tiled.h
	$(CC) -c $(client_folder)/load/cute_tiled.c -o $(precompiled_folder)/load/cute_tiled.o $(include_flags) $(libs)

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

$(precompiled_folder)/load/chunk.o: $(client_folder)/load/chunk.c $(client_folder)/load/chunk.h
	$(CC) -c $(client_folder)/load/chunk.c -o $(precompiled_folder)/load/chunk.o $(include_flags) $(libs)

$(precompiled_folder)/draw/load_shaders.o: $(client_folder)/draw/load_shaders.c $(client_folder)/draw/load_shaders.h
	$(CC) -c $(client_folder)/draw/load_shaders.c -o $(precompiled_folder)/draw/load_shaders.o $(include_flags) $(libs)

$(CURDIR)/builds/imorter.exe: 
	gcc $(CURDIR)/importer/import.c $(special_flags) -o $(CURDIR)/builds/imorter.exe
# full:
import_: $(CURDIR)/importer/import.c
	gcc $(CURDIR)/importer/import.c $(special_flags) -o $(CURDIR)/builds/imorter.exe
	$(CURDIR)/builds/imorter.exe

# uptodate: $(client_)

run: client_ $(precompiled_client_libs) 
	cd ./builds && \
	$(CURDIR)/builds/client.exe