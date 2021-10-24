--[[
作者： ObjectNotFound <xml@live.com>.
修改重发布必须署原作者名。
免费使用，不得以任何方式进行销售，包括独立销售和捆绑销售等。
--]]

--[[
更新日志(Alpha v1.3起)：
-- Alpha v1.4
1.中英双语界面支持。
2.随着1.3的修复，发声参数现在也可正弦颤抖。
3.增加选项，可选择是否抹去SynthV内置的颤音设置。
-- Alpha v1.3:
1.修正了平滑带来的参数设置问题。
2.加入更新日志。
--]]


-- 插件基本信息
SCRIPT_TITLE = 'SineVibrato Beta v1.5'
SCRIPT_INFO = 'SineVibrato ported to Synthesizer V\nObjectNotFound <xml@live.com>'

function getClientInfo()
    return {
        name = SV:T(SCRIPT_TITLE),
        author = 'ObjectNotFound <xml@live.com>',
        versionNumber = 1,
        minEditorVersion = 65540
    }
end

function getTranslations(langCode)
    if langCode == 'zh-cn' then
        return {
            {SCRIPT_TITLE, '参数颤音 Beta v1.5'},
            {SCRIPT_INFO, '适用于Synthesizer V的参数颤音插件\nObjectNotFound <xml@live.com>'},
            {'Number of Control points (per quarter note)', '控制点数量（个每四分音符）'},
            {'Pitch Deviation', '音高偏差'},
            {'Tension', '张力'},
            {'Loudness', '响度'},
            {'Breathiness', '气声'},
            {'Gender', '性别'},
            {'Voicing', '发声'},
            {'Freq (Hz)', '频率（赫兹）'},
            {'Depth (Semitone)', '深度（半音）'},
            {'Left Fade In (Second)', '左侧淡入（秒）'},
            {'Right Fade Out (Second)', '右侧淡出（秒）'},
            {'Parameter Curve Smoothness', '参数曲线平滑度'},
            {'Zero out Vibrato Depth in \'Note Properties\' panel', '将“音符属性”面板中的颤音深度置0'}
        }
    end
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

function writeParam(notegroup, param, start, stop, delta, sampleBlick, ratio, simplifyValue)
    local param = notegroup:getParameter(param)
    local startPoint = param:get(start)
    local stopPoint = param:get(stop)
    -- 保存原来的点值，避免平滑
    local origin = {}
    local j = start
    for k = 1, #delta do
        if j > stop then
            break
        end
        
        param:remove(j - sampleBlick, j)
        origin[k] = param:get(j)
        
        j = j + sampleBlick
    end
    
    j = start
    for k = 1, #delta do
        if j > stop then
            break
        end
        
        local point = origin[k]
        point = point + delta[k] * ratio
        param:add(j, point)
        
        j = j + sampleBlick
    end
    param:add(start, startPoint)
    param:add(stop, stopPoint)
    param:simplify(startPoint, stopPoint, simplifyValue)
end

-- 拿到所有已选中的音符时间范围，单位是b
function getNoteRange(eraseDepth)
    -- 拿到音符
    local notes = SV:getMainEditor():getSelection():getSelectedNotes()
    -- 没有就直接退出
    if #notes == 0 then
        return {}
    end
    -- 按时间先后顺序排序
    table.sort( notes, function (A, B)
        return A:getOnset() < B:getOnset()
    end)
    
    local range = {}
    for i = 1, #notes do
        range[#range+1] = {notes[i]:getOnset(), notes[i]:getEnd()}
        -- 在这里清除颤音参数
        if eraseDepth then
            notes[i]:setAttributes({
                dF0Vbr = 0
            })
        end
    end
    return range
end


function main()
    -- Form
    local form = {
        title = SV:T(SCRIPT_TITLE),
        message = SV:T(SCRIPT_INFO),
        buttons = 'OkCancel',
        widgets = {
            {
                name = 'sampleRate',
                type = 'ComboBox',
                label = SV:T('Number of Control points (per quarter note)'),
                choices = {'32', '64', '128', '256'},
                default = 1
            },
            {
                name = 'pitch',
                type = 'CheckBox',
                text = SV:T('Pitch Deviation'),
                default = false
            },
            {
                name = 'tension',
                type = 'CheckBox',
                text = SV:T('Tension'),
                default = false
            },
            {
                name = 'dynamics',
                type = 'CheckBox',
                text = SV:T('Loudness'),
                default = false
            },
            {
                name = 'breath',
                type = 'CheckBox',
                text = SV:T('Breathiness'),
                default = false
            },
            {
                name = 'gender',
                type = 'CheckBox',
                text = SV:T('Gender'),
                default = false
            },
            {
                name = 'voice',
                type = 'CheckBox',
                text = SV:T('Voicing'),
                default = false
            },
            {
                name = 'freq',
                type = 'Slider',
                label = SV:T('Freq (Hz)'),
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
                label = SV:T('Depth (Semitone)'),
                format = '%1.2f',
                minValue = 0.01,
                maxValue = 5,
                interval = 0.01,
                default = 1.0
            },
            {
                name = 'left',
                type = 'Slider',
                label = SV:T('Left Fade In (Second)'),
                format = '%1.2f',
                minValue = 0,
                maxValue = 1.5,
                interval = 0.01,
                default = 0.25
            },
            {
                name = 'right',
                type = 'Slider',
                label = SV:T('Right Fade Out (Second)'),
                format = '%1.2f',
                minValue = 0,
                maxValue = 1.5,
                interval = 0.01,
                default = 0.25
            },
            {
                name = 'simplify',
                type = 'Slider',
                label = SV:T('Parameter Curve Smoothness'),
                format = '%1.3f',
                minValue = 0,
                maxValue = 0.05,
                interval = 0.002,
                default = 0.002
            },
            {
                name = 'defaultErase',
                type = 'CheckBox',
                text = SV:T('Zero out Vibrato Depth in \'Note Properties\' panel'),
                default = true
            }
        }
    }
    
    local result = SV:showCustomDialog(form)
    if result.status then
        -- 计算点间隔
        local sampleBlick = math.floor(SV.QUARTER / (32 + 32 * (2 ^ result.answers.sampleRate - 1)))
        -- 获取音符
        local notegroup = SV:getMainEditor():getCurrentGroup():getTarget()
        local erase = result.answers.defaultErase
        local range = getNoteRange(erase)
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
            
            local simplifyValue = result.answers.simplify
            
            if result.answers.pitch then
                writeParam(notegroup, 'pitchDelta', start, stop, delta, sampleBlick, 45, simplifyValue)
            end
            if result.answers.tension then
                writeParam(notegroup, 'tension', start, stop, delta, sampleBlick, 0.15, simplifyValue)
            end
            if result.answers.dynamics then
                writeParam(notegroup, 'loudness', start, stop, delta, sampleBlick, 1.8, simplifyValue)
            end
            if result.answers.breath then
                writeParam(notegroup, 'breathiness', start, stop, delta, sampleBlick, 0.15, simplifyValue)
            end
            if result.answers.gender then
                writeParam(notegroup, 'gender', start, stop, delta, sampleBlick, 0.15, simplifyValue)
            end
            if result.answers.voice then
                writeParam(notegroup, 'voicing', start, stop, delta, sampleBlick, 0.10, simplifyValue)
            end
        end
    end
    
    SV:finish()

end
