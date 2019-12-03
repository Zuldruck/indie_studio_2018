EMPTY = 0
FENCE = 1
WALL = 2
BOX = 3
EXIT = 4
BOMB = 5
FIRE = 6
BONUS = 7
map = getMap(AI)
mapWidth = getMapWidth(AI)
mapHeight = getMapHeight(AI)
aiPosition = getAIPosition(AI)

previousDirection = getPreviousDirection(AI)

math.randomseed(os.time())

function doRandom()
    rand = math.random(1, 4)
    direction = ""

    if rand == 1 then
        direction = "right"
    elseif rand == 2 then
        direction = "left"
    elseif rand == 3 then
        direction = "up"
    elseif rand == 4 then
        direction = "down"
    end
    return direction
end

function isBlockBlocked(block)
    if block == WALL or block == FENCE or block == BOX or block == BOMB then
        return true
    end
    return false
end

function aiIsBlocked()
    local up = map[aiPosition["x"] - 1][aiPosition["y"]]
    local down = map[aiPosition["x"] + 1][aiPosition["y"]]
    local right = map[aiPosition["x"]][aiPosition["y"] + 1]
    local left = map[aiPosition["x"]][aiPosition["y"] - 1]

    if previousDirection == "left" then
        if isBlockBlocked(up) and isBlockBlocked(down) and isBlockBlocked(left) then
            return true
        end
    elseif previousDirection == "right" then
        if isBlockBlocked(up) and isBlockBlocked(down) and isBlockBlocked(right) then
            return true
        end
    elseif previousDirection == "down" then
        if isBlockBlocked(left) and isBlockBlocked(right) and isBlockBlocked(down) then
            return true
        end
    elseif previousDirection == "up" then
        if isBlockBlocked(left) and isBlockBlocked(right) and isBlockBlocked(up) then
            return true
        end
    end
    return false
end

function isDirectionBlocked(dir)
    local up = map[aiPosition["x"] - 1][aiPosition["y"]]
    local down = map[aiPosition["x"] + 1][aiPosition["y"]]
    local right = map[aiPosition["x"]][aiPosition["y"] + 1]
    local left = map[aiPosition["x"]][aiPosition["y"] - 1]

    if dir == "left" then
        if isBlockBlocked(left) == true then
            return true
        end
    elseif dir == "right" then
        if isBlockBlocked(right) == true then
            return true
        end
    elseif dir == "up" then
        if isBlockBlocked(up) == true then
            return true
        end
    elseif dir == "down" then
        if isBlockBlocked(down) == true then
            return true
        end
    end
    return false
end

function isAtIntersection()
    local up = map[aiPosition["x"] - 1][aiPosition["y"]]
    local down = map[aiPosition["x"] + 1][aiPosition["y"]]
    local right = map[aiPosition["x"]][aiPosition["y"] + 1]
    local left = map[aiPosition["x"]][aiPosition["y"] - 1]

    if previousDirection == "none" then
        return true
    elseif previousDirection == "left" and (isBlockBlocked(down) == false or isBlockBlocked(up) == false) then
        return true
    elseif previousDirection == "right" and (isBlockBlocked(down) == false or isBlockBlocked(up) == false) then
        return true
    elseif previousDirection == "down" and (isBlockBlocked(left) == false or isBlockBlocked(right) == false) then
        return true
    elseif previousDirection == "up" and (isBlockBlocked(left) == false or isBlockBlocked(right) == false) then
        return true
    end
    return false
end

function isTakingOpposite(dir)
    if previousDirection == "left" and dir == "right" then
        return true
    elseif previousDirection == "right" and dir == "left" then
        return true
    elseif previousDirection == "down" and dir == "up" then
        return true
    elseif previousDirection == "up" and dir == "down" then
        return true
    end
    return false
end

function isAiIsolated()
    local up = map[aiPosition["x"] - 1][aiPosition["y"]]
    local down = map[aiPosition["x"] + 1][aiPosition["y"]]
    local right = map[aiPosition["x"]][aiPosition["y"] + 1]
    local left = map[aiPosition["x"]][aiPosition["y"] - 1]

    if isBlockBlocked(up) and isBlockBlocked(down) and isBlockBlocked(left) and isBlockBlocked(right) then
        return true
    end
    return false
end

if isAiIsolated() == true then
    setDirection(AI, "none")
    return
end

rand = doRandom()

if isAtIntersection() == true then
    local count = 0
    while isDirectionBlocked(rand) == true or isTakingOpposite(rand) == true do
        if count > 100 then
            break
        end
        rand = doRandom()
        count = count + 1
    end
    setDirection(AI, rand)
    return
end

if aiIsBlocked() == true then
    if previousDirection == "left" then
        setDirection(AI, "right")
    elseif previousDirection == "right" then
        setDirection(AI, "left")
    elseif previousDirection == "up" then
        setDirection(AI, "down")
    elseif previousDirection == "down" then
        setDirection(AI, "up")
    end
end
