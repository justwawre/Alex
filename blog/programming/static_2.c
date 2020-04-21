int f()
{
    static int i;
    return i;
}
int g()
{
    static int i;
    return i;
}
int main()
{
    return f() + g();
}