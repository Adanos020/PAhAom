-- Vector and rectangle types.

function is_vector(v)
    return (type(v) == "table") and v.x and v.y
end

function vectors_equal(v1, v2)
    assert(is_vector(v1))
    assert(is_vector(v2))

    return v1.x == v2.x and v1.y == v2.y
end

function is_rectangle(v)
    return (type(v) == "table") and is_vector(v.position) and is_vector(v.size)
end

function rectangles_intersect(r1, r2)
    assert(is_rectangle(r1))
    assert(is_rectangle(r2))

    local r1_min_x = math.min(r1.position.x, r1.position.x + r1.size.x)
    local r1_max_x = math.max(r1.position.x, r1.position.x + r1.size.x)
    local r1_min_y = math.min(r1.position.y, r1.position.y + r1.size.y)
    local r1_max_y = math.max(r1.position.y, r1.position.y + r1.size.y)

    local r2_min_x = math.min(r2.position.x, r2.position.x + r2.size.x)
    local r2_max_x = math.max(r2.position.x, r2.position.x + r2.size.x)
    local r2_min_y = math.min(r2.position.y, r2.position.y + r2.size.y)
    local r2_max_y = math.max(r2.position.y, r2.position.y + r2.size.y)

    local il = math.max(r1_min_x, r2_min_x)
    local it = math.max(r1_min_y, r2_min_y)
    local ir = math.min(r1_max_x, r2_max_x)
    local ib = math.min(r1_max_y, r2_max_y)

    return il < ir and it < ib
end

function rectangle_contains(rect, point)
    assert(is_rectangle(rect))
    assert(is_vector(point))

    local min_x = math.min(rect.position.x, rect.position.x + rect.size.x - 1)
    local max_x = math.max(rect.position.x, rect.position.x + rect.size.x - 1)
    local min_y = math.min(rect.position.y, rect.position.y + rect.size.y - 1)
    local max_y = math.max(rect.position.y, rect.position.y + rect.size.y - 1)

    return point.x >= min_x and point.x <= max_x
       and point.y >= min_y and point.y <= max_y
end

-- Mathematical.

function math.clamp(v, l, h)
    return math.min(math.max(v, l), h)
end

-- Functional.

function table.all(array, pred)
    assert(type(array) == "table" and type(pred) == "function")
    for i,el in ipairs(array) do
        if not pred(el) then return false end
    end
    return true
end

function table.any(array, pred)
    return not table.all(array, function(x) return not pred(x) end)
end

function table.none(array, pred)
    return not table.any(array, pred)
end