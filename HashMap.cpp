#ifdef HASHMAP_UNIT_TEST
#include "HashMap.h"
#include <iostream>

using namespace tiger_cat;

int main(int argc, char* argv[])
{
	auto hash_map = HashMap<std::string, int>(
		50,
		[](const std::string& str) -> unsigned int{
			unsigned int sum = 0;
			unsigned int count = 1;
			for(const auto c : str){
				sum += static_cast<unsigned int>(c*count);
				count*=2;
			}
			return sum;
		});

	hash_map.Insert("hello", 1);
	std::cout << hash_map << std::endl;
	//hash_map.Insert("mornin", 2);
	std::cout << hash_map << std::endl;
	hash_map.Insert("helol", 3);
	hash_map.Insert("hleol", 4);
	hash_map.Insert("ehlol", 5);
	std::cout << hash_map << std::endl;
	std::cout << "hello" << hash_map.Find("hello")->GetValue() << std::endl;
	std::cout << "helol" << hash_map.Find("helol")->GetValue() << std::endl;
	std::cout << "hleol" << hash_map.Find("hleol")->GetValue() << std::endl;
	if(!hash_map.Find("hello")){
		std::cout << "???no such key" << std::endl;
	}
	if(!hash_map.Find("ornin")){
		std::cout << "no such key" << std::endl;
	}
	//std::cout << hash_map.Find("ornin")->GetValue() << std::endl;
	try {
		//std::cout << hash_map["mornin"] << std::endl;
	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
	}	
	//std::cout << hash_map["helol"] << std::endl;
    return 0;
}

#endif
