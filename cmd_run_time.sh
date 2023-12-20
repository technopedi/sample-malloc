#rm -rf run_time_hello_world.wasm static_hello_world.a static_hello_world.o main.html main.wasm main.js main.wasm  main.worker.js &&
#
#emcc  -g -DDEBUG -O0 source/lib_static/static_hello_world.cpp  -fwasm-exceptions -pthread -c -fPIC  -o static_hello_world.o
#emar rcs static_hello_world.a static_hello_world.o 
#
emcc -g -DDEBUG -O0 --emit-symbol-map -std=c++14 -s SIDE_MODULE=2 -s WASM_BIGINT=1 -fwasm-exceptions -pthread -s ALLOW_MEMORY_GROWTH=1 \
 source/lib_run_time/run_time_hello_world.cpp static_hello_world.a -o run_time_hello_world.wasm &&

export EMCC_FORCE_STDLIBS=1

emcc -g -DDEBUG -O0 -DDYLINK_DEBUG -pthread  -s PROXY_TO_PTHREAD  -fwasm-exceptions -s PROXY_TO_PTHREAD --bind -s WASM_BIGINT=1 \
 -s INITIAL_MEMORY=2080309248 -s ALLOW_MEMORY_GROWTH=1 \
 source/lib_main/hello_world.cpp \
 -ferror-limit=0 --bind -s WASM_BIGINT=1 -s INITIAL_MEMORY=2080309248 -s ALLOW_MEMORY_GROWTH=1 \
		-s DEMANGLE_SUPPORT=1 \
		-s USE_SDL=2  -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 \
		-s FORCE_FILESYSTEM=1 -sDEFAULT_PTHREAD_STACK_SIZE=2MB -sSTACK_SIZE=5MB -sMAXIMUM_MEMORY=3968MB \
		-s EXPORTED_RUNTIME_METHODS='cwrap' -s ALLOW_TABLE_GROWTH=1 \
		-s MAIN_MODULE=2 -sNO_AUTOLOAD_DYLIBS --use-preload-plugins \
		-s PTHREAD_POOL_SIZE=navigator.hardwareConcurrency -s PTHREAD_POOL_SIZE_STRICT=0 -s PTHREAD_POOL_DELAY_LOAD=1 \
		-s EXCEPTION_STACK_TRACES=1 \
  run_time_hello_world.wasm  -o main.html
