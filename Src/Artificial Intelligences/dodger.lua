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

function chooseCurrent(openList)
    local chosen = 0
    local keyToFind = 0

    for key, i in pairs(openList) do
        if chosen == 0 or i["fCost"] < chosen["fCost"] or (i["fCost"] == chosen["fCost"] and i["hCost"] < chosen["hCost"]) then
            chosen = i
            keyToFind = key
        end
    end
    return chosen, keyToFind
end

function findElemWithPos(list, x, y)
    for key, value in pairs(list) do
        if value["posX"] == x and value["posY"] == y then
            return value
        end 
    end
    return 0
end

function computeHCost(startX, startY, endX, endY)
    local xDistance = 0
    local yDistance = 0

    if startX > endX then
        xDistance = startX - endX
    else
        xDistance = endX - startX
    end
    if startY > endY then
        yDistance = startY - endY
    else
        yDistance = endY - startY
    end
    return xDistance + yDistance
end

function getNeighbours(list, current, endNode)
    local neighbours = {}
    local left = findElemWithPos(list, current["posX"], current["posY"] - 1)
    local right = findElemWithPos(list, current["posX"], current["posY"] + 1)
    local up = findElemWithPos(list, current["posX"] - 1, current["posY"])
    local down = findElemWithPos(list, current["posX"] + 1, current["posY"])

    if left ~= 0 and left["blocked"] == 0 then
        table.insert(neighbours, left)
    end
    if right ~= 0 and right["blocked"] == 0 then
        table.insert(neighbours, right)
    end
    if up ~= 0 and up["blocked"] == 0 then
        table.insert(neighbours, up)
    end
    if down ~= 0 and down["blocked"] == 0 then
        table.insert(neighbours, down)
    end
    return neighbours
end

function findShortestPath(list, first, last)
    local openList = {}
    local closeList = {}
    local startNode = findElemWithPos(list, first["x"], first["y"])
    local endNode = findElemWithPos(list, last["x"], last["y"])

    if startNode == 0 then
        return 0
    end
    table.insert(openList, startNode)
    while 1 do
        local current, pos = chooseCurrent(openList)

        if current == 0 then
            return 0
        end
        table.remove(openList, pos)
        table.insert(closeList, current)

        if current["posX"] == last["x"] and current["posY"] == last["y"] then
            return 1
        end

        local neighbours = getNeighbours(list, current, endNode)
        
        for key, neighbour in pairs(neighbours) do
            if findElemWithPos(closeList, neighbour["posX"], neighbour["posY"]) == 0 then
                local gCost = current["gCost"] + 10
                local hCost = computeHCost(neighbour["posX"], neighbour["posY"], endNode["posX"], endNode["posY"])
                local fCost = gCost + hCost

                if neighbour["parent"] == nil or fCost < neighbour["fCost"] then
                    neighbour["gCost"] = gCost
                    neighbour["hCost"] = hCost
                    neighbour["fCost"] = fCost
                    neighbour["parent"] = current

                    if findElemWithPos(openList, neighbour["posX"], neighbour["posY"]) == 0 then
                        table.insert(openList, neighbour)
                    end
                end 
            end
        end
    end
end

function isPosThreatened(pos)
    if map[pos["x"]][pos["y"]] == BOMB or map[pos["x"]][pos["y"]] == FIRE then
        return true
    end
    for i = pos["y"] + 1, mapWidth - 1, 1 do
        if map[pos["x"]][i] == WALL or map[pos["x"]][i] == BOX or map[pos["x"]][i] == FENCE then
            break
        end
        if map[pos["x"]][i] == BOMB then
            return true
        end
    end
    for i = pos["y"] - 1, 0, -1 do
        if map[pos["x"]][i] == WALL or map[pos["x"]][i] == BOX or map[pos["x"]][i] == FENCE then
            break
        end
        if map[pos["x"]][i] == BOMB then
            return true
        end
    end
    for i = pos["x"] + 1, mapHeight - 1, 1 do
        if map[i][pos["y"]] == WALL or map[i][pos["y"]] == BOX or map[i][pos["y"]] == FENCE then
            break
        end
        if map[i][pos["y"]] == BOMB then
            return true
        end
    end
    for i = pos["x"] - 1, 0, -1 do
        if map[i][pos["y"]] == WALL or map[i][pos["y"]] == BOX or map[i][pos["y"]] == FENCE then
            break
        end
        if map[i][pos["y"]] == BOMB then
            return true
        end
    end
    return false
end

function setTileList(boxCount)
    local tileList = {}

    for x = 0, mapHeight - 1, 1 do
        for y = 0, mapWidth - 1, 1 do
            local tile = {}
    
            tile["blocked"] = 0
            if map[x][y] == WALL or map[x][y] == FENCE or map[x][y] == BOX or map[x][y] == BOMB or map[x][y] == FIRE then
                tile["blocked"] = 1
                if boxCount == false and map[x][y] == BOX then
                    tile["blocked"] = 0
                end
            end
            tile["gCost"] = 0
            tile["hCost"] = 0
            tile["fCost"] = 0
            tile["parent"] = nil
            tile["posX"] = x
            tile["posY"] = y
            table.insert(tileList, tile)
        end
    end
    return tileList
end

function copyTable(toCopy)
    local copy = {}

    for key, value in pairs(toCopy) do
        table.insert(copy, value)
    end
    return copy
end

function callSetDestination(tilePath, needToPutBomb)
    local destination = {}
    local target = {}

    if tilePath["posX"] > aiPosition["x"] and tilePath["posY"] == aiPosition["y"] then
        destination["x"] = aiPosition["x"] + 1
        destination["y"] = aiPosition["y"]
        if isPosThreatened(destination) == false or isPosThreatened(aiPosition) == true then
            setDirection(AI, "down")
        else
            setDirection(AI, "none")
        end
    elseif tilePath["posX"] < aiPosition["x"] and tilePath["posY"] == aiPosition["y"] then
        destination["x"] = aiPosition["x"] - 1
        destination["y"] = aiPosition["y"]
        if isPosThreatened(destination) == false or isPosThreatened(aiPosition) == true then
            setDirection(AI, "up")
        else
            setDirection(AI, "none")
        end
    elseif tilePath["posY"] > aiPosition["y"] and tilePath["posX"] == aiPosition["x"] then    
        destination["x"] = aiPosition["x"]
        destination["y"] = aiPosition["y"] + 1
        if isPosThreatened(destination) == false or isPosThreatened(aiPosition) == true then
            setDirection(AI, "right")
        else
            setDirection(AI, "none")
        end
    elseif tilePath["posY"] < aiPosition["y"] and tilePath["posX"] == aiPosition["x"] then
        destination["x"] = aiPosition["x"]
        destination["y"] = aiPosition["y"] - 1
        if isPosThreatened(destination) == false or isPosThreatened(aiPosition) == true then
            setDirection(AI, "left")
        else
            setDirection(AI, "none")
        end
    else
        setDirection(AI, "none")
    end
end

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

------------------ BEGINNING OF AI -----------------

function processAI()
    map = getMap(AI)
    local tileList = setTileList(true)
    local target = {}
    local needToPutBomb = false
    local isThreatened = false
    local agressiveMode = false

    if isPosThreatened(aiPosition) == true then
        local tiles = {}
        
        isThreatened = true
        for key, value in pairs(tileList) do
            local listCopy = copyTable(tileList)
            
            if value["blocked"] == 0 then
                local tileInfo = {}
                local elem = {}
                local pos = {}

                pos["x"] = value["posX"]
                pos["y"] = value["posY"]
                if isPosThreatened(pos) == false then
                    if findShortestPath(listCopy, aiPosition, pos) ~= 0 then
                        elem = findElemWithPos(listCopy, pos["x"], pos["y"])
                        tileInfo["x"] = pos["x"]
                        tileInfo["y"] = pos["y"]
                        tileInfo["fCost"] = elem["fCost"]
                        table.insert(tiles, tileInfo)
                    end
                end
            end
        end
        
        local picked = nil

        for key, value in pairs(tiles) do
            if picked == nil or value["fCost"] < picked["fCost"] then
                picked = value
            end
        end
        target["x"] = picked["x"]
        target["y"] = picked["y"]
    else
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
            if rand == "left" then
                target["x"] = aiPosition["x"]
                target["y"] = aiPosition["y"] - 1
            elseif rand == "right" then
                target["x"] = aiPosition["x"]
                target["y"] = aiPosition["y"] + 1
            elseif rand == "up" then
                target["x"] = aiPosition["x"] - 1
                target["y"] = aiPosition["y"]
            elseif rand == "down" then
                target["x"] = aiPosition["x"] + 1
                target["y"] = aiPosition["y"]
            end
            if isPosThreatened(target) == true then
                setDirection(AI, "none")
            else
                setDirection(AI, rand)
            end
            return
        end
        if previousDirection == "left" then
            target["x"] = aiPosition["x"]
            target["y"] = aiPosition["y"] + 1
        elseif previousDirection == "right" then
            target["x"] = aiPosition["x"]
            target["y"] = aiPosition["y"] - 1
        elseif previousDirection == "up" then
            target["x"] = aiPosition["x"] + 1
            target["y"] = aiPosition["y"]
        elseif previousDirection == "down" then
            target["x"] = aiPosition["x"] - 1
            target["y"] = aiPosition["y"]
        end
        if isPosThreatened(target) == true then
            setDirection(AI, "none")
        elseif aiIsBlocked() == true then
            if previousDirection == "left" then
                setDirection(AI, "right")
            elseif previousDirection == "right" then
                setDirection(AI, "left")
            elseif previousDirection == "up" then
                setDirection(AI, "down")
            elseif previousDirection == "down" then
                setDirection(AI, "up")
            end
        else
            setDirection(AI, "none")
        end
        return
    end

    tileList = setTileList(true)

    if findShortestPath(tileList, aiPosition, target) == 0 then
        setDirection(AI, "none")
    end

    local tilePath = findElemWithPos(tileList, target["x"], target["y"])

    while tilePath do
        if tilePath["parent"] == nil then
            break
        elseif tilePath["parent"]["parent"] ~= nil then
            tilePath = tilePath["parent"]
        else
            break
        end
    end

    callSetDestination(tilePath, needToPutBomb)
end

processAI()