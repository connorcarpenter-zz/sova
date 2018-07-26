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

            Graphics/Internal/InternalCamera.h Graphics/Internal/InternalCamera.cpp
            Graphics/Internal/InternalViewport.h Graphics/Internal/InternalViewport.cpp

            Math/Point.h Math/Point.cpp
            Math/Math.h Math/Math.cpp

            Network/Websocket.h Network/Websocket.cpp
            Network/HttpRequest.h Network/HttpRequest.cpp
            Network/HttpResponse.h Network/HttpResponse.cpp
            Network/Impls/HttpRequestImpl.h Network/Impls/HttpRequestImpl.cpp
            Network/Impls/WebsocketImpl.h Network/Impls/WebsocketImpl.cpp
            Network/Impls/HttpRequest/baseHttpRequest.h

            Common/List.h
            Common/String.h Common/String.cpp
            Common/StringBuilder.h Common/StringBuilder.cpp

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
    )
    if (ORYOL_USE_LIBCURL)
        fips_files(Network/Impls/HttpRequest/curl/curlHttpRequest.h Network/Impls/HttpRequest/curl/curlHttpRequest.cpp)
    elseif (FIPS_EMSCRIPTEN)
        fips_files(Network/Impls/HttpRequest/emsc/emscHttpRequest.h Network/Impls/HttpRequest/emsc/emscHttpRequest.cpp)
    endif()
    fips_deps(Core IO Gfx Input Assets HttpFS LocalFS lodepng WebSocketClient)
fips_end_module()