cmake_minimum_required(VERSION 3.8)
project(ros2_app_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(my_robot_interfaces REQUIRED)

add_executable(number_publisher src/number_publisher.cpp)
ament_target_dependencies(number_publisher rclcpp std_msgs)

install(TARGETS
  number_publisher
  DESTINATION lib/${PROJECT_NAME}/
)

add_executable(number_counter src/number_counter.cpp)
ament_target_dependencies(number_counter rclcpp std_msgs my_robot_interfaces)

install(TARGETS
  number_counter
  DESTINATION lib/${PROJECT_NAME}/
)

set_target_properties(
  number_publisher
  number_counter
  PROPERTIES CXX_STANDARD 17
             CXX_STANDARD_REQUIRED TRUE
             CXX_EXTENSIONS FALSE)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
