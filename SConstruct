from scons_cfg import *
COMMON_CXX_FLAGS = "-std=c++1y -g"

ROCKET_LIBS = ['RocketCore', 'RocketControls', 'RocketDebugger', ]
GENERAL_LIBS = ['stdc++', 'pthread', 'python2.7', 'dl', ]
GL_LIBS = ['GL', 'GLEW', 'GLU']
BOOST_LIBS = ['boost_timer', 'boost_filesystem', 'boost_system', 'boost_thread', 'boost_python', ]
SDL_LIBS = ['SDL2', 'SDL2_ttf', 'SDL2_image', ]
BULLET_LIBS = ['BulletCollision', 'BulletSoftBody', 'BulletDynamics', 'LinearMath']

ALL_LIBS = GENERAL_LIBS + GL_LIBS + BOOST_LIBS + SDL_LIBS + ROCKET_LIBS + BULLET_LIBS


engine_src = ENGINE_PATH + '/src/'

engine_deps = [
    Glob(engine_src + 'resources/*.cpp'),
    Glob(engine_src + 'libload/*.cpp'),
    Glob(engine_src + 'types/*.cpp'),
    Glob(engine_src + 'misc/*.cpp'),
    Glob(engine_src + 'world/*.cpp'),
    Glob(engine_src + 'entities/*.cpp'),
    Glob(engine_src + 'time/*.cpp'),
    Glob(engine_src + 'physics/*.cpp'),
    Glob(engine_src + 'config/*.cpp'),
    Glob(engine_src + 'python/*.cpp'),
Glob(engine_src + 'renderer/*.cpp'),
    engine_src + 'io/SDLIOInterface.cpp',
Glob(engine_src + 'ui/*.cpp'),
Glob(engine_src + 'ui/librocket_interfaces/*.cpp'),
]

main_modules = [
   Glob('src/*.cpp'),
] + engine_deps

env = Environment(CPPPATH=[
    '/usr/include/python2.7',
    '/usr/include/bullet',
    engine_src,
    './src',
])

env.Program('./level_editor', main_modules, LIBS=ALL_LIBS, LIBPATH='.', CXXFLAGS=COMMON_CXX_FLAGS, )