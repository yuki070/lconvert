function add(x, y)
    print("func add", x, y)
    return x + y
end

function conv(IN)
--    print(Env["BRANCH"])
--    for k in pairs(IN) do
--        print(k, IN[k])
--    end
    OUT = {}

    OUT[1] = IN[2]
    OUT[2] = Env["BRANCH"].."_"..IN[1]
    i = 2
    j = math.pi
    k = j / 2
    l = math.sin(k)
    OUT[3] = string.format("%2.2f", l)
    OUT[4] = "fixed_field"
    OUT[5] = 1

--    for k in pairs(OUT) do
--        print(k, OUT[k])
--    end
    return OUT
end

-- test main
-- libconv = package.loadlib(os.getenv("BIPROG_ROOT").."/lib/libconv.so", "luaopen_libconv")()
--Env = { BRANCH = "GZ" }
--input = { "15876512577", "Hello", "13560395000" }
--output = conv(input)
--for k in pairs(output) do
--    print(k, output[k])
--end

--print(Env["BRANCH"])
