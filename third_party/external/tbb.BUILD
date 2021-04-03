load("@rules_cc//cc:defs.bzl", "cc_library")

# mkdir build
# cd build
# cmake -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DTBB_TEST=OFF ..
# cmake --build .
# open compile_commands.json

_TBB_SRC_HDRS = glob([
    "src/tbb/**/*.h",
])

_TBB_SRCS = [
    "src/tbb/allocator.cpp",
    "src/tbb/arena.cpp",
    "src/tbb/arena_slot.cpp",
    "src/tbb/concurrent_monitor.cpp",
    "src/tbb/concurrent_bounded_queue.cpp",
    "src/tbb/dynamic_link.cpp",
    "src/tbb/exception.cpp",
    "src/tbb/governor.cpp",
    "src/tbb/global_control.cpp",
    "src/tbb/itt_notify.cpp",
    "src/tbb/main.cpp",
    "src/tbb/market.cpp",
    "src/tbb/misc.cpp",
    "src/tbb/misc_ex.cpp",
    "src/tbb/observer_proxy.cpp",
    "src/tbb/parallel_pipeline.cpp",
    "src/tbb/private_server.cpp",
    "src/tbb/profiling.cpp",
    "src/tbb/rml_tbb.cpp",
    "src/tbb/rtm_mutex.cpp",
    "src/tbb/rtm_rw_mutex.cpp",
    "src/tbb/semaphore.cpp",
    "src/tbb/small_object_pool.cpp",
    "src/tbb/task.cpp",
    "src/tbb/task_dispatcher.cpp",
    "src/tbb/task_group_context.cpp",
    "src/tbb/version.cpp",
    "src/tbb/queuing_rw_mutex.cpp",
]

_TBB_HDRS = glob([
    "include/tbb/**/*.h",
    "include/oneapi/**/*.h",
])

_TBB_COPTS = select({
    "@//:windows": [
        "/nologo",
        "/TP",
        "/GR",
        "/EHsc",
        # "/O2",
        "/Ob2",
        # "/MD",
        "/W4",
        "/WX",
        "/wd4324",
        "/wd4530",
        "/wd4577",
        "/GS",
        "/volatile:iso",
    ],
    "@//:macos": [
        "-O3",
        "-fPIC",
        # "-MMD",
        "-Wall",
        "-Wextra",
        "-Werror",
        "-Wno-parentheses",
        "-Wno-non-virtual-dtor",
        "-Wno-dangling-else",
        "-mrtm",
        "-std=c++11",
    ],
})

_TBB_DEFINES = select({
    "@//:windows": [
        "__TBB_BUILD",
        "__TBB_USE_ITT_NOTIFY",
        "WIN32",
        "_WINDOWS",
        "NDEBUG",
        "_CRT_SECURE_NO_WARNINGS",
    ],
    "@//:macos": [
        "__TBB_BUILD",
        "__TBB_USE_ITT_NOTIFY",
        "NDEBUG",
        "_XOPEN_SOURCE",
    ],
})

cc_library(
    name = "tbb",
    srcs = _TBB_SRC_HDRS + _TBB_SRCS,
    hdrs = _TBB_HDRS,
    copts = _TBB_COPTS,
    defines = _TBB_DEFINES,
    strip_include_prefix = "include",
    textual_hdrs = [
        "src/tbb/tools_api/ittnotify_static.c",
    ],
    visibility = [
        "//visibility:public",
    ],
)

_TBBMALLOC_SRCS = [
    "src/tbbmalloc/backend.cpp",
    "src/tbbmalloc/backref.cpp",
    "src/tbbmalloc/frontend.cpp",
    "src/tbbmalloc/large_objects.cpp",
    "src/tbbmalloc/tbbmalloc.cpp",
    "src/tbb/itt_notify.cpp",
]

_TBBMALLOC_COPTS = select({
    "@//:windows": [
        "/nologo",
        "/TP",
        "/GR",
        "/EHsc",
        # "/O2",
        "/Ob2",
        # "/MD",
        "/W4",
        "/WX",
        "/wd4324",
        "/wd4530",
        "/wd4577",
        "/GS",
        "/volatile:iso",
    ],
    "@//:macos": [
        # "-O3",
        "-fPIC",
        "-MMD",
        "-Wno-parentheses",
        "-Wno-non-virtual-dtor",
        "-Wno-dangling-else",
        "-fno-rtti",
        "-fno-exceptions",
        "-mrtm",
        "-std=c++11",
    ],
})

_TBBMALLOC_DEFINES = select({
    "@//:windows": [
        "__TBBMALLOCPROXY_BUILD",
        "tbbmalloc_proxy_EXPORTS",
        "WIN32",
        "_WINDOWS",
        "NDEBUG",
        "_CRT_SECURE_NO_WARNINGS",
    ],
    "@//:macos": [
        "__TBBMALLOC_BUILD",
        "__TBB_USE_ITT_NOTIFY",
        "NDEBUG",
        "_XOPEN_SOURCE",
    ],
})

cc_library(
    name = "tbbmalloc",
    srcs = _TBB_SRC_HDRS + _TBBMALLOC_SRCS,
    hdrs = _TBB_HDRS,
    copts = _TBBMALLOC_COPTS,
    defines = _TBBMALLOC_DEFINES,
    strip_include_prefix = "include",
    visibility = [
        "//visibility:public",
    ],
)

_TBBMALLOC_PROXY_SRCS = [
    "src/tbbmalloc_proxy/function_replacement.cpp",
    "src/tbbmalloc_proxy/proxy.cpp",
]

cc_library(
    name = "tbbmalloc_proxy",
    srcs = _TBB_SRC_HDRS + _TBBMALLOC_PROXY_SRCS,
    hdrs = _TBB_HDRS,
    copts = _TBBMALLOC_COPTS,
    defines = _TBBMALLOC_DEFINES,
    strip_include_prefix = "include",
    visibility = [
        "//visibility:public",
    ],
)
