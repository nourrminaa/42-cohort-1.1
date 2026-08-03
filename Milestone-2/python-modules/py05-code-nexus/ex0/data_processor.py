from abc import ABC, abstractmethod
from typing import Any


class DataProcessor(ABC):
    def __init__(self) -> None:
        self._storage: list[str] = []
        self._rank: int = 0

    @abstractmethod
    def validate(self, data: Any) -> bool:
        pass

    @abstractmethod
    def ingest(self, data: Any) -> None:
        pass

    def output(self) -> tuple[int, str]:
        rank = self._rank
        value = self._storage[0]
        new_storage = []
        for i in range(1, len(self._storage)):
            new_storage.append(self._storage[i])
        self._storage = new_storage
        self._rank += 1
        return (rank, value)


class NumericProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, (int, float)):
            return True
        if isinstance(data, list):
            for item in data:
                if isinstance(item, (int, float)) is False:
                    return False
            return True
        return False

    def ingest(self, data: int | float | list[int | float]) -> None:
        if self.validate(data) is False:
            raise ValueError("Improper numeric data")
        if isinstance(data, list):
            for item in data:
                self._storage.append(str(item))
        else:
            self._storage += [str(data)]


class TextProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, str):
            return True
        if isinstance(data, list):
            for item in data:
                if isinstance(item, str) is False:
                    return False
            return True
        return False

    def ingest(self, data: str | list[str]) -> None:
        if self.validate(data) is False:
            raise ValueError("Improper text data")
        if isinstance(data, list):
            self._storage += data
        else:
            self._storage += [data]


class LogProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        if isinstance(data, dict):
            for k, v in data.items():
                if (isinstance(k, str) and isinstance(v, str)) is False:
                    return False
            return True
        if isinstance(data, list):
            for item in data:
                if self.validate(item) is False:
                    return False
            return True
        return False

    def ingest(self, data: dict[str, str] | list[dict[str, str]]) -> None:
        if self.validate(data) is False:
            raise ValueError("Improper log data")
        if isinstance(data, list):
            entries = data
        else:
            entries = [data]
        for entry in entries:
            log = entry['log_level'].strip() + ": " + entry['log_message']
            self._storage.append(log)


def main() -> None:
    print("=== Code Nexus - Data Processor ===\n")

    print("Testing Numeric Processor...")
    numeric = NumericProcessor()
    print(f" Trying to validate input '42': {numeric.validate(42)}")
    print(f" Trying to validate input 'Hello': {numeric.validate('Hello')}")
    print(" Test invalid ingestion of string 'foo' without prior validation:")
    try:
        numeric.ingest('foo')
    except ValueError as e:
        print(f" Got exception: {e}")
    print(" Processing data: [1, 2, 3, 4, 5]")
    numeric.ingest([1, 2, 3, 4, 5])
    print(" Extracting 3 values...")
    for _ in range(3):
        rank, value = numeric.output()
        print(f" Numeric value {rank}: {value}")
    print()
    print("Testing Text Processor...")
    text = TextProcessor()
    print(f" Trying to validate input '42': {text.validate(42)}")
    print(" Processing data: ['Hello', 'Nexus', 'World']")
    text.ingest(['Hello', 'Nexus', 'World'])
    print(" Extracting 1 value...")
    rank, value = text.output()
    print(f" Text value {rank}: {value}")
    print()
    print("Testing Log Processor...")
    log = LogProcessor()
    print(f" Trying to validate input 'Hello': {log.validate('Hello')}")
    log_data = [
        {'log_level': 'NOTICE', 'log_message': 'Connection to server'},
        {'log_level': 'ERROR ', 'log_message': 'Unauthorized access!!'},
    ]
    print(f" Processing data: {log_data}")
    log.ingest(log_data)
    print(" Extracting 2 values...")
    for _ in range(2):
        rank, value = log.output()
        print(f"Log entry {rank}: {value}")


if __name__ == "__main__":
    main()
