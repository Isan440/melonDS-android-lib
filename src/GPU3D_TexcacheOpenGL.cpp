#include "GPU3D_TexcacheOpenGL.h"
#include "HDTexture.h"

namespace melonDS
{

GLuint TexcacheOpenGLLoader::GenerateTexture(u32 width, u32 height, u32 layers)
{
    GLuint texarray;
    glGenTextures(1, &texarray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texarray);
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8UI, width, height, layers);
    return texarray;
}

void TexcacheOpenGLLoader::UploadTexture(GLuint handle, u32 width, u32 height, u32 layer, void* data, u64 key)
{
    // HD Texture hook
static bool initialized = false;

if (!initialized)
{
    HDTexture::Initialize("/sdcard/Android/data/me.magnum.melonds.nightly.dev/files/textures");
    initialized = true;
}
    glBindTexture(GL_TEXTURE_2D_ARRAY, handle);

void* uploadData = data;

HDTexture::ReplaceTexture(
    key,
    width,
    height,
    uploadData);

HDTexture::DumpTexture(
    key,
    width,
    height,
    uploadData);

    glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
        0, 0, 0, layer,
        width, height, 1,
        GL_RGBA_INTEGER, GL_UNSIGNED_BYTE, uploadData);
}

void TexcacheOpenGLLoader::DeleteTexture(GLuint handle)
{
    glDeleteTextures(1, &handle);
}

}
