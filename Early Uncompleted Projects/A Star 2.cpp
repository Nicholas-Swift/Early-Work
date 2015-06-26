// A Star 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>

const int TILE_W(20), TILE_H(20);
static int Map[TILE_W][TILE_H] = {
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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

/* PATHFINDING CRAP PATHFINDING CRAP PATHFINDING CRAP PATHFINDING CRAP PATHFINDING CRAP PATHFINDING CRAP*/
static int closed_nodes_map[TILE_W][TILE_H];
static int open_nodes_map[TILE_W][TILE_H];
static int dir_map[TILE_W][TILE_H];
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

		d=static_cast<int>(sqrtf(xd*xd+yd*yd));

		return(d);
	}
};

bool operator<(const Node & a, const Node & b)
{
	return a.getPriority() > b.getPriority();
}

std::string PathFind(sf::Vector2f &Start, sf::Vector2f &Finish)
{
	static std::priority_queue<Node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static Node* n0;
    static Node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

	for(y = 0; y < TILE_H; y++)
    {
        for(x = 0; x < TILE_W; x++)
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
            return path;
        }

        for(i = 0; i < dir; i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx < 0 || xdx > TILE_W-1 || ydy < 0 || ydy > TILE_H-1 || Map[ydy][xdx] == 1 || closed_nodes_map[xdx][ydy] == 1))
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
	return "";
};

/* PATHFINDING CRAP PATHFINDING CRAP PATHFINDING CRAP PATHFINDING CRAP PATHFINDING CRAP PATHFINDING CRAP PATHFINDING CRAP */

class TileMap
{
public:
	sf::RectangleShape rect;

	TileMap(sf::Vector2f size, sf::Color defaultColor)
	{
		rect.setSize(size);
		rect.setFillColor(defaultColor);
		rect.setOutlineThickness(0.5);
		rect.setOutlineColor(sf::Color::Magenta);
	}

	void Update(sf::RenderWindow &Window)
	{
		for(int i = 0; i < TILE_H; i++)
		{
			for(int j = 0; j < TILE_W; j++)
			{
				if(Map[i][j] == 0)
					rect.setFillColor(sf::Color::White);
				else if(Map[i][j] == 1)
					rect.setFillColor(sf::Color::Black);
				else
					rect.setFillColor(sf::Color::Cyan);

				rect.setPosition(j*rect.getSize().x, i*rect.getSize().y);
				Window.draw(rect);
			}
		}
	}
};

class Player
{
public:
	sf::RectangleShape rect;

	std::vector<sf::Vector2f> path;
	std::string strPath;

	int movPos;
	int travelPos;

	sf::Vector2f partialDowns;

	Player(sf::Vector2f position, sf::Vector2f size)
	{
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Green);

		path.push_back(rect.getPosition());
		strPath = "";

		movPos = 0;
		travelPos = 0;
	}

	void Update(sf::RenderWindow &Window)
	{
		Window.draw(rect);
	}

	void PlayerPath(sf::RenderWindow &Window, sf::Vector2f fin)
	{
		sf::Vector2f start;

		std::string str = "";

		if( movPos < strPath.size())
		{
			start.x = path[movPos].x / 32;
			start.y = path[movPos].y / 32;
			str += strPath[movPos];

			std::cout<<"x: "<<path[movPos].x/32<<", y: "<<path[movPos].y/32<<std::endl; //MOVE POS IS THE ONE IT HAS TO MOVE TO, NOT THE ONE IT'S AT
		}
		else
		{
			start.x = (int(rect.getPosition().x) - int(rect.getPosition().x)%32) / 32;
			start.y = (int(rect.getPosition().y) - int(rect.getPosition().x)%32) / 32;
		}

		std::string s = PathFind(start, fin);
		str += s;

		PathRecombobulation(str);
	};

	void PathRecombobulation(std::string &string)
	{
		strPath = "";
		strPath += string;
		
		path.clear();
		int xPos((int(rect.getPosition().x) - int(rect.getPosition().x)%32));
		int yPos((int(rect.getPosition().y) - int(rect.getPosition().y)%32));
		path.push_back(sf::Vector2f(xPos, yPos));

		for(int i = 0; i < string.size(); i++)
		{
			switch(string[i])
			{
			case '0':
				path.push_back(sf::Vector2f(xPos + 32, yPos));
				xPos += 32;
				break;
			case '1':
				path.push_back(sf::Vector2f(xPos, yPos + 32));
				yPos += 32;
				break;
			case '2':
				path.push_back(sf::Vector2f(xPos - 32, yPos));
				xPos -= 32;
				break;
			case '3':
				path.push_back(sf::Vector2f(xPos, yPos - 32));
				yPos -= 32;
				break;
			}
		}

		//if(path.size() > 1)
			//path.erase(path.begin());
	}

	void Walk(sf::RenderWindow &Window, float movConstant)
	{
		if( (movPos + 1) == path.size())
		{
			movPos = 0;
			strPath = "";
			path.clear();
			path.push_back(rect.getPosition());
		}

		if(std::abs(rect.getPosition().x - path[movPos].x) >= 32 || std::abs(rect.getPosition().y - path[movPos].y) >= 32)
		{
			movPos += 1;
		}

		if(strPath == "")
		{
			movPos = 0;
			travelPos = 0;
		}
		else if(strPath[movPos] == '0')
		{
			rect.move(movConstant, 0);
			travelPos += movConstant;
		}
		else if(strPath[movPos] == '1')
		{
			rect.move(0, movConstant);
			travelPos += movConstant;
		}
		else if(strPath[movPos] == '2')
		{
			rect.move(-movConstant, 0);
			travelPos += movConstant;
		}
		else if(strPath[movPos] == '3')
		{
			rect.move(0, -movConstant);
			travelPos += movConstant;
		}

		//std::cout<<strPath<<std::endl;
		//for(int i = 0; i < path.size(); i++)
		//	std::cout<<"x: "<<path[i].x<<", y: "<<path[i].y<<std::endl;

		//std::cout<<path.size()<<std::endl;
		//std::cout<<strPath.size()<<std::endl;
		//std::cout<<movPos<<std::endl;

		//std::cout<<"x: "<<path[movPos].x<<", y: "<<path[movPos].y<<std::endl; //MOVE POS IS THE ONE IT HAS TO MOVE TO, NOT THE ONE IT'S AT
		//std::cout<<strPath[movPos]<<std::endl;

		//std::cout<<"x: "<<path[0].x<<", y: "<<path[0].y<<std::endl;

		//std::cout<<int(rect.getPosition().x)%32<<std::endl;
	}
};

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(640, 640), "Pathfinding revisited");
	Window.setFramerateLimit(300);

	TileMap tile(TileMap(sf::Vector2f(32, 32), sf::Color::Red));
	Player player(Player(sf::Vector2f(32, 32), sf::Vector2f(32, 32)));

	while(Window.isOpen())
	{
		sf::Event Event;
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2f finish;
				finish.x = /*(int*/(sf::Mouse::getPosition(Window).x) /*- int(sf::Mouse::getPosition(Window).x)%32)*/ / 32;
				finish.y = /*(int*/(sf::Mouse::getPosition(Window).y) /*- int(sf::Mouse::getPosition(Window).y)%32)*/ / 32;
				player.PlayerPath(Window, finish);
				break;
			}
		}

		tile.Update(Window);

		//if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		//{
		//	sf::Vector2f finish;
		//	finish.x = /*(int*/(sf::Mouse::getPosition(Window).x) /*- int(sf::Mouse::getPosition(Window).x)%32)*/ / 32;
		//	finish.y = /*(int*/(sf::Mouse::getPosition(Window).y) /*- int(sf::Mouse::getPosition(Window).y)%32)*/ / 32;
		//	player.PlayerPath(Window, finish);
		//}
		
		player.Walk(Window, 1);
		player.Update(Window);

		Window.display();
		Window.clear();
	}

	return 0;
}

