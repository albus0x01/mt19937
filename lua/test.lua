-- package.cpath = "../../../luaclib/?.so"
local mt19937 = require("mt19937")

function main()
    mt19937.randomseed(100)
    print(mt19937.random(100, 100000))
end

main()