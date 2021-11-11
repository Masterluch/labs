// Copyright 2021 Masterluch <atim2203@gmail.com>

#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_

#include <iostream>
#include <utility>
#include "ControlBlock.hpp"

template <typename T>
class SharedPtr {
 private:
  T* _ptr;
  ControlBlock* _control_block;

 public:
  SharedPtr() : _ptr(nullptr) {
      _control_block = new ControlBlock;
      _control_block->_link_counter++;
      }

  explicit SharedPtr(T* ptr) : _ptr(ptr) {
    _control_block = new ControlBlock;
    _control_block->_link_counter++;
  }

  SharedPtr(const SharedPtr& r)
      : _ptr(r._ptr), _control_block(r._control_block) {
    _control_block->_link_counter++;
  }

  SharedPtr(SharedPtr&& r) : _ptr(r._ptr), _control_block(r._control_block) {
    _control_block->_link_counter++;
  }

  ~SharedPtr() {
    if (_control_block->_link_counter == 1) {
      delete _ptr;
      delete _control_block;
    } else {
      _control_block->_link_counter--;
    }
  }

  auto operator=(const SharedPtr& r) {
    if (&r == this) {
      return *this;
    }

    if (_control_block->_link_counter == 1) {
      delete _ptr;
      delete _control_block;
    } else {
      _control_block->_link_counter--;
    }

    _ptr = r._ptr;
    _control_block = r._control_block;
    _control_block->_link_counter++;

    return *this;
  }

  auto operator=(SharedPtr&& r) {
    if (r._ptr == _ptr) {
      return *this;
    }

    if (_control_block->_link_counter == 1) {
      delete _ptr;
      delete _control_block;
    } else {
      _control_block->_link_counter--;
    }

    _ptr = r._ptr;
    _control_block = r._control_block;
    _control_block->_link_counter++;

    return *this;
  }

  operator bool() const { return _ptr != nullptr ? true : false; }
  auto operator*() const { return *_ptr; }
  auto operator->() const { return _ptr; }

  auto get() { return _ptr; }
  void reset() {
    if (_control_block->_link_counter == 1) {
      delete _ptr;
      delete _control_block;
    } else {
      _control_block->_link_counter--;
    }

    _ptr = nullptr;
    _control_block = new ControlBlock;
    _control_block->_link_counter++;
  }
  void reset(T* ptr) {
    if (_control_block->_link_counter == 1) {
      delete _ptr;
      delete _control_block;
    } else {
      _control_block->_link_counter--;
    }

    _ptr = ptr;
    _control_block = new ControlBlock;
    _control_block->_link_counter++;
  }
  void swap(SharedPtr& r) {
    T* ptr_buffer = r._ptr;
    ControlBlock* control_block_buffer = r._control_block;

    r._ptr = _ptr;
    r._control_block = _control_block;
    _ptr = ptr_buffer;
    _control_block = control_block_buffer;
  }

  auto use_count() const { return _control_block->_link_counter.load(); }
};

#endif  // INCLUDE_SHAREDPTR_HPP_
