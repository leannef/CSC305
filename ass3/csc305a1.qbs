import qbs

CppApplication {
    consoleApplication: true
    files: [
        "../../../../Users/leannef/Desktop/csc305_A01/aabb.h",
        "../../../../Users/leannef/Desktop/csc305_A01/box.h",
        "../../../../Users/leannef/Desktop/csc305_A01/bvh_node.h",
        "../../../../Users/leannef/Desktop/csc305_A01/camera.h",
        "../../../../Users/leannef/Desktop/csc305_A01/constant_medium.h",
        "../../../../Users/leannef/Desktop/csc305_A01/hitable.h",
        "../../../../Users/leannef/Desktop/csc305_A01/hitable_list.h",
        "../../../../Users/leannef/Desktop/csc305_A01/isotropic.h",
        "../../../../Users/leannef/Desktop/csc305_A01/lambertian.h",
        "../../../../Users/leannef/Desktop/csc305_A01/material.h",
        "../../../../Users/leannef/Desktop/csc305_A01/moving_sphere.h",
        "../../../../Users/leannef/Desktop/csc305_A01/perlin.h",
        "../../../../Users/leannef/Desktop/csc305_A01/ray.h",
        "../../../../Users/leannef/Desktop/csc305_A01/rotate_y.h",
        "../../../../Users/leannef/Desktop/csc305_A01/sphere.h",
        "../../../../Users/leannef/Desktop/csc305_A01/stb_image.h",
        "../../../../Users/leannef/Desktop/csc305_A01/stb_image_write.h",
        "../../../../Users/leannef/Desktop/csc305_A01/texture.h",
        "../../../../Users/leannef/Desktop/csc305_A01/translate.h",
        "../../../../Users/leannef/Desktop/csc305_A01/vec3.h",
        "main.cpp",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
    }
}
