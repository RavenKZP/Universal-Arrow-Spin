#include "Hooks.h"

void Hooks::Install() {
    ArrowUpdate::originalFunction = REL::Relocation<std::uintptr_t>(RE::ArrowProjectile::VTABLE[0]).write_vfunc(0xAB, ArrowUpdate::thunk); }

void Hooks::ArrowUpdate::thunk(RE::ArrowProjectile* a_this, float a_delta) {
    originalFunction(a_this, a_delta);
    float spinSpeed = 10 * M_PI;  // Radians per second  PI = 180 degrees per second
    RE::NiPoint3 angle = a_this->GetAngle();
    angle.y += spinSpeed * a_delta;
    if (angle.y > 2 * M_PI) {
        angle.y -= 2 * M_PI;
    }
    a_this->data.angle = angle;
}
