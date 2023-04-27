#include "event.h"
#include "device.h"
#include <errno.h>
#include <lauxlib.h>
#include <linux/input.h>
#include <lua.h>
#include <stdio.h>
#include <string.h>

int macrol_read_event(lua_State *L) {
  FILE *device = luaL_checkudata(L, 1, MACROL_DEVICE);
  struct input_event event = {0};

  if (fread(&event, sizeof(event), 1, device) != 1) {
    if (ferror(device)) {
      return luaL_error(L, "%s", strerror(errno));
    }
    return 0;
  }

  lua_newtable(L);
  lua_pushinteger(L, event.time.tv_sec);
  lua_setfield(L, -2, "tv_sec");
  lua_pushinteger(L, event.time.tv_usec);
  lua_setfield(L, -2, "tv_usec");
  lua_pushinteger(L, event.type);
  lua_setfield(L, -2, "type");
  lua_pushinteger(L, event.code);
  lua_setfield(L, -2, "code");
  lua_pushinteger(L, event.value);
  lua_setfield(L, -2, "value");

  return 1;
}

int macrol_write_event(lua_State *L) {
  FILE *device = luaL_checkudata(L, 1, MACROL_DEVICE);
  struct input_event event = {0};

  if (lua_getfield(L, 2, "type") != LUA_TNUMBER) {
    return luaL_argerror(L, 2, "expected number in 'type' field");
  }
  event.type = lua_tonumber(L, -1);

  if (lua_getfield(L, 2, "code") != LUA_TNUMBER) {
    return luaL_argerror(L, 2, "expected number in 'code' field");
  }
  event.code = lua_tonumber(L, -1);

  if (lua_getfield(L, 2, "value") != LUA_TNUMBER) {
    return luaL_argerror(L, 2, "expected number in 'value' field");
  }
  event.value = lua_tonumber(L, -1);

  if (fwrite(&event, sizeof(event), 1, device) != 1) {
    return luaL_error(L, "%s", strerror(errno));
  }

  return 0;
}
