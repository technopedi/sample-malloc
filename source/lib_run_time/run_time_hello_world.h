#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE  extern "C" int func_run_time();
EMSCRIPTEN_KEEPALIVE extern "C" void testFunc(std::shared_ptr<int>& ptr, std::vector<int>& v);

