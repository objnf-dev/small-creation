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

bd1=vscore.std.Trim(clip=bd, first=0, length=1000)
bd2=vscore.std.Trim(clip=bd, first=1001, last=2000)

bd1_resize=vscore.resize.Spline36(clip=bd1, width=1280, height=720)

bd_beforecrop=vscore.std.Splice(clips=[bd1_resize, bd2], mismatch=True)

bd_crop=vscore.std.CropAbs(clip=bd_beforecrop, width=640, height=480)

# Output
bd_crop.set_output()