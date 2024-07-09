/*
** EPITECH PROJECT, 2024
** synthese
** File description:
** Zipper.inl
*/

#pragma once
#include "ZipperIt.hpp"
#include "Zipper.hpp"

template <class... Containers>
Zipper<Containers...>::Zipper(Containers&... cs)
    : _begin(std::make_tuple(cs.begin()...)),
      _end(std::make_tuple(cs.end()...)),
      _size(_compute_size(cs...)) {}

template <class... Containers>
Zipper<Containers...>::Zipper(pred_type&& pred, Containers&... cs)
    : _begin(std::make_tuple(cs.begin()...)),
      _end(std::make_tuple(cs.end()...)),
      _size(_compute_size(cs...)),
      _pred(std::move(pred)) {}

template <class... Containers>
auto Zipper<Containers...>::begin() -> iterator {
    return iterator(_begin, _size);
}

template <class... Containers>
auto Zipper<Containers...>::end() -> iterator {
    return iterator(_end, _size);
}

template <class... Containers>
auto Zipper<Containers...>::_compute_size(Containers&... containers) -> std::size_t {
    return std::min({ containers.size()... });
}

template <class... Containers>
auto Zipper<Containers...>::_compute_end(Containers&... containers) -> iterator_tuple {
    return std::make_tuple(containers.end()...);
}
