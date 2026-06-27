#include "HDTexture.h"

#include <cstdint>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <android/log.h>

static void DebugLog(const std::string& msg)
{
    std::ofstream log(
        "/sdcard/Android/data/me.magnum.melonds.nightly.dev/files/debug.log",
        std::ios::app);

    if (!log)
        return;

    log << msg << std::endl;
}

std::string HDTexture::RootPath;
bool HDTexture::Initialized = false;
static bool DumpEnabled = false;
static std::string MakeTextureName(uint64_t key)
{
    std::stringstream ss;
    ss << std::hex
       << std::setw(16)
       << std::setfill('0')
       << key;
    return ss.str();
}

void HDTexture::Initialize(const char* rootPath)
{
    if (Initialized)
        return;

    RootPath = rootPath;

    DebugLog(std::string("Initialize: ") + rootPath); 

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
    std::string fileName = MakeTextureName(key) + ".bin";
    DebugLog("Looking for: " + fileName);

    if (!Initialized)
        return false;

    std::filesystem::path textureFile =
        std::filesystem::path(RootPath) /
        "load" /
        (MakeTextureName(key) + ".bin");

    if (!std::filesystem::exists(textureFile))
{
    DebugLog("Not found: " + fileName);
    return false;
}

    std::ifstream in(textureFile, std::ios::binary);
    if (!in)
        return false;

    size_t size = width * height * 4;

    uint8_t* newPixels = new uint8_t[size];

    in.read(reinterpret_cast<char*>(newPixels), size);

    if (!in)
    {
        delete[] newPixels;
        return false;
    }

    pixels = newPixels;

    DebugLog("Texture replaced: " + textureFile.string());
    DebugLog("Found: " + fileName);

    return true;
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
    if (!DumpEnabled)
        return;

    DebugLog("DumpTexture() called");

    std::filesystem::path dumpDir =
        std::filesystem::path(RootPath) / "dump";

    std::filesystem::create_directories(dumpDir);

    DebugLog("Directory ready");

    std::string fileName =
        MakeTextureName(key) + ".bin";

    std::filesystem::path outFile =
        dumpDir / fileName;

    if (std::filesystem::exists(outFile))

{
    DebugLog("Already exists: " + fileName);
    return;
}


    std::ofstream out(outFile, std::ios::binary);

    if (!out)

{
       DebugLog("FAILED opening file");
       return;
}

       DebugLog("Writing texture...");

    out.write(
        reinterpret_cast<const char*>(pixels),
        width * height * 4);

    out.close();

    DebugLog("Texture dumped: " + fileName);

}


