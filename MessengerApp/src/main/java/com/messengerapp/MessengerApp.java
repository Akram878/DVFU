package com.messengerapp;

import com.messengerapp.models.*;
import java.util.*;
import java.util.stream.Collectors;

/**
 * Main MessengerApp class that manages users, chats, and messaging functionality.
 * Serves as the central controller for the messenger application.
 */
public class MessengerApp {
    private Map<String, User> users;
    private Map<String, Chat> chats;
    private Scanner scanner;
    
    /**
     * Constructor initializes the messenger application
     */
    public MessengerApp() {
        this.users = new HashMap<>();
        this.chats = new HashMap<>();
        this.scanner = new Scanner(System.in);
    }
    
    /**
     * Register a new user in the system
     * @param name The user's name
     * @return The newly created User object
     */
    public User registerUser(String name) {
        if (name == null || name.trim().isEmpty()) {
            throw new IllegalArgumentException("User name cannot be empty");
        }
        
        User newUser = new User(name.trim());
        users.put(newUser.getId(), newUser);
        System.out.println("User registered successfully: " + newUser.getName() + " (ID: " + newUser.getId() + ")");
        return newUser;
    }
    
    /**
     * Register a new admin user in the system
     * @param name The admin user's name
     * @return The newly created AdminUser object
     */
    public AdminUser registerAdminUser(String name) {
        if (name == null || name.trim().isEmpty()) {
            throw new IllegalArgumentException("Admin user name cannot be empty");
        }
        
        AdminUser newAdmin = new AdminUser(name.trim());
        users.put(newAdmin.getId(), newAdmin);
        System.out.println("Admin user registered successfully: " + newAdmin.getName() + " (ID: " + newAdmin.getId() + ")");
        return newAdmin;
    }
    
    /**
     * Find a user by their ID
     * @param userId The user ID to search for
     * @return The User object or null if not found
     */
    public User findUserById(String userId) {
        return users.get(userId);
    }
    
    /**
     * Search for users by name (case-insensitive partial match)
     * @param name The name or partial name to search for
     * @return List of matching users
     */
    public List<User> searchUsersByName(String name) {
        if (name == null || name.trim().isEmpty()) {
            return new ArrayList<>();
        }
        
        String searchTerm = name.trim().toLowerCase();
        return users.values().stream()
                .filter(user -> user.getName().toLowerCase().contains(searchTerm))
                .collect(Collectors.toList());
    }
    
    /**
     * Update a user's status
     * @param userId The user ID
     * @param status The new status
     * @return true if status was updated successfully
     */
    public boolean updateUserStatus(String userId, User.UserStatus status) {
        User user = findUserById(userId);
        if (user != null) {
            user.setStatus(status);
            System.out.println("User " + user.getName() + " status updated to: " + status);
            return true;
        }
        return false;
    }
    
    /**
     * Create a private chat between two users
     * @param user1Id First user ID
     * @param user2Id Second user ID
     * @return The created Chat object or null if users don't exist
     */
    public Chat createPrivateChat(String user1Id, String user2Id) {
        User user1 = findUserById(user1Id);
        User user2 = findUserById(user2Id);
        
        if (user1 == null || user2 == null) {
            System.out.println("One or both users not found");
            return null;
        }
        
        // Check if private chat already exists
        Chat existingChat = findPrivateChat(user1Id, user2Id);
        if (existingChat != null) {
            System.out.println("Private chat already exists between these users");
            return existingChat;
        }
        
        Chat newChat = new Chat(user1Id, user2Id);
        chats.put(newChat.getChatId(), newChat);
        System.out.println("Private chat created between " + user1.getName() + " and " + user2.getName());
        return newChat;
    }
    
    /**
     * Create a group chat
     * @param chatName Name of the group chat
     * @param participantIds List of participant user IDs
     * @return The created Chat object or null if insufficient participants
     */
    public Chat createGroupChat(String chatName, List<String> participantIds) {
        if (participantIds.size() < 2) {
            System.out.println("Group chat requires at least 2 participants");
            return null;
        }
        
        // Verify all participants exist
        for (String userId : participantIds) {
            if (findUserById(userId) == null) {
                System.out.println("User not found: " + userId);
                return null;
            }
        }
        
        Chat newChat = new Chat(chatName, participantIds);
        chats.put(newChat.getChatId(), newChat);
        System.out.println("Group chat '" + chatName + "' created with " + participantIds.size() + " participants");
        return newChat;
    }
    
    /**
     * Send a text message between users
     * @param senderId Sender's user ID
     * @param receiverId Receiver's user ID
     * @param content Message content
     * @return true if message was sent successfully
     */
    public boolean sendTextMessage(String senderId, String receiverId, String content) {
        User sender = findUserById(senderId);
        User receiver = findUserById(receiverId);
        
        if (sender == null || receiver == null) {
            System.out.println("Sender or receiver not found");
            return false;
        }
        
        // Find or create private chat
        Chat chat = findPrivateChat(senderId, receiverId);
        if (chat == null) {
            chat = createPrivateChat(senderId, receiverId);
        }
        
        TextMessage message = new TextMessage(senderId, receiverId, content);
        boolean success = chat.addMessage(message);
        
        if (success) {
            System.out.println("Message sent from " + sender.getName() + " to " + receiver.getName());
            message.markAsDelivered();
        }
        
        return success;
    }
    
    /**
     * Send an image message between users
     * @param senderId Sender's user ID
     * @param receiverId Receiver's user ID
     * @param imagePath Path to the image
     * @param caption Optional caption for the image
     * @return true if message was sent successfully
     */
    public boolean sendImageMessage(String senderId, String receiverId, String imagePath, String caption) {
        User sender = findUserById(senderId);
        User receiver = findUserById(receiverId);
        
        if (sender == null || receiver == null) {
            System.out.println("Sender or receiver not found");
            return false;
        }
        
        Chat chat = findPrivateChat(senderId, receiverId);
        if (chat == null) {
            chat = createPrivateChat(senderId, receiverId);
        }
        
        ImageMessage message = new ImageMessage(senderId, receiverId, imagePath, caption);
        boolean success = chat.addMessage(message);
        
        if (success) {
            System.out.println("Image sent from " + sender.getName() + " to " + receiver.getName());
            message.markAsDelivered();
        }
        
        return success;
    }
    
    /**
     * Send a file message between users
     * @param senderId Sender's user ID
     * @param receiverId Receiver's user ID
     * @param filePath Path to the file
     * @return true if message was sent successfully
     */
    public boolean sendFileMessage(String senderId, String receiverId, String filePath) {
        User sender = findUserById(senderId);
        User receiver = findUserById(receiverId);
        
        if (sender == null || receiver == null) {
            System.out.println("Sender or receiver not found");
            return false;
        }
        
        Chat chat = findPrivateChat(senderId, receiverId);
        if (chat == null) {
            chat = createPrivateChat(senderId, receiverId);
        }
        
        FileMessage message = new FileMessage(senderId, receiverId, filePath);
        boolean success = chat.addMessage(message);
        
        if (success) {
            System.out.println("File sent from " + sender.getName() + " to " + receiver.getName());
            message.markAsDelivered();
        }
        
        return success;
    }
    
    /**
     * Find a private chat between two users
     * @param user1Id First user ID
     * @param user2Id Second user ID
     * @return The Chat object or null if not found
     */
    public Chat findPrivateChat(String user1Id, String user2Id) {
        return chats.values().stream()
                .filter(chat -> chat.getChatType() == Chat.ChatType.PRIVATE)
                .filter(chat -> {
                    List<String> participants = chat.getParticipantIds();
                    return participants.contains(user1Id) && participants.contains(user2Id);
                })
                .findFirst()
                .orElse(null);
    }
    
    /**
     * Get all chats for a specific user
     * @param userId The user ID
     * @return List of chats the user participates in
     */
    public List<Chat> getUserChats(String userId) {
        return chats.values().stream()
                .filter(chat -> chat.isParticipant(userId))
                .collect(Collectors.toList());
    }
    
    /**
     * Display all users in the system
     */
    public void displayAllUsers() {
        System.out.println("\n=== All Users ===");
        if (users.isEmpty()) {
            System.out.println("No users registered.");
        } else {
            users.values().forEach(user -> {
                System.out.println("- " + user.getName() + " (" + user.getId() + ") - Status: " + user.getStatus() + 
                                 (user instanceof AdminUser ? " [ADMIN]" : ""));
            });
        }
        System.out.println("================\n");
    }
    
    /**
     * Display all chats for a specific user
     * @param userId The user ID
     */
    public void displayUserChats(String userId) {
        User user = findUserById(userId);
        if (user == null) {
            System.out.println("User not found");
            return;
        }
        
        List<Chat> userChats = getUserChats(userId);
        System.out.println("\n=== Chats for " + user.getName() + " ===");
        if (userChats.isEmpty()) {
            System.out.println("No chats found.");
        } else {
            for (Chat chat : userChats) {
                System.out.println("- " + chat.getChatName() + " (" + chat.getChatType() + ") - " + 
                                 chat.getMessageCount() + " messages");
            }
        }
        System.out.println("========================\n");
    }
    
    /**
     * Get total number of users
     * @return Number of registered users
     */
    public int getUserCount() {
        return users.size();
    }
    
    /**
     * Get total number of chats
     * @return Number of chats
     */
    public int getChatCount() {
        return chats.size();
    }
    
    /**
     * Get all users
     * @return Collection of all users
     */
    public Collection<User> getAllUsers() {
        return new ArrayList<>(users.values());
    }
    
    /**
     * Get all chats
     * @return Collection of all chats
     */
    public Collection<Chat> getAllChats() {
        return new ArrayList<>(chats.values());
    }
}