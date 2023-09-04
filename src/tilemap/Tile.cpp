#include "../../include/tilemap/Tile.h"


Tile::Tile()
{
	// So far this shouldn't get used. No reason to create a 'blank' tile right now.
}


Tile::Tile(unsigned int row, unsigned int col, int x_pos, int y_pos, int len_px, int outline_thickness)
{
    this->row = row;
    this->col = col;

    this->x_pos = x_pos;
    this->y_pos = y_pos;

    this->len_px = len_px;

    this->outline_thickness = outline_thickness;

	outline_verts.setPrimitiveType(sf::Quads);
	verts.setPrimitiveType(sf::Quads);
    
    outline_color = sf::Color(151, 153, 175);
	color = sf::Color(35, 35, 35);

	outline_verts.append(sf::Vertex(sf::Vector2f(x_pos, y_pos), outline_color));  // Top-left
	outline_verts.append(sf::Vertex(sf::Vector2f(x_pos, y_pos + len_px), outline_color));  // Bottom-left
	outline_verts.append(sf::Vertex(sf::Vector2f(x_pos + len_px, y_pos + len_px), outline_color));  // Bottom-right
	outline_verts.append(sf::Vertex(sf::Vector2f(x_pos + len_px, y_pos), outline_color));  // Top-right

	verts.append(sf::Vertex(sf::Vector2f(x_pos + outline_thickness, y_pos + outline_thickness), color));
    verts.append(sf::Vertex(sf::Vector2f(x_pos + outline_thickness, y_pos + len_px - outline_thickness), color));
    verts.append(sf::Vertex(sf::Vector2f(x_pos + len_px - outline_thickness, y_pos + len_px - outline_thickness), color));
    verts.append(sf::Vertex(sf::Vector2f(x_pos + len_px - outline_thickness, y_pos + outline_thickness), color));
}


void Tile::setSize(const int len_px)
{
    this->len_px = len_px;
}


void Tile::setPosition(const int x_pos, const int y_pos)
{
    this->x_pos = x_pos;
    this->y_pos = y_pos;
}


void Tile::setColor(sf::Color color)
{
    this->color = color;
    verts.clear();
    verts.append(sf::Vertex(sf::Vector2f(x_pos + outline_thickness, y_pos + outline_thickness), color));
    verts.append(sf::Vertex(sf::Vector2f(x_pos + outline_thickness, y_pos - outline_thickness), color));
    verts.append(sf::Vertex(sf::Vector2f(x_pos - outline_thickness, y_pos - outline_thickness), color));
    verts.append(sf::Vertex(sf::Vector2f(x_pos - outline_thickness, y_pos + outline_thickness), color));
}


void Tile::setToHoveredColor()
{
	sf::Color hovered_color = sf::Color(97, 105, 183);
    setColor(sf::Color(hovered_color));
}


void Tile::setToNonHoveredColor()
{
	sf::Color nonhovered_color = sf::Color(35, 35, 35);
	setColor(sf::Color(nonhovered_color));
}


unsigned int Tile::getRow()
{
	return row;
}


unsigned int Tile::getCol()
{
	return col;
}


sf::Color& Tile::getColor()
{
	return color;
}


bool Tile::isHovered(int& mouse_pos_x, int& mouse_pos_y)
{
    return (mouse_pos_x > x_pos && mouse_pos_x < x_pos + len_px)
              &&
           (mouse_pos_y > y_pos && mouse_pos_y < y_pos + len_px);
}


void Tile::clearOutline()
{
	outline_verts.clear();
}


void Tile::clear()
{
	verts.clear();
}