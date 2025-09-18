# MessengerApp

A comprehensive Object-Oriented messaging application built in Java, demonstrating core OOP principles including encapsulation, inheritance, and polymorphism.

## Features

### Core Functionality
- **User Management**: Register users and admin users with different privileges
- **Messaging System**: Send text, image, and file messages between users
- **Chat Management**: Create private and group chats
- **Status Management**: Update and track user online/offline status
- **User Search**: Find users by name with partial matching
- **Message History**: View conversation history and message details

### OOP Principles Demonstrated

#### Encapsulation
- All model classes use private fields with public getters and setters
- Data validation and business logic encapsulated within appropriate classes
- Clean separation of concerns between different components

#### Inheritance
- `AdminUser` extends `User` class with additional administrative privileges
- Clear parent-child relationship demonstrating inheritance benefits

#### Polymorphism
- Abstract `Message` class with concrete implementations:
  - `TextMessage` - Simple text messages
  - `ImageMessage` - Image messages with captions and metadata
  - `FileMessage` - File attachments with MIME type detection
- All message types can be handled uniformly through the base `Message` interface

## Project Structure

```
MessengerApp/
├── src/main/java/
│   └── com/messengerapp/
│       ├── models/
│       │   ├── User.java              # Base user class
│       │   ├── AdminUser.java         # Admin user (inheritance)
│       │   ├── Message.java           # Abstract message class
│       │   ├── TextMessage.java       # Text message implementation
│       │   ├── ImageMessage.java      # Image message implementation
│       │   ├── FileMessage.java       # File message implementation
│       │   └── Chat.java              # Chat conversation management
│       ├── cli/
│       │   └── MessengerCLI.java      # Command-line interface
│       └── MessengerApp.java          # Main application controller
├── pom.xml                            # Maven configuration
└── README.md                          # This file
```

## Getting Started

### Prerequisites
- Java 8 or higher
- Maven 3.6+ (optional, for dependency management)

### Running the Application

#### Option 1: Using Maven (Recommended)
```bash
# Navigate to project directory
cd MessengerApp

# Compile the project
mvn compile

# Run the application
mvn exec:java -Dexec.mainClass="com.messengerapp.cli.MessengerCLI"
```

#### Option 2: Using Java directly
```bash
# Navigate to project directory
cd MessengerApp

# Compile all Java files
javac -d target/classes -cp src/main/java src/main/java/com/messengerapp/**/*.java

# Run the application
java -cp target/classes com.messengerapp.cli.MessengerCLI
```

### Using the Application

The application provides an interactive command-line interface with the following options:

1. **Register New User** - Create a regular user account
2. **Register New Admin User** - Create an admin user with additional privileges
3. **View All Users** - Display all registered users and their status
4. **Search Users** - Find users by name (partial matching supported)
5. **Update User Status** - Change user status (Online/Offline/Away/Busy)
6. **Send Message** - Send text messages between users
7. **View User Chats** - Display all chats for a specific user
8. **Display Chat Messages** - Show message history for a conversation
9. **Create Group Chat** - Create group conversations with multiple participants
10. **Send Image Message** - Send image files with optional captions
11. **Send File Message** - Send file attachments
12. **App Statistics** - View application usage statistics

## Class Documentation

### User Classes

#### User
- **Properties**: id, name, status
- **Methods**: Status management, online/offline tracking
- **Demonstrates**: Encapsulation with private fields and public methods

#### AdminUser (extends User)
- **Additional Properties**: permissions, canModerateChats
- **Additional Methods**: Permission management, user moderation
- **Demonstrates**: Inheritance with extended functionality

### Message Classes

#### Message (Abstract)
- **Properties**: id, senderId, receiverId, timestamp, status
- **Abstract Methods**: getContent(), getMessageType(), displayMessage()
- **Demonstrates**: Polymorphism through abstract base class

#### TextMessage, ImageMessage, FileMessage
- **Concrete implementations** of Message class
- **Demonstrates**: Polymorphism with different message types handled uniformly

### Chat Class
- **Properties**: chatId, participantIds, messages, chatType
- **Methods**: Message management, participant handling
- **Supports**: Both private (1-on-1) and group chats

### MessengerApp Class
- **Central controller** managing users and chats
- **Methods**: User registration, message sending, chat creation
- **Demonstrates**: Composition and aggregation relationships

## Key OOP Concepts Illustrated

1. **Encapsulation**
   - Private fields with controlled access through getters/setters
   - Data validation within setter methods
   - Business logic encapsulated in appropriate classes

2. **Inheritance**
   - AdminUser inherits from User and extends functionality
   - Method overriding (toString methods)
   - Access to parent class methods and properties

3. **Polymorphism**
   - Message hierarchy allows different message types to be handled uniformly
   - Abstract methods implemented differently in each subclass
   - Runtime type determination for appropriate behavior

4. **Abstraction**
   - Abstract Message class defines interface without implementation
   - Complex operations hidden behind simple method calls
   - Clear separation between interface and implementation

## Demo Data

The application automatically creates demo users when started:
- Alice Johnson (Regular User)
- Bob Smith (Regular User)  
- Admin User (Admin User)

These users are set to online status for immediate testing of messaging features.

## Future Enhancements

- Database integration for persistent storage
- Real-time messaging with WebSocket support
- GUI interface using JavaFX or Swing
- Message encryption and security features
- File upload/download functionality
- User authentication and authorization
- Message search and filtering
- Emoji and rich text support

## Contributing

This project serves as an educational example of OOP principles in Java. Feel free to extend the functionality or use it as a reference for learning object-oriented programming concepts.

## License

This project is created for educational purposes and is free to use and modify.