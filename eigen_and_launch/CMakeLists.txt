cmake_minimum_required(VERSION 3.8)
project(eigen_and_launch)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(include)
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIRS})


# Message files
rosidl_generate_interfaces(
  ${PROJECT_NAME}
  "msg/SineWaveStamped.msg"
  DEPENDENCIES std_msgs
)

ament_export_dependencies(rosidl_default_runtime)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")

# Executable
add_executable(sine_wave_publisher src/sine_wave_publisher.cpp)
add_executable(sine_wave_subscriber src/sine_wave_subscriber.cpp)

ament_target_dependencies(sine_wave_publisher rclcpp Eigen3 std_msgs)
ament_target_dependencies(sine_wave_subscriber rclcpp Eigen3 std_msgs)

target_link_libraries(sine_wave_publisher "${cpp_typesupport_target}" Eigen3::Eigen)
target_link_libraries(sine_wave_subscriber "${cpp_typesupport_target}" Eigen3::Eigen)

install(TARGETS sine_wave_publisher
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS sine_wave_subscriber
  DESTINATION lib/${PROJECT_NAME})


# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
