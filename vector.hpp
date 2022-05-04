/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:38:18 by jdidier           #+#    #+#             */
/*   Updated: 2022/05/03 15:58:11 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iterator>
# include <stdexcept>
# include <cstring>
# include "is_integral.hpp"
# include "enable_if.hpp"
# include "lexicographical_compare.hpp"
# include "iterator.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector 
	{
		private:
			T								*_datas;
			typename Allocator::size_type	_capacity;
			typename Allocator::size_type	_size;
			Allocator						_allocator;
			

		public:
			// types:
			typedef typename Allocator::reference					reference;
			typedef typename Allocator::const_reference				const_reference;
			typedef typename ft::random_access_iterator<T>			iterator; // See 23.1
			typedef typename ft::random_access_iterator<const T>	const_iterator; // See 23.1
			typedef typename Allocator::size_type					size_type; // See 23.1
			typedef typename Allocator::difference_type				difference_type;// See 23.1
			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef typename Allocator::pointer						pointer;
			typedef typename Allocator::const_pointer				const_pointer;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			// 23.2.4.1 construct/copy/destroy:
			explicit vector(const Allocator& = Allocator()):_datas(0), _capacity(0), _size(0){}
			explicit vector(size_type n, const T& value = T(), const Allocator& = Allocator()): _capacity(n), _size(n) {
				this->_datas = this->_allocator.allocate(n);
				for (typename Allocator::size_type i = 0; i < n; i++)
					this->_allocator.construct(this->_datas + i, value);
			}
			
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
				size_type n = 0;
				for (InputIterator it = first; it != last; it++) {
					n++;
				}
				this->_datas = this->_allocator.allocate(n);0
				for (int i = 0; first != last; first++, i++)
					this->_allocator.construct(this->_datas + i, *first);
				this->_capacity = n;
				this->_size = n; 
			}
			
			vector(const vector<T,Allocator>& x): _capacity(x.capacity()), _size(x.size()) {
				//*this = x;
				this->_datas = this->_allocator.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.construct(this->_datas + i, x[i]);
			}
			~vector() {
				this->clear();
				this->_allocator.deallocate(this->_datas, this->_capacity);
			}
			vector<T,Allocator>& operator=(const vector<T,Allocator>& x) {
				/*
				if (this != &x) {
					this->assign(x.begin(), x.end());
				}
				return *this;
				*/

				this->clear();
				this->_allocator.deallocate(this->_datas, this->_capacity);
				this->_datas = NULL;
				this->_size = x.size();
				this->_capacity = (this->_capacity >= x.capacity()) ? this->_capacity + 0 : x.capacity();
				this->_allocator = x.get_allocator();
				this->_datas = this->_allocator.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.construct(this->_datas + i, x._datas[i]);
				return *this;
			}

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last) {
				this->erase(this->begin(), this->end());
				this->insert(this->begin(), first, last);
			}
			void assign(size_type n, const T& u) {
				this->clear();
				this->resize(n, u);
			}
			allocator_type get_allocator() const {
				return this->_allocator;
			}

			// iterators:
			iterator begin() {
				return iterator(this->_datas);
			}
			const_iterator begin() const {
				return const_iterator(this->_datas);
			}
			iterator end() {
				return iterator(this->_datas + this->_size);
			}
			const_iterator end() const {
				return const_iterator(this->_datas + this->_size);
			}
			reverse_iterator rbegin() {
				return reverse_iterator(this->end());
			}
			const_reverse_iterator rbegin() const {
				return const_reverse_iterator(this->end());
			}
			reverse_iterator rend() {
				return reverse_iterator(this->begin());
			}
			const_reverse_iterator rend() const {
				return const_reverse_iterator(this->begin());
			}
			
			// 23.2.4.2 capacity:
			size_type size() const {
				return this->_size;
			}
			size_type max_size() const {
				return this->_allocator.max_size();
			}
			
			void resize(size_type sz, T c = T()) {
				if (sz < this->_size) {
					for (; sz < this->_size; this->_size--)
						this->_allocator.destroy(this->_datas + this->_size);
				} else {
					if (sz > this->_size) {
						if (sz > this->_capacity) {
							if (sz < this->_capacity * 2)
								this->reserve(this->_capacity * 2);
							else
								this->reserve(sz);
						}
					}
					for (; this->_size < sz; this->_size++)
						this->_allocator.construct(this->_datas + this->_size, c);
				}
				this->_size = sz;
			}
			
			size_type capacity() const {
				return this->_capacity;
			}
			bool empty() const {
				return (this->_size > 0) ? false : true;
			}
			void reserve(size_type n) {

				if (n > this->max_size())
					throw std::length_error("vector::reserve");
				if (n > this->capacity()) {
					T	*newDatas;
					newDatas = this->_allocator.allocate(n);
					for (iterator it = this->begin(); it != this->end(); it++) {
						this->_allocator.construct((newDatas + (it - this->begin())), *it);
						this->_allocator.destroy(this->_datas + (it - this->begin()));
					}
					this->_allocator.deallocate(this->_datas, this->_capacity);
					this->_capacity = n;
					this->_datas = newDatas;
				}
			}

			// element access:
			reference operator[](size_type n) {
				return *(this->_datas + n);
			}
			const_reference operator[](size_type n) const {
				return *(this->_datas + n);
			}
			const_reference at(size_type n) const {
				if (this->_size <= n) {
					throw std::out_of_range("prout");
				} else {
					return *(this->_datas + n);
				}
			}
			reference at(size_type n) {
				if (this->_size <= n) {
					throw std::out_of_range("prout"); 
				} else {
					return *(this->_datas + n);
				}
			}
			reference front() {
				return *(this->_datas);
			}
			const_reference front() const {
				return *(this->_datas);
			}
			reference back() {
				return *(this->_datas + (this->_size - 1));
			}
			const_reference back() const {
				return *(this->_datas + (this->_size - 1));
			}

			// 23.2.4.3 modifiers:
			void push_back(const T& x)
			{
				if (this->_capacity == 0)
					this->reserve(1);
				if (this->_size == this->_capacity)
				{
					this->reserve(this->_capacity * 2);
				}
				this->_allocator.construct(this->_datas + this->_size++, x);
			}
			void pop_back() {
				this->_allocator.destroy(this->_datas + --this->_size);
			}
			
			iterator insert(iterator position, const T& x) {
				this->insert(position, 1, x);
				return position;
			}
			void insert(iterator position, size_type n, const T& x) {
				// TODO : check position > begin()
				size_type j = position - this->begin();
				
				if (this->_size + n > this->_capacity * 2) {
					//this->_size += n;
					this->reserve(this->_size + n);
				} else if (this->_size + n > this->_capacity){
					//this->_size += n;
					this->reserve(this->_capacity * 2);
				}
				
				//this->resize(this->_size + n);
				size_type i = this->_size + n - 1;
				//size_type i = this->_size - 1;
				
				/*
				std::cout << "after realloc" << std::endl;
				for (iterator it = this->begin(); it != this->end(); it++) {
					std::cout << *it << std::endl;
				}
				*/
				for (; i > j; i--) {
					//std::cout << "i: " << i << " j: " << j << std::endl;
					this->_allocator.construct(this->_datas + i, *(this->_datas + i - n));
					this->_allocator.destroy(this->_datas + i - n);
				}
				size_type test = j + n;
				for (; j < test; j++) {
					this->_allocator.construct(this->_datas + j, x);
				}
				/*
				std::cout << "check" << std::endl;
				for (iterator it = this->begin(); it != this->end(); it++) {
					std::cout << *it << std::endl;
				}
				*/
				this->_size += n;
			}
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
				size_type n = 0;
				for (InputIterator it = first; it != last; it++) {
					n++;
				}
				size_type j = position - this->begin();
				if (this->_size + n > this->_capacity * 2) {
					this->reserve(this->_size + n);
				} else if (this->_size + n > this->_capacity){
					this->reserve(this->_size * 2);
				}
				this->_size += n;
				size_type i = this->_size - 1;
				for (; i > j; i--) {
					this->_allocator.construct(this->_datas + i, *(this->_datas + i - n));
					this->_allocator.destroy(this->_datas + i - n);
				}
				for (; first != last; first++, j++) {
					this->_allocator.construct(this->_datas + j, *first);
				}
			}
			
			iterator erase(iterator position) {
				for (iterator it = position; it != this->end(); it++)
				{
					size_type i = it - this->begin();
					this->_allocator.destroy(this->_datas + i);
					if (i < this->_size - 1)
						this->_allocator.construct(this->_datas + i, *(it + 1));
				}
				--this->_size;
				return position;
			}

			iterator erase(iterator first, iterator last) {
				for (iterator it = first; it != last; it++) {
					this->_allocator.destroy(this->_datas + (it - this->begin()));
				}
				//std::cout << "last: " << *last << std::endl;
				for (iterator it1 = first, it2 = last; it2 != this->end(); it1++, it2++) {
					size_type i = it2 - this->begin();
					this->_allocator.destroy(this->_datas + i);
					size_type j = it1 - this->begin();
					this->_allocator.construct(this->_datas + j, *it2);
				}
				this->_size -= (last - first);
				return first;
			}

			void swap(ft::vector<T,Allocator>& x) {
				/*
				ft::vector<T, Allocator> tmp = *this;
				*this = x;
				x = tmp;
				*/
				allocator_type tmp_allocator = this->_allocator;
				value_type *tmp_datas = this->_datas; 
				size_type tmp_size = this->_size;
				size_type tmp_capacity  = this->_capacity;

				this->_allocator = x.get_allocator();
				this->_datas = x._datas;
				this->_size = x.size();
				this->_capacity = x.capacity();

				x._allocator = tmp_allocator;
				x._datas = tmp_datas;
				x._size = tmp_size;
				x._capacity = tmp_capacity;
			}

			void clear() {
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.destroy(this->_datas + i);
				this->_size = 0;
			}
	};
	template <class T, class Allocator>
	bool operator==(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		if (x.size() == y.size() && x.capacity() == y.capacity()) {
			for (typename Allocator::size_type i = 0; i < x.size(); i++) {
				if ((x[i] != y[i]))
					return false;
			}
		} else {
			return false;
		}
		return true;
	}
	template <class T, class Allocator>
	bool operator< (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}
	template <class T, class Allocator>
	bool operator!=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return (!(x == y));
	}
	template <class T, class Allocator>
	bool operator> (const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return (y < x);
	}
	template <class T, class Allocator>
	bool operator>=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return (x == y || x > y);
	}
	template <class T, class Allocator>
	bool operator<=(const vector<T,Allocator>& x, const vector<T,Allocator>& y) {
		return (x == y || x < y);
	}
	// specialized algorithms:
	template <class T, class Allocator>
	void swap(vector<T,Allocator>& x, vector<T,Allocator>& y) {
		x.swap(y);
	}
}

#endif