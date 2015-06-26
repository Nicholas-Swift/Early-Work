//Exercise 2
//Change the Critter Caretaker program so that the critter is more expressive about its needs by hinting at how hungry
//and bored it is.

#include "stdafx.h"
#include <iostream>
using namespace std;

class Critter
{
public:
	Critter(int hunger = 0, int boredom = 0);
	void Talk();
	void Eat(int food = 4);
	void Play(int fun = 4);

private:
	int m_Hunger;
	int m_Boredom;

	int GetMood() const;
	void PassTime(int time = 1);
};

Critter::Critter(int hunger, int boredom):
	m_Hunger(hunger),
	m_Boredom(boredom)
{}

inline int Critter::GetMood() const
{
	return(m_Hunger + m_Boredom);
}

void Critter::PassTime(int time)  //had to add limits to boredom and hunger, so 'but' or 'and' would work properly
{
	m_Hunger += time;
	m_Boredom += time;

	if(m_Hunger > 12)
	{
		m_Hunger = 12;
	}

	if(m_Boredom > 12)
	{
		m_Boredom = 12;
	}
}

void Critter::Talk()
{
	cout<<"I'm a critter and I feel ";

	{	//The critter's overall mood
		int mood = GetMood();
		if(mood > 15)
		{
			cout<<"mad.\n";
		}
		
		else if(mood > 10)
		{
			cout<<"frustrated.\n";
		}
	
		else if(mood > 5)
		{
			cout<<"okay.\n";
		}
	
		else
		{
			cout<<"happy.\n";
		}
	}

	{	//the critter's hunger hint
		if(m_Hunger > 8)
		{
			cout<<"I'm starving to death";
		}

		else if(m_Hunger > 5)
		{
			cout<<"I'm hungry";
		}

		else if (m_Hunger > 2)
		{
			cout<<"I'm not hungry";
		}

		else
		{
			cout<<"I'm full";
		}
	}

	{	//whether to use 'but' or 'and'
		if((m_Boredom > m_Hunger + 3) || (m_Hunger > m_Boredom + 3))
		{
			cout<<", but ";
		}

		else
		{
			cout<<" and ";
		}
	}

	{	//the critter's boredom hint
		if(m_Boredom > 8)
		{
			cout<<"I'm bored out of my mind!\n";
		}

		else if(m_Boredom > 5)
		{
			cout<<"I'm bored.\n";
		}

		else if (m_Boredom > 2)
		{
			cout<<"I'm not bored.\n";
		}

		else
		{
			cout<<"I'm having a lot of fun!\n";
		}
	}
	
	PassTime();
}
	
void Critter::Eat(int food)
{
	cout<<"Burrppp.\n";
	m_Hunger -= food;

	if(m_Hunger < 0)
	{
		m_Hunger = 0;
	}

	PassTime();
}

void Critter::Play(int fun)
{
	cout<<"Wheee!\n";

	m_Boredom -= fun;
	if(m_Boredom < 0)
	{
		m_Boredom = 0;
	}

	PassTime();
}

int main()
{
	Critter crit;
	crit.Talk();

	int choice;
	do
	{
		cout<<"\nCritter Caretaker\n\n";
		cout<<"0 - Quit\n";
		cout<<"1 - Listen to your critter\n";
		cout<<"2 - Feed your critter\n";
		cout<<"3 - Play with your critter\n\n";

		cout<<"Choice: ";
		cin>>choice;

		switch(choice)
		{
		case 0:
			cout<<"Good-bye.\n";
			break;

		case 1:
			crit.Talk();
			break;

		case 2:
			crit.Eat();
			break;

		case 3:
			crit.Play();
			break;
		default:
			cout<<"\nSorry, but "<<choice<<" isn't a valid choice.\n";
		}
	}while(choice != 0);

	return 0;
}