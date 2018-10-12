SRC_DIR := src
INC_DIR := contrib/ace/include
BUILD_DIR := build
LIB_DIR := contrib/ace/lib
BIN_DIR := bin

GAME_NAME := $(shell basename $(shell pwd))
GAME_FILES := $(shell find $(SRC_DIR) -name "*.c")
GAME_OBJECTS := $(patsubst $(SRC_DIR)%, $(BUILD_DIR)%, $(GAME_FILES:.c=.o))
ACE_OBJECTS := $(shell find contrib/ace/build/ -name "*.o")

CC := vc +kick13
CC_FLAGS := -c99 -I$(SRC_DIR) -I$(INC_DIR) -DAMIGA -DACE_DEBUG
LINK_FLAGS := -L$(LIB_DIR) -lamiga -lace -lfixmath -lpario

.PHONY: game clean all gfx

game: $(GAME_OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CC_FLAGS) $(LINK_FLAGS) -o $(BIN_DIR)/$(GAME_NAME) $^

clean:
	@rm -drf $(BUILD_DIR)

all: clean game

gfx:
	./contrib/ace/tools/palette_conv/palette_conv.exe res/colors.gpl data/colors.plt

	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/background.png -o data/background.bm

	mkdir -p data/ship_frames
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/ship_frames/ship_0000_-2.png -o data/ship_frames/ship_0.bm -mo data/ship_frames/ship_0.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/ship_frames/ship_0001_-1.png -o data/ship_frames/ship_1.bm -mo data/ship_frames/ship_1.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/ship_frames/ship_0002_0.png -o data/ship_frames/ship_2.bm -mo data/ship_frames/ship_2.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/ship_frames/ship_0003_1.png -o data/ship_frames/ship_3.bm -mo data/ship_frames/ship_3.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/ship_frames/ship_0004_2.png -o data/ship_frames/ship_4.bm -mo data/ship_frames/ship_4.msk -mc \#FF00FF

	mkdir -p data/engine_frames
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/engine_frames/engine_0000_0.png -o data/engine_frames/engine_0.bm -mo data/engine_frames/engine_0.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/engine_frames/engine_0001_1.png -o data/engine_frames/engine_1.bm -mo data/engine_frames/engine_1.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/engine_frames/engine_0002_2.png -o data/engine_frames/engine_2.bm -mo data/engine_frames/engine_2.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/engine_frames/engine_0003_3.png -o data/engine_frames/engine_3.bm -mo data/engine_frames/engine_3.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/engine_frames/engine_0004_4.png -o data/engine_frames/engine_4.bm -mo data/engine_frames/engine_4.msk -mc \#FF00FF

	mkdir -p data/projectile_frames
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/projectile_frames/projectile_0000_0.png -o data/projectile_frames/projectile_0.bm -mo data/projectile_frames/projectile_0.msk -mc \#FF00FF

	mkdir -p data/monster_1_frames
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_1_frames/monster_1_0000_0.png -o data/monster_1_frames/monster_1_0.bm -mo data/monster_1_frames/monster_1_0.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_1_frames/monster_1_0001_1.png -o data/monster_1_frames/monster_1_1.bm -mo data/monster_1_frames/monster_1_1.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_1_frames/monster_1_0002_2.png -o data/monster_1_frames/monster_1_2.bm -mo data/monster_1_frames/monster_1_2.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_1_frames/monster_1_0003_3.png -o data/monster_1_frames/monster_1_3.bm -mo data/monster_1_frames/monster_1_3.msk -mc \#FF00FF

	mkdir -p data/monster_2_frames
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_2_frames/monster_2_0000_0.png -o data/monster_2_frames/monster_2_0.bm -mo data/monster_2_frames/monster_2_0.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_2_frames/monster_2_0001_1.png -o data/monster_2_frames/monster_2_1.bm -mo data/monster_2_frames/monster_2_1.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_2_frames/monster_2_0002_2.png -o data/monster_2_frames/monster_2_2.bm -mo data/monster_2_frames/monster_2_2.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_2_frames/monster_2_0003_3.png -o data/monster_2_frames/monster_2_3.bm -mo data/monster_2_frames/monster_2_3.msk -mc \#FF00FF

	mkdir -p data/monster_3_frames
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_3_frames/monster_3_0000_0.png -o data/monster_3_frames/monster_3_0.bm -mo data/monster_3_frames/monster_3_0.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_3_frames/monster_3_0001_1.png -o data/monster_3_frames/monster_3_1.bm -mo data/monster_3_frames/monster_3_1.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_3_frames/monster_3_0002_2.png -o data/monster_3_frames/monster_3_2.bm -mo data/monster_3_frames/monster_3_2.msk -mc \#FF00FF
	./contrib/ace/tools/bitmap_conv/bitmap_conv.exe data/colors.plt res/monster_3_frames/monster_3_0003_3.png -o data/monster_3_frames/monster_3_3.bm -mo data/monster_3_frames/monster_3_3.msk -mc \#FF00FF

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c -o $@ $<