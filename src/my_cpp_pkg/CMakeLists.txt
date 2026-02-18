cmake_minimum_required(VERSION 3.8)  #CMAKE version
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)


add_executable(cpp_node src/my_first_node.cpp)
# cpp_node:executable file name
# node directory path
ament_target_dependencies(cpp_node rclcpp)
# 1st: executable name
# 2nd dependencies

add_executable(robot_news_station src/robot_news_station.cpp)
ament_target_dependencies(robot_news_station rclcpp example_interfaces)


install(TARGETS
  cpp_node # exetable
  robot_news_station
  DESTINATION lib/${PROJECT_NAME} 
)

ament_package()
