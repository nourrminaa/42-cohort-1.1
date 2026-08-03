# this prevents "make" from confusing these names with files names
.PHONY: install run debug lint lint-strict clean build

# create the venv & install all dev dependencies into it
install:
	uv sync

# run the maze generator using the venv with config.txt as arg
run:
	uv run python3 a_maze_ing.py config.txt

# run the maze generator under pdb for debugging
debug:
	uv run python3 -m pdb a_maze_ing.py config.txt

lint:
	uv run python3 -m flake8 .
	uv run python3 -m mypy . --warn-return-any --warn-unused-ignores --ignore-missing-imports --disallow-untyped-defs --check-untyped-defs

lint-strict:
	uv run python3 -m flake8 .
	uv run python3 -m mypy . --strict

# remove all caches
clean:
	find . -type d -name "__pycache__" -exec rm -rf {} +
	find . -type d -name "*.egg-info" -exec rm -rf {} +
	rm -rf .mypy_cache .pytest_cache build dist

# build the mazegen wheel (mazegen-*.whl) from src/mazegen using pyproject.toml
build:
	uv build
