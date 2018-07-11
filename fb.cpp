// fb.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <fstream>

struct Attraction {
	std::string name;
	int pop = 0;
	int visited = 0;
};

bool compareByPopularity(const Attraction &a, const Attraction &b)
{
	return a.pop > b.pop;
}

bool compareByVisited(const Attraction &a, const Attraction &b)
{
	return a.visited < b.visited;
}


bool finalCompare(const Attraction &a, const Attraction &b)
{
	if (a.visited == b.visited)
	{
		return compareByPopularity(a, b);
	}
	else
		return compareByVisited(a, b);
}


int main()
{
	std::ifstream infile(_T("input.txt"), std::ifstream::in);
	std::fstream outfile(_T("output.txt"), std::ios::out);
	int T;
	//std::cin >> T;
	infile >> (int)T;
	std::cout << T;
	for (int t = 0; t < T; t++)
	{
		int N, K;
		long long V;
		//std::cin >> N >> K >> V;
		infile >> N >> K >> V;
		if (N == K)
			V = 1;
		else
			V = V % ((K%N) + (N-K));
		if (V == 0)
		{
			V = (K%N) + (N - K);
		}
		std::vector<std::string> attraction(N);
		std::vector<Attraction> atts(N);
		std::vector<Attraction> lastVisited(N);

		std::string x;
		getline(infile, x);
		for (int i = 0; i < N; i++)
		{
			//std::cin >> atts[i].name;
			//infile >> atts[i].name;
			getline(infile, atts[i].name, '\n');
			//std::cout << "\n... read that: " << atts[i].name;
		}

		for (int i = 0; i < atts.size(); i++)
		{
			atts[i].pop = atts.size() - i;
		}
		// iterate for visits:
		for (int v = 1; v <= V; v++)
		{
			// visit #v
			// sort first by Visited then by Popularity

			//std::sort(atts.begin(), atts.end(), compareByPopularity);
			//std::sort(atts.begin(), atts.end(), compareByVisited);
			//std::sort(atts.begin(), atts.en)
			std::sort(atts.begin(), atts.end(), finalCompare);
			lastVisited.clear();
			for (int k = 0; k < K; k++)
			{

				//std::cout << "\nVisit #" << v << " - Visiting: " << atts[k].name << std::endl;
				atts[k].visited++;
				//lastVisited[k].name = atts[k].name;
				lastVisited.push_back(atts[k]);
			}
		}

		std::sort(lastVisited.begin(), lastVisited.end(), compareByPopularity);
		// iterate over map..... vector of struct to display
		std::vector<Attraction>::iterator it;
		// (it = atts.begin(); it != atts.end(); it++)
		//{
		//	std::cout << it->name << ": " << it->pop << " (popularity) " << ": " << it->visited << " (visited) " << std::endl;
		//}

		//std::cout << "======== Final =======" << std::endl;
		int i = 0;
		//std::cout << "\nCase # " << T << ": ";
		outfile << "Case #" << t+1 << ": ";
		outfile.flush();
		for (it = lastVisited.begin(); it != lastVisited.end(); it++)
		{
			std::cout << it->name << " ";
			outfile << it->name << " ";
			outfile.flush();
		}
		//std::cout << std::endl;
		outfile << std::endl;
		//outfile.flush();
		//outfile.close();
	}
	
	infile.close();
	outfile.flush();
	
	system("pause");
	return 0;
}
