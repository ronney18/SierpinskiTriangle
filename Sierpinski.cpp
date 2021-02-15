//Name: Ronney Sanchez
//Date 1/31/18
//Course: COMP2040 (Computing IV)
//Program: Sierpinski Triangle

#include "Sierpinski.hpp"

Sierpinski::Sierpinski(int length, int depth)
	: initialDepth(depth)
{
	//Decrement the initial depth by 1
	int newDepth = initialDepth - 1;
	
	//Declare three vector points
	sf::Vector2f point1;
	sf::Vector2f point2;
	sf::Vector2f point3;
	
	//Assign half the length of the triangle to the x-axis of the bottom vector
	bottom.x = length/2.0;
	//Assign half the height of the triangle to the y-axis of the bottom vector
	bottom.y = (int)(0.5*sqrt(3.0)* float(length));
	
	//Assign a quarter of the length of the triangle to the x-axis of the left vector
	left.x = length/2.0 - length/4.0;
	//Assign half the height of the triangle to the y-axis of the left vector
	left.y = (int)(0.5*sqrt(3.0)* float(length))/2.0;
	
	//Assign a quarter of the length of the triangle to the x-axis of the right vector
	right.x = length/2.0 + length/4.0;
	//Assign the y-axis of the left vector to the y-axis of the right vector 
	right.y = left.y;
	
	//Set the three child pointers to NULL if the depth is zero
	if(newDepth == 0)
	{
		child1 = NULL;
		child2 = NULL;
		child3 = NULL;
	}
	
	else
	{
		//Assign the mid-points to the three vector points
		point1 = midPoint(left, right);
		point2 = midPoint(left, bottom);
		point3 = midPoint(right, bottom);
		
		//Create three new Sierpinski objects with the length divided by 4
		child1 = new Sierpinski(point1, 1, length/4.0, newDepth);
		child2 = new Sierpinski(point2, 2, length/4.0, newDepth);
		child3 = new Sierpinski(point3, 3, length/4.0, newDepth);
	}
}

Sierpinski::Sierpinski(sf::Vector2f vertex, int count, int length, int depth)
	: initialDepth(depth)
{
	//Decrement the initial depth by 1
	int newDepth = initialDepth - 1;
	
	//Declare three vector points
	sf::Vector2f point1;
	sf::Vector2f point2;
	sf::Vector2f point3;
	
	if(count == 1)
	{
		//Assign the vertex to the botton vector
		bottom = vertex;
		left.x = vertex.x - (length/2.0);
		left.y = vertex.y - ((0.5*sqrt(3.0))*float(length));
		right.x = vertex.x + (length/2.0);
		//Assign the y-axis of the left vector to the y-axis of the right vector
		right.y = left.y;
	}
	
	else if(count == 2)
	{
		bottom.x = vertex.x - (length/2.0);
		bottom.y = vertex.y + ((0.5*sqrt(3.0)) *float(length));
		left.x = vertex.x - length;
		left.y = vertex.y;
		right = vertex;
	}
	
	else
	{
		bottom.x = vertex.x + (length/2.0);
		bottom.y = vertex.y + ((0.5*sqrt(3.0)) *float(length));
		left = vertex;
		left.y = vertex.y;
		right.x = vertex.x + length;
		right.y = vertex.y;
	}
	
	//Set the three child pointers to NULL if the depth is zero
	if(newDepth == 0)
	{
		child1 = NULL;
		child2 = NULL;
		child3 = NULL;
	}
	
	else
	{
		//Assign the mid-points to the three vector points
		point1 = midPoint(left, right);
		point2 = midPoint(left, bottom);
		point3 = midPoint(right, bottom);
		
		//Create three new Sierpinski objects with half of the length
		child1 = new Sierpinski(point1, 1, length/2.0, newDepth);
		child2 = new Sierpinski(point2, 2, length/2.0, newDepth);
		child3 = new Sierpinski(point3, 3, length/2.0, newDepth);
	}
	
}

void Sierpinski::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	//Create a triangle shape
	sf::ConvexShape triangle;
	
	//Using 3 points (bottom, left, and right)
	triangle.setPointCount(3);
	//Setting the points to the bottom, left, and right
	triangle.setPoint(0, bottom);
	triangle.setPoint(1, left);
	triangle.setPoint(2, right);
	
	//Setting the color to a mix
	sf::Color myColor = sf::Color(255 - left.y, 35 + bottom.y, 75 + right.y);
	triangle.setFillColor(myColor);
	triangle.setOutlineColor(sf::Color::Yellow);
	triangle.setOutlineThickness(0.8);
	//Draw the figure
	target.draw(triangle);
	
	//Draw the state of each of the child's pointer if the first child is not NULL
	if(child1 != NULL) 
	{
    		child1->draw(target, states);
    		child2->draw(target, states);
    		child3->draw(target, states);
  	}
}

sf::Vector2f Sierpinski::midPoint(sf::Vector2f leftPoint, sf::Vector2f rightPoint)
{
	//The mid-point is half the sum of the length of the left and right axis vector
	return sf::Vector2f((leftPoint.x + rightPoint.x)/2.0, (leftPoint.y + rightPoint.y)/2.0);
}

Sierpinski::~Sierpinski()
{
	//Delete all the child's pointer if the first child pointer is not NULL
	if (child1 != NULL) 
	{
    		delete (child1);
    		delete (child2);
    		delete (child3);
  	}
}

int main(int argc, char *argv[])
{
       if(argc != 3)
       {
       		std::cout << "Sierpinski [side-length] [recursion-depth]" << std::endl;
       		return -1;
       }

       else
       {
		//Initialize the depth and size from the command line argument
       		int side = atoi(argv[1]);
       		int depth = atoi(argv[2]);

		if(depth > 12)
		{
			std::cout << "The depth limit is 12! Not enough buffer to have a higher depth than 12!" << std::endl;
			return -2;
		}
       		//Create a Sierpinski object
       		Sierpinski triangle(side, depth);
       		//Crete a window with the specified side length
       		sf::RenderWindow window(sf::VideoMode(side, (int)(0.5 * sqrt(3.0)*(float)side)), "Sierpinski Triangle");
       		window.setVerticalSyncEnabled(true);
       		//Set the window's frame limit to 1
       		window.setFramerateLimit(1);
       		
       		while(window.isOpen())
       		{
       			sf::Event event;
       		
       			while(window.pollEvent(event))
       			{
       				//Close the window if the close button is pressed
       				if(event.type == sf::Event::Closed)
       				{
       					window.close();
       				}
       			}
       			//Clear the window
       			window.clear();
       			//Draw the Sierpinski triangle
       			window.draw(triangle);
       			//Display the window
       			window.display();
       		}
       }	
       return 0;
}
