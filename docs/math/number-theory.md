本页用于演示网页和打印文档中的数学公式、列表、代码块和表格排版。

## 最大公约数

两个整数 $a,b$ 的最大公约数满足：

$$
\gcd(a,b)=\gcd(b,a\bmod b)
$$

当 $b=0$ 时，$\gcd(a,0)=|a|$。

```cpp
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return a < 0 ? -a : a;
}
```

## 整除与同余

| 概念 | 定义 |
| --- | --- |
| 整除 | 若存在整数 $k$ 使 $a=bk$，则 $b\mid a$ |
| 同余 | 若 $m\mid(a-b)$，则 $a\equiv b\pmod m$ |

后续可以继续添加素数筛、快速幂、扩展欧几里得等主题，网站和打印结构都不需要改变。
