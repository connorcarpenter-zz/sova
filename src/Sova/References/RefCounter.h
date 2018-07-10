#pragma once

//
// Created by connor on 7/9/18.
//

namespace Sova {
    class RefCounter {
    public:
        void Hold();
        int Release();
    private:
        int count = 0;
    };
}