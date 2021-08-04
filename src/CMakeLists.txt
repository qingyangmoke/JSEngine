# version 3.11 or later of CMake or needed later for installing GoogleTest
# so let's require it now.
cmake_minimum_required(VERSION 3.11-3.18)

project(JSEngineBridge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS -flto)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

string(TOLOWER ${CMAKE_SYSTEM_NAME} CMAKE_SYSTEM_NAME)
string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)


message("CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}")
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message("CMAKE_CXX_COMPILER_ID=Clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  message("CMAKE_CXX_COMPILER_ID=GNU")
  # using GCC
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  message("CMAKE_CXX_COMPILER_ID=Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  message("CMAKE_CXX_COMPILER_ID=MSVC")
  # using Visual Studio C++
endif()

if(${USE_MACRO})
  add_definitions(-DUSE_MACRO=1)
endif()

option(USE_MACRO_SWITCH "USE_MACRO_SWITCH" ON)

# 限制变量替换，让其只替换被 @VAR@ 引用的变量（那么 ${VAR} 格式的变量将不会被替换）。这在配置 ${VAR} 语法的脚本时是非常有用的。
configure_file(config.h.in config.h @ONLY)

list(APPEND PUBLIC_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/jsengine_bridge.h
)

#  specify the output directory as an include directory
include_directories(${CMAKE_CURRENT_BINARY_DIR})

list(APPEND APP_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/include/jsengine_bridge.h
  jsengine_bridge.cc
)

if ($ENV{BRIDGE_JS_ENGINE} MATCHES "jsc")
  list(APPEND APP_SOURCE
    core/jsengines/jsc/JSCoreContext.cc    
    core/jsengines/jsc/JSCoreConsole.cc    
    core/jsengines/jsc/JSCoreModule.cc
    core/jsengines/jsc/JSCoreHelper.cc
  )
elseif ($ENV{BRIDGE_JS_ENGINE} MATCHES "quickjs")
  list(APPEND APP_SOURCE
    core/jsengines/quickjs/QuickJSContext.cc
    core/jsengines/quickjs/QuickJSConsole.cc
    core/jsengines/quickjs/QuickJSModule.cc
  )
elseif ($ENV{BRIDGE_JS_ENGINE} MATCHES "v8")
  list(APPEND APP_SOURCE
    core/jsengines/v8/V8Context.cc
    core/jsengines/v8/V8Runtime.h
    core/jsengines/v8/V8Runtime.cc
    core/jsengines/v8/V8EngineAllocator.cc
    core/jsengines/v8/V8Console.cc
    core/jsengines/v8/V8EngineModule.cc
  )
endif()

list(APPEND APP_SOURCE
  core/Engine.cc 
  core/Scope.cc
  core/Context.cc
  core/NativeMethods.cc
  core/plugins/EnginePlugin.cc
  core/plugins/dom/DomPolyfill.cc
  core/plugins/dom/DomEnginePlugin.cc
  core/timer/Timer.cc
  core/timer/TimerManager.cc  
)

list(APPEND BRIDGE_INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

## 自定义一个library
add_library(jsengine_bridge_static STATIC ${APP_SOURCE})

# IOS配置 
if (${CMAKE_SYSTEM_NAME} MATCHES "ios")
  add_library(jsengine_bridge SHARED ${APP_SOURCE})
  set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")
  set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "")
  set_target_properties(jsengine_bridge PROPERTIES
    OUTPUT_NAME jsengine_bridge
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
  add_library(jsengine_bridge SHARED ${APP_SOURCE})
endif()

if ($ENV{BRIDGE_JS_ENGINE} MATCHES "jsc")
  add_definitions(-DBRIDGE_JS_ENGINE=1)
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
  add_definitions(-DBRIDGE_JS_ENGINE=2)
  if (${IS_ANDROID})
    message("IS_ANDROID=true")

    if("${ANDROID_ABI}" MATCHES "arm64-v8a$" OR "${ANDROID_ABI}" MATCHES "x86_64$")
      # Enable pointer compression on 64 bit platforms
      set(COMMON_CMAKE_ARGUMENTS "${COMMON_CMAKE_ARGUMENTS} -DV8_COMPRESS_POINTERS")
    endif()

    list(APPEND BRIDGE_INCLUDE
              ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/v8/include
              )
    target_link_libraries(jsengine_bridge "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/v8/libs/${ANDROID_ABI}/libv8_base.a")
    target_link_libraries(jsengine_bridge "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/v8/libs/${ANDROID_ABI}/libv8_snapshot.a")
    target_link_libraries(jsengine_bridge "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/v8/libs/${ANDROID_ABI}/libv8_init.a")
    target_link_libraries(jsengine_bridge "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/v8/libs/${ANDROID_ABI}/libv8_initializers.a")
    target_link_libraries(jsengine_bridge "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/v8/libs/${ANDROID_ABI}/libv8_libplatform.a")
    target_link_libraries(jsengine_bridge "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/v8/libs/${ANDROID_ABI}/libv8_libsampler.a")
    target_link_libraries(jsengine_bridge "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/v8/libs/${ANDROID_ABI}/libv8_libbase.a")

    # if("${ANDROID_ABI}" MATCHES "armeabi-v7a$" OR "${ANDROID_ABI}" MATCHES "x86$")
    #   # On API Level 19 and lower we need to link with android_support
    #   # because it contains some implementation of functions such as "strtoll" and "strtoul"
    #   message("# Linking with libandroid_support.a")
    #   target_link_libraries(jsengine_bridge "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/v8/libs/${ANDROID_ABI}/libandroid_support.a")
    # endif()
    find_library(system-log log)
    find_library(system-z z)
    find_library(system-android android)

    # Command info: https://cmake.org/cmake/help/v3.4/command/target_link_libraries.html
    # Specifies libraries CMake should link to your target library.
    target_link_libraries(jsengine_bridge ${system-log} ${system-z} ${system-android})
  else ()    
    message("v8 not support IOS ")
  endif()
elseif ($ENV{BRIDGE_JS_ENGINE} MATCHES "quickjs")
  message("BRIDGE_JS_ENGINE=quickjs")
  add_definitions(-DBRIDGE_JS_ENGINE=3)
  list(APPEND BRIDGE_INCLUDE
            ${CMAKE_CURRENT_SOURCE_DIR}/../third_party/quickjs
            )
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../third_party/quickjs/quickjs ${CMAKE_CURRENT_SOURCE_DIR}/../build/quickjs)
  list(APPEND BRIDGE_LINK_LIBS quickjs)
endif()

if (DEFINED ENV{LIBRARY_OUTPUT_DIR})
  set_target_properties(jsengine_bridge
          PROPERTIES
          LIBRARY_OUTPUT_DIRECTORY "$ENV{LIBRARY_OUTPUT_DIR}"
          )
elseif (IS_ANDROID)
  # android do nothing
endif()

# if (${CMAKE_BUILD_TYPE} STREQUAL "release" OR ${CMAKE_BUILD_TYPE} STREQUAL "relwithdebinfo")
#   ## http://ptspts.blogspot.com/2013/12/how-to-make-smaller-c-and-c-binaries.html
#   ### remove dynamic_cast and exceptions
#   target_compile_options(jsengine_bridge PRIVATE -fno-exceptions -fvisibility=hidden)
# else()
#   ### remove dynamic_cast and exceptions
#   target_compile_options(jsengine_bridge PRIVATE -fno-exceptions)
# endif()

target_include_directories(jsengine_bridge PRIVATE
  ${BRIDGE_INCLUDE}
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}
  PUBLIC ./include)

# link 自定义的library
target_link_libraries(jsengine_bridge PRIVATE ${BRIDGE_LINK_LIBS})

# Tell C++ compiler to use C++20 features. We don't actually use any of them.
target_compile_features(jsengine_bridge PUBLIC cxx_std_20)