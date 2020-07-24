'''
BDRip画质对比脚本
version 1.3
2016/01/10
Change lsmas to ffms2 to avoid wrong frame rate number.
LittlePox@VCB-Studio
http://vcb-s.com/archives/4891
'''

import vapoursynth as vs
import sys
import mvsfunc as mvf

core = vs.get_core(threads=10)

core.max_cache_size = 8192

source = r"D:\视频-音乐-图片\[SweetSub&LoliHouse&VCB-Studio] Shelter [Ma10p_1080p]\[SweetSub&LoliHouse&VCB-Studio] Shelter [Ma10p_1080p][x265_flac].mkv" 
# 原盘文件名称,注意r"xxx"这个格式前面r不要省略，下同
name_1 = r"D:\VCB-Training\2-3\with-mbtree\default\output-default.h264" # 第一份BDRip名称
name_2 = r"D:\VCB-Training\2-3\without-mbtree\default\output-default2.h264" # 第二份BDRip名称
# 如果有多份BDRip，请自行添加name_3 = r"xxxx.mkv", name_4 = r"xxxx.mp4"...

src16 = core.ffms2.Source(source) # 读入原盘，无需改动，下同
rip_1 = core.ffms2.Source(name_1) # 读入第一份BDRip
rip_2 = core.ffms2.Source(name_2) # 读入第二份BDRip
# 如果有多份BDRip，请自行添加rip_3 = core.lsmas.LWLibavSource(name_3), rip_4...

# 以下段落检查是否有非1080p的BDRip，如果有，将它们用non-ringing Lanczos 4 拉升到1080p
if (rip_1.height!=1080) or (rip_1.width!=1920):
	rip_1 = core.fmtc.resample(rip_1,1920,1080,kernel="lanczos",taps=4).rgvs.Repair(core.fmtc.resample(rip_1,1920,1080,kernel="gauss",a1=100),1)

if (rip_2.height!=1080) or (rip_2.width!=1920):
	rip_2 = core.fmtc.resample(rip_2,1920,1080,kernel="lanczos",taps=4).rgvs.Repair(core.fmtc.resample(rip_2,1920,1080,kernel="gauss",a1=100),1)
# 如果有多份BDRip，请自行添加rip_3, rip_4...格式仿照上文。注意一段共有5个rip_x
  
# 以下段落为原盘和成品的画面添加文件名。如果你不需要这个功能，你可以删除以下整段
# src16 = core.text.Text(src16, source)
# src16 = core.text.ClipInfo(src16)
src16 = core.sub.Subtitle(src16, text=source, style="微软雅黑,15,&H00FFFFFF,&H00FFFFFF,&H00000000,&H00000000,0,0,0,0,100,100,1,0.00,3,1,0,7,15,0,15,134")
src16 = core.text.ClipInfo(src16, 1)
rip_1 = core.sub.Subtitle(rip_1, text=name_1, style="微软雅黑,15,&H00FFFFFF,&H00FFFFFF,&H00000000,&H00000000,0,0,0,0,100,100,1,0.00,3,1,0,7,15,0,15,134")
rip_1 = core.text.ClipInfo(rip_1, 1)
rip_2 = core.sub.Subtitle(rip_2, text=name_2, style="微软雅黑,15,&H00FFFFFF,&H00FFFFFF,&H00000000,&H00000000,0,0,0,0,100,100,1,0.00,3,1,0,7,15,0,15,134")
rip_2 = core.text.ClipInfo(rip_2, 1)
# 如果有多份BDRip，请自行按格式添加rip_3, rip_4...


src16 = mvf.ToRGB(src16,full=False,depth=8) # 转为RGB24，下同。不用改变。
rip_1 = mvf.ToRGB(rip_1,full=False,depth=8) 
rip_2 = mvf.ToRGB(rip_2,full=False,depth=8) 
# 如果有多份BDRip，请自行按格式添加rip_3, rip_4...

res = core.std.Interleave([src16, rip_1, rip_2]) # 如果有多份BDRip，请自行按格式在中括号中添加rip_3, rip_4...相邻两个需要用, 隔开

ScreenBitDepth = 6 # 把这里修改为你显示器的精度，比如6bit抖动屏建议改为6。

# 以下是根据显示器精度，决定是否补偿性加噪点。如果屏幕精度=8，则不增加任何噪点。
res = core.std.ShufflePlanes(res, [0,1,2], vs.YUV)
res = core.grain.Add(res,var=0.1993*(8-ScreenBitDepth),uvar=0.1993*(8-ScreenBitDepth),constant=True) 
res = core.std.ShufflePlanes(res, [0,1,2], vs.RGB)

res.set_output()
