# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(MyBridge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS -flto)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOLOWER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME)
string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)

if(${USE_MACRO})
  add_definitions(-DUSE_MACRO=1)
endif()

option(USE_MACRO_SWITCH "USE_MACRO_SWITCH" ON)

# 限制变量替换，让其只替换被 @VAR@ 引用的变量（那么 ${VAR} 格式的变量将不会被替换）。这在配置 ${VAR} 语法的脚本时是非常有用的。
configure_file(config.h.in config.h @ONLY)

list(APPEND PUBLIC_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/my_bridge.h
)

#  specify the output directory as an include directory
include_directories(${CMAKE_CURRENT_BINARY_DIR})

list(APPEND APP_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/include/my_bridge.h
  my_bridge.cc
  apps/hello.h
  apps/hello.cc
  apps/Animal.h
  apps/Animal.cc
  apps/Dog.h
  apps/Dog.cc
)

if ($ENV{BRIDGE_JS_ENGINE} MATCHES "jsc")
  list(APPEND APP_SOURCE
    jsc/jsengines/jsc/utils.h
    jsc/jsengines/jsc/utils.cc
    jsc/jsengines/jsc/JSConsole.h
    jsc/jsengines/jsc/JSConsole.cc
    jsc/jsengines/jsc/JSCoreContext.h
    jsc/jsengines/jsc/JSCoreContext.cc
    jsc/jsengines/jsc/AlitaGlobalObject.h
    jsc/jsengines/jsc/AlitaGlobalObject.cc
  )
endif()

list(APPEND APP_SOURCE
  jsc/Engine.cc 
  jsc/Scope.cc
  jsc/Context.cc
  jsc/NativeMethods.cc
)

list(APPEND BRIDGE_INCLUDE
    ./include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

## 自定义一个library
add_library(my_bridge_static STATIC ${APP_SOURCE})

# IOS配置 
if (${CMAKE_SYSTEM_NAME} MATCHES "ios")
  add_library(my_bridge SHARED ${APP_SOURCE})
  set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")
  set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "")
  set_target_properties(my_bridge PROPERTIES
    OUTPUT_NAME my_bridge
    FRAMEWORK TRUE
    FRAMEWORK_VERSION C
    MACOSX_FRAMEWORK_IDENTIFIER com.cmake.dynamicFramework
    # MACOSX_FRAMEWORK_INFO_PLIST Info.plist
    # "current version" in semantic format in Mach-O binary file
    # VERSION 16.4.0
    # "compatibility version" in semantic format in Mach-O binary file
    # SOVERSION 1.0.0
    PUBLIC_HEADER ${PUBLIC_HEADERS}
    # XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
  )
else()
  add_library(my_bridge SHARED ${APP_SOURCE})
  # add_executable(my_bridge 
  #   main.cc
  #   class_test.h
  #   class_test.cc
  #   string_test.h
  #   string_test.cc
  #   values_test.h
  #   values_test.cc
  #   func_test.h
  #   func_test.cc
  # )
  # list(APPEND BRIDGE_LINK_LIBS my_bridge_static)
  # target_link_libraries(my_bridge PRIVATE my_bridge_static)
endif()

if ($ENV{BRIDGE_JS_ENGINE} MATCHES "jsc")
  add_compile_options(-DBRIDGE_JS_ENGINE=1)
  if (${IS_ANDROID})
    message("IS_ANDROID=true")
    list(APPEND BRIDGE_INCLUDE
            ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/JavaScriptCore/include
            )
    add_library(JavaScriptCore SHARED IMPORTED)
    set_target_properties(JavaScriptCore PROPERTIES IMPORTED_LOCATION
            "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/JavaScriptCore/lib/android/${ANDROID_ABI}/libjsc.so"
            )
    list(APPEND BRIDGE_LINK_LIBS
            JavaScriptCore
            )
    # message("APPLE=false")
    # target_include_directories(my_bridge
    #   PUBLIC
    #   "/usr/include/webkitgtk-3.0")
    # # target_link_libraries(my_bridge PRIVATE
    # #   # Our needed libraries
    # #   javascriptcoregtk-3.0
    # #   BlocksRuntime)
    # list(APPEND BRIDGE_LINK_LIBS javascriptcoregtk-3.0)
    # list(APPEND BRIDGE_LINK_LIBS BlocksRuntime)
  else ()
   
    message("APPLE=true")
    include_directories(/System/Library/Frameworks)
    find_library(JAVASCRIPTCORE_LIBRARY JavaScriptCore)
    mark_as_advanced(JAVASCRIPTCORE_LIBRARY)
    set(EXTRA_LIBS ${JAVASCRIPTCORE_LIBRARY})
    list(APPEND BRIDGE_LINK_LIBS ${EXTRA_LIBS})

    # list(APPEND BRIDGE_LINK_LIBS "-framework JavaScriptCore")
    # list(APPEND BRIDGE_INCLUDE ${DEBUG_JSC_ENGINE}/Headers)
    #     add_library(JavaScriptCore SHARED IMPORTED)
    #     set_target_properties(JavaScriptCore PROPERTIES IMPORTED_LOCATION ${DEBUG_JSC_ENGINE}/JavaScriptCore)
    #     list(APPEND BRIDGE_LINK_LIBS JavaScriptCore)
  endif()
elseif ($ENV{BRIDGE_JS_ENGINE} MATCHES "v8")
  message("v8 not support")
endif()

if (DEFINED ENV{LIBRARY_OUTPUT_DIR})
  set_target_properties(my_bridge
          PROPERTIES
          LIBRARY_OUTPUT_DIRECTORY "$ENV{LIBRARY_OUTPUT_DIR}"
          )
  # set_target_properties(kraken_static PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "$ENV{LIBRARY_OUTPUT_DIR}")
elseif (IS_ANDROID)
  # android do nothing
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "release" OR ${CMAKE_BUILD_TYPE} STREQUAL "relwithdebinfo")
  ## http://ptspts.blogspot.com/2013/12/how-to-make-smaller-c-and-c-binaries.html
  ### remove dynamic_cast and exceptions
  target_compile_options(my_bridge PRIVATE -fno-exceptions -fvisibility=hidden)
else()
  ### remove dynamic_cast and exceptions
  target_compile_options(my_bridge PRIVATE -fno-exceptions)
endif()

target_include_directories(my_bridge PRIVATE
  ${BRIDGE_INCLUDE}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC ./include)
# We need hello.h and the hello library
# add_subdirectory(apps)
# link 自定义的library
target_link_libraries(my_bridge PRIVATE ${BRIDGE_LINK_LIBS})

# Tell C++ compiler to use C++20 features. We don't actually use any of them.
target_compile_features(my_bridge PUBLIC cxx_std_20)