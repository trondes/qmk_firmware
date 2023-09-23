MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = yes
RGBLIGHT_ENABLE = yes
OLED_ENABLE = yes # turn off this to get 6k more free space. but then the screen
                  # will not work, but when are you looking on the keyboard?
# OLED_DRIVER = SSD1306 # when building with the new version this gave me an error. trying wihout
TAP_DANCE_ENABLE = yes 
RGB_MATRIX_ENABLE = no
# Enabling link-time optimization saves about 3 kilobytes.
# https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/
EXTRAFLAGS += -flto


SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no 
MAGIC_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
EXTRAKEY_ENABLE = no


