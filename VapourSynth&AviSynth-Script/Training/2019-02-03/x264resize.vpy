import vapoursynth as vs
import havsfunc as haf
import mvsfunc as mvf

vscore = vs.get_core(threads=10)
origin = vscore.ffms2.Source("D:\\视频-音乐-图片\\[SweetSub&LoliHouse&VCB-Studio] Shelter [Ma10p_1080p]\\[SweetSub&LoliHouse&VCB-Studio] Shelter [Ma10p_1080p][x265_flac].mkv",format=vs.YUV420P10)

resized = vscore.resize.Spline36(origin, width=1280, height=720, format=vs.YUV420P10)

resized.set_output()