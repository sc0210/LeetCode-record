import os

# 題號對應的額外資訊（你可持續擴充）
metadata = {
    "001": {"title": "Two Sum", "level": "Easy", "tags": ["Array", "Hash Table"]},
    "002": {
        "title": "Add Two Numbers",
        "level": "Medium",
        "tags": ["Linked List", "Math"],
    },
    "021": {
        "title": "Merge Two Sorted Lists",
        "level": "Easy",
        "tags": ["Linked List", "Recursion"],
    },
    "023": {
        "title": "Merge K Sorted Lists",
        "level": "Hard",
        "tags": ["Linked List", "Heap", "Divide and Conquer"],
    },
    "206": {"title": "Reverse Linked List", "level": "Easy", "tags": ["Linked List"]},
    # ... 可持續新增
}

# 搜尋所有 .c 檔案
files = sorted(f for f in os.listdir(".") if f.endswith(".c"))

with open("leetcode_summary.md", "w", encoding="utf-8") as f:
    f.write("# LeetCode C 解題總覽\n\n")
    f.write("| 題號 | 題目 | 難易度 | 主題 Tags | 原始碼 | 題目連結 |\n")
    f.write("|------|------|--------|------------|--------|-----------|\n")

    for filename in files:
        parts = filename.split("_", 1)
        if len(parts) != 2:
            continue  # skip non-standard files
        qid = parts[0]
        slug = parts[1].replace(".c", "")
        link = f"https://leetcode.com/problems/{slug.replace('_', '-')}/"

        if qid in metadata:
            title = metadata[qid]["title"]
            level = metadata[qid]["level"]
            tags = ", ".join(metadata[qid]["tags"])
        else:
            title = slug.replace("_", " ").title()
            level = "Unknown"
            tags = "?"

        f.write(
            f"| {qid} | {title} | {level} | {tags} | [{filename}]({filename}) | [🔗 題目]({link}) |\n"
        )
