# set the App name
NAME = rpg_side_screen
# set compiler
CC = g++ -std=c++20 -Wno-narrowing
STATIC_LIBS = -static-libstdc++ -static-libgcc
INCLUDES = -Iinclude -Iinclude/sdl -Iinclude/headers -Llib
LIBS = -lstdc++fs -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lole32 -mwindows
# set all the files needed
DEBUG_FOLDER = .build
RELEASE_FOLDER = .release

ICON_DIR = res/icon/icon.res
BIN = bin/*.o
DEBUG_FLAGS = -DF_ENABLE_ASSERTS -DF_ENABLE_DEBUG -DF_ENABLE_IMGUI

bin_dir:
	mkdir bin

imgui_o: $(patsubst src/ImGui/%.cpp,bin/%.o,$(wildcard src/ImGui/*.cpp))
app_o: $(patsubst src/Core/%.cpp,bin/%.o,$(wildcard src/Core/*.cpp))
entity_o : $(patsubst src/Entity/%.cpp,bin/%.o,$(wildcard src/Entity/*.cpp))
entity_ui_o : $(patsubst src/Entity/UI/%.cpp,bin/%.o,$(wildcard src/Entity/UI/*.cpp))
renderer_o : $(patsubst src/Renderer/%.cpp,bin/%.o,$(wildcard src/Renderer/*.cpp))
resources_o : $(patsubst src/Resources/%.cpp,bin/%.o,$(wildcard src/Resources/*.cpp))
scenes_o : $(patsubst src/Scenes/%.cpp,bin/%.o,$(wildcard src/Scenes/*.cpp))
tools_o : $(patsubst src/Tools/%.cpp,bin/%.o,$(wildcard src/Tools/*.cpp))
utils_o : $(patsubst src/Utils/%.cpp,bin/%.o,$(wildcard src/Utils/*.cpp))

# Rule to build all .cpp files in the src/ImGui folder
bin/%.o: src/ImGui/%.cpp
	$(CC) $(if $(filter true,$(DEBUG)),-g $(DEBUG_FLAGS)) $(INCLUDES) -c $< -o $@

bin/%.o: src/Core/%.cpp
	$(CC) $(if $(filter true,$(DEBUG)),-g $(DEBUG_FLAGS)) $(INCLUDES) -c $< -o $@

bin/%.o: src/Entity/%.cpp
	$(CC) $(if $(filter true,$(DEBUG)),-g $(DEBUG_FLAGS)) $(INCLUDES) -c $< -o $@

bin/%.o: src/Entity/UI/%.cpp
	$(CC) $(if $(filter true,$(DEBUG)),-g $(DEBUG_FLAGS)) $(INCLUDES) -c $< -o $@

bin/%.o: src/Renderer/%.cpp
	$(CC) $(if $(filter true,$(DEBUG)),-g $(DEBUG_FLAGS)) $(INCLUDES) -c $< -o $@

bin/%.o: src/Resources/%.cpp
	$(CC) $(if $(filter true,$(DEBUG)),-g $(DEBUG_FLAGS)) $(INCLUDES) -c $< -o $@

bin/%.o: src/Scenes/%.cpp
	$(CC) $(if $(filter true,$(DEBUG)),-g $(DEBUG_FLAGS)) $(INCLUDES) -c $< -o $@

bin/%.o: src/Tools/%.cpp
	$(CC) $(if $(filter true,$(DEBUG)),-g $(DEBUG_FLAGS)) $(INCLUDES) -c $< -o $@

bin/%.o: src/Utils/%.cpp
	$(CC) $(if $(filter true,$(DEBUG)),-g $(DEBUG_FLAGS)) $(INCLUDES) -c $< -o $@

debug: imgui_o app_o entity_o entity_ui_o renderer_o resources_o scenes_o tools_o utils_o
	${CC} -g -O0 $(STATIC_LIBS) $(INCLUDES) -o $(DEBUG_FOLDER)/fortress.exe ${BIN} $(ICON_DIR) $(LIBS) -mconsole

build: app_o entity_o entity_ui_o renderer_o resources_o scenes_o tools_o utils_o
	${CC} -s -O3 -finline-functions -flto $(STATIC_LIBS) $(INCLUDES) -o $(RELEASE_FOLDER)/${NAME}.exe ${BIN} $(ICON_DIR) $(LIBS)

compile: bin_dir imgui_o app_o entity_o entity_ui_o renderer_o resources_o scenes_o tools_o utils_o
	${CC} $(STATIC_LIBS) $(INCLUDES) -Llib -o ${NAME}_debug ${BIN} $(ICON_DIR) $(LIBS) -mconsole

web: src/Core/*.cpp src/Entity/*.cpp src/Entity/UI/*.cpp src/Renderer/*.cpp src/Resources/*.cpp src/Scenes/*.cpp src/Tools/*.cpp src/Utils/*.cpp
	em++ $^ -o .web/yare.js -g -lm --bind -std=c++20 -Wno-narrowing -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s SDL2_IMAGE_FORMATS='["png"]' -s ALLOW_MEMORY_GROWTH=1 -s TOTAL_STACK=128MB -s INITIAL_MEMORY=256MB -fsanitize=address --preload-file res --preload-file res/font --preload-file res/icon --preload-file res/sprites --use-preload-plugins


