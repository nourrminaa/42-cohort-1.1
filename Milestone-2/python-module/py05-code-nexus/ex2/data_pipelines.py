import abc
import typing


class DataProcessor(abc.ABC):
    def __init__(self, name: str) -> None:
        self._storage: list[str] = []
        self._rank: int = 0
        self._total: int = 0
        self._name: str = name

    @abc.abstractmethod
    def validate(self, data: typing.Any) -> bool:
        pass

    @abc.abstractmethod
    def ingest(self, data: typing.Any) -> None:
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

    def stats(self) -> tuple[str, int, int]:
        return (self._name, self._total, len(self._storage))


class NumericProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__("Numeric Processor")

    def validate(self, data: typing.Any) -> bool:
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
                self._total += 1
        else:
            self._storage.append(str(data))
            self._total += 1


class TextProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__("Text Processor")

    def validate(self, data: typing.Any) -> bool:
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
            for item in data:
                self._storage.append(item)
                self._total += 1
        else:
            self._storage.append(data)
            self._total += 1


class LogProcessor(DataProcessor):
    def __init__(self) -> None:
        super().__init__("Log Processor")

    def validate(self, data: typing.Any) -> bool:
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
            self._total += 1


class ExportPlugin(typing.Protocol):
    def process_output(self, data: list[tuple[int, str]]) -> None:
        ...


class CSVExportPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        line = ""
        for i in range(len(data)):
            _, value = data[i]
            if i > 0:
                line += ","
            line += value
        print(f"CSV Output: {line}")


class JSONExportPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        line = ""
        for i in range(len(data)):
            rank, value = data[i]
            if i > 0:
                line += ", "
            line += f'"item_{rank}": "{value}"'
        print(f"JSON Output: {{{line}}}")


class DataStream:
    def __init__(self) -> None:
        self._processors: list[DataProcessor] = []

    def register_processor(self, proc: DataProcessor) -> None:
        self._processors.append(proc)

    def process_stream(self, stream: list[typing.Any]) -> None:
        for e in stream:
            handled = False
            for proc in self._processors:
                if proc.validate(e):
                    proc.ingest(e)
                    handled = True
                    break
            if handled is False:
                print(f"DataStream error - Can't process element\
                       in stream: {e}")

    def output_pipeline(self, nb: int, plugin: ExportPlugin) -> None:
        for proc in self._processors:
            data: list[tuple[int, str]] = []
            for _ in range(nb):
                _, _, remaining = proc.stats()
                if remaining == 0:
                    break
                data.append(proc.output())
            plugin.process_output(data)

    def print_processors_stats(self) -> None:
        print("== DataStream statistics ==")
        if len(self._processors) == 0:
            print("No processor found, no data")
            return
        for proc in self._processors:
            name, total, remaining = proc.stats()
            print(f"{name}: total {total} items processed, \
                  remaining {remaining} on processor")


def main() -> None:
    print("=== Code Nexus - Data Pipeline ===")

    print("Initialize Data Stream...")
    stream = DataStream()
    stream.print_processors_stats()

    print("Registering Processors")
    numeric = NumericProcessor()
    text = TextProcessor()
    log = LogProcessor()
    stream.register_processor(numeric)
    stream.register_processor(text)
    stream.register_processor(log)

    batch1 = [
        'Hello world',
        [3.14, -1, 2.71],
        [
            {'log_level': 'WARNING',
                'log_message': 'Telnet access! Use ssh instead'},
            {'log_level': 'INFO', 'log_message': 'User wil is connected'},
        ],
        42,
        ['Hi', 'five'],
    ]

    print(f"Send first batch of data on stream: {batch1}")
    stream.process_stream(batch1)
    stream.print_processors_stats()

    print("Send 3 processed data from each processor to a CSV plugin:")
    csv_plugin = CSVExportPlugin()
    stream.output_pipeline(3, csv_plugin)
    stream.print_processors_stats()

    batch2 = [
        21,
        ['I love AI', 'LLMs are wonderful', 'Stay healthy'],
        [
            {'log_level': 'ERROR', 'log_message': '500 server crash'},
            {'log_level': 'NOTICE',
             'log_message': 'Certificate expires in 10 days'},
        ],
        [32, 42, 64, 84, 128, 168],
        'World hello ',
    ]

    print(f"Send another batch of data: {batch2}")
    stream.process_stream(batch2)
    stream.print_processors_stats()

    print("Send 5 processed data from each processor to a JSON plugin:")
    json_plugin = JSONExportPlugin()
    stream.output_pipeline(5, json_plugin)
    stream.print_processors_stats()


if __name__ == "__main__":
    main()
