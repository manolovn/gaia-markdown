set(gaia_ICONS
  hi16-apps-gaia.png
  hi22-apps-gaia.png
  hi32-apps-gaia.png
  hi48-apps-gaia.png
  hisc-apps-gaia.svgz
)

ecm_install_icons(ICONS ${gaia_ICONS} DESTINATION ${ICON_INSTALL_DIR} THEME hicolor)
