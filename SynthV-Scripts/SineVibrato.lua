--[[
作者： ObjectNotFound <xml@live.com>.
修改重发布必须署原作者名。
免费使用，不得以任何方式进行销售，包括独立销售和捆绑销售等。
--]]

-- 插件基本信息
function getClientInfo()
    return {
        name = 'SineVibrato',
        author = 'ObjectNotFound <xml@live.com>',
        versionNumber = 1,
        minEditorVersion = 65540
    }
end

-- 计算参数数值
function calculateParam(freq, depth, length, left, right, sampleBlick, blickPerSec)
    local xCoe = math.pi * 2 * freq
    local depthCents = depth
    local delta = {}
    
    -- 淡入部分
    local currentBlick = 0
    local leftSample = math.floor(left / sampleBlick)
    for i = 1, leftSample do
        delta[#delta+1] = math.sin(xCoe * (currentBlick / blickPerSec)) * (i / leftSample) * depthCents
        currentBlick = currentBlick + sampleBlick
    end
    
    -- 标准部分
    for i = 1, math.floor((length - left - right) / sampleBlick) do
        delta[#delta+1] = math.sin(xCoe * (currentBlick / blickPerSec)) * depthCents
        currentBlick = currentBlick + sampleBlick
    end
    
    -- 淡出部分
    local rightSample = math.floor(right / sampleBlick)
    for i = 1, rightSample do
        delta[#delta+1] = math.sin(xCoe * (currentBlick / blickPerSec)) * ((rightSample - i) / rightSample) * depthCents
        currentBlick = currentBlick + sampleBlick
    end
    return delta
end

function writeParam(notegroup, param, start, stop, delta, sampleBlick, ratio)
    local param = notegroup:getParameter(param)
    local startPoint = param:get(start)
    local stopPoint = param:get(stop)
    local j = start
    for k = 1, #delta do
        local point = param:get(j)
        point = point + delta[k] * ratio
        param:add(j, point)
        j = j + sampleBlick
    end
    param:add(start, startPoint)
    param:add(stop, stopPoint)
end

-- 拿到所有已选中的音符时间范围，单位是b
function getNoteRange()
    -- 拿到音符
    local notes = SV:getMainEditor():getSelection():getSelectedNotes()
    -- 没有就直接退出
    if #notes == 0 then
        return
    end
    -- 按时间先后顺序排序
    table.sort( notes, function (A, B)
        return A:getOnset() < B:getOnset()
    end)
    
    local range = {}
    for i = 1, #notes do
        range[#range+1] = {notes[i]:getOnset(), notes[i]:getEnd()}
    end
    return range
end


function main()
    -- Form
    local form = {
        title = 'SineVibrato',
        message = 'SineVibrato ported to Synthesizer V\nObjectNotFound <xml@live.com>',
        buttons = 'OkCancel',
        widgets = {
            {
                name = 'pitch',
                type = 'CheckBox',
                text = '音高偏差',
                default = false
            },
            {
                name = 'tension',
                type = 'CheckBox',
                text = '张力',
                default = false
            },
            {
                name = 'dynamics',
                type = 'CheckBox',
                text = '响度',
                default = false
            },
            {
                name = 'breath',
                type = 'CheckBox',
                text = '气声',
                default = false
            },
            {
                name = 'gender',
                type = 'CheckBox',
                text = '性别',
                default = false
            },
            {
                name = 'freq',
                type = 'Slider',
                label = '频率',
                format = '%1.2f',
                minValue = 0.01,
                maxValue = 20,
                interval = 0.01,
                default = 5.5
            },
            {
                -- 实际最高可1200音分（12个半音，即一个八度）
                name = 'depth',
                type = 'Slider',
                label = '深度',
                format = '%1.2f',
                minValue = 0.01,
                maxValue = 5,
                interval = 0.01,
                default = 1.0
            },
            {
                name = 'left',
                type = 'Slider',
                label = '左侧淡入',
                format = '%1.2f',
                minValue = 0,
                maxValue = 1.5,
                interval = 0.01,
                default = 0.25
            },
            {
                name = 'right',
                type = 'Slider',
                label = '右侧淡出',
                format = '%1.2f',
                minValue = 0,
                maxValue = 1.5,
                interval = 0.01,
                default = 0.25
            }
        }
    }
    
    local result = SV:showCustomDialog(form)
    if result.status then
        -- 计算点间隔
        local sampleBlick = math.floor(SV.QUARTER / 64)
        -- 获取音符
        local notegroup = SV:getMainEditor():getCurrentGroup():getTarget()
        local range = getNoteRange()
        -- 遍历音符
        for i=1, #range do
            local start = range[i][1]
            local stop = range[i][2]
            -- 时间轴
            local timeAxis = SV:getProject():getTimeAxis()
            local bpm = timeAxis:getTempoMarkAt(start).bpm
            local blickPerSec = SV:seconds2Blick(1, bpm)
            
            local leftBlick = result.answers.left * blickPerSec
            local rightBlick = result.answers.right * blickPerSec
        
            local delta = calculateParam(result.answers.freq, result.answers.depth, stop - start,
                leftBlick, rightBlick, sampleBlick, blickPerSec)
            if result.answers.pitch then
                writeParam(notegroup, 'pitchDelta', start, stop, delta, sampleBlick, 15)
            end
            if result.answers.tension then
                writeParam(notegroup, 'tension', start, stop, delta, sampleBlick, 0.05)
            end
            if result.answers.dynamics then
                writeParam(notegroup, 'loudness', start, stop, delta, sampleBlick, 0.6)
            end
            if result.answers.breath then
                writeParam(notegroup, 'breathiness', start, stop, delta, sampleBlick, 0.05)
            end
            if result.answers.gender then
                writeParam(notegroup, 'gender', start, stop, delta, sampleBlick, 0.05)
            end
        end
    end
    
    SV:finish()

end
