#include <iostream>
#include <dlfcn.h>

#include "gloop.hpp"

int main()
{
    void* handle = dlopen("libengine.so", RTLD_LAZY);
    if (!handle)
    {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return 1;
    }

    potEngine::gloop* (*create_t)();
    void (*destroy_t)(potEngine::gloop*);

    create_t = (potEngine::gloop* (*)())dlsym(handle, "entry_point");
    const char* dlsym_error = dlerror();
    if (dlsym_error)
    {
        std::cerr << "Cannot load symbol create: " << dlsym_error << '\n';
        dlclose(handle);
        return 1;
    }

    destroy_t = (void (*)(potEngine::gloop*))dlsym(handle, "delete_point");
    dlsym_error = dlerror();
    if (dlsym_error)
    {
        std::cerr << "Cannot load symbol destroy: " << dlsym_error << '\n';
        dlclose(handle);
        return 1;
    }

    potEngine::gloop* gloop = (potEngine::gloop*)create_t();
    gloop->mainPotEngine();
    destroy_t(gloop);

    return 0;
}