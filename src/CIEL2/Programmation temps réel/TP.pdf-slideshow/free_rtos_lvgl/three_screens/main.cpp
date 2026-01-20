#include <Arduino.h>
#include <M5Unified.h>
#include <lvgl_freertos_glue.hpp>
#include <esp_timer.h>

#define LV_CONF_INCLUDE_SIMPLE
#include <lvgl.h>
#include <array>

constexpr std::size_t ScreenCount = 3;
std::array<lv_obj_t *, ScreenCount> screens{};
std::size_t currentScreen = 0;

void gesture_event_cb(lv_event_t *e)
{
  auto *indev = lv_indev_active();

  const lv_dir_t dir = lv_indev_get_gesture_dir(indev);
  switch (dir)
  {
  case LV_DIR_LEFT:
    Serial.print("Gesture left: ");
    currentScreen = (currentScreen + ScreenCount - 1) % ScreenCount;
    break;

  case LV_DIR_RIGHT:
    Serial.print("Gesture right: ");
    currentScreen = (currentScreen + 1) % ScreenCount;
    break;

  default:
    return;
  }

  Serial.printf("%u\n", static_cast<unsigned>(currentScreen));

  lv_screen_load_anim(
      screens[currentScreen],
      LV_SCREEN_LOAD_ANIM_FADE_IN,
      500,
      0,
      false);
}

static void create_wifi_msgbox(lv_obj_t *parent)
{
  static lv_obj_t *wifi_msgbox = nullptr;

  if (wifi_msgbox != nullptr)
    return;

  wifi_msgbox = lv_msgbox_create(parent);
  lv_obj_set_width(wifi_msgbox, 260);
  lv_obj_set_height(wifi_msgbox, LV_SIZE_CONTENT);
  lv_obj_center(wifi_msgbox);

  lv_msgbox_add_title(wifi_msgbox, "Parametres WiFi");

  lv_obj_t *content = lv_msgbox_get_content(wifi_msgbox);
  lv_obj_set_style_pad_all(content, 10, 0);
  lv_obj_set_flex_flow(content, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(content, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

  lv_obj_t *label_ssid = lv_label_create(content);
  lv_label_set_text(label_ssid, "SSID :");

  lv_obj_t *ta_ssid = lv_textarea_create(content);
  lv_textarea_set_one_line(ta_ssid, true);
  lv_obj_set_width(ta_ssid, LV_PCT(100));
  lv_textarea_set_placeholder_text(ta_ssid, "Nom du reseau");

  lv_obj_t *label_pass = lv_label_create(content);
  lv_label_set_text(label_pass, "Mot de passe :");

  lv_obj_t *ta_password = lv_textarea_create(content);
  lv_textarea_set_one_line(ta_password, true);
  lv_textarea_set_password_mode(ta_password, true);
  lv_obj_set_width(ta_password, LV_PCT(100));
  lv_textarea_set_placeholder_text(ta_password, "Mot de passe");

  lv_msgbox_add_footer_button(wifi_msgbox, "Annuler");
  lv_msgbox_add_footer_button(wifi_msgbox, "OK");
}

lv_obj_t *create_settings_button(lv_obj_t *screen)
{
  lv_obj_t *float_btn = lv_button_create(screen);
  lv_obj_set_size(float_btn, 50, 50);
  lv_obj_add_flag(float_btn, LV_OBJ_FLAG_FLOATING);
  lv_obj_align(float_btn, LV_ALIGN_BOTTOM_RIGHT, -16, -16);
  lv_obj_set_style_radius(float_btn, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_bg_image_src(float_btn, LV_SYMBOL_SETTINGS, 0);
  lv_obj_set_style_text_font(float_btn, lv_theme_get_font_large(float_btn), 0);

  auto settings_clicked_event_cb{
      [](lv_event_t *e) -> void
      {
        create_wifi_msgbox(lv_screen_active());
      }};

  lv_obj_add_flag(float_btn, LV_OBJ_FLAG_CLICKABLE);
  lv_obj_add_event_cb(float_btn, settings_clicked_event_cb, LV_EVENT_CLICKED, nullptr);

  return float_btn;
}

lv_obj_t *create_temp_screen()
{
  // View
  lv_obj_t *screen = lv_obj_create(nullptr);

  static lv_subject_t value;
  lv_subject_init_int(&value, 0);

  lv_obj_t *knob = lv_arc_create(screen);
  lv_obj_set_size(knob, 150, 150);
  lv_arc_set_rotation(knob, 135);
  lv_arc_set_bg_angles(knob, 0, 270);
  lv_slider_set_max_value(knob, 100);
  lv_slider_set_min_value(knob, 0);
  lv_obj_center(knob);

  lv_arc_bind_value(knob, &value);

  lv_obj_t *info_label = lv_label_create(screen);

  lv_obj_t *scale = lv_scale_create(screen);
  lv_obj_set_size(scale, 150, 150);
  lv_scale_set_label_show(scale, true);
  lv_scale_set_mode(scale, LV_SCALE_MODE_ROUND_OUTER);
  lv_obj_center(scale);

  lv_scale_set_total_tick_count(scale, 21);
  lv_scale_set_major_tick_every(scale, 5);

  lv_obj_set_style_length(scale, 5, LV_PART_ITEMS);
  lv_obj_set_style_length(scale, 10, LV_PART_INDICATOR);
  lv_scale_set_range(scale, 0, 100);

  static const char *custom_labels[] = {"0 °C", "25 °C", "50 °C", "75 °C", "100 °C", NULL};
  lv_scale_set_text_src(scale, custom_labels);

  static lv_style_t indicator_style;
  lv_style_init(&indicator_style);

  lv_style_set_text_font(&indicator_style, LV_FONT_DEFAULT);
  lv_style_set_text_color(&indicator_style, lv_palette_darken(LV_PALETTE_BLUE, 3));

  lv_style_set_line_color(&indicator_style, lv_palette_darken(LV_PALETTE_BLUE, 3));
  lv_style_set_width(&indicator_style, 10U);
  lv_style_set_line_width(&indicator_style, 2U);
  lv_obj_add_style(scale, &indicator_style, LV_PART_INDICATOR);

  static lv_style_t minor_ticks_style;
  lv_style_init(&minor_ticks_style);
  lv_style_set_line_color(&minor_ticks_style, lv_palette_lighten(LV_PALETTE_BLUE, 2));
  lv_style_set_width(&minor_ticks_style, 5U);
  lv_style_set_line_width(&minor_ticks_style, 2U);
  lv_obj_add_style(scale, &minor_ticks_style, LV_PART_ITEMS);

  static lv_style_t main_line_style;
  lv_style_init(&main_line_style);

  lv_style_set_arc_color(&main_line_style, lv_palette_darken(LV_PALETTE_BLUE, 3));
  lv_style_set_arc_width(&main_line_style, 2U);
  lv_obj_add_style(scale, &main_line_style, LV_PART_MAIN);

  static lv_style_t section_minor_tick_style;
  static lv_style_t section_label_style;
  static lv_style_t section_main_line_style;

  lv_style_init(&section_label_style);
  lv_style_init(&section_minor_tick_style);
  lv_style_init(&section_main_line_style);

  lv_style_set_text_font(&section_label_style, LV_FONT_DEFAULT);
  lv_style_set_text_color(&section_label_style, lv_palette_darken(LV_PALETTE_RED, 3));

  lv_style_set_line_color(&section_label_style, lv_palette_darken(LV_PALETTE_RED, 3));
  lv_style_set_line_width(&section_label_style, 5U);

  lv_style_set_line_color(&section_minor_tick_style, lv_palette_lighten(LV_PALETTE_RED, 2));
  lv_style_set_line_width(&section_minor_tick_style, 4U);

  lv_style_set_arc_color(&section_main_line_style, lv_palette_darken(LV_PALETTE_RED, 3));
  lv_style_set_arc_width(&section_main_line_style, 4U);

  lv_scale_section_t *section = lv_scale_add_section(scale);
  lv_scale_set_section_range(scale, section, 75, 100);
  lv_scale_set_section_style_indicator(scale, section, &section_label_style);
  lv_scale_set_section_style_items(scale, section, &section_minor_tick_style);
  lv_scale_set_section_style_main(scale, section, &section_main_line_style);

  create_settings_button(screen);

  // ViewModel
  auto knob_event_cb{
      [](lv_event_t *e) -> void
      {
        auto *info_label = static_cast<lv_obj_t *>(lv_event_get_user_data(e));
        auto *knob = lv_event_get_target_obj(e);

        if (!info_label || !knob)
        {
          return;
        }

        lv_label_set_text_fmt(info_label, "%d °C", lv_slider_get_value(knob));
        lv_arc_rotate_obj_to_angle(knob, info_label, 25);
      }};

  lv_obj_add_event_cb(knob, knob_event_cb, LV_EVENT_VALUE_CHANGED, info_label);
  lv_obj_send_event(knob, LV_EVENT_VALUE_CHANGED, info_label);

  return screen;
}

lv_obj_t *create_light_screen()
{
  // View
  lv_obj_t *screen = lv_obj_create(nullptr);

  lv_obj_t *light = lv_led_create(screen);
  lv_obj_align(light, LV_ALIGN_CENTER, 0, -50);
  lv_obj_set_size(light, 64, 64);
  lv_led_set_color(light, lv_palette_main(LV_PALETTE_YELLOW));
  lv_led_on(light);

  lv_obj_t *sw = lv_switch_create(screen);
  lv_obj_set_size(sw, 30, 60);
  lv_obj_align(sw, LV_ALIGN_BOTTOM_MID, 0, -50);
  lv_switch_set_orientation(sw, LV_SWITCH_ORIENTATION_VERTICAL);
  lv_obj_add_state(sw, LV_STATE_CHECKED);

  // ViewModel
  auto switch_changed_event_cb{
      [](lv_event_t *e) -> void
      {
        auto *light = static_cast<lv_obj_t *>(lv_event_get_user_data(e));
        lv_obj_t *obj = lv_event_get_target_obj(e);

        if (lv_obj_has_state(obj, LV_STATE_CHECKED))
        {
          lv_led_on(light);
        }
        else
        {
          lv_led_off(light);
        }
      }};

  lv_obj_add_event_cb(sw, switch_changed_event_cb, LV_EVENT_VALUE_CHANGED, light);
  lv_obj_send_event(sw, LV_EVENT_VALUE_CHANGED, light);

  return screen;
}

lv_obj_t *create_air_quality_screen()
{
  lv_obj_t *screen = lv_obj_create(nullptr);

  lv_obj_t *info_label = lv_label_create(screen);
  lv_label_set_text(info_label, "Third screen");
  lv_obj_center(info_label);

  return screen;
}

void setup()
{
  M5.begin();
  lfg_m5::init();
  Serial.begin(115200);

  screens[0] = create_temp_screen();
  screens[1] = create_light_screen();
  screens[2] = create_air_quality_screen();

  for (auto *screen : screens)
  {
    lv_obj_add_event_cb(
        screen,
        gesture_event_cb,
        LV_EVENT_GESTURE,
        nullptr);
  }

  lv_screen_load(screens[currentScreen]);
}

void loop()
{
  lfg_m5::update();
  vTaskDelay(pdMS_TO_TICKS(1));
}
