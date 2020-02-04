include_directories("${CMAKE_SOURCE_DIR}/include")

# Ex - Simple usage
add_executable(ex_simple_usage ex_simple_usage/main.cpp)
add_custom_target(run_ex_simple_usage ex_simple_usage)

# Ex - multi classes
file(GLOB_RECURSE src_ex_multi_classes ex_multi_classes/*.cpp)
add_executable(ex_multi_classes ${src_ex_multi_classes})
add_custom_target(run_ex_multi_classes ex_multi_classes)

# Ex - custom outputs
add_executable(ex_custom_outputs ex_custom_outputs/main.cpp)
add_custom_target(run_ex_custom_outputs ex_custom_outputs)

# Ex - logger categories filter
add_executable(ex_logger_categories_filters ex_logger_categories_filters/main.cpp)
add_custom_target(run_ex_logger_categories_filters ex_logger_categories_filters)

