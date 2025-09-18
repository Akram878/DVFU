# MessengerApp

A clean, object-oriented messenger application built with Python. It demonstrates encapsulation, inheritance, and polymorphism with a simple CLI.

## Features
- Register users (including admin users)
- Create chats with 2+ participants
- Send polymorphic messages: text, image, file
- List messages in a chat
- Update user status (Online/Offline)
- Search users by name

## Project Structure
```
MessengerApp/
  messenger_app/
    models/
      user.py        # User, AdminUser, UserStatus
      message.py     # Message base, TextMessage, ImageMessage, FileMessage
      chat.py        # Chat aggregate
    services/
      messenger.py   # MessengerApp service orchestrating operations
    __init__.py
  app.py             # CLI entrypoint
  pyproject.toml     # Packaging metadata and entrypoint alias
  README.md
```

## Requirements
- Python 3.10+

## Run (from project root)
```bash
python app.py
```

Or install an entrypoint with pipx/pip (optional):
```bash
pip install -e .
messengerapp
```

## CLI Walkthrough
1. Register at least two users.
2. Create a chat with their user IDs (comma-separated).
3. Send messages and view them in option 5.

## Notes on OOP Principles
- Encapsulation via properties/getters/setters in `User` for `name` and `status`.
- Inheritance via `AdminUser(User)`.
- Polymorphism via `Message` abstract base with `TextMessage`, `ImageMessage`, and `FileMessage`.