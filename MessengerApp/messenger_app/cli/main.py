from __future__ import annotations

from messenger_app.services.app import MessengerService


def main() -> None:
    service = MessengerService()

    print("MessengerApp CLI. Type 'help' for commands. 'quit' to exit.")
    while True:
        try:
            raw = input("> ").strip()
        except (EOFError, KeyboardInterrupt):
            print()
            break

        if not raw:
            continue

        if raw in {"quit", "exit"}:
            break

        if raw == "help":
            print(
                "Commands:\n"
                "  register <name>                 - Register a new user\n"
                "  users                           - List users\n"
                "  status <user_id> <Online|Offline> - Update user status\n"
                "  chat <name_or_id>[,<name_or_id>...] - Create/open chat with users\n"
                "  send <chat_id> <sender_id> <message> - Send text message\n"
                "  show <chat_id>                  - Show chat messages\n"
                "  find <query>                    - Search users by name\n"
                "  help                            - Show this help\n"
                "  quit                            - Exit"
            )
            continue

        parts = raw.split()
        cmd = parts[0]

        try:
            if cmd == "register" and len(parts) >= 2:
                name = " ".join(parts[1:])
                user = service.register_user(name)
                print(f"Registered user {user.name} with id {user.id}")
            elif cmd == "users":
                for u in service.list_users():
                    print(f"{u.id}: {u.name} [{u.status.value}]")
            elif cmd == "status" and len(parts) == 3:
                user_id = parts[1]
                status_str = parts[2]
                service.update_user_status(user_id, status_str)
                print("Status updated")
            elif cmd == "chat" and len(parts) >= 2:
                targets = " ".join(parts[1:]).split(",")
                chat = service.create_or_get_chat_by_identifiers(targets)
                print(f"Chat {chat.id} with {[u.name for u in chat.participants]}")
            elif cmd == "send" and len(parts) >= 4:
                chat_id = parts[1]
                sender_id = parts[2]
                content = " ".join(parts[3:])
                msg = service.send_text_message(chat_id, sender_id, content)
                print(f"Sent: {msg.content}")
            elif cmd == "show" and len(parts) == 2:
                chat_id = parts[1]
                for m in service.get_chat_messages(chat_id):
                    print(f"[{m.timestamp.isoformat()}] {m.sender.name}: {m.display_summary()}")
            elif cmd == "find" and len(parts) >= 2:
                query = " ".join(parts[1:])
                results = service.search_users(query)
                for u in results:
                    print(f"{u.id}: {u.name} [{u.status.value}]")
            else:
                print("Unknown or malformed command. Type 'help'.")
        except Exception as exc:
            print(f"Error: {exc}")

