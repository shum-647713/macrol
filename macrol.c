#include "device.h"
#include "event.h"
#include <lauxlib.h>
#include <lua.h>

const luaL_Reg macrol_lib[] = {
    {"open", macrol_open_device},   {"close", macrol_close_device},
    {"read", macrol_read_event},    {"write", macrol_write_event},
    {"flush", macrol_flush_device}, {NULL, NULL}};

int luaopen_macrol(lua_State *L) {
  macrol_create_device_metatable(L);

  luaL_newlib(L, macrol_lib);

  return 1;
}
