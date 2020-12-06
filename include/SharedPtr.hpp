// Copyright 2020 MIX-1 <danilonil1@yandex.ru>

#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_

#include <string>
#include <atomic>
#include <utility>

using std :: atomic;

template <typename T>
struct Counter {
 public:
  explicit Counter(T* p) : ptr(p), counter(1) {}

  void AddCounter() {++counter;}

  void Clean() {
    if(!--counter) {
      ptr = nullptr;
      delete this;
    }
  }

  size_t get() {return counter;}

 private:
  T *ptr;

  atomic<size_t> counter;
};

template <typename T>
class SharedPtr {
 public:
  SharedPtr() {
    ptr = nullptr;
    counter = new Counter<T>(nullptr);
  }

  explicit SharedPtr(T* p) : ptr(p), counter(new Counter<T>(p)) {}

  SharedPtr(const SharedPtr& r) {
    if (std::is_move_constructible<T>::value) {
      ptr = r.ptr;
      counter = r.counter;
      counter->AddCounter();
    } else {
      throw std::runtime_error("Type not constructible.");
    }
  }

  SharedPtr(SharedPtr&& r) {
    if (std::is_move_assignable<T>::value) {
      std::swap(ptr, r.ptr);
      std::swap(counter, r.counter);
    } else {
      throw std::runtime_error("Type not assignable.");
    }
  }

  ~SharedPtr() {
    counter->Clean();
  }

  auto operator= (const SharedPtr& r) -> SharedPtr& {
    if (std::is_move_constructible<T>::value && &r != this) {
      counter->Clean();
      ptr = r.ptr;
      counter = r.counter;
      counter->AddCounter();
    } else if (&r == this) {
      std::cout << "Object equal to this\n";
    } else {
      throw std::runtime_error("Type not constructible");
    }
    return *this;
  }

  auto operator= (SharedPtr&& r) -> SharedPtr& {
    if (std::is_move_assignable<T>::value && &r != this) {
      std::swap(ptr, r.ptr);
      std::swap(counter, r.counter);
    } else if (&r == this) {
      std::cout << "Object equal to this\n";
    } else {
      throw std::runtime_error("Type not assignable.");
    }
    return *this;
  }

  explicit operator bool() const {
    return (ptr != nullptr);
  }

  auto operator*() const -> T& {return *ptr;}

  auto operator->() const -> T* {return ptr;}

  auto get() -> T* {return ptr;}

  void swap(SharedPtr& r) {
    std::swap(ptr, r.ptr);
    std::swap(counter, r.counter);
  }
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект

  auto use_count() const -> size_t {
    if(ptr != nullptr){
      return counter->get();
    } else {
      return 0;
    }
  }

 private:
  T *ptr;

  Counter<T>* counter;
};



#endif // INCLUDE_SHAREDPTR_HPP_
