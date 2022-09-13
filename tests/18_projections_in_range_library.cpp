//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>

/*
Projections decrease the need for writing custom comparison operator
*/

struct Person
{
	int age;
	int weight;
	int height;
	int id;
};

TEST( Projections, Find )
{
	std::vector<Person> persons = {
	Person{ 12, 43, 43, 0 }
	, Person{ 13, 20, 15, 2 }
	, Person{ 21, 123, 165, 3 }
	, Person{ 21, 100, 198, 4 }
	, Person{ 67, 65, 184, 1 }
	, Person{ 2, 5, 123, 10 }
	};

	// Find a person that is 20 kg weight
	auto person = std::ranges::find( persons, 20, &Person::weight );

	std::cout << "Found person: " << std::endl;
	std::cout << "age: " << person->age << std::endl;
	std::cout << "weight: " << person->weight << std::endl;
	std::cout << "height: " << person->height << std::endl;
	std::cout << "id: " << person->id << std::endl;
}

TEST( Projections, Sort )
{
	std::vector<Person> persons = {
			Person{ 12, 43, 43, 0 }
			, Person{ 13, 20, 15, 2 }
			, Person{ 21, 123, 165, 3 }
			, Person{ 21, 100, 198, 4 }
			, Person{ 67, 65, 184, 1 }
			, Person{ 2, 5, 123, 10 }
	};

	// Sort persons by age, then by weight
	auto sort_criteria = []( const Person& a_person )
	{
		// creates a tuple with references
		return std::tie( a_person.age, a_person.weight );
	};
	std::ranges::sort( persons, std::less<>{}, sort_criteria );

	for ( const auto& person : persons )
	{
		std::cout << "--------------" << std::endl;
		std::cout << "age: " << person.age << std::endl;
		std::cout << "weight: " << person.weight << std::endl;
		std::cout << "height: " << person.height << std::endl;
		std::cout << "id: " << person.id << std::endl;
	}
}