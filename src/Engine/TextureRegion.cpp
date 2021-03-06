#include "TextureRegion.h"

#include <QDebug>

TextureRegion::TextureRegion()
{
    atlas = 0;
    region = QRect(0, 0, 0, 0);
}

TextureRegion::TextureRegion(TextureAtlas *atlas)
{
    this->atlas = atlas;
    region = QRect(0, 0, 0, 0);
}

TextureRegion::TextureRegion(TextureAtlas *atlas, float x, float y, float width, float height)
{
    this->atlas = atlas;
    region = QRect(x, y, width, height);
}

void TextureRegion::setTextureAtlas(TextureAtlas *atlas)
{
    this->atlas = atlas;
}

void TextureRegion::setRegion(float x, float y, float width, float height)
{
    region = QRect(x, y, width, height);
}

void TextureRegion::setRegion(QRect region)
{
    this->region = region;
}

TextureAtlas *TextureRegion::getAtlas()
{
    return atlas;
}

QRect TextureRegion::getRegion()
{
    return region;
}

QRectF TextureRegion::getAbsRegion()
{
    if (atlas == 0)
    {
        return region;
    }
    else
    {
        QRectF reg = QRectF((float)region.x() / atlas->width(), (float)region.y() / atlas->height(), (float)region.width() / atlas->width(), (float)region.height() / atlas->height());
        return reg;
    }

}
