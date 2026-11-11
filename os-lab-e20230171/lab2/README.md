# Lab 2 — Linux Navigation and File Management: individual report

- Student name/ID: RENG IENGSENG / e20230171
- Ubuntu username: gic-reng-iengseng
- My values (`oslab values lab2`): file1 = cash flow.txt, file2 = budget 2026.txt, owner = Sales, reader = Support, third = Engineering
- Files: `evidence/paths.txt`, `evidence/tree.txt`, `evidence/checkpoint.txt`

## What I Did

| Step | My command | Current folder when I ran it |
|---|---|---|
| Move the first file (relative destination) | `mv -- "cash flow.txt" ../reports/` | `~/oslab-work/lab2/incoming` |
| Move the second file (absolute paths) | `mv -- "$OSLAB_WORKSPACE/lab2/incoming/budget 2026.txt" "$OSLAB_WORKSPACE/lab2/reports/budget 2026.txt"` | `~/oslab-work/lab2` |
| Read the report from my reader department (relative path) | `cat -- "../Sales/cash flow.txt"` | `~/oslab-work/lab2/TechCorp/Support` |
| The path error I made on purpose, and its message | `cat "reports/cash flow.txt"` -> `cat: 'reports/cash flow.txt': No such file or directory` | `~/oslab-work/lab2/TechCorp/Support` |
| The relative path that fixed it | `../../reports/cash flow.txt` | `~/oslab-work/lab2/TechCorp/Support` |

## Explanation

Even when a file name is spelled correctly, a relative path is resolved starting from the current working directory (`pwd`), so running `cat "reports/cash flow.txt"` from `TechCorp/Support` fails with "No such file or directory" because `reports/` is two directories up (`../../reports/cash flow.txt`), and unquoted spaces in a file name also cause the shell to split it into multiple missing paths. Using `mv -- "cash flow.txt" ../reports/` moved the file out of `incoming/` into `reports/` leaving only one copy. In contrast, using `cp -- "reports/cash flow.txt" "reports/budget 2026.txt" "TechCorp/Sales/"` created independent copies in `TechCorp/Sales/` while keeping the originals in `reports/`.

## What My Tests Do Not Prove

`ls` only confirms that a file name exists in a folder and does not verify its contents. `cmp` proves that two files (such as `reports/cash flow.txt` and `TechCorp/Sales/cash flow.txt`) have identical bytes, but it does not prove which copy is the original or verify the overall directory layout without checking the tree (`find`/`tree.txt`).

## Plus / Challenge (only if you did them)

Not attempted.

## AI Note (optional)

Suggested quoting paths with spaces (such as `Fix: "../../reports/cash flow.txt"`) so the shell keeps the filename as one argument, verified with `cat "../../reports/cash flow.txt"`.
