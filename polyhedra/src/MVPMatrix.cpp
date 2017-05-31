#include "MVPMatrix.h"

MVPMatrix::MVPMatrix()
{
    model.setToIdentity();
    view.setToIdentity();
    projection.setToIdentity();
}
