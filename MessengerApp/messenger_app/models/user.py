from __future__ import annotations

from dataclasses import dataclass
from enum import Enum
from typing import Optional


class UserStatus(Enum):
    ONLINE = "Online"
    OFFLINE = "Offline"


@dataclass
class User:
    _id: str
    _name: str
    _status: UserStatus = UserStatus.OFFLINE

    @property
    def id(self) -> str:
        return self._id

    @property
    def name(self) -> str:
        return self._name

    @name.setter
    def name(self, value: str) -> None:
        if not value or not value.strip():
            raise ValueError("User name cannot be empty")
        self._name = value.strip()

    @property
    def status(self) -> UserStatus:
        return self._status

    @status.setter
    def status(self, value: UserStatus) -> None:
        if not isinstance(value, UserStatus):
            raise TypeError("status must be a UserStatus")
        self._status = value


@dataclass
class AdminUser(User):
    _admin_notes: Optional[str] = None

    @property
    def admin_notes(self) -> Optional[str]:
        return self._admin_notes

    @admin_notes.setter
    def admin_notes(self, value: Optional[str]) -> None:
        self._admin_notes = value.strip() if isinstance(value, str) else value

