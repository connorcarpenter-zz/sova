fips_begin_module(Sova)
    fips_vs_warning_level(3)
    fips_files(
            Sova.h Sova.cpp
            App.h App.cpp
            Container.h Container.cpp
            Sprite.h Sprite.cpp
            Camera.h Camera.cpp
            Viewport.h Viewport.cpp
            Loader.h Loader.cpp

            Internal/OryolApp.h Internal/OryolApp.cpp
            Internal/PNGLoader.h Internal/PNGLoader.cpp
            Internal/shaders.h Internal/shaders.cpp)
    fips_deps(Core IO Gfx Assets HttpFS LocalFS lodepng)
fips_end_module()