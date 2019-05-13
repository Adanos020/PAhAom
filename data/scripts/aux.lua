-- Mathematical.

function math.clamp(v, l, h)
    return math.min(math.max(v, l), h)
end

-- Functional.

function table.all(array, pred)
    assert(type(array) == "table")
    assert(type(pred) == "function")

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