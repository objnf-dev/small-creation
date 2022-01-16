# 加载必要库
# havsfunc 和 mvsfunc 需要手动到github下载
import vapoursynth as vs
import sys
import os
import havsfunc as haf
import mvsfunc as mvf

# 旧有调用方式弃用
vscore = vs.get_core(threads=6)   
vscore.max_cache_size = 4096
# Input
bd=vscore.lsmas.LWLibavSource(source="D:\\视频-音乐-图片\\VPR练习\\00000.m2ts", threads=2)
bd_crop=vscore.std.CropAbs(clip=bd, width=1440, height=1080, left=240)
# Output
bd_crop.set_output()