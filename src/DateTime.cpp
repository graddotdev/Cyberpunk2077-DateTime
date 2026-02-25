#include <chrono>
#include <format>

#include <RedLib.hpp>

using namespace std::chrono;
using TimePoint = sys_time<nanoseconds>;

struct DateTime : Red::IScriptable
{
    TimePoint timePoint;

    DateTime(TimePoint timePoint) : timePoint(timePoint) {}

    DateTime() : timePoint(system_clock::now()) {}

    static Red::Handle<DateTime> Now()
    {
        return Red::MakeHandle<DateTime>();
    }

    template <typename T> static Red::Handle<DateTime> FromUnixTime(uint64_t unixTime)
    {
        return Red::MakeHandle<DateTime>(TimePoint(T(unixTime)));
    }

    static Red::Handle<DateTime> FromUnixTimeSeconds(uint64_t unixTime)
    {
        return FromUnixTime<seconds>(unixTime);
    }

    static Red::Handle<DateTime> FromUnixTimeMilliseconds(uint64_t unixTime)
    {
        return FromUnixTime<milliseconds>(unixTime);
    }

    static Red::Handle<DateTime> FromUnixTimeNanoseconds(uint64_t unixTime)
    {
        return FromUnixTime<nanoseconds>(unixTime);
    }

    template <typename T> uint64_t ToUnixTime() const
    {
        return duration_cast<T>(timePoint.time_since_epoch()).count();
    }

    uint64_t ToUnixTimeSeconds() const
    {
        return ToUnixTime<seconds>();
    }

    uint64_t ToUnixTimeMilliseconds() const
    {
        return ToUnixTime<milliseconds>();
    }

    uint64_t ToUnixTimeNanoseconds() const
    {
        return ToUnixTime<nanoseconds>();
    }

    Red::CString Format(Red::CString &specification) const
    {
        try
        {
            auto localTime = zoned_time(current_zone(), floor<seconds>(timePoint));
            auto format = "{:" + std::string(specification.c_str()) + "}";
            return std::vformat(format, std::make_format_args(localTime));
        }
        catch (const std::format_error &error)
        {
            return std::string("<Formatting Error: ") + error.what() + ">";
        }
        catch (const std::runtime_error &error)
        {
            return std::string("<Runtime Error: ") + error.what() + ">";
        }
        catch (...)
        {
            return std::string("<Unknown Error>");
        }
    }

    RTTI_IMPL_TYPEINFO(DateTime);
    RTTI_IMPL_ALLOCATOR();
};

RTTI_DEFINE_CLASS(DateTime, {
    RTTI_METHOD(Now);

    RTTI_METHOD(FromUnixTimeSeconds);
    RTTI_METHOD(FromUnixTimeMilliseconds);
    RTTI_METHOD(FromUnixTimeNanoseconds);

    RTTI_METHOD(ToUnixTimeSeconds);
    RTTI_METHOD(ToUnixTimeMilliseconds);
    RTTI_METHOD(ToUnixTimeNanoseconds);

    RTTI_METHOD(Format);
});
