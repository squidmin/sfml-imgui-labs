#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>

#include "Tile.h"


#ifndef GRID_H
#define GRID_H


class Grid : public sf::Drawable
{
private:
    int x_pos;
    int y_pos;
    int x_tiles;
    int y_tiles;
    int tile_size;
    int tile_outline_thickness;
    int x1_bound;
    int x2_bound;
    int y1_bound;
    int y2_bound;
    unsigned int current_row;
    unsigned int current_col;
    sf::Color tile_outline_color;
    sf::Color tile_color;
    std::vector<Tile> tiles;
    sf::VertexArray tile_outline_verts;
    sf::VertexArray tile_verts;

    void init();
    void update();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(tile_outline_verts, states);
        target.draw(tile_verts, states);
    }      
public:
    Grid();
    Grid(const unsigned int, const unsigned int, const unsigned int, const unsigned int, const int, const int);
    void setTileSize(const int);
    void setTileOutlineSize(const int);
    void setXTiles(int);
    void setYTiles(int);
    void setPosition(int, int);
    void setHoveredTile(int, int);
    int getTileSize();
    int getTileOutlineSize();
    int getXTiles();
    int getYTiles();
    int getXPos();
    int getYPos();
    int getXLen_px();
    int getYLen_px();
    int getX1Bound();
    int getX2Bound();
    int getY1Bound();
    int getY2Bound();
    sf::Vector2f getCenter();
    unsigned int getCurrentRow();
    unsigned int getCurrentCol();
    void reset();
    //void colorHoveredTile(int*, int*);
    void clear();
    void clearOutlines();
    void clearTiles();
};


#endif