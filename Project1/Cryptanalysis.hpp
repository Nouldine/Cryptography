

// Author: ABDOUL-NOUROU YIGO


#include <iostream>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iterator>
#include <typeinfo>
#include <algorithm>
#include <functional>
#include <cmath>
#include <set>

// Define a typedef to enable the comparison of a map element
typedef std::function<bool(std::pair< std::string, double >, std::pair< std::string, double > ) > Comparator;

struct Cryptanalysis
{
	// Creating a map of characters
	// that would be used to decipher the ciphertext
	std::map< char, char > character_map { {'A','N'},
                                               {'B','G'},
                                               {'C','Z'},
                                               {'D','X'},
                                               {'E','R'},
                                               {'F','V'},
                                               {'G','P'},
                                               {'H','S'},
                                               {'I','T'},
                                               {'J','F'},
                                               {'K','I'},
                                               {'L','O'},
                                               {'M','X'},
                                               {'N','Y'},
                                               {'O','H'},
                                               {'P','E'},
                                               {'Q','M'},
                                               {'R','D'},
                                               {'S','L'},
                                               {'T','B'},
                                               {'U','W'},
                                               {'V','K'},
                                               {'W','A'},
                                               {'X','X'},
                                               {'Y','C'},
                                               {'Z','U'}
        };

	// Creating a map of strings that would be use
	// to decipher the encrypted text
	std::map< std::string, std::string > two_character_map{ {"IO", "TH"},
								{"OP", "HE"},
								{"KA", "IN"}, 
								{"PE", "ER"},
								{"PR", "ED"}, 
								{"EP", "RE"},
								{"LZ", "OU"},
								{"WA", "AU"}, 
								{"WI", "AN"},
								{"IL", "TO"}	

	};

	// This function is used to get all valid strings within the text file
	// those strings would be pushed into a vector 
	// that would be used  by other function
	std::vector< std::string > frequency_two_letter( std::ifstream & );	
	
	// this function to get the successive pair of charater in string
	// those pair of characters would be stored in vector with 
	// the percentage of their appearances
	std::vector< std::pair< std::string, double >> check_frequency( std::vector< std::string > & );

	// This function is used to calculate the percentage of the 
	// appearances of all of the alphabetic letter
	void frequency_one_letter( std::ifstream & );
	
	// This function is used to decrypt a text by replacing 
	// the 2 characters with the right ones
	void decryption_with_two_letters( std::ifstream &, std::ofstream & );

	// funtion to open an input_file	
	void open_file( std::ifstream  & );
	
	// function to open an input and output files
	void input_output_file( std::ifstream &, std::ofstream & ); 
	
	// This funtion is used to decrypt a by replacing 
	// the each character accordingly 
	void decryption_with_one_letter( std::ifstream &, std::ofstream & );

	// This function is used to the two charaters string of 
	// according to their percentages	
	std::vector< std::pair< std::string, double >> get_high_rank_frequencs( std::vector< std::pair< std::string, double >> & );
	
	// function is used to return a sorted  list elements
	Comparator compare_map_second = []( std::pair< std::string, double > frequence_one, std::pair< std::string, double > frequence_two )
	{
        	return frequence_one.second > frequence_two.second;
	};



};


