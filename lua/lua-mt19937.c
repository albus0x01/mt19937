#include <lua.h>
#include <lauxlib.h>
#include<mt19937-64.h>

static int lrandomseed(lua_State *L){
    mt19937 *mt = lua_touserdata(L, lua_upvalueindex(1));
    uint32_t seed = (uint32_t)luaL_checknumber(L, 1);
    mt19937_seed(mt, seed);
    return 0;
}

static int lrandom(lua_State *L){
    mt19937 *mt = lua_touserdata(L, lua_upvalueindex(1));
    uint64_t r = mt19937_uint64(mt);
    lua_Integer low, up;
    switch(lua_gettop(L)){
        case 0:{
            lua_pushnumber(L, (lua_Number)r);
            return 1;
        }
        case 1:{
            low = 1;
            up = luaL_checkinteger(L, 1);
            break;
        }
        case 2:{
            low = luaL_checkinteger(L, 1);
            up = luaL_checkinteger(L, 2);
            break;
        }
        default:{
            return luaL_error(L, "wrong number of arguments");
        }
    }
    if(up <= low){
        return luaL_error(L, "invalid param");
    }
    r = r % (up - low) + low;
    lua_pushinteger(L, r);
    return 1;
}

static int lgc(lua_State *L){
    // printf("mt19937 gc\n");
    mt19937 *mt = lua_touserdata(L, lua_upvalueindex(1));
    mt19937_free(mt);
    return 0;
}

int
luaopen_mt19937(lua_State *L){
    luaL_checkversion(L);
    luaL_Reg l[] = {
        {"randomseed", lrandomseed},
        {"random", lrandom},
        {NULL, NULL},
    };
    luaL_newlibtable(L, l);
    mt19937 *mt = mt19937_new();
    lua_pushlightuserdata(L, mt);
    luaL_setfuncs(L, l, 1);
    lua_createtable(L, 0, 1);
    lua_pushcfunction(L, lgc);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);
    return 1;
}