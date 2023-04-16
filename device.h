#ifndef DEVICE_H
#define DEVICE_H

#include <lua.h>

#define MACROL_DEVICE "macrol_device"

void macrol_create_device_metatable(lua_State *L);

int macrol_open_device(lua_State *L);
int macrol_close_device(lua_State *L);

#endif
