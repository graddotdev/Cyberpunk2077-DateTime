#include <RED4ext/RED4ext.hpp>
#include <RED4ext/RTTITypes.hpp>
#include <RED4ext/Scripting/IScriptable.hpp>
#include <RedLib.hpp>
#include <chrono>
#include <format>

RED4EXT_C_EXPORT bool RED4EXT_CALL Main(
    RED4ext::PluginHandle aHandle,
    RED4ext::EMainReason aReason,
    const RED4ext::Sdk *aSdk
)
{
    switch (aReason)
    {
        case RED4ext::EMainReason::Load: {
            Red::TypeInfoRegistrar::RegisterDiscovered();
            aSdk->scripts->Add(aHandle, L".");
            break;
        }
        case RED4ext::EMainReason::Unload: {
            break;
        }
    }
    return true;
}

RED4EXT_C_EXPORT void RED4EXT_CALL Query(RED4ext::PluginInfo *aInfo)
{
    aInfo->name = L"DateTime";
    aInfo->author = L"Alex Grad <alex@grad.dev>";
    aInfo->version = RED4EXT_SEMVER(2, 0, 0);
    aInfo->runtime = RED4EXT_RUNTIME_LATEST;
    aInfo->sdk = RED4EXT_SDK_LATEST;
}

RED4EXT_C_EXPORT uint32_t RED4EXT_CALL Supports()
{
    return RED4EXT_API_VERSION_LATEST;
}
