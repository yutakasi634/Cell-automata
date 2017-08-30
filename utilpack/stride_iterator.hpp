#ifndef UTIL_STRIDE_ITERATOR
#define UTIL_STRIDE_ITERATOR

#include <iterator>

namespace Utilpack
{


template<typename value_T, std::size_t stride, typename container_T>
class stride_iterator
{
    friend container_T;
    
  public:
    using value_type            = value_T;
    using difference_type	= std::ptrdiff_t;
    using pointer               = value_type*;
    using reference		= value_type&;
    using iterator_category	= std::random_access_iterator_tag;
    using self_type             = stride_iterator<value_type, stride, container_T>;
    
    //for foward iterator
    reference operator*() const
    {
	return *elem_p;
    }
    
    pointer operator->()
    {
	return elem_p;
    }

    const pointer operator->() const
    {
	return elem_p;
    }
    
    
    stride_iterator& operator++()
    {
	elem_p += stride;
	return *this;
    }
    
    stride_iterator operator++(int)
    {
	stride_iterator result(elem_p);
	++elem_p;
	return result;
    }

    //for bidirectional iterator
    stride_iterator& operator--()
    {
	elem_p -= stride;
	return *this;
    }
    stride_iterator operator--(int)
    {
	stride_iterator result(elem_p);
	--elem_p;
	return result;
    }

    //for random access iterator
    reference operator[](difference_type arg) const
    {
	return *(elem_p + (arg * stride));
    }
    
    stride_iterator& operator+=(const difference_type arg)
    {
	elem_p += stride * arg;
	return *this;
    }
    stride_iterator& operator-=(const difference_type arg)
    {
	elem_p -= stride * arg;
	return *this;
    }

    template<typename T, std::size_t N, typename C>
    friend bool operator== (const stride_iterator<T,N,C>&,
			    const stride_iterator<T,N,C>&);
    template<typename T, std::size_t N, typename C>
    friend bool operator!= (const stride_iterator<T,N,C>&,
			    const stride_iterator<T,N,C>&);
    template<typename T, std::size_t N, typename C>
    friend bool operator< (const stride_iterator<T,N,C>&,
			   const stride_iterator<T,N,C>&);
    template<typename T, std::size_t N, typename C>
    friend bool operator> (const stride_iterator<T,N,C>&,
			   const stride_iterator<T,N,C>&);
    template<typename T, std::size_t N, typename C>
    friend bool operator<= (const stride_iterator<T,N,C>&,
			    const stride_iterator<T,N,C>&);
    template<typename T, std::size_t N, typename C>
    friend bool operator>= (const stride_iterator<T,N,C>&,
			    const stride_iterator<T,N,C>&);

    template<typename T, std::size_t N, typename C>
    friend stride_iterator<T,N,C> operator+ (const difference_type,
					     const stride_iterator<T,N,C>&);
    template<typename T, std::size_t N, typename C>
    friend stride_iterator<T,N,C> operator+ (const stride_iterator<T,N,C>&,
					     const difference_type);
    template<typename T, std::size_t N, typename C>
    friend stride_iterator<T,N,C> operator- (const stride_iterator<T,N,C>&,
					     const difference_type);
    template<typename T, std::size_t N, typename C>
    friend difference_type operator- (const stride_iterator<T,N,C>&,
				      const stride_iterator<T,N,C>&);
    
  private:
    pointer elem_p;
    
    stride_iterator()
    { elem_p = nullptr; }

    stride_iterator(pointer value_p)
    { elem_p = value_p; }    
    
};

//friend operator for stride_iterator

template<typename value_T, std::size_t stride, typename container_T>
bool operator==(const stride_iterator<value_T, stride, container_T>& one,
		const stride_iterator<value_T, stride, container_T>& two)
{
    return one.elem_p == two.elem_p;
}

template<typename value_T, std::size_t stride, typename container_T>
bool operator!=(const stride_iterator<value_T, stride, container_T>& one,
		const stride_iterator<value_T, stride, container_T>& two)
{
    return !(one == two);
}

template<typename value_T, std::size_t stride, typename container_T>
bool operator<(const stride_iterator<value_T, stride, container_T>& one,
	       const stride_iterator<value_T, stride, container_T>& two)
{
    return one.elem_p < two.elem_p;
}

template<typename value_T, std::size_t stride, typename container_T>
bool operator>(const stride_iterator<value_T, stride, container_T>& one,
	       const stride_iterator<value_T, stride, container_T>& two)
{
    return one.elem_p > two.elem_p;
}

template<typename value_T, std::size_t stride, typename container_T>
bool operator<=(const stride_iterator<value_T, stride, container_T>& one,
		const stride_iterator<value_T, stride, container_T>& two)
{
    return !(one > two);
}

template<typename value_T, std::size_t stride, typename container_T>
bool operator>=(const stride_iterator<value_T, stride, container_T>& one,
		const stride_iterator<value_T, stride, container_T>& two){
    return !(one < two);
}


template<typename value_T, std::size_t stride, typename container_T>
stride_iterator<value_T, stride, container_T> operator+(
    const typename
    stride_iterator<value_T, stride, container_T>::difference_type p_diff,
    const stride_iterator<value_T, stride, container_T>& arg_itr)
{
    return arg_itr.elem_p + p_diff * stride;
}

template<typename value_T, std::size_t stride, typename container_T>
stride_iterator<value_T, stride, container_T> operator+(
    const stride_iterator<value_T, stride, container_T>& arg_itr,
    const typename
    stride_iterator<value_T, stride, container_T>::difference_type p_diff)
{
    return p_diff + arg_itr;
}

template<typename value_T, std::size_t stride, typename container_T>
stride_iterator<value_T, stride, container_T> operator-(
    const stride_iterator<value_T, stride, container_T>& arg_itr,
    const typename
    stride_iterator<value_T, stride, container_T>::difference_type p_diff) 
{
    return arg_itr.elem_p - p_diff * stride;
}

template<typename value_T, std::size_t stride, typename container_T>
typename stride_iterator<value_T, stride, container_T>::difference_type operator-(
    const stride_iterator<value_T, stride, container_T>& one,
    const stride_iterator<value_T, stride, container_T>& two)
{
    auto return_value = one.elem_p - two.elem_p;
    if(return_value % stride != 0)
	throw std::invalid_argument("stride iterators of arguments are not correspond.");
    return return_value / stride;
}
    
} /* Utilpack */

#endif
