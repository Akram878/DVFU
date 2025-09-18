package com.messengerapp.cli;

import com.messengerapp.MessengerApp;
import com.messengerapp.models.*;
import java.util.*;

/**
 * Command Line Interface for the Messenger Application.
 * Provides an interactive interface for users to interact with the messenger.
 */
public class MessengerCLI {
    private MessengerApp app;
    private Scanner scanner;
    private boolean running;
    
    /**
     * Constructor initializes the CLI
     */
    public MessengerCLI() {
        this.app = new MessengerApp();
        this.scanner = new Scanner(System.in);
        this.running = true;
    }
    
    /**
     * Start the CLI application
     */
    public void start() {
        System.out.println("=================================");
        System.out.println("   Welcome to MessengerApp!");
        System.out.println("=================================");
        
        // Create some demo users for testing
        createDemoUsers();
        
        while (running) {
            displayMainMenu();
            handleUserChoice();
        }
        
        System.out.println("Thank you for using MessengerApp!");
        scanner.close();
    }
    
    /**
     * Create demo users for testing purposes
     */
    private void createDemoUsers() {
        app.registerUser("Alice Johnson");
        app.registerUser("Bob Smith");
        app.registerAdminUser("Admin User");
        
        // Set some users online
        List<User> users = new ArrayList<>(app.getAllUsers());
        if (users.size() >= 2) {
            app.updateUserStatus(users.get(0).getId(), User.UserStatus.ONLINE);
            app.updateUserStatus(users.get(1).getId(), User.UserStatus.ONLINE);
        }
        
        System.out.println("Demo users created for testing purposes.\n");
    }
    
    /**
     * Display the main menu options
     */
    private void displayMainMenu() {
        System.out.println("\n========== MAIN MENU ==========");
        System.out.println("1. Register New User");
        System.out.println("2. Register New Admin User");
        System.out.println("3. View All Users");
        System.out.println("4. Search Users");
        System.out.println("5. Update User Status");
        System.out.println("6. Send Message");
        System.out.println("7. View User Chats");
        System.out.println("8. Display Chat Messages");
        System.out.println("9. Create Group Chat");
        System.out.println("10. Send Image Message");
        System.out.println("11. Send File Message");
        System.out.println("12. App Statistics");
        System.out.println("0. Exit");
        System.out.println("===============================");
        System.out.print("Choose an option: ");
    }
    
    /**
     * Handle user's menu choice
     */
    private void handleUserChoice() {
        try {
            int choice = Integer.parseInt(scanner.nextLine().trim());
            
            switch (choice) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    registerAdminUser();
                    break;
                case 3:
                    app.displayAllUsers();
                    break;
                case 4:
                    searchUsers();
                    break;
                case 5:
                    updateUserStatus();
                    break;
                case 6:
                    sendTextMessage();
                    break;
                case 7:
                    viewUserChats();
                    break;
                case 8:
                    displayChatMessages();
                    break;
                case 9:
                    createGroupChat();
                    break;
                case 10:
                    sendImageMessage();
                    break;
                case 11:
                    sendFileMessage();
                    break;
                case 12:
                    displayStatistics();
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please enter a valid number.");
        }
    }
    
    /**
     * Register a new user
     */
    private void registerUser() {
        System.out.print("Enter user name: ");
        String name = scanner.nextLine().trim();
        
        if (!name.isEmpty()) {
            try {
                app.registerUser(name);
            } catch (IllegalArgumentException e) {
                System.out.println("Error: " + e.getMessage());
            }
        } else {
            System.out.println("Name cannot be empty.");
        }
    }
    
    /**
     * Register a new admin user
     */
    private void registerAdminUser() {
        System.out.print("Enter admin user name: ");
        String name = scanner.nextLine().trim();
        
        if (!name.isEmpty()) {
            try {
                app.registerAdminUser(name);
            } catch (IllegalArgumentException e) {
                System.out.println("Error: " + e.getMessage());
            }
        } else {
            System.out.println("Name cannot be empty.");
        }
    }
    
    /**
     * Search for users by name
     */
    private void searchUsers() {
        System.out.print("Enter search term: ");
        String searchTerm = scanner.nextLine().trim();
        
        List<User> results = app.searchUsersByName(searchTerm);
        
        System.out.println("\n=== Search Results ===");
        if (results.isEmpty()) {
            System.out.println("No users found matching: " + searchTerm);
        } else {
            System.out.println("Found " + results.size() + " user(s):");
            for (User user : results) {
                System.out.println("- " + user.getName() + " (" + user.getId() + ") - Status: " + user.getStatus());
            }
        }
        System.out.println("====================");
    }
    
    /**
     * Update a user's status
     */
    private void updateUserStatus() {
        app.displayAllUsers();
        System.out.print("Enter user ID: ");
        String userId = scanner.nextLine().trim();
        
        User user = app.findUserById(userId);
        if (user == null) {
            System.out.println("User not found.");
            return;
        }
        
        System.out.println("\nAvailable statuses:");
        User.UserStatus[] statuses = User.UserStatus.values();
        for (int i = 0; i < statuses.length; i++) {
            System.out.println((i + 1) + ". " + statuses[i]);
        }
        
        System.out.print("Choose status (1-" + statuses.length + "): ");
        try {
            int choice = Integer.parseInt(scanner.nextLine().trim());
            if (choice >= 1 && choice <= statuses.length) {
                app.updateUserStatus(userId, statuses[choice - 1]);
            } else {
                System.out.println("Invalid choice.");
            }
        } catch (NumberFormatException e) {
            System.out.println("Please enter a valid number.");
        }
    }
    
    /**
     * Send a text message between users
     */
    private void sendTextMessage() {
        app.displayAllUsers();
        
        System.out.print("Enter sender user ID: ");
        String senderId = scanner.nextLine().trim();
        
        System.out.print("Enter receiver user ID: ");
        String receiverId = scanner.nextLine().trim();
        
        System.out.print("Enter message content: ");
        String content = scanner.nextLine().trim();
        
        if (!content.isEmpty()) {
            app.sendTextMessage(senderId, receiverId, content);
        } else {
            System.out.println("Message content cannot be empty.");
        }
    }
    
    /**
     * Send an image message between users
     */
    private void sendImageMessage() {
        app.displayAllUsers();
        
        System.out.print("Enter sender user ID: ");
        String senderId = scanner.nextLine().trim();
        
        System.out.print("Enter receiver user ID: ");
        String receiverId = scanner.nextLine().trim();
        
        System.out.print("Enter image path: ");
        String imagePath = scanner.nextLine().trim();
        
        System.out.print("Enter caption (optional): ");
        String caption = scanner.nextLine().trim();
        
        if (!imagePath.isEmpty()) {
            app.sendImageMessage(senderId, receiverId, imagePath, caption);
        } else {
            System.out.println("Image path cannot be empty.");
        }
    }
    
    /**
     * Send a file message between users
     */
    private void sendFileMessage() {
        app.displayAllUsers();
        
        System.out.print("Enter sender user ID: ");
        String senderId = scanner.nextLine().trim();
        
        System.out.print("Enter receiver user ID: ");
        String receiverId = scanner.nextLine().trim();
        
        System.out.print("Enter file path: ");
        String filePath = scanner.nextLine().trim();
        
        if (!filePath.isEmpty()) {
            app.sendFileMessage(senderId, receiverId, filePath);
        } else {
            System.out.println("File path cannot be empty.");
        }
    }
    
    /**
     * View chats for a specific user
     */
    private void viewUserChats() {
        app.displayAllUsers();
        System.out.print("Enter user ID: ");
        String userId = scanner.nextLine().trim();
        
        app.displayUserChats(userId);
    }
    
    /**
     * Display messages in a specific chat
     */
    private void displayChatMessages() {
        app.displayAllUsers();
        System.out.print("Enter first user ID: ");
        String user1Id = scanner.nextLine().trim();
        
        System.out.print("Enter second user ID: ");
        String user2Id = scanner.nextLine().trim();
        
        Chat chat = app.findPrivateChat(user1Id, user2Id);
        if (chat != null) {
            chat.displayMessages();
        } else {
            System.out.println("No chat found between these users.");
        }
    }
    
    /**
     * Create a group chat
     */
    private void createGroupChat() {
        System.out.print("Enter group chat name: ");
        String chatName = scanner.nextLine().trim();
        
        if (chatName.isEmpty()) {
            System.out.println("Chat name cannot be empty.");
            return;
        }
        
        app.displayAllUsers();
        System.out.print("Enter participant user IDs (comma-separated): ");
        String participantsInput = scanner.nextLine().trim();
        
        if (participantsInput.isEmpty()) {
            System.out.println("Participants cannot be empty.");
            return;
        }
        
        List<String> participantIds = Arrays.asList(participantsInput.split(","));
        participantIds = participantIds.stream()
                .map(String::trim)
                .filter(id -> !id.isEmpty())
                .collect(ArrayList::new, ArrayList::add, ArrayList::addAll);
        
        app.createGroupChat(chatName, participantIds);
    }
    
    /**
     * Display application statistics
     */
    private void displayStatistics() {
        System.out.println("\n=== App Statistics ===");
        System.out.println("Total Users: " + app.getUserCount());
        System.out.println("Total Chats: " + app.getChatCount());
        
        long onlineUsers = app.getAllUsers().stream()
                .mapToLong(user -> user.getStatus() == User.UserStatus.ONLINE ? 1 : 0)
                .sum();
        
        System.out.println("Online Users: " + onlineUsers);
        
        long adminUsers = app.getAllUsers().stream()
                .mapToLong(user -> user instanceof AdminUser ? 1 : 0)
                .sum();
        
        System.out.println("Admin Users: " + adminUsers);
        
        int totalMessages = app.getAllChats().stream()
                .mapToInt(Chat::getMessageCount)
                .sum();
        
        System.out.println("Total Messages: " + totalMessages);
        System.out.println("=====================");
    }
    
    /**
     * Main method to start the application
     * @param args Command line arguments
     */
    public static void main(String[] args) {
        new MessengerCLI().start();
    }
}