#ifndef DEQUE_H_
#define DEQUE_H_

#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

template<typename T>
class Deque {
 public:
  Deque();

  ~Deque();

  bool Empty() const noexcept;

  size_t Size() const noexcept;
  // resize internal data structure to fit precisely the number of items; frees
  // unused memory in O(N)
  void ShrinkToFit();

  // Indexing
  // ret item at <pos> in O(1)
  T& operator[](size_t pos);
  // ret item at front in O(1)
  T& Front();
  // ret item at back in O(1)
  T& Back();

  // Empties deque in O(1)
  void Clear(void) noexcept;
  // Push item <value> from front in O(1) amortized
  void PushFront(const T &value);
  // Push item <value> from back in O(1) amortized
  void PushBack(const T &value);
  // Remove item at front in O(1) amortized
  void PopFront();
  // Remove item at back in O(1) amortized
  void PopBack();

 private:

  // Private vars
  int head = -1;
  int tail = -1;
  int size;
  int capacity = 1;
  std::unique_ptr<T[]> items;

  // Private methods
  void Resize(int new_size) {
    std::unique_ptr<T[]> temp(new T[capacity]);
    if (tail == head - 1) {
      int index = 0;
      for (int i = head; i < capacity; i++) {
        temp[index] = items[i];
        index++;
      }
      for (int i = 0; i < tail + 1; i++) {
        temp[index] = items[i];
        index++;
      }
    } else {
      for (int i = 0; i < capacity; i++)
        temp[i] = items[i];
    }
    std::unique_ptr<T[]> big_arr(new T[new_size]);
    std::move(temp.get(), std::next(temp.get(), capacity), big_arr.get());
    capacity = new_size;
    head = 0;
    tail = size - 1;
    std::swap(items, big_arr);
  }
};

// implement deque
template<typename T>
Deque<T>::Deque() : size(0), items(std::unique_ptr<T[]>(new T[size])) {}

template<typename T>
Deque<T>::~Deque() = default;

template<typename T>
bool Deque<T>::Empty() const noexcept {
  if (head == - 1)
    return true;
  return false;
}

template<typename T>
size_t Deque<T>::Size() const noexcept {
  return size;
}

template<typename T>
void Deque<T>::ShrinkToFit() {
  Resize(size);
}

template<typename T>
T& Deque<T>::operator[](size_t pos) {
  if (static_cast<int>(pos) >= size || pos >= static_cast<unsigned int>(-1))
    throw std::out_of_range("Error: indexing out of range");
  return items[(head + pos) % capacity];
}

template<typename T>
T& Deque<T>::Front() {
  if (head == -1)
    throw std::out_of_range("Front() called: index for Front() out of range");
  return items[head];
}

template<typename T>
T& Deque<T>::Back() {
  if (tail == -1)
    throw std::out_of_range("Back() called: index for Back() out of range");
  return items[tail];
}

template<typename T>
void Deque<T>::Clear(void) noexcept {
  std::unique_ptr<T[]> temp(new T[size]);
  std::swap(items, temp);
  head = tail = -1;
  size = 0;
}

template<typename T>
void Deque<T>::PushFront(const T &value) {
  if (size == capacity) {
    // resize
    Resize(capacity * 2);
  }
  if (head == -1) {
    head++;
    tail++;
  } else if (head == 0) {
    head = capacity - 1;
  } else {
    head--;
  }
  items[head] = value;
  size++;
}

template<typename T>
void Deque<T>::PushBack(const T &value) {
  if (size == capacity) {
    // resize
    Resize(capacity * 2);
  }
  if (head == -1) {
    head++;
    tail++;
  } else if (tail == capacity - 1) {
    tail = 0;
  } else {
    tail++;
  }
  items[tail] = value;
  size++;
}

template<typename T>
void Deque<T>::PopFront() {
  if (size == 0) {
    // Underflow error
    throw std::out_of_range("PopFront() called: index to pop out of range");
  }
  // if only 1 element in list
  if (tail == head) {
    head = -1;
    tail = -1;
  } else {
    // if head at end of list, wrap head to start of list
    if (head == capacity - 1)
      head = 0;
    else
      // Head is next element in list adj to old head after the pop has occurred
      head++;
  }
  size--;

  if (size <= capacity / 4)
    Resize(capacity / 2);
}

template<typename T>
void Deque<T>::PopBack() {
  if (size == 0) {
    // Underflow error
    throw std::out_of_range("PopBack() called: index to pop out of range");
  }
  // if only 1 element in list
  if (tail == 0) {
    head--;
    tail--;
  } else {
    // if tail at start of list, wrap tail to end of list
    if (tail == 0)
      tail = capacity - 1;
    else
      // Tail is prev element in list adj to old tail after pop has occurred
      tail--;
  }
  size--;

  if (size <= capacity / 4)
    Resize(capacity / 2);
}

#endif  // DEQUE_H_
