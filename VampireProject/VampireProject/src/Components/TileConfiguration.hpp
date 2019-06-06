#ifndef HEX_TILE_CONFIGURATION_H_
#define HEX_TILE_CONFIGURATION_H_

#define TILE_TYPE_EMPTY 0
#define TILE_TYPE_ANY   1
#define TILE_TYPE_RED   2
#define TILE_TYPE_GREEN 3
#define TILE_TYPE_BLUE  4

#define TILE_DIR_ANY    0
#define TILE_DIR_NONE   1
#define TILE_DIR_RIGHT  2
#define TILE_DIR_LEFT   3

#define TILE_COLOR_BLACK 0x00000000
#define TILE_COLOR_WHITE 0xFFFFFFFF
#define TILE_COLOR_RED   0xFF0000FF
#define TILE_COLOR_GREEN 0x00FF00FF
#define TILE_COLOR_BLUE  0x0000FFFF

struct TileConfiguration {
    TileConfiguration(unsigned char type = TILE_TYPE_EMPTY, unsigned char dir = TILE_DIR_ANY) : mType(type), mDir(dir) { };

    unsigned char mType;
    unsigned char mDir;

    unsigned int GetColor() {
        switch (mType) {
            case TILE_TYPE_EMPTY : return TILE_COLOR_BLACK;
            case TILE_TYPE_ANY   : return TILE_COLOR_WHITE;
            case TILE_TYPE_RED   : return TILE_COLOR_RED  ;
            case TILE_TYPE_GREEN : return TILE_COLOR_GREEN;
            case TILE_TYPE_BLUE  : return TILE_COLOR_BLUE ;
        }
        return 0;
    }

    float GetNormDir() {
        switch (mDir) {
            case TILE_DIR_ANY    : return 0;
            case TILE_DIR_NONE   : return 0;
            case TILE_DIR_RIGHT  : return 1;
            case TILE_DIR_LEFT   : return -1;
        }
    }
};

#endif // HEX_TILE_CONFIGURATION_H_
