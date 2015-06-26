// Fortress Survival Alpha 0.0.4
//

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

sf::String level[] =
{
	"00000000000000000000",
	"00000000000000000000",
	"00000000000000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00011111111111111000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000001000000000",
	"00000000000000000000",
	"00000000000000000000"
}; const int tileW = 20, tileH = 20;

static int levelss[tileW][tileH] = {
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

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
				if(levelss[i][j] == 0)
					rect.setFillColor(sf::Color::White);
				else if(levelss[i][j] == 1)
					rect.setFillColor(sf::Color::Black);
				else
					continue;

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

class Player
{
public:
	sf::RectangleShape rect;

	bool selected;

	bool once;
	sf::Vector2f prevPos;

	Player(sf::Vector2f position, sf::Vector2f size)
	{
		once = true;
		rect.setPosition(position);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Green);
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
};

static int map[tileW][tileH];
static int closed_nodes_map[tileW][tileH]; // map of closed (tried-out) nodes
static int open_nodes_map[tileW][tileH]; // map of open (not-yet-tried) nodes
static int dir_map[tileW][tileH]; // map of directions
const int dir=8; // number of possible directions to go at any position
// if dir==4
//static int dx[dir]={1, 0, -1, 0};
//static int dy[dir]={0, 1, 0, -1};
// if dir==8
static int dx[dir]={1, 1, 0, -1, -1, -1, 0, 1};
static int dy[dir]={0, 1, 1, 1, 0, -1, -1, -1};

class node
{
    // current position
    int xPos;
    int yPos;
    // total distance already travelled to reach the node
    int level;
    // priority=level+remaining distance estimate
    int priority;  // smaller: higher priority

    public:
        node(int xp, int yp, int d, int p) 
            {xPos=xp; yPos=yp; level=d; priority=p;}
    
        int getxPos() const {return xPos;}
        int getyPos() const {return yPos;}
        int getLevel() const {return level;}
        int getPriority() const {return priority;}

        void updatePriority(const int & xDest, const int & yDest)
        {
             priority=level+estimate(xDest, yDest)*10; //A*
        }

        // give better priority to going strait instead of diagonally
        void nextLevel(const int & i) // i: direction
        {
             level+=(dir==8?(i%2==0?10:14):10);
        }
        
        // Estimation function for the remaining distance to the goal.
        const int & estimate(const int & xDest, const int & yDest) const
        {
            static int xd, yd, d;
            xd=xDest-xPos;
            yd=yDest-yPos;         

            // Euclidian Distance
            //d=static_cast<int>(sqrt(xd*xd+yd*yd));

            // Manhattan distance
            d=abs(xd)+abs(yd);
            
            // Chebyshev distance
            //d=max(abs(xd), abs(yd));

            return(d);
        }
};

// Determine priority (in the priority queue)
bool operator<(const node & a, const node & b)
{
  return a.getPriority() > b.getPriority();
}

// A-star algorithm.
// The route returned is a string of direction digits.
std::string pathFind( const int & xStart, const int & yStart, const int & xFinish, const int & yFinish )
{
    static std::priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
    static int pqi; // pq index
    static node* n0;
    static node* m0;
    static int i, j, x, y, xdx, ydy;
    static char c;
    pqi=0;

    // reset the node maps
    for(y=0;y<tileH;y++)
    {
        for(x=0;x<tileW;x++)
        {
            closed_nodes_map[x][y]=0;
            open_nodes_map[x][y]=0;
        }
    }

    // create the start node and push into list of open nodes
    n0=new node(xStart, yStart, 0, 0);
    n0->updatePriority(xFinish, yFinish);
    pq[pqi].push(*n0);
    open_nodes_map[x][y]=n0->getPriority(); // mark it on the open nodes map

    // A* search
    while(!pq[pqi].empty())
    {
        // get the current node w/ the highest priority
        // from the list of open nodes
        n0=new node( pq[pqi].top().getxPos(), pq[pqi].top().getyPos(), 
                     pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

        x=n0->getxPos(); y=n0->getyPos();

        pq[pqi].pop(); // remove the node from the open list
        open_nodes_map[x][y]=0;
        // mark it on the closed nodes map
        closed_nodes_map[x][y]=1;

        // quit searching when the goal state is reached
        //if((*n0).estimate(xFinish, yFinish) == 0)
        if(x==xFinish && y==yFinish) 
        {
            // generate the path from finish to start
            // by following the directions
            std::string path="";
            while(!(x==xStart && y==yStart))
            {
                j=dir_map[x][y];
                c='0'+(j+dir/2)%dir;
                path=c+path;
                x+=dx[j];
                y+=dy[j];
            }

            // garbage collection
            delete n0;
            // empty the leftover nodes
            while(!pq[pqi].empty()) pq[pqi].pop();           
            return path;
        }

        // generate moves (child nodes) in all possible directions
        for(i=0;i<dir;i++)
        {
            xdx=x+dx[i]; ydy=y+dy[i];

            if(!(xdx<0 || xdx>tileW-1 || ydy<0 || ydy>tileH-1 || map[xdx][ydy]==1 
                || closed_nodes_map[xdx][ydy]==1))
            {
                // generate a child node
                m0=new node( xdx, ydy, n0->getLevel(), 
                             n0->getPriority());
                m0->nextLevel(i);
                m0->updatePriority(xFinish, yFinish);

                // if it is not in the open list then add into that
                if(open_nodes_map[xdx][ydy]==0)
                {
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    pq[pqi].push(*m0);
                    // mark its parent node direction
                    dir_map[xdx][ydy]=(i+dir/2)%dir;
                }
                else if(open_nodes_map[xdx][ydy]>m0->getPriority())
                {
                    // update the priority info
                    open_nodes_map[xdx][ydy]=m0->getPriority();
                    // update the parent direction info
                    dir_map[xdx][ydy]=(i+dir/2)%dir;

                    // replace the node
                    // by emptying one pq to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(pq[pqi].top().getxPos()==xdx && 
                           pq[pqi].top().getyPos()==ydy))
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pq[pqi].pop(); // remove the wanted node

                    // empty the larger size pq to the smaller one
                    if(pq[pqi].size()>pq[1-pqi].size()) pqi=1-pqi;
                    while(!pq[pqi].empty())
                    {                
                        pq[1-pqi].push(pq[pqi].top());
                        pq[pqi].pop();       
                    }
                    pqi=1-pqi;
                    pq[pqi].push(*m0); // add the better node instead
                }
                else delete m0;
            }
        }
        delete n0; // garbage collection
    }
    return ""; // no route found
}

int main()
{
	sf::RenderWindow Window;
	Window.create(sf::VideoMode(640, 640), "Fortress Survival 0.0.4, a new approach!");
	Window.setFramerateLimit(300);

	Selection selection(Selection(2, sf::Color::White));
	Player player(Player(sf::Vector2f(32, 32), sf::Vector2f(32, 32)));

	TileMap tile(TileMap(sf::Vector2f(Window.getSize().x / tileW, Window.getSize().y / tileH), sf::Color::Red));
	for(int i = 0; i < tileH; i++)
	{
		for(int j = 0; j < tileW; j++)
		{
			if(level[i][j] == '0')
				map[j][i] = 0;
			else if(level[i][j] == '1')
				map[j][i] = 1;
		}
	}
	int xA, yA, xB, yB;
	std::string route;

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
			}
		}

		tile.Update(Window);

		selection.Update(Window);

		player.IsSelected(selection, Window);
		//player.Walk(Window);

		if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
		xA = player.rect.getPosition().x / 32; yA = player.rect.getPosition().y / 32; xB = sf::Mouse::getPosition(Window).x / 32; yB = sf::Mouse::getPosition(Window).y /32;

	//std::cout<<"Map Size (X,Y): "<<tileW<<","<<tileH<<std::endl;
    //std::cout<<"Start: "<<xA<<","<<yA<<std::endl;
    //std::cout<<"Finish: "<<xB<<","<<yB<<std::endl;
	// get the route
    //clock_t start = clock();
    route = pathFind(xA, yA, xB, yB);
    if(route=="") std::cout<<"An empty route generated!"<<std::endl;
    //clock_t end = clock();
    //double time_elapsed = double(end - start);
    //std::cout<<"Time to calculate the route (ms): "<<time_elapsed<<std::endl;
    //std::cout<<"Route:"<<std::endl;
    //std::cout<<route<<std::endl<<std::endl;

	 // follow the route on the map and display it 
    if(route.length()>0)
    {
        int j; char c;
        int x=xA;
        int y=yA;
        map[x][y]=2;
        for(int i=0;i<route.length();i++)
        {
            c =route.at(i);
            j=atoi(&c); 
            x=x+dx[j];
            y=y+dy[j];
            map[x][y]=3;
        }
        map[x][y]=4;
    
        // display the map with the route
        /*for(int y=0;y<tileH;y++)
        {
            for(int x=0;x<tileW;x++)
                if(map[x][y]==0)
                    std::cout<<".";
                else if(map[x][y]==1)
                    std::cout<<"O"; //obstacle
                else if(map[x][y]==2)
                    std::cout<<"S"; //start
                else if(map[x][y]==3)
                    std::cout<<"R"; //route
                else if(map[x][y]==4)
                    std::cout<<"F"; //finish
            std::cout<<std::endl;
        }*/

		for(int i = 0; i < tileH; i++)
	{
		for(int j = 0; j < tileW; j++)
		{
			if(level[i][j] == '0')
				map[j][i] = 0;
			else if(level[i+1][j] == '1')
				map[j][i] = 1;
		}
	}


	}
	}
		for(int i = 0; i < route.size(); i++)
		{
			sf::Time wtf;
			if(route[i] == '0')
				player.rect.move(32, 0);
			else if(route[i] == '1')
				player.rect.move(32, 32);
			else if(route[i] == '2')
				player.rect.move(0, 32);
			else if(route[i] == '3')
				player.rect.move(-32, 32);
			else if(route[i] == '4')
				player.rect.move(-32, 0);
			else if(route[i] == '5')
				player.rect.move(-32, -32);
			else if(route[i] == '6')
				player.rect.move(0, -32);
			else if(route[i] == '7')
				player.rect.move(32, -32);
		}
		if(player.rect.getPosition().x > Window.getSize().x || player.rect.getPosition().y > Window.getSize().x)
		{
			player.rect.setPosition(32, 32);
		}
		std::cout<<"Player pos: "<<player.rect.getPosition().x<<", "<<player.rect.getPosition().y<<"\n";

		Window.display();
		Window.clear();
	}
	return 0;
}