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
            Graphics/AnimatedSprite.h Graphics/AnimatedSprite.cpp
            Graphics/AnimatedSpriteInfo.h Graphics/AnimatedSpriteInfo.cpp
            Graphics/Camera.h Graphics/Camera.cpp
            Graphics/Viewport.h Graphics/Viewport.cpp
            Graphics/DisplayObject.h Graphics/DisplayObject.cpp
            Graphics/Color.h Graphics/Color.cpp
            Graphics/Shape.h Graphics/Shape.cpp
            Graphics/Rectangle.h Graphics/Rectangle.cpp
            Graphics/Line.h Graphics/Line.cpp
            Graphics/Pixel.h Graphics/Pixel.cpp

            Graphics/Internal/InternalPixelDrawer.h Graphics/Internal/InternalPixelDrawer.cpp
            Graphics/Internal/InternalLineDrawer.h Graphics/Internal/InternalLineDrawer.cpp
            Graphics/Internal/InternalRectangleDrawer.h Graphics/Internal/InternalRectangleDrawer.cpp
            Graphics/Internal/InternalCamera.h Graphics/Internal/InternalCamera.cpp
            Graphics/Internal/InternalViewport.h Graphics/Internal/InternalViewport.cpp

            Audio/Sound.h Audio/Sound.cpp
            Audio/Internal/InternalSound.h Audio/Internal/InternalSound.cpp

            Math/FloatPoint.h Math/FloatPoint.cpp
            Math/Point.h Math/Point.cpp
            Math/Math.h Math/Math.cpp

            Network/Websocket.h Network/Websocket.cpp
            Network/HttpRequest.h Network/HttpRequest.cpp
            Network/HttpResponse.h Network/HttpResponse.cpp
            Network/Impls/HttpRequestImpl.h Network/Impls/HttpRequestImpl.cpp
            Network/Impls/WebsocketImpl.h Network/Impls/WebsocketImpl.cpp
            Network/Impls/HttpRequest/baseHttpRequest.h

            Common/List.h Common/SortedList.h
            Common/String.h Common/String.cpp
            Common/Int.h Common/Int.cpp
            Common/StringBuilder.h Common/StringBuilder.cpp
            Common/Array.h

            References/Ref.h References/IRef.h
            References/Refable.h References/Refable.cpp
            References/GarbageCollector.h References/GarbageCollector.cpp
            References/RefCounter.h References/RefCounter.cpp
            References/RefTypes.h

            Time/Timer.h Time/Timer.cpp

            Graphics/Internal/ShaderHandler.h
            Internal/InternalApp.h Internal/InternalApp.cpp
            Graphics/Internal/PNGLoader.h Graphics/Internal/PNGLoader.cpp
            Graphics/Internal/InternalSprite.h Graphics/Internal/InternalSprite.cpp
            Graphics/Internal/InternalTexture.h Graphics/Internal/InternalTexture.cpp
            Graphics/Internal/InternalResourceManager.h Graphics/Internal/InternalResourceManager.cpp
            Internal/InternalDestructionManager.h Internal/InternalDestructionManager.cpp
    )
    if (ORYOL_USE_LIBCURL)
        fips_files(Network/Impls/HttpRequest/curl/curlHttpRequest.h Network/Impls/HttpRequest/curl/curlHttpRequest.cpp)
    elseif (FIPS_EMSCRIPTEN)
        fips_files(Network/Impls/HttpRequest/emsc/emscHttpRequest.h Network/Impls/HttpRequest/emsc/emscHttpRequest.cpp)
    endif()
    fips_deps(Core IO Gfx Input Assets HttpFS LocalFS lodepng WebSocketClient soloud)
fips_end_module()