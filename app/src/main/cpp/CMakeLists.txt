# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
#定义cmake支持的最小版本号
cmake_minimum_required(VERSION 3.4.1)

# ##################### OpenCV 环境

#设置OpenCV-android-sdk路径
set( OpenCV_DIR E:/opencv/OpenCV-android-sdk/sdk/native/jni )

find_package(OpenCV REQUIRED )
if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    message(STATUS "OpenCV library status:")
    message(STATUS "    version: ${OpenCV_VERSION}")
    message(STATUS "    libraries: ${OpenCV_LIBS}")
    message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
else(OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV library not found")
endif(OpenCV_FOUND)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        # 设置生成so库的文件名称，例如此处生成的so库文件名称应该为：native-lib.so
        native-lib

        # Sets the library as a shared library.
        # 设置生成的so库类型，类型只包含两种：
        # STATIC:静态库，为目标文件的归档文件，在链接其他目标的时候使用
        # SHARED:动态库，会被动态链接，在运行时被加载
        SHARED

        # Provides a relative path to your source file(s).
        # 设置源文件的位置，可以是很多个源文件，都要添加进来，注意相对位置
        native-lib.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
# 从系统里查找依赖库，可添加多个
find_library( # Sets the name of the path variable.
        # 例如查找系统中的log库liblog.so
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        # liblog.so库指定的名称即为log,如同上面指定生成的libnative-lib.so库名称为native-lib一样
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
# 配置目标库的链接，即相互依赖关系
target_link_libraries( # Specifies the target library.
        # 目标库（最终生成的库）
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        # 依赖于log库，一般情况下，如果依赖的是系统中的库，需要加 ${} 进行引用，
        # 如果是第三方库，可以直接引用库名，例如：
        # 引用第三方库libthird.a，引用时直接写成third;注意，引用时，每一行只能引用一个库
        ${log-lib})