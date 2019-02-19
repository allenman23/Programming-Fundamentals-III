//Allen Lim

#include <iostream>
#include <string>
#include <algorithm>

template <class ElementType>
ElementType maxArray(ElementType array[], int first, int last);

int main()
{
   double x[] = {1.1, 6.6, 3.3, 4.4, 2.2};
   std::cout << "max of (1.1, 6.6, 3.3, 4.4, 2.2): " << maxArray(x, 0, (sizeof(x) / sizeof(x[0])) - 1) << "\n";
   int num[] = {1, 2, 5, 4};
   std::cout << "max of (1, 2, 5, 4): " << maxArray(num, 0, (sizeof(num) / sizeof(num[0])) - 1) << "\n";
   std::string s[] = {"zz", "aa", "bb", "cc"};
   std::cout << "max of (zz, aa, bb, cc): " << maxArray(s, 0, (sizeof(s) / sizeof(s[0])) - 1) << "\n";
	return 0;
}

template<class ElementType>
ElementType maxArray(ElementType array[], int first, int last)
{
	int mid = (first + last) / 2;
	if (first == last)
		return array[first];
	else
		return std::max(maxArray(array, first, mid), maxArray(array, mid + 1, last));
}
