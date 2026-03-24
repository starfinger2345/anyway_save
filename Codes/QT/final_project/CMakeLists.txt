cmake_minimum_required(VERSION 3.8)
project(final_project)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(std_srvs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Qt6 REQUIRED Widgets Core Gui)
find_package(nav2_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(image_transport REQUIRED)
find_package(OpenCV REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(ament_index_cpp REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

# Set Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Build
add_executable(final_project
	src/mainwidget.cpp
	src/mainwidget.h
	src/mainwidget.ui
	src/main.cpp
	src/rosnode.cpp
	src/rosnode.h
        icon.qrc
        src/mapnode.h
        src/mapnode.cpp
)
ament_target_dependencies(final_project
    rclcpp
    geometry_msgs
    sensor_msgs
    nav2_msgs
    tf2_geometry_msgs
    tf2
    tf2_ros
    nav_msgs
    cv_bridge
    custom_interfaces
    image_transport
    std_srvs
    ament_index_cpp
)

target_link_libraries(final_project
      Qt6::Widgets
      Qt6::Core
      Qt6::Gui
      ${OpenCV_LIBS}
)

target_include_directories(final_project PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Install
Install(TARGETS
	final_project
	DESTINATION lib/${PROJECT_NAME})

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
