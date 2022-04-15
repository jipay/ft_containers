/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:00:37 by jdidier           #+#    #+#             */
/*   Updated: 2022/04/06 16:00:58 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

# include <iterator>

namespace ft
{
	template<bool Cond, class T = void>
	struct enable_if {};
	template<class T>struct enable_if<true, T> { typedef T type; };
}

#endif