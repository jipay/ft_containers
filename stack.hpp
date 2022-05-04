/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 17:02:27 by jdidier           #+#    #+#             */
/*   Updated: 2022/04/28 18:22:33 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <deque>
# include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef typename	Container::value_type		value_type;
			typedef typename	Container::size_type		size_type;
			typedef				Container					container_type;
		protected:
			Container _c;
		public:
			explicit stack(const Container&c = Container()): _c(c) {}
			bool empty() const { return _c.empty(); }
			size_type size() const { return _c.size(); }
			value_type& top() { return _c.back(); }
			const value_type& top() const { return _c.back(); }
			void push(const value_type& x) { _c.push_back(x); }
			void pop() { _c.pop_back(); }
			Container getContainer(void) const { return this->_c;}
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& x, const stack<T, Container>& y) {
		return (x.getContainer() == y.getContainer());
	}
	template <class T, class Container>
	bool operator< (const stack<T, Container>& x, const stack<T, Container>& y) {
		return (x.getContainer() < y.getContainer());
	}
	template <class T, class Container>
	bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return (x.getContainer() != y.getContainer());
	}
	template <class T, class Container>
	bool operator> (const stack<T, Container>& x, const stack<T, Container>& y) {
		return (x.getContainer() > y.getContainer());
	}
	template <class T, class Container>
	bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return (x.getContainer() >= y.getContainer());
	}
	template <class T, class Container>
	bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y) {
		return (x.getContainer() <= y.getContainer());
	}
}

#endif