import json

data = {"studentName":"Mike", "studentGender":False, "studentGrade":[87, 122, 54, 107, 144]}

print(json.dumps(data, sort_keys=True, indent=4, separators=(",", ": ")))

