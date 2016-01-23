/* lpdflib.c

   Copyright 2006-2011 Taco Hoekwater <taco@luatex.org>

   This file is part of LuaTeX.

   LuaTeX is free software; you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 2 of the License, or (at your
   option) any later version.

   LuaTeX is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
   License for more details.

   You should have received a copy of the GNU General Public License along
   with LuaTeX; if not, see <http://www.gnu.org/licenses/>. */


#include "ptexlib.h"
#include "lua/luatex-api.h"
#include "pdf/pdftables.h"

static int luapdfprint(lua_State * L)
{
    int n;
    const_lstring st;
    const char *modestr_s;
    ctm_transform_modes literal_mode;
    st.s = modestr_s = NULL;
    n = lua_gettop(L);
    if (!lua_isstring(L, -1)) { /* or number */
        luaL_error(L, "no string to print");
    }
    literal_mode = set_origin;
    if (n == 2) {
        if (lua_type(L,-2) != LUA_TSTRING) {
            luaL_error(L, "invalid first argument for print literal mode");
        } else {
            modestr_s = lua_tostring(L, -2);
            if (lua_key_eq(modestr_s,direct))
                literal_mode = direct_always;
            else if (lua_key_eq(modestr_s,page))
                literal_mode = direct_page;
            else {
                luaL_error(L, "invalid first argument for print literal mode");
            }
        }
    } else if (n != 1) {
        luaL_error(L, "invalid number of arguments");
    }
    check_o_mode(static_pdf, "pdf.print()", 1 << OMODE_PDF, true);
    switch (literal_mode) {
        case (set_origin):
            pdf_goto_pagemode(static_pdf);
            pdf_set_pos(static_pdf, static_pdf->posstruct->pos);
            (void) calc_pdfpos(static_pdf->pstruct, static_pdf->posstruct->pos);
            break;
        case (direct_page):
            pdf_goto_pagemode(static_pdf);
            (void) calc_pdfpos(static_pdf->pstruct, static_pdf->posstruct->pos);
            break;
        case (direct_always):
            pdf_end_string_nl(static_pdf);
            break;
        default:
            assert(0);
    }
    st.s = lua_tolstring(L, n, &st.l);
    pdf_out_block(static_pdf, st.s, st.l);
    return 0;
}

static unsigned char *fread_to_buf(lua_State * L, const char *filename, size_t * len)
{
    int ilen = 0;
    FILE *f;
    unsigned char *buf = NULL;
    if ((f = fopen(filename, "rb")) == NULL)
        luaL_error(L, "pdf.immediateobj() cannot open input file");
    if (readbinfile(f, &buf, &ilen) == 0)
        luaL_error(L, "pdf.immediateobj() cannot read input file");
    fclose(f);
    *len = (size_t) ilen;
    return buf;
}

static int l_immediateobj(lua_State * L)
{
    int n, first_arg = 1;
    int k;
    lstring buf;
    const_lstring st1,st2, st3;
    const char *st1_s = NULL;
    st1.s = st2.s = st3.s = NULL;
    check_o_mode(static_pdf, "immediateobj()", 1 << OMODE_PDF, true);
    if (global_shipping_mode != NOT_SHIPPING)
        luaL_error(L, "pdf.immediateobj() can not be used with \\latelua");
    n = lua_gettop(L);
    if ((n > 0) && (lua_type(L, 1) == LUA_TNUMBER)) {
        first_arg++;
        k = (int) lua_tointeger(L, 1);
        check_obj_type(static_pdf, obj_type_obj, k);
        if (is_obj_scheduled(static_pdf, k) || obj_data_ptr(static_pdf, k) != 0)
            luaL_error(L, "pdf.immediateobj() object in use");
    } else {
        static_pdf->obj_count++;
        k = pdf_create_obj(static_pdf, obj_type_obj, static_pdf->obj_ptr + 1);
    }
    pdf_last_obj = k;
    switch (n - first_arg + 1) {
        case 0:
            luaL_error(L, "pdf.immediateobj() needs at least one argument");
            break;
        case 1:
            if (!lua_isstring(L, first_arg)) /* or number */
                luaL_error(L, "pdf.immediateobj() 1st argument must be string");
            pdf_begin_obj(static_pdf, k, OBJSTM_ALWAYS);
            st1.s = lua_tolstring(L, first_arg, &st1.l);
            pdf_out_block(static_pdf, st1.s, st1.l);
            pdf_end_obj(static_pdf);
            break;
        case 2:
        case 3:
            if (lua_type(L,first_arg) != LUA_TSTRING)
                luaL_error(L, "pdf.immediateobj() 1st argument must be string");
            if (!lua_isstring(L, first_arg + 1)) /* or number */
                luaL_error(L, "pdf.immediateobj() 2nd argument must be string");
            st1_s = lua_tostring(L, first_arg);
            st2.s = lua_tolstring(L, first_arg + 1, &st2.l);
            if (lua_key_eq(st1_s, file)) {
                if (n == first_arg + 2)
                    luaL_error(L, "pdf.immediateobj() 3rd argument forbidden in file mode");
                pdf_begin_obj(static_pdf, k, OBJSTM_ALWAYS);
                buf.s = fread_to_buf(L, st2.s, &buf.l);
                pdf_out_block(static_pdf, (const char *) buf.s, buf.l);
                xfree(buf.s);
                pdf_end_obj(static_pdf);
            } else {
                pdf_begin_obj(static_pdf, k, OBJSTM_NEVER); /* not an object stream candidate! */
                pdf_begin_dict(static_pdf);
                if (n == first_arg + 2) {   /* write attr text */
                    if (!lua_isstring(L, first_arg + 2)) /* or number (maybe only string as it's an attr) */
                        luaL_error(L, "pdf.immediateobj() 3rd argument must be string");
                    st3.s = lua_tolstring(L, first_arg + 2, &st3.l);
                    pdf_out_block(static_pdf, st3.s, st3.l);
                    if (st3.s[st3.l - 1] != '\n')
                        pdf_out(static_pdf, '\n');
                }
                pdf_dict_add_streaminfo(static_pdf);
                pdf_end_dict(static_pdf);
                pdf_begin_stream(static_pdf);
                if (lua_key_eq(st1_s, stream)) {
                    pdf_out_block(static_pdf, st2.s, st2.l);
                }  else if (lua_key_eq(st1_s, streamfile)) {
                    buf.s = fread_to_buf(L, st2.s, &buf.l);
                    pdf_out_block(static_pdf, (const char *) buf.s, buf.l);
                    xfree(buf.s);
                } else
                    luaL_error(L, "pdf.immediateobj() invalid argument");
                pdf_end_stream(static_pdf);
                pdf_end_obj(static_pdf);
            }
            break;
        default:
            luaL_error(L, "pdf.immediateobj() allows max. 3 arguments");
    }
    lua_pushinteger(L, k);
    return 1;
}

static int table_obj(lua_State * L)
{
    const char *type;
    int k, obj_compression;
    int compress_level = -1;    /* unset */
    int os_threshold = OBJSTM_ALWAYS;   /* default: put non-stream objects into object streams */
    int saved_compress_level = static_pdf->compress_level;
    const_lstring attr, st;
    lstring buf;
    int immediate = 0;          /* default: not immediate */
    attr.s = st.s = NULL;
    attr.l = 0;
    assert(lua_istable(L, 1));  /* t */
    lua_key_rawgeti(type);
    if (lua_isnil(L, -1))       /* !vs t */
        luaL_error(L, "pdf.obj(): object \"type\" missing");
    if (lua_type(L,-1) != LUA_TSTRING)   /* !vs t */
        luaL_error(L, "pdf.obj(): object \"type\" must be string");
    type = lua_tostring(L, -1);
    if (! (lua_key_eq(type, raw) || lua_key_eq(type, stream))) {
        luaL_error(L, "pdf.obj(): \"%s\" is not a valid object type", type);     /* i vs t */
    }
    lua_pop(L, 1);              /* t */
    lua_key_rawgeti(immediate);
    if (!lua_isnil(L, -1)) {    /* b? t */
        if (!lua_isboolean(L, -1))      /* !b t */
            luaL_error(L, "pdf.obj(): \"immediate\" must be boolean");
        immediate = lua_toboolean(L, -1);       /* 0 or 1 */
    }
    lua_pop(L, 1);              /* t */

    /* is a reserved object referenced by "objnum"? */

    lua_key_rawgeti(objnum);
    if (!lua_isnil(L, -1)) {    /* vi? t */
        if (lua_type(L,-1) != LUA_TNUMBER)       /* !vi t */
            luaL_error(L, "pdf.obj(): \"objnum\" must be integer");
        k = (int) lua_tointeger(L, -1); /* vi t */
        check_obj_type(static_pdf, obj_type_obj, k);
        if (is_obj_scheduled(static_pdf, k) || obj_data_ptr(static_pdf, k) != 0)
            luaL_error(L, "pdf.obj() object in use");
    } else {
        static_pdf->obj_count++;
        k = pdf_create_obj(static_pdf, obj_type_obj, static_pdf->obj_ptr + 1);
    }
    pdf_last_obj = k;
    if (immediate == 0) {
        obj_data_ptr(static_pdf, k) = pdf_get_mem(static_pdf, pdfmem_obj_size);
        init_obj_obj(static_pdf, k);
    }
    lua_pop(L, 1);              /* t */

    /* get optional "attr" (allowed only for stream case) */

    lua_key_rawgeti(attr);
    if (!lua_isnil(L, -1)) {    /* attr-s? t */
        if (! lua_key_eq(type, stream))
            luaL_error(L, "pdf.obj(): \"attr\" key not allowed for non-stream object");
        if (!lua_isstring(L, -1)) /* or number */      /* !attr-s t */
            luaL_error(L, "pdf.obj(): object \"attr\" must be string");
        if (immediate == 1) {
            attr.s = lua_tolstring(L, -1, &attr.l);     /* attr-s t */
            lua_pop(L, 1);      /* t */
        } else
            obj_obj_stream_attr(static_pdf, k) = luaL_ref(Luas, LUA_REGISTRYINDEX);     /* t */
    } else {
        lua_pop(L, 1);          /* t */
    }

    /* get optional "compresslevel" (allowed only for stream case) */

    lua_key_rawgeti(compresslevel);
    if (!lua_isnil(L, -1)) {    /* vi? t */
        if (lua_key_eq(type, raw))
            luaL_error(L, "pdf.obj(): \"compresslevel\" key not allowed for raw object");
        if (lua_type(L, -1) != LUA_TNUMBER)       /* !vi t */
            luaL_error(L, "pdf.obj(): \"compresslevel\" must be integer");
        compress_level = (int) lua_tointeger(L, -1);    /* vi t */
        if (compress_level > 9)
            luaL_error(L, "pdf.obj(): \"compresslevel\" must be <= 9");
        else if (compress_level < 0)
            luaL_error(L, "pdf.obj(): \"compresslevel\" must be >= 0");
        if (immediate == 0)
            obj_obj_pdfcompresslevel(static_pdf, k) = compress_level;
    }
    lua_pop(L, 1);              /* t */

    /* get optional "objcompression" (allowed only for non-stream case) */

    lua_key_rawgeti(objcompression);
    if (!lua_isnil(L, -1)) {    /* b? t */
        if (lua_key_eq(type, stream))
            luaL_error(L, "pdf.obj(): \"objcompression\" key not allowed for stream object");
        if (!lua_isboolean(L, -1))      /* !b t */
            luaL_error(L, "pdf.obj(): \"objcompression\" must be boolean");
        obj_compression = lua_toboolean(L, -1); /* 0 or 1 */
        /* OBJSTM_NEVER: never into object stream; OBJSTM_ALWAYS: depends then on \pdfobjcompresslevel */
        if (obj_compression > 0)
            os_threshold = OBJSTM_ALWAYS;
        else
            os_threshold = OBJSTM_NEVER;
        if (immediate == 0)
            obj_obj_objstm_threshold(static_pdf, k) = os_threshold;
    }
    lua_pop(L, 1);              /* t */

    /* now the object contents for all cases are handled */

    lua_key_rawgeti(string);
    lua_key_rawgeti_n(file,-2);

    if (!lua_isnil(L, -1) && !lua_isnil(L, -2)) /* file-s? string-s? t */
        luaL_error(L, "pdf.obj(): \"string\" and \"file\" must not be given together");
    if (lua_isnil(L, -1) && lua_isnil(L, -2))   /* nil nil t */
        luaL_error(L, "pdf.obj(): no \"string\" or \"file\" given");

    if (lua_key_eq(type, raw)) {
        if (immediate == 1)
            pdf_begin_obj(static_pdf, k, os_threshold);
        if (!lua_isnil(L, -2)) {        /* file-s? string-s? t */
            /* from string */
            lua_pop(L, 1);      /* string-s? t */
            if (!lua_isstring(L, -1)) /* or number */   /* !string-s t */
                luaL_error(L, "pdf.obj(): \"string\" must be string for raw object");
            if (immediate == 1) {
                st.s = lua_tolstring(L, -1, &st.l);
                pdf_out_block(static_pdf, st.s, st.l);
            } else
                obj_obj_data(static_pdf, k) = luaL_ref(L, LUA_REGISTRYINDEX);   /* t */
        } else {
            /* from file */
            if (lua_type(L, -1) != LUA_TSTRING)   /* !file-s nil t */
                luaL_error(L, "pdf.obj(): \"file\" name must be string for raw object");
            if (immediate == 1) {
                st.s = lua_tolstring(L, -1, &st.l);     /* file-s nil t */
                buf.s = fread_to_buf(L, st.s, &buf.l);
                pdf_out_block(static_pdf, (const char *) buf.s, buf.l);
                /* already in pdf_end_obj:
                    if (buf.s[buf.l - 1] != '\n')
                        pdf_out(static_pdf, '\n');
                */
                xfree(buf.s);
            } else {
                set_obj_obj_is_file(static_pdf, k);
                obj_obj_data(static_pdf, k) = luaL_ref(L, LUA_REGISTRYINDEX);   /* nil t */
            }
        }
        if (immediate == 1)
            pdf_end_obj(static_pdf);
    } else {
        if (immediate == 1) {
            pdf_begin_obj(static_pdf, k, OBJSTM_NEVER); /* 0 = not an object stream candidate! */
            pdf_begin_dict(static_pdf);
            if (attr.s != NULL) {
                pdf_out_block(static_pdf, attr.s, attr.l);
                if (attr.s[attr.l - 1] != '\n')
                    pdf_out(static_pdf, '\n');
            }
            if (compress_level > -1)
                static_pdf->compress_level = compress_level;
            pdf_dict_add_streaminfo(static_pdf);
            pdf_end_dict(static_pdf);
            pdf_begin_stream(static_pdf);
        } else {
            set_obj_obj_is_stream(static_pdf, k);
            if (compress_level > -1)
                obj_obj_pdfcompresslevel(static_pdf, k) = compress_level;
        }
        if (!lua_isnil(L, -2)) {        /* file-s? string-s? t */
            /* from string */
            lua_pop(L, 1);      /* string-s? t */
            if (!lua_isstring(L, -1)) /* or number */  /* !string-s t */
                luaL_error(L, "pdf.obj(): \"string\" must be string for stream object");
            if (immediate == 1) {
                st.s = lua_tolstring(L, -1, &st.l);     /* string-s t */
                pdf_out_block(static_pdf, st.s, st.l);
            } else
                obj_obj_data(static_pdf, k) = luaL_ref(L, LUA_REGISTRYINDEX);   /* t */
        } else {
            /* from file */
            if (lua_type(L, -1) != LUA_TSTRING)   /* !file-s nil t */
                luaL_error(L, "pdf.obj(): \"file\" name must be string for stream object");
            if (immediate == 1) {
                st.s = lua_tolstring(L, -1, &st.l);     /* file-s nil t */
                buf.s = fread_to_buf(L, st.s, &buf.l);
                pdf_out_block(static_pdf, (const char *) buf.s, buf.l);
                xfree(buf.s);
            } else {
                set_obj_obj_is_file(static_pdf, k);
                obj_obj_data(static_pdf, k) = luaL_ref(L, LUA_REGISTRYINDEX);   /* nil t */
            }
        }
        if (immediate == 1) {
            pdf_end_stream(static_pdf);
            pdf_end_obj(static_pdf);
        }
    }
    static_pdf->compress_level = saved_compress_level;
    return k;
}

static int orig_obj(lua_State * L)
{
    int n, first_arg = 1;
    int k;
    const char *st_s = NULL ;
    n = lua_gettop(L);
    if ((n > 0) && (lua_type(L, 1) == LUA_TNUMBER)) {
        first_arg++;
        k = (int) lua_tointeger(L, 1);
        check_obj_type(static_pdf, obj_type_obj, k);
        if (is_obj_scheduled(static_pdf, k) || obj_data_ptr(static_pdf, k) != 0)
            luaL_error(L, "pdf.obj() object in use");
    } else {
        static_pdf->obj_count++;
        k = pdf_create_obj(static_pdf, obj_type_obj, static_pdf->obj_ptr + 1);
    }
    pdf_last_obj = k;
    obj_data_ptr(static_pdf, k) = pdf_get_mem(static_pdf, pdfmem_obj_size);
    init_obj_obj(static_pdf, k);
    switch (n - first_arg + 1) {
    case 0:
        luaL_error(L, "pdf.obj() needs at least one argument");
        break;
    case 1:
        if (!lua_isstring(L, first_arg)) /* or number */
            luaL_error(L, "pdf.obj() 1st argument must be string");
        break;
    case 2:
    case 3:
        if (lua_type(L, first_arg) != LUA_TSTRING)
            luaL_error(L, "pdf.obj() 1st argument must be string");
        if (!lua_isstring(L, first_arg + 1)) /* or number */
            luaL_error(L, "pdf.obj() 2nd argument must be string");
        st_s = lua_tostring(L, first_arg);
        if (lua_key_eq(st_s, file)) {
            if (n == first_arg + 2)
                luaL_error(L, "pdf.obj() 3rd argument forbidden in file mode");
            set_obj_obj_is_file(static_pdf, k);
        } else {
            if (n == first_arg + 2) {   /* write attr text */
                if (!lua_isstring(L, -1)) /* or number */
                    luaL_error(L, "pdf.obj() 3rd argument must be string");
                obj_obj_stream_attr(static_pdf, k) =
                    luaL_ref(Luas, LUA_REGISTRYINDEX);
            }
            if (lua_key_eq(st_s, stream)) {
                set_obj_obj_is_stream(static_pdf, k);
            } else if (lua_key_eq(st_s, streamfile)) {
                set_obj_obj_is_stream(static_pdf, k);
                set_obj_obj_is_file(static_pdf, k);
            } else
                luaL_error(L, "pdf.obj() invalid argument");
        }
        break;
    default:
        luaL_error(L, "pdf.obj() allows max. 3 arguments");
    }
    obj_obj_data(static_pdf, k) = luaL_ref(L, LUA_REGISTRYINDEX);
    return k;
}

static int l_obj(lua_State * L)
{
    int k, n;
    ensure_output_state(static_pdf, ST_HEADER_WRITTEN);
    n = lua_gettop(L);
    if (n == 1 && lua_istable(L, 1))
        k = table_obj(L);       /* new */
    else
        k = orig_obj(L);
    lua_pushinteger(L, k);
    return 1;
}

static int l_refobj(lua_State * L)
{
    int k, n;
    n = lua_gettop(L);
    if (n != 1)
        luaL_error(L, "pdf.refobj() needs exactly 1 argument");
    k = (int) luaL_checkinteger(L, 1);
    if (global_shipping_mode == NOT_SHIPPING)
        scan_refobj_lua(static_pdf, k);
    else
        pdf_ref_obj_lua(static_pdf, k);
    return 0;
}

static int l_reserveobj(lua_State * L)
{
    int n;
    const char *st_s = NULL;
    n = lua_gettop(L);
    switch (n) {
    case 0:
        static_pdf->obj_count++;
        pdf_last_obj = pdf_create_obj(static_pdf, obj_type_obj, static_pdf->obj_ptr + 1);
        break;
    case 1:
        if (lua_type(L, -1) != LUA_TSTRING)
            luaL_error(L, "pdf.reserveobj() optional argument must be string");
        st_s = luaL_checkstring(L, 1);
        if (lua_key_eq(st_s, annot)) {
            pdf_last_annot = pdf_create_obj(static_pdf, obj_type_annot, 0);
        } else {
            luaL_error(L, "pdf.reserveobj() optional string must be \"annot\"");
        }
        lua_pop(L, 1);
        break;
    default:
        luaL_error(L, "pdf.reserveobj() allows max. 1 argument");
    }
    lua_pushinteger(L, static_pdf->obj_ptr);
    return 1;
}

static int l_registerannot(lua_State * L)
{
    int n, i;
    n = lua_gettop(L);
    switch (n) {
    case 1:
        if (global_shipping_mode == NOT_SHIPPING)
            luaL_error(L, "pdf.registerannot() can only be used in late lua");
        i = (int) luaL_checkinteger(L, 1);
        if (i <= 0)
            luaL_error(L, "pdf.registerannot() can only register positive object numbers");
        addto_page_resources(static_pdf, obj_type_annot, i);
        break;
    default:
        luaL_error(L, "pdf.registerannot() needs exactly 1 argument");
    }
    return 0;
}

static int l_get_pdf_value(lua_State * L, int key)
{
    lua_rawgeti(L, LUA_REGISTRYINDEX, lua_key_index(pdf_data));
    lua_gettable(L, LUA_REGISTRYINDEX);
    /* [table] */
    lua_rawgeti(L, LUA_REGISTRYINDEX, key);
    /* [table] [key] */
    lua_rawget(L,-2);
    return 1;
}

static int l_get_pageresources(lua_State * L) {
    return l_get_pdf_value(L,lua_key_index(pageresources));
}
static int l_get_pageattributes(lua_State * L) {
    return l_get_pdf_value(L,lua_key_index(pageattributes));
}
static int l_get_pagesattributes(lua_State * L) {
    return l_get_pdf_value(L,lua_key_index(pagesattributes));
}
static int l_get_catalog(lua_State * L) {
    return l_get_pdf_value(L,lua_key_index(catalog));
}
static int l_get_info(lua_State * L) {
    return l_get_pdf_value(L,lua_key_index(info));
}
static int l_get_names(lua_State * L) {
    return l_get_pdf_value(L,lua_key_index(names));
}
static int l_get_trailer(lua_State * L) {
    return l_get_pdf_value(L,lua_key_index(trailer));
}
static int l_get_xformresources(lua_State * L) {
    return l_get_pdf_value(L,lua_key_index(xformresources));
}
static int l_get_xformattributes(lua_State * L) {
    return l_get_pdf_value(L,lua_key_index(xformattributes));
}

# define valid_pdf_key ( \
    lua_key_eq(s,catalog) || \
    lua_key_eq(s,info) || \
    lua_key_eq(s,trailer) || \
    lua_key_eq(s,names) || \
    lua_key_eq(s,pageattributes) || \
    lua_key_eq(s,pagesattributes) || \
    lua_key_eq(s,pageresources) \
)

static int getpdf(lua_State * L)
{
    /* [pdf table] [key] */
    const char *s ;
    if (lua_gettop(L) != 2) {
        return 0;
    }
    if (lua_type(L,-1) == LUA_TSTRING) {
        s =  lua_tostring(L, -1);
        if (lua_key_eq(s,h)) {
            lua_pushinteger(L, static_pdf->posstruct->pos.h);
            return 1;
        } else if (lua_key_eq(s,v)) {
            lua_pushinteger(L, static_pdf->posstruct->pos.v);
            return 1;
        } else if (valid_pdf_key) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, luaS_index(pdf_data));
            lua_gettable(L, LUA_REGISTRYINDEX);
            /* [pdf table] [key] [pdf.data table] */
            lua_replace(L, -3);
            /* [pdf.data table] [key] */
            lua_rawget(L, -2);
            return 1;
        }
    }
    return 0;
}

static int l_set_pdf_value(lua_State * L, int key)
{
    if (lua_type(L,-1) == LUA_TSTRING) {
        /* [value] */
        lua_rawgeti(L, LUA_REGISTRYINDEX, lua_key_index(pdf_data));
        lua_gettable(L, LUA_REGISTRYINDEX);
        /* [value] [table]  */
        lua_rawgeti(L, LUA_REGISTRYINDEX, key);
        /* [value] [table] [key] */
        lua_pushvalue(L, -3);
        /* [table] [key] [value] */
        lua_rawset(L,-3);
    }
    return 0;
}

static int l_set_pageresources(lua_State * L) {
    return l_set_pdf_value(L,lua_key_index(pageresources));
}
static int l_set_pageattributes(lua_State * L) {
    return l_set_pdf_value(L,lua_key_index(pageattributes));
}
static int l_set_pagesattributes(lua_State * L) {
    return l_set_pdf_value(L,lua_key_index(pagesattributes));
}
static int l_set_catalog(lua_State * L) {
    return l_set_pdf_value(L,lua_key_index(catalog));
}
static int l_set_info(lua_State * L) {
    return l_set_pdf_value(L,lua_key_index(info));
}
static int l_set_names(lua_State * L) {
    return l_set_pdf_value(L,lua_key_index(names));
}
static int l_set_trailer(lua_State * L) {
    return l_set_pdf_value(L,lua_key_index(trailer));
}
static int l_set_xformresources(lua_State * L) {
    return l_set_pdf_value(L,lua_key_index(xformresources));
}
static int l_set_xformattributes(lua_State * L) {
    return l_set_pdf_value(L,lua_key_index(xformattributes));
}

static int setpdf(lua_State * L)
{
    /* [pdf table] [key] [value] */
    const char *s ;
    if (lua_gettop(L) != 3) {
        return 0;
    }
    if (lua_type(L, -2) == LUA_TSTRING) {
        s = lua_tostring(L, -1);
        if (valid_pdf_key) {
            lua_rawgeti(L, LUA_REGISTRYINDEX, luaS_index(pdf_data));
            lua_gettable(L, LUA_REGISTRYINDEX);
            /* [pdf table] [key] [value] [pdf.data table] */
            lua_replace(L, -4);
            /* [pdf.data table] [key] [value] */
        }
    }
    lua_rawset(L, -3);
    return 0;
}

static int l_objtype(lua_State * L)
{
    int n = lua_gettop(L);
    if (n != 1)
        luaL_error(L, "pdf.objtype() needs exactly 1 argument");
    n = (int) luaL_checkinteger(L, 1);
    if (n < 0 || n > static_pdf->obj_ptr)
        lua_pushnil(L);
    else
        lua_pushstring(L, pdf_obj_typenames[obj_type(static_pdf, n)]);
    return 1;
}

static int l_maxobjnum(lua_State * L)
{
    int n = lua_gettop(L);
    if (n != 0)
        luaL_error(L, "pdf.maxobjnum() needs 0 arguments");
    lua_pushinteger(L, static_pdf->obj_ptr);
    return 1;
}

static int l_mapfile(lua_State * L)
{
    char *s;
    const char *st;
    if ((lua_type(L,-1) == LUA_TSTRING) && (st = lua_tostring(L, -1)) != NULL) {
        s = xstrdup(st);
        process_map_item(s, MAPFILE);
        free(s);
    }
    return 0;
}

static int l_mapline(lua_State * L)
{
    char *s;
    const char *st;
    if ((lua_type(L,-1) == LUA_TSTRING) && (st = lua_tostring(L, -1)) != NULL) {
        s = xstrdup(st);
        process_map_item(s, MAPLINE);
        free(s);
    }
    return 0;
}

static int l_pageref(lua_State * L)
{
    int n = lua_gettop(L);
    if (n != 1)
        luaL_error(L, "pdf.pageref() needs exactly 1 argument");
    n = (int) luaL_checkinteger(L, 1);
    if (n <= 0)
        luaL_error(L, "pdf.pageref() needs page number > 0");
    n = pdf_get_obj(static_pdf, obj_type_page, n, false);
    lua_pushinteger(L, n);
    return 1;
}

static int l_getpos(lua_State * L)
{
    lua_pushinteger(L, static_pdf->posstruct->pos.h);
    lua_pushinteger(L, static_pdf->posstruct->pos.v);
    return 2;
}

static int l_gethpos(lua_State * L)
{
    lua_pushinteger(L, static_pdf->posstruct->pos.h);
    return 1;
}

static int l_getvpos(lua_State * L)
{
    lua_pushinteger(L, static_pdf->posstruct->pos.v);
    return 1;
}

static int l_getmatrix(lua_State * L)
{
    if (matrix_stack_used > 0) {
        matrix_entry *m = &matrix_stack[matrix_stack_used - 1];
        lua_pushinteger(L, m->a);
        lua_pushinteger(L, m->b);
        lua_pushinteger(L, m->c);
        lua_pushinteger(L, m->d);
        lua_pushinteger(L, m->e);
        lua_pushinteger(L, m->f);
    } else {
        lua_pushinteger(L, 1);
        lua_pushinteger(L, 0);
        lua_pushinteger(L, 0);
        lua_pushinteger(L, 1);
        lua_pushinteger(L, 0);
        lua_pushinteger(L, 0);
    }
    return 6 ;
}

static int l_hasmatrix(lua_State * L)
{
    lua_pushboolean(L, (matrix_stack_used > 0));
    return 1 ;
}

static int l_get_lastlink(lua_State * L)
{
    lua_pushinteger(L, (pdf_last_link));
    return 1 ;
}

static int l_get_retval(lua_State * L)
{
    lua_pushinteger(L, (pdf_retval));
    return 1 ;
}

static int l_get_lastobj(lua_State * L)
{
    lua_pushinteger(L, (pdf_last_obj));
    return 1 ;
}

static int l_get_lastannot(lua_State * L)
{
    lua_pushinteger(L, (pdf_last_annot));
    return 1 ;
}

/* maybe:

    get_fontname    : set_ff(i)  obj_info(static_pdf, pdf_font_num(ff))
    get_fontobjnum  : set_ff(i)  pdf_font_num(ff)
    get_fontsize    : font_size(i)
    get_xformname   : obj_info(static_pdf, i)

*/

static int l_get_compresslevel(lua_State * L)
{
    lua_pushinteger(L, (pdf_compress_level));
    return 1 ;
}

static int l_get_objcompresslevel(lua_State * L)
{
    lua_pushinteger(L, (pdf_objcompresslevel));
    return 1 ;
}

static int l_set_compresslevel(lua_State * L)
{
    int c ;
    if (lua_type(L, 1) == LUA_TNUMBER) {
        c = (int) lua_tointeger(L, 1);
        if (c<0)
            c = 0 ;
        else if (c>9)
            c = 9 ;
        set_pdf_objcompresslevel(c);
    }
    return 0 ;
}

static int l_set_objcompresslevel(lua_State * L)
{
    int c ;
    if (lua_type(L, 1) == LUA_TNUMBER) {
        c = (int) lua_tointeger(L, 1);
        if (c<0)
            c = 0 ;
        else if (c>9)
            c = 9 ;
        set_pdf_compress_level(c);
    }
    return 0 ;
}

/* accuracy */

static int l_get_decimal_digits(lua_State * L)
{
    lua_pushinteger(L, (pdf_decimal_digits));
    return 1 ;
}


static int l_set_decimal_digits(lua_State * L)
{
    int c ;
    if (lua_type(L, 1) == LUA_TNUMBER) {
        c = (int) lua_tointeger(L, 1);
        if (c<0)
            c = 0 ;
        set_pdf_decimal_digits(c);
    }
    return 0 ;
}

/* pdf stuff */

static int getpdffontname(lua_State * L)
{
    int c, ff ;
    if (lua_type(L, 1) == LUA_TNUMBER) {
        c = (int) lua_tointeger(L, 1);
        pdf_check_vf(c);
        if (!font_used(c))
            pdf_init_font(static_pdf,c);
        set_ff(c);
        lua_pushinteger(L, (obj_info(static_pdf, pdf_font_num(ff))));
    } else {
        lua_pushnil(L);
    }
    return 1 ;
}

static int getpdffontobjnum(lua_State * L)
{
    int c, ff ;
    if (lua_type(L, 1) == LUA_TNUMBER) {
        c = (int) lua_tointeger(L, 1);
        pdf_check_vf(c);
        if (!font_used(c))
            pdf_init_font(static_pdf,c);
        set_ff(c);
        lua_pushinteger(L, (pdf_font_num(ff)));
    } else {
        lua_pushnil(L);
    }
    return 1 ;
}

static int getpdffontsize(lua_State * L)
{
    int c;
    if (lua_type(L, 1) == LUA_TNUMBER) {
        c = (int) lua_tointeger(L, 1);
        lua_pushinteger(L, (font_size(c)));
    } else {
        lua_pushnil(L);
    }
    return 1 ;
}

static int getpdfpageref(lua_State * L)
{
    int c ;
    if (lua_type(L, 1) == LUA_TNUMBER) {
        c = (int) lua_tointeger(L, 1);
        lua_pushinteger(L, (pdf_get_obj(static_pdf, obj_type_page, c, false)));
    } else {
        lua_pushnil(L);
    }
    return 1 ;
}

static int getpdfxformname(lua_State * L)
{
    int c ;
    if (lua_type(L, 1) == LUA_TNUMBER) {
        c = (int) lua_tointeger(L, 1);
        check_obj_type(static_pdf, obj_type_xform, c);
        lua_pushinteger(L, (obj_info(static_pdf, c)));
    } else {
        lua_pushnil(L);
    }
    return 1 ;
}

static int getpdfversion(lua_State * L)
{
    lua_pushinteger(L,1);
    return 1 ;
}

static int getpdfminorversion(lua_State * L)
{
 /* lua_pushinteger(L,static_pdf->minor_version); */
    lua_pushinteger(L,pdf_minor_version);
    return 1 ;
}

static int setpdfminorversion(lua_State * L)
{
    int c ;
    if (lua_type(L, 1) == LUA_TNUMBER) {
        c = (int) lua_tointeger(L, 1);
        if ((c >= 0) && (c <= 9)) {
            static_pdf->minor_version = c;
            set_pdf_minor_version(c);
        }
    }
    return 0 ;
}

static int setpdforigin(lua_State * L)
{
    int h = 0 ;
    int v = 0 ;
    if (lua_type(L, 1) == LUA_TNUMBER) {
        h = (int) lua_tointeger(L, 1);
        if (lua_type(L, 2) == LUA_TNUMBER) {
            v = (int) lua_tointeger(L, 1);
        } else {
            v = h;
        }
    }
    set_tex_extension_dimen_register(d_pdf_h_origin,h);
    set_tex_extension_dimen_register(d_pdf_v_origin,v);
    return 0 ;
}

static int getpdforigin(lua_State * L)
{
    lua_pushinteger(L,get_tex_extension_dimen_register(d_pdf_h_origin));
    lua_pushinteger(L,get_tex_extension_dimen_register(d_pdf_v_origin));
    return 2 ;
}

static int setpdfthreadmargin(lua_State * L) {
    if (lua_type(L, 1) == LUA_TNUMBER) {
        set_tex_extension_dimen_register(d_pdf_thread_margin,lua_tointeger(L, 1));
    }
    return 0;
}

static int setpdfdestmargin(lua_State * L) {
    if (lua_type(L, 1) == LUA_TNUMBER) {
        set_tex_extension_dimen_register(d_pdf_dest_margin,lua_tointeger(L, 1));
    }
    return 0;
}

static int setpdflinkmargin(lua_State * L) {
    if (lua_type(L, 1) == LUA_TNUMBER) {
        set_tex_extension_dimen_register(d_pdf_link_margin,lua_tointeger(L, 1));
    }
    return 0;
}

static int setpdfxformmargin(lua_State * L) {
    if (lua_type(L, 1) == LUA_TNUMBER) {
        set_tex_extension_dimen_register(d_pdf_xform_margin,lua_tointeger(L, 1));
    }
    return 0;
}

static int getpdfthreadmargin(lua_State * L) {
    lua_pushinteger(L,get_tex_extension_dimen_register(d_pdf_thread_margin));
    return 1;
}

static int getpdfdestmargin(lua_State * L) {
    lua_pushinteger(L,get_tex_extension_dimen_register(d_pdf_dest_margin));
    return 1;
}

static int getpdflinkmargin(lua_State * L) {
    lua_pushinteger(L,get_tex_extension_dimen_register(d_pdf_link_margin));
    return 1;
}

static int getpdfxformmargin(lua_State * L) {
    lua_pushinteger(L,get_tex_extension_dimen_register(d_pdf_xform_margin));
    return 1;
}

static int setpdfinclusionerrorlevel(lua_State * L) {
    if (lua_type(L, 1) == LUA_TNUMBER) {
        set_tex_extension_count_register(c_pdf_inclusion_errorlevel,lua_tointeger(L, 1));
    }
    return 0;
}

static int setpdfignoreunknownimages(lua_State * L) {
    if (lua_type(L, 1) == LUA_TNUMBER) {
        set_tex_extension_count_register(c_pdf_ignore_unknown_images,lua_tointeger(L, 1));
    }
    return 0;
}

static int getpdfinclusionerrorlevel(lua_State * L) {
    lua_pushinteger(L,get_tex_extension_count_register(c_pdf_inclusion_errorlevel));
    return 1;
}

static int getpdfignoreunknownimages(lua_State * L) {
    lua_pushinteger(L,get_tex_extension_count_register(c_pdf_ignore_unknown_images));
    return 1;
}

static int newpdfcolorstack(lua_State * L)
{
    const char *s = NULL;
    const char *l = NULL;
    int literal_mode = 0; /* set_origin */
    boolean page_start = false;
    int id ;
    if (lua_type(L,1) != LUA_TSTRING) {
        luaL_error(L, "pdf.newcolorstack() expects a string as first argument");
    }
    s =	lua_tostring(L, 1);
    if (lua_type(L,2) == LUA_TSTRING) {
        l =	lua_tostring(L, 2);
        if (lua_key_eq(l,origin)) {
            literal_mode = 0;
        } else if (lua_key_eq(l,page))  {
            literal_mode = 1; /* direct_page */
        } else if (lua_key_eq(l,direct)) {
            literal_mode = 2; /* direct_always */
        } else {
            luaL_error(L, "invalid literal mode in pdf.newcolorstack()");
        }
    }
    if (lua_isboolean(L, 3)) {
        page_start = lua_toboolean(L, 3);
    }
    id = newcolorstack(s, literal_mode, page_start);
    lua_pushinteger(L, id);
    return 1 ;
}

static const struct luaL_Reg pdflib[] = {
    { "gethpos", l_gethpos },
    { "getvpos", l_getvpos },
    { "obj", l_obj },
    { "immediateobj", l_immediateobj },
    { "refobj", l_refobj },
    { "registerannot", l_registerannot },
    { "reserveobj", l_reserveobj },
    { "getpos", l_getpos },
    { "pageref", getpdfpageref },
    { "maxobjnum", l_maxobjnum },
    { "pageref", l_pageref },
    { "print", luapdfprint },
    { "objtype", l_objtype },
    { "getmatrix", l_getmatrix },
    { "hasmatrix", l_hasmatrix },
    { "setcatalog", l_set_catalog },
    { "setinfo", l_set_info },
    { "setnames", l_set_names },
    { "settrailer", l_set_trailer },
    { "setpageresources", l_set_pageresources },
    { "setpageattributes", l_set_pageattributes },
    { "setpagesattributes", l_set_pagesattributes },
    { "setxformresources", l_set_xformresources },
    { "setxformattributes", l_set_xformattributes },
    { "getcatalog", l_get_catalog },
    { "getinfo", l_get_info },
    { "getnames", l_get_names },
    { "gettrailer", l_get_trailer },
    { "getpageresources", l_get_pageresources },
    { "getpageattributes", l_get_pageattributes },
    { "getpagesattributes", l_get_pagesattributes },
    { "getxformresources", l_get_xformresources },
    { "getxformattributes", l_get_xformattributes },
    { "getlastlink", l_get_lastlink },
    { "getretval", l_get_retval },
    { "getlastobj", l_get_lastobj },
    { "getlastannot", l_get_lastannot },
    { "getcompresslevel", l_get_compresslevel },
    { "getobjcompresslevel", l_get_objcompresslevel },
    { "setcompresslevel", l_set_compresslevel },
    { "setobjcompresslevel", l_set_objcompresslevel },
    { "getdecimaldigits", l_get_decimal_digits },
    { "setdecimaldigits", l_set_decimal_digits },
    /* moved from tex table */
    { "fontname", getpdffontname },
    { "fontobjnum", getpdffontobjnum },
    { "fontsize", getpdffontsize },
    { "xformname", getpdfxformname },
    { "getversion", getpdfversion },
    { "getminorversion", getpdfminorversion },
    { "setminorversion", setpdfminorversion },
    { "newcolorstack", newpdfcolorstack },
    { "setorigin", setpdforigin },
    { "getorigin", getpdforigin },
    { "setthreadmargin", setpdfthreadmargin },
    { "setdestmargin", setpdfdestmargin },
    { "setlinkmargin", setpdflinkmargin },
    { "setxformmargin", setpdfxformmargin },
    { "getthreadmargin", getpdfthreadmargin },
    { "getdestmargin", getpdfdestmargin },
    { "getlinkmargin", getpdflinkmargin },
    { "getxformmargin", getpdfxformmargin },
    { "getinclusionerrorlevel", getpdfinclusionerrorlevel },
    { "getignoreunknownimages", getpdfignoreunknownimages },
    { "setinclusionerrorlevel", setpdfinclusionerrorlevel },
    { "setignoreunknownimages", setpdfignoreunknownimages },
    { "mapfile", l_mapfile },
    { "mapline", l_mapline },
    /* sentinel */
    {NULL, NULL}
};

int luaopen_pdf(lua_State * L)
{
    lua_pushstring(L,"pdf.data");
    lua_newtable(L);
    lua_settable(L,LUA_REGISTRYINDEX);
    /* */
    luaL_register(L, "pdf", pdflib);
    /* build meta table */
    luaL_newmetatable(L, "pdf.meta");
    lua_pushstring(L, "__index");
    lua_pushcfunction(L, getpdf);
    /* do these later, NYI */
    lua_settable(L, -3);
    lua_pushstring(L, "__newindex");
    lua_pushcfunction(L, setpdf);
    lua_settable(L, -3);
    lua_setmetatable(L, -2);    /* meta to itself */
    return 1;
}
