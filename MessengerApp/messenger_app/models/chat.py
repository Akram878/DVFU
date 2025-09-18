from __future__ import annotations

from dataclasses import dataclass, field
from typing import List, Set

from .message import Message


@dataclass
class Chat:
    """Represents a conversation among two or more users."""

    id: str
    participant_ids: Set[str] = field(default_factory=set)
    messages: List[Message] = field(default_factory=list)

    def add_participant(self, user_id: str) -> None:
        self.participant_ids.add(user_id)

    def remove_participant(self, user_id: str) -> None:
        self.participant_ids.discard(user_id)

    def add_message(self, message: Message) -> None:
        if message.sender_id not in self.participant_ids:
            raise ValueError("Sender must be a chat participant")
        self.messages.append(message)

    def get_messages(self) -> List[Message]:
        return list(self.messages)

