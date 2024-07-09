/*
** EPITECH PROJECT, 2024
** synthese
** File description:
** ZipperIt.hpp
*/

#pragma once
#include "Ecs.hpp"
#include <tuple>
#include <optional>
#include <functional>
#include <iterator>
#include <type_traits>

template <class... Containers>
class ZipperIterator {
    template <class Container>
    using iterator_t = decltype(std::begin(std::declval<Container&>()));

    template <class Container>
    using it_reference_t = typename iterator_t<Container>::reference;

public:
    using value_type = std::tuple<std::size_t, decltype(std::declval<it_reference_t<Containers>>().value())&...>;
    using reference = value_type;
    using iterator_category = std::input_iterator_tag;
    using iterator_tuple = std::tuple<iterator_t<Containers>...>;
    using pred_type = std::function<bool(const value_type&)>;

public:
    ZipperIterator(const iterator_tuple& it_tuple, std::size_t max);
    ZipperIterator(const iterator_tuple& it_tuple, std::size_t max, pred_type&& pred);
    ZipperIterator(const ZipperIterator& z);
    ~ZipperIterator() = default;

    auto operator++() -> ZipperIterator&;
    auto operator++(int) -> ZipperIterator;
    auto operator*() -> value_type;
    auto operator->() -> value_type;
    auto operator==(const ZipperIterator<Containers...>& rhs) -> bool;
    auto operator!=(const ZipperIterator<Containers...>& rhs) -> bool;

private:
    template <std::size_t... Is>
    auto incr_all(std::index_sequence<Is...>) -> void;
    template <std::size_t... Is>
    auto all_set(std::index_sequence<Is...>) -> bool;
    template <std::size_t... Is>
    auto to_value(std::index_sequence<Is...>) -> value_type;

private:
    iterator_tuple _current;
    std::size_t _max;
    std::size_t _idx;
    std::optional<pred_type> _pred;
    static constexpr auto _seq = std::index_sequence_for<Containers...>{};
};

#include "ZipperIt.inl"