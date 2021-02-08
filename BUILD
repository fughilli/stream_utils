package(default_visibility = [
    "//stream_utils:__subpackages__",
    "//jog_controller_server:__subpackages__",
])

load("@com_google_protobuf//:protobuf.bzl", "py_proto_library")
load("//stream_utils:build_defs.bzl", "nanopb_library")

cc_library(
    name = "bits",
    hdrs = ["bits.h"],
)

cc_test(
    name = "bits_test",
    srcs = ["bits_test.cc"],
    deps = [
        ":bits",
        "@com_googletest//:gtest",
        "@com_googletest//:gtest_main",
    ],
)

cc_library(
    name = "bit_pipe",
    hdrs = ["bit_pipe.h"],
    deps = [
        ":bits",
    ],
)

cc_test(
    name = "bit_pipe_test",
    srcs = ["bit_pipe_test.cc"],
    deps = [
        ":bit_pipe",
        "@com_googletest//:gtest",
        "@com_googletest//:gtest_main",
    ],
)

cc_library(
    name = "stream",
    hdrs = ["stream.h"],
)

cc_library(
    name = "pb_stream",
    hdrs = ["pb_stream.h"],
    deps = [
        ":stream",
        "//nanopb",
    ],
)

cc_library(
    name = "base64_stream",
    srcs = ["base64_stream.cc"],
    hdrs = ["base64_stream.h"],
    deps = [
        ":bit_pipe",
        ":stream",
    ],
)

cc_test(
    name = "base64_stream_test",
    srcs = ["base64_stream_test.cc"],
    deps = [
        ":base64_stream",
        "@com_googletest//:gtest",
        "@com_googletest//:gtest_main",
    ],
)

sh_binary(
    name = "nanopb_shim",
    srcs = ["nanopb_shim.sh"],
)

nanopb_library(
    name = "control_message",
    srcs = ["control_message.proto"],
)

py_proto_library(
    name = "control_message_py_proto",
    srcs = ["control_message.proto"],
)

cc_binary(
    name = "nanopb_test",
    srcs = ["nanopb_test.cc"],
    copts = [
        "-isystemnanopb",
    ],
    deps = [
        ":base64_stream",
        ":control_message",
        ":pb_stream",
        ":stream",
    ],
)
