module DateTime

public native class DateTime {
  public native func ToUnixTimeSeconds() -> Int64;

  public native func ToUnixTimeMilliseconds() -> Int64;

  public native func ToUnixTimeNanoseconds() -> Int64;

  public native func Format(format: String) -> String;
}

