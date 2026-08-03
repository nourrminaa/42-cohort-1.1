"""app package: top-level entry point for maze configuration parsing."""

from app.config_parser import parse_config
from app.errors import ConfigError
from app.writer import output_writer

__all__ = ["parse_config", "ConfigError", "output_writer"]
