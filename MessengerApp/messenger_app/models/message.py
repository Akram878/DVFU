from __future__ import annotations

from abc import ABC, abstractmethod
from dataclasses import dataclass
from datetime import datetime, timezone
from typing import Optional

from .user import User


@dataclass
class Message(ABC):
    id: str
    sender: User
    receiver: User
    timestamp: datetime

    @abstractmethod
    def display_summary(self) -> str:  # polymorphic
        raise NotImplementedError


@dataclass
class TextMessage(Message):
    content: str

    def display_summary(self) -> str:
        return self.content


@dataclass
class ImageMessage(Message):
    image_url: str
    caption: Optional[str] = None

    def display_summary(self) -> str:
        return f"[image] {self.caption or self.image_url}"


@dataclass
class FileMessage(Message):
    file_name: str
    file_size_bytes: int

    def display_summary(self) -> str:
        size_kb = self.file_size_bytes / 1024
        return f"[file] {self.file_name} ({size_kb:.1f} KB)"


def utcnow() -> datetime:
    return datetime.now(timezone.utc)

