[下载最新打印版 PDF](https://github.com/dsyfb437/wiki-template/releases/latest/download/wiki-template.pdf)

本模板以 OI Wiki 的信息架构为参考，使用 MkDocs 生成网页，并把同一份 Markdown 交给 Typst 生成 A4 文档。

## 模板能力

| 能力 | 网页 | 打印 |
| --- | --- | --- |
| 多级文章结构 | 支持 | 由导航生成章节 |
| 代码高亮 | 支持 | 支持 |
| 数学公式 | MathJax | Typst 原生公式 |
| 站内搜索 | 支持 | 自动生成目录 |
| 浅色与深色模式 | 支持 | 不适用 |

## 构建流程

```text
Markdown 内容
    ├─ MkDocs → 静态网页
    └─ remark-typst → Typst → PDF
```

网页预览命令：

```bash
uv run mkdocs serve -f mkdocs.yml -a 0.0.0.0:8001
```

## 数学示例

二分查找的时间复杂度是 $O(\log n)$。完整排序的常见复杂度是：

$$
T(n) = O(n \log n)
$$

模板保留的是内容结构和排版方法，站点名称、作者、颜色和标志都可以替换。
