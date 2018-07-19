fips_begin_module(Sova)
    fips_vs_warning_level(3)
    fips_files(
            SovaMain.h SovaMain.cpp
            App.h App.cpp
            Loader.h Loader.cpp
            Log.h Log.cpp
            Input.h Input.cpp

            Graphics/Container.h Graphics/Container.cpp
            Graphics/Sprite.h Graphics/Sprite.cpp
            Graphics/Camera.h Graphics/Camera.cpp
            Graphics/Viewport.h Graphics/Viewport.cpp
            Graphics/DisplayObject.h Graphics/DisplayObject.cpp

            Math/Point.h Math/Point.cpp
            Math/Math.h Math/Math.cpp

            Network/Websocket.h Network/Websocket.cpp
            Network/HttpRequest.h Network/HttpRequest.cpp
            Network/HttpResponse.h Network/HttpResponse.cpp

            Common/List.h
            Common/String.cpp
            Common/String.h

            References/Ref.h References/IRef.h
            References/Refable.h References/Refable.cpp
            References/GarbageCollector.h References/GarbageCollector.cpp
            References/RefCounter.h References/RefCounter.cpp
            References/RefTypes.h

            Internal/ShaderHandler.h
            Internal/OryolApp.h Internal/OryolApp.cpp
            Internal/PNGLoader.h Internal/PNGLoader.cpp
            Internal/shaders.h Internal/shaders.cpp
            Internal/OryolDisplayObject.h Internal/OryolDisplayObject.cpp
            Internal/OryolTexture.h Internal/OryolTexture.cpp
            Internal/OryolResourceManager.h Internal/OryolResourceManager.cpp
            Internal/InternalDestructionManager.h Internal/InternalDestructionManager.cpp
            Internal/WebSocketClientImpl.h Internal/WebSocketClientImpl.cpp)
    fips_deps(Core IO Gfx Input Assets HttpFS LocalFS lodepng WebSocketClient)
fips_end_module()