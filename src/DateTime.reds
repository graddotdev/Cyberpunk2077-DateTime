
public native class DateTime {
  public native static func Now() -> ref<DateTime>;

  public native static func FromUnixTimeSeconds(unixTime: Uint64) -> ref<DateTime>;

  public native static func FromUnixTimeMilliseconds(unixTime: Uint64) -> ref<DateTime>;

  public native static func FromUnixTimeNanoseconds(unixTime: Uint64) -> ref<DateTime>;

  public native func ToUnixTimeSeconds() -> Uint64;

  public native func ToUnixTimeMilliseconds() -> Uint64;

  public native func ToUnixTimeNanoseconds() -> Uint64;

  public native func Format(format: String) -> String;
}

