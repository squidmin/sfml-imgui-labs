#include "../../include/tilemap/Grid.h"


Grid::Grid()
{
    tile_verts.setPrimitiveType(sf::Quads);
    tile_outline_verts.setPrimitiveType(sf::Quads);
    tile_size = 32;
    tile_outline_thickness = 1;
    tile_outline_color = sf::Color(97, 105, 183);
    tile_color = sf::Color(35, 35, 35);
    x_tiles = 0;
    y_tiles = 0;
    x_pos = 0;
    y_pos = 0;
    x1_bound = x_pos - 32;
    x2_bound = x_pos + (x_tiles * tile_size) + 32;
    y1_bound = y_pos - 32;
    y2_bound = y_pos + (y_tiles * tile_size) + 32;
    current_row = 0;
    current_col = 0;
}


Grid::Grid(const unsigned int tile_size, const unsigned int tile_outline_thickness, const unsigned int x_tiles, const unsigned int y_tiles, const int x_pos, const int y_pos)
{
    tile_verts.setPrimitiveType(sf::Quads);
    tile_outline_verts.setPrimitiveType(sf::Quads);
    this->tile_size = tile_size;
    this->tile_outline_thickness = tile_outline_thickness;
    tile_outline_color = sf::Color(97, 105, 183);
    tile_color = sf::Color(35, 35, 35);
    this->x_tiles = x_tiles;
    this->y_tiles = y_tiles;
    this->x_pos = x_pos;
    this->y_pos = y_pos;
    x1_bound = x_pos - 32;
    x2_bound = x_pos + (x_tiles * tile_size) + 32;
    y1_bound = y_pos - 32;
    y2_bound = y_pos + (y_tiles * tile_size) + 32;
    current_row = 0;
    current_col = 0;
    init();
}


void Grid::setTileSize(const int tile_size)
{
    this->tile_size = tile_size;
}


void Grid::setTileOutlineSize(const int tile_outline_thickness)
{
    this->tile_outline_thickness = tile_outline_thickness;
}


void Grid::setXTiles(int x_tiles)
{
    this->x_tiles = x_tiles;
    update();
}


void Grid::setYTiles(int y_tiles)
{
    this->y_tiles = y_tiles;
    update();
}


void Grid::setPosition(int x_pos, int y_pos)
{
    this->x_pos = x_pos;
    this->y_pos = y_pos;

    //update();
}


void Grid::setHoveredTile(int mouse_pos_x, int mouse_pos_y)
{
    for (unsigned int i = 0; i < tiles.size(); ++i)
    {
        if (tiles[i].isHovered(mouse_pos_x, mouse_pos_y))
        {
            current_row = tiles[i].getRow();
            current_col = tiles[i].getCol();
        }
    }
}


int Grid::getTileSize()
{
    return tile_size;
}


int Grid::getTileOutlineSize()
{
    return tile_outline_thickness;
}


int Grid::getXTiles()
{
    return x_tiles;
}


int Grid::getYTiles()
{
    return y_tiles;
}


int Grid::getXPos()
{
    return x_pos;
}


int Grid::getYPos()
{
    return y_pos;
}


int Grid::getXLen_px()
{
    return ( x_tiles * tile_size ) - x_pos;
}


int Grid::getYLen_px()
{
    return ( y_tiles * tile_size ) - y_pos;
}


int Grid::getX1Bound()
{
    return x1_bound;
}


int Grid::getX2Bound()
{
    return x2_bound;
}


int Grid::getY1Bound()
{
    return y1_bound;
}


int Grid::getY2Bound()
{
    return y2_bound;
}


sf::Vector2f Grid::getCenter()
{
    sf::Vector2f center;
    center.x = (x2_bound - x1_bound) / 2.f;
    center.y = (y2_bound - y1_bound) / 2.f;
    return center;
}


unsigned int Grid::getCurrentRow()
{
    return current_row;
}


unsigned int Grid::getCurrentCol()
{
    return current_col;
}


void Grid::reset()
{
    tile_size = 32;
    tile_outline_thickness = 1;
    x_tiles = 50;
    y_tiles = 50;
    x_pos = 0;
    y_pos = 0;
    tile_outline_verts.clear();
    tile_verts.clear();
}


/*
void Grid::colorHoveredTile(int* mouse_pos_x, int* mouse_pos_y)
{
    for (unsigned int i = 0; i < tiles.size(); ++i)
    {
        if (tiles[i].isHovered(mouse_pos_x, mouse_pos_y))
        {
            current_row = tiles[i].getRow();
            current_col = tiles[i].getCol();
            tile_verts[i * 4 + 0].color = hovered_tile_color;
            tile_verts[i * 4 + 1].color = hovered_tile_color;
            tile_verts[i * 4 + 2].color = hovered_tile_color;
            tile_verts[i * 4 + 3].color = hovered_tile_color;
        }
    }
}
*/


void Grid::clear()
{
    tiles.clear();
    tile_outline_verts.clear();
    tile_verts.clear();
}


void Grid::clearOutlines()
{
    for (unsigned int i = 0; i < tiles.size(); ++i)
        tiles[i].clearOutline();
    tile_outline_verts.clear();
}


void Grid::clearTiles()
{
    for (unsigned int i = 0; i < tiles.size(); ++i)
        tiles[i].clear();
    tile_verts.clear();
}


//////////////* PRIVATE MEMBER FUNCTIONS *//////////////////

void Grid::init()
{
    for (unsigned int i = 0; i < y_tiles; ++i)
    {
        for (unsigned int j = 0; j < x_tiles; ++j)
        {
            tiles.push_back(Tile(i + 1, j + 1, x_pos + (j * tile_size), y_pos + (i * tile_size), tile_size, tile_outline_thickness));
            
            tile_outline_verts.append(sf::Vertex(sf::Vector2f(x_pos + (j * tile_size), y_pos + (i * tile_size)), sf::Color(151, 153, 175)));
            tile_outline_verts.append(sf::Vertex(sf::Vector2f(x_pos + (j * tile_size), y_pos + (i * tile_size) + tile_size), sf::Color(151, 153, 175)));
            tile_outline_verts.append(sf::Vertex(sf::Vector2f(x_pos + (j * tile_size) + tile_size, y_pos + (i * tile_size) + tile_size), sf::Color(151, 153, 175)));
            tile_outline_verts.append(sf::Vertex(sf::Vector2f(x_pos + (j * tile_size) + tile_size, y_pos + (i * tile_size)), sf::Color(151, 153, 175)));

            tile_verts.append(sf::Vertex(sf::Vector2f(x_pos + (j * tile_size) + tile_outline_thickness, y_pos + (i * tile_size) + tile_outline_thickness), sf::Color(35, 35, 35)));
            tile_verts.append(sf::Vertex(sf::Vector2f(x_pos + (j * tile_size) + tile_outline_thickness, y_pos + (i * tile_size) + tile_size - tile_outline_thickness), sf::Color(35, 35, 35)));
            tile_verts.append(sf::Vertex(sf::Vector2f(x_pos + (j * tile_size) + tile_size - tile_outline_thickness, y_pos + (i * tile_size) + tile_size - tile_outline_thickness), sf::Color(35, 35, 35)));
            tile_verts.append(sf::Vertex(sf::Vector2f(x_pos + (j * tile_size) + tile_size - tile_outline_thickness, y_pos + (i * tile_size) + tile_outline_thickness), sf::Color(35, 35, 35)));
        }
    }
    x1_bound = x_pos - 32;
    x2_bound = x_pos + (x_tiles * tile_size) + 32;
    y1_bound = y_pos - 32;
    y2_bound = y_pos + (y_tiles * tile_size) + 32;
}


void Grid::update()
{
    tiles.clear();
    tile_outline_verts.clear();
    tile_verts.clear();
    init();
}
