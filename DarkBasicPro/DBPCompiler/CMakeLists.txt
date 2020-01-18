# CMakeList.txt : CMake project for DBPCompiler, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (DBPCompiler "DBPCompiler.cpp" "DBPCompiler.h")


target_link_libraries(DBPCompiler PUBLIC Encryptor)

# TODO: Add tests and install targets if needed.
