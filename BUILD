load("//bazel:data_view_cc.bzl", "data_view_copts")

exports_files(["LICENSE"])

config_setting(
    name = "windows",
    constraint_values = ["@bazel_tools//platforms:windows"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "data_view",
    hdrs = [
        "data_view/arch.h",
        "data_view/data_view.h",
        "data_view/export.h",
    ],
    srcs = [
        "data_view/data_view.cc",
    ],
    copts = data_view_copts(),
    visibility = ["//visibility:public"],
)

cc_test(
    name = "data_view_unittest",
    srcs = [
        "data_view/data_view_unittest.cc",
    ],
    copts = data_view_copts(),
    deps = [
        ":data_view",
        "@com_google_googletest//:gtest_main",
    ],
)