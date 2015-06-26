// Swift's Pathfinding Algorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

const int tile_width(10), tile_height(10);
int map[tile_width][tile_height] = {
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 1, 1, 1, 1, 1, 0, 0,
	0, 1, 0, 1, 0, 0, 0, 1, 0, 0,
	0, 1, 0, 1, 0, 0, 0, 1, 0, 0,
	0, 1, 0, 1, 1, 0, 1, 1, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

struct Node
{
	int xPosition, yPosition;
	int posInVector;
	int parentInVector;

	Node(int xp, int yp)
	{
		xPosition = xp;
		yPosition = yp;
	}
};

void addToVector(std::vector<Node> &vectorOfNodes, int &parentNumber, int &positionNumber, int xPlus, int yPlus)
{
	vectorOfNodes.push_back(Node(vectorOfNodes[parentNumber].xPosition + xPlus, vectorOfNodes[parentNumber].yPosition + yPlus));
	vectorOfNodes[positionNumber].posInVector = positionNumber;
	vectorOfNodes[positionNumber].parentInVector = parentNumber;
}

std::string FindPath(int xStart, int yStart, int xFinish, int yFinish)
{
	int pathMap[tile_width][tile_height];
	for(int i = 0; i < tile_height; i++)
	{
		for(int j = 0; j < tile_width; j++)
		{
			if(map[i][j] == 1)
				pathMap[j][i] = 1;
			else if(map[i][j] == 0)
				pathMap[j][i] = 0;
		}
	}

	std::vector<Node> vectorOfNodes;

	vectorOfNodes.push_back(Node(xStart, yStart));
	vectorOfNodes[0].posInVector = 0;
	pathMap[vectorOfNodes[0].xPosition][vectorOfNodes[0].yPosition] = 1;

	int parentNumber = 0;
	int positionNumber = 1;

	while( !(vectorOfNodes[parentNumber].xPosition == xFinish && vectorOfNodes[parentNumber].yPosition == yFinish) )
	{
		if(parentNumber % 2 == 0)
		{
			//top
			if( pathMap[vectorOfNodes[parentNumber].xPosition][vectorOfNodes[parentNumber].yPosition - 1] == 0 && vectorOfNodes[parentNumber].yPosition - 1 > 0 )
			{
				addToVector(vectorOfNodes, parentNumber, positionNumber, 0, -1);
				pathMap[vectorOfNodes[positionNumber].xPosition][vectorOfNodes[positionNumber].yPosition] = 1;
				positionNumber += 1;
			}

			//bottom
			if( pathMap[vectorOfNodes[parentNumber].xPosition][vectorOfNodes[parentNumber].yPosition + 1] == 0 && vectorOfNodes[parentNumber].yPosition + 1 < tile_height )
			{
				addToVector(vectorOfNodes, parentNumber, positionNumber, 0, 1);
				pathMap[vectorOfNodes[positionNumber].xPosition][vectorOfNodes[positionNumber].yPosition] = 1;
				positionNumber += 1;
			}

			//right
			if( pathMap[vectorOfNodes[parentNumber].xPosition + 1][vectorOfNodes[parentNumber].yPosition] == 0 && vectorOfNodes[parentNumber].xPosition + 1 < tile_width )
			{
				addToVector(vectorOfNodes, parentNumber, positionNumber, 1, 0);
				pathMap[vectorOfNodes[positionNumber].xPosition][vectorOfNodes[positionNumber].yPosition] = 1;
				positionNumber += 1;
			}

			//left
			if( pathMap[vectorOfNodes[parentNumber].xPosition - 1][vectorOfNodes[parentNumber].yPosition] == 0 && vectorOfNodes[parentNumber].xPosition - 1 > 0 )
			{
				addToVector(vectorOfNodes, parentNumber, positionNumber, -1, 0);
				pathMap[vectorOfNodes[positionNumber].xPosition][vectorOfNodes[positionNumber].yPosition] = 1;
				positionNumber += 1;
			}
		}

		else
		{
			//right
			if( pathMap[vectorOfNodes[parentNumber].xPosition + 1][vectorOfNodes[parentNumber].yPosition] == 0 && vectorOfNodes[parentNumber].xPosition + 1 < tile_width )
			{
				addToVector(vectorOfNodes, parentNumber, positionNumber, 1, 0);
				pathMap[vectorOfNodes[positionNumber].xPosition][vectorOfNodes[positionNumber].yPosition] = 1;
				positionNumber += 1;
			}

			//left
			if( pathMap[vectorOfNodes[parentNumber].xPosition - 1][vectorOfNodes[parentNumber].yPosition] == 0 && vectorOfNodes[parentNumber].xPosition - 1 > 0 )
			{
				addToVector(vectorOfNodes, parentNumber, positionNumber, -1, 0);
				pathMap[vectorOfNodes[positionNumber].xPosition][vectorOfNodes[positionNumber].yPosition] = 1;
				positionNumber += 1;
			}

			//top
			if( pathMap[vectorOfNodes[parentNumber].xPosition][vectorOfNodes[parentNumber].yPosition - 1] == 0 && vectorOfNodes[parentNumber].yPosition - 1 > 0 )
			{
				addToVector(vectorOfNodes, parentNumber, positionNumber, 0, -1);
				pathMap[vectorOfNodes[positionNumber].xPosition][vectorOfNodes[positionNumber].yPosition] = 1;
				positionNumber += 1;
			}

			//bottom
			if( pathMap[vectorOfNodes[parentNumber].xPosition][vectorOfNodes[parentNumber].yPosition + 1] == 0 && vectorOfNodes[parentNumber].yPosition + 1 < tile_height )
			{
				addToVector(vectorOfNodes, parentNumber, positionNumber, 0, 1);
				pathMap[vectorOfNodes[positionNumber].xPosition][vectorOfNodes[positionNumber].yPosition] = 1;
				positionNumber += 1;
			}
		}

		parentNumber += 1;
	}

	//MODIFY THIS PART TO FIT YOUR NEEDS!
	std::string path;
	int g;

	g = vectorOfNodes[parentNumber].posInVector;
	std::cout<<vectorOfNodes[g].xPosition<<", "<<vectorOfNodes[g].yPosition<<"... ";

	while(g != 0)
	{
		g = vectorOfNodes[g].parentInVector;
		std::cout<<vectorOfNodes[g].xPosition<<", "<<vectorOfNodes[g].yPosition<<"... ";
	}

	return(path);
	//MODIFY THIS PART TO FIT YOUR NEEDS!
};

int main()
{
	std::cout<<"Swift's Simple Pathfinding Algorithm!\n"<<std::endl;

	std::cout<<"Map:\n";
	for(int i = 0; i < tile_height; i++)
	{
		for(int j = 0; j < tile_width; j++)
		{
			std::cout<<map[i][j];
		}
		std::cout<<"\n";
	}

	std::cout<<"\n\n";
	std::string path = FindPath(0, 0, 2, 1);
	std::cout<<path<<std::endl;

	int downs;
	std::cin>>downs;
	return 0;
}

