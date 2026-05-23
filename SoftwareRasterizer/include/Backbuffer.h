#pragma once

#include <windows.h>
#include <cstdint>
#include <vector>

#include "Color32.h"
#include "Types.h"

namespace SR
{
    typedef u32 WindowCoord;
    
    class Backbuffer
    {
    public:
        Backbuffer()
        {
            _pixels.reserve(2560 * 1440);
        }
        
        void Resize(WindowCoord width, WindowCoord height);
        void Clear(Color32 color);
        void PutPixel(WindowCoord x, WindowCoord y, Color32 color);
        void Present(HDC dc, WindowCoord width, WindowCoord height) const;
    
        [[nodiscard]] WindowCoord GetWidth() const { return _width; }
        [[nodiscard]] WindowCoord GetHeight() const { return _height; }
    
    private:
        std::vector<Color32> _pixels;
        
        WindowCoord _width = 0;
        WindowCoord _height = 0;
        
        // format description of backbuffer for Win32
        BITMAPINFO _info = {};
    };
}
