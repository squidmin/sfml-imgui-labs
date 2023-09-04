#ifndef CANVAS_H
#define CANVAS_H


class Canvas
{
private:
    unsigned int x_dim;
    unsigned int y_dim;
public:
    Canvas();
    Canvas(unsigned int, unsigned int);
    void setXDim(unsigned int);
    void setYDim(unsigned int);
    unsigned int getXDim() const;
    unsigned int getYDim() const;
};

#endif