#ifndef MMKKWRG_CIRCULAR_QUEUE_hpp
#define MMKKWRG_CIRCULAR_QUEUE_hpp

#include <cassert>
#include <vector>
#include <iterator>

template<typename Type>
class CircularQueue {
    private:
        const size_t N;
        std::vector<Type> arr;
        size_t front;
        size_t rear;
        size_t __size;

    public:
        CircularQueue(size_t max_elems): N(max_elems), arr(N), front(0), rear(-1), __size(0) {}
        size_t size() const { return __size; }

        void clear() {
            front = 0;
            rear = -1;
            __size = 0;
        }

        void enqueue(Type x) {
            assert(__size != N);
            rear = (rear + 1) % N;
            arr[rear] = x;
            __size++;
        }

        Type dequeue() {
            assert(__size != 0);
            Type x = arr[front];
            front = (front + 1) % N;
            __size--;
            return x;
        }

        Type& operator[](int idx) {
            assert(idx >= 0 && idx < static_cast<int>(__size));
            return arr[(front + idx) % N];
        }

        class iterator {
            private:
                CircularQueue* q;
                size_t i;

            public:
                using iterator_category = std::forward_iterator_tag;
                using value_type = Type;
                using difference_type = std::ptrdiff_t;
                using pointer = Type*;
                using reference = Type&;

                iterator(CircularQueue* q, size_t pos = 0): q(q), i(pos) {}

                reference operator*() {
                    return q->arr[(q->front + i) % q->N];
                }

                pointer operator->() {
                    return &q->arr[(q->front + i) % q->N];
                }

                iterator& operator++() {
                    ++i;
                    return *this;
                }

                iterator operator++(int) {
                    iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                bool operator==(const iterator& other) const {
                    return q == other.q && i == other.i;
                }

                bool operator!=(const iterator& other) const {
                    return !(*this == other);
                }
        };

        class const_iterator {
            private:
                const CircularQueue* q;
                size_t i;

            public:
                using iterator_category = std::random_access_iterator_tag;
                using value_type = Type;
                using difference_type = std::ptrdiff_t;
                using pointer = const Type*;
                using reference = const Type&;

                const_iterator(const CircularQueue* q, size_t pos = 0): q(q), i(pos) {}

                reference operator*() const {
                    return q->arr[(q->front + i) % q->N];
                }

                pointer operator->() const {
                    return &q->arr[(q->front + i) % q->N];
                }

                const_iterator& operator++() {
                    ++i;
                    return *this;
                }

                const_iterator operator++(int) {
                    const_iterator temp = *this;
                    ++(*this);
                    return temp;
                }

                bool operator==(const const_iterator& other) const {
                    return q == other.q && i == other.i;
                }

                bool operator!=(const const_iterator& other) const {
                    return !(*this == other);
                }
        };

        iterator begin() { return iterator(this, 0); }
        const_iterator cbegin() const { return const_iterator(this, 0); }
        iterator end() { return iterator(this, __size); }
        const_iterator cend() const { return const_iterator(this, __size); }

};

#endif
