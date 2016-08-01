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
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/pahaom

OBJ_DEBUG = $(OBJDIR_DEBUG)/src/program/game/ui/PauseMenu.o $(OBJDIR_DEBUG)/src/program/game/ui/MainMenu.o $(OBJDIR_DEBUG)/src/program/game/ui/Journal.o $(OBJDIR_DEBUG)/src/program/game/ui/Inventory.o $(OBJDIR_DEBUG)/src/program/game/ui/BookOfSpells.o $(OBJDIR_DEBUG)/src/program/gui/Bar.o $(OBJDIR_DEBUG)/src/program/game/ui/Attributes.o $(OBJDIR_DEBUG)/src/program/game/fov/FOV.o $(OBJDIR_DEBUG)/src/program/game/entity/npc/Bandit.o $(OBJDIR_DEBUG)/src/program/game/entity/npc/Teacher.o $(OBJDIR_DEBUG)/src/program/path_finder/PathFinder.o $(OBJDIR_DEBUG)/src/program/path_finder/PathFinder_Node.o $(OBJDIR_DEBUG)/src/program/observer/Observer.o $(OBJDIR_DEBUG)/src/program/messages/MessageManager.o $(OBJDIR_DEBUG)/src/program/messages/Message.o $(OBJDIR_DEBUG)/src/program/gui/Window.o $(OBJDIR_DEBUG)/src/program/gui/Text.o $(OBJDIR_DEBUG)/src/program/gui/Switch.o $(OBJDIR_DEBUG)/src/program/game/entity/item/Rune.o $(OBJDIR_DEBUG)/src/program/gui/Slot.o $(OBJDIR_DEBUG)/src/program/gui/ScrollBar.o $(OBJDIR_DEBUG)/src/program/gui/Menu.o $(OBJDIR_DEBUG)/src/program/gui/Image.o $(OBJDIR_DEBUG)/src/program/gui/Checkbox.o $(OBJDIR_DEBUG)/src/program/gui/Button.o $(OBJDIR_DEBUG)/src/program/game/Level.o $(OBJDIR_DEBUG)/src/program/game/ui/HUD.o $(OBJDIR_DEBUG)/src/program/game/Game.o $(OBJDIR_DEBUG)/src/program/Settings.o $(OBJDIR_DEBUG)/src/program/Resources.o $(OBJDIR_DEBUG)/src/program/Program.o $(OBJDIR_DEBUG)/src/main.o $(OBJDIR_DEBUG)/lib/Animation.o $(OBJDIR_DEBUG)/src/program/game/entity/item/Potion.o $(OBJDIR_DEBUG)/src/program/game/entity/item/Food.o $(OBJDIR_DEBUG)/src/program/game/entity/item/ColdWeapon.o $(OBJDIR_DEBUG)/src/program/game/entity/item/Coin.o $(OBJDIR_DEBUG)/src/program/game/entity/item/Book.o $(OBJDIR_DEBUG)/lib/AnimatedSprite.o $(OBJDIR_DEBUG)/src/program/game/entity/Stairs.o $(OBJDIR_DEBUG)/src/program/game/entity/Shadow.o $(OBJDIR_DEBUG)/src/program/game/entity/Player.o $(OBJDIR_DEBUG)/src/program/game/entity/Door.o $(OBJDIR_DEBUG)/src/program/game/entity/Chest.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/src/program/game/ui/PauseMenu.o $(OBJDIR_RELEASE)/src/program/game/ui/MainMenu.o $(OBJDIR_RELEASE)/src/program/game/ui/Journal.o $(OBJDIR_RELEASE)/src/program/game/ui/Inventory.o $(OBJDIR_RELEASE)/src/program/game/ui/BookOfSpells.o $(OBJDIR_RELEASE)/src/program/gui/Bar.o $(OBJDIR_RELEASE)/src/program/game/ui/Attributes.o $(OBJDIR_RELEASE)/src/program/game/fov/FOV.o $(OBJDIR_RELEASE)/src/program/game/entity/npc/Bandit.o $(OBJDIR_RELEASE)/src/program/game/entity/npc/Teacher.o $(OBJDIR_RELEASE)/src/program/path_finder/PathFinder.o $(OBJDIR_RELEASE)/src/program/path_finder/PathFinder_Node.o $(OBJDIR_RELEASE)/src/program/observer/Observer.o $(OBJDIR_RELEASE)/src/program/messages/MessageManager.o $(OBJDIR_RELEASE)/src/program/messages/Message.o $(OBJDIR_RELEASE)/src/program/gui/Window.o $(OBJDIR_RELEASE)/src/program/gui/Text.o $(OBJDIR_RELEASE)/src/program/gui/Switch.o $(OBJDIR_RELEASE)/src/program/game/entity/item/Rune.o $(OBJDIR_RELEASE)/src/program/gui/Slot.o $(OBJDIR_RELEASE)/src/program/gui/ScrollBar.o $(OBJDIR_RELEASE)/src/program/gui/Menu.o $(OBJDIR_RELEASE)/src/program/gui/Image.o $(OBJDIR_RELEASE)/src/program/gui/Checkbox.o $(OBJDIR_RELEASE)/src/program/gui/Button.o $(OBJDIR_RELEASE)/src/program/game/Level.o $(OBJDIR_RELEASE)/src/program/game/ui/HUD.o $(OBJDIR_RELEASE)/src/program/game/Game.o $(OBJDIR_RELEASE)/src/program/Settings.o $(OBJDIR_RELEASE)/src/program/Resources.o $(OBJDIR_RELEASE)/src/program/Program.o $(OBJDIR_RELEASE)/src/main.o $(OBJDIR_RELEASE)/lib/Animation.o $(OBJDIR_RELEASE)/src/program/game/entity/item/Potion.o $(OBJDIR_RELEASE)/src/program/game/entity/item/Food.o $(OBJDIR_RELEASE)/src/program/game/entity/item/ColdWeapon.o $(OBJDIR_RELEASE)/src/program/game/entity/item/Coin.o $(OBJDIR_RELEASE)/src/program/game/entity/item/Book.o $(OBJDIR_RELEASE)/lib/AnimatedSprite.o $(OBJDIR_RELEASE)/src/program/game/entity/Stairs.o $(OBJDIR_RELEASE)/src/program/game/entity/Shadow.o $(OBJDIR_RELEASE)/src/program/game/entity/Player.o $(OBJDIR_RELEASE)/src/program/game/entity/Door.o $(OBJDIR_RELEASE)/src/program/game/entity/Chest.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG)/src/program/game/ui || mkdir -p $(OBJDIR_DEBUG)/src/program/game/ui
	test -d $(OBJDIR_DEBUG)/src/program/gui || mkdir -p $(OBJDIR_DEBUG)/src/program/gui
	test -d $(OBJDIR_DEBUG)/src/program/game/fov || mkdir -p $(OBJDIR_DEBUG)/src/program/game/fov
	test -d $(OBJDIR_DEBUG)/src/program/game/entity/npc || mkdir -p $(OBJDIR_DEBUG)/src/program/game/entity/npc
	test -d $(OBJDIR_DEBUG)/src/program/observer || mkdir -p $(OBJDIR_DEBUG)/src/program/observer
	test -d $(OBJDIR_DEBUG)/src/program/path_finder || mkdir -p $(OBJDIR_DEBUG)/src/program/path_finder
	test -d $(OBJDIR_DEBUG)/src/program/messages || mkdir -p $(OBJDIR_DEBUG)/src/program/messages
	test -d $(OBJDIR_DEBUG)/src/program/game/entity/item || mkdir -p $(OBJDIR_DEBUG)/src/program/game/entity/item
	test -d $(OBJDIR_DEBUG)/src/program/game || mkdir -p $(OBJDIR_DEBUG)/src/program/game
	test -d $(OBJDIR_DEBUG)/src/program || mkdir -p $(OBJDIR_DEBUG)/src/program
	test -d $(OBJDIR_DEBUG)/src || mkdir -p $(OBJDIR_DEBUG)/src
	test -d $(OBJDIR_DEBUG)/lib || mkdir -p $(OBJDIR_DEBUG)/lib
	test -d $(OBJDIR_DEBUG)/src/program/game/entity || mkdir -p $(OBJDIR_DEBUG)/src/program/game/entity

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/src/program/game/ui/PauseMenu.o: src/program/game/ui/PauseMenu.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/ui/PauseMenu.cpp -o $(OBJDIR_DEBUG)/src/program/game/ui/PauseMenu.o

$(OBJDIR_DEBUG)/src/program/game/ui/MainMenu.o: src/program/game/ui/MainMenu.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/ui/MainMenu.cpp -o $(OBJDIR_DEBUG)/src/program/game/ui/MainMenu.o

$(OBJDIR_DEBUG)/src/program/game/ui/Journal.o: src/program/game/ui/Journal.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/ui/Journal.cpp -o $(OBJDIR_DEBUG)/src/program/game/ui/Journal.o

$(OBJDIR_DEBUG)/src/program/game/ui/Inventory.o: src/program/game/ui/Inventory.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/ui/Inventory.cpp -o $(OBJDIR_DEBUG)/src/program/game/ui/Inventory.o

$(OBJDIR_DEBUG)/src/program/game/ui/BookOfSpells.o: src/program/game/ui/BookOfSpells.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/ui/BookOfSpells.cpp -o $(OBJDIR_DEBUG)/src/program/game/ui/BookOfSpells.o

$(OBJDIR_DEBUG)/src/program/gui/Bar.o: src/program/gui/Bar.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/Bar.cpp -o $(OBJDIR_DEBUG)/src/program/gui/Bar.o

$(OBJDIR_DEBUG)/src/program/game/ui/Attributes.o: src/program/game/ui/Attributes.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/ui/Attributes.cpp -o $(OBJDIR_DEBUG)/src/program/game/ui/Attributes.o

$(OBJDIR_DEBUG)/src/program/game/fov/FOV.o: src/program/game/fov/FOV.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/fov/FOV.cpp -o $(OBJDIR_DEBUG)/src/program/game/fov/FOV.o

$(OBJDIR_DEBUG)/src/program/game/entity/npc/Bandit.o: src/program/game/entity/npc/Bandit.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/npc/Bandit.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/npc/Bandit.o

$(OBJDIR_DEBUG)/src/program/game/entity/npc/Teacher.o: src/program/game/entity/npc/Teacher.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/npc/Teacher.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/npc/Teacher.o

$(OBJDIR_DEBUG)/src/program/observer/Observer.o: src/program/observer/Observer.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/observer/Observer.cpp -o $(OBJDIR_DEBUG)/src/program/observer/Observer.o

$(OBJDIR_DEBUG)/src/program/path_finder/PathFinder.o: src/program/path_finder/PathFinder.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/path_finder/PathFinder.cpp -o $(OBJDIR_DEBUG)/src/program/path_finder/PathFinder.o

$(OBJDIR_DEBUG)/src/program/path_finder/PathFinder_Node.o: src/program/path_finder/PathFinder_Node.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/path_finder/PathFinder_Node.cpp -o $(OBJDIR_DEBUG)/src/program/path_finder/PathFinder_Node.o

$(OBJDIR_DEBUG)/src/program/messages/MessageManager.o: src/program/messages/MessageManager.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/messages/MessageManager.cpp -o $(OBJDIR_DEBUG)/src/program/messages/MessageManager.o

$(OBJDIR_DEBUG)/src/program/messages/Message.o: src/program/messages/Message.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/messages/Message.cpp -o $(OBJDIR_DEBUG)/src/program/messages/Message.o

$(OBJDIR_DEBUG)/src/program/gui/Window.o: src/program/gui/Window.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/Window.cpp -o $(OBJDIR_DEBUG)/src/program/gui/Window.o

$(OBJDIR_DEBUG)/src/program/gui/Text.o: src/program/gui/Text.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/Text.cpp -o $(OBJDIR_DEBUG)/src/program/gui/Text.o

$(OBJDIR_DEBUG)/src/program/gui/Switch.o: src/program/gui/Switch.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/Switch.cpp -o $(OBJDIR_DEBUG)/src/program/gui/Switch.o

$(OBJDIR_DEBUG)/src/program/game/entity/item/Rune.o: src/program/game/entity/item/Rune.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/item/Rune.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/item/Rune.o

$(OBJDIR_DEBUG)/src/program/gui/Slot.o: src/program/gui/Slot.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/Slot.cpp -o $(OBJDIR_DEBUG)/src/program/gui/Slot.o

$(OBJDIR_DEBUG)/src/program/gui/ScrollBar.o: src/program/gui/ScrollBar.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/ScrollBar.cpp -o $(OBJDIR_DEBUG)/src/program/gui/ScrollBar.o

$(OBJDIR_DEBUG)/src/program/gui/Menu.o: src/program/gui/Menu.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/Menu.cpp -o $(OBJDIR_DEBUG)/src/program/gui/Menu.o

$(OBJDIR_DEBUG)/src/program/gui/Image.o: src/program/gui/Image.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/Image.cpp -o $(OBJDIR_DEBUG)/src/program/gui/Image.o

$(OBJDIR_DEBUG)/src/program/gui/Checkbox.o: src/program/gui/Checkbox.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/Checkbox.cpp -o $(OBJDIR_DEBUG)/src/program/gui/Checkbox.o

$(OBJDIR_DEBUG)/src/program/gui/Button.o: src/program/gui/Button.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/gui/Button.cpp -o $(OBJDIR_DEBUG)/src/program/gui/Button.o

$(OBJDIR_DEBUG)/src/program/game/Level.o: src/program/game/Level.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/Level.cpp -o $(OBJDIR_DEBUG)/src/program/game/Level.o

$(OBJDIR_DEBUG)/src/program/game/ui/HUD.o: src/program/game/ui/HUD.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/ui/HUD.cpp -o $(OBJDIR_DEBUG)/src/program/game/ui/HUD.o

$(OBJDIR_DEBUG)/src/program/game/Game.o: src/program/game/Game.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/Game.cpp -o $(OBJDIR_DEBUG)/src/program/game/Game.o

$(OBJDIR_DEBUG)/src/program/Settings.o: src/program/Settings.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/Settings.cpp -o $(OBJDIR_DEBUG)/src/program/Settings.o

$(OBJDIR_DEBUG)/src/program/Resources.o: src/program/Resources.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/Resources.cpp -o $(OBJDIR_DEBUG)/src/program/Resources.o

$(OBJDIR_DEBUG)/src/program/Program.o: src/program/Program.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/Program.cpp -o $(OBJDIR_DEBUG)/src/program/Program.o

$(OBJDIR_DEBUG)/src/main.o: src/main.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/main.cpp -o $(OBJDIR_DEBUG)/src/main.o

$(OBJDIR_DEBUG)/lib/Animation.o: lib/Animation.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c lib/Animation.cpp -o $(OBJDIR_DEBUG)/lib/Animation.o

$(OBJDIR_DEBUG)/src/program/game/entity/item/Potion.o: src/program/game/entity/item/Potion.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/item/Potion.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/item/Potion.o

$(OBJDIR_DEBUG)/src/program/game/entity/item/Food.o: src/program/game/entity/item/Food.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/item/Food.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/item/Food.o

$(OBJDIR_DEBUG)/src/program/game/entity/item/ColdWeapon.o: src/program/game/entity/item/ColdWeapon.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/item/ColdWeapon.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/item/ColdWeapon.o

$(OBJDIR_DEBUG)/src/program/game/entity/item/Coin.o: src/program/game/entity/item/Coin.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/item/Coin.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/item/Coin.o

$(OBJDIR_DEBUG)/src/program/game/entity/item/Book.o: src/program/game/entity/item/Book.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/item/Book.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/item/Book.o

$(OBJDIR_DEBUG)/lib/AnimatedSprite.o: lib/AnimatedSprite.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c lib/AnimatedSprite.cpp -o $(OBJDIR_DEBUG)/lib/AnimatedSprite.o

$(OBJDIR_DEBUG)/src/program/game/entity/Stairs.o: src/program/game/entity/Stairs.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/Stairs.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/Stairs.o

$(OBJDIR_DEBUG)/src/program/game/entity/Shadow.o: src/program/game/entity/Shadow.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/Shadow.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/Shadow.o

$(OBJDIR_DEBUG)/src/program/game/entity/Player.o: src/program/game/entity/Player.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/Player.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/Player.o

$(OBJDIR_DEBUG)/src/program/game/entity/Door.o: src/program/game/entity/Door.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/Door.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/Door.o

$(OBJDIR_DEBUG)/src/program/game/entity/Chest.o: src/program/game/entity/Chest.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c src/program/game/entity/Chest.cpp -o $(OBJDIR_DEBUG)/src/program/game/entity/Chest.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)/src/program/game/ui
	rm -rf $(OBJDIR_DEBUG)/src/program/gui
	rm -rf $(OBJDIR_DEBUG)/src/program/game/fov
	rm -rf $(OBJDIR_DEBUG)/src/program/game/entity/npc
	rm -rf $(OBJDIR_DEBUG)/src/program/observer
	rm -rf $(OBJDIR_DEBUG)/src/program/path_finder
	rm -rf $(OBJDIR_DEBUG)/src/program/messages
	rm -rf $(OBJDIR_DEBUG)/src/program/game/entity/item
	rm -rf $(OBJDIR_DEBUG)/src/program/game
	rm -rf $(OBJDIR_DEBUG)/src/program
	rm -rf $(OBJDIR_DEBUG)/src
	rm -rf $(OBJDIR_DEBUG)/lib
	rm -rf $(OBJDIR_DEBUG)/src/program/game/entity

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE)/src/program/game/ui || mkdir -p $(OBJDIR_RELEASE)/src/program/game/ui
	test -d $(OBJDIR_RELEASE)/src/program/gui || mkdir -p $(OBJDIR_RELEASE)/src/program/gui
	test -d $(OBJDIR_RELEASE)/src/program/game/fov || mkdir -p $(OBJDIR_RELEASE)/src/program/game/fov
	test -d $(OBJDIR_RELEASE)/src/program/game/entity/npc || mkdir -p $(OBJDIR_RELEASE)/src/program/game/entity/npc
	test -d $(OBJDIR_RELEASE)/src/program/observer || mkdir -p $(OBJDIR_RELEASE)/src/program/observer
	test -d $(OBJDIR_RELEASE)/src/program/path_finder || mkdir -p $(OBJDIR_RELEASE)/src/program/path_finder
	test -d $(OBJDIR_RELEASE)/src/program/messages || mkdir -p $(OBJDIR_RELEASE)/src/program/messages
	test -d $(OBJDIR_RELEASE)/src/program/game/entity/item || mkdir -p $(OBJDIR_RELEASE)/src/program/game/entity/item
	test -d $(OBJDIR_RELEASE)/src/program/game || mkdir -p $(OBJDIR_RELEASE)/src/program/game
	test -d $(OBJDIR_RELEASE)/src/program || mkdir -p $(OBJDIR_RELEASE)/src/program
	test -d $(OBJDIR_RELEASE)/src || mkdir -p $(OBJDIR_RELEASE)/src
	test -d $(OBJDIR_RELEASE)/lib || mkdir -p $(OBJDIR_RELEASE)/lib
	test -d $(OBJDIR_RELEASE)/src/program/game/entity || mkdir -p $(OBJDIR_RELEASE)/src/program/game/entity

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/src/program/game/ui/PauseMenu.o: src/program/game/ui/PauseMenu.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/ui/PauseMenu.cpp -o $(OBJDIR_RELEASE)/src/program/game/ui/PauseMenu.o

$(OBJDIR_RELEASE)/src/program/game/ui/MainMenu.o: src/program/game/ui/MainMenu.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/ui/MainMenu.cpp -o $(OBJDIR_RELEASE)/src/program/game/ui/MainMenu.o

$(OBJDIR_RELEASE)/src/program/game/ui/Journal.o: src/program/game/ui/Journal.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/ui/Journal.cpp -o $(OBJDIR_RELEASE)/src/program/game/ui/Journal.o

$(OBJDIR_RELEASE)/src/program/game/ui/Inventory.o: src/program/game/ui/Inventory.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/ui/Inventory.cpp -o $(OBJDIR_RELEASE)/src/program/game/ui/Inventory.o

$(OBJDIR_RELEASE)/src/program/game/ui/BookOfSpells.o: src/program/game/ui/BookOfSpells.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/ui/BookOfSpells.cpp -o $(OBJDIR_RELEASE)/src/program/game/ui/BookOfSpells.o

$(OBJDIR_RELEASE)/src/program/gui/Bar.o: src/program/gui/Bar.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/Bar.cpp -o $(OBJDIR_RELEASE)/src/program/gui/Bar.o

$(OBJDIR_RELEASE)/src/program/game/ui/Attributes.o: src/program/game/ui/Attributes.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/ui/Attributes.cpp -o $(OBJDIR_RELEASE)/src/program/game/ui/Attributes.o

$(OBJDIR_RELEASE)/src/program/game/fov/FOV.o: src/program/game/fov/FOV.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/fov/FOV.cpp -o $(OBJDIR_RELEASE)/src/program/game/fov/FOV.o

$(OBJDIR_RELEASE)/src/program/game/entity/npc/Bandit.o: src/program/game/entity/npc/Bandit.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/npc/Bandit.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/npc/Bandit.o

$(OBJDIR_RELEASE)/src/program/game/entity/npc/Teacher.o: src/program/game/entity/npc/Teacher.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/npc/Teacher.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/npc/Teacher.o

$(OBJDIR_RELEASE)/src/program/observer/Observer.o: src/program/observer/Observer.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/observer/Observer.cpp -o $(OBJDIR_RELEASE)/src/program/observer/Observer.o

$(OBJDIR_RELEASE)/src/program/path_finder/PathFinder.o: src/program/path_finder/PathFinder.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_DEBUG) -c src/program/path_finder/PathFinder.cpp -o $(OBJDIR_RELEASE)/src/program/path_finder/PathFinder.o

$(OBJDIR_RELEASE)/src/program/path_finder/PathFinder_Node.o: src/program/path_finder/PathFinder_Node.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_DEBUG) -c src/program/path_finder/PathFinder_Node.cpp -o $(OBJDIR_RELEASE)/src/program/path_finder/PathFinder_Node.o

$(OBJDIR_RELEASE)/src/program/messages/MessageManager.o: src/program/messages/MessageManager.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/messages/MessageManager.cpp -o $(OBJDIR_RELEASE)/src/program/messages/MessageManager.o

$(OBJDIR_RELEASE)/src/program/messages/Message.o: src/program/messages/Message.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/messages/Message.cpp -o $(OBJDIR_RELEASE)/src/program/messages/Message.o

$(OBJDIR_RELEASE)/src/program/gui/Window.o: src/program/gui/Window.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/Window.cpp -o $(OBJDIR_RELEASE)/src/program/gui/Window.o

$(OBJDIR_RELEASE)/src/program/gui/Text.o: src/program/gui/Text.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/Text.cpp -o $(OBJDIR_RELEASE)/src/program/gui/Text.o

$(OBJDIR_RELEASE)/src/program/gui/Switch.o: src/program/gui/Switch.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/Switch.cpp -o $(OBJDIR_RELEASE)/src/program/gui/Switch.o

$(OBJDIR_RELEASE)/src/program/game/entity/item/Rune.o: src/program/game/entity/item/Rune.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/item/Rune.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/item/Rune.o

$(OBJDIR_RELEASE)/src/program/gui/Slot.o: src/program/gui/Slot.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/Slot.cpp -o $(OBJDIR_RELEASE)/src/program/gui/Slot.o

$(OBJDIR_RELEASE)/src/program/gui/ScrollBar.o: src/program/gui/ScrollBar.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/ScrollBar.cpp -o $(OBJDIR_RELEASE)/src/program/gui/ScrollBar.o

$(OBJDIR_RELEASE)/src/program/gui/Menu.o: src/program/gui/Menu.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/Menu.cpp -o $(OBJDIR_RELEASE)/src/program/gui/Menu.o

$(OBJDIR_RELEASE)/src/program/gui/Image.o: src/program/gui/Image.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/Image.cpp -o $(OBJDIR_RELEASE)/src/program/gui/Image.o

$(OBJDIR_RELEASE)/src/program/gui/Checkbox.o: src/program/gui/Checkbox.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/Checkbox.cpp -o $(OBJDIR_RELEASE)/src/program/gui/Checkbox.o

$(OBJDIR_RELEASE)/src/program/gui/Button.o: src/program/gui/Button.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/gui/Button.cpp -o $(OBJDIR_RELEASE)/src/program/gui/Button.o

$(OBJDIR_RELEASE)/src/program/game/Level.o: src/program/game/Level.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/Level.cpp -o $(OBJDIR_RELEASE)/src/program/game/Level.o

$(OBJDIR_RELEASE)/src/program/game/ui/HUD.o: src/program/game/ui/HUD.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/ui/HUD.cpp -o $(OBJDIR_RELEASE)/src/program/game/ui/HUD.o

$(OBJDIR_RELEASE)/src/program/game/Game.o: src/program/game/Game.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/Game.cpp -o $(OBJDIR_RELEASE)/src/program/game/Game.o

$(OBJDIR_RELEASE)/src/program/Settings.o: src/program/Settings.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/Settings.cpp -o $(OBJDIR_RELEASE)/src/program/Settings.o

$(OBJDIR_RELEASE)/src/program/Resources.o: src/program/Resources.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/Resources.cpp -o $(OBJDIR_RELEASE)/src/program/Resources.o

$(OBJDIR_RELEASE)/src/program/Program.o: src/program/Program.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/Program.cpp -o $(OBJDIR_RELEASE)/src/program/Program.o

$(OBJDIR_RELEASE)/src/main.o: src/main.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/main.cpp -o $(OBJDIR_RELEASE)/src/main.o

$(OBJDIR_RELEASE)/lib/Animation.o: lib/Animation.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c lib/Animation.cpp -o $(OBJDIR_RELEASE)/lib/Animation.o

$(OBJDIR_RELEASE)/src/program/game/entity/item/Potion.o: src/program/game/entity/item/Potion.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/item/Potion.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/item/Potion.o

$(OBJDIR_RELEASE)/src/program/game/entity/item/Food.o: src/program/game/entity/item/Food.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/item/Food.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/item/Food.o

$(OBJDIR_RELEASE)/src/program/game/entity/item/ColdWeapon.o: src/program/game/entity/item/ColdWeapon.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/item/ColdWeapon.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/item/ColdWeapon.o

$(OBJDIR_RELEASE)/src/program/game/entity/item/Coin.o: src/program/game/entity/item/Coin.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/item/Coin.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/item/Coin.o

$(OBJDIR_RELEASE)/src/program/game/entity/item/Book.o: src/program/game/entity/item/Book.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/item/Book.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/item/Book.o

$(OBJDIR_RELEASE)/lib/AnimatedSprite.o: lib/AnimatedSprite.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c lib/AnimatedSprite.cpp -o $(OBJDIR_RELEASE)/lib/AnimatedSprite.o

$(OBJDIR_RELEASE)/src/program/game/entity/Stairs.o: src/program/game/entity/Stairs.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/Stairs.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/Stairs.o

$(OBJDIR_RELEASE)/src/program/game/entity/Shadow.o: src/program/game/entity/Shadow.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/Shadow.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/Shadow.o

$(OBJDIR_RELEASE)/src/program/game/entity/Player.o: src/program/game/entity/Player.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/Player.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/Player.o

$(OBJDIR_RELEASE)/src/program/game/entity/Door.o: src/program/game/entity/Door.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/Door.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/Door.o

$(OBJDIR_RELEASE)/src/program/game/entity/Chest.o: src/program/game/entity/Chest.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c src/program/game/entity/Chest.cpp -o $(OBJDIR_RELEASE)/src/program/game/entity/Chest.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)/src/program/game/ui
	rm -rf $(OBJDIR_RELEASE)/src/program/gui
	rm -rf $(OBJDIR_RELEASE)/src/program/game/fov
	rm -rf $(OBJDIR_RELEASE)/src/program/game/entity/npc
	rm -rf $(OBJDIR_RELEASE)/src/program/observer
	rm -rf $(OBJDIR_RELEASE)/src/program/path_finder
	rm -rf $(OBJDIR_RELEASE)/src/program/messages
	rm -rf $(OBJDIR_RELEASE)/src/program/game/entity/item
	rm -rf $(OBJDIR_RELEASE)/src/program/game
	rm -rf $(OBJDIR_RELEASE)/src/program
	rm -rf $(OBJDIR_RELEASE)/src
	rm -rf $(OBJDIR_RELEASE)/lib
	rm -rf $(OBJDIR_RELEASE)/src/program/game/entity

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

