/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:07:16 by jdidier           #+#    #+#             */
/*   Updated: 2022/05/06 20:13:20 by jdidier          ###   ########.fr       */
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
		public:
			typedef ft::Node<T>																	Node;
		private:
			Node	*_current;
			Node	*_nil;

			// TODO :: NIL BORDEL A COMPARER SINON NULL CA VA FOUTRE LA MERDE
		public:
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category		iterator_category;
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
			RBTIterator	&operator++() {
				if (this->_current->_child[RIGHT] != this->_nil) { 
					this->_current = this->_current->_child[RIGHT];
					while (this->_current && this->_current->_child[LEFT])
						this->_current = this->_current->_child[LEFT];
				} else {
					Node *tmp = this->_current->_parent;
					if (tmp->_child[RIGHT] == this->_current) {
						while (tmp->_child[RIGHT] == this->_current) {
							this->_current = tmp;
							tmp = tmp->_parent;
						}
					}
					if (this->_current != tmp)
						this->_current = tmp;
				}
				return *this;
			}
			RBTIterator	operator++(int) {
				RBTIterator tmp = *this;
				operator++();
				return tmp;
			}
			RBTIterator	&operator--() {
				if (this->_current->_parent->_parent == this->_current && this->_current->_color == RED)
					this->_current = this->_current->_child[LEFT];
				else if (this->_current->_child[LEFT]) {
					while (this->_current->_child[RIGHT])
						this->_current = this->_current->_child[RIGHT];
				} else {
					Node *parent = this->_current->_parent;
					while (parent->_child[LEFT] == this->_current) {
						this->_current = parent;
						parent = parent->_parent;
					}
					this->_current = parent;
				}
				return *this;
			}
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