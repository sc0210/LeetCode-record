
# 🧠 Bash 語法教學與筆記

## 📌 變數宣告與使用
```bash
# 宣告變數（= 兩邊不能有空格）
name="Sam"

# 使用變數
echo "Hello, $name"
```

## 📌 字串處理
```bash
str="HelloWorld"
echo "${str:0:5}"   # Hello
echo "${#str}"      # 長度：10
```

## 📌 條件判斷 if-else
```bash
if [ $age -gt 18 ]; then
  echo "Adult"
else
  echo "Minor"
fi
```

### 常用條件運算子：

| 說明       | 語法             |
|------------|------------------|
| 等於       | -eq / =          |
| 不等於     | -ne / !=         |
| 大於       | -gt              |
| 小於       | -lt              |
| 字串比較   | =, !=, -z, -n     |

## 📌 迴圈 for / while
```bash
# for 迴圈
for i in 1 2 3; do
  echo "Number $i"
done

# while 迴圈
count=1
while [ $count -le 5 ]; do
  echo $count
  ((count++))
done
```

## 📌 函式定義與使用
```bash
greet() {
  echo "Hello $1"
}

greet "Sam"
```

## 📌 陣列處理
```bash
arr=("apple" "banana" "cherry")
echo ${arr[1]}        # banana
echo ${#arr[@]}       # 3
for item in "${arr[@]}"; do
  echo "$item"
done
```

## 📌 Bash Cheat Sheet

| 類別        | 語法                          | 說明                     |
|-------------|-------------------------------|--------------------------|
| 註解        | #                             | 單行註解                |
| 變數        | name=value                    | 宣告變數                |
| 輸出        | echo, printf                  | 顯示文字                |
| 條件判斷    | if [ $x -eq 1 ]; then ...     | 數字或字串條件         |
| 迴圈        | for, while                    | 遍歷或條件式            |
| 函式        | function fname() {}           | 自訂函式                |
| 陣列        | arr=(a b c)                   | 陣列處理                |
| 命令替換    | var=`ls` 或 $(ls)             | 將命令結果存變數        |
| 檔案判斷    | -f, -d, -e                    | 判斷檔案/目錄存在       |
| 錯誤處理    | if command; then ...          | 判斷命令是否成功        |


---

# 🔧 Bash 進階語法筆記

## 📌 參數與位置變數
```bash
echo "Script name: $0"
echo "第一個參數: $1"
echo "參數個數: $#"
echo "所有參數: $@"
```

## 📌 命令替換與流程控制
```bash
today=$(date +%Y-%m-%d)
echo "Today is $today"

# 使用 && 和 ||
mkdir new_dir && echo "Created" || echo "Failed"
```

## 📌 檔案與目錄判斷
```bash
if [ -f "file.txt" ]; then
  echo "file exists"
fi

if [ -d "/etc" ]; then
  echo "directory exists"
fi
```

## 📌 標準輸入輸出與重導
```bash
command > out.txt        # 標準輸出導向到檔案（覆蓋）
command >> out.txt       # 標準輸出導向到檔案（附加）
command 2> err.txt       # 錯誤輸出導向到檔案
command &> all.txt       # 同時導向 stdout 和 stderr
```

## 📌 管線與 tee
```bash
ls -l | grep ".sh" | tee result.txt
```

## 📌 trap 與中斷處理
```bash
trap "echo Ctrl+C 被偵測"; INT

while true; do
  sleep 1
done
```

## 📌 awk：行為單位處理
```bash
# 印出第一欄
awk '{print $1}' file.txt

# 使用條件式
awk '$3 > 100 { print $1, $3 }' file.txt
```

## 📌 sed：文字替換與刪除
```bash
sed 's/old/new/' file.txt     # 只替換第一個
sed 's/old/new/g' file.txt    # 全部替換
sed '/^#/d' file.txt          # 刪除註解行
```

## 📌 bash script 中的 case 語法
```bash
case $1 in
  start)
    echo "Starting..."
    ;;
  stop)
    echo "Stopping..."
    ;;
  *)
    echo "Unknown command"
    ;;
esac
```

## 📌 常見系統與工作管理指令
| 指令         | 說明 |
|--------------|------|
| `top`        | 顯示系統資源使用 |
| `ps aux`     | 顯示所有進程     |
| `kill PID`   | 終止進程         |
| `jobs`       | 查看背景任務     |
| `fg` / `bg`  | 前景或背景執行任務 |
| `nohup cmd &`| 永久執行背景程式 |

