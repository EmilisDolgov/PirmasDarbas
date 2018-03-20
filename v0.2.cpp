// Vidurkis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdlib.h>
#include <chrono>
#include "studentai.h"


using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::array;
using std::fixed;
using std::setprecision;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::stringstream;


int main()
{
	string vardas;
	string pavarde;
	bool inpmetodas;
	bool sk;
	double vidurkis{};
	double sum{};
	double egz{};
	int n{};
	int moksk{};
	double laik{};
	vector<double> paz{};
	vector<mokinys> prileisti;
	vector<mokinys> neprileisti;
	cout << "Kiek mokiniu sugeneruoti?" << endl;
	cin >> moksk;
	auto start = std::chrono::high_resolution_clock::now();
	generavimasfailo(moksk);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	cout << "Failo nuskaitymo laikas: " << elapsed.count() << "s" << endl;
	cout << "Duomenu ivedimo budas: ivedimas(0) arba skaitymas is failo(1)" << endl;
	cin >> sk;
	if (!sk)
	{
		cout << "Vardas: ";
		cin >> vardas;
		cout << "Pavarde: ";
		cin >> pavarde;
		cout << "Egzamino ivertinimas: ";
		cin >> egz;
		cout << "Pazymiu gavimo budas: ivedimas(0) arba generavimas(1)" << endl;
		cin >> inpmetodas;
		int input{};
		if (!inpmetodas)
		{
			cout << "Pazymiai. Noredami sustabdyti vedima iveskite -1" << endl;
			while (cin >> input)
			{
				if (input==-1)
					break;
				paz.push_back(input);
				n++;
			}
			if (paz.size()== 0)
			{
				cout << "Privalote ivesti ND ivertinimus" << endl;
				return 1;
			}
		}
		else
		{
			std::random_device rd;  //Will be used to obtain a seed for the random number engine
			std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
			std::uniform_int_distribution<> dis(1, 10);
			cout << "Kiek skaiciu sugeneruoti?" << endl;
			cin >> n;
			for (auto i = 0; i < n; i++)
			{
				paz.push_back(dis(gen));
			}

		}
		outputcons(vardas, pavarde, paz, egz);
	}
	else
	{
		vector<mokinys> a;
		ifstream in("kursiokai.txt");
		int i{};
		for(auto i=0;i<moksk;i++)
		{	
			a.push_back(mokinys());
			in >> a[i].vardas >> a[i].pavarde;
			string line;
			getline(in, line);
			std::istringstream iss(line);
			double temp;
			while (iss >> temp)
				a[i].paz.push_back(temp);
			temp = a[i].paz.back();
			a[i].egz = temp;
			a[i].paz.pop_back();
		}
		bool metodas;
		cout << "Pazymiu skaiciavimo budas: mediana(0) arba vidurkis(1)" << endl;
		cin >> metodas;
		auto start = std::chrono::high_resolution_clock::now();
		sortas(a);
		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;
		cout << "Duomenu suskirtimo ir isvedimo laikas: " << elapsed.count() << "s" << endl;
		outputfile(a, prileisti, neprileisti, metodas);
		cout << a.size() << endl;
		in.close();
	}
	return 0;
}