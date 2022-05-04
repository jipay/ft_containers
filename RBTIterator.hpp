/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:07:16 by jdidier           #+#    #+#             */
/*   Updated: 2022/05/04 14:21:39 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTITERATOR_HPP
# define RBTITERATOR_HPP

# include "Node.hpp"
# include "iterator.hpp"

namespace ft {
	template<class T>
	class RBTIterator : public iterator<bidirectional_iterator_tag, T>
	{
		private:
			Node	*_current;
		public:
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category		iterator_category;
			typedef ft::Node<T>																	Node;
			RBTIterator(void): _current(NULL) { }
			explicit RBTIterator(Node const* n): _current(n) {}
			RBTIterator(RBTIterator const& src) {
				*this = src;
			}
			template <class U>
			RBTIterator		&operator=(RBTIterator<U> const& u) {
				if (this != &u)
					this->_current = u.base();
				return *this;
			}
			operator		RBTIterator<const T>(void) const {
				return	RBTIterator<const T>(this->_current);
			}
			~RBTIterator();
			pointer		base() const {
				return this->_current;
			}
			reference	operator*() const {
				return *(this->_current);
			}

			pointer		operator->() const {
				return &(operator*());
			}
			RBTIterator	&operator++();
			RBTIterator	operator++(int) {
				RBTIterator tmp = *this;
				operator++();
				return tmp;
			}
			RBTIterator	&operator--();
			RBTIterator	operator--(int) {
				RBTIterator tmp = *this;
				operator--();
				return tmp;
			}
	};
	template <class T>
	bool	operator==(RBTIterator<T> const& x, RBTIterator<T> const& y) {
		return (x.base() == y.base());
	}
	template <class T>
	bool	operator!=(RBTIterator<T> const& x, RBTIterator<T> const& y) {
		return (x.base() != y.base());
	}
	template <class TL, class TR>
	bool	operator==(RBTIterator<TL> const& x, RBTIterator<TR> const& y) {
		return (x.base() == y.base());
	}
	template <class TL, class TR>
	bool	operator!=(RBTIterator<TL> const& x, RBTIterator<TR> const& y) {
		return (x.base() != y.base());
	}
}

#endif