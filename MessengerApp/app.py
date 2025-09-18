from __future__ import annotations

from typing import Optional

from messenger_app.models.user import UserStatus
from messenger_app.services.messenger import MessengerApp


def print_menu() -> None:
    print("\nMessengerApp CLI")
    print("1) Register user")
    print("2) List users")
    print("3) Create chat")
    print("4) Send text message")
    print("5) Show chat messages")
    print("6) Set user status")
    print("7) Search users")
    print("0) Quit")


def main() -> None:
    app = MessengerApp()
    chat_id: Optional[str] = None

    while True:
        print_menu()
        choice = input("Select an option: ").strip()

        try:
            if choice == "1":
                name = input("Enter user name: ").strip()
                is_admin = input("Is admin? (y/N): ").strip().lower() == "y"
                user = app.register_user(name=name, is_admin=is_admin)
                print(f"Registered user: {user.id} ({user.name}){' [ADMIN]' if hasattr(user, 'is_admin') and user.is_admin else ''}")

            elif choice == "2":
                if not app.users_by_id:
                    print("No users registered.")
                else:
                    for u in app.users_by_id.values():
                        print(f"- {u.id}: {u.name} [{u.status}]")

            elif choice == "3":
                ids = input("Enter comma-separated user IDs to include: ").split(",")
                ids = [i.strip() for i in ids if i.strip()]
                chat = app.create_chat(ids)
                chat_id = chat.id
                print(f"Created chat: {chat_id} with participants: {', '.join(chat.participant_ids)}")

            elif choice == "4":
                if not chat_id:
                    chat_id = input("Enter chat id: ").strip()
                sender = input("Enter sender user id: ").strip()
                content = input("Enter text content: ").strip()
                msg = app.send_text(chat_id, sender, content)
                print("Sent:", msg.display())

            elif choice == "5":
                if not chat_id:
                    chat_id = input("Enter chat id: ").strip()
                messages = app.list_messages(chat_id)
                if not messages:
                    print("No messages yet.")
                else:
                    for m in messages:
                        print(m.display())

            elif choice == "6":
                uid = input("Enter user id: ").strip()
                status_in = input("Enter status (Online/Offline): ").strip().capitalize()
                status = UserStatus.ONLINE if status_in == "Online" else UserStatus.OFFLINE
                app.set_user_status(uid, status)
                print("Updated.")

            elif choice == "7":
                q = input("Search query: ").strip()
                matches = app.find_users_by_name(q)
                for u in matches:
                    print(f"- {u.id}: {u.name} [{u.status}]")
                if not matches:
                    print("No matches.")

            elif choice == "0":
                print("Goodbye!")
                break

            else:
                print("Unknown option.")

        except Exception as exc:  # Simple CLI-friendly error handling
            print("Error:", exc)


if __name__ == "__main__":
    main()

