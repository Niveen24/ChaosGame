// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
// Create a video mode object
     VideoMode vm(1920, 1080);
// Create and open a window for the game
    RenderWindow window(vm, "Chaos..?", Style::Default);
    vector<Vector2f> vertices;
    vector<Vector2f> points;

//background 
	Texture background;
	background.loadFromFile("textures/sp7.png");
	Sprite bg;
	bg.setTexture(background);
    float scaleX = 1920.0f / background.getSize().x;
    float scaleY = 1080.0f / background.getSize().y;
	float scale = max(scaleX, scaleY);
	bg.setScale(scale, scale);
	bg.setPosition((1920 - background.getSize().x * scale) / 2, (1080 - background.getSize().y * scale) / 2);
//font
	Font font;
	font.loadFromFile("fonts/f3.ttf"); //insert font here
//text object for title
	Text title("CHAOS", font, 70);
	title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
	title.setPosition(window.getSize().x / 2, 40);
    title.setFillColor(Color::White);
//text object for instructions
	Text instructions("Click 3 points to set as vertices", font, 10);
	instructions.setOrigin(instructions.getLocalBounds().width / 2, instructions.getLocalBounds().height / 2);
	instructions.setPosition(window.getSize().x / 2, 100);
 

    while (window.isOpen())
    {
        //input section****

        Event event;

        while (window.pollEvent(event))

        {
            if (event.type == Event::Closed)
            {
                window.close(); //quit game when closed
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y)); //tracks the vertices positions and puts into vector
                        if (vertices.size() == 3)
                        {
                            instructions.setString("Now click 1 final point to start the chaos.");
                        }
                    }
                   
                    else if (points.size() == 0)
                    {
                        ///fourth click
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y)); //tracks 4th point position and into vector
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

		//update section****

        int ppf = 150; //sets num of points to update per frame

        if (points.size() > 0) //so it only runs this after 4th click
        {
            for (int i = 0; i < ppf; i++) //repeats body code ppf times per update
            {
                Vector2f randomVertex = vertices[rand() % vertices.size()]; //gets random vertices from vector
                Vector2f lastPoint = points.back(); //gets last point generated
				Vector2f newPoint = (lastPoint + randomVertex) / 2.0f; //gets midpoint of the rand vertice and last vertice
                points.push_back(newPoint); //stores new point to be drawn
            }
        }

		//draw section****

        window.clear();
        window.draw(bg); //load background first so it shows

        for (int i = 0; i < vertices.size(); i++) 
        {
            RectangleShape rect(Vector2f(5, 5)); //makes rectangle 10x10 to mark each pt clicked

            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y)); //puts rect at the vertices coords

            rect.setFillColor(Color::White);

            window.draw(rect);
        }

        //draw title before display
        window.draw(title);
        window.draw(instructions);
		//draw points
        for (int i = 0; i < points.size(); i++) //loops through all points
        {
            CircleShape circle(1); //makes 1pxl circle to mark each point
            circle.setPosition(points[i].x, points[i].y); //positions the pixel at the point coords
            circle.setFillColor(Color::Red);
            window.draw(circle);
		}

        window.display();
    }
}