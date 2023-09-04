#include "../../include/tilemap/Canvas.h"


Canvas::Canvas()
{
    x_dim = 1280;
    y_dim = 960;
}


Canvas::Canvas(const unsigned int x_dim, const unsigned int y_dim)
{
    this->x_dim = x_dim;
    this->y_dim = y_dim;
}


void Canvas::setXDim(const unsigned int x_dim)
{
    this->x_dim = x_dim;
}


void Canvas::setYDim(const unsigned int y_dim)
{
    this->y_dim = y_dim;
}


unsigned int Canvas::getXDim() const
{
    return x_dim;
}


unsigned int Canvas::getYDim() const
{
    return y_dim;
}