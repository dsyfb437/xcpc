# Wiki Template

[在线阅读](https://azusaaa.com/wiki-template/) · [打印版 PDF](https://github.com/dsyfb437/wiki-template/releases/latest/download/wiki-template.pdf)

在 `docs/` 写 Markdown，在 `mkdocs.yml` 登记文章顺序。网站和书共用这份目录。示例使用平铺导航；上游转换器对部分嵌套导航会卡住。

- 本地预览：`uv run --locked mkdocs serve`。
- 网站发布：推送到 main，GitHub Actions 自动更新 Pages。
- 打印版发布：给要发布的提交打版本标签并推送，例如 `git tag v0.2.0 && git push origin v0.2.0`。成功后 PDF 出现在对应 Release。
- 本地生成 PDF：安装 Git、Node 20、Typst 0.15.1、Noto CJK 和 DejaVu 字体，在 Linux 运行 `bash scripts/print.sh`。首次构建需要联网。输出为 `dist/wiki-template.pdf`。

网页使用 Material for MkDocs，公式使用 MathJax（Apache-2.0）。`print/` 的排版文件改自 [OI-Wiki-export](https://github.com/OI-wiki/OI-Wiki-export/tree/960f4345100a1b8caaea8fb13f5b813ec46985d0)，许可见该目录。打印脚本在临时目录使用固定版本的上游转换器，不改写原稿。
