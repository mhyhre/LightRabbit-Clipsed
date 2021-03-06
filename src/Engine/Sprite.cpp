#include "Sprite.h"

#include "DefaultShaders.h"
#include "VertexTypes.h"

namespace Entity
{


Sprite::Sprite()
{
    initializeGLFunctions();

    region = new TextureRegion(nullptr,0,0,128,128);
    size = QVector3D(region->getRegion().width(), region->getRegion().height(),0);

    shaderProgram = DefaultShaders::getInstance()->getShader("SimpleTextured");

    initGeometry();
}

Sprite::Sprite(TextureAtlas *pAtlas)
{
    initializeGLFunctions();

    region = new TextureRegion(pAtlas, 0, 0, pAtlas->width(), pAtlas->height());
    size = QVector3D(pAtlas->width(), pAtlas->height(),0);

    shaderProgram = DefaultShaders::getInstance()->getShader("SimpleTextured");

    initGeometry();
}

Sprite::Sprite(TextureRegion *pRegion)
{
    initializeGLFunctions();

    region = new TextureRegion(pRegion->getAtlas());
    region->setRegion(pRegion->getRegion());
    size = QVector3D(region->getRegion().width(), region->getRegion().height(),0);

    shaderProgram = DefaultShaders::getInstance()->getShader("SimpleTextured");

    initGeometry();
}

Sprite::~Sprite()
{

}

void Sprite::setAtlas(TextureAtlas *pAtlas)
{
    region->setTextureAtlas(pAtlas);

    if (region->getAtlas() != 0 || region->getAtlas() != nullptr)
    {
        TextureRegion  reg(pAtlas, 0, 0, pAtlas->width(), pAtlas->height());
        setRegion(&reg);
        size = QVector3D(region->getRegion().width(), region->getRegion().height(),0);
    }

}

void Sprite::setRegion(TextureRegion *pRegion)
{
    region->setTextureAtlas(pRegion->getAtlas());
    region->setRegion(pRegion->getRegion());
    size = QVector3D(region->getRegion().width(), region->getRegion().height(),0);

    if (region->getAtlas() != 0 || region->getAtlas() != nullptr)
    {
        QRectF reg = region->getAbsRegion();

        vertexBuffer->bind();
        Vertex2D *data = (Vertex2D *)vertexBuffer->map(QGLBuffer::ReadWrite);

        float hw = size.x() / 2;
        float hh = size.y() / 2;

        data[0].position =  QVector2D(-hw, -hh);
        data[1].position =  QVector2D(hw, -hh);
        data[2].position =  QVector2D(-hw,  hh);
        data[3].position =  QVector2D(hw,  hh);

        data[0].texCoord =  QVector2D(reg.topLeft());
        data[1].texCoord =  QVector2D(reg.topRight());
        data[2].texCoord =  QVector2D(reg.bottomLeft());
        data[3].texCoord =  QVector2D(reg.bottomRight());

        vertexBuffer->unmap();
    }
}



void Sprite::update()
{

}

void Sprite::draw()
{
    if (!visible)
        return;

    shaderProgram->bind();
    vertexBuffer->bind();

    transform.setToIdentity();

    transform.translate(position);
    transform.rotate(zRotation, 0, 0, 1);
    transform.scale(scale);

    transform = camera->getCameraMatrix() * transform;

    if (region->getAtlas() != nullptr)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, region->getAtlas()->textureID());
        shaderProgram->setUniformValue("texture", 0);
    }

    shaderProgram->setUniformValue("mvp_matrix", transform);
    shaderProgram->setUniformValue("color", color);

    quintptr offset = 0;

    // Locate vertex position data
    int vertexLocation = shaderProgram->attributeLocation("a_position");
    shaderProgram->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector2D);

    // Locate vertex texture coordinate data
    int texcoordLocation = shaderProgram->attributeLocation("a_texcoord");
    shaderProgram->enableAttributeArray(texcoordLocation);
    glVertexAttribPointer(texcoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void *)offset);



    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    shaderProgram->disableAttributeArray(vertexLocation);
    shaderProgram->disableAttributeArray(texcoordLocation);

}




void Sprite::initGeometry()
{
    float hw = region->getRegion().width() / 2;
    float hh = region->getRegion().height() / 2;

    Vertex2D vertices[4] =
    {
        {QVector2D(-hw, -hh), QVector2D(0.0, 0.0)},  // v0
        {QVector2D(hw, -hh), QVector2D(1.0, 0.0)},    // v1
        {QVector2D(-hw,  hh), QVector2D(0.0, 1.0)},  // v2
        {QVector2D(hw,  hh), QVector2D(1.0, 1.0)},    // v3
    };

    vertexBuffer = new QGLBuffer(QGLBuffer::VertexBuffer);
    vertexBuffer->create();
    vertexBuffer->bind();
    vertexBuffer->allocate(vertices, sizeof(Vertex2D) * 4);
}

}
