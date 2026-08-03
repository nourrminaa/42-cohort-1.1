from abc import ABC, abstractmethod
from typing import Optional


class HealCapability(ABC):
    @abstractmethod
    def heal(self, target: Optional["HealCapability"] = None) -> str:
        ...


class TransformCapability(ABC):
    def __init__(self) -> None:
        self.transformed = False

    @abstractmethod
    def transform(self) -> str:
        ...

    @abstractmethod
    def revert(self) -> str:
        ...
