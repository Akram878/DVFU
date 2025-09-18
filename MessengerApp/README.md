## MessengerApp

MessengerApp is a simple, object-oriented messaging application implemented in Python. It demonstrates core OOP principles (encapsulation, inheritance, polymorphism) and provides a minimal CLI to interact with users, chats, and messages.

### Requirements
- Python 3.9+
- No external dependencies

### Project Structure
```
MessengerApp/
  messenger_app/
    models/
    services/
    cli/
  run.py
  requirements.txt
  README.md
```

### Quickstart
1) Create a virtual environment (optional but recommended):
```bash
python3 -m venv .venv && source .venv/bin/activate
```

2) Install requirements (none are needed, but this ensures parity):
```bash
pip install -r requirements.txt
```

3) Run the CLI:
```bash
python run.py
```

From the CLI, type `help` to see available commands.

### Notes
- All data is in-memory only.
- This code is designed for clarity and scalability, not persistence or networking.

