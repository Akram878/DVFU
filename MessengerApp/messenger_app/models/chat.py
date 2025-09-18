from __future__ import annotations

from dataclasses import dataclass, field
from typing import List

from .message import Message
from .user import User


@dataclass
class Chat:
    id: str
    participants: List[User] = field(default_factory=list)
    messages: List[Message] = field(default_factory=list)

    def add_participant(self, user: User) -> None:
        if user not in self.participants:
            self.participants.append(user)

    def add_message(self, message: Message) -> None:
        if message.sender not in self.participants or message.receiver not in self.participants:
            raise ValueError("Both sender and receiver must be participants of the chat")
        self.messages.append(message)

