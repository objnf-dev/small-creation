import vapoursynth as vs
core = vs.get_core(threads = 10)

src = core.ffms2.Source(r"D:\视频-音乐-图片\bilibili2019拜年祭1080p+\【哔哩哔哩2019拜年祭】1-珠.flv",format=vs.YUV420P8)
res1 = core.rgvs.RemoveGrain(src, 20).rgvs.RemoveGrain(20).rgvs.RemoveGrain(20)

res2 = core.std.Median(src, [0])

res2.set_output()