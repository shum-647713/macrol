#include <lauxlib.h>
#include <lua.h>

const luaL_Reg macrol_lib[] = {{NULL, NULL}};

int luaopen_macrol(lua_State *L) {
  luaL_newlib(L, macrol_lib);

  return 1;
}
