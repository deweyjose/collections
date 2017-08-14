//
// Created by Dewey Jose on 6/14/17.
//

#ifndef COLLECTIONS_DLINKEDLIST_H
#define COLLECTIONS_DLINKEDLIST_H

template<class T>
class dlinkedlist {

private:

    class node {

    public:
        T value;
        node * next;
        node * previous;

        node() : value(0), next(0), previous(0) {}
        node(T _value, node * _next, node * _previous) : value(_value), next(_next), previous(_previous) {}
    };

public:
    template<bool is_const = true>
    class dlinkedlist_iter {

        friend class dlinkedlist;

        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef T value_type;
        typedef dlinkedlist_iter iterator;

        typedef typename std::conditional<is_const ,const node*, node*>::type   pointer_node;
        typedef typename std::conditional<is_const ,const node&, node&>::type   reference_node;

        typedef typename std::conditional<is_const ,const T*, T*>::type         pointer_T;
        typedef typename std::conditional<is_const ,const T&, T&>::type         reference_T;

    private:
        pointer_node node;

    public:

        dlinkedlist_iter(pointer_node _node) : node(_node) {}

        dlinkedlist_iter(const dlinkedlist_iter<false>& original) : node(original.node) {}

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

        iterator & operator--() {
            node = node->previous;
            return *this;
        }

        iterator operator--(int) {
            iterator clone(*this);
            node = node->previous;
            return clone;
        }
    };

    typedef dlinkedlist_iter<false> iterator;
    typedef dlinkedlist_iter<true> const_iterator;

    dlinkedlist() {
        _size = 0;
        nil = new node();
        nil->next = nil;
        nil->previous = nil;
    }

    ~dlinkedlist() {
        delete nil;
    }

    bool isEmpty() const {
        return nil->next == nil;
    }

    int size() const {
        return _size;
    }

    void push_front(T value) {
        node * old_front = nil->next;

        node * new_front = new node(value, old_front, nil);

        old_front->previous = new_front;

        nil->next = new_front;

        ++_size;
    }

    void push_back(T value) {
        node * old_back = nil->previous;

        node * new_back = new node(value, nil, old_back);

        old_back->next = new_back;

        nil->previous = new_back;

        ++_size;
    }

    iterator erase(iterator i) {
        if (i.node == nil) {
            return NULL;
        }

        i.node->previous->next = i.node->next;
        i.node->next->previous = i.node->previous;

        node * to_delete = i.node;  // remember who to delete
        ++i;                        // move the iterator along so we can return it
        delete to_delete;           // delete the node being erased
        --_size;                    // decrement size

        return i;
    }

    iterator begin() {
        return dlinkedlist_iter<false>(nil->next);
    }

    const_iterator cbegin() {
        return dlinkedlist_iter<true>(nil->next);
    }

    iterator end() {
        return dlinkedlist_iter<false>(nil);
    }

    const_iterator cend() {
        return dlinkedlist_iter<true>(nil);
    }

private:
    int _size;
    node * nil;
};
#endif //COLLECTIONS_DLINKEDLIST_H
