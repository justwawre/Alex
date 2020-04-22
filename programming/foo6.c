#include <dlfcn.h>
int i;
void (*bar)(void);
int main()
{
    i = 1;
    void *handle = dlopen("./libbar.so", RTLD_LAZY);
    if (!handle)
    {
        return -1;
    }
    bar = dlsym(handle, "bar");
    if (dlerror())
    {
        return -2;
    }

    bar();
    if (dlclose(handle) < 0)
    {
        return -3;
    }
    return 0;
}