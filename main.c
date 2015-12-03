
int main()
{
	struct my_int{
		int b : 17;
		int a : 2;
	}salut;
	salut.b = 1;
	salut.a = 0;
	printf("%d\n", salut.b);
	printf("%d\n", salut.a);
	salut.b >>= 1;
	printf("%d\n", salut.b);
	printf("%d\n", salut.a);
}
