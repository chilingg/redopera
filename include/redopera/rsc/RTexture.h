#ifndef RTEXTURE_H
#define RTEXTURE_H

#include "RResource.h"
#include "../ROpenGL.h"

#include <memory>

namespace Redopera {

class RImage;
class RSize;

class RTexture
{
    friend void swap(RTexture &texture1, RTexture &texture2);

public:
    enum class inFormat
    {
        R8 = GL_R8,
        RG8 = GL_RG8,
        RGB8 = GL_RGB8,
        RGBA8 = GL_RGBA8
    };

    enum class ExtFormat
    {
        RED = GL_RED,
        RG = GL_RG,
        RGB = GL_RGB,
        RGBA = GL_RGBA
    };

    enum class Wrap
    {
        Repeat = GL_REPEAT,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        ClampToEdge = GL_CLAMP_TO_EDGE,
        ClampToBorder = GL_CLAMP_TO_BORDER,
    };

    enum class Filter
    {
        Nearest = GL_NEAREST,
        Linear = GL_LINEAR
    };

    struct Format
    {
        struct {
            Filter max, min;
        } filter { Filter::Nearest, Filter::Nearest };

        int inChannel = 4;

        struct {
            Wrap s, t;
        } wrap { Wrap::ClampToBorder, Wrap::ClampToBorder };

        std::array<GLuint, 4> edgeColor { 0, 0, 0, 0 };
    };

    static const Format Linear4;
    static const Format Linear3;
    static const Format Nearest4;
    static const Format Nearest3;
    static const Format SingleL;
    static const Format SingleN;

    static RTexture whiteTex();
    static RTexture blackTex();
    static RTexture transTex();

    static void setDefaultTextureFomat(const Format &format);
    static void unbindTexture();

    RTexture() = default;
    RTexture(const std::string &path, const Format &format = textureFormat);
    RTexture(const RImage &img, const Format &format = textureFormat);
    RTexture(const RData *data, int width, int height, int channel, const Format &format = textureFormat);
    RTexture(const RTexture &tex);
    RTexture(const RTexture &&tex);
    RTexture& operator=(RTexture tex);
    void swap(RTexture &tex);
    ~RTexture() = default;

    bool isValid() const;
    int width() const;
    int height() const;
    RSize size() const;
    const Format format() const;
    GLuint textureID() const;
    void bind(unsigned unit = 0) const; // unit直接指定纹理单元号，无需使用GL_TEXTURE0

    bool load(const RData *data, int width, int height, int echannel, const Format &format = textureFormat);
    bool load(const RImage &img, const Format &format = textureFormat);
    bool load(const std::string &path, const Format &format = textureFormat);
    void reload(const RData* data);
    void release();

private:
    static void deleteTexture(GLuint *id);
    static Format textureFormat;

    std::shared_ptr<GLuint> textureID_;
    Format format_;
    int width_ = 0, height_ = 0;
};

} // Redopera

void swap(Redopera::RTexture &tex1, Redopera::RTexture &tex2);

#endif // RTEXTURE_H
