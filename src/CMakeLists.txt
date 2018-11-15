
add_executable(${PROJECT_NAME}
    main.cpp
    gui/openglapp.cpp

    gui/openglapp.h
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    ${PROJECT_NAME}-submodules
)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
