cmake_minimum_required(VERSION 3.16)
project(Afrika)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 COMPONENTS Widgets WebEngineWidgets REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/ui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/storage)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/utils)

add_executable(Afrika
	src/main.cpp
	src/ui/BrowserWindow.cpp
	src/ui/BrowserWindowMenu.cpp
	src/ui/BrowserWindowTabs.cpp
	src/ui/BrowserWindowNavigation.cpp
	src/ui/BrowserWindowSession.cpp
	src/ui/UIStyleSheetToolbar.cpp
	src/ui/UIStyleSheetTabs.cpp
	src/ui/UIStyleSheetDialogs.cpp
	src/utils/UrlUtils.cpp
	src/storage/SessionStorage.cpp
	src/storage/Settings.cpp
)

target_link_libraries(Afrika PRIVATE Qt6::Widgets Qt6::WebEngineWidgets)
