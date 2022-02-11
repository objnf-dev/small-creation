function getClientInfo()
    return {
        name = SV:T('Lua environment'),
        author = 'ObjectNotFound <xml@live.com>',
        versionNumber = 2,
        minEditorVersion = 0x010004
    }
end

function getTranslations(langCode)
	if langCode == 'zh-cn' then
		return {
			{'Lua environment', 'Lua环境信息'}
		}
	end
end

function main()
    file = io.open('module.txt', 'w')
	-- path
	file:write('包导入路径：\n')
	file:write(package.path)
	file:write('\n\n')
	-- modules
	file:write('内置包：\n')
	for k, v in pairs(package.loaded) do
		file:write(k)
		file:write('\n')
	end
	file:write('\n')
	-- _G
	file:write('全局变量：\n')
	for k, v in pairs(_G) do
		file:write(k)
		file:write('\n')
	end
	file:write('\n')
	-- SV
	file:write('SV对象成员：\n')
	for k, v in pairs(_G['SV']) do
		file:write(k)
		file:write('\n')
	end
	file:close()
    SV:finish()

end
