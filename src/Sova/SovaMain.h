#pragma once

//
// Created by connor on 7/8/18.
//

#include "App.h"
#include "Sova/Graphics/Container.h"
#include "Sova/Graphics/Sprite.h"
#include "Sova/Graphics/AnimatedSprite.h"
#include "Sova/Math/Point.h"
#include "Sova/Graphics/Viewport.h"
#include "Sova/Graphics/Camera.h"
#include "Loader.h"
#include "Log.h"
#include "Input.h"
#include "Sova/Math/Math.h"
#include "Sova/Network/Websocket.h"
#include "Sova/Network/HttpRequest.h"
#include "Sova/Network/HttpResponse.h"
#include "Common/String.h"
#include "Common/StringBuilder.h"
#include "Sova/Common/List.h"
#include "References/Ref.h"
#include "References/Refable.h"
#include "References/GarbageCollector.h"
#include "References/RefTypes.h"

namespace Sova
{
    class SovaMain
    {
        SovaMain() = default;
    };
}