/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:00:05 by jdidier           #+#    #+#             */
/*   Updated: 2022/04/28 18:00:33 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {
	template <class Iterator>
	class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::value_type,
		typename iterator_traits<Iterator>::difference_type,
		typename iterator_traits<Iterator>::pointer,
		typename iterator_traits<Iterator>::reference> {

		protected:
			Iterator current;

		public:
			typedef Iterator iterator_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::reference reference;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			reverse_iterator(): current() {}
			explicit reverse_iterator(Iterator x): current(x) {}
			template <class U> reverse_iterator(const reverse_iterator<U>& u) {
				this->current = u.base();
			}
			Iterator base() const {
				return this->current;
			} // explicit
			reference operator*() const {
				Iterator tmp = this->current;
				return *--tmp;
			}
			pointer operator->() const {
				return &(operator*());
			}
			reverse_iterator& operator++() {
				--this->current;
				return *this;
			}
			reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				--this->current;
				return tmp;
			}
			reverse_iterator& operator--() {
				++this->current;
				return *this;
			}
			reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				++this->current;
				return tmp;
			}
			reverse_iterator operator+ (difference_type n) const {
				return reverse_iterator(this->current - n);
			}
			reverse_iterator& operator+=(difference_type n) {
				this->current -= n;
				return *this;
			}
			reverse_iterator operator- (difference_type n) const {
				return reverse_iterator(this->current + n);
			}
			reverse_iterator& operator-=(difference_type n) {
				this->current += n;
				return *this;
			}
			reference operator[](difference_type n) const {
				return this->current[-n - 1];
			}
	};
	template <class Iterator>
	bool operator==(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() == y.base());
	}
	template <class Iterator>
	bool operator<(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() > y.base());
	}
	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return !(x == y);
	}
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() < y.base());
	}
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() < y.base() || x.base() == y.base());
	}
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x.base() > y.base() || x.base() == y.base());
	}
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (y.base() - x.base());
	}
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) {
		return reverse_iterator<Iterator> (x.base() - n);
	}

	template <class IteratorL, class IteratorR>
	bool operator==( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current == y.current
	{
		return (x.base() == y.base());
	}
	template <class IteratorL, class IteratorR>
	bool operator<( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current > y.current
	{
		return (x.base() > y.base());
	}
	template <class IteratorL, class IteratorR>
	bool operator!=( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current != y.current
	{
		return (x.base() != y.base());
	}
	template <class IteratorL, class IteratorR>
	bool operator>( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current < y.current
	{
	return (x.base() < y.base());
	}
	template <class IteratorL, class IteratorR>
	bool operator>=( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current <= y.current
	{
	return (x.base() <= y.base());
	}
	template <class IteratorL, class IteratorR>
	bool operator<=( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: x.current >= y.current
	{
		return (x.base() >= y.base());
	}

	template <class IteratorL, class IteratorR>
	typename reverse_iterator<IteratorL>::difference_type operator-( const reverse_iterator<IteratorL>& x, const reverse_iterator<IteratorR>& y) // Returns: y.current - x.current
	{
		return (y.base() - x.base());
	}
	template <class IteratorL, class IteratorR>
	reverse_iterator<IteratorL> operator+( typename reverse_iterator<IteratorL>::difference_type n, const reverse_iterator<IteratorR>& x) // Returns: reverse_iterator<Iterator> (x.current - n)
	{
		return reverse_iterator<IteratorL> (x.base() - n);
	}
}

#endif