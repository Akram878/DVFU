from __future__ import annotations

from abc import ABC, abstractmethod
from dataclasses import dataclass
from datetime import datetime, timezone
from typing import List, Optional


@dataclass
class Message(ABC):
    """Abstract base message supporting polymorphic display.

    Subclasses represent specific message types (text, image, file).
    """

    id: str
    chat_id: str
    sender_id: str
    timestamp: datetime

    @abstractmethod
    def display(self) -> str:  # pragma: no cover - formatting
        """Return a human-readable representation of the message."""
        raise NotImplementedError


@dataclass
class TextMessage(Message):
    content: str

    def display(self) -> str:
        ts = self.timestamp.astimezone(timezone.utc).strftime("%Y-%m-%d %H:%M:%S UTC")
        return f"[{ts}] (text) {self.sender_id}: {self.content}"


@dataclass
class ImageMessage(Message):
    url: str
    caption: Optional[str] = None

    def display(self) -> str:
        ts = self.timestamp.astimezone(timezone.utc).strftime("%Y-%m-%d %H:%M:%S UTC")
        caption_part = f" caption=\"{self.caption}\"" if self.caption else ""
        return f"[{ts}] (image) {self.sender_id}: url={self.url}{caption_part}"


@dataclass
class FileMessage(Message):
    filename: str
    file_url: str
    size_bytes: int

    def display(self) -> str:
        ts = self.timestamp.astimezone(timezone.utc).strftime("%Y-%m-%d %H:%M:%S UTC")
        size_kb = self.size_bytes / 1024.0
        return f"[{ts}] (file) {self.sender_id}: {self.filename} ({size_kb:.1f} KB) -> {self.file_url}"

