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

#ifndef RECT_H
#define RECT_H

#include "DrawableEntity.h"
#include <QGLFunctions>
#include <QVector3D>

namespace Entity
{

class Rect : public DrawableEntity , QGLFunctions
{

    public:
        Rect(float pX, float pY, float pWidth, float pHeight);
        Rect(QVector3D pPosition, QVector3D pSize);
        virtual ~Rect();

        void init();

        void setFilledDraw(bool arg);
        bool isFilledDraw();

        // НЕОБХОДИМО ПЕРЕПИСАТЬ КОНСТРУКТОР И КЛАСС НА ИСПОЛЬЗОВАНИЕ X,Y,W,H + ВЕКТОРНЫЕ ПЕРЕГРУЗКИ
        void setSize(float pWidth, float pHeight);
        void setSize(QVector3D pSize);

        void update();
        void draw();

    private:
        bool filledDraw;
        void initGeometry();
};

}

#endif // RECT_H
