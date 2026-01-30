#pragma once

#define M_PI 3.14159265358979323846f

namespace Hooks {
    void Install();

     struct ArrowUpdate {
        static void thunk(RE::ArrowProjectile* a_this, float a_delta);
        static inline REL::Relocation<decltype(thunk)> originalFunction;
    };
}