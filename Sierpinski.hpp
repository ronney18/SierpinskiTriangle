//Name: Ronney Sanchez
//Date 1/31/18
//Course: COMP2040 (Computing IV)
//Program: Sierpinski Triangle

#ifndef SIERPINSKI_INCLUDED
#define SIERPINSKI_INCLUDED

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Sierpinski : public sf::Drawable
{
  	private:
  		//Use three vectors points
  		sf::Vector2f bottom;  // my own triangle
  		sf::Vector2f left;
  		sf::Vector2f right;
  		
  		//The depth of the triangle
  		int initialDepth; 
  		//Three triangle pointer inside of the initial triangle
  		Sierpinski* child1;		     // my "children" -- three more triangles  inside
  		Sierpinski* child2;
  		Sierpinski* child3;
  		void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  		sf::Vector2f midPoint(sf::Vector2f leftPoint, sf::Vector2f rightPoint);
  		
  	public:
  		Sierpinski(int length, int depth);
		Sierpinski(sf::Vector2f vertex, int count, int length, int depth);
		~Sierpinski();
};

#endif
