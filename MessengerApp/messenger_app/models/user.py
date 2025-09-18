from __future__ import annotations

from dataclasses import dataclass, field
from enum import Enum
from typing import Optional


class UserStatus(str, Enum):
    ONLINE = "Online"
    OFFLINE = "Offline"


@dataclass
class User:
    """Represents a basic user in the messenger system.

    Encapsulates fields with properties to allow validation and future changes
    without breaking external code.
    """

    _id: str
    _name: str
    _status: UserStatus = field(default=UserStatus.OFFLINE)

    # Encapsulated id with getter only to keep it immutable post-creation
    @property
    def id(self) -> str:
        return self._id

    # Encapsulated name with getter/setter
    @property
    def name(self) -> str:
        return self._name

    @name.setter
    def name(self, value: str) -> None:
        value = value.strip()
        if not value:
            raise ValueError("User name cannot be empty")
        self._name = value

    # Encapsulated status with getter/setter
    @property
    def status(self) -> UserStatus:
        return self._status

    @status.setter
    def status(self, value: UserStatus) -> None:
        if not isinstance(value, UserStatus):
            raise ValueError("status must be a UserStatus enum value")
        self._status = value

    def is_online(self) -> bool:
        return self._status == UserStatus.ONLINE


class AdminUser(User):
    """Specialized user with administrative capabilities.

    Demonstrates inheritance from the base User.
    """

    def __init__(self, user_id: str, name: str) -> None:
        super().__init__(user_id, name, UserStatus.OFFLINE)
        self._is_admin = True

    @property
    def is_admin(self) -> bool:
        return True

