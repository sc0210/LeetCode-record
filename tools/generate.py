import os
import requests
import json
from pathlib import Path

SCRIPT_DIR = Path(__file__).resolve().parent  # tools/
SOURCE_DIR = SCRIPT_DIR.parent / "source"  # ../source

# 列出 source/ 下所有 .c 檔
files = sorted(p.name for p in SOURCE_DIR.glob("*.c"))

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


def fetch_meta(slug: str):
    url = "https://leetcode.com/graphql"
    query = """
    query getQuestion($titleSlug: String!) {
      question(titleSlug: $titleSlug) {
        title
        difficulty
        topicTags { name }
      }
    }"""
    variables = {"titleSlug": slug}

    with requests.Session() as s:
        # 先 GET 任何頁面拿 cookie (不一定有 csrftoken)
        s.get("https://leetcode.com")

        # 安全取得 csrftoken
        csrftoken = s.cookies.get("csrftoken", "")

        headers = {
            "Content-Type": "application/json",
            "Referer": f"https://leetcode.com/problems/{slug}/",
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
            "AppleWebKit/537.36 (KHTML, like Gecko) "
            "Chrome/114.0.0.0 Safari/537.36",
        }

        if csrftoken:
            headers["x-csrftoken"] = csrftoken

        payload = {"query": query, "variables": variables}
        r = s.post(url, headers=headers, data=json.dumps(payload))
        r.raise_for_status()  # 如果回傳錯誤，會丟例外
        data = r.json().get("data", {}).get("question", None)

        if not data:
            raise ValueError(f"找不到問題資料，slug={slug}")

    return {
        "title": data["title"],
        "difficulty": data["difficulty"],
        "tags": [t["name"] for t in data["topicTags"]],
    }


md_path = SCRIPT_DIR / "leetcode_summary.md"
with md_path.open("w", encoding="utf-8") as f:
    f.write("# LeetCode C 解題總覽\n\n")
    f.write("| 題號 | 題目 | 難易度 | 主題 Tags | 原始碼 | 題目連結 |\n")
    f.write("|------|------|--------|------------|--------|-----------|\n")

    for filename in files:
        parts = filename.split("_", 1)
        if len(parts) != 2:
            continue
        qid = parts[0]
        slug = parts[1].replace(".c", "").replace("_", "-").lower()
        link = f"https://leetcode.com/problems/{slug}/"

        if qid in metadata:
            title = metadata[qid]["title"]
            level = metadata[qid]["level"]
            tags = ", ".join(metadata[qid]["tags"])
        else:
            obj = fetch_meta(slug)
            title = obj["title"]
            level = obj["difficulty"]
            tags = ", ".join(obj["tags"])

        f.write(
            f"| {qid} | {title} | {level} | {tags} | "
            f"[{filename}](../source/{filename}) | [🔗 題目]({link}) |\n"
        )
