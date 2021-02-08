def nanopb_library(name, srcs = []):
    if (len(srcs) != 1):
        fail("srcs must have one element")

    native.genrule(
        name = name + "_nanopb_gen",
        srcs = srcs,
        outs = [name + ".pb.h", name + ".pb.c"],
        cmd = ("$(location :nanopb_shim) " +
               "$(location //nanopb/generator:nanopb_generator) $(SRCS) " +
               "$(OUTS)"),
        tools = ["//nanopb/generator:nanopb_generator", ":nanopb_shim"],
    )

    native.cc_library(
        name = name,
        srcs = [name + ".pb.c"],
        hdrs = [name + ".pb.h"],
        deps = [
            "//nanopb",
        ],
        copts = [
            "-isystemnanopb",
        ],
    )
