import qbs

CppApplication {
    consoleApplication: true
    files: [
        "bvh_node.h",
        "camera.h",
        "constant_medium.h",
        "hitable.h",
        "main.cpp",
        "material.h",
        "moving_sphere.h",
        "perlin.h",
        "ray.h",
        "rotate.h",
        "sphere.h",
        "stb_image.h",
        "stb_image_write.h",
        "texture.h",
        "translate.h",
        "vec3.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
