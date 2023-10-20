.ONESHELL:

compiled := $(CURDIR)/client/precompiled
client := $(CURDIR)/client

include_flags := -L$(CURDIR)/libs -I$(CURDIR)/includes -I$(CURDIR)/client
flags := -o $(CURDIR)/builds/client.exe $(include_flags) -fdiagnostics-color=always
special_flags := -pipe #-O2 -Wall 
special_flags_optimized := -pipe -O3 # -Wall 
libs := -lglfw3 -lglew32s -lopengl32 -lgdi32
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
	$(compiled)/mob.o \
	$(compiled)/vector.o

client_libs := \
	$(client)/client.c \
	$(client)/common/input.c \
	$(client)/map/chunk.c \
	$(client)/draw/window/window.c \
	$(client)/draw/camera/camera.c \
	$(client)/draw/draw.c \
	$(client)/draw/load/lodepng.c \
	$(client)/draw/load/load_texture.c \
	$(client)/draw/load/load_shaders.c \
	$(client)/logic/mob/mob.c \
	$(CURDIR)/includes/vector.c

client_libs_headers := \
	$(client)/common/game_t.h \
	$(client)/common/input.h \
	$(client)/map/chunk.h \
	$(client)/map/chunk_t.h \
	$(client)/draw/window/window.h \
	$(client)/draw/window/window_t.h \
	$(client)/draw/camera/camera.h \
	$(client)/draw/camera/camera_t.h \
	$(client)/draw/draw.h \
	$(client)/draw/load/lodepng.h \
	$(client)/draw/load/load_texture.h \
	$(client)/draw/load/load_shaders.h \
	$(client)/logic/mob/mob.h \
	$(client)/logic/mob/mob_t.h \
	$(CURDIR)/includes/vector.h


client_: $(precompiled_client_libs) 
	$(GCC) $(flags) $(precompiled_client_libs) $(libs) $(special_flags)

$(compiled)/client.o: $(client)/client.c $(client_libs_headers)
	$(GCC) -c $(client)/client.c -o $(compiled)/client.o $(include_flags) $(libs)

$(compiled)/input.o: $(client)/common/input.c $(client_libs_headers)
	$(GCC) -c $(client)/common/input.c -o $(compiled)/input.o $(include_flags) $(libs)

$(compiled)/camera.o: $(client)/draw/camera/camera.c $(client_libs_headers)
	$(GCC) -c $(client)/draw/camera/camera.c -o $(compiled)/camera.o $(include_flags) $(libs)

$(compiled)/window.o: $(client)/draw/window/window.c $(client_libs_headers)
	$(GCC) -c $(client)/draw/window/window.c -o $(compiled)/window.o $(include_flags) $(libs)

$(compiled)/draw.o: $(client)/draw/draw.c $(client_libs_headers)
	$(GCC) -c $(client)/draw/draw.c -o $(compiled)/draw.o $(include_flags) $(libs)

$(compiled)/load_texture.o: $(client)/draw/load/load_texture.c $(client_libs_headers)
	$(GCC) -c $(client)/draw/load/load_texture.c -o $(compiled)/load_texture.o $(include_flags) $(libs)

$(compiled)/lodepng.o: $(client)/draw/load/lodepng.c $(client_libs_headers)
	$(GCC) -c $(client)/draw/load/lodepng.c -o $(compiled)/lodepng.o $(include_flags) $(libs)

$(compiled)/load_shaders.o: $(client)/draw/load/load_shaders.c $(client_libs_headers)
	$(GCC) -c $(client)/draw/load/load_shaders.c -o $(compiled)/load_shaders.o $(include_flags) $(libs)

$(compiled)/chunk.o: $(client)/map/chunk.c $(client_libs_headers)
	$(GCC) -c $(client)/map/chunk.c -o $(compiled)/chunk.o $(include_flags) $(libs)

$(compiled)/mob.o: $(client)/logic/mob/mob.c $(client_libs_headers)
	$(GCC) -c $(client)/logic/mob/mob.c -o $(compiled)/mob.o $(include_flags) $(libs)

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