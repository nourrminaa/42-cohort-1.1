"""Centralized custom exceptions used across this package."""


class MazeError(Exception):
    def __init__(self, message: str):
        super().__init__(message)
