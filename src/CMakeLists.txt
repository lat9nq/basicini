# Enables modules to include other modules
include_directories(.)

add_compile_options(
    -Wall
    -Werror=array-bounds
    -Werror=implicit-fallthrough
    -Werror=missing-declarations
    -Werror=missing-field-initializers
    -Werror=reorder
    -Werror=sign-compare
    -Werror=switch
    -Werror=uninitialized
    -Werror=unused-function
    -Werror=unused-result
    -Werror=unused-variable
    -Wextra
    -Wmissing-declarations
    -Wno-attributes
    -Wno-invalid-offsetof
    -Wno-unused-parameter
)

add_subdirectory(basicini)
add_subdirectory(test)
