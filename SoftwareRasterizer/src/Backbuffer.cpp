#include "BackBuffer.h"

using namespace SR;

void Backbuffer::Resize(WindowCoord width, WindowCoord height)
{
    if (width <= 0 || height <= 0)
    {
        return;
    }

    _width = width;
    _height = height;
    
    _info = {};
    _info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    _info.bmiHeader.biWidth = width;
    _info.bmiHeader.biHeight = -height; // top-down
    _info.bmiHeader.biPlanes = 1;
    _info.bmiHeader.biBitCount = 32;
    _info.bmiHeader.biCompression = BI_RGB;

    const size_t size = static_cast<size_t>(width) * static_cast<size_t>(height) * 4;
    _pixels.resize(size);
}

void Backbuffer::Clear(Color32 color)
{
    const WindowCoord pixelCount = _width * _height;
    for (WindowCoord i = 0; i < pixelCount; ++i)
    {
        _pixels[i] = color;
    }
}

void Backbuffer::PutPixel(WindowCoord x, WindowCoord y, Color32 color)
{
    if (_pixels.empty())
    {
        return;
    }
    
    if (x < 0 || y < 0 || x >= _width || y >= _height)
    {
        return;
    }

    _pixels[y * _width + x] = color;
}

void Backbuffer::Present(HDC dc, WindowCoord width, WindowCoord height) const
{
    if (_pixels.empty())
    {
        return;
    }
    
    StretchDIBits
    (
        dc,
        0, 0, width, height,
        0, 0, _width, _height,
        _pixels.data(),
        &_info,
        DIB_RGB_COLORS,
        SRCCOPY
    );
}