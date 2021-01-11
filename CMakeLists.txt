cmake_minimum_required(VERSION 2.8.3)
project(object_detection_gl_ros)

EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "Architecture: ${ARCHITECTURE}" )
set( LIBRARY_PATH "${PROJECT_SOURCE_DIR}/lib/${ARCHITECTURE}" )
set( GL_LIBRARY "${LIBRARY_PATH}/libobject_detection.so" "${LIBRARY_PATH}/libgl_driver.so" "${LIBRARY_PATH}/libserial.so" )

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  visualization_msgs 
  geometry_msgs
  std_msgs
  message_generation
)

## 사용할 메세지 파일 선언
add_message_files(
  FILES
  CoordArray.msg
  Coord.msg
  ObjectWidthArray.msg
  ObjectWidth.msg
  ObjectCount.msg
  LeftDistance.msg
  FrontDistance.msg
  Distance.msg
)
generate_messages(
  DEPENDENCIES
  std_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp sensor_msgs visualization_msgs geometry_msgs std_msgs
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

#add_executable(${PROJECT_NAME}_node
#  src/${PROJECT_NAME}_node.cpp
#)
add_executable(object_detection_gl_ros_node src/object_detection_gl_ros_node)
add_executable(object_detection_sub_node src/object_detection_sub_node)
add_executable(raw_data_manager src/raw_data_manager)
add_executable(test_file src/test_file)


#target_link_libraries(${PROJECT_NAME}_node
#  ${catkin_LIBRARIES}
#  ${GL_LIBRARY}
#)
target_link_libraries(object_detection_gl_ros_node ${catkin_LIBRARIES} ${GL_LIBRARY})
target_link_libraries(object_detection_sub_node ${catkin_LIBRARIES} ${GL_LIBRARY})
target_link_libraries(raw_data_manager ${catkin_LIBRARIES} ${GL_LIBRARY})
target_link_libraries(test_file ${catkin_LIBRARIES} ${GL_LIBRARY})


#add_dependencies(${PROJECT_NAME}_node
#  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
#  ${catkin_EXPORTED_TARGETS}
#  ${GL_LIBRARY}
#)
add_dependencies(object_detection_gl_ros_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
  ${GL_LIBRARY}
)
add_dependencies(object_detection_sub_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS} 
  ${catkin_EXPORTED_TARGETS}
  ${GL_LIBRARY}
)
add_dependencies(raw_data_manager
 ${${PROJECT_NAME}_EXPORTED_TARGETS} 
 ${catkin_EXPORTED_TARGETS}
 ${GL_LIBRARY}
)
add_dependencies(test_file
 ${${PROJECT_NAME}_EXPORTED_TARGETS} 
 ${catkin_EXPORTED_TARGETS}
 ${GL_LIBRARY}
)


