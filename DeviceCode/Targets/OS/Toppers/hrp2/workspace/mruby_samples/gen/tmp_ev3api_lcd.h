/*  1 "gen/tmp_C_src.c" */
/*  1 "<built-in>" */
/*  1 "<command-line>" */
/*  1 "gen/tmp_C_src.c" */
/*  27 "gen/tmp_C_src.c" */
typedef struct { int dummy; } va_list;

/*  1 "../../target/ev3_gcc/api/src/ev3api_lcd.h" 1 */






       
/*  32 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
typedef int32_t lcdfont_t;
/*  48 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
typedef int32_t lcdcolor_t;
/*  72 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
ER ev3_lcd_set_font(lcdfont_t font);
/*  89 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
ER ev3_font_get_size(lcdfont_t font, int32_t *p_width, int32_t *p_height);
/*  99 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
typedef struct {
    int32_t width;
    int32_t height;
    void* data;
} image_t;
/*  121 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
ER ev3_image_load(const memfile_t *p_memfile, image_t *p_image);
/*  134 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
ER ev3_image_free(image_t *p_image);
/*  147 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
ER ev3_lcd_draw_string(const char *str, int32_t x, int32_t y);
/*  161 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
ER ev3_lcd_draw_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
/*  176 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
ER ev3_lcd_fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, lcdcolor_t color);
/*  190 "../../target/ev3_gcc/api/src/ev3api_lcd.h" */
ER ev3_lcd_draw_image(const image_t *p_image, int32_t x, int32_t y);
/*  30 "gen/tmp_C_src.c" 2 */
