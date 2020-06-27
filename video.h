#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "board_config.h"

enum VideoRegisterType
{
    LCDC,
    STAT,
    SCY,
    SCX,
    LY,
    LYC,
    DMA,
    BGP,
    OBP0,
    OBP1,
    WY,
    WX
};

enum VideoMode
{
    HBlank,
    VBlank,
    ReadingOAM,
    ReadingOAMVRAM
};

struct Sprite
{
    long x;
    long y;
    long tile;
    long flags;

    long vram;
    bool flip_x;
    bool flip_y;

    long color_palette;
    long palette;

    bool priority;
};

class GameboyCPU;
class Video
{
private:
    GameboyCPU* cpu;
    GxEPD_Class* display;

    Sprite sprites[0x40];
    uint8_t registers[VideoRegisterType::WX + 1];
    uint8_t* framebuffer;
    uint8_t* framebuffer_numbers;

    long cycles, cycles_extra;
    long background_tilemap;
    long window_tilemap;
    long active_tileset;

    bool scanline_transferred;
    long vblank;

    int frame_skip;
public:
    Video(GameboyCPU* cpu, GxEPD_Class* display);

    long read_register(VideoRegisterType reg);
    void write_register(VideoRegisterType reg, long data);

    void tick(long delta);
    void render();
    void render_scanline();
    void render_background();
    void render_window();
    void render_sprites();

    void oam_write(long position, long data);

    static Video* instance;
};

#endif
