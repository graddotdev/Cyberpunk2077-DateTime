#include <RED4ext/RED4ext.hpp>
#include <RED4ext/RTTITypes.hpp>
#include <RED4ext/Scripting/IScriptable.hpp>
#include <chrono>
#include <ctime>
#include <iomanip>

using SystemClock = std::chrono::system_clock;
using TimePoint = std::chrono::system_clock::time_point;

struct DateTime : RED4ext::IScriptable
{
    TimePoint timePoint;

    DateTime()
    {
        timePoint = SystemClock::now();
    }

    RED4ext::CClass* GetNativeType() override;
};

RED4ext::TTypedClass<DateTime> cls("DateTime.DateTime");

RED4ext::CClass* DateTime::GetNativeType()
{
    return &cls;
}

void ToUnixTimeSeconds(RED4ext::IScriptable* aContext, RED4ext::CStackFrame* aFrame, int64_t* aOut, int64_t a4)
{
    RED4EXT_UNUSED_PARAMETER(a4);
    auto obj = reinterpret_cast<DateTime*>(aContext);
    aFrame->code++;

    if (aOut)
    {
        auto duration = obj->timePoint.time_since_epoch();
        *aOut = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    }
}

void ToUnixTimeMilliseconds(RED4ext::IScriptable* aContext, RED4ext::CStackFrame* aFrame, int64_t* aOut, int64_t a4)
{
    RED4EXT_UNUSED_PARAMETER(a4);
    auto obj = reinterpret_cast<DateTime*>(aContext);
    aFrame->code++;

    if (aOut)
    {
        auto duration = obj->timePoint.time_since_epoch();
        *aOut = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
}

void ToUnixTimeNanoseconds(RED4ext::IScriptable* aContext, RED4ext::CStackFrame* aFrame, int64_t* aOut, int64_t a4)
{
    RED4EXT_UNUSED_PARAMETER(a4);
    auto obj = reinterpret_cast<DateTime*>(aContext);
    aFrame->code++;

    if (aOut)
    {
        auto duration = obj->timePoint.time_since_epoch();
        *aOut = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    }
}

void Format(RED4ext::IScriptable* aContext, RED4ext::CStackFrame* aFrame, RED4ext::CString* aOut, int64_t a4)
{
    RED4EXT_UNUSED_PARAMETER(a4);
    auto obj = reinterpret_cast<DateTime*>(aContext);

    RED4ext::CString format;
    RED4ext::GetParameter(aFrame, &format);
    aFrame->code++; // skip ParamEnd

    if (aOut)
    {
        std::time_t now_c = SystemClock::to_time_t(obj->timePoint);
        std::tm now_tm;

        // Use localtime_s (Windows/MSVC safe)
        localtime_s(&now_tm, &now_c);

        char buffer[256];
        if (std::strftime(buffer, sizeof(buffer), format.c_str(), &now_tm))
        {
            *aOut = buffer;
        }
        else
        {
            *aOut = "";
        }
    }
}

RED4EXT_C_EXPORT void RED4EXT_CALL RegisterTypes()
{
    RED4ext::CNamePool::Add("DateTime.DateTime");
    cls.flags = {.isNative = true};
    RED4ext::CRTTISystem::Get()->RegisterType(&cls);
}

RED4EXT_C_EXPORT void RED4EXT_CALL PostRegisterTypes()
{
    auto rtti = RED4ext::CRTTISystem::Get();
    auto scriptable = rtti->GetClass("IScriptable");
    cls.parent = scriptable;

    RED4ext::CBaseFunction::Flags flags = {.isNative = true};

    // ToUnixTimeSeconds
    auto getSecs = RED4ext::CClassFunction::Create(&cls, "ToUnixTimeSeconds", "ToUnixTimeSeconds", &ToUnixTimeSeconds);
    getSecs->flags = flags;
    getSecs->SetReturnType("Int64");
    cls.RegisterFunction(getSecs);

    // ToUnixTimeMilliseconds
    auto getMillis = RED4ext::CClassFunction::Create(&cls, "ToUnixTimeMilliseconds", "ToUnixTimeMilliseconds",
                                                     &ToUnixTimeMilliseconds);
    getMillis->flags = flags;
    getMillis->SetReturnType("Int64");
    cls.RegisterFunction(getMillis);

    // ToUnixTimeNanoseconds
    auto getNanos =
        RED4ext::CClassFunction::Create(&cls, "ToUnixTimeNanoseconds", "ToUnixTimeNanoseconds", &ToUnixTimeNanoseconds);
    getNanos->flags = flags;
    getNanos->SetReturnType("Int64");
    cls.RegisterFunction(getNanos);

    // Format
    auto formatFunc = RED4ext::CClassFunction::Create(&cls, "Format", "Format", &Format);
    formatFunc->flags = flags;
    formatFunc->AddParam("String", "format");
    formatFunc->SetReturnType("String");
    cls.RegisterFunction(formatFunc);
}

RED4EXT_C_EXPORT bool RED4EXT_CALL Main(RED4ext::PluginHandle aHandle, RED4ext::EMainReason aReason,
                                        const RED4ext::Sdk* aSdk)
{
    switch (aReason)
    {
    case RED4ext::EMainReason::Load:
    {
        auto rtti = RED4ext::CRTTISystem::Get();
        rtti->AddRegisterCallback(RegisterTypes);
        rtti->AddPostRegisterCallback(PostRegisterTypes);

        aSdk->scripts->Add(aHandle, L".");

        break;
    }
    case RED4ext::EMainReason::Unload:
    {
        break;
    }
    }
    return true;
}

RED4EXT_C_EXPORT void RED4EXT_CALL Query(RED4ext::PluginInfo* aInfo)
{
    aInfo->name = L"DateTime";
    aInfo->author = L"Alex Grad <alex@grad.dev>";
    aInfo->version = RED4EXT_SEMVER(1, 0, 0);
    aInfo->runtime = RED4EXT_RUNTIME_LATEST;
    aInfo->sdk = RED4EXT_SDK_LATEST;
}

RED4EXT_C_EXPORT uint32_t RED4EXT_CALL Supports()
{
    return RED4EXT_API_VERSION_LATEST;
}
