# 编写者：xml@live.com 引用指明出处
# 试验脚本 仅为本人学习用

# 加载必要库
# havsfunc 和 mvsfunc 需要手动到github下载
import vapoursynth as vs
import sys
import os
import havsfunc as haf
import mvsfunc as mvf

# 旧有调用方式弃用，当不需要指定线程数时直接使用vs.core即可
vscore = vs.get_core(threads=12)
# 最大内存使用，单位MB
vscore.max_cache_size = 16384

# 指定输入
zj_bd=vscore.ffms2.Source(source="00000.m2ts")

# 进行卷积模糊（同一区块的9个像素点取平均，即低通滤波）
zj_blur=vscore.std.Convolution(clip=zj_bd, matrix=[1, 1, 1, 1, 1, 1, 1, 1, 1], planes=[0])

# 遮罩和边缘检测
# 黑帧
blackmask=vscore.std.BlankClip(clip=zj_bd, format=vs.GRAYS, color=0)
# 白帧
whitemask=vscore.std.BlankClip(clip=zj_bd, format=vs.GRAYS, color=1)
# 堆栈
mask=vscore.std.StackHorizontal(clips=[blackmask, whitemask])
# 给堆栈设置FPS
mask=vscore.std.AssumeFPS(clip=mask, src=zj_bd)
# 进行边缘检测
tcannymask=vscore.tcanny.TCanny(clip=zj_bd, sigma=1.2, t_h=6, t_l=4, mode=1, op=2, planes=[0])
# 转换边缘检测后信息为灰度
tsuffle=vscore.std.ShufflePlanes(clips=[tcannymask], planes=[0], colorfamily=vs.GRAY)

# 膨胀再紧缩填充线条空隙
tmax=vscore.std.Maximum(clip=tsuffle)
tmin=vscore.std.Minimum(clip=tmax)

# 设置LUT比较列表
reslut=[]
for i in range(256):
	if i<= 100:
		reslut.append(0)
	elif i<=240:
		reslut.append(int((i-100)*(255/140)))
	else:
		reslut.append(255)
# 应用LUT
maskres=vscore.std.Lut(clip=tmin, planes=[0], lut=reslut)

# 获取差异部分，低通滤波前-低通滤波后=高频部分
zj_highrange=vscore.std.MakeDiff(clipa=zj_bd, clipb=zj_blur, planes=[0])

# 降噪
# 高频区域降噪
zj_denoise=mvf.BM3D(zj_highrange, sigma=[6, 6, 6], radius1=0)
# 低频区域轻微降噪
zj_blur=mvf.BM3D(zj_blur, sigma=[1, 1, 1], radius1=0)
# 确认降噪，低通滤波后+高频部分=完整
zj_merge1=vscore.std.MergeDiff(clipa=zj_blur, clipb=zj_denoise, planes=[0])

# 整合降噪后的画面和降噪前的线条
zj_merge2=vscore.std.MaskedMerge(clipa=zj_merge1, clipb=zj_bd, mask=maskres)

# 锐化
# 完整+高频部分=锐化
zj_blur2=vscore.std.Convolution(clip=zj_merge2, matrix=[1, 1, 1, 1, 1, 1, 1, 1, 1], planes=[0])
zj_highrange2=vscore.std.MakeDiff(clipa=zj_merge2, clipb=zj_blur2, planes=[0])
zj_merge=vscore.std.MergeDiff(clipa=zj_merge2, clipb=zj_highrange2, planes=[0])

# 比较（通过交叉排列帧进行多画面比较）
# output=vscore.std.Interleave([zj_bd,zj_denoise])

# 输出，有输出才能预览
zj_merge.set_output()