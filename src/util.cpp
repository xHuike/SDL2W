#include "../include/util.hpp"
#include <random>

namespace util
{

namespace 
{
	std::random_device rd;
    std::mt19937 gen(rd());
}

Vector2::Vector2() : x{0}, y{0}
{}
Vector2::Vector2( int _x, int _y ) : x{_x}, y{_y} 
{}
Vector2 Vector2::operator+(Vector2 const &other)
{
	return Vector2(x+other.x, y+other.y);
}
Vector2 Vector2::operator-(Vector2 const &other)
{
	return Vector2(x-other.x, y-other.y);
}

Rect::Rect() : Vector2(0, 0), w{0}, h{0}
{

}
Rect::Rect( int _x, int _y, int _w, int _h ) : Vector2( _x, _y ), w{_w}, h{_h} 
{

}	

/*
Shitty brute force collision.
TODO: Add better collision. See Minkowski.
*/	
bool insec( SDL_Rect a, SDL_Rect b )
{
	int atop = a.y;
	int abot = a.y+a.h;
	int btop = b.y;
	int bbot = b.y+b.h;
	int aleft = a.x;
	int aright = a.x+a.w;
	int bleft = b.x;
	int bright = b.x+b.w;
	
	return(
	/*if a intersects b*/
	(((abot >= btop && abot <= bbot) && ((aleft >= bleft && aleft <= bright) || (aright <= bright && aright >= bleft)))//from top
	||((abot >= btop && abot <= bbot) && ((aleft >= bleft && aleft <= bright) || (aright <= bright && aright >= bleft)))//from bot
	||((aleft >= bleft && aleft <= bright) && ((abot >= btop && abot <= bbot) || (abot >= btop && abot <= bbot)))//from left
	||((aright <= bright && aright >= bleft) && ((abot >= btop && abot <= bbot) || (abot >= btop && abot <= bbot))))//from right
	||
	/*if b intersects a*/
	(((bbot >= atop && bbot <= abot) && ((bleft >= aleft && bleft <= aright) || (bright <= aright && bright >= aleft)))//from top
	||((bbot >= atop && bbot <= abot) && ((bleft >= aleft && bleft <= aright) || (bright <= aright && bright >= aleft)))//from bot
	||((bleft >= aleft && bleft <= aright) && ((bbot >= atop && bbot <= abot) || (bbot >= atop && bbot <= abot)))//from left
	||((bright <= aright && bright >= aleft) && ((bbot >= atop && bbot <= abot) || (bbot >= atop && bbot <= abot))))//from right
	);
}
int randNum(int min, int max)
{
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

}
