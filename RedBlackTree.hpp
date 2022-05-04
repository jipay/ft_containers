/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 19:03:48 by jdidier           #+#    #+#             */
/*   Updated: 2022/05/04 14:14:07 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP
# include <memory>
# include "Node.hpp"
# define NIL NULL // null pointer  or  pointer to sentinel node

namespace ft {
	template <class T, class Allocator = std::allocator<ft::Node<T>>>
	class RedBlackTree
	{
		private:
			ft::Node<T>						*_root;
			ft::Node<T>						*_nil;
			typename Allocator::size_type	_size;
			Allocator						_allocator;
			

		public:
			
			RedBlackTree(void): _root(NIL), _size(0) { //init empty _tree
				this->_nil = this->_allocator.allocate(1);
				this->_allocator.construct(this->_nil, make_node(NIL, BLACK, NIL));
				this->_root = this->_nil;
			}
			~RedBlackTree(/* args */);
			
			
			void	Rotate(ft::Node<T> *x, int dir) {
				ft::Node<T> y = x->child[1 - dir];
				x->child[1 - dir] = y->child[dir];
				if (y->child[dir] != NIL) {
					y->(child[dir])->_parent = x; 
				}
				y->_parent = x->_parent;
				if (x->_parent == this->_nil)
					this->_root = y;
				else
					x->_parent->child[x.ChildDir()] = y;
				// return y; return new root
			}

			

			void	Insert()
	};
}

#endif