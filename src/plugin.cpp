#include "Hooks.h"

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    Hooks::Install();
    return true;
}