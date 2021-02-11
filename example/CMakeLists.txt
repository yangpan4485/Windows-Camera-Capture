set(DEMO_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/device_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/device_window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/main_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main_window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/my_window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/my_window.h
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/sink_filter_ds.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/sink_filter_ds.h
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_capture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_capture.h
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_capture_ds.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_capture_ds.h
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_device_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_device_manager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_device_observer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_device_observer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_message_loop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_message_loop.h
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_device_ds.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_device_ds.h
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/video_utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/capture_frame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/capture/capture_frame.h
    ${CMAKE_CURRENT_SOURCE_DIR}/common/video_frame.h
    ${CMAKE_CURRENT_SOURCE_DIR}/common/string_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/string_utils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/common/json.hpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/render/video_render.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/render/d2d/video_render_d2d.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/render/d2d/video_render_d2d.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/render/d3d9/video_render_d3d9.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/render/d3d9/video_render_d3d9.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/render/gdi/video_render_gdi.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/render/gdi/video_render_gdi.h
    # ${CMAKE_CURRENT_SOURCE_DIR}/render/opengl/video_render_opengl.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/render/opengl/video_render_opengl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/render/sdl2/video_render_sdl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/render/sdl2/video_render_sdl.h
    )

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third/lib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../DuiLib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third/include/jpeg)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third/include/sdl2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../third/include/yuv)


add_executable(capture_demo ${DEMO_SOURCE})

target_link_libraries(capture_demo  SDL2
                                    SDL2main
                                    yuv
                                    duilib
                                    jpeg
                                    strmiids)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT capture_demo)