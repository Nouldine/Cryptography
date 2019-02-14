
// Auther: ABDOUL-NOUROU YIGO

#include "Cryptanalysis.hpp"


int main()
{
	// create a Cryptanalysis object 
	Cryptanalysis C;
	
	// Create variable to open and close 
	// files
	std::ifstream file_content;
	std::ifstream file_content2;

	// Call to open file 
	// to open an input file that would be used
	// to execute some operations
	C.open_file( file_content );

	// Create ressources for 
	// input and output files 
	std::ifstream input_file;
	std::ofstream output_file;

	// Call this function to read and write
	// from a file to a file
	C.input_output_file( input_file, output_file );
		
	return 0;
}

/* This function is used to open an input file  
 * that  will be used by different others
 * with the system 
 * @param: file_input that is the input file
 */

void Cryptanalysis::open_file( std::ifstream & file_content  )
{
	//  Create variable for 
	//  input file
	std::ifstream  file_content_2;
	
	// Open input file
	file_content.open( "CS762Abdoul.txt", std::ios_base::in );
	file_content_2.open("CS762Abdoul.txt", std::ios_base::in );

	// Create a set of variable that would be used  by 
	// the appropriate  functions
	std::vector< std::string > string_vec;
	std::vector< std::pair< std::string, double >> vector_of_sorted_frequences; 
	std::vector< std::pair< std::string, double >> vector_of_sorted_freq;

	// proceed if the file is openned
	if( file_content.is_open() &&  file_content_2.is_open() ) 
	{
		frequency_one_letter( file_content );
		string_vec = frequency_two_letter( file_content_2 );
		vector_of_sorted_frequences = check_frequency( string_vec );
		vector_of_sorted_freq = get_high_rank_frequencs( vector_of_sorted_frequences );
	}

	// Close file when the operations
	// are done
	file_content.close();
	
} // end function

/*
 * This function is used  to open an input and output file
 * @param1: input_file is used to get the input file
 * @param2: ouput_file is used to get the output file
 *
 */
void Cryptanalysis::input_output_file( std::ifstream & input_file, std::ofstream & output_file )
{
	// open ouput and input file
	input_file.open("CS762Abdoul.txt", std::ios_base::in );
	output_file.open("output_file2.txt", std::ios_base::out );

	// Proceed if the files are openned
	if( input_file.is_open() && output_file.is_open() ) {

		 decryption_with_one_letter( input_file,  output_file );
		 //decryption_with_two_letters( input_file, output_file );


	 }

	
	// Create another set of input and ouput 
	// files to make some tests
	std::ifstream second_input_file;
	std::ofstream new_out_put_file;
	
       	// passing the decrypted output file from one letter decryption function 
	// To the two letters decryption function
	second_input_file.open("output_file2.txt", std::ios_base::in );
	
	// Open a new file
	new_out_put_file.open("output_file3.txt", std::ios_base::out ); 
	
	// Actual passing
	decryption_with_two_letters( second_input_file, new_out_put_file );
	 
	// close the file at the end of 
	// the operations
	input_file.close();
	output_file.close();
		  
} // end function

/*
 * This function is used to the percentages of  each  alphabetic 
 * letter in  the input text file\
 * @param: file_content is the input file ( cipher text )
 *
 */
void Cryptanalysis::frequency_one_letter( std::ifstream & file_content ) 
{
	std::cout <<"*********************************** ONE LETTER FREQUENCIES ************************************" << std::endl;
	// Create a vector of all the characters
	std::vector<double> frequency_vector(128);
	
	// create char variable 
	char character;
	
	// create a variable to count all the
	// character within the text file
	int character_counter = 0;

	//  the size of the vector
	int vector_size = frequency_vector.size();

	// Assign zero to vector content
	for( int i = 0;  i < vector_size; ++i )

		frequency_vector[ i ]  = 0;

	// get the first character in the
	// text file
	character = file_content.get();

	//  Loop to get all the characters 
	//  in the text file
        while( character != EOF )
        {
		// increment counter for each character in the text file
                frequency_vector[ character ]++;

		// Make sure that the characters that are counted
		// are alphabetic symbol
                if( character >= 'A' && character <= 'Z' )

			// This counter is counting all of the alphabetic 
			// characters in the text file. It would be used 
			// to determined the percentages for each character 
                        ++character_counter;

		// make sure that we can get each character
                character = file_content.get();
        } // end while

        std::cout << std::endl << "The letters frequency from the cipher text: " << std::endl;
	// Loop to calculate the percentages of each charater each using their 
	// counter
        for( auto character_in_file = 'A'; character_in_file <= 'Z'; ++character_in_file )
        {
		// calculate the percentages
                double percentage = (  frequency_vector[ character_in_file ] * 100 ) / character_counter;
                std::cout << character_in_file << " : " << std::setprecision(3) << std::fixed << percentage << "%" << std::endl;

        } // end for

} // end function

/*
 * This function is used to get all of the valid strings within the text file
 * it would return a vector of strings that would be used by function 
 * @param1: file_content( input file )
 *
 */
std::vector< std::string > Cryptanalysis::frequency_two_letter( std::ifstream & file_content )
{

	std::cout <<"*********************************** TWO LETTER FREQUENCIES ************************************" << std::endl;

	// variable to the string in the text file
	std::string line;
        int count_string = 0;

        std::vector< std::string > vec_string{};
        std::map< std::string, int > map_two_characters;
        std::map< std::string, int >::iterator string_count;
	std::map< std::pair<char, char>, int > char_pair; 
	std::vector< std::string > words;

	// Loop to get all of the string in the 
	// text file
        while( std::getline( file_content, line ) )
        {
		//  Use this loop to get red of non-alphabetic characters 
                for( int itr = 0, itr2 =  0; itr < line.length(); ++itr ) {

                        char & cha = line[ itr ];

			// If the character is alphetic  proceed and store 
			// the string in vector
                        if( cha < 'A' || ( cha > 'Z' && cha < 'a') || cha > 'z' ) 
			{
                                std::string word = line.substr( itr2, itr - itr2 );
                                itr2 = itr + 1;

				// Make sure that the string length 
				// superior or equal to 2 because 
				// We dont consider one character at this stage
                                if( word.length() >= 2 ) 
                                        
					words.push_back(word);
                        } // end if

                } // end for
        
	} // end while 

	return words; 

} // end function


/* This function is used to got the top 10 two letters frequency within the text file
 * It returns a vector of pair of string ( string of size 2 and double that is the frequency related to that strings
 * @param:  stored_list a vector of pair of strings and their frequencies.
 *
 */
std::vector< std::pair< std::string, double >> Cryptanalysis::get_high_rank_frequencs( std::vector< std::pair<  std::string, double >> & sorted_list )
{

	//  Define a vector to store the strings and their frequencies
	std::vector< std::pair< std::string, double >> frequency_list;

	//  loop to get the top frequencies 
	//  the container is previously sorted
	for( int i = 0;  i < 10; ++i )
		
		frequency_list.push_back( sorted_list[ i ] ); 

	std::cout <<"Selected List" << std::endl;
	for( auto & content :  frequency_list )

		// print the vector content. Since it is a pair of elements 
		// content.first refers to the first element of the pair 
		// content.second refers to the second element of the pair
		std::cout << content.first << " : " << content.second << "%" << std::endl;

	// return the sorted list
	return frequency_list;

} // end function

/*
 * This function is used to get consecutive sequences of two letter within a string. it is the
 * most curcial  function that could allow the determination of the  two letter
 * frequencies in any text file. After getting the two letters frequencies, it would calculate 
 * the percentages of their appearances. It would returns a vector containing those information
 * 
 * @param: words  that is a vector of strings
 *
 */
std::vector< std::pair< std::string, double >>  Cryptanalysis::check_frequency( std::vector< std::string >  & words ) {


	// Defining the appropriate variables to structure and to manupulate 
	// the  data
	std::vector< std::string > vec_string{};

        std::map< std::string, int > map_two_characters;
        std::map< std::string, int >::iterator string_count;
        std::map< std::pair<char, char>, int > char_pair;
	std::map< std::string, double >  map_of_frequences;
	std::vector< std::pair< std::string, double >> vector_of_sorted_frequences;
	
	// Create a counter of each string( two letters )
	int count_string = 0;

	// get the size of the vector 
	// of strings
	int vec_size = words.size();

	// loop  to get each string in the string vector
	for( int it = 0; it < vec_size; ++it )
        {
		// get each the string at index it
                std::string word_in_index = words[ it ];

		// for each string make pair of the successive characters
		// making sure that we move the index  appropriatly 
		// to get all the characters in the right order
		// to get accurate concatenations
                for(  int i = 0;  i < word_in_index.length() - 1; ++i )
                {
			// Since it is a map the pair of character  would be  used as a key and 
			// the counters of these as value. The counter will be incremented
			// each time the same pair of character is seen. 
			// At the end of the iterations. We would  have a map of all two letters 
			// and their appearance
                        char_pair[ std::make_pair( word_in_index[ i ],  word_in_index[ i + 1 ] ) ]++;
                        
			// Counting all of these strings
			++count_string;
                
		} // end for

        } // end for

	// With the information we got above. The percentages  
	// can be calculated by looping  through the map
        for( auto it = char_pair.begin(); it != char_pair.end(); ++it )
        {
		// calculate the percentages of each pair of character
                double multiplication = it->second * 100;
                double percentage =  multiplication / count_string;

		// Since the characters are stored as pair
		// used the sstream library facility to stringed 
		// those pair of characters together
		std::stringstream ss;

		// Get the first element in the map and then get 
		// the first and second elements of that element 	
		ss << it->first.first  << it->first.second; 

		// stringed the elements together
		std::string str_form = ss.str();

		//  Insert the strings into another map with their appearance percentages
		map_of_frequences.insert( std::pair< std::string, double >( str_form,  percentage ) );

	} // end for

	// Create a set of pair ( string and double )  that would be sorted 
	// using the comparator funtionality we have defined
	// copy the map contents( strings: double = ) to be sorted  
	std::set< std::pair< std::string, double >, Comparator> set_of_sorted_frequences(  
			
			map_of_frequences.begin(), map_of_frequences.end(), compare_map_second ); 

	// When the sorting is  done, we can push those frequences into 
	// a vector for other uses
	for( std::pair< std::string, double > set_content : set_of_sorted_frequences )
	{
		vector_of_sorted_frequences.push_back( set_content ); 
		std::cout << set_content.first << ":" << set_content.second << "%" << std::endl;
		

	} // end for



        std::cout <<"Count two Strings: " << count_string << std::endl;

	// Return a sorted list of elements 
	return vector_of_sorted_frequences;

} // end function

/*
 * This function is another import function to decrypt the cipher text. It does so by mapping the exchanging
 * the encrypted character to the decrypted character. the logic is that  we store each 
 * character( in alphabetic order ) as key and thev value would be the decrypted characters. For each character 
 * found in the ciphertext find its location in the map is replace that character by value. 
 * Write the character value to the output file. 
 *
 * @param1: input_file to read the ciphertext 
 * @param2: output_file to write the decrypt content
 *
 */
void Cryptanalysis::decryption_with_one_letter( std::ifstream & input_file, std::ofstream & output_file )
{
	std::string line_in_file;
	
	// Create a map iterator that would be 
	// used the character in key set
	std::map< char, char >::iterator char_count; 
	
	// Loop through all the strings in the file
	while( std::getline( input_file, line_in_file ) )
	{
		// for each string each character 
		for( int i = 0; i < line_in_file.size(); ++i )
		{
			char character = line_in_file[ i ];
			
			// Find the character in the key set 
			// in the map
			char_count =  character_map.find(character);
		
			// if the character is found replace 
			// by its value 
			if( char_count != character_map.end() )
				
				character = char_count->second;

			// Write the character in a map 
			output_file << character;
		
		} // end for loop
	} // end while loop 

} // end function


/* 
 * This function is one of important function to decrypt a ciphertext by using the two letter exchanges approach.
 * a map is created with the top strings ( two letters ) use as key and the value are their corresponding decryption string 
 * It loops through the ciphertext to find patterns. when the partern matches with the correspinding key. The key would replace 
 * by its value in the decrypted text. 
 *
 * @param1: input_file for the ciphertext
 * @param2: out_file to write the decrytion
 * 
 */
void Cryptanalysis::decryption_with_two_letters( std::ifstream & input_file, std::ofstream & output_file )
{
	// Define a string
	std::string string_in_file;

	// Loop to get all the strings
	while( std::getline( input_file, string_in_file ) )
	{
		//   try the string in the map 
		for(  auto it = two_character_map.begin(); it != two_character_map.end(); ++it )
		{
			// this most important part because it would check to try to find the appropriate pattern checkeing each position 
			// When the string matches with the key in the map. output the in the output file. Otherwise do nothing
			for( size_t position = string_in_file.find( it->first ); position != std::string::npos; position = string_in_file.find( it->first, position ) )

				// Replace thes string structure at the right position
				string_in_file.replace( position, ( it->first ).length(), it->second );
			 
		} // end for
		
		// Write the strings in the outputfile
		output_file << string_in_file;
	} // end while
	
} // end function


