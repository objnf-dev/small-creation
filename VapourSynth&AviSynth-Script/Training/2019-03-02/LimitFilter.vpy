# 加载Python库
import vapoursynth as vs
import mvsfunc as mvf

# 设置核心
core = vs.get_core(threads = 10)

#读入视频
src = core.ffms2.Source(r"D:\视频-音乐-图片\压制练习视频\[SweetSub&LoliHouse&VCB-Studio] Shelter [Ma10p_1080p][x265_flac].mkv",format=vs.YUV420P10)

# 通过 RemoveGrain mode=11 做平滑
res1 = core.rgvs.RemoveGrain(src, 11)

# MakeDiff 对两个平面做差
diff = core.std.MakeDiff(src, res1)

# 合并
merge = core.std.MergeDiff(src, diff)

# 对合并操作进行限制
final = mvf.LimitFilter(diff, src, thr=3.0, elast=4.0)

# 与源进行间隔插入，方便比较
final = core.std.Interleave([src, res1, final])

# 做输出
final.set_output()