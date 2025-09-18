package com.messengerapp.demo;

import com.messengerapp.MessengerApp;
import com.messengerapp.models.*;

/**
 * Demo class to showcase the MessengerApp functionality and OOP principles.
 * This class demonstrates how the application works without the CLI interface.
 */
public class MessengerDemo {
    
    public static void main(String[] args) {
        System.out.println("=== MessengerApp Demo ===\n");
        
        // Create the messenger application
        MessengerApp app = new MessengerApp();
        
        // Demonstrate user registration and inheritance
        System.out.println("1. USER REGISTRATION (Encapsulation & Inheritance)");
        System.out.println("---------------------------------------------------");
        
        User alice = app.registerUser("Alice Johnson");
        User bob = app.registerUser("Bob Smith");
        AdminUser admin = app.registerAdminUser("System Admin");
        
        // Demonstrate encapsulation - using getters/setters
        alice.setStatus(User.UserStatus.ONLINE);
        bob.setStatus(User.UserStatus.ONLINE);
        admin.setStatus(User.UserStatus.ONLINE);
        
        // Show inheritance - AdminUser has additional methods
        admin.addPermission("CUSTOM_PERMISSION");
        System.out.println("Admin permissions: " + admin.getPermissions().size());
        
        app.displayAllUsers();
        
        // Demonstrate polymorphism with different message types
        System.out.println("\n2. POLYMORPHISM - Different Message Types");
        System.out.println("------------------------------------------");
        
        // Send different types of messages (polymorphism)
        app.sendTextMessage(alice.getId(), bob.getId(), "Hello Bob! How are you?");
        app.sendTextMessage(bob.getId(), alice.getId(), "Hi Alice! I'm doing great, thanks!");
        
        app.sendImageMessage(alice.getId(), bob.getId(), "/photos/vacation.jpg", "Check out my vacation photos!");
        
        app.sendFileMessage(bob.getId(), alice.getId(), "/documents/report.pdf");
        
        // Demonstrate chat functionality
        System.out.println("\n3. CHAT MANAGEMENT");
        System.out.println("------------------");
        
        Chat privateChat = app.findPrivateChat(alice.getId(), bob.getId());
        if (privateChat != null) {
            privateChat.displayMessages();
        }
        
        // Demonstrate polymorphism - all message types handled uniformly
        System.out.println("4. POLYMORPHISM DEMONSTRATION");
        System.out.println("-----------------------------");
        
        if (privateChat != null) {
            System.out.println("Processing all messages polymorphically:");
            for (Message message : privateChat.getMessages()) {
                System.out.println("Message Type: " + message.getMessageType());
                System.out.println("Content: " + message.getContent());
                System.out.println("Status: " + message.getStatus());
                message.displayMessage(); // Polymorphic method call
                System.out.println();
            }
        }
        
        // Demonstrate search functionality
        System.out.println("5. USER SEARCH FUNCTIONALITY");
        System.out.println("-----------------------------");
        
        System.out.println("Searching for users with 'Alice':");
        app.searchUsersByName("Alice").forEach(user -> 
            System.out.println("Found: " + user.getName() + " (" + user.getId() + ")")
        );
        
        // Demonstrate group chat
        System.out.println("\n6. GROUP CHAT CREATION");
        System.out.println("----------------------");
        
        java.util.List<String> participants = java.util.Arrays.asList(
            alice.getId(), bob.getId(), admin.getId()
        );
        
        Chat groupChat = app.createGroupChat("Project Discussion", participants);
        
        if (groupChat != null) {
            // Send a message to the group (demonstrates group messaging)
            TextMessage groupMessage = new TextMessage(admin.getId(), alice.getId(), "Welcome to the project discussion group!");
            groupChat.addMessage(groupMessage);
            
            System.out.println("Group chat created with " + groupChat.getParticipantCount() + " participants");
        }
        
        // Display final statistics
        System.out.println("\n7. APPLICATION STATISTICS");
        System.out.println("-------------------------");
        System.out.println("Total Users: " + app.getUserCount());
        System.out.println("Total Chats: " + app.getChatCount());
        
        long adminCount = app.getAllUsers().stream()
            .mapToLong(user -> user instanceof AdminUser ? 1 : 0)
            .sum();
        
        System.out.println("Admin Users: " + adminCount);
        
        int totalMessages = app.getAllChats().stream()
            .mapToInt(Chat::getMessageCount)
            .sum();
        
        System.out.println("Total Messages: " + totalMessages);
        
        System.out.println("\n=== Demo Complete ===");
        System.out.println("\nKey OOP Principles Demonstrated:");
        System.out.println("• Encapsulation: Private fields with public getters/setters");
        System.out.println("• Inheritance: AdminUser extends User with additional functionality");
        System.out.println("• Polymorphism: Different message types (Text, Image, File) handled uniformly");
        System.out.println("• Abstraction: Abstract Message class with concrete implementations");
        System.out.println("\nRun MessengerCLI.main() for interactive experience!");
    }
}