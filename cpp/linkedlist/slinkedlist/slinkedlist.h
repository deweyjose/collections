//
// Created by Dewey Jose on 5/23/17.
//

#ifndef COLLECTIONS_SLINKEDLIST_H
#define COLLECTIONS_SLINKEDLIST_H

template<class T>
class slinkedlist {

private:

    class node {

    public:
        T value;
        node * next;

        node() : value(0), next(0) {}
        node(T _value, node * _next) : value(_value), next(_next) {}
    };

public:
    template<bool is_const = true>
    class slinkedlist_iter {

        friend class slinkedlist;

        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef T value_type;
        typedef slinkedlist_iter iterator;

        typedef typename std::conditional<is_const ,const node*, node*>::type   pointer_node;
        typedef typename std::conditional<is_const ,const node&, node&>::type   reference_node;

        typedef typename std::conditional<is_const ,const T*, T*>::type         pointer_T;
        typedef typename std::conditional<is_const ,const T&, T&>::type         reference_T;

    private:
        pointer_node node;

    public:

        slinkedlist_iter(pointer_node _node) : node(_node) {}

        slinkedlist_iter(const slinkedlist_iter<false>& original) : node(original.node) {}

        bool operator == (const iterator & rhs) {
            return node == rhs.node;
        }

        bool operator != (const iterator & rhs) {
            return !operator==(rhs);
        }

        reference_T operator * () {
            return node->value;
        }

        pointer_T operator -> () {
            return &(node->value);
        }

        iterator & operator++ () {
            node = node->next;
            return *this;
        }

        iterator operator++(int) {
            iterator clone(*this);
            node = node->next;
            return clone;
        }
    };

    typedef slinkedlist_iter<false> iterator;
    typedef slinkedlist_iter<true> const_iterator;

    slinkedlist() {
        _size = 0;
        nil = new node();
        nil->next = nil;
    }

    ~slinkedlist() {
        delete nil;
    }

    bool isEmpty() const {
        return nil->next == nil;
    }

    int size() const {
        return _size;
    }

    void push_front(T value) {
        node * n = new node(value, nil->next);
        nil->next = n;
        ++_size;
    }

    iterator erase(iterator i) {
        if (i.node == nil) {
            return NULL;
        }

        iterator previous = begin();
        for (; previous.node->next != i.node; ++previous);

        node * to_delete = i.node;

        previous.node->next = (++i).node;

        delete to_delete;

        --_size;

        return i;
    }

    iterator begin() {
        return slinkedlist_iter<false>(nil->next);
    }

    const_iterator cbegin() {
        return slinkedlist_iter<true>(nil->next);
    }

    iterator end() {
        return slinkedlist_iter<false>(nil);
    }

    const_iterator cend() {
        return slinkedlist_iter<true>(nil);
    }

private:
    int _size;
    node * nil;
};

#endif //COLLECTIONS_SLINKEDLIST_H
