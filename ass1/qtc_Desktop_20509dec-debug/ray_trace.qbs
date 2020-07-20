import qbs

CppApplication {
    consoleApplication: true
    files: [
        "../../../Volumes/leannef/csc305/ass1/ass1/moving_sphere.h",
        "aabb.h",
        "camera.h",
        "constant_medium.h",
        "hitable.h",
        "hitablelist.h",
        "main.cpp",
        "material.h",
        "moving_sphere.h",
        "perlin.h",
        "ray.h",
        "sphere.h",
        "stb_image.h",
        "stb_image_write.h",
        "texture.h",
        "vec3.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
