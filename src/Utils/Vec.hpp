#pragma once

#include <functional>
#include <iostream>
#include <memory>

namespace Vec {
template <typename T>
void remove_vec_element_if(std::vector<T> &vec,
                           std::function<bool(T)> condition,
                           std::function<void(T)> finish_function) {
  for (auto it = vec.begin(); it != vec.end();) {
    if (condition(*it)) {
      finish_function(*it);
      it = vec.erase(it);
      // erase returns the next iterator
    } else {
      ++it; // only increment if not erasing
    }
  }
}
template <typename T>
void remove_vec_element(std::vector<std::unique_ptr<T>> &vec,
                        std::unique_ptr<T> &element,
                        std::function<void()> finish_function) {
  for (auto it = vec.begin(); it != vec.end();) {
    if (*it == element) {
      finish_function();
      it = vec.erase(it); // erase returns the next iterator
    } else {
      ++it; // only increment if not erasing
    }
  }
}
} // namespace Vec
