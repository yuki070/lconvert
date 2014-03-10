function conv(IN)
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

    return OUT
end

-- test main
--Env = { BRANCH = "GZ" }
--input = { "15876512577", "Hello", "13560395000" }
--output = conv(input)
--for k in pairs(output) do
--    print(k, output[k])
--end
