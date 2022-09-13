//
// Created by it on 7/8/22.
//

#include <gtest/gtest.h>
#include <algorithm>
#include <chrono>
#include <ranges>
#include <numeric>

/*
 * Having a collection of students we want to find a student with the maximum rate for given year.
 * It can be implemented in at least 3 ways:
 * - using standard algorithms
 * - using one for loop
 * - using ranges and views
 */
struct Student
{
	std::string name;
	int year;
	int score;
};

TEST( Ranges, FindingMaxScoreForLoopApproach )
{
	std::vector<Student> students;
	for ( int i = 0 ; i < 1000000 ; ++i )
	{
		std::string name = "Student" + std::to_string( i );
		int year = 1980 + i % 5;
		int score = i % 400;
		students.emplace_back( Student{ name, year, score } );
	}

	auto yearToFind = 1982;

	auto start = std::chrono::system_clock::now();
	int maxScore = 0;
	for ( const auto& student : students )
	{
		if ( student.year == yearToFind )
		{
			maxScore = std::max( student.score, maxScore );
		}
	}
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "Max score: " << maxScore << " in: " << elapsed_seconds.count() << "s" << std::endl;
}

TEST( Ranges, FindingMaxScoreViews )
{
	std::vector<Student> students;
	for ( int i = 0 ; i < 1000000 ; ++i )
	{
		std::string name = "Student" + std::to_string( i );
		int year = 1980 + i % 5;
		int score = i % 400;
		students.emplace_back( Student{ name, year, score } );
	}

	auto yearToFind = 1982;

	const auto byYear = [yearToFind]( auto&& a_student )
	{
		return a_student.year == yearToFind;
	};

	auto start = std::chrono::system_clock::now();

	auto scores = students | std::views::filter( byYear ) | std::views::transform( &Student::score );
	auto maxScore = std::ranges::max_element( scores );

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "Max score: " << *maxScore << " in: " << elapsed_seconds.count() << "s" << std::endl;
}

/*
 * Views use proxy object and lazy evaluation. That means we evaluate expression when is needed
 *
 * LazyEvaluationTransform - transform from views does not square. Only we access object square is calculated
 * StandardTransform - do square when transform is called
 *
 * Pipe is working, because each view has adapter, that has pipe operator implemented and also
 * input containers can be converted to that adapters
 */
TEST( Ranges, LazyEvaluationTransform )
{
	std::vector<int> numbers( 100000 );
	std::iota( numbers.begin(), numbers.end(), 1 );

	const auto square = []( auto&& a_value )
	{
		return a_value * a_value;
	};

	auto start = std::chrono::system_clock::now();
	std::views::transform( numbers, square );
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "No calculation until we need data: " << elapsed_seconds.count() << "s" << std::endl;
}

TEST( Ranges, StandardTransform )
{
	std::vector<int> numbers( 100000 );
	std::vector<int> out( 100000 );
	std::iota( numbers.begin(), numbers.end(), 1 );

	const auto square = []( auto&& a_value )
	{
		return a_value * a_value;
	};

	auto start = std::chrono::system_clock::now();
	std::transform( numbers.begin(), numbers.end(), out.begin(), square );
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "No calculation until we need data: " << elapsed_seconds.count() << "s" << std::endl;
}