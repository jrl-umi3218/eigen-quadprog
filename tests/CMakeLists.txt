find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(QPTest QPTest.cpp)
target_link_libraries(QPTest PRIVATE Boost::unit_test_framework ${PROJECT_NAME})
add_test(QPTestUnit QPTest)
# Adding a project configuration file (for MSVC only)
generate_msvc_dot_user_file(QPTest "$(SolutionDir)/src/quadprog_fortran")
