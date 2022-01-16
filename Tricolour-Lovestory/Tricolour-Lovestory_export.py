import getopt, sys, codecs

inputFileName = ""
opts, _ = getopt.getopt(sys.argv[1:], "-i:", ["input="])
for optname, optval in opts:
    if optname in ("-i", "--input"):
        inputFileName = optval

inputFile = codecs.open(inputFileName, "r", encoding="utf_16_le")
outputFile = codecs.open(inputFileName + ".txt", "x", encoding="utf_8")

templine = {"line1":"", "line2":"", "line3":""}
msgOn = False
while True:
    line = inputFile.readline()
    pairBrk = True
    if not line:
        break
    templine["line1"] = templine["line2"]
    templine["line2"] = line
    if "============================================" in line:
        outputFile.writelines(templine["line1"][1:])
        outputFile.writelines(templine["line2"][1:])
    elif "[msgon]" in line:
        msgOn = True
        continue
    elif "[msgoff]" in line:
        msgOn = False
        continue
    elif msgOn and line[0] != "[":
        if line[0] == ";":
            templine["line2"] = "\n// " + templine["line2"][1:] + "\n"
        for i in templine["line2"]:
            if i == "[":
                pairBrk = False
                continue
            elif i == "]":
                pairBrk = True
                continue
            if pairBrk:
                templine["line3"] += i
        outputFile.writelines(templine["line3"])
        templine["line3"] = ""
