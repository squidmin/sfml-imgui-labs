#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


#ifndef TILE_H
#define TILE_H


class Tile
{
private:
	unsigned int row;
	unsigned int col;
	int len_px;
	int x_pos;
	int y_pos;
    sf::VertexArray outline_verts;
    sf::VertexArray verts;
    sf::Color outline_color;
    sf::Color color;
    unsigned int outline_thickness;
          
public:
    Tile();
    Tile(unsigned int, unsigned int, int, int, int, int);
    void setSize(const int);
    void setPosition(const int, const int);
    void setColor(sf::Color);
    void setToHoveredColor();
    void setToNonHoveredColor();
    unsigned int getRow();
    unsigned int getCol();
    sf::Color& getColor();
    bool isHovered(int&, int&);
    void clearOutline();
    void clear();
};


#endif