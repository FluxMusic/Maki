add_executable(Maki)

ecm_add_qml_module(Maki
    URI
    io.github.FluxMusic.Maki
)

target_include_directories(Maki
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/backend"
    "${CMAKE_CURRENT_SOURCE_DIR}/mpv"
)

target_sources(Maki
    PRIVATE
    main.cpp
    backend/WindowManager.cpp
    backend/WindowManager.h
    backend/ImageProvider.h
    mpv/MpvItem.h
    mpv/MpvItem.cpp
)

ecm_target_qml_sources(Maki
    SOURCES
    Main.qml
    qml/ImagePreview.qml
    qml/FallbackPreview.qml
    qml/TextPreview.qml
    qml/AudioPreview.qml
    qml/VideoPreview.qml
    qml/DocumentPreview.qml
)

target_link_libraries(Maki
    PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui
    Qt6::Widgets
    Qt6::Multimedia
    KF6::I18n
    KF6::CoreAddons
    KF6::IconThemes
    Poppler::Qt6
    MpvQt::MpvQt
)

install(TARGETS Maki ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})