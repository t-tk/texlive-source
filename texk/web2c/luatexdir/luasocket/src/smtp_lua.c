/*
 * This file is auto-generated by "lua2c smtp.lua smtp_lua"
 */

#include "lua.h"
#include "lauxlib.h"

int luatex_smtp_lua_open (lua_State *L) { 
    static unsigned char B[] = {
    45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 10, 45, 45,
 32, 83, 77, 84, 80, 32, 99,108,105,101,110,116, 32,115,117,112,112,111,114,116,
 32,102,111,114, 32,116,104,101, 32, 76,117, 97, 32,108, 97,110,103,117, 97,103,
101, 46, 10, 45, 45, 32, 76,117, 97, 83,111, 99,107,101,116, 32,116,111,111,108,
107,105,116, 46, 10, 45, 45, 32, 65,117,116,104,111,114, 58, 32, 68,105,101,103,
111, 32, 78,101,104, 97, 98, 10, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 10, 10, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 10, 45, 45, 32, 68,101, 99,108, 97,114,101, 32,109,111,100,117,
108,101, 32, 97,110,100, 32,105,109,112,111,114,116, 32,100,101,112,101,110,100,
101,110, 99,105,101,115, 10, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 10,108,111, 99, 97,108, 32, 98, 97,115,101, 32, 61, 32, 95, 71,
 10, 45, 45,108,111, 99, 97,108, 32, 99,111,114,111,117,116,105,110,101, 32, 61,
 32,114,101,113,117,105,114,101, 40, 34, 99,111,114,111,117,116,105,110,101, 34,
 41, 10,108,111, 99, 97,108, 32,115,116,114,105,110,103, 32, 61, 32,114,101,113,
117,105,114,101, 40, 34,115,116,114,105,110,103, 34, 41, 10,108,111, 99, 97,108,
 32,109, 97,116,104, 32, 61, 32,114,101,113,117,105,114,101, 40, 34,109, 97,116,
104, 34, 41, 10,108,111, 99, 97,108, 32,111,115, 32, 61, 32,114,101,113,117,105,
114,101, 40, 34,111,115, 34, 41, 10,108,111, 99, 97,108, 32,115,111, 99,107,101,
116, 32, 61, 32,114,101,113,117,105,114,101, 40, 34,115,111, 99,107,101,116, 34,
 41, 10,108,111, 99, 97,108, 32,116,112, 32, 61, 32,114,101,113,117,105,114,101,
 40, 34,115,111, 99,107,101,116, 46,116,112, 34, 41, 10,108,111, 99, 97,108, 32,
108,116,110, 49, 50, 32, 61, 32,114,101,113,117,105,114,101, 40, 34,108,116,110,
 49, 50, 34, 41, 10,108,111, 99, 97,108, 32,104,101, 97,100,101,114,115, 32, 61,
 32,114,101,113,117,105,114,101, 40, 34,115,111, 99,107,101,116, 46,104,101, 97,
100,101,114,115, 34, 41, 10,108,111, 99, 97,108, 32,109,105,109,101, 32, 61, 32,
114,101,113,117,105,114,101, 40, 34,109,105,109,101, 34, 41, 10,109,111,100,117,
108,101, 40, 34,115,111, 99,107,101,116, 46,115,109,116,112, 34, 41, 10, 10, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 10, 45, 45, 32,
 80,114,111,103,114, 97,109, 32, 99,111,110,115,116, 97,110,116,115, 10, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 10, 45, 45, 32,116,
105,109,101,111,117,116, 32,102,111,114, 32, 99,111,110,110,101, 99,116,105,111,
110, 10, 84, 73, 77, 69, 79, 85, 84, 32, 61, 32, 54, 48, 10, 45, 45, 32,100,101,
102, 97,117,108,116, 32,115,101,114,118,101,114, 32,117,115,101,100, 32,116,111,
 32,115,101,110,100, 32,101, 45,109, 97,105,108,115, 10, 83, 69, 82, 86, 69, 82,
 32, 61, 32, 34,108,111, 99, 97,108,104,111,115,116, 34, 10, 45, 45, 32,100,101,
102, 97,117,108,116, 32,112,111,114,116, 10, 80, 79, 82, 84, 32, 61, 32, 50, 53,
 10, 45, 45, 32,100,111,109, 97,105,110, 32,117,115,101,100, 32,105,110, 32, 72,
 69, 76, 79, 32, 99,111,109,109, 97,110,100, 32, 97,110,100, 32,100,101,102, 97,
117,108,116, 32,115,101,110,100,109, 97,105,108, 10, 45, 45, 32, 73,102, 32,119,
101, 32, 97,114,101, 32,117,110,100,101,114, 32, 97, 32, 67, 71, 73, 44, 32,116,
114,121, 32,116,111, 32,103,101,116, 32,102,114,111,109, 32,101,110,118,105,114,
111,110,109,101,110,116, 10, 68, 79, 77, 65, 73, 78, 32, 61, 32,111,115, 46,103,
101,116,101,110,118, 40, 34, 83, 69, 82, 86, 69, 82, 95, 78, 65, 77, 69, 34, 41,
 32,111,114, 32, 34,108,111, 99, 97,108,104,111,115,116, 34, 10, 45, 45, 32,100,
101,102, 97,117,108,116, 32,116,105,109,101, 32,122,111,110,101, 32, 40,109,101,
 97,110,115, 32,119,101, 32,100,111,110, 39,116, 32,107,110,111,119, 41, 10, 90,
 79, 78, 69, 32, 61, 32, 34, 45, 48, 48, 48, 48, 34, 10, 10, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 10, 45, 45, 32, 76,111,119, 32,108,101,
118,101,108, 32, 83, 77, 84, 80, 32, 65, 80, 73, 10, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 10,108,111, 99, 97,108, 32,109,101,116,
 97,116, 32, 61, 32,123, 32, 95, 95,105,110,100,101,120, 32, 61, 32,123,125, 32,
125, 10, 10,102,117,110, 99,116,105,111,110, 32,109,101,116, 97,116, 46, 95, 95,
105,110,100,101,120, 58,103,114,101,101,116, 40,100,111,109, 97,105,110, 41, 10,
 32, 32, 32, 32,115,101,108,102, 46,116,114,121, 40,115,101,108,102, 46,116,112,
 58, 99,104,101, 99,107, 40, 34, 50, 46, 46, 34, 41, 41, 10, 32, 32, 32, 32,115,
101,108,102, 46,116,114,121, 40,115,101,108,102, 46,116,112, 58, 99,111,109,109,
 97,110,100, 40, 34, 69, 72, 76, 79, 34, 44, 32,100,111,109, 97,105,110, 32,111,
114, 32, 68, 79, 77, 65, 73, 78, 41, 41, 10, 32, 32, 32, 32,114,101,116,117,114,
110, 32,115,111, 99,107,101,116, 46,115,107,105,112, 40, 49, 44, 32,115,101,108,
102, 46,116,114,121, 40,115,101,108,102, 46,116,112, 58, 99,104,101, 99,107, 40,
 34, 50, 46, 46, 34, 41, 41, 41, 10,101,110,100, 10, 10,102,117,110, 99,116,105,
111,110, 32,109,101,116, 97,116, 46, 95, 95,105,110,100,101,120, 58,109, 97,105,
108, 40,102,114,111,109, 41, 10, 32, 32, 32, 32,115,101,108,102, 46,116,114,121,
 40,115,101,108,102, 46,116,112, 58, 99,111,109,109, 97,110,100, 40, 34, 77, 65,
 73, 76, 34, 44, 32, 34, 70, 82, 79, 77, 58, 34, 32, 46, 46, 32,102,114,111,109,
 41, 41, 10, 32, 32, 32, 32,114,101,116,117,114,110, 32,115,101,108,102, 46,116,
114,121, 40,115,101,108,102, 46,116,112, 58, 99,104,101, 99,107, 40, 34, 50, 46,
 46, 34, 41, 41, 10,101,110,100, 10, 10,102,117,110, 99,116,105,111,110, 32,109,
101,116, 97,116, 46, 95, 95,105,110,100,101,120, 58,114, 99,112,116, 40,116,111,
 41, 10, 32, 32, 32, 32,115,101,108,102, 46,116,114,121, 40,115,101,108,102, 46,
116,112, 58, 99,111,109,109, 97,110,100, 40, 34, 82, 67, 80, 84, 34, 44, 32, 34,
 84, 79, 58, 34, 32, 46, 46, 32,116,111, 41, 41, 10, 32, 32, 32, 32,114,101,116,
117,114,110, 32,115,101,108,102, 46,116,114,121, 40,115,101,108,102, 46,116,112,
 58, 99,104,101, 99,107, 40, 34, 50, 46, 46, 34, 41, 41, 10,101,110,100, 10, 10,
102,117,110, 99,116,105,111,110, 32,109,101,116, 97,116, 46, 95, 95,105,110,100,
101,120, 58,100, 97,116, 97, 40,115,114, 99, 44, 32,115,116,101,112, 41, 10, 32,
 32, 32, 32,115,101,108,102, 46,116,114,121, 40,115,101,108,102, 46,116,112, 58,
 99,111,109,109, 97,110,100, 40, 34, 68, 65, 84, 65, 34, 41, 41, 10, 32, 32, 32,
 32,115,101,108,102, 46,116,114,121, 40,115,101,108,102, 46,116,112, 58, 99,104,
101, 99,107, 40, 34, 51, 46, 46, 34, 41, 41, 10, 32, 32, 32, 32,115,101,108,102,
 46,116,114,121, 40,115,101,108,102, 46,116,112, 58,115,111,117,114, 99,101, 40,
115,114, 99, 44, 32,115,116,101,112, 41, 41, 10, 32, 32, 32, 32,115,101,108,102,
 46,116,114,121, 40,115,101,108,102, 46,116,112, 58,115,101,110,100, 40, 34, 92,
114, 92,110, 46, 92,114, 92,110, 34, 41, 41, 10, 32, 32, 32, 32,114,101,116,117,
114,110, 32,115,101,108,102, 46,116,114,121, 40,115,101,108,102, 46,116,112, 58,
 99,104,101, 99,107, 40, 34, 50, 46, 46, 34, 41, 41, 10,101,110,100, 10, 10,102,
117,110, 99,116,105,111,110, 32,109,101,116, 97,116, 46, 95, 95,105,110,100,101,
120, 58,113,117,105,116, 40, 41, 10, 32, 32, 32, 32,115,101,108,102, 46,116,114,
121, 40,115,101,108,102, 46,116,112, 58, 99,111,109,109, 97,110,100, 40, 34, 81,
 85, 73, 84, 34, 41, 41, 10, 32, 32, 32, 32,114,101,116,117,114,110, 32,115,101,
108,102, 46,116,114,121, 40,115,101,108,102, 46,116,112, 58, 99,104,101, 99,107,
 40, 34, 50, 46, 46, 34, 41, 41, 10,101,110,100, 10, 10,102,117,110, 99,116,105,
111,110, 32,109,101,116, 97,116, 46, 95, 95,105,110,100,101,120, 58, 99,108,111,
115,101, 40, 41, 10, 32, 32, 32, 32,114,101,116,117,114,110, 32,115,101,108,102,
 46,116,112, 58, 99,108,111,115,101, 40, 41, 10,101,110,100, 10, 10,102,117,110,
 99,116,105,111,110, 32,109,101,116, 97,116, 46, 95, 95,105,110,100,101,120, 58,
108,111,103,105,110, 40,117,115,101,114, 44, 32,112, 97,115,115,119,111,114,100,
 41, 10, 32, 32, 32, 32,115,101,108,102, 46,116,114,121, 40,115,101,108,102, 46,
116,112, 58, 99,111,109,109, 97,110,100, 40, 34, 65, 85, 84, 72, 34, 44, 32, 34,
 76, 79, 71, 73, 78, 34, 41, 41, 10, 32, 32, 32, 32,115,101,108,102, 46,116,114,
121, 40,115,101,108,102, 46,116,112, 58, 99,104,101, 99,107, 40, 34, 51, 46, 46,
 34, 41, 41, 10, 32, 32, 32, 32,115,101,108,102, 46,116,114,121, 40,115,101,108,
102, 46,116,112, 58,115,101,110,100, 40,109,105,109,101, 46, 98, 54, 52, 40,117,
115,101,114, 41, 32, 46, 46, 32, 34, 92,114, 92,110, 34, 41, 41, 10, 32, 32, 32,
 32,115,101,108,102, 46,116,114,121, 40,115,101,108,102, 46,116,112, 58, 99,104,
101, 99,107, 40, 34, 51, 46, 46, 34, 41, 41, 10, 32, 32, 32, 32,115,101,108,102,
 46,116,114,121, 40,115,101,108,102, 46,116,112, 58,115,101,110,100, 40,109,105,
109,101, 46, 98, 54, 52, 40,112, 97,115,115,119,111,114,100, 41, 32, 46, 46, 32,
 34, 92,114, 92,110, 34, 41, 41, 10, 32, 32, 32, 32,114,101,116,117,114,110, 32,
115,101,108,102, 46,116,114,121, 40,115,101,108,102, 46,116,112, 58, 99,104,101,
 99,107, 40, 34, 50, 46, 46, 34, 41, 41, 10,101,110,100, 10, 10,102,117,110, 99,
116,105,111,110, 32,109,101,116, 97,116, 46, 95, 95,105,110,100,101,120, 58,112,
108, 97,105,110, 40,117,115,101,114, 44, 32,112, 97,115,115,119,111,114,100, 41,
 10, 32, 32, 32, 32,108,111, 99, 97,108, 32, 97,117,116,104, 32, 61, 32, 34, 80,
 76, 65, 73, 78, 32, 34, 32, 46, 46, 32,109,105,109,101, 46, 98, 54, 52, 40, 34,
 92, 48, 34, 32, 46, 46, 32,117,115,101,114, 32, 46, 46, 32, 34, 92, 48, 34, 32,
 46, 46, 32,112, 97,115,115,119,111,114,100, 41, 10, 32, 32, 32, 32,115,101,108,
102, 46,116,114,121, 40,115,101,108,102, 46,116,112, 58, 99,111,109,109, 97,110,
100, 40, 34, 65, 85, 84, 72, 34, 44, 32, 97,117,116,104, 41, 41, 10, 32, 32, 32,
 32,114,101,116,117,114,110, 32,115,101,108,102, 46,116,114,121, 40,115,101,108,
102, 46,116,112, 58, 99,104,101, 99,107, 40, 34, 50, 46, 46, 34, 41, 41, 10,101,
110,100, 10, 10,102,117,110, 99,116,105,111,110, 32,109,101,116, 97,116, 46, 95,
 95,105,110,100,101,120, 58, 97,117,116,104, 40,117,115,101,114, 44, 32,112, 97,
115,115,119,111,114,100, 44, 32,101,120,116, 41, 10, 32, 32, 32, 32,105,102, 32,
110,111,116, 32,117,115,101,114, 32,111,114, 32,110,111,116, 32,112, 97,115,115,
119,111,114,100, 32,116,104,101,110, 32,114,101,116,117,114,110, 32, 49, 32,101,
110,100, 10, 32, 32, 32, 32,105,102, 32,115,116,114,105,110,103, 46,102,105,110,
100, 40,101,120,116, 44, 32, 34, 65, 85, 84, 72, 91, 94, 92,110, 93, 43, 76, 79,
 71, 73, 78, 34, 41, 32,116,104,101,110, 10, 32, 32, 32, 32, 32, 32, 32, 32,114,
101,116,117,114,110, 32,115,101,108,102, 58,108,111,103,105,110, 40,117,115,101,
114, 44, 32,112, 97,115,115,119,111,114,100, 41, 10, 32, 32, 32, 32,101,108,115,
101,105,102, 32,115,116,114,105,110,103, 46,102,105,110,100, 40,101,120,116, 44,
 32, 34, 65, 85, 84, 72, 91, 94, 92,110, 93, 43, 80, 76, 65, 73, 78, 34, 41, 32,
116,104,101,110, 10, 32, 32, 32, 32, 32, 32, 32, 32,114,101,116,117,114,110, 32,
115,101,108,102, 58,112,108, 97,105,110, 40,117,115,101,114, 44, 32,112, 97,115,
115,119,111,114,100, 41, 10, 32, 32, 32, 32,101,108,115,101, 10, 32, 32, 32, 32,
 32, 32, 32, 32,115,101,108,102, 46,116,114,121, 40,110,105,108, 44, 32, 34, 97,
117,116,104,101,110,116,105, 99, 97,116,105,111,110, 32,110,111,116, 32,115,117,
112,112,111,114,116,101,100, 34, 41, 10, 32, 32, 32, 32,101,110,100, 10,101,110,
100, 10, 10, 45, 45, 32,115,101,110,100, 32,109,101,115,115, 97,103,101, 32,111,
114, 32,116,104,114,111,119, 32, 97,110, 32,101,120, 99,101,112,116,105,111,110,
 10,102,117,110, 99,116,105,111,110, 32,109,101,116, 97,116, 46, 95, 95,105,110,
100,101,120, 58,115,101,110,100, 40,109, 97,105,108,116, 41, 10, 32, 32, 32, 32,
115,101,108,102, 58,109, 97,105,108, 40,109, 97,105,108,116, 46,102,114,111,109,
 41, 10, 32, 32, 32, 32,105,102, 32, 98, 97,115,101, 46,116,121,112,101, 40,109,
 97,105,108,116, 46,114, 99,112,116, 41, 32, 61, 61, 32, 34,116, 97, 98,108,101,
 34, 32,116,104,101,110, 10, 32, 32, 32, 32, 32, 32, 32, 32,102,111,114, 32,105,
 44,118, 32,105,110, 32, 98, 97,115,101, 46,105,112, 97,105,114,115, 40,109, 97,
105,108,116, 46,114, 99,112,116, 41, 32,100,111, 10, 32, 32, 32, 32, 32, 32, 32,
 32, 32, 32, 32, 32,115,101,108,102, 58,114, 99,112,116, 40,118, 41, 10, 32, 32,
 32, 32, 32, 32, 32, 32,101,110,100, 10, 32, 32, 32, 32,101,108,115,101, 10, 32,
 32, 32, 32, 32, 32, 32, 32,115,101,108,102, 58,114, 99,112,116, 40,109, 97,105,
108,116, 46,114, 99,112,116, 41, 10, 32, 32, 32, 32,101,110,100, 10, 32, 32, 32,
 32,115,101,108,102, 58,100, 97,116, 97, 40,108,116,110, 49, 50, 46,115,111,117,
114, 99,101, 46, 99,104, 97,105,110, 40,109, 97,105,108,116, 46,115,111,117,114,
 99,101, 44, 32,109,105,109,101, 46,115,116,117,102,102, 40, 41, 41, 44, 32,109,
 97,105,108,116, 46,115,116,101,112, 41, 10,101,110,100, 10, 10,102,117,110, 99,
116,105,111,110, 32,111,112,101,110, 40,115,101,114,118,101,114, 44, 32,112,111,
114,116, 44, 32, 99,114,101, 97,116,101, 41, 10, 32, 32, 32, 32,108,111, 99, 97,
108, 32,116,112, 32, 61, 32,115,111, 99,107,101,116, 46,116,114,121, 40,116,112,
 46, 99,111,110,110,101, 99,116, 40,115,101,114,118,101,114, 32,111,114, 32, 83,
 69, 82, 86, 69, 82, 44, 32,112,111,114,116, 32,111,114, 32, 80, 79, 82, 84, 44,
 10, 32, 32, 32, 32, 32, 32, 32, 32, 84, 73, 77, 69, 79, 85, 84, 44, 32, 99,114,
101, 97,116,101, 41, 41, 10, 32, 32, 32, 32,108,111, 99, 97,108, 32,115, 32, 61,
 32, 98, 97,115,101, 46,115,101,116,109,101,116, 97,116, 97, 98,108,101, 40,123,
116,112, 32, 61, 32,116,112,125, 44, 32,109,101,116, 97,116, 41, 10, 32, 32, 32,
 32, 45, 45, 32,109, 97,107,101, 32,115,117,114,101, 32,116,112, 32,105,115, 32,
 99,108,111,115,101,100, 32,105,102, 32,119,101, 32,103,101,116, 32, 97,110, 32,
101,120, 99,101,112,116,105,111,110, 10, 32, 32, 32, 32,115, 46,116,114,121, 32,
 61, 32,115,111, 99,107,101,116, 46,110,101,119,116,114,121, 40,102,117,110, 99,
116,105,111,110, 40, 41, 10, 32, 32, 32, 32, 32, 32, 32, 32,115, 58, 99,108,111,
115,101, 40, 41, 10, 32, 32, 32, 32,101,110,100, 41, 10, 32, 32, 32, 32,114,101,
116,117,114,110, 32,115, 10,101,110,100, 10, 10, 45, 45, 32, 99,111,110,118,101,
114,116, 32,104,101, 97,100,101,114,115, 32,116,111, 32,108,111,119,101,114, 99,
 97,115,101, 10,108,111, 99, 97,108, 32,102,117,110, 99,116,105,111,110, 32,108,
111,119,101,114, 95,104,101, 97,100,101,114,115, 40,104,101, 97,100,101,114,115,
 41, 10, 32, 32, 32, 32,108,111, 99, 97,108, 32,108,111,119,101,114, 32, 61, 32,
123,125, 10, 32, 32, 32, 32,102,111,114, 32,105, 44,118, 32,105,110, 32, 98, 97,
115,101, 46,112, 97,105,114,115, 40,104,101, 97,100,101,114,115, 32,111,114, 32,
108,111,119,101,114, 41, 32,100,111, 10, 32, 32, 32, 32, 32, 32, 32, 32,108,111,
119,101,114, 91,115,116,114,105,110,103, 46,108,111,119,101,114, 40,105, 41, 93,
 32, 61, 32,118, 10, 32, 32, 32, 32,101,110,100, 10, 32, 32, 32, 32,114,101,116,
117,114,110, 32,108,111,119,101,114, 10,101,110,100, 10, 10, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 10, 45, 45, 32, 77,117,108,116,105,112,
 97,114,116, 32,109,101,115,115, 97,103,101, 32,115,111,117,114, 99,101, 10, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 10, 45, 45, 32,
114,101,116,117,114,110,115, 32, 97, 32,104,111,112,101,102,117,108,108,121, 32,
117,110,105,113,117,101, 32,109,105,109,101, 32, 98,111,117,110,100, 97,114,121,
 10,108,111, 99, 97,108, 32,115,101,113,110,111, 32, 61, 32, 48, 10,108,111, 99,
 97,108, 32,102,117,110, 99,116,105,111,110, 32,110,101,119, 98,111,117,110,100,
 97,114,121, 40, 41, 10, 32, 32, 32, 32,115,101,113,110,111, 32, 61, 32,115,101,
113,110,111, 32, 43, 32, 49, 10, 32, 32, 32, 32,114,101,116,117,114,110, 32,115,
116,114,105,110,103, 46,102,111,114,109, 97,116, 40, 39, 37,115, 37, 48, 53,100,
 61, 61, 37, 48, 53,117, 39, 44, 32,111,115, 46,100, 97,116,101, 40, 39, 37,100,
 37,109, 37, 89, 37, 72, 37, 77, 37, 83, 39, 41, 44, 10, 32, 32, 32, 32, 32, 32,
 32, 32,109, 97,116,104, 46,114, 97,110,100,111,109, 40, 48, 44, 32, 57, 57, 57,
 57, 57, 41, 44, 32,115,101,113,110,111, 41, 10,101,110,100, 10, 10, 45, 45, 32,
115,101,110,100, 95,109,101,115,115, 97,103,101, 32,102,111,114,119, 97,114,100,
 32,100,101, 99,108, 97,114, 97,116,105,111,110, 10,108,111, 99, 97,108, 32,115,
101,110,100, 95,109,101,115,115, 97,103,101, 10, 10, 45, 45, 32,121,105,101,108,
100, 32,116,104,101, 32,104,101, 97,100,101,114,115, 32, 97,108,108, 32, 97,116,
 32,111,110, 99,101, 44, 32,105,116, 39,115, 32,102, 97,115,116,101,114, 10,108,
111, 99, 97,108, 32,102,117,110, 99,116,105,111,110, 32,115,101,110,100, 95,104,
101, 97,100,101,114,115, 40,116,111,115,101,110,100, 41, 10, 32, 32, 32, 32,108,
111, 99, 97,108, 32, 99, 97,110,111,110,105, 99, 32, 61, 32,104,101, 97,100,101,
114,115, 46, 99, 97,110,111,110,105, 99, 10, 32, 32, 32, 32,108,111, 99, 97,108,
 32,104, 32, 61, 32, 34, 92,114, 92,110, 34, 10, 32, 32, 32, 32,102,111,114, 32,
102, 44,118, 32,105,110, 32, 98, 97,115,101, 46,112, 97,105,114,115, 40,116,111,
115,101,110,100, 41, 32,100,111, 10, 32, 32, 32, 32, 32, 32, 32, 32,104, 32, 61,
 32, 40, 99, 97,110,111,110,105, 99, 91,102, 93, 32,111,114, 32,102, 41, 32, 46,
 46, 32, 39, 58, 32, 39, 32, 46, 46, 32,118, 32, 46, 46, 32, 34, 92,114, 92,110,
 34, 32, 46, 46, 32,104, 10, 32, 32, 32, 32,101,110,100, 10, 32, 32, 32, 32, 99,
111,114,111,117,116,105,110,101, 46,121,105,101,108,100, 40,104, 41, 10,101,110,
100, 10, 10, 45, 45, 32,121,105,101,108,100, 32,109,117,108,116,105,112, 97,114,
116, 32,109,101,115,115, 97,103,101, 32, 98,111,100,121, 32,102,114,111,109, 32,
 97, 32,109,117,108,116,105,112, 97,114,116, 32,109,101,115,115, 97,103,101, 32,
116, 97, 98,108,101, 10,108,111, 99, 97,108, 32,102,117,110, 99,116,105,111,110,
 32,115,101,110,100, 95,109,117,108,116,105,112, 97,114,116, 40,109,101,115,103,
116, 41, 10, 32, 32, 32, 32, 45, 45, 32,109, 97,107,101, 32,115,117,114,101, 32,
119,101, 32,104, 97,118,101, 32,111,117,114, 32, 98,111,117,110,100, 97,114,121,
 32, 97,110,100, 32,115,101,110,100, 32,104,101, 97,100,101,114,115, 10, 32, 32,
 32, 32,108,111, 99, 97,108, 32, 98,100, 32, 61, 32,110,101,119, 98,111,117,110,
100, 97,114,121, 40, 41, 10, 32, 32, 32, 32,108,111, 99, 97,108, 32,104,101, 97,
100,101,114,115, 32, 61, 32,108,111,119,101,114, 95,104,101, 97,100,101,114,115,
 40,109,101,115,103,116, 46,104,101, 97,100,101,114,115, 32,111,114, 32,123,125,
 41, 10, 32, 32, 32, 32,104,101, 97,100,101,114,115, 91, 39, 99,111,110,116,101,
110,116, 45,116,121,112,101, 39, 93, 32, 61, 32,104,101, 97,100,101,114,115, 91,
 39, 99,111,110,116,101,110,116, 45,116,121,112,101, 39, 93, 32,111,114, 32, 39,
109,117,108,116,105,112, 97,114,116, 47,109,105,120,101,100, 39, 10, 32, 32, 32,
 32,104,101, 97,100,101,114,115, 91, 39, 99,111,110,116,101,110,116, 45,116,121,
112,101, 39, 93, 32, 61, 32,104,101, 97,100,101,114,115, 91, 39, 99,111,110,116,
101,110,116, 45,116,121,112,101, 39, 93, 32, 46, 46, 10, 32, 32, 32, 32, 32, 32,
 32, 32, 39, 59, 32, 98,111,117,110,100, 97,114,121, 61, 34, 39, 32, 46, 46, 32,
 32, 98,100, 32, 46, 46, 32, 39, 34, 39, 10, 32, 32, 32, 32,115,101,110,100, 95,
104,101, 97,100,101,114,115, 40,104,101, 97,100,101,114,115, 41, 10, 32, 32, 32,
 32, 45, 45, 32,115,101,110,100, 32,112,114,101, 97,109, 98,108,101, 10, 32, 32,
 32, 32,105,102, 32,109,101,115,103,116, 46, 98,111,100,121, 46,112,114,101, 97,
109, 98,108,101, 32,116,104,101,110, 10, 32, 32, 32, 32, 32, 32, 32, 32, 99,111,
114,111,117,116,105,110,101, 46,121,105,101,108,100, 40,109,101,115,103,116, 46,
 98,111,100,121, 46,112,114,101, 97,109, 98,108,101, 41, 10, 32, 32, 32, 32, 32,
 32, 32, 32, 99,111,114,111,117,116,105,110,101, 46,121,105,101,108,100, 40, 34,
 92,114, 92,110, 34, 41, 10, 32, 32, 32, 32,101,110,100, 10, 32, 32, 32, 32, 45,
 45, 32,115,101,110,100, 32,101, 97, 99,104, 32,112, 97,114,116, 32,115,101,112,
 97,114, 97,116,101,100, 32, 98,121, 32, 97, 32, 98,111,117,110,100, 97,114,121,
 10, 32, 32, 32, 32,102,111,114, 32,105, 44, 32,109, 32,105,110, 32, 98, 97,115,
101, 46,105,112, 97,105,114,115, 40,109,101,115,103,116, 46, 98,111,100,121, 41,
 32,100,111, 10, 32, 32, 32, 32, 32, 32, 32, 32, 99,111,114,111,117,116,105,110,
101, 46,121,105,101,108,100, 40, 34, 92,114, 92,110, 45, 45, 34, 32, 46, 46, 32,
 98,100, 32, 46, 46, 32, 34, 92,114, 92,110, 34, 41, 10, 32, 32, 32, 32, 32, 32,
 32, 32,115,101,110,100, 95,109,101,115,115, 97,103,101, 40,109, 41, 10, 32, 32,
 32, 32,101,110,100, 10, 32, 32, 32, 32, 45, 45, 32,115,101,110,100, 32,108, 97,
115,116, 32, 98,111,117,110,100, 97,114,121, 10, 32, 32, 32, 32, 99,111,114,111,
117,116,105,110,101, 46,121,105,101,108,100, 40, 34, 92,114, 92,110, 45, 45, 34,
 32, 46, 46, 32, 98,100, 32, 46, 46, 32, 34, 45, 45, 92,114, 92,110, 92,114, 92,
110, 34, 41, 10, 32, 32, 32, 32, 45, 45, 32,115,101,110,100, 32,101,112,105,108,
111,103,117,101, 10, 32, 32, 32, 32,105,102, 32,109,101,115,103,116, 46, 98,111,
100,121, 46,101,112,105,108,111,103,117,101, 32,116,104,101,110, 10, 32, 32, 32,
 32, 32, 32, 32, 32, 99,111,114,111,117,116,105,110,101, 46,121,105,101,108,100,
 40,109,101,115,103,116, 46, 98,111,100,121, 46,101,112,105,108,111,103,117,101,
 41, 10, 32, 32, 32, 32, 32, 32, 32, 32, 99,111,114,111,117,116,105,110,101, 46,
121,105,101,108,100, 40, 34, 92,114, 92,110, 34, 41, 10, 32, 32, 32, 32,101,110,
100, 10,101,110,100, 10, 10, 45, 45, 32,121,105,101,108,100, 32,109,101,115,115,
 97,103,101, 32, 98,111,100,121, 32,102,114,111,109, 32, 97, 32,115,111,117,114,
 99,101, 10,108,111, 99, 97,108, 32,102,117,110, 99,116,105,111,110, 32,115,101,
110,100, 95,115,111,117,114, 99,101, 40,109,101,115,103,116, 41, 10, 32, 32, 32,
 32, 45, 45, 32,109, 97,107,101, 32,115,117,114,101, 32,119,101, 32,104, 97,118,
101, 32, 97, 32, 99,111,110,116,101,110,116, 45,116,121,112,101, 10, 32, 32, 32,
 32,108,111, 99, 97,108, 32,104,101, 97,100,101,114,115, 32, 61, 32,108,111,119,
101,114, 95,104,101, 97,100,101,114,115, 40,109,101,115,103,116, 46,104,101, 97,
100,101,114,115, 32,111,114, 32,123,125, 41, 10, 32, 32, 32, 32,104,101, 97,100,
101,114,115, 91, 39, 99,111,110,116,101,110,116, 45,116,121,112,101, 39, 93, 32,
 61, 32,104,101, 97,100,101,114,115, 91, 39, 99,111,110,116,101,110,116, 45,116,
121,112,101, 39, 93, 32,111,114, 10, 32, 32, 32, 32, 32, 32, 32, 32, 39,116,101,
120,116, 47,112,108, 97,105,110, 59, 32, 99,104, 97,114,115,101,116, 61, 34,105,
115,111, 45, 56, 56, 53, 57, 45, 49, 34, 39, 10, 32, 32, 32, 32,115,101,110,100,
 95,104,101, 97,100,101,114,115, 40,104,101, 97,100,101,114,115, 41, 10, 32, 32,
 32, 32, 45, 45, 32,115,101,110,100, 32, 98,111,100,121, 32,102,114,111,109, 32,
115,111,117,114, 99,101, 10, 32, 32, 32, 32,119,104,105,108,101, 32,116,114,117,
101, 32,100,111, 10, 32, 32, 32, 32, 32, 32, 32, 32,108,111, 99, 97,108, 32, 99,
104,117,110,107, 44, 32,101,114,114, 32, 61, 32,109,101,115,103,116, 46, 98,111,
100,121, 40, 41, 10, 32, 32, 32, 32, 32, 32, 32, 32,105,102, 32,101,114,114, 32,
116,104,101,110, 32, 99,111,114,111,117,116,105,110,101, 46,121,105,101,108,100,
 40,110,105,108, 44, 32,101,114,114, 41, 10, 32, 32, 32, 32, 32, 32, 32, 32,101,
108,115,101,105,102, 32, 99,104,117,110,107, 32,116,104,101,110, 32, 99,111,114,
111,117,116,105,110,101, 46,121,105,101,108,100, 40, 99,104,117,110,107, 41, 10,
 32, 32, 32, 32, 32, 32, 32, 32,101,108,115,101, 32, 98,114,101, 97,107, 32,101,
110,100, 10, 32, 32, 32, 32,101,110,100, 10,101,110,100, 10, 10, 45, 45, 32,121,
105,101,108,100, 32,109,101,115,115, 97,103,101, 32, 98,111,100,121, 32,102,114,
111,109, 32, 97, 32,115,116,114,105,110,103, 10,108,111, 99, 97,108, 32,102,117,
110, 99,116,105,111,110, 32,115,101,110,100, 95,115,116,114,105,110,103, 40,109,
101,115,103,116, 41, 10, 32, 32, 32, 32, 45, 45, 32,109, 97,107,101, 32,115,117,
114,101, 32,119,101, 32,104, 97,118,101, 32, 97, 32, 99,111,110,116,101,110,116,
 45,116,121,112,101, 10, 32, 32, 32, 32,108,111, 99, 97,108, 32,104,101, 97,100,
101,114,115, 32, 61, 32,108,111,119,101,114, 95,104,101, 97,100,101,114,115, 40,
109,101,115,103,116, 46,104,101, 97,100,101,114,115, 32,111,114, 32,123,125, 41,
 10, 32, 32, 32, 32,104,101, 97,100,101,114,115, 91, 39, 99,111,110,116,101,110,
116, 45,116,121,112,101, 39, 93, 32, 61, 32,104,101, 97,100,101,114,115, 91, 39,
 99,111,110,116,101,110,116, 45,116,121,112,101, 39, 93, 32,111,114, 10, 32, 32,
 32, 32, 32, 32, 32, 32, 39,116,101,120,116, 47,112,108, 97,105,110, 59, 32, 99,
104, 97,114,115,101,116, 61, 34,105,115,111, 45, 56, 56, 53, 57, 45, 49, 34, 39,
 10, 32, 32, 32, 32,115,101,110,100, 95,104,101, 97,100,101,114,115, 40,104,101,
 97,100,101,114,115, 41, 10, 32, 32, 32, 32, 45, 45, 32,115,101,110,100, 32, 98,
111,100,121, 32,102,114,111,109, 32,115,116,114,105,110,103, 10, 32, 32, 32, 32,
 99,111,114,111,117,116,105,110,101, 46,121,105,101,108,100, 40,109,101,115,103,
116, 46, 98,111,100,121, 41, 10,101,110,100, 10, 10, 45, 45, 32,109,101,115,115,
 97,103,101, 32,115,111,117,114, 99,101, 10,102,117,110, 99,116,105,111,110, 32,
115,101,110,100, 95,109,101,115,115, 97,103,101, 40,109,101,115,103,116, 41, 10,
 32, 32, 32, 32,105,102, 32, 98, 97,115,101, 46,116,121,112,101, 40,109,101,115,
103,116, 46, 98,111,100,121, 41, 32, 61, 61, 32, 34,116, 97, 98,108,101, 34, 32,
116,104,101,110, 32,115,101,110,100, 95,109,117,108,116,105,112, 97,114,116, 40,
109,101,115,103,116, 41, 10, 32, 32, 32, 32,101,108,115,101,105,102, 32, 98, 97,
115,101, 46,116,121,112,101, 40,109,101,115,103,116, 46, 98,111,100,121, 41, 32,
 61, 61, 32, 34,102,117,110, 99,116,105,111,110, 34, 32,116,104,101,110, 32,115,
101,110,100, 95,115,111,117,114, 99,101, 40,109,101,115,103,116, 41, 10, 32, 32,
 32, 32,101,108,115,101, 32,115,101,110,100, 95,115,116,114,105,110,103, 40,109,
101,115,103,116, 41, 32,101,110,100, 10,101,110,100, 10, 10, 45, 45, 32,115,101,
116, 32,100,101,102, 97,117,108, 32,104,101, 97,100,101,114,115, 10,108,111, 99,
 97,108, 32,102,117,110, 99,116,105,111,110, 32, 97,100,106,117,115,116, 95,104,
101, 97,100,101,114,115, 40,109,101,115,103,116, 41, 10, 32, 32, 32, 32,108,111,
 99, 97,108, 32,108,111,119,101,114, 32, 61, 32,108,111,119,101,114, 95,104,101,
 97,100,101,114,115, 40,109,101,115,103,116, 46,104,101, 97,100,101,114,115, 41,
 10, 32, 32, 32, 32,108,111,119,101,114, 91, 34,100, 97,116,101, 34, 93, 32, 61,
 32,108,111,119,101,114, 91, 34,100, 97,116,101, 34, 93, 32,111,114, 10, 32, 32,
 32, 32, 32, 32, 32, 32,111,115, 46,100, 97,116,101, 40, 34, 33, 37, 97, 44, 32,
 37,100, 32, 37, 98, 32, 37, 89, 32, 37, 72, 58, 37, 77, 58, 37, 83, 32, 34, 41,
 32, 46, 46, 32, 40,109,101,115,103,116, 46,122,111,110,101, 32,111,114, 32, 90,
 79, 78, 69, 41, 10, 32, 32, 32, 32,108,111,119,101,114, 91, 34,120, 45,109, 97,
105,108,101,114, 34, 93, 32, 61, 32,108,111,119,101,114, 91, 34,120, 45,109, 97,
105,108,101,114, 34, 93, 32,111,114, 32,115,111, 99,107,101,116, 46, 95, 86, 69,
 82, 83, 73, 79, 78, 10, 32, 32, 32, 32, 45, 45, 32,116,104,105,115, 32, 99, 97,
110, 39,116, 32, 98,101, 32,111,118,101,114,114,105,100,101,110, 10, 32, 32, 32,
 32,108,111,119,101,114, 91, 34,109,105,109,101, 45,118,101,114,115,105,111,110,
 34, 93, 32, 61, 32, 34, 49, 46, 48, 34, 10, 32, 32, 32, 32,114,101,116,117,114,
110, 32,108,111,119,101,114, 10,101,110,100, 10, 10,102,117,110, 99,116,105,111,
110, 32,109,101,115,115, 97,103,101, 40,109,101,115,103,116, 41, 10, 32, 32, 32,
 32,109,101,115,103,116, 46,104,101, 97,100,101,114,115, 32, 61, 32, 97,100,106,
117,115,116, 95,104,101, 97,100,101,114,115, 40,109,101,115,103,116, 41, 10, 32,
 32, 32, 32, 45, 45, 32, 99,114,101, 97,116,101, 32, 97,110,100, 32,114,101,116,
117,114,110, 32,109,101,115,115, 97,103,101, 32,115,111,117,114, 99,101, 10, 32,
 32, 32, 32,108,111, 99, 97,108, 32, 99,111, 32, 61, 32, 99,111,114,111,117,116,
105,110,101, 46, 99,114,101, 97,116,101, 40,102,117,110, 99,116,105,111,110, 40,
 41, 32,115,101,110,100, 95,109,101,115,115, 97,103,101, 40,109,101,115,103,116,
 41, 32,101,110,100, 41, 10, 32, 32, 32, 32,114,101,116,117,114,110, 32,102,117,
110, 99,116,105,111,110, 40, 41, 10, 32, 32, 32, 32, 32, 32, 32, 32,108,111, 99,
 97,108, 32,114,101,116, 44, 32, 97, 44, 32, 98, 32, 61, 32, 99,111,114,111,117,
116,105,110,101, 46,114,101,115,117,109,101, 40, 99,111, 41, 10, 32, 32, 32, 32,
 32, 32, 32, 32,105,102, 32,114,101,116, 32,116,104,101,110, 32,114,101,116,117,
114,110, 32, 97, 44, 32, 98, 10, 32, 32, 32, 32, 32, 32, 32, 32,101,108,115,101,
 32,114,101,116,117,114,110, 32,110,105,108, 44, 32, 97, 32,101,110,100, 10, 32,
 32, 32, 32,101,110,100, 10,101,110,100, 10, 10, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 10, 45, 45, 32, 72,105,103,104, 32,108,101,118,101,
108, 32, 83, 77, 84, 80, 32, 65, 80, 73, 10, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45,
 45, 45, 45, 45, 45, 45, 45, 45, 10,115,101,110,100, 32, 61, 32,115,111, 99,107,
101,116, 46,112,114,111,116,101, 99,116, 40,102,117,110, 99,116,105,111,110, 40,
109, 97,105,108,116, 41, 10, 32, 32, 32, 32,108,111, 99, 97,108, 32,115, 32, 61,
 32,111,112,101,110, 40,109, 97,105,108,116, 46,115,101,114,118,101,114, 44, 32,
109, 97,105,108,116, 46,112,111,114,116, 44, 32,109, 97,105,108,116, 46, 99,114,
101, 97,116,101, 41, 10, 32, 32, 32, 32,108,111, 99, 97,108, 32,101,120,116, 32,
 61, 32,115, 58,103,114,101,101,116, 40,109, 97,105,108,116, 46,100,111,109, 97,
105,110, 41, 10, 32, 32, 32, 32,115, 58, 97,117,116,104, 40,109, 97,105,108,116,
 46,117,115,101,114, 44, 32,109, 97,105,108,116, 46,112, 97,115,115,119,111,114,
100, 44, 32,101,120,116, 41, 10, 32, 32, 32, 32,115, 58,115,101,110,100, 40,109,
 97,105,108,116, 41, 10, 32, 32, 32, 32,115, 58,113,117,105,116, 40, 41, 10, 32,
 32, 32, 32,114,101,116,117,114,110, 32,115, 58, 99,108,111,115,101, 40, 41, 10,
101,110,100, 41, 10,
 0 };
  return luaL_dostring(L, (const char*)B); 
} /* end of embedded lua code */

