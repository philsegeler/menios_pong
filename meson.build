project('Oxygen Engine', ['cpp', 'c'], default_options : ['cpp_std=c++20', 'buildtype=debugoptimized'])

# declare sources and include direcctories for prerequisites
src = ['src/glad.c',
       'src/render_image.cpp']

internal_inc = include_directories('./include') 

# compile prerequisites as a static library. SDL2 not needed on emscripten
if meson.get_compiler('c', native : false).get_id() != 'emscripten'
    sdl2_dep = dependency('sdl2')
    dl_dep = dependency('dl', required : false)
    oe_lib = static_library('OxygenEngine', sources : src, dependencies : [sdl2_dep, dl_dep], include_directories : [internal_inc])
else
    thread_dep = dependency('threads')
    oe_lib = static_library('OxygenEngine', sources : src, dependencies : [thread_dep], include_directories : [internal_inc])
endif

oe_dep = declare_dependency(link_with : oe_lib, include_directories : [internal_inc])

# compile menios pong
if meson.get_compiler('c', native : false).get_id() != 'emscripten'
    sdl2_dep = dependency('sdl2')
    dl_dep = dependency('dl', required : false)
    executable('menios_pong', sources : 'main.cpp', dependencies : [oe_dep, sdl2_dep, dl_dep], include_directories : [internal_inc], win_subsystem: 'windows')
else
    executable('menios_pong', sources : 'main.cpp', dependencies : [oe_dep], include_directories : [internal_inc], win_subsystem: 'windows')
endif