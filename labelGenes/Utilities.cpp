#include "stdafx.h"
#include "Utilities.h"
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>

::std::vector<::std::string> ReadLinesFromFile(const ::std::string& pathToFile)
{
	::std::vector< ::std::string> linesVector;

	::std::ifstream inputFile(pathToFile.c_str());
	
	::std::string tempLine;
	while(::std::getline(inputFile, tempLine))
		linesVector.push_back(tempLine);

	return linesVector;
}


::std::vector< double> DoubleVectorFromString(const ::std::string& inputString)
{
	::std::istringstream ss(inputString);

	::std::vector<double> result;
	while(!ss.eof())
	{
		double tmp;
		ss >> tmp;
		result.push_back(tmp);
	}

	return result;
}

::std::vector< double> DoubleVectorFromString(const ::std::string& inputString, char delim)
{
	::std::vector<::std::string> strs = splitString(inputString, delim);
	
	::std::vector<double> result;

	for (int i = 0; i < strs.size(); ++i)
		result.push_back(atof(strs[i].c_str()));

	return result;
}

std::vector<std::string> splitString(const std::string &s, char delim) 
{
    std::vector<std::string> elems;
    splitString(s, delim, std::back_inserter(elems));
    return elems;
}

::std::vector<::std::string> splitString(const ::std::string& inputStr)
{
	::std::istringstream ss(inputStr);

	::std::vector<::std::string> result;
	while(!ss.eof())
	{
		::std::string tmp;
		ss >> tmp;
		result.push_back(tmp);
	}
	//result.pop_back(); // HACKY
	return result;
}

double Norm2(const ::std::vector< double>& doubleVector)
{
	double tmp = 0;

	for (::std::vector<double>::const_iterator it = doubleVector.begin(); it != doubleVector.end(); ++ it)
		tmp += ::std::pow(*it, 2);

	return ::std::sqrt(tmp);
}


double NormSquared(const ::std::vector<double>& input)
{
	double sum = 0;
	for(::std::vector<double>::const_iterator it = input.begin(); it != input.end(); ++it)
		sum += ::std::pow(*it, 2);

	return sum;
}

::std::string GetDateString()
{
  time_t rawtime;
  struct tm * timeinfo;

  char buffer [80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime (buffer,80,"%Y-%m-%d-%H-%M-%S", timeinfo);

  return ::std::string(buffer);
}


void PrintCArray(const double* toPrint, size_t size, ::std::ostream& os)
{
	for (size_t i = 0; i < size; ++i)
		os << toPrint[i] << " ";

	os << ::std::endl;

}


double angularDistanceMinusPItoPI(const double angle1, const double angle2)
{
	return ::std::atan2(::std::sin(angle1 - angle2), ::std::cos(angle1 - angle2));	
}

bool is_not_digit(char c)
{
    return !std::isdigit(c);
}


