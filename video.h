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

class GameboyCPU;
class Video
{
private:
    GameboyCPU* cpu;
    GxEPD_Class* display;

    uint8_t registers[VideoRegisterType::WX + 1];
    uint8_t framebuffer[160 * 144];

    long cycles, cycles_extra;
    long background_tilemap;
    long window_tilemap;
    long active_tileset;

    bool scanline_transferred;
    long vblank;
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
