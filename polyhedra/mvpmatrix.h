#ifndef MVPMATRIX_H
#define MVPMATRIX_H

// math
#include "QMatrix4x4"

class MVPMatrix
{
public:
    MVPMatrix();
    QMatrix4x4 model, view, projection;
};

#endif // MVPMATRIX_H
