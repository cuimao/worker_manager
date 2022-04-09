# CMakeList.txt: worker_manager 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("worker_manager")

# 将源代码添加到此项目的可执行文件。
add_executable (worker_manager "worker.h" "employee.h" "employee.cpp" "manager.h" "manager.cpp" "boss.h" "boss.cpp""worker_manager.cpp" "worker_manager.h")

# TODO: 如有需要，请添加测试并安装目标。
