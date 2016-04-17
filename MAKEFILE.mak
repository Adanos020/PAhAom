#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.147                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS = -Wall -std=c++14
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -std=c++14 -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = bin/Debug/pahaom

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2 -std=c++14
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/pahaom

OBJ_DEBUG = $(OBJDIR_DEBUG)/src/program/gui/gui_Image.o $(OBJDIR_DEBUG)/src/program/game/menus/menus_Inventory.o $(OBJDIR_DEBUG)/src/program/game/menus/menus_MainMenu.o $(OBJDIR_DEBUG)/src/program/game/menus/menus_PauseMenu.o $(OBJDIR_DEBUG)/src/program/game/menus/menus_Quests.o $(OBJDIR_DEBUG)/src/program/game/player/player_Player.o $(OBJDIR_DEBUG)/src/program/gui/gui_Bar.o $(OBJDIR_DEBUG)/src/program/gui/gui_Button.o $(OBJDIR_DEBUG)/src/program/gui/gui_Checkbox.o $(OBJDIR_DEBUG)/src/program/game/menus/menus_GameMap.o $(OBJDIR_DEBUG)/src/program/gui/gui_ScrollBar.o $(OBJDIR_DEBUG)/src/program/gui/gui_Slot.o $(OBJDIR_DEBUG)/src/program/gui/gui_Switch.o $(OBJDIR_DEBUG)/src/program/gui/gui_Text.o $(OBJDIR_DEBUG)/src/program/gui/gui_Window.o $(OBJDIR_DEBUG)/src/program/program_Dictionary.o $(OBJDIR_DEBUG)/src/program/program_Program.o $(OBJDIR_DEBUG)/src/program/program_Resources.o $(OBJDIR_DEBUG)/src/program/program_Settings.o $(OBJDIR_DEBUG)/src/program/game/game_TileMap.o $(OBJDIR_DEBUG)/lib/Animation.o $(OBJDIR_DEBUG)/src/main.o $(OBJDIR_DEBUG)/src/program/game/game_Game.o $(OBJDIR_DEBUG)/src/program/game/game_HUD.o $(OBJDIR_DEBUG)/lib/AnimatedSprite.o $(OBJDIR_DEBUG)/src/program/game/item/item_Potion.o $(OBJDIR_DEBUG)/src/program/game/menus/menus_Attributes.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/src/program/gui/gui_Image.o $(OBJDIR_RELEASE)/src/program/game/menus/menus_Inventory.o $(OBJDIR_RELEASE)/src/program/game/menus/menus_MainMenu.o $(OBJDIR_RELEASE)/src/program/game/menus/menus_PauseMenu.o $(OBJDIR_RELEASE)/src/program/game/menus/menus_Quests.o $(OBJDIR_RELEASE)/src/program/game/player/player_Player.o $(OBJDIR_RELEASE)/src/program/gui/gui_Bar.o $(OBJDIR_RELEASE)/src/program/gui/gui_Button.o $(OBJDIR_RELEASE)/src/program/gui/gui_Checkbox.o $(OBJDIR_RELEASE)/src/program/game/menus/menus_GameMap.o $(OBJDIR_RELEASE)/src/program/gui/gui_ScrollBar.o $(OBJDIR_RELEASE)/src/program/gui/gui_Slot.o $(OBJDIR_RELEASE)/src/program/gui/gui_Switch.o $(OBJDIR_RELEASE)/src/program/gui/gui_Text.o $(OBJDIR_RELEASE)/src/program/gui/gui_Window.o $(OBJDIR_RELEASE)/src/program/program_Dictionary.o $(OBJDIR_RELEASE)/src/program/program_Program.o $(OBJDIR_RELEASE)/src/program/program_Resources.o $(OBJDIR_RELEASE)/src/program/program_Settings.o $(OBJDIR_RELEASE)/src/program/game/game_TileMap.o $(OBJDIR_RELEASE)/lib/Animation.o $(OBJDIR_RELEASE)/src/main.o $(OBJDIR_RELEASE)/src/program/game/game_Game.o $(OBJDIR_RELEASE)/src/program/game/game_HUD.o $(OBJDIR_RELEASE)/lib/AnimatedSprite.o $(OBJDIR_RELEASE)/src/program/game/item/item_Potion.o $(OBJDIR_RELEASE)/src/program/game/menus/menus_Attributes.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG)/src/program/gui || mkdir -p $(OBJDIR_DEBUG)/src/program/gui
	test -d $(OBJDIR_DEBUG)/src/program/game/menus || mkdir -p $(OBJDIR_DEBUG)/src/program/game/menus
	test -d $(OBJDIR_DEBUG)/src/program/game/player || mkdir -p $(OBJDIR_DEBUG)/src/program/game/player
	test -d $(OBJDIR_DEBUG)/src/program || mkdir -p $(OBJDIR_DEBUG)/src/program
	test -d $(OBJDIR_DEBUG)/src/program/game || mkdir -p $(OBJDIR_DEBUG)/src/program/game
	test -d $(OBJDIR_DEBUG)/lib || mkdir -p $(OBJDIR_DEBUG)/lib
	test -d $(OBJDIR_DEBUG)/src || mkdir -p $(OBJDIR_DEBUG)/src
	test -d $(OBJDIR_DEBUG)/src/program/game/item || mkdir -p $(OBJDIR_DEBUG)/src/program/game/item

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/src/program/gui/gui_Image.o: src/program/gui/gui_Image.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/gui_Image.cpp -o $(OBJDIR_DEBUG)/src/program/gui/gui_Image.o

$(OBJDIR_DEBUG)/src/program/game/menus/menus_Inventory.o: src/program/game/menus/menus_Inventory.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/menus/menus_Inventory.cpp -o $(OBJDIR_DEBUG)/src/program/game/menus/menus_Inventory.o

$(OBJDIR_DEBUG)/src/program/game/menus/menus_MainMenu.o: src/program/game/menus/menus_MainMenu.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/menus/menus_MainMenu.cpp -o $(OBJDIR_DEBUG)/src/program/game/menus/menus_MainMenu.o

$(OBJDIR_DEBUG)/src/program/game/menus/menus_PauseMenu.o: src/program/game/menus/menus_PauseMenu.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/menus/menus_PauseMenu.cpp -o $(OBJDIR_DEBUG)/src/program/game/menus/menus_PauseMenu.o

$(OBJDIR_DEBUG)/src/program/game/menus/menus_Quests.o: src/program/game/menus/menus_Quests.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/menus/menus_Quests.cpp -o $(OBJDIR_DEBUG)/src/program/game/menus/menus_Quests.o

$(OBJDIR_DEBUG)/src/program/game/player/player_Player.o: src/program/game/player/player_Player.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/player/player_Player.cpp -o $(OBJDIR_DEBUG)/src/program/game/player/player_Player.o

$(OBJDIR_DEBUG)/src/program/gui/gui_Bar.o: src/program/gui/gui_Bar.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/gui_Bar.cpp -o $(OBJDIR_DEBUG)/src/program/gui/gui_Bar.o

$(OBJDIR_DEBUG)/src/program/gui/gui_Button.o: src/program/gui/gui_Button.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/gui_Button.cpp -o $(OBJDIR_DEBUG)/src/program/gui/gui_Button.o

$(OBJDIR_DEBUG)/src/program/gui/gui_Checkbox.o: src/program/gui/gui_Checkbox.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/gui_Checkbox.cpp -o $(OBJDIR_DEBUG)/src/program/gui/gui_Checkbox.o

$(OBJDIR_DEBUG)/src/program/game/menus/menus_GameMap.o: src/program/game/menus/menus_GameMap.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/menus/menus_GameMap.cpp -o $(OBJDIR_DEBUG)/src/program/game/menus/menus_GameMap.o

$(OBJDIR_DEBUG)/src/program/gui/gui_ScrollBar.o: src/program/gui/gui_ScrollBar.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/gui_ScrollBar.cpp -o $(OBJDIR_DEBUG)/src/program/gui/gui_ScrollBar.o

$(OBJDIR_DEBUG)/src/program/gui/gui_Slot.o: src/program/gui/gui_Slot.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/gui_Slot.cpp -o $(OBJDIR_DEBUG)/src/program/gui/gui_Slot.o

$(OBJDIR_DEBUG)/src/program/gui/gui_Switch.o: src/program/gui/gui_Switch.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/gui_Switch.cpp -o $(OBJDIR_DEBUG)/src/program/gui/gui_Switch.o

$(OBJDIR_DEBUG)/src/program/gui/gui_Text.o: src/program/gui/gui_Text.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/gui_Text.cpp -o $(OBJDIR_DEBUG)/src/program/gui/gui_Text.o

$(OBJDIR_DEBUG)/src/program/gui/gui_Window.o: src/program/gui/gui_Window.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/gui_Window.cpp -o $(OBJDIR_DEBUG)/src/program/gui/gui_Window.o

$(OBJDIR_DEBUG)/src/program/program_Dictionary.o: src/program/program_Dictionary.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/program_Dictionary.cpp -o $(OBJDIR_DEBUG)/src/program/program_Dictionary.o

$(OBJDIR_DEBUG)/src/program/program_Program.o: src/program/program_Program.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/program_Program.cpp -o $(OBJDIR_DEBUG)/src/program/program_Program.o

$(OBJDIR_DEBUG)/src/program/program_Resources.o: src/program/program_Resources.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/program_Resources.cpp -o $(OBJDIR_DEBUG)/src/program/program_Resources.o

$(OBJDIR_DEBUG)/src/program/program_Settings.o: src/program/program_Settings.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/program_Settings.cpp -o $(OBJDIR_DEBUG)/src/program/program_Settings.o

$(OBJDIR_DEBUG)/src/program/game/game_TileMap.o: src/program/game/game_TileMap.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/game_TileMap.cpp -o $(OBJDIR_DEBUG)/src/program/game/game_TileMap.o

$(OBJDIR_DEBUG)/lib/Animation.o: lib/Animation.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c lib/Animation.cpp -o $(OBJDIR_DEBUG)/lib/Animation.o

$(OBJDIR_DEBUG)/src/main.o: src/main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/main.cpp -o $(OBJDIR_DEBUG)/src/main.o

$(OBJDIR_DEBUG)/src/program/game/game_Game.o: src/program/game/game_Game.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/game_Game.cpp -o $(OBJDIR_DEBUG)/src/program/game/game_Game.o

$(OBJDIR_DEBUG)/src/program/game/game_HUD.o: src/program/game/game_HUD.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/game_HUD.cpp -o $(OBJDIR_DEBUG)/src/program/game/game_HUD.o

$(OBJDIR_DEBUG)/lib/AnimatedSprite.o: lib/AnimatedSprite.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c lib/AnimatedSprite.cpp -o $(OBJDIR_DEBUG)/lib/AnimatedSprite.o

$(OBJDIR_DEBUG)/src/program/game/item/item_Potion.o: src/program/game/item/item_Potion.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/item/item_Potion.cpp -o $(OBJDIR_DEBUG)/src/program/game/item/item_Potion.o

$(OBJDIR_DEBUG)/src/program/game/menus/menus_Attributes.o: src/program/game/menus/menus_Attributes.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/menus/menus_Attributes.cpp -o $(OBJDIR_DEBUG)/src/program/game/menus/menus_Attributes.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)/src/program/gui
	rm -rf $(OBJDIR_DEBUG)/src/program/game/menus
	rm -rf $(OBJDIR_DEBUG)/src/program/game/player
	rm -rf $(OBJDIR_DEBUG)/src/program
	rm -rf $(OBJDIR_DEBUG)/src/program/game
	rm -rf $(OBJDIR_DEBUG)/lib
	rm -rf $(OBJDIR_DEBUG)/src
	rm -rf $(OBJDIR_DEBUG)/src/program/game/item

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE)/src/program/gui || mkdir -p $(OBJDIR_RELEASE)/src/program/gui
	test -d $(OBJDIR_RELEASE)/src/program/game/menus || mkdir -p $(OBJDIR_RELEASE)/src/program/game/menus
	test -d $(OBJDIR_RELEASE)/src/program/game/player || mkdir -p $(OBJDIR_RELEASE)/src/program/game/player
	test -d $(OBJDIR_RELEASE)/src/program || mkdir -p $(OBJDIR_RELEASE)/src/program
	test -d $(OBJDIR_RELEASE)/src/program/game || mkdir -p $(OBJDIR_RELEASE)/src/program/game
	test -d $(OBJDIR_RELEASE)/lib || mkdir -p $(OBJDIR_RELEASE)/lib
	test -d $(OBJDIR_RELEASE)/src || mkdir -p $(OBJDIR_RELEASE)/src
	test -d $(OBJDIR_RELEASE)/src/program/game/item || mkdir -p $(OBJDIR_RELEASE)/src/program/game/item

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/src/program/gui/gui_Image.o: src/program/gui/gui_Image.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/gui_Image.cpp -o $(OBJDIR_RELEASE)/src/program/gui/gui_Image.o

$(OBJDIR_RELEASE)/src/program/game/menus/menus_Inventory.o: src/program/game/menus/menus_Inventory.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/menus/menus_Inventory.cpp -o $(OBJDIR_RELEASE)/src/program/game/menus/menus_Inventory.o

$(OBJDIR_RELEASE)/src/program/game/menus/menus_MainMenu.o: src/program/game/menus/menus_MainMenu.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/menus/menus_MainMenu.cpp -o $(OBJDIR_RELEASE)/src/program/game/menus/menus_MainMenu.o

$(OBJDIR_RELEASE)/src/program/game/menus/menus_PauseMenu.o: src/program/game/menus/menus_PauseMenu.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/menus/menus_PauseMenu.cpp -o $(OBJDIR_RELEASE)/src/program/game/menus/menus_PauseMenu.o

$(OBJDIR_RELEASE)/src/program/game/menus/menus_Quests.o: src/program/game/menus/menus_Quests.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/menus/menus_Quests.cpp -o $(OBJDIR_RELEASE)/src/program/game/menus/menus_Quests.o

$(OBJDIR_RELEASE)/src/program/game/player/player_Player.o: src/program/game/player/player_Player.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/player/player_Player.cpp -o $(OBJDIR_RELEASE)/src/program/game/player/player_Player.o

$(OBJDIR_RELEASE)/src/program/gui/gui_Bar.o: src/program/gui/gui_Bar.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/gui_Bar.cpp -o $(OBJDIR_RELEASE)/src/program/gui/gui_Bar.o

$(OBJDIR_RELEASE)/src/program/gui/gui_Button.o: src/program/gui/gui_Button.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/gui_Button.cpp -o $(OBJDIR_RELEASE)/src/program/gui/gui_Button.o

$(OBJDIR_RELEASE)/src/program/gui/gui_Checkbox.o: src/program/gui/gui_Checkbox.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/gui_Checkbox.cpp -o $(OBJDIR_RELEASE)/src/program/gui/gui_Checkbox.o

$(OBJDIR_RELEASE)/src/program/game/menus/menus_GameMap.o: src/program/game/menus/menus_GameMap.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/menus/menus_GameMap.cpp -o $(OBJDIR_RELEASE)/src/program/game/menus/menus_GameMap.o

$(OBJDIR_RELEASE)/src/program/gui/gui_ScrollBar.o: src/program/gui/gui_ScrollBar.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/gui_ScrollBar.cpp -o $(OBJDIR_RELEASE)/src/program/gui/gui_ScrollBar.o

$(OBJDIR_RELEASE)/src/program/gui/gui_Slot.o: src/program/gui/gui_Slot.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/gui_Slot.cpp -o $(OBJDIR_RELEASE)/src/program/gui/gui_Slot.o

$(OBJDIR_RELEASE)/src/program/gui/gui_Switch.o: src/program/gui/gui_Switch.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/gui_Switch.cpp -o $(OBJDIR_RELEASE)/src/program/gui/gui_Switch.o

$(OBJDIR_RELEASE)/src/program/gui/gui_Text.o: src/program/gui/gui_Text.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/gui_Text.cpp -o $(OBJDIR_RELEASE)/src/program/gui/gui_Text.o

$(OBJDIR_RELEASE)/src/program/gui/gui_Window.o: src/program/gui/gui_Window.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/gui_Window.cpp -o $(OBJDIR_RELEASE)/src/program/gui/gui_Window.o

$(OBJDIR_RELEASE)/src/program/program_Dictionary.o: src/program/program_Dictionary.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/program_Dictionary.cpp -o $(OBJDIR_RELEASE)/src/program/program_Dictionary.o

$(OBJDIR_RELEASE)/src/program/program_Program.o: src/program/program_Program.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/program_Program.cpp -o $(OBJDIR_RELEASE)/src/program/program_Program.o

$(OBJDIR_RELEASE)/src/program/program_Resources.o: src/program/program_Resources.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/program_Resources.cpp -o $(OBJDIR_RELEASE)/src/program/program_Resources.o

$(OBJDIR_RELEASE)/src/program/program_Settings.o: src/program/program_Settings.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/program_Settings.cpp -o $(OBJDIR_RELEASE)/src/program/program_Settings.o

$(OBJDIR_RELEASE)/src/program/game/game_TileMap.o: src/program/game/game_TileMap.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/game_TileMap.cpp -o $(OBJDIR_RELEASE)/src/program/game/game_TileMap.o

$(OBJDIR_RELEASE)/lib/Animation.o: lib/Animation.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c lib/Animation.cpp -o $(OBJDIR_RELEASE)/lib/Animation.o

$(OBJDIR_RELEASE)/src/main.o: src/main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/main.cpp -o $(OBJDIR_RELEASE)/src/main.o

$(OBJDIR_RELEASE)/src/program/game/game_Game.o: src/program/game/game_Game.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/game_Game.cpp -o $(OBJDIR_RELEASE)/src/program/game/game_Game.o

$(OBJDIR_RELEASE)/src/program/game/game_HUD.o: src/program/game/game_HUD.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/game_HUD.cpp -o $(OBJDIR_RELEASE)/src/program/game/game_HUD.o

$(OBJDIR_RELEASE)/lib/AnimatedSprite.o: lib/AnimatedSprite.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c lib/AnimatedSprite.cpp -o $(OBJDIR_RELEASE)/lib/AnimatedSprite.o

$(OBJDIR_RELEASE)/src/program/game/item/item_Potion.o: src/program/game/item/item_Potion.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/item/item_Potion.cpp -o $(OBJDIR_RELEASE)/src/program/game/item/item_Potion.o

$(OBJDIR_RELEASE)/src/program/game/menus/menus_Attributes.o: src/program/game/menus/menus_Attributes.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/menus/menus_Attributes.cpp -o $(OBJDIR_RELEASE)/src/program/game/menus/menus_Attributes.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)/src/program/gui
	rm -rf $(OBJDIR_RELEASE)/src/program/game/menus
	rm -rf $(OBJDIR_RELEASE)/src/program/game/player
	rm -rf $(OBJDIR_RELEASE)/src/program
	rm -rf $(OBJDIR_RELEASE)/src/program/game
	rm -rf $(OBJDIR_RELEASE)/lib
	rm -rf $(OBJDIR_RELEASE)/src
	rm -rf $(OBJDIR_RELEASE)/src/program/game/item

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

