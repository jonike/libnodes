#pragma once

#include "libnodes/algorithms.h"
#include <type_traits>
#include <tuple>
#include <array>

namespace nodes {


template< std::int64_t S = 0, std::int64_t E = -1 >
struct xlet_selector {
    algorithms::index_constant<S> start;
    algorithms::index_constant<E> end;
    static constexpr std::int64_t start_value = S;
    static constexpr std::int64_t end_value = E;

    template< std::int64_t Te >
    using to = xlet_selector<S, Te>;
};

template< std::int64_t S = 0 >
using from = xlet_selector<S>;


template< typename T, std::int64_t S = 0, std::int64_t E = -1 >
class xlet_iterator
{
public:
    //! the underlying container for Xlets, either a std::tuple or std::array
    typedef T container_type;

protected:

    xlet_selector<S, E> mSelected;
    container_type &mXlets;

public:
    xlet_iterator( container_type &xlets ) : mXlets( xlets ) {};


    //! the number of Xlets
    static constexpr std::size_t size = std::tuple_size< container_type >::value;

    //! get the type of an Xlet at index \a I
    template< std::size_t I >
    using type = typename std::tuple_element< I, container_type >::type;

    //! returns a reference to the Xlet at index \a I
    template< std::size_t I >
    type< I > &get() { return std::get< I >( mXlets ); }

    //! returns a const reference to the Xlet at index \a I
    template< std::size_t I >
    type< I > const &get() const { return std::get< I >( mXlets ); }

    //! iterate over all xlets, starting at index \a i
    template< typename F >
    void each( F &fn )
    {
        return algorithms::call( mXlets, fn, mSelected.start, mSelected.end );
    }

    //! iterate over all xlets, starting at index \a i
    template< typename F >
    void each( F &&fn )
    {
        return algorithms::call( mXlets, fn, mSelected.start, mSelected.end );
    }

    //! iterate over all xlets, passing the index of the element, starting at
    //! index \a i
    template< typename F >
    void each_with_index( F &fn )
    {
        return algorithms::call_with_index( mXlets, fn, mSelected.start,
                                            mSelected.end );
    }

    //! iterate over all xlets, passing the index of the element, starting at
    //! index \a i
    template< typename F >
    void each_with_index( F &&fn )
    {
        return algorithms::call_with_index( mXlets, fn, mSelected.start,
                                            mSelected.end );
    }


    template<
            typename Ts,
            typename Ti = xlet_iterator<container_type, Ts::start_value, Ts::end_value>
    >
    Ti operator[]( const Ts &sel )
    {
        return Ti{mXlets};
    }
};

template< typename T, std::int64_t S = 0, std::int64_t E = -1 >
class uniform_xlet_iterator : public xlet_iterator< T, S, E >
{
public:
    uniform_xlet_iterator( T &xlets ) : xlet_iterator< T, S, E >( xlets ) {}

    //! returns an iterator to the first element, if the container type allows
    inline typename T::iterator begin() noexcept { return this->mXlets.begin(); }

    //! returns a const iterator to the first element, if the container type allows
    inline typename T::const_iterator
    cbegin() noexcept { return this->mXlets.cbegin(); }

    //! returns an iterator to the element following the last element, if the container type allows
    inline typename T::iterator end() noexcept { return this->mXlets.end(); }

    //! returns a const iterator to the element following the last element, if the container type allows
    inline typename T::const_iterator cend() noexcept { return this->mXlets.cend(); }

    //! Returns a reference to the element at specified location pos, with bounds checking if the container type allows
    inline typename T::reference
    at( typename T::size_type i ) { return this->mXlets.at( i ); }
};

}