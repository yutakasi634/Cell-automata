#ifndef UTIL_TEST_TOW_DIMENSION_MATRIX
#define UTIL_TEST_TOW_DIMENSION_MATRIX

#include <iostream>
#include "array_matrix.hpp"

using namespace std;
using namespace Utilpack;

int main()
{
    cout  << "generate array_matrix<int, 0, 0>" << endl;    
    array_matrix<int, 0, 0> empty_matrix;
    cout << "judge empty = " << boolalpha << empty_matrix.empty() << endl;
    const size_t column_Num{3}, row_Num{4};
    cout  << "generate array_matrix<int, "
	  << column_Num << ", " << row_Num << ">" << endl;
    array_matrix<int, row_Num, column_Num> test_matrix;
    cout << "judge empty = " << boolalpha << test_matrix.empty() << endl;
    cout << "fill with 1." << endl;
    test_matrix.fill(1);
    cout << "elem num = " << test_matrix.size() << endl;
    cout << "row num = " << test_matrix.row_num() << endl;
    cout << "column num = " << test_matrix.column_num() << endl;

    cout << "access and fill with rowcolumn num" << endl;
    for(size_t i = 0; i < row_Num; ++i){
	for(size_t j = 0; j < column_Num; ++j)
	    test_matrix.at(i,j) = i * 10 + j;
    }
    
    cout << "access and output." << endl;
    for(size_t i = 0; i < row_Num; ++i){
	for(size_t j = 0; j < column_Num; ++j)
	    cout << test_matrix.at(i,j) << " ";
	cout << endl;
    }

    cout << "access with for each." << endl;
    for(auto elem : test_matrix)
	cout << elem << " ";
    cout << endl;

    cout << "test rowbegin() and rowend()." << endl;
    for(array_matrix<int, row_Num, column_Num>::row_iterator itr =
	    test_matrix.rowbegin(2);
	itr != (test_matrix.rowend(2)); ++itr)
	cout << *itr << " ";
    cout << endl;

    cout << "test columnbegin() and columnend() for const matrix." << endl;
    for(array_matrix<int, row_Num, column_Num>::column_iterator itr =
	    test_matrix.columnbegin(2);
	itr != (test_matrix.columnend(2)); ++itr)
	cout << *itr << " ";
    cout << endl;
    
    return 0;
}

#endif /*UTIL-TEST-TOW-DIMENSION-MATRIX*/
