from __future__ import annotations

import uuid
from dataclasses import dataclass, field
from typing import Dict, List, Iterable

from messenger_app.models.chat import Chat
from messenger_app.models.message import (
    Message,
    TextMessage,
    ImageMessage,
    FileMessage,
    utcnow,
)
from messenger_app.models.user import User, AdminUser, UserStatus


def _new_id(prefix: str) -> str:
    return f"{prefix}_{uuid.uuid4().hex[:8]}"


@dataclass
class MessengerService:
    users: Dict[str, User] = field(default_factory=dict)
    chats: Dict[str, Chat] = field(default_factory=dict)

    # Users
    def register_user(self, name: str, is_admin: bool = False) -> User:
        user_id = _new_id("usr")
        user: User = AdminUser(user_id, name.strip(), UserStatus.OFFLINE) if is_admin else User(
            user_id, name.strip(), UserStatus.OFFLINE
        )
        self.users[user_id] = user
        return user

    def list_users(self) -> List[User]:
        return list(self.users.values())

    def update_user_status(self, user_id: str, status: str | UserStatus) -> None:
        user = self._get_user(user_id)
        if isinstance(status, str):
            normalized = status.strip().lower()
            if normalized == "online":
                user.status = UserStatus.ONLINE
            elif normalized == "offline":
                user.status = UserStatus.OFFLINE
            else:
                raise ValueError("Status must be Online or Offline")
        else:
            user.status = status

    def search_users(self, query: str) -> List[User]:
        q = query.strip().lower()
        return [u for u in self.users.values() if q in u.name.lower()]

    # Chats
    def create_chat(self, participants: Iterable[User]) -> Chat:
        unique = []
        seen = set()
        for u in participants:
            if u.id not in seen:
                unique.append(u)
                seen.add(u.id)
        if len(unique) < 2:
            raise ValueError("A chat requires at least two distinct participants")
        chat_id = _new_id("cht")
        chat = Chat(id=chat_id, participants=unique)
        self.chats[chat_id] = chat
        return chat

    def create_or_get_chat_by_identifiers(self, identifiers: List[str]) -> Chat:
        users = [self._get_user_by_identifier(x) for x in identifiers]
        # Try to find an existing chat with the same participant set
        target_ids = {u.id for u in users}
        for chat in self.chats.values():
            if {u.id for u in chat.participants} == target_ids:
                return chat
        return self.create_chat(users)

    def get_chat_messages(self, chat_id: str) -> List[Message]:
        chat = self._get_chat(chat_id)
        return list(chat.messages)

    # Messaging (polymorphic)
    def send_text_message(self, chat_id: str, sender_id: str, content: str) -> TextMessage:
        chat = self._get_chat(chat_id)
        sender = self._get_user(sender_id)
        # naive: use the first non-sender as receiver if group chat; receivers are used for validation
        receiver = next(u for u in chat.participants if u.id != sender.id)
        msg = TextMessage(id=_new_id("msg"), sender=sender, receiver=receiver, timestamp=utcnow(), content=content)
        chat.add_message(msg)
        return msg

    def send_image_message(self, chat_id: str, sender_id: str, image_url: str, caption: str | None = None) -> ImageMessage:
        chat = self._get_chat(chat_id)
        sender = self._get_user(sender_id)
        receiver = next(u for u in chat.participants if u.id != sender.id)
        msg = ImageMessage(id=_new_id("msg"), sender=sender, receiver=receiver, timestamp=utcnow(), image_url=image_url, caption=caption)
        chat.add_message(msg)
        return msg

    def send_file_message(self, chat_id: str, sender_id: str, file_name: str, file_size_bytes: int) -> FileMessage:
        chat = self._get_chat(chat_id)
        sender = self._get_user(sender_id)
        receiver = next(u for u in chat.participants if u.id != sender.id)
        msg = FileMessage(id=_new_id("msg"), sender=sender, receiver=receiver, timestamp=utcnow(), file_name=file_name, file_size_bytes=file_size_bytes)
        chat.add_message(msg)
        return msg

    # Helpers
    def _get_user(self, user_id: str) -> User:
        if user_id not in self.users:
            raise KeyError(f"User not found: {user_id}")
        return self.users[user_id]

    def _get_chat(self, chat_id: str) -> Chat:
        if chat_id not in self.chats:
            raise KeyError(f"Chat not found: {chat_id}")
        return self.chats[chat_id]

    def _get_user_by_identifier(self, identifier: str) -> User:
        ident = identifier.strip()
        if ident in self.users:
            return self.users[ident]
        # fallback: find by name exact match, else partial single match
        exact = [u for u in self.users.values() if u.name == ident]
        if len(exact) == 1:
            return exact[0]
        partial = [u for u in self.users.values() if ident.lower() in u.name.lower()]
        if len(partial) == 1:
            return partial[0]
        raise KeyError(f"User identifier ambiguous or not found: {identifier}")

