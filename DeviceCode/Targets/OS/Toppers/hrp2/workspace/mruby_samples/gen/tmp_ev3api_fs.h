/*  1 "gen/tmp_C_src.c" */
/*  1 "<built-in>" */
/*  1 "<command-line>" */
/*  1 "gen/tmp_C_src.c" */
/*  27 "gen/tmp_C_src.c" */
typedef struct { int dummy; } va_list;

/*  1 "../../target/ev3_gcc/api/src/ev3api_fs.h" 1 */






       
/*  34 "../../target/ev3_gcc/api/src/ev3api_fs.h" */
typedef struct {
 void* buffer;
 uint32_t filesz;
 uint32_t buffersz;
} memfile_t;
/*  50 "../../target/ev3_gcc/api/src/ev3api_fs.h" */
typedef struct {
 uint32_t size;
 uint16_t date;
 uint16_t time;
    bool_t is_dir;
    bool_t is_readonly;
    bool_t is_hidden;
 char name[(255) + 1];
} fileinfo_t;
/*  78 "../../target/ev3_gcc/api/src/ev3api_fs.h" */
ER_ID ev3_sdcard_opendir(const char *path);
/*  99 "../../target/ev3_gcc/api/src/ev3api_fs.h" */
ER ev3_sdcard_readdir(ID dirid, fileinfo_t *p_fileinfo);
/*  117 "../../target/ev3_gcc/api/src/ev3api_fs.h" */
ER ev3_sdcard_closedir(ID dirid);
/*  141 "../../target/ev3_gcc/api/src/ev3api_fs.h" */
ER ev3_memfile_load(const char *path, memfile_t *p_memfile);
/*  160 "../../target/ev3_gcc/api/src/ev3api_fs.h" */
ER ev3_memfile_free(memfile_t *p_memfile);
/*  170 "../../target/ev3_gcc/api/src/ev3api_fs.h" */
typedef int32_t FILE;
typedef int32_t serial_port_t;
/*  189 "../../target/ev3_gcc/api/src/ev3api_fs.h" */
FILE* ev3_serial_open_file(serial_port_t port);
/*  200 "../../target/ev3_gcc/api/src/ev3api_fs.h" */
bool_t ev3_bluetooth_is_connected();
/*  30 "gen/tmp_C_src.c" 2 */
