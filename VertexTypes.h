#ifndef VERTEXTYPES_H
#define VERTEXTYPES_H


struct Vertex2D {
    QVector2D position;
    QVector2D texCoord;
};

struct Vertex2DTextureColor {
    QVector2D position;
    QVector2D texCoord;
    QVector4D color;
};


struct VertexSimple {
    QVector3D position;
};

#endif // VERTEXTYPES_H
