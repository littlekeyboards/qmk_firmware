#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _QWERTY 0
#define _NAVIGATION 1
#define _CODE 2
#define _CONSTANTS 3
#define _NUMBERS_AND_SYMBOLS 4
#define _ADJUST 9

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  RGBRST,
  END_CONSTANT,
  NAVIGATION_ENTER,
  NUMBERS_SPACE,
  CODE_SPACE,
  COMMAND_ESCAPE,
  ALT_CONSTANTS
};

#define KC_ KC_TRNS
#define KC_RST   RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD

#define KC_RSMOD RGB_RMOD

#define KC_LCCA CTL_T(KC_TAB)
#define KC_SHDE  MT(MOD_LSFT, KC_DEL) // Tap for delete, hold for left shift
#define KC_RSEN MT(MOD_RSFT, KC_ENT) // Tap for enter, hold for right shift
#define KC_ALTDEL MT(MOD_LALT, KC_DEL) // Tap for enter, hold for left alt
#define KC_NAVENT NAVIGATION_ENTER
#define KC_NUMSPC NUMBERS_SPACE
#define KC_CODE MO(_CODE)
#define KC_CTLESC COMMAND_ESCAPE
#define KC_ALTCON ALT_CONSTANTS
#define KC_GUIDEL GUI_T(KC_DEL)

#define KC_TO_DEF TO(_QWERTY)
#define KC_ENDCON END_CONSTANT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
     CTLESC,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B,                      N,     M,  COMM,   DOT,  SLSH,  RSEN,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                 ALTDEL,NUMSPC,NAVENT,   SPC, CODE,GUIDEL \
                              //`--------------------'  `--------------------'
  ),

  [_NAVIGATION] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
           ,      ,      ,  UP  ,      ,      ,                       ,      ,      ,      ,      ,      ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
           ,      , LEFT , DOWN , RIGHT,      ,                       ,      ,      ,      ,      ,      ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
           ,      ,      ,      ,      ,      ,                       ,      ,      ,      ,      ,      ,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                       ,      ,      ,         ,      ,       \
                              //`--------------------'  `--------------------'
  ),

  [_CODE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
           ,      ,      , LCBR , RCBR ,      ,                       ,AMPR  ,PIPE  ,      ,      ,      ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
           ,      ,      , LPRN , RPRN ,      ,                       ,UNDS  ,MINS  ,      ,      , BSLS ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
           ,      ,      , LBRC , RBRC ,      ,                       ,PLUS  ,EQL   ,      , BSLS ,      ,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                       ,      ,      ,         ,      ,       \
                              //`--------------------'  `--------------------'
  ),

  [_NUMBERS_AND_SYMBOLS] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
           ,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0, GRV  ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
           ,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN, TILD ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
           ,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10,      ,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                       ,      ,      ,         ,      ,       \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      LRST , LTOG ,      ,      ,      , RST  ,                       ,      ,      ,      ,      ,      ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
           ,      ,  LHUI,  LSAI, LVAI ,      ,                       ,      ,      ,      ,      ,      ,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
           , RSMOD,  LHUD,  LSAD, LVAD ,      ,                       ,      ,      ,      ,      ,      ,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                       ,      ,      ,         ,      ,       \
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

uint16_t custom_lt_timer;
keypos_t prv_key_pressed;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  inline void tap(uint16_t keycode) {
    register_code(keycode);
    unregister_code(keycode);
  };

  if (record->event.pressed) {
    #ifdef SSD1306OLED
        set_keylog(keycode, record);
    #endif
    prv_key_pressed = record->event.key;
    // set_timelog();
  }

  #define IS_KEYPOS_SAME(keyone,keytwo)  ((keyone.col==keytwo.col)&&(keyone.row==keytwo.row))
  #define ANOTHER_KEY_PRESSED (!IS_KEYPOS_SAME(prv_key_pressed, record->event.key))

  switch (keycode) {
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case NAVIGATION_ENTER:
      if (record->event.pressed) {
        custom_lt_timer = timer_read();
        layer_on(_NAVIGATION);
      } else {
        layer_off(_NAVIGATION);
        if (timer_elapsed(custom_lt_timer)<150 && (!ANOTHER_KEY_PRESSED)) {
          tap(KC_ENT);
        }
      }
      return false;
      break;
        case NUMBERS_SPACE:
      if (record->event.pressed) {
        custom_lt_timer = timer_read();
        layer_on(_NUMBERS_AND_SYMBOLS);
        update_tri_layer_RGB(_NUMBERS_AND_SYMBOLS, _CODE, _ADJUST);
      } else {
        layer_off(_NUMBERS_AND_SYMBOLS);
        update_tri_layer_RGB(_NUMBERS_AND_SYMBOLS, _CODE, _ADJUST);
        if (timer_elapsed(custom_lt_timer)<150 && (!ANOTHER_KEY_PRESSED)) {
          tap(KC_SPC);
        }
      }
      return false;
      break;
    case CODE_SPACE:
      if (record->event.pressed) {
        custom_lt_timer = timer_read();
        layer_on(_CODE);
        update_tri_layer_RGB(_NUMBERS_AND_SYMBOLS, _CODE, _ADJUST);
      } else {
        layer_off(_CODE);
        update_tri_layer_RGB(_NUMBERS_AND_SYMBOLS, _CODE, _ADJUST);
        if (timer_elapsed(custom_lt_timer)<150 && (!ANOTHER_KEY_PRESSED)) {
          tap(KC_SPC);
        }
      }
      return false;
      break;
    case ALT_CONSTANTS:
      if (record->event.pressed) {
        custom_lt_timer = timer_read();
        register_code(KC_LALT);
      } else {
        unregister_code(KC_LALT);
        if (timer_elapsed(custom_lt_timer)<150 && (!ANOTHER_KEY_PRESSED)) {
          layer_on(_CONSTANTS);
        }
      }
      return false;
      break;
    case COMMAND_ESCAPE:
      if (record->event.pressed) {
        custom_lt_timer = timer_read();
        register_code(KC_LCTL);
      } else {
        unregister_code(KC_LCTL);
        if (timer_elapsed(custom_lt_timer)<150 && (!ANOTHER_KEY_PRESSED)) {
          tap(KC_ESC);
        }
      }
      return false;
      break;
    case END_CONSTANT:
      if (record->event.pressed) {
        SEND_STRING(" = ");
        layer_off(_CONSTANTS);
      }
      return false;
      break;
    }
  return true;
}
