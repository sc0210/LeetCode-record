#!/usr/bin/env python3
# tools/gen_md.py
import json
from pathlib import Path
import requests
from collections import defaultdict
from copy import deepcopy

SCRIPT_DIR = Path(__file__).resolve().parent  # tools/
SOURCE_DIR = SCRIPT_DIR.parent / "source"  # ../source
META_PATH = SCRIPT_DIR / "metadata.json"  # tools/metadata.json
QID_WIDTH = 4  # how many digits to show in the table

# ──────────────────────────────────────────────────────────────
# 1. 讀取（或初始化）metadata.json
# ──────────────────────────────────────────────────────────────
if META_PATH.exists():
    with META_PATH.open(encoding="utf-8") as jf:
        metadata: dict[str, dict] = json.load(jf)
else:
    # ★ 第一次執行：可以留空 {} 也可以塞幾筆範例
    metadata = {
        "1": {  # ← 這些預塞的 key 也用「無前導零」型式
            "title": "Two Sum",
            "level": "Easy",
            "tags": ["Array", "Hash Table"],
        },
        "2": {
            "title": "Add Two Numbers",
            "level": "Medium",
            "tags": ["Linked List", "Math"],
        },
    }
    META_PATH.write_text(json.dumps(metadata, ensure_ascii=False, indent=2))

# 1‑B. 把舊檔裡「有前導零」的 key 清理掉
original_metadata = deepcopy(metadata)
metadata = {k.lstrip("0") or "0": v for k, v in metadata.items()}


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
                "Chrome/137.0.0.0 Safari/537.36"
            ),
        }
        if csrftoken:
            headers["x-csrftoken"] = csrftoken

        payload = {"query": query, "variables": variables}
        r = s.post(url, headers=headers, data=json.dumps(payload, ensure_ascii=False))
        r.raise_for_status()
        data = r.json().get("data", {}).get("question")

    if not data:
        print(f"⚠️ 找不到題目資料，slug={slug}，略過 fetch")
        return None

    return {
        "title": data["title"],
        "difficulty": data["difficulty"],
        "tags": [t["name"] for t in data["topicTags"]],
    }


# ──────────────────────────────────────────────────────────────
# 3. 掃描 source/ 產生 README + 動態更新 metadata
# ──────────────────────────────────────────────────────────────
files = sorted(p.name for p in SOURCE_DIR.glob("*.*"))

qid_files: dict[str, list[tuple[str, str]]] = defaultdict(
    list
)  # qid -> [(lang, filename)]
for filename in files:
    if "_" not in filename:  # 不符合「{qid}_{slug}.ext」就跳過
        continue
    qid_raw, _ = filename.split("_", 1)
    qid = qid_raw.lstrip("0") or "0"  # 轉成「無前導零」
    ext = filename.split(".")[-1].lower()
    language = (
        "C"
        if ext == "c"
        else "C++" if ext in ("cpp", "cc") else "Python" if ext == "py" else ext.upper()
    )
    qid_files[qid].append((language, filename))

md_path = SCRIPT_DIR / "leetcode_summary.md"
changed = metadata != original_metadata  # 若 key 清理就應該重寫 JSON

with md_path.open("w", encoding="utf-8") as f_md:
    # f_md.write("# LeetCode 解題總覽\n\n")
    f_md.write("| Number | Title | Difficulty | Tags | Solution | Link |\n")
    f_md.write("|-------:|-------|------------|------|----------|------|\n")

    for qid in sorted(qid_files.keys(), key=lambda s: int(s)):
        qid_display = qid.zfill(QID_WIDTH)  # 0001、0345…
        first_filename = qid_files[qid][0][1]
        slug = Path(first_filename).stem.split("_", 1)[1].replace("_", "-").lower()
        link = f"https://leetcode.com/problems/{slug}/"

        if qid not in metadata:
            print(f"📥 fetch meta for Q{qid} ({slug})")
            meta = fetch_meta(slug)
            if meta:
                metadata[qid] = {
                    "title": meta["title"],
                    "level": meta["difficulty"],
                    "tags": meta["tags"],
                }
            else:
                # fallback metadata
                metadata[qid] = {
                    "title": "(unavailable)",
                    "level": "Unknown",
                    "tags": [],
                }
            changed = True

        entry = metadata[qid]
        title = entry["title"]
        level = entry["level"]
        tags = ", ".join(entry["tags"])
        sources = "<br>".join(
            f"[{lang}](/source/{fname})" for lang, fname in qid_files[qid]
        )

        f_md.write(
            f"| {qid_display} | {title} | {level} | {tags} | {sources} | [🔗]({link}) |\n"
        )

# ──────────────────────────────────────────────────────────────
# 4. 若有變動就把 metadata.json 寫回
# ──────────────────────────────────────────────────────────────
if changed:
    with META_PATH.open("w", encoding="utf-8") as jf:
        json.dump(metadata, jf, ensure_ascii=False, indent=2)
    print(f"⚙️  metadata.json 已更新，共 {len(metadata)} 題。")
else:
    print("✅  metadata.json 無需更新。")
