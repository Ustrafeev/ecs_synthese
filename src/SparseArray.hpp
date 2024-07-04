/*
** EPITECH PROJECT, 2024
** synthese
** File description:
** SparseArray.hpp
*/

#pragma once
#include <optional>
#include <vector>

template <typename Component>
class SparseArray {
    public :
        using value_type = std::optional<Component> ; // optional component type
        using reference_type = value_type &;
        using const_reference_type = const value_type &;
        using container_t = std::vector<value_type>;
        using size_type = typename container_t :: size_type ;
        using iterator = typename container_t :: iterator ;
        using const_iterator = typename container_t :: const_iterator ;
    public :
        SparseArray();
        SparseArray(const SparseArray & other); // copy constructor
        SparseArray(SparseArray && other)noexcept; // move constructor
        ~SparseArray() = default;
        auto operator=(const SparseArray &other) -> SparseArray &; // copy assignment operator
        auto operator=( SparseArray && other ) noexcept -> SparseArray &; // move assignment operator
        auto operator[](size_t idx) -> reference_type ;
        auto operator[](size_t idx) const -> const_reference_type ;
        auto begin () -> iterator ;
        auto begin () const -> const_iterator ;
        auto cbegin () const -> const_iterator ;
        auto end () -> iterator ;
        auto end () const -> const_iterator ;
        auto cend () const -> const_iterator ;
        auto size () const -> size_type ;
        auto insert_at ( size_type pos , const Component & value ) -> reference_type ;
        auto insert_at ( size_type pos , Component && rvalue ) -> reference_type ;
        template <class ... Params >
        auto emplace_at ( size_type pos , Params &&... args ) -> reference_type ; // build the component object in - place .
        auto erase ( size_type pos ) -> void ;
        auto clear ( void ) -> void ;
    private :
        container_t _data ;
};

#include "SparseArray.inl"