static int
context_create (lua_State *L) {
    cairo_surface_t **surface = luaL_checkudata(L, 1, MT_NAME_SURFACE);
    cairo_t **obj;
    obj = lua_newuserdata(L, sizeof(cairo_t *));
    *obj = 0;
    luaL_getmetatable(L, MT_NAME_CONTEXT);
    lua_setmetatable(L, -2);
    *obj = cairo_create(*surface);
    return 1;
}

static int
cr_gc (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_destroy(*obj);
    *obj = 0;
    return 0;
}

static int
cr_arc (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_arc(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
              luaL_checknumber(L, 4), luaL_checknumber(L, 5),
              luaL_checknumber(L, 6));
    return 0;
}

static int
cr_close_path (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_close_path(*obj);
    return 0;
}

static int
cr_curve_to (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_curve_to(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
                   luaL_checknumber(L, 4), luaL_checknumber(L, 5),
                   luaL_checknumber(L, 6), luaL_checknumber(L, 7));
    return 0;
}

static int
cr_fill (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_fill(*obj);
    return 0;
}

static int
cr_fill_preserve (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_fill_preserve(*obj);
    return 0;
}

static int
cr_get_dash (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    int cnt, i;
    double *dashes = 0, offset;

    cnt = cairo_get_dash_count(*obj);
    if (cnt > 0) {
        dashes = malloc(sizeof(double) * cnt);
        assert(dashes);
    }

    cairo_get_dash(*obj, dashes, &offset);

    lua_createtable(L, cnt, 0);
    for (i = 0; i < cnt; ++i) {
        lua_pushnumber(L, dashes[i]);
        lua_rawseti(L, -2, i + 1);
    }
    lua_pushnumber(L, offset);

    if (cnt > 0)
        free(dashes);
    return 2;
}

static int
cr_get_fill_rule (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    switch (cairo_get_fill_rule(*obj)) {
        case CAIRO_FILL_RULE_WINDING:  lua_pushliteral(L, "winding");   break;
        case CAIRO_FILL_RULE_EVEN_ODD: lua_pushliteral(L, "even-odd");  break;
        default:                       lua_pushliteral(L, "<invalid>"); break;
    }
    return 1;
}

static int
cr_get_line_cap (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    switch (cairo_get_line_cap(*obj)) {
        case CAIRO_LINE_CAP_BUTT:   lua_pushliteral(L, "butt");      break;
        case CAIRO_LINE_CAP_ROUND:  lua_pushliteral(L, "round");     break;
        case CAIRO_LINE_CAP_SQUARE: lua_pushliteral(L, "square");    break;
        default:                    lua_pushliteral(L, "<invalid>"); break;
    }
    return 1;
}

static int
cr_get_line_join (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    switch (cairo_get_line_join(*obj)) {
        case CAIRO_LINE_JOIN_MITER: lua_pushliteral(L, "miter");     break;
        case CAIRO_LINE_JOIN_ROUND: lua_pushliteral(L, "round");     break;
        case CAIRO_LINE_JOIN_BEVEL: lua_pushliteral(L, "bevel");     break;
        default:                    lua_pushliteral(L, "<invalid>"); break;
    }
    return 1;
}

static int
cr_get_line_width (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushnumber(L, cairo_get_line_width(*obj));
    return 1;
}

static int
cr_get_miter_limit (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushnumber(L, cairo_get_miter_limit(*obj));
    return 1;
}

static int
cr_get_tolerance (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushnumber(L, cairo_get_tolerance(*obj));
    return 1;
}

static int
cr_in_fill (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushboolean(L,
        cairo_in_fill(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3)));
    return 1;
}

static int
cr_in_stroke (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    lua_pushboolean(L,
        cairo_in_stroke(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3)));
    return 1;
}

static int
cr_line_to (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_line_to(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
    return 0;
}

static int
cr_move_to (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_move_to(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3));
    return 0;
}

static int
cr_new_path (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_new_path(*obj);
    return 0;
}

static int
cr_new_sub_path (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_new_sub_path(*obj);
    return 0;
}

static int
cr_paint (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_paint(*obj);
    return 0;
}

static int
cr_paint_with_alpha (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_paint_with_alpha(*obj, luaL_checknumber(L, 2));
    return 0;
}

static int
cr_rectangle (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_rectangle(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
                    luaL_checknumber(L, 4), luaL_checknumber(L, 5));
    return 0;
}

static int
cr_set_dash (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    int num_dashes, i;
    double *dashes = 0, offset;

    luaL_checktype(L, 2, LUA_TTABLE);
    offset = luaL_checknumber(L, 3);

    num_dashes = lua_objlen(L, 2);
    if (num_dashes > 0) {
        dashes = malloc(sizeof(double) * num_dashes);
        assert(dashes);
        for (i = 0; i < num_dashes; ++i) {
            lua_rawgeti(L, 2, i + 1);
            if (!lua_isnumber(L, -1)) {
                free(dashes);
                return luaL_error(L, "bad dash pattern, dash value %d isn't"
                                  " a number", i + 1);
            }
            dashes[i] = lua_tonumber(L, -1);
            lua_pop(L, 1);
        }
    }

    cairo_set_dash(*obj, dashes, num_dashes, offset);

    if (num_dashes > 0)
        free(dashes);
    return 0;
}

static int
cr_set_fill_rule (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_fill_rule(*obj,
            fillrule_values[luaL_checkoption(L, 2, 0, fillrule_names)]);
    return 0;
}

static int
cr_set_line_cap (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_line_cap(*obj,
            linecap_values[luaL_checkoption(L, 2, 0, linecap_names)]);
    return 0;
}

static int
cr_set_line_join (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_line_join(*obj,
            linejoin_values[luaL_checkoption(L, 2, 0, linejoin_names)]);
    return 0;
}

static int
cr_set_line_width (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_line_width(*obj, luaL_checknumber(L, 2));
    return 0;
}

static int
cr_set_miter_limit (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_miter_limit(*obj, luaL_checknumber(L, 2));
    return 0;
}

static int
cr_set_source_rgb (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_source_rgb(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
                         luaL_checknumber(L, 4));
    return 0;
}

static int
cr_set_source_rgba (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_source_rgba(*obj, luaL_checknumber(L, 2), luaL_checknumber(L, 3),
                          luaL_checknumber(L, 4), luaL_checknumber(L, 5));
    return 0;
}

static int
cr_set_tolerance (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_set_tolerance(*obj, luaL_checknumber(L, 2));
    return 0;
}

static int
cr_stroke (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_stroke(*obj);
    return 0;
}

static int
cr_stroke_preserve (lua_State *L) {
    cairo_t **obj = luaL_checkudata(L, 1, MT_NAME_CONTEXT);
    cairo_stroke_preserve(*obj);
    return 0;
}

static const luaL_Reg
context_methods[] = {
    { "__gc", cr_gc },
    { "arc", cr_arc },
    { "close_path", cr_close_path },
    { "curve_to", cr_curve_to },
    { "fill", cr_fill },
    { "fill_preserve", cr_fill_preserve },
    { "get_dash", cr_get_dash },
    { "get_fill_rule", cr_get_fill_rule },
    { "get_line_cap", cr_get_line_cap },
    { "get_line_join", cr_get_line_join },
    { "get_line_width", cr_get_line_width },
    { "get_miter_limit", cr_get_miter_limit },
    { "get_tolerance", cr_get_tolerance },
    { "in_fill", cr_in_fill },
    { "in_stroke", cr_in_stroke },
    { "line_to", cr_line_to },
    { "move_to", cr_move_to },
    { "new_path", cr_new_path },
    { "new_sub_path", cr_new_sub_path },
    { "paint", cr_paint },
    { "paint_with_alpha", cr_paint_with_alpha },
    { "rectangle", cr_rectangle },
    { "set_dash", cr_set_dash },
    { "set_fill_rule", cr_set_fill_rule },
    { "set_line_cap", cr_set_line_cap },
    { "set_line_join", cr_set_line_join },
    { "set_line_width", cr_set_line_width },
    { "set_miter_limit", cr_set_miter_limit },
    { "set_source_rgb", cr_set_source_rgb },
    { "set_source_rgba", cr_set_source_rgba },
    { "set_tolerance", cr_set_tolerance },
    { "stroke", cr_stroke },
    { "stroke_preserve", cr_stroke_preserve },
    { 0, 0 }
};

/* vi:set ts=4 sw=4 expandtab: */
