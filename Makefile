.ONESHELL:

precompiled_folder := $(CURDIR)/client/precompiled
client_folder := $(CURDIR)/client

include_flags := -L$(CURDIR)/libs -I$(CURDIR)/includes
flags := -o $(CURDIR)/builds/client.exe $(include_flags) -fdiagnostics-color=always
special_flags := -pipe #-O2 -Wall 
special_flags_optimized := -pipe #-O2 # -Wall 
libs := -lglfw3 -lglew32s -lopengl32 -lgdi32
CC = C:\msys64\mingw64\bin\gcc.exe

precompiled_client_libs := \
	$(precompiled_folder)/client.o \
	$(precompiled_folder)/common/game.o \
	$(precompiled_folder)/common/input.o \
	$(precompiled_folder)/load/chunk.o \
	$(precompiled_folder)/draw/window.o \
	$(precompiled_folder)/draw/camera.o \
	$(precompiled_folder)/draw/draw.o \
	$(precompiled_folder)/draw/load/lodepng.o \
	$(precompiled_folder)/draw/load/load_texture.o \
	$(precompiled_folder)/draw/load/load_shaders.o \
	$(precompiled_folder)/logic/mob.o \
	$(precompiled_folder)/includes/vector.o

client_libs := \
	$(client_folder)/client.c \
	$(client_folder)/common/game.c \
	$(client_folder)/common/input.c \
	$(client_folder)/load/chunk.c \
	$(client_folder)/draw/window.c \
	$(client_folder)/draw/camera.c \
	$(client_folder)/draw/draw.c \
	$(client_folder)/draw/load/lodepng.c \
	$(client_folder)/draw/load/load_texture.c \
	$(client_folder)/draw/load/load_shaders.c \
	$(client_folder)/logic/mob.c \
	$(CURDIR)/includes/vector.c

client_libs_headers := \
	$(client_folder)/common/game.h \
	$(client_folder)/common/input.h \
	$(client_folder)/load/chunk.h \
	$(client_folder)/draw/window.h \
	$(client_folder)/draw/camera.h \
	$(client_folder)/draw/draw.h \
	$(client_folder)/draw/load/lodepng.h \
	$(client_folder)/draw/load/load_texture.h \
	$(client_folder)/draw/load/load_shaders.h \
	$(client_folder)/logic/mob.h \
	$(CURDIR)/includes/vector.h


client_: $(precompiled_client_libs) 
	$(CC) $(flags) $(precompiled_client_libs) $(libs) $(special_flags)

$(precompiled_folder)/client.o: $(client_folder)/client.c $(client_libs_headers)
	$(CC) -c $(client_folder)/client.c -o $(precompiled_folder)/client.o $(include_flags) $(libs)

# $(precompiled_folder)/load/cute_tiled.o: $(client_folder)/load/cute_tiled.c $(client_folder)/load/cute_tiled.h
# 	$(CC) -c $(client_folder)/load/cute_tiled.c -o $(precompiled_folder)/load/cute_tiled.o $(include_flags) $(libs)

$(precompiled_folder)/common/game.o: $(client_folder)/common/game.c $(client_libs_headers)
	$(CC) -c $(client_folder)/common/game.c -o $(precompiled_folder)/common/game.o $(include_flags) $(libs)

$(precompiled_folder)/common/input.o: $(client_folder)/common/input.c $(client_libs_headers)
	$(CC) -c $(client_folder)/common/input.c -o $(precompiled_folder)/common/input.o $(include_flags) $(libs)

$(precompiled_folder)/draw/camera.o: $(client_folder)/draw/camera.c $(client_libs_headers)
	$(CC) -c $(client_folder)/draw/camera.c -o $(precompiled_folder)/draw/camera.o $(include_flags) $(libs)

$(precompiled_folder)/draw/window.o: $(client_folder)/draw/window.c $(client_libs_headers)
	$(CC) -c $(client_folder)/draw/window.c -o $(precompiled_folder)/draw/window.o $(include_flags) $(libs)

$(precompiled_folder)/draw/draw.o: $(client_folder)/draw/draw.c $(client_libs_headers)
	$(CC) -c $(client_folder)/draw/draw.c -o $(precompiled_folder)/draw/draw.o $(include_flags) $(libs)

$(precompiled_folder)/draw/load/load_texture.o: $(client_folder)/draw/load/load_texture.c $(client_libs_headers)
	$(CC) -c $(client_folder)/draw/load/load_texture.c -o $(precompiled_folder)/draw/load/load_texture.o $(include_flags) $(libs)

$(precompiled_folder)/draw/load/lodepng.o: $(client_folder)/draw/load/lodepng.c $(client_libs_headers)
	$(CC) -c $(client_folder)/draw/load/lodepng.c -o $(precompiled_folder)/draw/load/lodepng.o $(include_flags) $(libs)

$(precompiled_folder)/draw/load/load_shaders.o: $(client_folder)/draw/load/load_shaders.c $(client_libs_headers)
	$(CC) -c $(client_folder)/draw/load/load_shaders.c -o $(precompiled_folder)/draw/load/load_shaders.o $(include_flags) $(libs)

$(precompiled_folder)/load/chunk.o: $(client_folder)/load/chunk.c $(client_libs_headers)
	$(CC) -c $(client_folder)/load/chunk.c -o $(precompiled_folder)/load/chunk.o $(include_flags) $(libs)

$(precompiled_folder)/logic/mob.o: $(client_folder)/logic/mob.c $(client_libs_headers)
	$(CC) -c $(client_folder)/logic/mob.c -o $(precompiled_folder)/logic/mob.o $(include_flags) $(libs)

$(precompiled_folder)/includes/vector.o: $(CURDIR)/includes/vector.c $(client_libs_headers)
	$(CC) -c $(CURDIR)/includes/vector.c -o $(precompiled_folder)/includes/vector.o $(include_flags) $(libs)

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

client_o2:
	$(CC) $(flags) $(client_libs) $(libs) $(special_flags_optimized)