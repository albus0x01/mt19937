-- package.cpath = "../../../luaclib/?.so"
local mt19937 = require("mt19937")

function normal()
    mt19937.randomseed(100)
    print(mt19937.random(100, 100000))
end

function multi()
    player1.mt19937 = require("mt19937")
    player1.mt19937.randomseed(100)
    local player2 = {}
    package.loaded["mt19937"] = nil
    player2.mt19937 = require("mt19937")
    --  print(player1.mt19937, player2.mt19937)
    player2.mt19937.randomseed(500)
    print(player1.mt19937.random(1, 100))
    print(player1.mt19937.random(1, 100))
    print(player2.mt19937.random(1, 100))
    print(player2.mt19937.random(1, 100))
    print(player2.mt19937.random(1, 100))
end

function main()
    normal()
end

main()