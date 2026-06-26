#pragma once

#include <cstdint>
#include <string>

class HDTexture
{
public:
    static void Initialize(const char* rootPath);

    static bool IsEnabled();

    static bool ReplaceTexture(
        uint64_t key,
        uint32_t width,
        uint32_t height,
        void*& pixels);

    static void DumpTexture(
        uint64_t key,
        uint32_t width,
        uint32_t height,
        const void* pixels);

static void SetDumpEnabled(bool enabled);

static bool IsDumpEnabled();

private:
    static std::string RootPath;
    static bool Initialized;
};
