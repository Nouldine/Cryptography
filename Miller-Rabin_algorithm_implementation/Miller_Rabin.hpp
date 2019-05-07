// Author: Abdoul-Nourou Yigo
//


#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <sstream> 
#include <vector>
#include <iostream>

using namespace boost::multiprecision; 
using namespace boost::random; 

struct Miller_Rabin 
{
	// Create functions prototypes 
	cpp_int Miller_Rabin_primality_test( cpp_int );
       	cpp_int Miller_Rabin_primality_test_2( cpp_int );	
	cpp_int primes_generation( unsigned int = 50, unsigned int  = 60); 
	cpp_int calculate_large_modulo( cpp_int, cpp_int, cpp_int ); 
	std::vector< int >  get_user_input( int, int ); 
};
