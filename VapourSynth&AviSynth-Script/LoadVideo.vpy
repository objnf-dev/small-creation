# 加载必要库
import vapoursynth as vs
# 得到 vapoursynth 核心，通过此核心载入滤镜
vscore = vs.get_core(threads=10)

# 文件位置字符串（注意去除转义）
pos = r"D:\视频-音乐-图片\[BDMV][20190130][Sword Art Online Alicization][Vol.01]\BD\BDMV\STREAM\00002.m2ts"
# 通过ffms2或者lsmas读取视频
source = vscore.ffms2.Source(pos, format=vs.YUV420P8)

# 输出节点，数据可以由VSPipe或Editor读取
source.set_output()
