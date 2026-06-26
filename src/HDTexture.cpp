#include "HDTexture.h"

#include <string>

std::string HDTexture::RootPath;
bool HDTexture::Initialized = false;
static bool DumpEnabled = false;

void HDTexture::Initialize(const char* rootPath)
{
    if (Initialized)
        return;

    RootPath = rootPath;
    Initialized = true;
}

bool HDTexture::IsEnabled()
{
    return Initialized;
}

bool HDTexture::ReplaceTexture(
    uint64_t key,
    uint32_t width,
    uint32_t height,
    void*& pixels)
{
    (void)key;
    (void)width;
    (void)height;
    (void)pixels;

    // Belum ada replacement.
    // Untuk saat ini selalu gunakan texture asli.
    return false;
}

void HDTexture::SetDumpEnabled(bool enabled)
{
    DumpEnabled = enabled;
}

bool HDTexture::IsDumpEnabled()
{
    return DumpEnabled;
}

void HDTexture::DumpTexture(
    uint64_t key,
    uint32_t width,
    uint32_t height,
    const void* pixels)
{
    (void)key;
    (void)width;
    (void)height;
    (void)pixels;
}
