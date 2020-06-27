#include "video.h"
#include "gameboy_cpu.h"
#include "memory.h"

Video *Video::instance = nullptr;

static long bit_get(long input, long bit)
{
    return input & (1 << bit) ? 1 : 0;
}

static uint8_t get_color(long palette, long bit, bool transparent)
{
    auto hi = ((bit << 1) + 1);
    auto lo = (bit << 1);
    auto color = (bit_get(palette, hi) << 1) | (bit_get(palette, lo));

    if (bit == 0 && transparent)
    {
        return 0;
    }

    return color;
}

static long read_register(long location)
{
    switch (location)
    {
    case 0xFF40: //LCDC
        return Video::instance->read_register(VideoRegisterType::LCDC);

    case 0xFF41: //STAT
        return Video::instance->read_register(VideoRegisterType::STAT);

    case 0xFF42: //SCY
        return Video::instance->read_register(VideoRegisterType::SCY);

    case 0xFF43: //SCX
        return Video::instance->read_register(VideoRegisterType::SCX);

    case 0xFF44: //LY
        return Video::instance->read_register(VideoRegisterType::LY);

    case 0xFF45: //LYC
        return Video::instance->read_register(VideoRegisterType::LYC);

    case 0xFF46: //DMA
        return Video::instance->read_register(VideoRegisterType::DMA);

    case 0xFF47: //BGP
        return Video::instance->read_register(VideoRegisterType::BGP);

    case 0xFF48: //OBP0
        return Video::instance->read_register(VideoRegisterType::OBP0);

    case 0xFF49: //OBP1
        return Video::instance->read_register(VideoRegisterType::OBP1);

    case 0xFF4A: //WY
        return Video::instance->read_register(VideoRegisterType::WY);

    case 0xFF4B: //WX
        return Video::instance->read_register(VideoRegisterType::WX);
    }
}

static void write_register(long location, long data)
{
    switch (location)
    {
    case 0xFF40: //LCDC
        Video::instance->write_register(VideoRegisterType::LCDC, data);
        return;

    case 0xFF41: //STAT
        Video::instance->write_register(VideoRegisterType::STAT, data);
        return;

    case 0xFF42: //SCY
        Video::instance->write_register(VideoRegisterType::SCY, data);
        return;

    case 0xFF43: //SCX
        Video::instance->write_register(VideoRegisterType::SCX, data);
        return;

    case 0xFF44: //LY
        Video::instance->write_register(VideoRegisterType::LY, data);
        return;

    case 0xFF45: //LYC
        Video::instance->write_register(VideoRegisterType::LYC, data);
        return;

    case 0xFF46: //DMA
        Video::instance->write_register(VideoRegisterType::DMA, data);
        return;

    case 0xFF47: //BGP
        Video::instance->write_register(VideoRegisterType::BGP, data);
        return;

    case 0xFF48: //OBP0
        Video::instance->write_register(VideoRegisterType::OBP0, data);
        return;

    case 0xFF49: //OBP1
        Video::instance->write_register(VideoRegisterType::OBP1, data);
        return;

    case 0xFF4A: //WY
        Video::instance->write_register(VideoRegisterType::WY, data);
        return;

    case 0xFF4B: //WX
        Video::instance->write_register(VideoRegisterType::WX, data);
        return;
    }
}

Video::Video(GameboyCPU *cpu, GxEPD_Class *display)
{
    this->cpu = cpu;
    this->display = display;

    instance = this;

    framebuffer = new uint8_t[160 * 144];
    framebuffer_numbers = new uint8_t[160 * 144];

    frame_skip = 0;

    memset(framebuffer, 0, 160 * 144 * sizeof(uint8_t));
    memset(framebuffer_numbers, 0, 160 * 144 * sizeof(uint8_t));
    memset(registers, 0, (VideoRegisterType::WX + 1) * sizeof(uint8_t));
    memset(sprites, 0, 0x40 * sizeof(Sprite));

    auto memory = cpu->get_memory();
    memory->add_register(0xFF40, &::read_register, &::write_register);
    memory->add_register(0xFF41, &::read_register, &::write_register);
    memory->add_register(0xFF42, &::read_register, &::write_register);
    memory->add_register(0xFF43, &::read_register, &::write_register);
    memory->add_register(0xFF44, &::read_register, &::write_register);
    memory->add_register(0xFF45, &::read_register, &::write_register);
    memory->add_register(0xFF46, &::read_register, &::write_register);
    memory->add_register(0xFF47, &::read_register, &::write_register);
    memory->add_register(0xFF48, &::read_register, &::write_register);
    memory->add_register(0xFF49, &::read_register, &::write_register);
    memory->add_register(0xFF4A, &::read_register, &::write_register);
    memory->add_register(0xFF4B, &::read_register, &::write_register);
}

void Video::tick(long delta)
{
    auto control = read_register(VideoRegisterType::LCDC);

    if (!(control & (1 << 7)))
    {
        registers[VideoRegisterType::LY] = 0;
        registers[VideoRegisterType::STAT] = (registers[VideoRegisterType::STAT] & ~0x03);
        cycles = 0;

        return;
    }

    background_tilemap = (control & (1 << 3)) ? 1 : 0;
    window_tilemap = (control & (1 << 6)) ? 1 : 0;
    active_tileset = (control & (1 << 4)) ? 1 : 0;
    cycles += delta;
    cycles_extra += delta;

    auto mode = registers[VideoRegisterType::STAT] & 0x03;

    switch (mode)
    {
    case VideoMode::HBlank:
        if (cycles >= 204)
        {
            cycles -= 204;
            registers[VideoRegisterType::LY]++;

            if (registers[VideoRegisterType::LY] == registers[VideoRegisterType::LYC])
            {
                registers[VideoRegisterType::STAT] |= 1 << 2;
            }
            else
            {
                registers[VideoRegisterType::STAT] &= ~(1 << 2);
            }

            if (registers[VideoRegisterType::LY] == 144)
            {
                render();
                vblank = 0;

                registers[VideoRegisterType::STAT] = ((registers[VideoRegisterType::STAT] & ~0x03) | VideoMode::VBlank);
                cpu->request_interrupt(Interrupt::VBlankInterrupt);

                if ((registers[VideoRegisterType::STAT] & (1 << 4)) != 0)
                {
                    cpu->request_interrupt(Interrupt::LCDStatInterrupt);
                }
            }
            else
            {
                if ((registers[VideoRegisterType::STAT] & (1 << 5)) != 0)
                {
                    cpu->request_interrupt(Interrupt::LCDStatInterrupt);
                }

                if ((registers[VideoRegisterType::STAT] & (1 << 6)) != 0 && registers[VideoRegisterType::LY] == registers[VideoRegisterType::LYC])
                {
                    cpu->request_interrupt(Interrupt::LCDStatInterrupt);
                }

                registers[VideoRegisterType::STAT] = ((registers[VideoRegisterType::STAT] & ~0x03) | VideoMode::ReadingOAM);
            }
        }
        break;

    case VideoMode::VBlank:
        while (cycles_extra > 456)
        {
            cycles_extra -= 456;
            vblank++;
        }

        if (cycles >= 4560)
        {
            cycles -= 4560;
            registers[VideoRegisterType::STAT] = ((registers[VideoRegisterType::STAT] & ~0x03) | VideoMode::ReadingOAM);
        }
        break;

    case VideoMode::ReadingOAM:
        if (cycles >= 80)
        {
            cycles -= 80;
            scanline_transferred = false;
            registers[VideoRegisterType::STAT] = ((registers[VideoRegisterType::STAT] & ~0x03) | VideoMode::ReadingOAMVRAM);
        }
        break;

    case VideoMode::ReadingOAMVRAM:
        if (cycles >= 160 && !scanline_transferred)
        {
            render_scanline();
            scanline_transferred = true;
        }

        if (cycles >= 172)
        {
            cycles -= 172;
            registers[VideoRegisterType::STAT] = ((registers[VideoRegisterType::STAT] & ~0x03) | VideoMode::HBlank);

            if ((registers[VideoRegisterType::STAT] & (1 << 3)) != 0)
            {
                cpu->request_interrupt(Interrupt::LCDStatInterrupt);
            }
        }
        break;
    }
}

long Video::read_register(VideoRegisterType reg)
{
    if (reg > VideoRegisterType::WX)
    {
        return 0xFF;
    }

    auto val = registers[reg];

    switch (reg)
    {
    case VideoRegisterType::STAT:
        val |= 0b10000000;
        break;
    }

    return val;
}

void Video::write_register(VideoRegisterType reg, long value)
{
    switch (reg)
    {
        case VideoRegisterType::DMA:
            cpu->get_memory()->perform_oam_dma_transfer(value * 0x100);
            break;

        case VideoRegisterType::LCDC:
            if (!(value & (1 << 7)))
            {
                for (auto x = 0; x < 160; x++)
                {
                    for (auto y = 0; y < 144; y++)
                    {
                        auto index = (y * 160) + x;

                        framebuffer[index] = 0xFF;
                    }
                }

                render();
            }
            break;

        case VideoRegisterType::LY:
            return;
    }

    registers[reg] = value;
}

void Video::render_scanline()
{
    render_background();
    render_window();
    render_sprites();
}

void Video::render()
{
    if (frame_skip < 2)
    {
        frame_skip++;
        return;
    }

    frame_skip = 0;

    float y_scaling = 122.0f / 144.0f;

    for (long x = 0; x < 160; x++)
    {
        for (long y = 0; y < 144; y++)
        {
            long index = (y * 160) + x;

            long render_y = y * y_scaling;

            if (framebuffer[index] > 0)
            {
                display->writePixel(x, render_y, GxEPD_BLACK);
            }
            else
            {
                display->writePixel(x, render_y, GxEPD_WHITE);
            }
        }
    }

    display->updateWindow(0, 0, 160, 122);
}

void Video::render_window()
{
    if ((registers[VideoRegisterType::LCDC] & (1 << 5)) == 0)
    {
        return;
    }

    auto LY = registers[VideoRegisterType::LY];
    auto BGP = registers[VideoRegisterType::BGP];

    auto base = window_tilemap ? 0x9C00 : 0x9800;
    auto tileBase = active_tileset ? 0x8000 : 0x9000;

    auto wx = registers[VideoRegisterType::WX] - 7;
    auto wy = registers[VideoRegisterType::WY];

    if (wx > 159)
    {
        return;
    }

    if ((wy > 143) || (wy > LY))
    {
        return;
    }

    auto winY = LY - wy;
    long tileY = ((long)floor(winY / 8.0f)) % 32;
    auto tileYOffset = winY % 8;

    long tx = -1;
    long byte1 = 0;
    long byte2 = 0;
    auto tileFlipX = false;
    auto tileFlipY = false;
    auto tilePriority = false;
    long tileBank = 0;
    long tilePalette = 0;

    for (long x = 0; x < 160; x++)
    {
        if ((wx + x) < 0 || (wx + x) >= 160)
        {
            continue;
        }

        long tileX = ((long)floor(x / 8.0f)) % 32;

        if (tx != tileX)
        {
            auto tileMapAddr = base + (tileY * 32) + tileX;
            auto tileNumber = cpu->get_memory()->read_video_ram(tileMapAddr, 0);

            // Read tileValue as signed
            if (!active_tileset)
            {
                auto msb_mask = 1 << (8 - 1);
                tileNumber = (tileNumber ^ msb_mask) - msb_mask;
            }

            auto offset = tileFlipY ? 7 - tileYOffset : tileYOffset;
            auto tileAddr = tileBase + tileNumber * 0x10 + (offset * 2);

            byte1 = cpu->get_memory()->read_video_ram(tileAddr, tileBank);
            byte2 = cpu->get_memory()->read_video_ram(tileAddr + 1, tileBank);

            tx = tileX;
        }

        auto bit = 7 - (x % 8);

        auto color_num = (bit_get(byte2, bit) << 1) | (bit_get(byte1, bit));
        auto index = (LY * 160) + wx + x;

        framebuffer[index] = get_color(BGP, color_num, false);
        framebuffer_numbers[index] = color_num;
    }
}

void Video::render_background()
{
    if ((registers[VideoRegisterType::LCDC] & (1 << 0)) == 0)
    {
        return;
    }

    auto LY = registers[VideoRegisterType::LY];
    auto SCX = registers[VideoRegisterType::SCX];
    auto SCY = registers[VideoRegisterType::SCY];
    auto BGP = registers[VideoRegisterType::BGP];

    auto base = background_tilemap ? 0x9C00 : 0x9800;
    auto tileBase = active_tileset ? 0x8000 : 0x9000;

    long tileY = ((long)floor((LY + SCY) / 8.0f)) % 32;
    auto tileYOffset = (LY + SCY) % 8;

    long tx = -1;
    long byte1 = 0;
    long byte2 = 0;
    bool tileFlipX = false;
    bool tileFlipY = false;
    bool tilePriority = false;
    long tileBank = 0;
    long tilePalette = 0;

    for (long x = 0; x < 160; x++)
    {
        long tileX = ((long)floor((SCX + x) / 8.0f)) % 32;

        if (tx != tileX)
        {
            auto tileMapAddr = base + (tileY * 32) + tileX;
            auto tileNumber = cpu->get_memory()->read_video_ram(tileMapAddr, 0);

            tileFlipX = false;
            tileFlipY = false;
            tilePriority = false;
            tilePalette = 0;
            tileBank = 0;

            // Read tileValue as signed
            if (!active_tileset)
            {
                auto msb_mask = 1 << (8 - 1);
                tileNumber = (tileNumber ^ msb_mask) - msb_mask;
            }

            auto offset = tileFlipY ? 7 - tileYOffset : tileYOffset;
            auto tileAddr = tileBase + tileNumber * 0x10 + (offset * 2);

            byte1 = cpu->get_memory()->read_video_ram(tileAddr, tileBank);
            byte2 = cpu->get_memory()->read_video_ram(tileAddr + 1, tileBank);

            tx = tileX;
        }

        auto tmp_x = ((SCX + x) % 8);
        auto bit = tileFlipX ? 7 - (7 - tmp_x) : 7 - tmp_x;

        auto color_num = (bit_get(byte2, bit) << 1) | (bit_get(byte1, bit));
        auto base_index = (LY * 160) + x;

        framebuffer[base_index] = get_color(BGP, color_num, false);
        framebuffer_numbers[base_index] = color_num;
    }
}

void Video::render_sprites()
{
    if ((registers[VideoRegisterType::LCDC] & (1 << 1)) == 0) {
        return;
    }

    auto width = 8;
    auto height = (registers[VideoRegisterType::LCDC] & (1 << 2)) ? 16 : 8;
    auto tileBase = 0x8000;

    auto LY = registers[VideoRegisterType::LY];

    for (long i = 0; i < 40; i++) {
        auto sprite = sprites[i];
        auto tile = height == 16 ? sprite.tile & ~0x01 : sprite.tile;

        if (LY < sprite.y || LY >= sprite.y + height) {
            continue;
        }

        auto sprite_y = LY - sprite.y;

        if (sprite.flip_y) {
            sprite_y = height - sprite_y - 1;
        }

        for (long spriteX = 0; spriteX < width; spriteX++) {
            auto pixelX = sprite.x + spriteX;
            auto tileAddr = tileBase + tile * 16 + (sprite_y * 2);

            if (pixelX < 0 || pixelX >= 160) {
                continue;
            }
            
            auto byte1 = cpu->get_memory()->read_video_ram(tileAddr, sprite.vram);
            auto byte2 = cpu->get_memory()->read_video_ram(tileAddr + 1, sprite.vram);

            auto bit = 7 - spriteX;

            if (sprite.flip_x) {
                bit = 7 - (7 - spriteX);
            }

            auto colorNum = (bit_get(byte2, bit) << 1) | (bit_get(byte1, bit));

            auto color = get_color(registers[sprite.palette], colorNum, true);
            auto base_index = (LY * 160) + pixelX;

            if (sprite.priority)
            {
                if (framebuffer_numbers[base_index] != 0)
                {
                    continue;
                }
            }

            framebuffer[base_index] = get_color(registers[sprite.palette], colorNum, true);
        }
    }
}

void Video::oam_write(long position, long data)
{
    long sprite = floor(position / 4);
    long attrib = position - (sprite * 4);

    switch (attrib)
    {
        case 0:
            sprites[sprite].y = data - 16;
            break;
        
        case 1:
            sprites[sprite].x = data - 8;
            break;
        
        case 2:
            sprites[sprite].tile = data;
            break;
        
        case 3:
            sprites[sprite].flags = data;
            sprites[sprite].vram = 0;
            sprites[sprite].flip_x = data & (1 << 5) ? true : false;
            sprites[sprite].flip_y = data & (1 << 6) ? true : false;
            sprites[sprite].color_palette = data & 0x07;
            sprites[sprite].palette = data & (1 << 4) ? VideoRegisterType::OBP1 : VideoRegisterType::OBP0;
            sprites[sprite].priority = (data & (1 << 7)) != 0;
            break;
    }
}
