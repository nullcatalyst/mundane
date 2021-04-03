load(
    "@rules_cc//cc:defs.bzl",
    native_cc_binary = "cc_binary",
    native_cc_library = "cc_library",
    native_cc_test = "cc_test",
    native_objc_library = "objc_library",
)

_COPTS = select({
    "//:windows_opt": [
        "/std:c++latest",
        "/EHs-c-",
        "/GR-",
        "/O2",
        "/Ob3",
        "/GL",
    ],
    "//:windows": [
        "/std:c++latest",
        "/EHs-c-",
        "/GR-",
    ],
    "//:macos_opt": [
        "-std=c++17",
        "-flto",
    ],
    "//:macos": [
        "-std=c++17",
    ],
    "//:linux_opt": [
        "-std=c++17",
        "-flto",
    ],
    "//:linux": [
        "-std=c++17",
    ],
})

_DEFINES = select({
    "//:windows": [
        "_HAS_DEPRECATED_RESULT_OF=1",
        "_HAS_EXCEPTIONS=0",
    ],
    "//:macos": [],
    "//:linux": [],
})

_LINKOPTS = select({
    "//:windows_opt": [
        "/LTCG",
    ],
    "//:windows": [],
    "//:macos_opt": [
        "-flto",
    ],
    "//:macos": [],
    "//:linux_opt": [
        "-flto",
    ],
    "//:linux": [],
})

def cc_library(**kwargs):
    if "copts" in kwargs:
        kwargs["copts"] = _COPTS + kwargs["copts"]
    else:
        kwargs["copts"] = _COPTS

    if "defines" in kwargs:
        kwargs["defines"] = _DEFINES + kwargs["defines"]
    else:
        kwargs["defines"] = _DEFINES

    if "linkopts" in kwargs:
        kwargs["linkopts"] = _LINKOPTS + kwargs["linkopts"]
    else:
        kwargs["linkopts"] = _LINKOPTS

    return native_cc_library(**kwargs)

def cc_binary(**kwargs):
    if "copts" in kwargs:
        kwargs["copts"] = _COPTS + kwargs["copts"]
    else:
        kwargs["copts"] = _COPTS

    if "defines" in kwargs:
        kwargs["defines"] = _DEFINES + kwargs["defines"]
    else:
        kwargs["defines"] = _DEFINES

    if "linkopts" in kwargs:
        kwargs["linkopts"] = _LINKOPTS + kwargs["linkopts"]
    else:
        kwargs["linkopts"] = _LINKOPTS

    return native_cc_binary(**kwargs)

def cc_test(**kwargs):
    if "copts" in kwargs:
        kwargs["copts"] = _COPTS + kwargs["copts"]
    else:
        kwargs["copts"] = _COPTS

    if "defines" in kwargs:
        kwargs["defines"] = _DEFINES + kwargs["defines"]
    else:
        kwargs["defines"] = _DEFINES

    if "linkopts" in kwargs:
        kwargs["linkopts"] = _LINKOPTS + kwargs["linkopts"]
    else:
        kwargs["linkopts"] = _LINKOPTS

    return native_cc_test(**kwargs)

def objc_library(**kwargs):
    if "copts" in kwargs:
        kwargs["copts"] = _COPTS + kwargs["copts"]
    else:
        kwargs["copts"] = _COPTS

    if "defines" in kwargs:
        kwargs["defines"] = _DEFINES + kwargs["defines"]
    else:
        kwargs["defines"] = _DEFINES

    return native_objc_library(**kwargs)
