.ONESHELL:

compiled := $(CURDIR)/client/precompiled
client := $(CURDIR)/client

include_flags := -L$(CURDIR)/libs -I$(CURDIR)/includes -I$(CURDIR)/client
flags := -o $(CURDIR)/builds/client.exe $(include_flags) -fdiagnostics-color=always
special_flags := -pipe #-O2 -Wall 
special_flags_optimized := -pipe -O3 #-march=native# -Wall 
libs := -lglfw3 -lglew32s -lopengl32 -lgdi32 -lccd -lenet64
GCC = C:\msys64\mingw64\bin\gcc.exe

precompiled_client_libs := \
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
	$(compiled)/vector.o

client_libs := \
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
	includes/vector.c

client_libs_headers := \
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
	client/HUD/hud.h \
	client/draw/draw.h \
	client/draw/load/lodepng.h \
	client/draw/load/load_texture.h \
	client/draw/load/load_shaders.h \
	client/logic/mob/mob.h \
	client/logic/mob/mob_t.h \
	client/physics/update/update.h \
	includes/debug_defines.h \
	includes/vector.h


client_: $(precompiled_client_libs) 
	$(GCC) $(flags) $(precompiled_client_libs) $(libs) $(special_flags)

# $(compiled)/vec.o: includes/vec.c $(client_libs_headers)
# 	$(GCC) -c includes/vec.c -o $(compiled)/vec.o $(include_flags) $(libs)

$(compiled)/client.o: client/client.c $(client_libs_headers)
	$(GCC) -c client/client.c -o $(compiled)/client.o $(include_flags) $(libs)

$(compiled)/input.o: client/common/input.c $(client_libs_headers)
	$(GCC) -c client/common/input.c -o $(compiled)/input.o $(include_flags) $(libs)

$(compiled)/camera.o: client/draw/camera/camera.c $(client_libs_headers)
	$(GCC) -c client/draw/camera/camera.c -o $(compiled)/camera.o $(include_flags) $(libs)

$(compiled)/window.o: client/draw/window/window.c $(client_libs_headers)
	$(GCC) -c client/draw/window/window.c -o $(compiled)/window.o $(include_flags) $(libs)

$(compiled)/hud.o: client/HUD/hud.c $(client_libs_headers)
	$(GCC) -c client/HUD/hud.c -o $(compiled)/hud.o $(include_flags) $(libs)

$(compiled)/draw.o: client/draw/draw.c $(client_libs_headers)
	$(GCC) -c client/draw/draw.c -o $(compiled)/draw.o $(include_flags) $(libs)

$(compiled)/load_texture.o: client/draw/load/load_texture.c $(client_libs_headers)
	$(GCC) -c client/draw/load/load_texture.c -o $(compiled)/load_texture.o $(include_flags) $(libs)

$(compiled)/lodepng.o: client/draw/load/lodepng.c $(client_libs_headers)
	$(GCC) -c client/draw/load/lodepng.c -o $(compiled)/lodepng.o $(include_flags) $(libs)

$(compiled)/load_shaders.o: client/draw/load/load_shaders.c $(client_libs_headers)
	$(GCC) -c client/draw/load/load_shaders.c -o $(compiled)/load_shaders.o $(include_flags) $(libs)

$(compiled)/texture_manager.o: client/draw/textures/texture_manager.c $(client_libs_headers)
	$(GCC) -c client/draw/textures/texture_manager.c -o $(compiled)/texture_manager.o $(include_flags) $(libs)

$(compiled)/chunk.o: client/map/chunk.c $(client_libs_headers)
	$(GCC) -c client/map/chunk.c -o $(compiled)/chunk.o $(include_flags) $(libs)

$(compiled)/mob.o: client/logic/mob/mob.c $(client_libs_headers)
	$(GCC) -c client/logic/mob/mob.c -o $(compiled)/mob.o $(include_flags) $(libs)

$(compiled)/update.o: client/physics/update/update.c $(client_libs_headers)
	$(GCC) -c client/physics/update/update.c -o $(compiled)/update.o $(include_flags) $(libs)

$(compiled)/vector.o: $(CURDIR)/includes/vector.c $(client_libs_headers)
	$(GCC) -c $(CURDIR)/includes/vector.c -o $(compiled)/vector.o $(include_flags) $(libs)

$(CURDIR)/builds/imorter.exe: 
	$(GCC) $(CURDIR)/importer/import.c $(special_flags_optimized) -o $(CURDIR)/builds/imorter.exe
# full:
import_: $(CURDIR)/importer/import.c
	$(GCC) $(CURDIR)/importer/import.c $(special_flags) -o $(CURDIR)/builds/imorter.exe
	$(CURDIR)/builds/imorter.exe

# uptodate: $(client_)

run: client_ $(precompiled_client_libs) 
	cd ./builds && \
	$(CURDIR)/builds/client.exe

client_opt:
	$(GCC) $(flags) $(client_libs) $(libs) $(special_flags_optimized)
	cd ./builds && \
	$(CURDIR)/builds/client.exe