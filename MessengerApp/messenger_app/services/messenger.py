from __future__ import annotations

from dataclasses import dataclass
from datetime import datetime, timezone
from typing import Dict, List, Optional, Sequence
from uuid import uuid4

from messenger_app.models.chat import Chat
from messenger_app.models.message import FileMessage, ImageMessage, Message, TextMessage
from messenger_app.models.user import AdminUser, User, UserStatus


@dataclass
class MessengerApp:
    """Main application service to manage users, chats, and messaging."""

    users_by_id: Dict[str, User]
    chats_by_id: Dict[str, Chat]

    def __init__(self) -> None:
        self.users_by_id = {}
        self.chats_by_id = {}

    # User management
    def register_user(self, name: str, is_admin: bool = False) -> User:
        user_id = str(uuid4())
        user: User = AdminUser(user_id, name) if is_admin else User(user_id, name)
        self.users_by_id[user_id] = user
        return user

    def set_user_status(self, user_id: str, status: UserStatus) -> None:
        user = self._require_user(user_id)
        user.status = status

    def find_users_by_name(self, query: str) -> List[User]:
        q = query.strip().lower()
        return [u for u in self.users_by_id.values() if q in u.name.lower()]

    def get_user(self, user_id: str) -> Optional[User]:
        return self.users_by_id.get(user_id)

    # Chat management
    def create_chat(self, participant_ids: Sequence[str]) -> Chat:
        if len(participant_ids) < 2:
            raise ValueError("A chat requires at least two participants")
        for pid in participant_ids:
            self._require_user(pid)
        chat_id = str(uuid4())
        chat = Chat(id=chat_id)
        for pid in participant_ids:
            chat.add_participant(pid)
        self.chats_by_id[chat_id] = chat
        return chat

    def get_chat(self, chat_id: str) -> Optional[Chat]:
        return self.chats_by_id.get(chat_id)

    # Messaging operations (polymorphic message types)
    def send_text(self, chat_id: str, sender_id: str, content: str) -> TextMessage:
        chat = self._require_chat(chat_id)
        self._require_participant(chat, sender_id)
        msg = TextMessage(id=str(uuid4()), chat_id=chat_id, sender_id=sender_id,
                          timestamp=datetime.now(timezone.utc), content=content)
        chat.add_message(msg)
        return msg

    def send_image(self, chat_id: str, sender_id: str, url: str, caption: Optional[str] = None) -> ImageMessage:
        chat = self._require_chat(chat_id)
        self._require_participant(chat, sender_id)
        msg = ImageMessage(id=str(uuid4()), chat_id=chat_id, sender_id=sender_id,
                           timestamp=datetime.now(timezone.utc), url=url, caption=caption)
        chat.add_message(msg)
        return msg

    def send_file(self, chat_id: str, sender_id: str, filename: str, file_url: str, size_bytes: int) -> FileMessage:
        chat = self._require_chat(chat_id)
        self._require_participant(chat, sender_id)
        msg = FileMessage(id=str(uuid4()), chat_id=chat_id, sender_id=sender_id,
                          timestamp=datetime.now(timezone.utc), filename=filename, file_url=file_url, size_bytes=size_bytes)
        chat.add_message(msg)
        return msg

    def list_messages(self, chat_id: str) -> List[Message]:
        chat = self._require_chat(chat_id)
        return chat.get_messages()

    # Helpers
    def _require_user(self, user_id: str) -> User:
        user = self.get_user(user_id)
        if not user:
            raise KeyError(f"User not found: {user_id}")
        return user

    def _require_chat(self, chat_id: str) -> Chat:
        chat = self.get_chat(chat_id)
        if not chat:
            raise KeyError(f"Chat not found: {chat_id}")
        return chat

    def _require_participant(self, chat: Chat, user_id: str) -> None:
        if user_id not in chat.participant_ids:
            raise PermissionError("User is not a participant of the chat")

