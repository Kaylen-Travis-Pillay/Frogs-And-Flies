#pragma once
#define DLLExport __declspec(dllexport) 
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <typeinfo>
#include <vector>

#define output std::cout
#define nxtln std::endl
#define input std::cin

/*
	File Name: KTPAlgo_LIB.h
	Date     : 10/04/2017
	Author   : Kaylen Travis Pillay
	Creation : COMP315 - Advanced Programming { Major Group Project }

	Details  : This is a library that I (Kaylen Travis Pillay) created to
	           help build an assignment. This library however has general
			   methods and classes that will help with many different 
			   applications, like a simple database for csv files, or 
			   getting the IPv4 address of your computer with a single 
			   method call.

			   This library is completely open source and was made as a 
			   contribution to programmers all over the world in mind. 
			   Make it your own and enjoy! I hope this made your life a
			   little easier. 

			   Please find the full documentation for this class at
			   http://www.ktpsolutions.co.za/KTPALGO/

    KTPAlgo_Library Copyright (C) 2017  Kaylen Travis Pillay

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

namespace ktp {

	/*
	For Abstraction and clarity typedefs have been created to encapsulate and abstract a database
	and its many components used throught the software.
	*/
	typedef unsigned int UInt;
	typedef unsigned int Point;
	typedef unsigned int Col_LEN;
	typedef std::string FString;
	typedef std::string Str_PK;
	typedef std::string TableName;
	typedef std::vector<Point> PointsContainer_VEC;
	typedef std::vector<FString> DetailsContainer_VEC;
	typedef std::vector<FString> TextFileContainer_VEC;

	using DataBaseTable = std::map<Str_PK, std::vector<FString>>;
	using DataFileCollection = std::map<TableName, DataBaseTable*>;

	

	class KTP_Algo {
	public:
	//===Static Functions===
		//A test method to check whether the DLL file has been set up properly.{prints to STD OUTPUT}
		static DLLExport void TestLibraryLinking();

		/*
			This method takes a .txt file and returns a TextFileContainer_VEC(Vector) with
			each line in the textfile as an element in the vector. DON'T USE THIS METHOD
			FOR CSV FILES!!! A database class has been created for handling CSV files
		*/
		static DLLExport TextFileContainer_VEC* LoadTextFileData(FString);

		/*
			This method takes in a string and writes out the text to the STD OUTPUT, but
			it does so in a mannor that looks like the computer is writting the string
			out live. This has the effect of someone typing something onto the screen.
		*/
		static DLLExport void AutoTypeText(FString, UInt);

		/*
			This method clears either a windows console or a linux console dynamically
		*/
		static DLLExport void ClearConsole();

		/*
			This method gets valid input from the user and places the information into
			the variable provided. STANDARD INPUT AND OUTPUT are used here. This is a 
			template function and will work with all class types assumming that the 
			'>>' and '<<' operators have been written for those classes.
		*/
		template<class E> static DLLExport void GetValidInput(E &e) {
			while (!(std::cin >> e)) {
				std::cerr << "ERROR: Incorrect input {ERR501 - Incorrect type used expected " << typeid(e).name() << "}"<< std::endl;

				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
			}
		}

		/*
			This method gets the IPv4 address of your wifi adapter to the current network
			that you are connected to at the moment.
		*/
		static DLLExport FString GetIPv4Address_WIN();

		/*
			This method shuffles a map and returns a vector of map entries (pairs!).
			This would allow the user to have access to all the entries in a map 
			which has been shuffled
		*/
		template<typename Key, typename Value>
		static DLLExport std::vector<std::pair<Key, Value>> ShuffleMap(std::map<Key,Value> _map);
	};

	/*
		The following class helps to encapsulate a basic database. CSV files are
		an ineffiecient way of store small chunks of data from a program, however
		it can be a challenge to read from and update information. This class seeks
		to encapsulate all those tasks into simple method calls that guarentee to 
		complete there goals.
	*/

	class KTP_Database {
	public:
	//===Constructor/Destructor===
		/*
			KTP_Database constructor. This constructor creates the databases core structure
			which will allow the user of this database to freely load tables of different 
			datatypes.
		*/
		DLLExport KTP_Database();

		DLLExport ~KTP_Database();

	//===Assessors===

		/*
			GetDatabaseTable. This returns a pointer to the database table with the specified
			name.
		*/
		DLLExport DataBaseTable* GetDataBaseTable(TableName);

	//===Operations===

		/*
			Loads a table into the database. Note that all the data will be stored as STRING
			datatype and is left to the user to convert were nessisary.
		*/
		DLLExport bool LoadTableInto_DB(TableName, Col_LEN, FString);

		/*
			SaveDataBaseTable. This method saves a database table to the file the file that you 
			choose.
		*/
		DLLExport bool SaveDataBaseTable(TableName, FString);

	private:
		DataFileCollection* databaseFileCollection_DB;
	};
	
	
	template<typename Key, typename Value>
	inline DLLExport std::vector<std::pair<Key, Value>> KTP_Algo::ShuffleMap(std::map<Key, Value> _map)
	{
		std::srand(time(NULL));
		std::vector<std::pair<Key, Value>> _pairs_VEC;


		for (std::map<Key, Value>::iterator each_pair = _map.begin(); each_pair != _map.end(); each_pair++) {
			_pairs_VEC.push_back(std::pair<Key, Value>(each_pair->first, each_pair->second));
		}

		std::random_shuffle(_pairs_VEC.begin(), _pairs_VEC.end());

		return _pairs_VEC;
	}
}