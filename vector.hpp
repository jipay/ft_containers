/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:38:18 by jdidier           #+#    #+#             */
/*   Updated: 2022/04/25 18:46:52 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iterator>
# include <vector>
# include <stdexcept>
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
			vector(InputIterator first, InputIterator last, const Allocator& = Allocator(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _capacity(last - first), _size(last - first) {
				this->_datas = this->_allocator.allocate(last - first);
				for (int i = 0; first != last; first++, i++)
					this->_allocator.construct(this->_datas + i, *first);
			}
			
			vector(const vector<T,Allocator>& x) {
				*this = x;
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
				this->_size = x._size;
				this->_capacity = (this->_capacity >= x._capacity) ? this->_capacity + 0 : x._capacity;
				this->_allocator = x._allocator;
				this->_datas = this->_allocator.allocate(this->_capacity);
				for (size_type i = 0; i < this->_size; i++)
					this->_allocator.construct(&this->_datas[i], x._datas[i]);
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
						this->_alloctor.construct(this->_memory + this->_size, c);
				}
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
				T	*newDatas;
				newDatas = this->_allocator.allocate(n);
				for (iterator it = this->begin(); it != this->end(); it++)
					this->_allocator.construct((newDatas + (it - this->begin())), *it);
				this->clear();
				this->_allocator.deallocate(this->_datas, this->_capacity);
				this->_capacity = n;
				this->_datas = newDatas;
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
				if (this->size == this->_capacity)
				{
					this->reserve(this->_capacity * 2);
					this->_capacity *= 2;
				}
				this->_allocator.construct(this->_datas + (this->_size + 1), x);
				this->_size++;
			}
			void pop_back() {
				this->_allocator.destroy(this->_datas + this->_size);
				this->_size--;
			}
			
			iterator insert(iterator position, const T& x) {
				this->insert(position, 1, x);
			}
			void insert(iterator position, size_type n, const T& x) {
				if (this->_size + n > this->_capacity * 2) {
					this->_size += n;
					this->reserve(this->_size);
					this->_capacity = this->_size;
				} else if (this->_size + n > this->_capacity){
					this->_size += n;
					this->reserve(this->_capacity * 2);
					this->_capacity *= 2;
				}
				//TODO : move element from to 'position' to this->end() to +n position
				for (size_type i = 0; i < this->end() - position; i++) {
					this->_allocator.construct(this->back() - i, *(position + (this->end() - position - 1) - i));
				}
				//TODO : erase element from 'position' to +n 'position'
				//TODO : consctruct from 'position' to +n 'position' element x
				for (iterator it = position; it != position + n; it++) {
					this->_allocator.destroy(it);
					this->_allocator.construct(it, x);
				}
			}
			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
				size_type n = last - first;
				if (this->_size + n > this->_capacity * 2) {
					this->_size += n;
					this->reserve(this->_size);
					this->_capacity = this->_size;
				} else if (this->_size + n > this->_capacity){
					this->_size += n;
					this->reserve(this->_capacity * 2);
					this->_capacity *= 2;
				}
				for (size_type i = 0; i < this->end() - position; i++) {
					this->_allocator.construct(this->end() - i, *(position + (this->end() - position - 1) - i));
				}
				for (iterator it = position; it != position + n; it++, first++) {
					//this->_allocator.destroy(it);
					this->_allocator.construct(it, *first);
				}
			}
			
			iterator erase(iterator position) {
				
				for (size_type i = position - this->begin(); i < this->_size; i++)
				{
					this->_allocator.destroy(this->_datas + i);
					if (i < this->_size - 1)
						this->_allocator.construct(this->_datas + i, *(this->_datas + i + 1));
				}
				this->_size--;
				return position;
			}

			iterator erase(iterator first, iterator last) {
				for (long i = first - this->begin(); i < (first - this->begin() + (last - first)); i++) {
					this->_allocator.destroy(this->_datas + i);
				}
				this->_size -= (last - first);
				size_type i = first - this->begin();
				for (iterator it = last; it < this->end(); it++, i++) {
					this->_allocator.construct(this->_datas + i, *it);
				}
				return first;
			}

			void swap(ft::vector<T,Allocator>& x) {
				ft::vector<T, Allocator> tmp = *this;
				*this = x;
				x = tmp;
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
				if ((x[i] != y[y]))
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