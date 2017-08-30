#include <iostream>
#include <array>
#include "stride_iterator.hpp"

using namespace std;
using namespace Utilpack;

template<size_t size>
class test_array
{
  public:
    test_array()
    {
	for(size_t i = 0; i < size; ++i)
	    inter_array.at(i) = i;
    }

    stride_iterator<int, 2, test_array<size> > s2_begin()
    { return stride_iterator<int, 2, test_array<size> >(inter_array.begin());}

    stride_iterator<int, 2, test_array<size> > s2_end()
    { return inter_array.end();}

    stride_iterator<int, 3, test_array<size> > s3_begin()
    { return stride_iterator<int, 3, test_array<size> >(inter_array.begin());}

    stride_iterator<int, 3, test_array<size> > s3_end()
    { return inter_array.end();}

    stride_iterator<int, 7, test_array<size> > s7_begin()
    { return stride_iterator<int, 7, test_array<size> >(inter_array.begin());}

    stride_iterator<int, 7, test_array<size> > s7_end()
    { return inter_array.end();}
    
  private:
    array<int, size> inter_array;
};

int main(){
    constexpr size_t ar_size(28);
    test_array<ar_size> tes_ar;
    cout << "test for stride_iterator<int, 2, test_array<ar_size> >." << endl;
    for(stride_iterator<int, 2, test_array<ar_size> > itr = tes_ar.s2_begin();
	itr < tes_ar.s2_end(); ++itr)
	cout << *itr << " ";
    cout << endl;

    cout << "test for stride_iterator<int, 3, test_array<ar_size> >." << endl;
    for(stride_iterator<int, 3, test_array<ar_size> > itr = tes_ar.s3_begin();
    	itr < tes_ar.s3_end(); ++itr)
    	cout << *itr << " ";
    cout << endl;

    //for loop based on != is not recomended.
    cout << "test for stride_iterator<int, 7, test_array<ar_size> >." << endl;
    for(stride_iterator<int, 7, test_array<ar_size> > itr = tes_ar.s7_begin();
	itr != tes_ar.s7_end(); ++itr)
	cout << *itr << " ";
    cout << endl;

    stride_iterator<int, 3, test_array<ar_size> > g_itr = tes_ar.s3_begin();
    cout << "test for new stride_iterator<int, 3, test_array<ar_size> > operator +=."
	 << endl << "*(g_itr += 3) is " << *(g_itr += 3) << endl;
    cout << "test for stride_iterator<int, 3, test_array<ar_size> > operator -=."
	 << endl << "*(g_itr -= 2) is " << *(g_itr -= 2) << endl;
    cout << "test for stride_iterator<int, 3, test_array<ar_size> > operator ++(int)."
	 << endl << "*(g_itr++) is " << *(g_itr++) << endl
	 << "*g_itr is " << *g_itr << endl;
    cout << "test for stride_iterator<int, 3, test_array<ar_size> > operator --(int)."
	 << endl << "*(g_itr--) is " << *(g_itr--) << endl
	 << "*g_itr is " << *g_itr << endl;
    cout << "test for stride_iterator<int, 3, test_array<ar_size> > operator -= []."
	 << endl << "g_itr[2] is " << g_itr[2] << endl;
    
    return 0;
}
