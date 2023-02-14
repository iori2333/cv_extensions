#pragma once

#include <Mat.h>
#include <type_traits>

template <typename T> constexpr auto py2cv(T &&value) -> decltype(auto) {
  using val_t = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<val_t, PyImage>) {
    return convertMat(std::forward<T>(value));
  } else {
    return std::forward<T>(value);
  }
}

template <typename T> constexpr auto cv2py(T &&value) -> decltype(auto) {
  using val_t = std::remove_cvref_t<T>;
  if constexpr (std::is_same_v<val_t, Image>) {
    return convertImage(std::forward<T>(value));
  } else {
    return std::forward<T>(value);
  }
}

template <typename T> struct as_py {
  using type = decltype(cv2py(std::declval<T>()));
};

template <typename T> struct as_cv {
  using type = decltype(py2cv(std::declval<T>()));
};

template <typename T> using as_py_t = typename as_py<T>::type;
template <typename T> using as_cv_t = typename as_cv<T>::type;

template <typename Ret, typename... Args>
auto pyFunction(Ret (*func)(Args...)) {
  return [func](const as_py_t<Args> &...args) -> as_py_t<Ret> {
    auto ret = func(py2cv(std::forward<decltype(args)>(args))...);
    return cv2py(ret);
  };
}
