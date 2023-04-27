#include "device.h"
#include "event.h"
#include <errno.h>
#include <lauxlib.h>
#include <lua.h>
#include <stdio.h>
#include <string.h>

const luaL_Reg macrol_device_metatable[] = {{NULL, NULL}};
const luaL_Reg macrol_device_methods[] = {{"close", macrol_close_device},
                                          {"read", macrol_read_event},
                                          {"write", macrol_write_event},
                                          {"flush", macrol_flush_device},
                                          {NULL, NULL}};

void macrol_create_device_metatable(lua_State *L) {
  luaL_newmetatable(L, MACROL_DEVICE);
  luaL_setfuncs(L, macrol_device_metatable, 0);

  luaL_newlibtable(L, macrol_device_methods);
  luaL_setfuncs(L, macrol_device_methods, 0);
  lua_setfield(L, -2, "__index");

  lua_pop(L, 1);
}

int macrol_open_device(lua_State *L) {
  const char *pathname = luaL_checkstring(L, 1);
  const char *mode = luaL_checkstring(L, 2);

  FILE *device = fopen(pathname, mode);
  if (device == NULL) {
    return luaL_error(L, "%s", strerror(errno));
  }

  lua_pushlightuserdata(L, device);
  luaL_setmetatable(L, MACROL_DEVICE);

  return 1;
}

int macrol_close_device(lua_State *L) {
  FILE *device = luaL_checkudata(L, 1, MACROL_DEVICE);

  if (fclose(device) != 0) {
    return luaL_error(L, "%s", strerror(errno));
  }

  return 0;
}

int macrol_flush_device(lua_State *L) {
  FILE *device = luaL_checkudata(L, 1, MACROL_DEVICE);

  if (fflush(device) != 0) {
    return luaL_error(L, "%s", strerror(errno));
  }

  return 0;
}
