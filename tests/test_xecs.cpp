#include "xecs.cpp"
#include <iostream>

using namespace std;

auto test_resgistry_create_destroy() {
	Registry r;
	auto e1 = r.create();
	auto e2 = r.create();
	assert(e2 == 1);
	r.destroy(e2);
	auto e3 = r.create();
	assert(e3 == 1);
	auto e4 = r.create();
	assert(e4 == 2);
	r.destroy(e1);
	auto e5 = r.create();
	assert(e5 == 0);
}

struct vel : Component<vel> {
	int x, y;
	vel(int x, int y) :x(x), y(y) {};
};
struct pos : Component<pos> {
	int x, y;
	pos(int x, int y) :x(x), y(y) {};
};	
struct vec2 : Component<vec2> {
	int x, y;
	vec2(int x, int y) :x(x), y(y) {};
};

auto test_resgistry_components() {

	Registry r;
	auto e1 = r.create();
	auto e2 = r.create();
	auto e3 = r.create();


	r.each( [&r](auto&& e) -> void {
		r.add<vec2>	(e,vec2{e, e});
		r.add<pos>	(e,pos{ e, e});
		r.add<vel>	(e,vel{ e, e });
	});
	for (auto& c : r.components<vec2>())
	{
		auto e = r.owner(c);
		cout <<  e << "\n";
		r.remove<vec2>(e);
	}
	assert(r.components<vec2>().size() == 0);
	
	for (auto& c : r.components<vec2>())
	{
		auto e = r.owner(c);
		cout <<  e << "\n";
		r.remove<vec2>(e);
	}
	assert(r.components<vec2>().size() == 0);
	|
}


int main() {
	test_resgistry_create_destroy();
	test_resgistry_components();
}