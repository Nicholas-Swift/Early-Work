// Fortress Survival Alpha 0.0.5

//Add A* movement to player
//Add pressureplate + wall
//Add monsters

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <cstdio>

const int tileW(20), tileH(20);
static int level[tileW][tileH] = {
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};

class TileMap
{
public:
	sf::RectangleShape rect;

	TileMap(sf::Vector2f size, sf::Color defaultColor)
	{
		rect.setSize(size);
		rect.setFillColor(defaultColor);
	}

	void Update(sf::RenderWindow &Window)
	{
		for(int i = 0; i < tileH; i++)
		{
			for(int j = 0; j < tileW; j++)
			{
				if(level[i][j] == 0)
					rect.setFillColor(sf::Color::White);
				else if(level[i][j] == 1)
					rect.setFillColor(sf::Color::Black);
				else
					rect.setFillColor(sf::Color::Cyan);

				rect.setPosition(j*rect.getSize().x, i*rect.getSize().y);
				Window.draw(rect);
			}
		}
	}
};

class Selection
{
public:
	sf::RectangleShape rect;
	sf::Vector2f selectDown, selectCurrent;

	Selection(float thickness, sf::Color color)
	{
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineThickness(thickness);
		rect.setOutlineColor(color);
	}

	void Update(sf::RenderWindow &Window)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			rect.setPosition(selectDown);
			selectCurrent.x = sf::Mouse::getPosition(Window).x - selectDown.x;
			selectCurrent.y = sf::Mouse::getPosition(Window).y - selectDown.y;
			rect.setSize(selectCurrent);
			Window.draw(rect);
		}
		else
		{
			selectDown.x = sf::Mouse::getPosition(Window).x;
			selectDown.y = sf::Mouse::getPosition(Window).y;
		}
	}
};

//A*
static int Map[tileW][tileH];
static int closed_nodes_map[tileW][tileH];
static int open_nodes_map[tileW][tileH];
static int dir_map[tileW][tileH];
const int dir=4;
static int dx[dir]={1, 0, -1, 0};
static int dy[dir]={0, 1, 0, -1};

class Node
{
	sf::Vector2f pos;
	int level;
	int priority;

public:
	Node(int xp, int yp, int d, int p)
	{
		pos.x = xp;
		pos.y = yp;
		level = d;
		priority = p;
	}

	sf::Vector2f getPos() const
	{
		return pos;
	}

    int getLevel() const
	{
		return level;
	}

    int getPriority() const
	{
		return priority;
	}

	void updatePriority(const int & xDest, const int & yDest)
	{
		priority = level + estimate(xDest, yDest) * 10;
	}

	void nextLevel(const int & i)
	{
		level += (dir==8?(i%2==0?10:14):10);
	}

	const int & estimate(const int & xDest, const int & yDest) const
	{
		static int xd, yd, d;
		xd = xDest - pos.x;
		yd = yDest - pos.y;

		d=static_cast<int>(sqrt(xd*xd+yd*yd));

		return(d);
	}
};

bool operator<(const Node & a, const Node & b)
{
	return a.getPriority() > b.getPriority();
}

std::vector<sf::Vector2f> PathFind(sf::Vector2f &Start, sf::Vector2f &Finish)
{
	static std::priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static Node* n0;
    static Node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

	for(y = 0; y < tileH; y++)
    {
        for(x = 0; x < tileW; x++)
        {
            closed_nodes_map[x][y] = 0;
            open_nodes_map[x][y] = 0;
        }
    }

	n0 = new Node(Start.x, Start.y, 0, 0);
    n0->updatePriority(Finish.x, Finish.y);
    pq[pqi].push(*n0);
    open_nodes_map[x][y] = n0->getPriority();

    while(!pq[pqi].empty())
    {
        n0 = new Node( pq[pqi].top().getPos().x, pq[pqi].top().getPos().y, pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x = n0->getPos().x;
		y = n0->getPos().y;

        pq[pqi].pop();
        open_nodes_map[x][y] = 0;
        closed_nodes_map[x][y] = 1;

        if(x == Finish.x && y == Finish.y) 
        {
			std::string path = "";
            while(!(x == Start.x && y == Start.y))
            {
                j = dir_map[x][y];
                c = '0'+(j+dir/2)%dir;
                path = c+path;
                x += dx[j];
                y += dy[j];
            }
            delete n0;

            while(!pq[pqi].empty())
				pq[pqi].pop();
            //return path;

			///////////////////////////
			std::vector<sf::Vector2f> pathVec;
			int xer = Start.x * 32, yer = Start.y * 32;
			for(int i = 0; i < path.size(); i++)
			{
				switch(path[i])
				{
				case '0':
					pathVec.push_back(sf::Vector2f(xer + 32, yer));
					xer += 32;
					break;
				case '1':
					pathVec.push_back(sf::Vector2f(xer, yer + 32));
					yer += 32;
					break;
				case '2':
					pathVec.push_back(sf::Vector2f(xer - 32, yer));
					xer -= 32;
					break;
				case '3':
					pathVec.push_back(sf::Vector2f(xer, yer - 32));
					yer -= 32;
					break;
				}
			}
			return pathVec;
			///////////////////////////
        }

        for(i = 0; i < dir; i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx < 0 || xdx > tileW-1 || ydy < 0 || ydy > tileH-1 || Map[xdx][ydy] == 1 || closed_nodes_map[xdx][ydy] == 1))
            {
                m0 = new Node( xdx, ydy, n0->getLevel(), n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(Finish.x, Finish.y);

                if(open_nodes_map[xdx][ydy] == 0)
                {
                    open_nodes_map[xdx][ydy] = m0->getPriority();
                    pq[pqi].push(*m0);
                    dir_map[xdx][ydy] = (i+dir/2)%dir;
                }
                else if(open_nodes_map[xdx][ydy] > m0->getPriority())
                {
                    open_nodes_map[xdx][ydy] = m0->getPriority();
                    dir_map[xdx][ydy] = (i+dir/2)%dir;

                    while(!(pq[pqi].top().getPos().x == xdx && pq[pqi].top().getPos().y == ydy))
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pq[pqi].pop();

                    if(pq[pqi].size() > pq[1-pqi].size())
						pqi = 1-pqi;
                    while(!pq[pqi].empty())
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pqi = 1-pqi;
                    pq[pqi].push(*m0);
                }
                else
					delete m0;
            }
        }
        delete n0;
    }
	//return "";
	////////////////////////////////////////////////////
	std::vector<sf::Vector2f> nothing;
	return nothing;
	//////////////////////////////////////////////////////
};

class Player
{
public:
	sf::RectangleShape rect;
	bool selected;

	std::vector<sf::Vector2f> route;

	Player(sf::Vector2f position, sf::Vector2f size)
	{
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Green);

		selected = false;

		route.push_back(sf::Vector2f(0, 0));
	}

	void IsSelected(Selection s, sf::RenderWindow &Window)
	{
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if(rect.getGlobalBounds().intersects(s.rect.getGlobalBounds()) || (sf::Mouse::getPosition(Window).x > rect.getPosition().x && sf::Mouse::getPosition(Window).x < rect.getPosition().x + rect.getSize().x && sf::Mouse::getPosition(Window).y > rect.getPosition().y && sf::Mouse::getPosition(Window).y < rect.getPosition().y + rect.getSize().y))
			{
				selected = true;
				rect.setFillColor(sf::Color::Magenta);
			}
			else
			{
				selected = false;
				rect.setFillColor(sf::Color::Green);
			}
		}
	}

	std::vector<sf::Vector2f> Path(sf::RenderWindow &Window)
	{
		sf::Vector2f xyStart(rect.getPosition().x / 32, rect.getPosition().y / 32);
		sf::Vector2f xyFinish( (sf::Mouse::getPosition(Window).x - sf::Mouse::getPosition(Window).x%32 )/ 32, (sf::Mouse::getPosition(Window).y - sf::Mouse::getPosition(Window).y%32) / 32);

		for(int i = 0; i < tileH; i++)
		{
			for(int j = 0; j < tileW; j++)
			{
				if(level[i][j] == 0)
					Map[j][i] = 0;
				else if(level[i][j] == 1)
					Map[j][i] = 1;
			}
		}
		route = PathFind(xyStart, xyFinish);

		if(route.size() == 0 && rect.getPosition().x / 32 != xyFinish.x && rect.getPosition().y != xyFinish.y)
		{
			std::cout<<"An empty route generated!"<<std::endl;
			if(Map[int(xyFinish.x)][int(xyFinish.y-1)] != 1) //NEED MASSIVE WORK HERE
				xyFinish.y -= 1;
			else if(Map[int(xyFinish.x+1)][int(xyFinish.y)] != 1)
				xyFinish.x += 1;
			else if(Map[int(xyFinish.x)][int(xyFinish.y+1)] != 1)
				xyFinish.y += 1;
			else if(Map[int(xyFinish.x-1)][int(xyFinish.y)] != 1)
				xyFinish.x -= 1;
			route = PathFind(xyStart, xyFinish);
		}

		return route;
	}

	void Walk(sf::RenderWindow &Window)
	{
		for(int i = 0; i < route.size(); i++)
		{
			std::cout<<"route "<<i<<": "<<route[i].x<<", "<<route[i].y<<".\n";
		}

			rect.move(route[1].x/32, route[1].y/32);

		Window.draw(rect);
	}
};

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(640, 640), "Fortress Survival 0.0.5: simple, focused, new!");
	Window.setFramerateLimit(300);
	sf::Clock Clock;
	sf::Time deltaTime;

	TileMap tile(TileMap(sf::Vector2f(Window.getSize().x / tileW, Window.getSize().y / tileH), sf::Color::Red));
	Selection selection(Selection(2, sf::Color::White));
	Player player(Player(sf::Vector2f(64, 64), sf::Vector2f(Window.getSize().x / tileW, Window.getSize().y / tileH)));

	while(Window.isOpen())
	{
		deltaTime = Clock.restart();
		sf::Event Event;
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			}
		}

		tile.Update(Window);
		selection.Update(Window);

		player.IsSelected(selection, Window);
		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			player.route = player.Path(Window);
		}
		player.Walk(Window);

		Window.display();
		Window.clear();
	}
	return 0;
}