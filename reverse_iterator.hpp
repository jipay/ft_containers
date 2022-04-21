/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:00:05 by jdidier           #+#    #+#             */
/*   Updated: 2022/04/18 17:59:38 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft {
	template <class Iterator>
	class reverse_iterator : public
		iterator<typename iterator_traits<Iterator>::iterator_category,
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
				reverse_iterator(this->current - n);
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
		return (x.base() < y.base());
	}
	template <class Iterator>
	bool operator!=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return !(x == y);
	}
	template <class Iterator>
	bool operator>(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (y < x);
	}
	template <class Iterator>
	bool operator>=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x > y || x == y);
	}
	template <class Iterator>
	bool operator<=(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (x < y || x == y);
	}
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y) {
		return (y.base() - x.base());
	}
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) {
		return (x.base() - n);
	}
}

#endif