#王畅 2016-08-02 
#要求CMake的最低版本为2.8 
cmake_minimum_required(VERSION 2.8)


#设置项目名称  
PROJECT (logger)

add_definitions(-DACE_AS_STATIC_LIBS)
add_definitions(-D_LINUX_)
add_definitions(-D_LINUX)

if (USE_DEBUG)
    add_definitions(-ggdb3)
endif(USE_DEBUG)	

if (USE_CPPUNIT)
endif(USE_CPPUNIT)	

if (USE_COV)
    add_definitions(-fprofile-arcs -ftest-coverage)
endif(USE_COV)	

set(CMAKE_CXX_FLAGS "-g -Wall")

#添加头文件搜索路径
INCLUDE_DIRECTORIES( ./)
INCLUDE_DIRECTORIES( $ENV{HOME}/include)


#用于将当前目录下的所有源文件的名字保存在变量中
aux_source_directory(../config SRC_CONFIG)
aux_source_directory(../common SRC_COMMON)
aux_source_directory(./ SRC_SOURCE)

SET(LINK_DIR $ENV{HOME}/lib
	)

#添加库文件搜索路径 
LINK_DIRECTORIES(${LINK_DIR})

SET(SRC_LIST ${SRC_CONFIG} ${SRC_COMMON} ${SRC_SOURCE})
ADD_LIBRARY(logger SHARED ${SRC_LIST}) 

if (USE_FOAF)
endif (USE_FOAF)

if (USE_CPPUNIT)
else()
    SET( EXE_SRC ${SRC_LIST} )
endif (USE_CPPUNIT)

#set (EXTRA_LIBS ncurses clntsh z occi ACE log rt ComFun curl ssl crypto gcov foaf)

#用于指定从一组源文件 source1 source2 … sourceN(在变量DIR_SRCS中定义)   
#编译出一个可执行文件且命名为CMake_Tutorial1  
#ADD_EXECUTABLE(CMake_Tutorial3 ${DIR_SRCS})
#add_executable (date_time ${EXE_SRC})
#添加编译可执行程序所需要的链接库、如果有多个中间用空格隔开  
#第一个参数是可执行程序名称，第二个开始是依赖库  
#在这里根据名字boost_thread去寻找libboost_thread.a文件 
  #target_link_libraries (date_time
	#${PROJECT_SOURCE_DIR}/lib/libssdb-client.a
     #${EXTRA_LIBS})

if (USE_DEBUG)
    MESSAGE(STATUS "USE DEBUG!!!!!!!!!!!!!")
    add_definitions(-g3)
else()
    MESSAGE(STATUS "USE RELEASE!!!!!!!!!!!!!")
endif (USE_DEBUG)

if (USE_COV)
    MESSAGE(STATUS "USE coverage!!!")
endif(USE_COV)

SET(HEADERS
	logger.h)
SET(CMAKE_INSTALL_PREFIX ../../)
INSTALL(TARGETS logger LIBRARY DESTINATION lib)
INSTALL(FILES ${HEADERS} DESTINATION include/clog4cpp)
