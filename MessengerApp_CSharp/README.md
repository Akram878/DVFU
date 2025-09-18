# MessengerApp (C#)

A clean, object-oriented messenger application built in C# demonstrating encapsulation, inheritance, and polymorphism, with a simple console UI.

## Features
- Register users (including admin users)
- Create chats with 2+ participants
- Send polymorphic messages: text, image, file
- List messages in a chat
- Update user status (Online/Offline)
- Search users by name or ID

## Structure
```
MessengerApp_CSharp/
  MessengerApp.sln
  src/
    MessengerApp/
      MessengerApp.csproj
      Program.cs           # Console UI
      Models/
        User.cs            # User, AdminUser, UserStatus
        Message.cs         # Message base, TextMessage, ImageMessage, FileMessage
        Chat.cs            # Chat aggregate
      Services/
        MessengerService.cs# App service orchestrating operations
```

## Build & Run
Requires .NET SDK 8.0 or newer.

```bash
# from MessengerApp_CSharp
dotnet build

dotnet run --project src/MessengerApp/MessengerApp.csproj
```

## Quick CLI Flow
1. Register at least two users.
2. Create a chat with their user IDs (comma-separated GUIDs).
3. Send messages and list them.

## OOP Notes
- Encapsulation: private fields and public properties on `User`.
- Inheritance: `AdminUser : User`.
- Polymorphism: abstract `Message` base with `TextMessage`, `ImageMessage`, `FileMessage`.