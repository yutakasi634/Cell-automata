#ifndef UTIL-TOW-DIMENSION-MATRIX
#define UTIL-TOW-DIMENSION-MATRIX

#include <array>

namespace Utilpack
{

template<typename value_T, std::size_t row_Num, std::size_t culum_Num>
class array_matrix
{
    using value_type			= value_T;
    using pointer			= value_type*;
    using const_pointer			= const value_type*;
    using reference			= value_type&;
    using const_reference		= const value_type&;
    using iterator			= value_type*;
    using const_iterator		= const value_type*;
    using size_type			= std::size_t;
    using difference_type		= std::ptrdiff_t;
    using reverse_iterator		= std::reverse_iterator<iterator>;
    using const_reverse_iterator	= std::reverse_iterator<const_iterator>;

    array_traits():elem_Num(row_Num * culum_Num){};

    void fill(const value_type& i)
    {std::fill_n(begin(), size(), i); }

    //iterator
    iterator begin() noexcept
    { return content.begin(); }

    const_iterator begin() const noexcept
    { return content.cbegin(); }
    
    
  private:
    constexpr std::size_t elem_Num;
    std::array<value_type, elem_Num> content;    
}

} /* Utilpack */

#endif /*UTIL-TOW-DIMENSION-MATRIX*/

