# 网页版

模板册的网页版，发布在 <https://azusaaa.com/xcpc/>。章节 Markdown 通过 snippets 直接引用仓库根目录 `src/` 下的模板原件，不另存副本。

- 本地预览：在 `site/` 下运行 `uv run --locked mkdocs serve`。
- 发布：`site/` 或 `src/` 有改动并推送到 main 后，`.github/workflows/site.yml` 自动更新 Pages。
- 新增章节：在 `docs/` 写 Markdown，并在 `mkdocs.yml` 的 `nav` 登记。

只收录标记为 `@verified` 的模板。打印版 PDF 由仓库根目录的 `print.py` 生成，不在这里。
