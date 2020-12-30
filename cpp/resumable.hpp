#pragma once
#include <cassert>
#include <experimental/coroutine>
#include <iostream>


struct resumable_noinc {
  struct promise_type {
    using coro_handle = std::experimental::coroutine_handle<promise_type>;
    auto get_return_object() { return coro_handle::from_promise(*this); }
    auto initial_suspend() { return std::experimental::suspend_always(); }
    auto final_suspend() { return std::experimental::suspend_always(); }
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
  };

  using coro_handle = std::experimental::coroutine_handle<promise_type>;
  resumable_noinc(coro_handle handle) : handle_(handle) { assert(handle); }
  resumable_noinc(resumable_noinc &) = delete;
  resumable_noinc(resumable_noinc &&rhs) : handle_(rhs.handle_) { rhs.handle_ = nullptr; }
  bool resume() {
    if (!handle_.done())
      handle_.resume();
    return !handle_.done();
  }
  ~resumable_noinc() {
    if (handle_)
      handle_.destroy();
  }
  coro_handle handle() {
    coro_handle h = handle_;
    handle_ = nullptr;
    return h;
  }

private:
  coro_handle handle_;
};