set(gaia_SRCS
    main.cpp
    gaia.cpp
    gaiaview.cpp
)

kconfig_add_kcfg_files(gaia_SRCS gaiaSettings.kcfgc)
ki18n_wrap_ui(gaia_SRCS gaiaViewBase.ui settingsBase.ui)

add_executable(gaia ${gaia_SRCS})

target_link_libraries(gaia
    Qt5::Widgets
    KF5::CoreAddons
    KF5::I18n
    KF5::XmlGui
    KF5::ConfigWidgets
    markdown
)

install(TARGETS gaia ${INSTALL_TARGETS_DEFAULT_ARGS})
install(PROGRAMS gaia.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR})
install(FILES gaiaui.rc DESTINATION ${KXMLGUI_INSTALL_DIR}/gaia)