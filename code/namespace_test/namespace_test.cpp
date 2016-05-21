
namespace A
{
	namespace B
	{
		class C{};
		f(A::B::C c){}
	}
	
}

void f(A::B::C c){}

int main()
{
	f(A::B::C());
	return 0;
}