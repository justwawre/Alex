int f()
{
    static int i = 2;
    return i;
}
int g()
{
    static int i = 3;
    return i;
}
int main()
{
    return f() + g();
}