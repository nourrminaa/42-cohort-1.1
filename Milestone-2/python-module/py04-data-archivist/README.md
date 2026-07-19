_This project has been created as part of the 42 curriculum by nmina._

# PY04 — Data Archivist: Digital Preservation in the Cyber Archives

## Ex0 — Ancient Text Recovery

- `open()` returns a **file object**.
- Use `with open()` instead of bare `open()` — it auto-closes the file even if an exception occurs during reading.
- Mode strings beyond `'r'` (read):
  - `'w'` (Write) — creates a new file, or **overwrites** an existing one.
  - `'a'` (Append) — adds data to the end of an existing file, preserving current contents.
  - `'x'` (Exclusive Creation) — creates a new file; **fails with an error if the file already exists**.
- General syntax:

```python
with open("file_path", "mode", encoding="utf-8") as variable_name:
    ...
```

## Ex1 — Archive Creation

### `str.splitlines()`

Splits a string into a list of lines, breaking on line boundaries (`\n`, `\r\n`, `\r`, and a few rarer Unicode line separators), and **strips the line-ending characters** from each element.

```python
content = "line1\nline2\nline3\n"
content.splitlines()
# ['line1', 'line2', 'line3']
```

### vs. `str.split("\n")`

```python
content.split("\n")
# ['line1', 'line2', 'line3', '']
```

`split("\n")` leaves a **trailing empty string** if the file ends with a newline (which almost every text file does). `splitlines()` doesn't — that's why it's the right tool here: clean lines, no ghost empty entry to slap a stray `#` onto.

### `"\n".join(transformed_lines)`

Takes the list of `#`-suffixed lines and glues them into one string, inserting `"\n"` between each element. **No newline after the last item** — that's why the write step adds one manually:

```python
file.write(transformed + "\n")
```

### Overwrite warning

`open(filename, 'w')` truncates and overwrites if the file already exists — **no warning, no confirmation, no backup**.

**The butter basically:** `splitlines()` = split on any line ending and discard the ending itself; safer than `split("\n")` for file content because it won't leave a trailing empty element.

## Ex2 — Stream Management

Writing errors to `stderr` with a clear prefix instead of `stdout`:

```python
sys.stderr.write(f"[STDERR] Error opening file '{sys.argv[1]}': {e}")
```

- `sys.stderr.write(...)` sends the message to the **standard error stream**, not standard output — keeps error output separable from normal program output (e.g. when piping/redirecting: `python3 script.py 2> errors.log`).
- The `[STDERR]` prefix is just a visual marker in the message itself, not a stream property.

## The butter basically (overall)

- `with open(...)` > bare `open()` — guarantees closing on error.
- `'w'` overwrites silently, `'a'` appends, `'x'` refuses to clobber.
- `splitlines()` over `split("\n")` for line-based file processing — no trailing empty-string trap.
- Errors → `sys.stderr`, normal output → `sys.stdout`.

### AI Usage

AI (Claude) was used during this project for the following:

- **README writing**: Generating structured notes based on my understanding built during development

All code was written and understood by me. AI was not used to generate final solutions directly.
