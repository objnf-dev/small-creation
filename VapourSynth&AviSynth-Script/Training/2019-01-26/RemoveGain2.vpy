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
bd=vscore.lsmas.LWLibavSource(source="D:\\视频-音乐-图片\\VCB_test\\提交版本\\比较BDrip\\[YYDM-11FANS][Sword Art Online][PV][BDRIP][720P][X264-10bit_AAC][BE1B00B1].mp4", threads=2)

bd1=vscore.rgvs.RemoveGrain(clip=bd, mode=4)
bd2=vscore.rgvs.RemoveGrain(clip=bd, mode=11)

bd_comp=vscore.std.Interleave(clips=[bd1,bd2])

# Output
bd_comp.set_output()