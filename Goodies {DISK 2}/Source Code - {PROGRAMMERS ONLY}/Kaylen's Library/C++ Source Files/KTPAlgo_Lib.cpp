#include "KTPAlgo_Lib.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace ktp {
	void ktp::KTP_Algo::TestLibraryLinking()
	{
		std::cout << "Kaylens Algo Library is set up correctly.";
	}

	DLLExport TextFileContainer_VEC * KTP_Algo::LoadTextFileData(FString textfilename)
	{
		FString data;
		std::ifstream textfile(textfilename);
		TextFileContainer_VEC* textFileDataStore = new TextFileContainer_VEC();

		if (textfile.is_open()) {
			while (std::getline(textfile,data)) {
				textFileDataStore->push_back(data);
			}
		}
		textfile.close();

		return textFileDataStore;
	}

	DLLExport void KTP_Algo::AutoTypeText(FString string, UInt milliseconds)
	{
		/*
			This method prints out a character ina string every 'm' milliseconds
		*/
		for (UInt charPos = 0; charPos < string.length(); charPos++) {
			std::cout << string[charPos];
			std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
		}
	}

	DLLExport void KTP_Algo::ClearConsole()
	{
		//Clears the windows console
		#ifdef _WIN32
		system("cls");
		#endif // _WIN32

		//Clears the linux console
		#ifdef Linux
		system("clear");
		#endif // linux
	}

	DLLExport FString KTP_Algo::GetIPv4Address_WIN()
	{
		FString IPv4_STR = "";

		//Local machines IP File
		std::ifstream IProtocolFile;
		std::ofstream OutputFile;

		//Search offset and pattern
		int searchOffset;
		char* searchPattern = "IPv4 Address. . . . . . . . . . . :";

		//Create a text file with the IP configuration {ipconfig command in cmd}
		//system("ipconfig > MyInternetConfiguration.txt");
		IProtocolFile.open("MyInternetConfiguration.txt");

		if (IProtocolFile.is_open()) {
			while (!IProtocolFile.eof()) {
				std::getline(IProtocolFile, IPv4_STR);

				/*
				Search for the pattern in the line, if the
				pattern matches then we can get the relevant
				information and erase the rest
				*/
				if (searchOffset = IPv4_STR.find(searchPattern, 0) != std::string::npos) {
					IPv4_STR.erase(0, 39);
					
					OutputFile.open("MyInternetConfiguration.txt");

					OutputFile << IPv4_STR;

					OutputFile.close();

					IProtocolFile.close();
				}
			}
		}

		TextFileContainer_VEC* IPAdd = LoadTextFileData("MyInternetConfiguration.txt");
		IPv4_STR = IPAdd->at(0);
		return IPv4_STR;
	}
	
	KTP_Database::KTP_Database()
	{
		databaseFileCollection_DB = new DataFileCollection();
	}
	
	KTP_Database::~KTP_Database()
	{
		delete databaseFileCollection_DB;
	}
	
	DLLExport DataBaseTable * KTP_Database::GetDataBaseTable(TableName tableName)
	{
		return databaseFileCollection_DB->at(tableName);
	}
	
	DLLExport bool KTP_Database::LoadTableInto_DB(TableName tableName, Col_LEN columnLength, FString CSVFileName)
	{
		// If the table name is not in the current database
		if (databaseFileCollection_DB->find(tableName) == databaseFileCollection_DB->end()) {
			
			// Read in the data from a csv file and place the DatabaseTable in the Database

			FString data;
			std::ifstream csvfiledata(CSVFileName);
			DataBaseTable* databasetable = new DataBaseTable();

			if (csvfiledata.is_open()) {

				while (std::getline(csvfiledata, data)) {

					std::istringstream rowdata(data);
					FString coldata_STR;
					Str_PK primaryKey;
					std::vector<FString> rowentrydata;

					for (int colIterator = 0; colIterator < columnLength; colIterator++) {

						std::getline(rowdata, coldata_STR, ',');
						if (colIterator == 0) {
							primaryKey = coldata_STR;
						}
						else {
							rowentrydata.push_back(coldata_STR);
						}
					}
					databasetable->insert(std::pair<Str_PK, std::vector<FString>>(primaryKey, rowentrydata));
				}
			}

			csvfiledata.close();
			databaseFileCollection_DB->insert(std::pair<TableName, DataBaseTable*>(tableName, databasetable));

			return true;
		}
		//Otherwise the table name is duplicated and the program is terminated.
		else {
			system("clr");
			std::cout << "\n\nERROR: Duplicate Table Names found! Please use unique Table Names\n\n";
			exit(1);
		}
	}
	
	DLLExport bool KTP_Database::SaveDataBaseTable(TableName tableName, FString outputCSVFileName)
	{
		/*
			NOTES ON CSV FILES:
				Due to the nature of a csv file, we are unable to undate just a single entry
				in the file without removing all the other entries as well. Therefore the following
				algorithm is used to solve this problem.

			UPDATE CSV ENTRY ALGORITHM:
				1. The first entry into the csv file opens the file and overwrites all the data
				   in the csv file and then closes the file.

		        2. The second entry into the csv file opens the file and appends itself to the
		           csv file data.

		        3. All the remaing entries (EXCEPT FOR THE VERY LAST ENTRY) just continues to
		           append themselves to the end of the csv file data. NB - Due to the nature of
		           the CSV file structure, these entries must include a 'new line' character at
		           the end.

		        4. The very last entry into the CSV file should again append itself to the end of
		           the CSV file data, however this entry does not end on a 'new line' character.
		           This allows the entry to signal the end of all the entries to the CSV file.

		        5. Finally we end by closing the file.

		    @author: Kaylen Travis Pillay
		*/


		//If the database table does exist then we can save the table to the HDD
		if (databaseFileCollection_DB->find(tableName) != databaseFileCollection_DB->end()) {

			//Setting up the output file stream
			std::ofstream outputCVSFile;
			UInt algoState = 0;
			DataBaseTable* databaseTable = databaseFileCollection_DB->at(tableName);

			//Loop through all the entries in the database table
			for (DataBaseTable::iterator eachEntry = databaseTable->begin(); eachEntry != databaseTable->end(); eachEntry++) {

				if (algoState == 0) {
					// Algorithm step 1
					
					outputCVSFile.open(outputCSVFileName);
					outputCVSFile << eachEntry->first << ",";
					
					for (int eachValue = 0; eachValue < eachEntry->second.size() - 1; eachValue++) {
						outputCVSFile << eachEntry->second[eachValue] << ",";
					}

					outputCVSFile << eachEntry->second[eachEntry->second.size() - 1] << "\n";
					outputCVSFile.close();

					//Move to the next state
					algoState++;
				}
				else if (algoState == 1) {
					//Algorithm step 2

					outputCVSFile.open(outputCSVFileName, std::ios_base::app);

					outputCVSFile << eachEntry->first << ",";

					for (int eachValue = 0; eachValue < eachEntry->second.size() - 1; eachValue++) {
						outputCVSFile << eachEntry->second[eachValue] << ",";
					}

					outputCVSFile << eachEntry->second[eachEntry->second.size() - 1] << "\n";

					//Move to the next state
					algoState++;
				}
				else if (algoState > 1 && algoState < databaseTable->size() - 1) {
					//Aglorithm step 3

					outputCVSFile << eachEntry->first << ",";

					for (int eachValue = 0; eachValue < eachEntry->second.size() - 1; eachValue++) {
						outputCVSFile << eachEntry->second[eachValue] << ",";
					}

					outputCVSFile << eachEntry->second[eachEntry->second.size() - 1] << "\n";

					//Move to the next state
					algoState++;
				}
				else {
					//Algorthim step 4

					outputCVSFile << eachEntry->first << ",";

					for (UInt eachValue = 0; eachValue < eachEntry->second.size() - 1; eachValue++) {
						outputCVSFile << eachEntry->second[eachValue] << ",";
					}

					outputCVSFile << eachEntry->second[eachEntry->second.size() - 1];
				}
			}

			//Algorithm step 5
			outputCVSFile.close();
		}
		//Otherwise the table does not exist in the current database and the program terminates
		else {
			system("clr");
			std::cout << "\n\nERROR: The DataBase table " << tableName << " does not exist! Cannot proceed.\n\n";
			exit(1);
		}
	}
}
