/*
 * Copyright (C) 2013 Andrey Tulyakov
 * @mail: mhyhre@gmail.com
 *
 * This work is licensed under a Creative Commons
 * Attribution-NonCommercial-NoDerivs 3.0 Unported License.
 * You may obtain a copy of the License at
 *
 *              http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode
 *
 */

#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <QGLFunctions>
#include "DrawableEntity.h"
#include "VertexTypes.h"
#include "TextureAtlas.h"
#include "TextureRegion.h"

#include <QGLBuffer>


namespace Entity
{


class SpriteBatch: public DrawableEntity , QGLFunctions
{
    public:
        SpriteBatch(TextureAtlas *atlas, int capacity);
        virtual ~SpriteBatch();

        void init();
        void update();
        void draw();

        void addStart();
        void addEnd();
        void addSprite(TextureRegion *region, float x, float y, float scaleX, float scaleY, float rotation, float r, float g, float b, float a);


    private:
        void initGeometry();

        int capacity;
        int used;

        QGLBuffer *indicesBuffer;

        bool nowMapped;
        Vertex2DTextureColor *mapedVertices;

        TextureAtlas *atlas;
};


}

#endif // SPRITEBATCH_H
