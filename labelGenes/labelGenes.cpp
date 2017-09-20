// labelGenes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <map>
#include <locale>
#include <codecvt>

#include "Utilities.h"

#ifndef UNICODE  
  typedef std::string String; 
#else
  typedef std::wstring String; 
#endif

void createLibrary(const ::std::string& libraryFile, ::std::map<::std::string, ::std::string>& libraryMap);

int _tmain(int argc, _TCHAR* argv[])
{

	//if (argc < 3)
	//{
	//	::std::cout << "Not enough input arguments!!" <<::std::endl;
	//	::std::cout << "Please use this command with the following input arguments:" << ::std::endl;
	//	::std::cout << "labelGenes.exe inputfile.txt libraryfile.txt" << ::std::endl;
	//	return 1;
	//}

	//::std::wcout << "input file used: " << String(argv[1]).c_str() << ::std::endl;
	//::std::wcout << "library used: " << String(argv[2]).c_str() << ::std::endl;

	//::std::string input_str = "ST24-Lib-B-SLO-R4_UniqueSeq";
	::std::string input_str = "ST23-Lib-B-R0_UniqueSeq";
	
	::std::string library_str = "Human_GeCKOv2_Library_B.txt";
	// setup converter
	//using convert_type = std::codecvt_utf8<wchar_t>;
	//std::wstring_convert<convert_type, wchar_t> converter;
	//	
	//std::string input_str = converter.to_bytes(String(argv[1]).c_str());
	//std::string library_str = converter.to_bytes(String(argv[2]).c_str());
	std::string output_str = input_str + "_result.txt";

	// parse the gene library
	::std::map<::std::string, ::std::string> libraryMap;
	createLibrary(library_str, libraryMap);

	// create the output file
	::std::ofstream	os(output_str);

	// load data to annotate
	::std::vector<::std::string> lines = ReadLinesFromFile(input_str+".txt");

	// annotate line by line and append the data in parallel into the output file
	::std::string sequence;
	::std::vector<::std::string>::const_iterator it = lines.begin();
	int counter = 0;
	for (it; it != lines.end(); ++it)
	{
		sequence = splitString(*it).front();
		os << *it << "\t" << libraryMap[sequence] << ::std::endl;
		counter++;
	}

	os.close();

	::std::cout << "Finished labelling " << counter << " gene sequences" << ::std::endl;
	::std::cout << "The annotated file is stored as: " << output_str.c_str() << ::std::endl;

	return 0;
}

void createLibrary(const ::std::string& libraryFile, ::std::map<::std::string, ::std::string>& libraryMap)
{
	::std::cout << "Building index..." << ::std::endl;
	::std::vector<::std::string> data = ReadLinesFromFile(libraryFile);
	
	::std::vector<::std::string> dataBuffer;

	::std::vector<::std::string>::const_iterator it = data.begin();
	for (it ; it != data.end(); ++it)
	{
		dataBuffer = splitString(*it);
		libraryMap[dataBuffer[2]] = dataBuffer[0];
	}

	::std::cout << "Index built! " << ::std::endl;
}