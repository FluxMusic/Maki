add_executable(Maki)

ecm_add_qml_module(Maki
    URI
    io.github.FluxMusic.Maki
)

target_include_directories(Maki
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/backend"
)

target_sources(Maki
    PRIVATE
    main.cpp
    backend/WindowManager.cpp
    backend/WindowManager.h
)

ecm_target_qml_sources(Maki
    SOURCES
    Main.qml
)

target_link_libraries(Maki
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui
    Qt6::Widgets
    KF6::I18n
    KF6::CoreAddons
    KF6::IconThemes
)

install(TARGETS Maki ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})