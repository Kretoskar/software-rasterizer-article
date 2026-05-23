#pragma once
#include <windows.h>

#include "BackBuffer.h"
#include "Types.h"

namespace SR
{
    class Window
    {
    public:
        Window(HINSTANCE instance, i16 width, i16 height, const wchar_t* title)
            : _instance(instance)
        {
            Register();
            Create(width, height, title);
        }

        ~Window();
        
        bool ProcessMessages();
        void Show(i32 cmdShow);
        void Present();
        
        [[nodiscard]] HWND GetHandle() const { return _hwnd; }
        [[nodiscard]] Backbuffer& GetBackbuffer() { return _backbuffer; }

    private:
        void Register();
        void Create(int width, int height, const wchar_t* title);
        static LRESULT CALLBACK StaticWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
        LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

        HINSTANCE _instance = nullptr;
        HWND _hwnd = nullptr;
        Backbuffer _backbuffer;
    };
}


