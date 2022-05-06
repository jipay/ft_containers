/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 19:03:48 by jdidier           #+#    #+#             */
/*   Updated: 2022/05/06 20:09:47 by jdidier          ###   ########.fr       */
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
		public:
			public:
			typedef ft::Node<T>				Node;
		private:
			Node							*_root;
			Node							*_nil;
			typename Allocator::size_type	_size;
			Allocator						_allocator;
			

		public:
			
			RedBlackTree(void): _root(NIL), _size(0) { //init empty _tree
				this->_nil = this->_allocator.allocate(1);
				this->_allocator.construct(this->_nil, make_node(NIL, BLACK, NIL));
				this->_root = this->_nil;
			}
			~RedBlackTree(/* args */);
			
			Node	*getRoot(void) const {
				return this->_root;
			}
			Node	*getNil(void) const {
				return this->_nil;
			}
			Node	*getBegin(void) const {
				Node *tmp = this->_root;
				while (tmp->_child[LEFT] != this->_nil)
					tmp = tmp->_child[LEFT];
				return tmp;
			}

			Node	*TreeSearch(Node *x, T const& key) {
				// recursive way
				if (x == this->_nil || key == x->_datas)
					return x;
				if (key < x->_datas)
					return TreeSearch(x->_child[LEFT], key);
				else
					return TreeSearch(x->_child[RIGHT], key);
				// iterative way : to compare process' time
				/*
				while (x != this->_nil && key != x->_datas) {
					if (key < x->_datas)
						x = x->_child[LEFT];
					else
						x = x->_child[RIGHT];
					return x;
				}
				*/
			}

			Node	*min(Node *x) {
				while (x->_child[LEFT] != this->_nil)
					x = x->_child[LEFT];
				return x;
			}

			Node	*max(Node *x) {
				while (x->_child[RIGHT] != this->_nil)
					x = x->_child[RIGHT];
				return x;
			}

			Node	*Successor(Node *x) {
				if (x->_child[RIGHT] != this->_nil)
					return min(x->_child[RIGHT]);
				Node *y = x->_parent;
				while (y != this->_nil && x == y->_child[RIGHT]) {
					x = y;
					y = y->_parent;
				}
				return y;
			}

			Node	*Predecessor(Node *x) {
				if (x->_child[LEFT] != this->_nil)
					return max(x->_child[RIGHT]);
				Node *y = x->_parent;
				while (y != this->_nil && x == y->_child[LEFT]) {
					x = y;
					y = y->_parent;
				}
				return y;
			}

			void	Rotate(Node *x, int dir) {
				Node *y = x->child[1 - dir];
				x->child[1 - dir] = y->child[dir];
				if (y->child[dir] != this->_nil) {
					y->(child[dir])->_parent = x;
				}
				y->_parent = x->_parent;
				if (x->_parent == this->_nil)
					this->_root = y;
				else
					x->_parent->child[x.ChildDir()] = y;
				// return y; return new root
			}

			void	InsertRebalance(Node *x) {
				while (x->_parent->_color == RED) {
					if (x->_parent->ChildDir() == LEFT) {
						Node *y = x->_parent->_parent->_child[RIGHT]; //get x's aunt
						if (y->_color == RED) {
							x->_parent->_color = BLACK;
							y->_color = BLACK;
							x->_parent->_parent->_color = RED;
							x = x->_parent->_parent;
						} else {
							if (x->ChildDir() == RIGHT) {
								x = x->_parent;
								this->Rotate(x, LEFT);
							}
							x->_parent->_color = BLACK;
							x->_parent->_parent->_color = RED;
							this->Rotate(x->_parent->_parent, RIGHT);
						}
					} else {
						Node *y = x->_parent->_parent->_child[LEFT]; // get x's aunt

					}
				}
				this->_root = BLACK;
			}

			void	Insert(T const& data) {
				Node *new = this->_allocator.allocate(1)
				this->_allocator.construct(new, make_node(data, RED, this->_nil));
				new->_child[LEFT] = this->_nil;
				new->_child[RIGHT] = this->_nil;
				Node *x = this->_root;
				Node *y = this->_nil;
				while (x != this->_nil) {
					y = x;
					if (*new < *x)
						x = x->_child[LEFT];
					else
						x = x->_child[RIGHT];
				}
				new->_parent = y;
				if (y == this->_nil)
					this->_root = new;
				else if (*new < *y)
					y->_child[LEFT] = new;
				else
					y->_child[RIGHT] = new;
				this->_size += 1;
				this->InsertRebalance(new);
			}

			void	Tranplant(Node *u, Node *v) {
				if (u->_parent == this->_nil)
					this->_root = v;
				else if (u->ChildDir() == LEFT)
					u->_parent->_child[LEFT] = v;
				else
					u->_parent->_child[RIGHT] = v;
				if (v != this->_nil)
					v->_parent = u->_parent;
			}
			void	Delete(Node *x) {
				if (x->_child[LEFT] == this->_nil)
					this->Tranplant(x, x->_child[RIGHT]);
				else if (x->_child[RIGHT] == this->_nil)
					this->Tranplant(x, x->_child[LEFT]);
				else {
					Node *y = this->min(x->_child[RIGHT]);
					if (y->_parent != x) {
						this->Tranplant(y, y->_child[RIGHT]);
						y->_child[RIGHT] = x->_child[RIGHT];
						y->_child[RIGHT]->_parent = y;
					}
					this->Tranplant(x, y);
					y->_child[LEFT] = x->_child[LEFT];
					y->_child[LEFT]->_parent = y;
				}
				this->_size -= 1;
				this->_allocator.destroy(x);
				this->_allocator.deallocate(x, 1);
			}
	};
}

#endif