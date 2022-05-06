/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdidier <jdidier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 21:11:49 by jdidier           #+#    #+#             */
/*   Updated: 2022/05/05 19:34:31 by jdidier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP


namespace ft {
	enum e_color {RED, BLACK};
	enum e_dir {LEFT, RIGHT};
	template<class T>
	struct	Node {
		e_color		_color;
		T			_datas;
		Node<T>		*_child[2];
		Node<T>		*_parent;
		Node(): _color(BLACK), _datas(T()), _parent(NIL) {
			this->_child[LEFT] = NIL;
			this->_child[RIGHT] = NIL;
		}
		Node(T const& x, e_color color, Node *parent): _datas(x), _color(color), _parent(parent) {
			this->_child[LEFT] = NIL;
			this->_child[RIGHT] = NIL;
		}
		template<class U>
		Node(Node<U> const& n) {
			*this = n;
		}
		Node	&operator=(Node const& n) {
			this->_color = n._color;
			this->_datas = n._datas;
			this->_child = n._child;
			this->_parent = n._parent;
			return *this;
		}
		e_dir		ChildDir(void) const {
			return (this == this->_parent->child[RIGHT] ? RIGHT : LEFT);
		}
	};

	template <class T>
	bool				operator==(Node<T> const& x, Node<T> const& y) {
		return (x._datas == y._datas);
	}
	template <class T>
	bool				operator!=(Node<T> const& x, Node<T> const& y) {
		return (!(x == y));
	}
	template <class T>
	bool				operator<(Node<T> const& x, Node<T> const& y) {
		return (x._datas < y._datas);
	}
	template <class T>
	bool				operator>(Node<T> const& x, Node<T> const& y) {
		return (x._datas > y._datas);
	}
	template <class T>
	bool				operator<=(Node<T> const& x, Node<T> const& y) {
		return (x == y || x < y);
	}
	template <class T>
	bool				operator>=(Node<T> const& x, Node<T> const& y) {
		return (x == y || x > y);
	}
	template <class T>
	Node<T>				make_node(T const& x, e_color color, Node<T> *parent) {
		return ft::Node<T>(x, color, parent);
	}
	template <class T>
	Node<T>				make_node(Node<T> const& x) {
		return ft::Node<T>(x);
	}
}

#endif NODE_HPP