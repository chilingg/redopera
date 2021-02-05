#include <RModelMat.h>

using namespace Redopera;

RModelMat::RModelMat():
    model_(0)
{

}

RModelMat::RModelMat(float x, float y, float z, float width, float height):
    model_(0)
{
    setModel(x, y, z, width, height);
}

RModelMat::RModelMat(const RPointF &pos, const RSizeF &size):
    RModelMat(pos.x(), pos.y(), pos.z(), size.width(), size.height())
{

}

RModelMat::RModelMat(const RRectF &rect, float depth):
    RModelMat(rect.x(), rect.y(), depth, rect.width(), rect.height())
{

}

const glm::mat4 &RModelMat::model() const
{
    return model_;
}

float RModelMat::top() const
{
    return model_[3].y + std::abs(model_[1].y / 2);
}

float RModelMat::bottom() const
{
    return model_[3].y - std::abs(model_[1].y / 2);
}

float RModelMat::left() const
{
    return model_[3].x - std::abs(model_[0].x) / 2;
}

float RModelMat::right() const
{
    return model_[3].x + std::abs(model_[0].x) / 2;
}

float RModelMat::depth() const
{
    return model_[3].z;
}

float RModelMat::x() const
{
    return model_[3].x - std::abs(model_[0].x) / 2;
}

float RModelMat::y() const
{
    return model_[3].y - std::abs(model_[1].y / 2);
}

float RModelMat::centerX() const
{
    return model_[3].x;
}

float RModelMat::centerY() const
{
    return model_[3].y;
}

RPoint2F RModelMat::center() const
{
    return { model_[3].x, model_[3].y };
}

RPointF RModelMat::pos() const
{
    return RPointF(model_[3].x - std::abs(model_[0].x) / 2,
            model_[3].y - std::abs(model_[1].y / 2),
            model_[3].z);
}

float RModelMat::width() const
{
    return std::abs(model_[0].x);
}

float RModelMat::height() const
{
    return std::abs(model_[1].y);
}

RSizeF RModelMat::size() const
{
    return RSizeF(std::abs(model_[0].x), std::abs(model_[1].y));
}

RRectF RModelMat::rect() const
{
    return RRectF(pos(), size());
}

bool RModelMat::isFlipH() const
{
    return model_[0].x < 0;
}

bool RModelMat::isFlipV() const
{
    return model_[1].y < 0;
}

void RModelMat::move(float x, float y, float z)
{
    model_[3].x += x; model_[3].y += y; model_[3].z += z;
}

void RModelMat::move(const RPoint2F &pos, float depth)
{
    move(pos.x(), pos.y(), depth);
}

void RModelMat::setPos(float x, float y)
{
    setPos(x, y, model_[3].z);
}

void RModelMat::setPos(float x, float y, float z)
{
    model_[3].x = x + std::abs(model_[0].x / 2);
    model_[3].y = y + std::abs(model_[1].y / 2);
    model_[3].z = z;
}

void RModelMat::setPos(const RPoint2F &pos)
{
    setPos(pos.x(), pos.y(), model_[3].z);
}

void RModelMat::setPos(const RPoint2F &pos, float depth)
{
    setPos(pos.x(), pos.y(), depth);
}

void RModelMat::setDepth(float depth)
{
    model_[3].z = depth;
}

void RModelMat::flipH()
{
    model_[0][0] *= -1;
}

void RModelMat::flipV()
{
    model_[1][1] *= -1;
}

void RModelMat::setModel(float x, float y, float z, float width, float height)
{
    model_[0].x = width;
    model_[1].y = height;
    model_[3] = { x + width / 2.f, y + height / 2.f, z, 1 };
}

void RModelMat::setModel(const RPoint2F &pos, const RSizeF &size)
{
    setModel(pos.x(), pos.y(), model_[3].z, size.width(), size.height());
}

void RModelMat::setModel(const RPoint2F &pos, const RSizeF &size, float depth)
{
    setModel(pos.x(), pos.y(), depth, size.width(), size.height());
}

void RModelMat::setModel(const RRectF &rect)
{
    setModel(rect.x(), rect.y(), model_[3].z, rect.width(), rect.height());
}

void RModelMat::setModel(const RRectF &rect, float depth)
{
    setModel(rect.x(), rect.y(), depth, rect.width(), rect.height());
}

std::string RModelMat::toString() const
{
    char buf[256];
    std::snprintf(buf, sizeof(buf),
                  "mat:(%10.3f, %10.3f, %10.3f, %10.3f)\n"
                  "    (%10.3f, %10.3f, %10.3f, %10.3f)\n"
                  "    (%10.3f, %10.3f, %10.3f, %10.3f)\n"
                  "    (%10.3f, %10.3f, %10.3f, %10.3f). ",
                  model_[0][0], model_[1][0], model_[2][0], model_[3][0],
                  model_[0][1], model_[1][1], model_[2][1], model_[3][1],
                  model_[0][2], model_[1][2], model_[2][2], model_[3][2],
                  model_[0][3], model_[1][3], model_[2][3], model_[3][3]);

    return buf;
}
