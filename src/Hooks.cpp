#include "Hooks.h"

void Hooks::Install() {
    ArrowUpdate::originalFunction = REL::Relocation<std::uintptr_t>(RE::ArrowProjectile::VTABLE[0]).write_vfunc(0xAB, ArrowUpdate::thunk); }

void Hooks::ArrowUpdate::thunk(RE::ArrowProjectile* a_this, float a_delta) {
    originalFunction(a_this, a_delta);

    // Skip spinning if impacts have been processed
    const auto& rt = a_this->GetProjectileRuntimeData();
    if (rt.flags.any(RE::Projectile::Flags::kProcessedImpacts)) {
        return;
    }

    // Apply spinning effect
    float spinSpeed = 10 * M_PI;  // Radians per second  PI = 180 degrees per second
    int spinDirection = a_this->GetFormID() % 2 == 0 ? 1 : -1;  // Alternate spin direction based on FormID
    RE::NiPoint3 angle = a_this->GetAngle();
    angle.y += spinDirection * spinSpeed * a_delta;
    if (angle.y > M_PI) {  // Wrap around to keep angle within -PI to PI
        angle.y -=  2 * M_PI;
    } else if (angle.y < -M_PI) {
        angle.y += 2 * M_PI;
    }
    a_this->data.angle = angle;
}
