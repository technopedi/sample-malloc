#rm -rf run_time_hello_world.wasm static_hello_world.a static_hello_world.o main.html main.wasm main.js main.wasm  main.worker.js &&
#
#emcc  -g -DDEBUG -O0 source/lib_static/static_hello_world.cpp  -fwasm-exceptions -pthread -c -fPIC  -o static_hello_world.o
#emar rcs static_hello_world.a static_hello_world.o 
#
emcc -g -DDEBUG -O0 -std=c++14 -s SIDE_MODULE=2 -fwasm-exceptions -pthread source/lib_run_time/run_time_hello_world.cpp static_hello_world.a -o run_time_hello_world.wasm &&

export EMCC_FORCE_STDLIBS=1

emcc -g -DDEBUG -O0 -DDYLINK_DEBUG -pthread  -s PROXY_TO_PTHREAD  -fwasm-exceptions -s PROXY_TO_PTHREAD --bind -s WASM_BIGINT=1 -s INITIAL_MEMORY=2080309248 -s ALLOW_MEMORY_GROWTH=1 source/lib_main/hello_world.cpp -s MAIN_MODULE=2  -sNO_AUTOLOAD_DYLIBS run_time_hello_world.wasm  -o main.html
