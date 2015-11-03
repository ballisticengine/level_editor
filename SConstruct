from scons_cfg import *
COMMON_CXX_FLAGS = "-std=c++1y -g -ggdb -fPIC"

ROCKET_LIBS = ['RocketCore', 'RocketControls', 'RocketDebugger', ]
GENERAL_LIBS = ['stdc++', 'pthread', 'python2.7', 'dl', ]
GL_LIBS = ['GL', 'GLEW', 'GLU']
BOOST_LIBS = ['boost_timer', 'boost_filesystem', 'boost_system', 'boost_thread', 'boost_python', ]
SDL_LIBS = ['SDL2', 'SDL2_ttf', 'SDL2_image', ]
BULLET_LIBS = ['BulletCollision', 'BulletSoftBody', 'BulletDynamics', 'LinearMath']

ALL_LIBS = GENERAL_LIBS + GL_LIBS + BOOST_LIBS + SDL_LIBS + ROCKET_LIBS + BULLET_LIBS 


engine_src = ENGINE_PATH + '/src/'



engine_deps = [
       
   
]

main_modules = [
   Glob('src/*.cpp'),
    Glob('src/listeners/*.cpp'),
Glob('src/rendering/*.cpp'),
Glob('src/state_handlers/*.cpp'),
] + engine_deps

env = Environment(CPPPATH=[
    '/usr/include/python2.7',
    '/usr/include/bullet',
    engine_src,
    './src',
])

lib = File(ENGINE_PATH+'/bin/libengine.so')

env.Append(LINKFLAGS=['-rdynamic'])
env.Program('./bin/level_editor', main_modules, LIBS=ALL_LIBS+[lib], CXXFLAGS=COMMON_CXX_FLAGS, )


