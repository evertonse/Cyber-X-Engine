#include <vector>
#include <iostream>

using namespace std;

template<class T>
struct A
{
	vector <T> v;
	static	vector <T> vec;

	void emplace() {
		static_cast<T*>(this)->implementation();
	}
};

template<class T>
vector<T> A<T>::vec{};


template<class T>
auto add(T a)
{
	T x;
	A<T>::vec.push_back(a);
	a.emplace();
}


struct T : A<T> {
	void implementation()
	{
		cout << "T implementation" << "\n";
	}
};

int main()
{
	T t; 
	add<T>(t);
}
