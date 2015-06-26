// Mood Music.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <array>
using namespace std;

class Song
{
public:
	string artist, songName, genre; int moodLevel;

	Song()
	{}

	void setSong(string ar, string so, string ge, int mo)
	{
		artist = ar;
		songName = so;
		genre = ge;
		moodLevel = mo;
	}
};

int main()
{
	int userMoodLevel;
	cout<<"What is your mood level? -10 to 10: ";
	cin>>userMoodLevel;

	const int songNum = 5; //idk placeholder '20' for 20 songs right now
	//Song mySongs[songNum];

	array<Song, songNum> mySongs;

	int playOrSetsongs = 0;
	while(playOrSetsongs != 3)
	{
	cout<<"play songs - 1 \n set songs - 2 \n exit - 3 \n\n";
	cin>>playOrSetsongs;

	switch(playOrSetsongs)
	{
	case 1:
		for(int i = 0/*mySongs.begin()*/; i < songNum/*mySongs.end()*/; ++i)
		{
			if(mySongs[i].moodLevel == userMoodLevel)
			{
				//somehow play the mySongs[i];
				std::cout<<"playing song... "<<mySongs[i].songName<<" by "<<mySongs[i].artist<<"./n";
				userMoodLevel += 1; //1 right now, but possibly .1 in future or something
			}
		}
		break;
	case 2:
		for(int i = 0/*mySongs.begin()*/; i < songNum/*mySongs.end()*/; ++i)
		{
			cout<<"Song "<<i<<"\n";
			string ar; cout<<"artist: "; cin>>ar;
			string so; cout<<"song name: "; cin>>so;
			string ge; cout<<"genre: "; cin>>ge;
			int mo; cout<<"mood level: "; cin>>mo;
			mySongs[i].setSong(ar, so, ge, mo);
		}
		break;
	}
	}

	int fuck;
	cout<<"what the fuck. "; cin>>fuck;
	return 0;
}