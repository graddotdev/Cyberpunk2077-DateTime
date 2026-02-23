# DateTime

[RED4ext](https://github.com/wopss/RED4ext) plugin for Cyberpunk 2077: native DateTime type for Redscript (Unix time + strftime formatting).

## For users

**Requirements:** Cyberpunk 2077, [RED4ext](https://github.com/wopss/RED4ext).

**Install:** Download the latest `DateTime-*.zip` from Releases. Extract into game root so you have:
- `red4ext/plugins/DateTime/DateTime.dll`
- `red4ext/plugins/DateTime/DateTime.reds`

**Usage:** Import the module and use the native class in Redscript:

```swift
import DateTime

let dateTime = new DateTime();
let seconds = dateTime.ToUnixTimeSeconds();
let milliseconds = dateTime.ToUnixTimeMilliseconds();
let nanoseconds = dateTime.ToUnixTimeNanoseconds();
let formatted = dateTime.Format("%Y-%m-%d %H:%M:%S");
```

## For contributors

**Requirements:** CMake 3.12+.

**Clone:** `git clone --recurse-submodules https://github.com/graddotdev/Cyberpunk2077-DateTime`.

**Build:** From the repo root:

```powershell
cmake -E make_directory build
cmake -B build -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

DLL output: `build/src/Release/DateTime.dll`.

**Bundle zip:** Run `./tools/bundle.ps1` from repo root. Version comes from `RED4EXT_SEMVER` in `src/DateTime.cpp`. Output: `dist/DateTime-<version>/` and `dist/DateTime-<version>.zip`.

**License:** MIT (see LICENSE.md).
