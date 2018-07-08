fips_begin_module(Sova)
    fips_vs_warning_level(3)
    fips_files(
            Sova.h Sova.cpp
            PNGLoader.h PNGLoader.cpp
            shaders.h shaders.cpp)
    fips_deps(Core IO Gfx Assets HttpFS LocalFS lodepng)
fips_end_module()