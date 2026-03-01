#pragma once

#include <iostream>
#include <string>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Log
{
#ifdef _WIN32
    enum class Color
    {
        RESET,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE
    };

    inline void setConsoleColor(Color color)
    {
        static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        switch (color)
        {
            case Color::RESET:  SetConsoleTextAttribute(hConsole, 7); break; // gris clair
            case Color::RED:    SetConsoleTextAttribute(hConsole, 4); break;
            case Color::GREEN:  SetConsoleTextAttribute(hConsole, 2); break;
            case Color::YELLOW: SetConsoleTextAttribute(hConsole, 6); break;
            case Color::BLUE:   SetConsoleTextAttribute(hConsole, 1); break;
            case Color::MAGENTA:SetConsoleTextAttribute(hConsole, 5); break;
            case Color::CYAN:   SetConsoleTextAttribute(hConsole, 3); break;
            case Color::WHITE:  SetConsoleTextAttribute(hConsole, 7); break;
        }
    }

    inline void print(const std::string& text, Color color)
    {
        setConsoleColor(color);
        std::cout << text << std::endl;
        setConsoleColor(Color::RESET);
    }

    inline std::string FormatContext(const char* file, int line, const char* func)
    {
        std::ostringstream ss;
        ss << " (" << file << ":" << line << ", " << func << ")";
        return ss.str();
    }

#else
    inline constexpr const char* RESET   = "\033[0m";
    inline constexpr const char* RED     = "\033[31m";
    inline constexpr const char* GREEN   = "\033[32m";
    inline constexpr const char* YELLOW  = "\033[33m";
    inline constexpr const char* BLUE    = "\033[34m";
    inline constexpr const char* MAGENTA = "\033[35m";
    inline constexpr const char* CYAN    = "\033[36m";
    inline constexpr const char* WHITE   = "\033[37m";

    inline void print(const std::string& text, const char* color)
    {
        std::cout << color << text << RESET << std::endl;
    }
#endif

    // Fonctions log
    inline void Info(const std::string& text)
    {
#ifdef _WIN32
        print("[INFO] " + text, Color::CYAN);
#else
        print("[INFO] " + text, CYAN);
#endif
    }

    inline void Warning(const std::string& text)
    {
#ifdef _WIN32
        print("[WARNING] " + text, Color::YELLOW);
#else
        print("[WARNING] " + text, YELLOW);
#endif
    }

    inline void Error(const std::string& text)
    {
#ifdef _WIN32
        print("[ERROR] " + text, Color::RED);
#else
        print("[ERROR] " + text, RED);
#endif
    }

    inline void Debug(const std::string& text)
    {
#ifdef _WIN32
        print("[DEBUG] " + text, Color::GREEN);
#else
        print("[DEBUG] " + text, GREEN);
#endif
    }

    inline void Success(const std::string& text)
    {
#ifdef _WIN32
        print("[SUCCESS] " + text, Color::GREEN);
#else
        print("[SUCCESS] " + text, GREEN);
#endif
    }
}

//macros pour indiquer le file, la line, et la fonction apres l'appel
#define LOG_SUCCESS(msg) Log::Success(std::string(msg) + Log::FormatContext(__FILE__, __LINE__, __FUNCTION__))
#define LOG_WARNING(msg) Log::Warning(std::string(msg) + Log::FormatContext(__FILE__, __LINE__, __FUNCTION__))
#define LOG_ERROR(msg)   Log::Error(std::string(msg) + Log::FormatContext(__FILE__, __LINE__, __FUNCTION__))
#define LOG_DEBUG(msg)   Log::Debug(std::string(msg) + Log::FormatContext(__FILE__, __LINE__, __FUNCTION__))
#define LOG_INFO(msg)   Log::Info(std::string(msg) + Log::FormatContext(__FILE__, __LINE__, __FUNCTION__))

#define DEBUG_MSG Log::Debug(Log::FormatContext(__FILE__, __LINE__, __FUNCTION__))