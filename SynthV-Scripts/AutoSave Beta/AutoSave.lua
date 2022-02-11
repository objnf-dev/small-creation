-- 导入第三方包和系统包
local lunajson = require 'lunajson'
local io = require 'io'
local os = require 'os'

-- 全局变量
-- 默认配置文件位置，请直接修改config_file_ostype()
local config_file = ''
local autosave_dir_os = ''
local ostype = ''
local conf_content = {}
local running = false

-- 工程结构
local project_template = {
	-- 硬编码部分：工程版本，无API获取
	version = 120,
	time = {
		meter = {},
		tempo = {}
	},
	library = {},
	tracks = {},
	-- 硬编码部分：渲染设置，无API获取
	renderConfig = {
		destination = './',
		filename = '未命名',
		numChannels = 1,
		aspirationFormat = 'noAspiration',
		bitDepth = 16,
		sampleRate = 44100,
		exportMixDown = true
	}
	
}

-- 生成下一个自动保存的文件名
function filename_generate()
	-- 当前项目名
	local project_name = SV:getProject():getFileName()
	-- 分离出文件名
	if ostype == 'Windows' then
		project_name = string.match(project_name, '.*\\(.*)')
	else
		project_name = string.match(project_name, '.*/(.*)')
	end
	
	-- 如果文件名为空
	if project_name == nil then
		project_name = 'Unnamed'
	end
	
	-- 当前时间
	local current_time = os.date('%y%m%d_%H%M%S')
	-- 合成文件名
	local next_filename = project_name .. '-' .. current_time .. '.svp'
	return next_filename
end

-- 判断系统
function config_file_ostype()
	ostype = SV:getHostInfo().osType
	if ostype == 'Windows' then
		-- Windows系统下的配置文件位置
		config_file = os.getenv('USERPROFILE') .. '\\Documents\\Dreamtonics\\Synthesizer V Studio\\scripts\\autosave.cfg'
		autosave_dir_os = os.getenv('USERPROFILE') .. '\\Documents\\Dreamtonics\\Synthesizer V Studio\\autosave'
	elseif ostype == 'Linux' then
		-- Linux系统下的配置文件位置
		config_file = os.getenv('PWD') .. '/scripts/autosave.cfg'
		autosave_dir_os = os.getenv('PWD') .. '/autosave'
	else
		-- Mac系统下的配置文件位置
		config_file = os.getenv('HOME') .. 'Library/Application Support/Dreamtonics/Synthesizer V Studio/scripts/autosave.cfg'
		autosave_dir_os = os.getenv('HOME') .. 'Library/Application Support/Dreamtonics/Synthesizer V Studio/autosave'
	end
end

-- 读取配置文件
function readConfig()
	-- 读取文件内容
	local conf_file_ptr = io.open(config_file, 'a+')
	conf_file_ptr:seek('set')
	local conf_content_str = conf_file_ptr:read('*a')
	
	-- 如果文件内容为空
	if conf_content_str == "" then
		writeDefaultConfig(conf_file_ptr)
		conf_file_ptr:seek('set')
		conf_content_str = conf_file_ptr:read('*a')
	end
	
	-- JSON解码
	conf_content = lunajson.decode(conf_content_str)
	conf_file_ptr:close()
end

-- 配置文件不存在，写入默认配置
function writeDefaultConfig(conf_file_ptr)
	-- 默认配置
	local default_conf = {
		-- 自动保存时间间隔
		interval = 5,
		-- 自动保存的文件位置
		autosave_dir = autosave_dir_os
	}
	
	-- JSON编码
	local default_conf_json = lunajson.encode(default_conf)
	conf_file_ptr:write(default_conf_json)
end

-- 修改配置文件
function writeConfig()
	-- 清空文件内容
	local conf_file_ptr = io.open(config_file, 'w')
	-- 直接覆盖JSON
	conf_file_ptr:write(lunajson.encode(conf_content))
	-- 关闭文件
	conf_file_ptr:close()
end

-- 曲速标记
function project_tempo()
	-- 项目 - 时间轴 - 获取所有曲速标记
	local tempo_mark = SV:getProject():getTimeAxis():getAllTempoMarks()
	-- 删掉不需要的成员
	for key, _ in pairs(tempo_mark)
	do
		tempo_mark[key]['positionSeconds'] = nil
	end
	return tempo_mark
end

-- 拍号标记
function project_measure()
	-- 项目 - 时间轴 - 获取所有拍号标记
	local measure_mark = SV:getProject():getTimeAxis():getAllMeasureMarks()
	-- 格式修改
	for key, _ in pairs(measure_mark)
	do
		measure_mark[key]['positionBlick'] = nil
		measure_mark[key]['index'] = measure_mark[key]['position']
		measure_mark[key]['position'] = nil
	end
	return measure_mark
end

-- 参数点
function note_params(notegroup)
	-- 模板
	local param_array = {}
	-- 参数类型
	local param_type = {
		'pitchDelta',
		'vibratoEnv',
		'loudness',
		'tension',
		'breathiness',
		'voicing',
		'gender'
	}
	
	-- 对每一种参数类型都执行
	for _, val in pairs(param_type)
	do
		-- 获取参数对应的Automation
		local automate_data = notegroup:getParameter(val)
		-- 单一参数的模板
		param_array[val] = {
			-- 插值类型
			mode = automate_data:getInterpolationMethod(),
			-- 点数组
			points = {}
		}
		
		param_array[val]['points'][0] = 0
		-- 获得所有点的二维数组
		local all_points = automate_data:getAllPoints()
		
		-- 二维数组转一维数组
		for _, vec in pairs(all_points)
		do
			table.insert(param_array[val]['points'], vec[1])
			table.insert(param_array[val]['points'], vec[2])
			param_array[val]['points'][0] = param_array[val]['points'][0] + 2
		end
	end
	
	return param_array
end

-- 音符轨道公共属性
function note_attribute(attribute_obj)
	-- 音符属性模板
	local attribute_array = {}
	
	-- 属性列表
	local attribute_type = {
		'tF0Left',
		'tF0Right',
		'dF0Left',
		'dF0Right',
		'tF0VbrStart',
		'tF0VbrLeft',
		'tF0VbrRight',
		'dF0Vbr',
		'fF0Vbr',
	}
	-- 判断各属性值是否进行了修改
	for _, param in pairs(attribute_type)
	do
		if attribute_obj[param] ~= nil then
			attribute_array[param] = attribute_obj[param]
		end
	end
	
	return attribute_array
end

-- 音符信息
function note_info(notegroup)
	-- 单个音符组的音符信息模板
	local note_info_array = {
		-- 音符组名
		name = notegroup:getName(),
		-- 音符组UUID
		uuid = notegroup:getUUID(),
		-- 音符组的各参数信息
		parameters = note_params(notegroup)
	}
	
	-- 音符数组
	local note_array = {}
	-- 共有几个音符？
	local note_num = notegroup:getNumNotes()
	note_array[0] = 0
	-- 对每一个音符执行
	for j=1, note_num
	do
		-- 获取到音符对象
		local current_note = notegroup:getNote(j)
		note_array[0] = note_array[0] + 1
		-- 单个音符的模板
		note_array[j] = {
			-- 开始时间
			onset = current_note:getOnset(),
			-- 持续时间
			duration = current_note:getDuration(),
			-- 歌词
			lyrics = current_note:getLyrics(),
			-- 音素
			phonemes = current_note:getPhonemes(),
			-- 所在音高
			pitch = current_note:getPitch(),
			
			-- 音符属性
			attributes = {}
		}
			
		-- 音符属性
		local attribute_obj = current_note:getAttributes()
		note_array[j]['attributes'] = note_attribute(attribute_obj)
		
		-- 特有的音符属性
		local special_attribute = {
			'tF0Offset',
			'pF0Vbr',
			'tNoteOffset',
			'exprGroup'
		}
		for _, param in pairs(special_attribute)
		do
			if attribute_obj[param] ~= nil then
				note_array[j]['attributes'][param] = attribute_obj[param]
			end
		end
		
		-- array类型的属性
		if next(attribute_obj.dur) ~= nil then
			note_array[j]['attributes']['dur'] = attribute_obj['dur']
		end
		if next(attribute_obj.alt) ~= nil then
			note_array[j]['attributes']['alt'] = attribute_obj['alt']
		end
		
	end
		
	note_info_array['notes'] = note_array
	return note_info_array
end

-- 音符组引用
function notegroup_ref(current_ref)
	-- 音符组引用模板
	local ref_obj = {
		groupID = current_ref:getTarget():getUUID(),
		blickOffset = current_ref:getTimeOffset(),
		pitchOffset = current_ref:getPitchOffset(),
		isInstrumental = current_ref:isInstrumental(),
		
		-- 硬编码部分，伴奏文件名和位置，无API
		audio = {
			filename = '',
			duration = 0.0
		},
		
		-- 硬编码部分，声库设置，无API
		database = {
			name = '',
			language = '',
			languageOverride = '',
			phonesetOverride = '',
			backendType = ''
		},
			
		-- 硬编码部分，词典设置，无API
		dictionary = '',
		
		-- 音符属性
		voice = {}
	}
	
	local attribute_obj = current_ref:getVoice()
	-- 公有属性
	ref_obj['voice'] = note_attribute(attribute_obj)
	
	-- 特有属性
	local special_attribute = {
		'paramLoudness',
		'paramTension',
		'paramBreathiness',
		'paramGender'
	}
	for _, param in pairs(special_attribute)
	do
		if attribute_obj[param] ~= nil then
			ref_obj['voice'][param] = attribute_obj[param]
		end
	end
	
	return ref_obj
end

-- 轨道
function project_track()
	-- 轨道数组
	local track_array = {}
	-- 工程里共有几个轨道？
	local track_num = SV:getProject():getNumTracks()
	-- 对每条轨道都执行
	for i=1, track_num
	do
		-- 获取轨道对象
		local current_track = SV:getProject():getTrack(i)
		-- 单个轨道的模板
		track_array[i] = {
			-- 轨道名称
			name = current_track:getName(),
			-- 显示颜色
			dispColor = current_track:getDisplayColor(),
			-- 显示顺序
			dispOrder = current_track:getDisplayOrder(),
			-- 有没有启用渲染
			renderEnabled = current_track:isBounced(),
			
			-- 硬编码部分，混音器设置，无API
			mixer = {
				gainDecibel = 0.0,
				pan = 0.0,
				mute = false,
				solo = false,
				display = true
			}
		}
		
		-- 轨道里不在任何音符组里的内容
		local current_ref = current_track:getGroupReference(1)
		-- 这些音符所在的main音符组
		track_array[i]['mainGroup'] = note_info(current_ref:getTarget())
		-- main音符组的引用
		track_array[i]['mainRef'] = notegroup_ref(current_ref)
		
		-- 总音符组数，去掉main
		local track_group_num = current_track:getNumGroups() - 1
		-- 初始化数组
		track_array[i]['groups'] = {}
		track_array[i]['groups'][0] = 0
		-- 把每一个组都加入
		for j=1, track_group_num
		do
			track_array[i]['groups'][0] = track_array[i]['groups'][0] + 1
			track_array[i]['groups'][j] = notegroup_ref(current_track:getGroupReference(j + 1))
		end
	end
	
	return track_array
end

-- 库
function project_library()
	-- 库数组模板
	local library_array = {}
	library_array[0] = 0
	-- 找到库里的轨道数
	local notegroup_num = SV:getProject():getNumNoteGroupsInLibrary()
	-- 对库里的每个轨道执行
	for i=1, notegroup_num
	do
		library_array[0] = library_array[0] + 1
		-- 得到对应的音符组
		local current_group = SV:getProject():getNoteGroup(i)
		-- 获得该音符组的信息
		library_array[i] = note_info(current_group)
	end
	return library_array
end

-- 持续执行函数
function autosave_main()
	-- 创建工程文件
	local filename = filename_generate()
	local full_path = autosave_dir_os .. '/' .. filename
	local file_ptr = io.open(full_path, 'w')
	
	-- 组装工程文件
	local current_project = project_template
	-- 曲速
	current_project['time']['tempo'] = project_tempo()
	-- 拍号
	current_project['time']['meter'] = project_measure()
	-- 库
	current_project['library'] = project_library()
	-- 轨道
	current_project['tracks'] = project_track()
	
	-- 写文件
	file_ptr:write(lunajson.encode(current_project))
	file_ptr:write('\0')
	file_ptr:close()
	
	-- 预定下一次运行
	SV:setTimeout(conf_content['interval'] * 60 * 1000, autosave_main)
end

-- 插件描述
function getClientInfo()
	return {
		name = SV:T('AutoSave Preview'),
		author = 'ObjectNotFound <xml@live.com>',
		versionNumber = 1,
		minEditorVersion = 65540
	}
end

-- 本地化
function getTranslations(langCode)
	if langCode == 'zh-cn' then
		return {
			{'AutoSave Preview', '自动保存 测试版'},
			{'AutoSave Plugin Settings', '自动保存插件设置'},
			{'File save interval (minutes)', '保存时间间隔（分钟）'},
			{'File save location', '自动保存文件位置'},
			{'Filename demo (display only)', '自动保存文件名示例（修改无效）'}
		}
	end
end

function main()
	-- 加载
	config_file_ostype()
	readConfig()
	
	-- 设置窗口
	local form = {
		title = SV:T('AutoSave Plugin Settings'),
		message = 'ObjectNotFound <xml@live.com>',
		buttons = 'OkCancel',
		widgets = {
			{
				name = 'interval',
				type = 'Slider',
				label = SV:T('File save interval (minutes)'),
				format = '%0.1f',
				minValue = 1,
				maxValue = 60,
				interval = 0.5,
				default = conf_content['interval']
			},
			{
				name = 'autosave_dir',
				type = 'TextArea',
				label = SV:T('File save location'),
				default = conf_content['autosave_dir']
			},
			{
				name = 'filename_demo',
				type = 'TextArea',
				label = SV:T('Filename demo (display only)'),
				default = filename_generate()
			}
		}
	}
	-- 拿返回值
	local settings = SV:showCustomDialog(form)
	local triggerWriteConfig = false
	-- 确认才进行比较
	if settings.status == true then
		-- 需要修改配置文件吗？
		if conf_content['interval'] ~= settings.answers.interval then
			conf_content['interval'] = settings.answers.interval
			triggerWriteConfig = true
		end
		if conf_content['autosave_dir'] ~= settings.answers.autosave_dir then
			conf_content['autosave_dir'] = settings.answers.autosave_dir
			triggerWriteConfig = true
		end
	end
	
	-- 如果配置文件被修改，则重写配置文件
	if triggerWriteConfig == true then
		writeConfig()
	end
	
	if running == false then
		autosave_main()
		running = true
	end
end