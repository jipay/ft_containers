/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:28:54 by jdidier           #+#    #+#             */
/*   Updated: 2022/04/14 14:53:35 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// is_integral example
#include <iostream>
#include <vector>
#include "vector.hpp"

int main() {
	std::cout << "Vector tests:\n" << std::endl;

	
	std::cout << "std::vector<int>	first;" << std::endl;
	std::vector<int>	first;
	std::cout << "size: " << first.size() << " capacity: " << first.capacity() << " max size: " << first.max_size() << std::endl;
	std::cout << "std::vector<int>	second (4, 100);" << std::endl;
	std::vector<int>	second (4, 100);
	std::cout << "size: " << second.size() << " capacity: " << second.capacity() << " max size: " << second.max_size() << std::endl;
	std::cout << "std::vector<int>	third (second.begin(), second.end());" << std::endl;
	std::vector<int>	third (second.begin(), second.end());
	std::cout << "size: " << third.size() << " capacity: " << third.capacity() << " max size: " << third.max_size() << std::endl;
	std::cout << "std::vector<int>	fourth (third);" << std::endl;
	std::vector<int>	fourth (third);
	std::cout << "size: " << fourth.size() << " capacity: " << fourth.capacity() << " max size: " << fourth.max_size() << std::endl;
	std::cout << std::endl;
	std::cout << "first.insert(first.begin(), 42);" << std::endl;
	first.insert(first.begin(), 42);
	std::cout << "size: " << first.size() << " capacity: " << first.capacity() << " max size: " << first.max_size() << std::endl;
	std::cout << "first.insert(first.begin(), 42);" << std::endl;
	first.insert(first.begin(), 42);
	std::cout << "size: " << first.size() << " capacity: " << first.capacity() << " max size: " << first.max_size() << std::endl;
	std::cout << "first.insert(first.begin(), 42);" << std::endl;
	first.insert(first.begin(), 42);
	std::cout << "size: " << first.size() << " capacity: " << first.capacity() << " max size: " << first.max_size() << std::endl;
	std::cout << "second.insert(second.begin(), first.begin(), first.end());" << std::endl;
	second.insert(second.begin(), first.begin(), first.end());
	std::cout << "first.end() - first.begin()" << std::endl;
	std::cout << first.end() - first.begin() << std::endl;
	std::cout << "size: " << second.size() << " capacity: " << second.capacity() << " max size: " << second.max_size() << std::endl;
	std::cout << "third.push_back(42);" << std::endl;
	third.push_back(42);
	std::cout << "size: " << third.size() << " capacity: " << third.capacity() << " max size: " << third.max_size() << std::endl;
	std::cout << "third.push_back(42);" << std::endl;
	third.push_back(42);
	std::cout << "size: " << third.size() << " capacity: " << third.capacity() << " max size: " << third.max_size() << std::endl;
	std::cout << "third.push_back(42);" << std::endl;
	third.push_back(42);
	std::cout << "size: " << third.size() << " capacity: " << third.capacity() << " max size: " << third.max_size() << std::endl;
	std::cout << "third.push_back(42);" << std::endl;
	third.push_back(42);
	std::cout << "size: " << third.size() << " capacity: " << third.capacity() << " max size: " << third.max_size() << std::endl;
	std::cout << "third.push_back(42);" << std::endl;
	third.push_back(42);
	std::cout << "size: " << third.size() << " capacity: " << third.capacity() << " max size: " << third.max_size() << std::endl;
	

	/*
	ft::vector<int> test1;
	std::cout << "size: " << test1.size() << " capacity: " << test1.capacity() << " max size: " << test1.max_size() << std::endl;
	ft::vector<int> test2 (4, 42);
	std::cout << "size: " << test2.size() << " capacity: " << test2.capacity() << " max size: " << test2.max_size() << std::endl;
	ft::vector<int> test3(test2.begin(), test2.end());
	std::cout << "size: " << test3.size() << " capacity: " << test3.capacity() << " max size: " << test3.max_size() << std::endl;
	test2.erase(test2.begin());
	std::cout << "size: " << test2.size() << " capacity: " << test2.capacity() << " max size: " << test2.max_size() << std::endl;
	*/
	return 0;
}
