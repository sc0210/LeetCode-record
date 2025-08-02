
# 🧠 Tcl 語法教學與筆記

## 📌 基本語法
```tcl
# 註解使用 #
set name "Sam"          ;# 設定變數
puts "Hello, $name"     ;# 印出訊息
```

## 📌 變數與資料型別
```tcl
set a 5
set b 10
set sum [expr $a + $b]
puts "總和為 $sum"
```

## 📌 字串操作
```tcl
set str "hello world"
string length $str           ;# 11
string toupper $str          ;# "HELLO WORLD"
string match "*world" $str   ;# 1 (true)
```

## 📌 清單（List）
```tcl
set mylist [list a b c d]
lindex $mylist 1           ;# b
llength $mylist            ;# 4
lrange $mylist 1 2         ;# b c
lappend mylist e           ;# 加入 e
```

## 📌 陣列（Array）
```tcl
array set colors {red #f00 green #0f0 blue #00f}
puts $colors(red)
array names colors         ;# 所有 keys
```

## 📌 流程控制
### if-elseif-else
```tcl
set x 10
if {$x > 0} {
    puts "positive"
} elseif {$x == 0} {
    puts "zero"
} else {
    puts "negative"
}
```

### switch
```tcl
switch $x {
  1 {puts "one"}
  2 {puts "two"}
  default {puts "other"}
}
```

## 📌 迴圈語法
```tcl
# for loop
for {set i 0} {$i < 5} {incr i} {
    puts $i
}

# while loop
set i 0
while {$i < 5} {
    puts $i
    incr i
}

# foreach loop
foreach item {a b c} {
    puts $item
}
```

## 📌 函式（Procedure）
```tcl
proc say_hello {name} {
    puts "Hello, $name!"
}
say_hello "Sam"
```

## 📌 檔案處理
```tcl
set f [open "myfile.txt" r]
set content [read $f]
close $f
puts $content
```

## 📌 錯誤處理
```tcl
if {[catch {expr 5 / 0} result]} {
    puts "Error: $result"
} else {
    puts "Result: $result"
}
```

---

# 📌 Tcl Cheat Sheet

| 主題        | 語法                            | 說明                   |
|-------------|----------------------------------|------------------------|
| 註解        | `#`                             | 單行註解              |
| 變數設定    | `set var value`                 | 宣告變數              |
| 字串長度    | `string length $str`            | 字串長度              |
| 清單操作    | `lindex`, `lappend`, `llength`  | 清單處理              |
| 條件判斷    | `if {cond} {...} elseif {...}`  | if 條件               |
| 迴圈        | `for`, `while`, `foreach`       | 控制流程              |
| 函式定義    | `proc name {args} {body}`       | 定義程序              |
| 檔案開關    | `open`, `read`, `close`         | 檔案存取              |
| 錯誤捕捉    | `catch {...} result`            | 錯誤處理              |
