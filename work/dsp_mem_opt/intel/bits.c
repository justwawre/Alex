/*
gcc -masm=intel -S
*/
struct bits
{
	unsigned int low : 2;
	unsigned int bits : 10;
	unsigned int high : 20;
	unsigned int normal;
};
unsigned int i;
int main()
{
	struct bits b;
	b.bits = i;
	b.normal = i;
	return 0;
}
