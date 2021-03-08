#include <zip/ZipEngine.hpp>

#include <vector>

struct A
{
	void setG() { g = 1; }
	int g = 0;
};

struct B : A
{
	int c = 3;
};

int main()
{
	zip::ZipEngine z;

	while (true)
		z.application.update();

	return 0;
}
