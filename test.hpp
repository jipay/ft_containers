/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:50:01 by jdidier           #+#    #+#             */
/*   Updated: 2022/04/26 16:38:14 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
# define TEST_HPP

# include <iostream>
# include "vector.hpp"

template <class T>
void	print_vector(ft::vector<T> & vec) {
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "capacity: " << vec.capacity() << std::endl;
	std::cout << "max_size: " << vec.max_size() << std::endl;
	std::cout << "Content:" << std::endl;
	typename ft::vector<T>::const_iterator it = vec.begin();
	typename ft::vector<T>::const_iterator ite = vec.end();
	for (; it < ite; it++) {
		std::cout << *it << std::endl;
	}
	std::cout << "--------------------------------------------" << std::endl;
}

#endif