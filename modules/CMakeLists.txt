
add_library(ksmaxis_module)

target_sources(ksmaxis_module
    PUBLIC
        FILE_SET CXX_MODULES FILES
            ksmaxis.cppm
)

target_compile_features(ksmaxis_module PUBLIC cxx_std_20)

target_include_directories(ksmaxis_module PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(ksmaxis::module ALIAS ksmaxis_module)

# Installation
install(TARGETS ksmaxis_module
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    FILE_SET CXX_MODULES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ksmaxis/modules
)
