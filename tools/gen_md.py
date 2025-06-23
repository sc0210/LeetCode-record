#!/usr/bin/env python3
# tools/gen_md.py
import json
from pathlib import Path
import requests
from collections import defaultdict

SCRIPT_DIR = Path(__file__).resolve().parent  # tools/
SOURCE_DIR = SCRIPT_DIR.parent / "source"  # ../source
META_PATH = SCRIPT_DIR / "metadata.json"  # tools/metadata.json

# ──────────────────────────────────────────────────────────────
# 1. 讀取（或初始化）metadata.json
# ──────────────────────────────────────────────────────────────
if META_PATH.exists():
    with META_PATH.open(encoding="utf-8") as jf:
        metadata: dict[str, dict] = json.load(jf)
else:
    # ★ 第一次執行：先塞一點範例題目，也可以留空 {}
    metadata = {
        "001": {"title": "Two Sum", "level": "Easy", "tags": ["Array", "Hash Table"]},
        "002": {
            "title": "Add Two Numbers",
            "level": "Medium",
            "tags": ["Linked List", "Math"],
        },
    }
    META_PATH.write_text(json.dumps(metadata, ensure_ascii=False, indent=2))


# ──────────────────────────────────────────────────────────────
# 2. 工具：從 LeetCode GraphQL 抓題目 meta
# ──────────────────────────────────────────────────────────────
def fetch_meta(slug: str) -> dict[str, str | list[str]]:
    """回傳 {title, difficulty, tags(list[str])}；若失敗會丟例外"""
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
        s.get("https://leetcode.com")  # 取 cookie
        csrftoken = s.cookies.get("csrftoken", "")

        headers = {
            "Content-Type": "application/json",
            "Referer": f"https://leetcode.com/problems/{slug}/",
            "User-Agent": (
                "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                "AppleWebKit/537.36 (KHTML, like Gecko) "
                "Chrome/114.0.0.0 Safari/537.36"
            ),
        }
        if csrftoken:
            headers["x-csrftoken"] = csrftoken

        payload = {"query": query, "variables": variables}
        r = s.post(url, headers=headers, data=json.dumps(payload, ensure_ascii=False))
        r.raise_for_status()
        data = r.json()["data"]["question"]

    if not data:
        raise ValueError(f"找不到題目資料，slug={slug}")

    return {
        "title": data["title"],
        "difficulty": data["difficulty"],
        "tags": [t["name"] for t in data["topicTags"]],
    }


# ──────────────────────────────────────────────────────────────
# 3. 掃描 source/ 產生 README + 動態更新 metadata
# ──────────────────────────────────────────────────────────────
# --- 在掃描 source/ 產生 README 之前 ---
files = sorted(p.name for p in SOURCE_DIR.glob("*.*"))

# 先建立題號到檔案語言清單的映射

qid_files = defaultdict(list)  # qid -> list of (language, filename)
md_path = SCRIPT_DIR / "leetcode_summary.md"

changed = False  # 用來判斷 metadata 有沒有被擴充

for filename in files:
    parts = filename.split("_", 1)
    if len(parts) != 2:
        continue
    qid = parts[0]

    ext = filename.split(".")[-1].lower()
    if ext == "c":
        language = "C"
    elif ext in ("cpp", "cc"):
        language = "C++"
    elif ext == "py":
        language = "Python"
    else:
        language = ext.upper()  # 其他語言可自行擴充

    qid_files[qid].append((language, filename))

# --- 生成 Markdown ---
with md_path.open("w", encoding="utf-8") as f_md:
    f_md.write("# LeetCode 解題總覽\n\n")
    f_md.write("| Number | Tilte | Difficulty | Tags | Solution | Links |\n")
    f_md.write("|------|------|--------|-----------|--------|-----------|\n")

    # 用所有題號鍵排序（可用 qid_files.keys()）
    for qid in sorted(qid_files.keys()):
        # 只要取第一個檔名推 slug 即可
        first_filename = qid_files[qid][0][1]
        slug = (
            first_filename.split("_", 1)[1]
            .replace(".c", "")
            .replace(".cpp", "")
            .replace(".cc", "")
            .replace(".py", "")
            .replace("_", "-")
            .lower()
        )
        link = f"https://leetcode.com/problems/{slug}/"

        if qid not in metadata:
            obj = fetch_meta(slug)
            metadata[qid] = {
                "title": obj["title"],
                "level": obj["difficulty"],
                "tags": obj["tags"],
            }
            changed = True

        entry = metadata[qid]
        title = entry["title"]
        level = entry["level"]
        tags = ", ".join(entry["tags"])

        # 產生原始碼欄位多語言超連結
        source_links = []
        for lang, fname in qid_files[qid]:
            source_links.append(f"[{lang}](/source/{fname})")
        source_md = "<br>".join(source_links)  # Markdown 表格中用 <br> 換行

        f_md.write(
            f"| {qid} | {title} | {level} | {tags} | {source_md} | [🔗]({link}) |\n"
        )
# ──────────────────────────────────────────────────────────────
# 4. 若有變動就把 metadata 寫回 JSON
# ──────────────────────────────────────────────────────────────
if changed:
    with META_PATH.open("w", encoding="utf-8") as jf:
        json.dump(metadata, jf, ensure_ascii=False, indent=2)
    print(f"⚙️  metadata.json 已更新，共 {len(metadata)} 題。")
else:
    print("✅  metadata.json 無需更新。")
