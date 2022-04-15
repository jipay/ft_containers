/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:02:27 by jdidier           #+#    #+#             */
/*   Updated: 2022/03/30 17:43:19 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <deque>

namespace ft {
	template <class T, class Container = std::deque<T> >
	class stack
	{
		public:
			typedef typename	Container::value_type		value_type;
			typedef typename	Container::size_type		size_type;
			typedef				Container					container_type;
		protected:
			Container c;
		public:
			explicit stack(const Container& = Container());
			bool empty() const { return c.empty(); }
			size_type size() const { return c.size(); }
			value_type& tosp() { return c.back(); }
			const value_type& top() const { return c.back(); }
			void push(const value_type& x) { c.push_back(x); }
			void pop() { c.pop_back(); }
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& x, const stack<T, Container>& y);
	template <class T, class Container>
	bool operator< (const stack<T, Container>& x, const stack<T, Container>& y);
	template <class T, class Container>
	bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y);
	template <class T, class Container>
	bool operator> (const stack<T, Container>& x, const stack<T, Container>& y);
	template <class T, class Container>
	bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y);
	template <class T, class Container>
	bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y);
}

#endif