OLED_ENABLE = yes
OLED_DRIVER = SSD1306
KEY_OVERRIDE_ENABLE = yes

# Reduce firmware size
LTO_ENABLE = yes
BOOTMAGIC_ENABLE = no
MOUSEKEY_ENABLE = no

SRC += keycode_to_char.c
