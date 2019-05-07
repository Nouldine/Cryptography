// Author: Abdoul-Nourou Yigo 
//



#include "Miller_Rabin.hpp"

/* This function takes an ODD number to operate the following operations:
 * 	STEP 1: it finds the value of k and m in ( n - 1 = 2(^2) * m )
 * 	STEP 2: Generate 10 different values of a  for which to test. 
 * 		Calculate the value of b_0  = a(^m) % n
 * 	STEP 3: Try  b_0(^2) % n:
 * 		Do a search for n and n - 1 . 
 * 			if the search fails 
 * 				We know that the number is composite
 *
 * @PARAM: cpp_int odd_num that would be used to effectuate the test
 */
cpp_int Miller_Rabin::Miller_Rabin_primality_test( cpp_int n )
{
	 //std::cout << "Calling  Miller_Rabin_primarility_test() " << std::endl;
	 // Get the prime numbers that are in the range of 100 that we know that 
	 // they are clearly prime

	if( n < 100 ) 
	{
		// Added  a simple  for small primes based on known primes 
		std::vector< int > known_prime_set = { 2, 3, 5, 7, 11, 13, 17, 19, 31, 37, 41,  43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 }; 
		for( auto a : known_prime_set )
		{
			if ( a > n ) 

				return a; 
			
			if( n == a )

				return n;
		}	
	}

	cpp_int m; 
	int k = 1; 
	
	// STEP 1:
	// In this procedure, we are going 
	// to try to find k and m such that 
	// n - 1 = 2(^k) * m
	for(; k < 100; ++k )
	{
		if(( n - 1)  % (cpp_int)pow( 2, k ) == 0 )
		{
			m = ( n - 1 )  / (cpp_int)pow( 2, k );

			if( m == 1 )
				
				break;	
		}
		else
			break;
	}

	// STEP 2:
	// In this procedure, we are going to test the value of a 
	// 	if( a > 1 and  a < n - 1 ) 
	// 		proceed 
	std::mt19937 gen( ( unsigned int ) time(0) ); 

	// We are going to store the random values from a 
	// to   ( n - 1 ) in this container
	std::vector< cpp_int > get_random_values; 

	// Range  2 to ( n - 1 ) 
	std::uniform_int_distribution<> dist( 2, 100 ); 

	for( int count = 0; count < 10;  ++count )
	{
		//  the random values 
		get_random_values.push_back(dist(gen)); 
	}

	// We are going to test the random  values of a selected
	for( std::vector<cpp_int>::const_iterator iter = get_random_values.cbegin(); iter !=  get_random_values.cend(); ++iter )
	{
		cpp_int temp = 2;

		// Call the modulo calcalution function
		cpp_int b_0 = calculate_large_modulo( *iter,  m, n );
		
		//std::cout <<"b_0: " << b_0 << std::endl;

		//std::cout << "Test_1" << std::endl;
		// if b0_1 == n - 1 
		// return n
		if( b_0 == ( n - 1 ) || b_0 == 1 ) 
		{

			//std::cout << "TEST_1 " << std::endl;
			continue; // Return n

		}
		
		else 
		{
			 //std::cout << "Here " << std::endl;
			// In this procedure we are going to do multiple modulo operations 
			// if b_0  != n - 1, the number is a compisite. Otherwie, it is  prime 
			// so return n 
		
			unsigned int counter = 0; 
			cpp_int step_3;
			
			do
			{
				step_3 = (cpp_int)pow(b_0, 2) % n; 
				b_0  = step_3; 
				++counter;

			} while(  b_0 != 1 && b_0 != ( n - 1 )  &&  counter < 1000 );

			if(  b_0 == ( n - 1 )  ) 
			{	
				//std::cout << "TEST_2 " << std::endl;
				continue; // return n

			}
			else
				return -1; //  it must be composite
			   
		} // end condition
	
	
	} // end for

	// Print the values of a for which the test was done 
	
	std::cout << " Value of A Tested: : " <<  "\n"; 
	for( auto a : get_random_values )

		std::cout << a  << ",";

	std::cout << "\n";
	
	//std::cout << "n : " << n << std::endl;

	return n; 
}



/* This function takes an ODD number to operate the following operations:
 * 	STEP 1: it finds the value of k and m in ( n - 1 = 2(^2) * m )
 * 	STEP 2: Generate 10 different values of a  for which to test. 
 * 		Calculate the value of b_0  = a(^m) % n
 * 	STEP 3: Try  b_0(^2) % n:
 * 		Do a search for n and n - 1 . 
 * 			if the search fails 
 * 				We know that the number is composite
 *
 * @PARAM: cpp_int odd_num that would be used to effectuate the test
 *
 */
cpp_int  Miller_Rabin::Miller_Rabin_primality_test_2( cpp_int n )
{
	 //std::cout << "Calling  Miller_Rabin_primarility_test() " << std::endl;
	 // Get the prime numbers that are in the range of 100 that we know that 
	 // they are clearly prime

	if( n < 100 ) 
	{
		// Added  a simple  for small primes based on known primes 
		std::vector< int > known_prime_set = { 2, 3, 5, 7, 11, 13, 17, 19, 31, 37, 41,  43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 }; 
		for( auto a : known_prime_set )
		{
			if ( a > n ) 

				return a; 
			
			if( n == a )

				return n;
		}	
	}

	cpp_int m; 
	int k = 1; 
	
	// STEP 1:
	// In this procedure, we are going 
	// to try to find k and m such that 
	// n - 1 = 2(^k) * m
	for(; k < 100; ++k )
	{
		if(( n - 1)  % (cpp_int)pow( 2, k ) == 0 )
		{
			m = ( n - 1 )  / (cpp_int)pow( 2, k );

			if( m == 1 )
				
				break;	
		}
		else
			break;
	}

	// STEP 2:
	// In this procedure, we are going to test the value of a 
	// 	if( a > 1 and  a < n - 1 ) 
	// 		proceed 
	std::mt19937 gen( ( unsigned int ) time(0) ); 

	// We are going to store the random values from a 
	// to   ( n - 1 ) in this container
	std::vector< cpp_int > get_random_values; 

	// Range  2 to ( n - 1 ) 
	std::uniform_int_distribution<> dist( 2, 100 ); 

	for( int count = 0; count < 10;  ++count )
		//  the random values 
		get_random_values.push_back(dist(gen)); 

	// We are going to test the random  values of a selected
	for( std::vector<cpp_int>::const_iterator iter = get_random_values.cbegin(); iter !=  get_random_values.cend(); ++iter )
	{
		cpp_int temp = 2, test1 = 1;
		// Call the modulo calcalution function
		cpp_int b_0 = calculate_large_modulo( *iter,  m, n );
		
		//std::cout <<"b_0: " << b_0 << std::endl;

		//std::cout << "Test_1" << std::endl;
		// if b0_1 == n - 1 
		// return n
		if( /*b_0 == ( n - 1 ) || */ b_0 == 1 ) 
		{
			//std::cout << "TEST_1 " << std::endl;
			continue; // Return n

		}
		
		else 
		{
			 //std::cout << "Here " << std::endl;
			// In this procedure we are going to do multiple modulo operations 
			// if b_0  != n - 1, the number is a compisite. Otherwie, it is  prime 
			// so return n 
			unsigned int counter = 0; 
			cpp_int step_3;
			
			do
			{
				step_3 = (cpp_int)pow(b_0, 2) % n; 
				b_0  = step_3; 
				++counter;

			} while(  b_0 != 1 /*&& b_0 != ( n - 1 ) */  &&  counter < 1000 );

			if( b_0 == 1 /*( n - 1 ) */ ) 
			{	
				//std::cout << "TEST_2 " << std::endl;
				continue; // return n

			}
			else
				return -1; //  it must be composite
			   
		} // end condition
	
	
	} // end for

	// Print the values of a for which the test was done 
	
	std::cout << " Value of A Tested: : " <<  "\n"; 
	for( auto a : get_random_values )

		std::cout << a  << ",";

	std::cout << "\n";
	
	//std::cout << "n : " << n << std::endl;
	return n; 
}

/* This function is a driver to generate large prime number according to the user input 
 * @Param: unsigned num_primes 
 * @Param: unsigned min_size 
 * @Param: unsigned max_size 
 *
 */ 
cpp_int Miller_Rabin::primes_generation( unsigned min_size, unsigned  max_size )
{
	// Use the boost library to generate 
	// a set of random numbers
        std::mt19937  gen(( unsigned int) time(0));
        std::uniform_int_distribution<> dist(min_size, max_size);

        // use stringstream to concatenate long 
	// integers value 
        std::stringstream ss;
	int num_primes = 1; 	
	cpp_int temp;

        for( int i = 0; i < num_primes; ++i )
        {
                ss.clear();

                // Get random size of prime from  50-maxSize digits 
                int primeLengthInDigits = dist(gen);
                
		// Reset distributionn for string generator  
                std::uniform_int_distribution<> dist( 0, 9 );

                for( int j = 0; j < primeLengthInDigits; ++j )
                {
                        ss << dist(gen);

                }
                 
		cpp_int concatenateValue;
                ss >> concatenateValue;

                if( concatenateValue % 2 == 0 )
			
			concatenateValue++; // Get the nearest prime based on the random number  //  Returns -1 if not prime 

                //std::cout <<"ConcatenateValue: " << concatenateValue << std::endl;
                temp  = Miller_Rabin_primality_test(concatenateValue);
                 
		while( temp < 0 )
                {
			concatenateValue += 2; // Try the next odd number to see of it's prime =
                        temp = Miller_Rabin_primality_test(concatenateValue);
                }

        }
	
	return temp;
}



/* This function is recursive function that used to performe the modulo activity for very large number. 
 * The recursive procedures would be done in three steps. The first step is the base case. 
 * The second and third steps  are used to decompose the large prime number in small portions 
 * that could be handle efficiently by the algorithm. 
 * The function would call itself recursively to perform those the calculation with a very 
 * acceptable time complexity.
 * 
 * @Param1: cpp_int a  
 * @Param2: cpp_int m 
 * @Param3: cpp_int n 
 *
 */
cpp_int Miller_Rabin::calculate_large_modulo( cpp_int a, cpp_int m, cpp_int n )
{
	 //std::cout <<"Calling calculate_large_modulo() " << std::endl; 
	 
	cpp_int b_0; 
	 // Use recursive steps 
	 // Base case: if the exponent is 1 
	 // return a
	 if(  m == 1 )
		 return ( a % n ); 

	 else //  The primality  would need two condition 
	 {
		 // Verify if m is prime 
		 // The first recursive step is used  
		 // to spit m in case if it is still a large number
		 // So if the exponent is divisible ( m - 1 ) / 2 
		 // continue doing until  the condition  is false 
		 if( m  % 2 == 1 )
		 {
			 b_0 = calculate_large_modulo( a,  ( m - 1 ) / 2,  n ); 
			 
			 return  (  a * b_0 * b_0 ) % n;  
		 }
		 else
		 {
			 b_0 = calculate_large_modulo( a, m / 2, n ); 
			 
			 return ( b_0 * b_0 ) % n;
		 }
		
	 }

}

/* This function is used to get the user input 
 * @Param1: int min_size
 * @Param2: int max_size
 *
 */
std::vector< int >  Miller_Rabin::get_user_input( int min_size,  int max_size ) 
{
	std::cout << "Calling get_user_input() " << std::endl; 

	std::vector< int > input_vec; 

	std::cout << " Please Enter  the mininmum range of random numbers: "  << std::endl; 

	std::cin >>  min_size; 
	
	input_vec.push_back( min_size ); 	
	 
	std::cout << "Please Enter the maximum range of random numbers: " << std::endl; 

	std::cin >> max_size;

	input_vec.push_back( max_size );
	
	return   input_vec;

}	

