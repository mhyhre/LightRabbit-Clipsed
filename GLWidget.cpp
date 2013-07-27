
#include <QtWidgets>
#include <QtOpenGL>

#include <math.h>

#include "GLWidget.h"

#include "DefaultShaders.h"
#include "Line.h"
#include "Rect.h"
#include "Sprite.h"
#include "SpriteBatch.h"

#include <QMouseEvent>

#include <math.h>
#include <locale.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{

}

GLWidget::~GLWidget()
{
    VertexBufferManager::deleteInstance();
    DefaultShaders::deleteInstance();
    deleteTexture(texture);
}



void GLWidget::timerEvent(QTimerEvent *)
{

    updateGL();
}

void GLWidget::initializeGL()
{
    initializeGLFunctions();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_MULTISAMPLE);

    glClearColor(0.66f, 0.66f, 0.99f, 1.0f);

    initTextures();

    //VBManager = VertexBufferManager::getInstance();

    rootScene.setCamera(&camera);

    Entity::Line* eLine = new Entity::Line(0, -100, 0, 100);
    rootScene.attachChild(eLine);

    rootScene.attachChild(new Entity::Line(-100, 0, 100, 0));

    Entity::Rect* eRect = new Entity::Rect(-50, -50, 100, 100);
    eRect->setColor(1, 1, 1, 0.5f);
    rootScene.attachChild(eRect);

    Entity::Sprite* eSprite = new Entity::Sprite(512, 512);
    eSprite->setPosition(100,100,0);
    eSprite->setRotationZ(70);
    eSprite->setScale(0.3,0.3,1);
    rootScene.attachChild(eSprite);

    TextureAtlas atlas;

    Entity::SpriteBatch* eSb = new Entity::SpriteBatch(&atlas, 100);
    rootScene.attachChild(eSb);

    timer.start(15, this);
}

void GLWidget::initTextures()
{
    glEnable(GL_TEXTURE_2D);
    texture = bindTexture(QImage("res/textures/image.png"));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    camera.setOrtho(w, h, -10, 100, false);
    camera.setPosition(-width() / 2, - height() / 2, 1);
}


void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rootScene.update();
    rootScene.draw();

}
