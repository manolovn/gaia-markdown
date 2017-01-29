set(gaia_ICONS
  16-apps-gaia.png
  22-apps-gaia.png
  32-apps-gaia.png
  48-apps-gaia.png
  sc-apps-gaia.svgz
)

ecm_install_icons(ICONS ${gaia_ICONS} DESTINATION ${ICON_INSTALL_DIR} THEME hicolor)
